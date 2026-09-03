#pragma once
#include <Arduino.h>
#include <vector>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <Preferences.h>
#include "config.h"
#include "particle_system.h"
#include "sprites_data.h"
#include "u8g2_vietnamese.h"

static inline uint16_t parseHexColor565(const String& hex) {
  String h = hex;
  if (h.startsWith("#")) h = h.substring(1);
  if (h.length() == 6) {
    long rgb = strtol(h.c_str(), NULL, 16);
    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = rgb & 0xFF;
    return lgfx::color565(r, g, b);
  }
  return lgfx::color565(255, 184, 0); // Vàng Kim #FFB800
}

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789 _panel_instance;
  lgfx::Bus_SPI       _bus_instance;
  lgfx::Light_PWM     _light_instance;

public:
  LGFX(void) {
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host = VSPI_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000; // 40MHz
      cfg.pin_sclk = TFT_SCLK_PIN;
      cfg.pin_mosi = TFT_MOSI_PIN;
      cfg.pin_miso = -1;
      cfg.pin_dc   = TFT_DC_PIN;
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }
    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs           = TFT_CS_PIN;
      cfg.pin_rst          = TFT_RST_PIN;
      cfg.panel_width      = SCREEN_WIDTH;
      cfg.panel_height     = SCREEN_HEIGHT;
      cfg.offset_x         = SCREEN_OFFSET_X;
      cfg.offset_y         = SCREEN_OFFSET_Y;
      cfg.invert           = true;
      _panel_instance.config(cfg);
    }
    {
      auto cfg = _light_instance.config();
      cfg.pin_bl = TFT_BL_PIN;
      cfg.freq = 44100;
      cfg.pwm_channel = 7;
      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);
    }
    setPanel(&_panel_instance);
  }
};

class DisplayEngine {
public:
  static const int TOTAL_THEMES = 50;
  LGFX tft;
  LGFX_Sprite sprite;
  ParticleSystem particles;
  Preferences prefs;

  int currentSpriteIdx = 0;
  int currentPaletteIdx = 0;
  int lastSavedSpriteIdx = 0;
  int currentBrightness = 255;
  float floatAngle = 0.0f;
  float breathAngle = 0.0f;

  // Cấu hình Kiểu chữ & Bối cảnh trực tiếp từ Web Designer
  uint16_t currentTextColor = TFT_WHITE; // Trắng Kim Cương #FFFFFF chuẩn ảnh chụp thật
  uint8_t currentTextSize = 1;         // 1: 16px Chuẩn
  uint8_t currentSceneryId = 2;        // Mặc định: Mưa Cyberpunk siêu mượt chuẩn ảnh thật 100%

  String customQuote = "";

  bool needSavePrefs = false;
  unsigned long savePrefsTimer = 0;

  bool isQRMode = false;
  bool qrScreenRendered = false;
  bool isWifiActive = false;
  bool isWifiConnected = false;
  bool isCloudConnected = false;
  int wifiSecondsLeft = 0;
  int batteryPercent = 100;

  // Đo đạc FPS thực tế
  int frameCount = 0;
  int currentFps = 60;
  unsigned long lastFpsTime = 0;

  DisplayEngine() : sprite(&tft) {}

  void init() {
    tft.init();
    tft.setRotation(0);
    tft.setBrightness(currentBrightness);

    // Khởi tạo Canvas Framebuffer 172x320 16-bit RGB565
    sprite.setColorDepth(16);
    void* buffer = sprite.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!buffer) {
      Serial.println("[LỖI] Không đủ RAM tạo Framebuffer 172x320!");
    } else {
      Serial.println("[OK] Đã cấp phát Framebuffer 172x320 16-bit DMA!");
    }

    particles.init();

    prefs.begin("keychain", false);
    currentSpriteIdx = prefs.getInt("theme_id", 0);
    currentBrightness = prefs.getInt("bright", 255);
    currentSceneryId = prefs.getInt("scenery", 0);
    customQuote = prefs.getString("quote", "Ngủ ngon nhé cô bé đáng yêu của anh, chúc em mơ đẹp!");
    prefs.end();

    if (currentSpriteIdx < 0 || currentSpriteIdx >= TOTAL_THEMES) currentSpriteIdx = 0;
    lastSavedSpriteIdx = currentSpriteIdx;
    tft.setBrightness(currentBrightness);
  }

  static const char* getThemeDefaultQuote(int idx) {
    static const char* const QUOTES[50] = {
      "Dù ở thế giới nào, anh vẫn luôn tìm thấy em.",
      "Thế giới có 8 tỉ người, nhưng anh chỉ thích em!",
      "Lôi đình vạn trượng cũng chẳng bằng một nụ cười của em.",
      "Tình yêu của anh dành cho em như đại dương bất tận.",
      "Em là bông hoa đẹp nhất trong khu vườn của anh.",
      "Gió cuốn mây trôi, chỉ có tình yêu này là mãi mãi.",
      "Vô lượng không xứ cũng không chứa hết nỗi nhớ em.",
      "Nguyện bảo vệ em qua mọi bão giông cuộc đời.",
      "Trái tim anh đã rực cháy vì em từ ngày đầu gặp gỡ.",
      "Dù đi lạc khắp thế gian, anh vẫn sẽ tìm về bên em.",
      "Tự do lớn nhất của anh là được yêu em.",
      "Mọi nhẫn thuật đều vô nghĩa trước nụ cười của em.",
      "Hold me long enough\nand you will feel what\nI have already decided\nabout you.",
      "Lời nguyền ngọt ngào nhất là được bên em trọn kiếp.",
      "Ngọn lửa này sẽ sưởi ấm cho em suốt mùa đông dài.",
      "Năng lượng vô hạn cũng không sáng bằng mắt em.",
      "Dù thời gian đóng băng, tim anh vẫn đập vì em.",
      "Sấm sét rạch trời không sánh bằng tiếng sét ái tình.",
      "Ánh sáng bóng tối hòa quyện như đôi ta không rời.",
      "Chém tan mọi khoảng cách để đến bên em tức thì.",
      "Hái trăng sao trên trời cũng chỉ để em mỉm cười.",
      "Mục tiêu duy nhất cuộc đời anh là làm em hạnh phúc.",
      "Tình yêu của anh dành cho em lấp lánh như kim cương.",
      "Hai trái tim cùng chung một nhịp đập thiết tha.",
      "Mỗi nhịp tim đập đều mang tên người anh yêu.",
      "Bức thư tình này gửi trọn ngàn lời yêu thương.",
      "Yêu em không có điểm dừng, vĩnh cửu như vô cực.",
      "Bông hoa hồng đẹp nhất chỉ dành riêng tặng em.",
      "Mũi tên thần Cupid đã bắn trúng tim anh từ lâu.",
      "Chòm sao đẹp nhất trên trời là đôi mắt của em.",
      "Ngồi bên bếp lửa ấm, ngắm em cười là đủ bình yên.",
      "Liều thuốc ngọt ngào nhất thế gian chính là nụ cười em.",
      "Dù bay vào vũ trụ, trái tim anh vẫn hướng về em.",
      "Anh sẽ luôn ngoan ngoãn bên em như chú cún nhỏ.",
      "Em là viên trân châu ngọt ngào nhất cuộc đời anh.",
      "Anh nguyện làm chú thỏ nhỏ sưởi ấm cho em.",
      "Cả thế giới này dễ thương cũng không bằng em đâu!",
      "Boo! Dọa em một chút để em ôm anh thật chặt nè.",
      "Rồng con sẽ phun lửa sưởi ấm cho em mỗi đêm lạnh.",
      "Mang cả hạt dưa ngon nhất thế gian về cho em ăn.",
      "Gấu trúc nhỏ muốn ôm em ngủ mỗi ngày cơ.",
      "Cáo nhỏ cuộn tròn chúc em ngủ thật ngon nhé.",
      "Anh yêu em 3000, mãi mãi một tình yêu vững bền.",
      "Mục tiêu duy nhất trong tầm ngắm của anh là em.",
      "Chơi ván game nào cũng muốn có em là Player 2.",
      "Em là bình hồi máu quý giá nhất cuộc đời anh.",
      "Bản tình ca này chỉ muốn ngân vang cùng em mãi.",
      "Dù thế giới đảo điên, tình ta vẫn vẹn nguyên như cũ.",
      "Mọi dòng code anh viết đều hướng về tương lai có em.",
      "Em là trung tâm của cả vũ trụ trong lòng anh."
    };
    if (idx >= 0 && idx < 50) return QUOTES[idx];
    return "Ngủ ngon nhé cô bé đáng yêu của anh, chúc em mơ đẹp!";
  }

  static DisplayEngine& getInstance();

  void setTheme(int idx) {
    if (idx < 0) idx = TOTAL_THEMES - 1;
    if (idx >= TOTAL_THEMES) idx = 0;
    currentSpriteIdx = idx;
    needSavePrefs = true;
    savePrefsTimer = millis() + 3000;
  }

  void setSprite(int idx) { setTheme(idx); }

  void nextTheme() {
    setTheme(currentSpriteIdx + 1);
  }

  void nextSprite() { nextTheme(); }

  void cyclePalette() {
    currentPaletteIdx = (currentPaletteIdx + 1) % 6;
    particles.setPalette(currentPaletteIdx);
  }

  void updateBattery(int adc) {
    float v = (adc / 4095.0f) * 3.3f * 2.0f;
    batteryPercent = constrain((int)((v - 3.3f) / (4.2f - 3.3f) * 100.0f), 0, 100);
  }

  int getFPS() { return currentFps; }

  void dumpFramebuffer() {
    Serial.println("#RAW_START");
    uint16_t* buf = (uint16_t*)sprite.getBuffer();
    if (buf) {
      Serial.write((uint8_t*)buf, SCREEN_WIDTH * SCREEN_HEIGHT * 2);
    }
    Serial.println("\n#RAW_END");
  }

  void setBrightness(int b) {
    currentBrightness = constrain(b, 10, 255);
    tft.setBrightness(currentBrightness);
  }

  void setCustomQuote(const String& q) {
    customQuote = q;
    needSavePrefs = true;
    savePrefsTimer = millis() + 3000;
  }

  void setTextColor(uint16_t col) {
    currentTextColor = col;
  }

  void setTextSize(uint8_t sz) {
    currentTextSize = (sz >= 2) ? 2 : 1;
  }

  void setScenery(uint8_t sc) {
    currentSceneryId = sc % 9;
    needSavePrefs = true;
    savePrefsTimer = millis() + 3000;
  }

  void setQRMode(bool qr) {
    isQRMode = qr;
    qrScreenRendered = false;
    sprite.setTextDatum(textdatum_t::top_left);
  }

  void toggleQRMode() {
    isQRMode = !isQRMode;
    qrScreenRendered = false;
    sprite.setTextDatum(textdatum_t::top_left);
  }

  void setWifiStats(bool active, bool connected, bool cloud, int secLeft) {
    isWifiActive = active;
    isWifiConnected = connected;
    isCloudConnected = cloud;
    wifiSecondsLeft = secLeft;
  }

  void checkDelayedSave() {
    if (needSavePrefs && millis() > savePrefsTimer) {
      prefs.begin("keychain", false);
      prefs.putInt("theme_id", currentSpriteIdx);
      prefs.putInt("bright", currentBrightness);
      prefs.putInt("scenery", currentSceneryId);
      prefs.putString("quote", customQuote);
      prefs.end();
      needSavePrefs = false;
    }
  }

  // 1. LAYER 0: HỆ THỐNG 9 LIVING DIORAMAS 3D QUANG HỌC CHÂN THỰC (FULL-BLEED 90-100% REALISM)
  void renderLivingScenery(LGFX_Sprite* spr, float timeAngle) {
    switch (currentSceneryId) {
      case 0: {
        // SCENE_COZY_CAMPFIRE (Lửa Trại Rừng Sao Đêm):
        // Bầu trời đêm sâu thẳm tĩnh lặng, không có hạt chấm rơi
        for (int y = 0; y < 275; y += 8) {
          uint8_t b = 16 + y * 14 / 275;
          spr->fillRect(0, y, SCREEN_WIDTH, 8, lgfx::color565(3, 5, b));
        }
        // Rừng thông bạt ngàn neo ở đáy (Y = 275 - 295)
        for (int tr = 0; tr < 8; tr++) {
          int tx = tr * 24 - 8;
          spr->fillTriangle(tx, 295, tx + 16, 272, tx + 32, 295, lgfx::color565(10, 18, 28));
        }
        // Mặt đất đồi cỏ đêm (Y = 295 - 320)
        spr->fillRect(0, 295, SCREEN_WIDTH, 25, lgfx::color565(12, 20, 14));
        // Đống lửa trại ấm áp neo dưới đáy (Y = 290 - 305)
        spr->fillCircle(86, 305, 20, lgfx::color565(80, 35, 0));
        spr->fillRect(74, 308, 24, 4, lgfx::color565(60, 35, 30)); // Khúc củi
        int fFlap = (int)(sinf(timeAngle * 8.0f) * 2.0f);
        spr->fillTriangle(78, 308, 86 + fFlap, 292, 94, 308, 0xF800); // Ngọn lửa ngoài
        spr->fillTriangle(81, 308, 86 + fFlap / 2, 296, 91, 308, 0xFE40); // Lửa vàng
        spr->fillTriangle(83, 308, 86, 301, 89, 308, TFT_WHITE); // Tâm lửa
        break;
      }

      case 1: {
        // SCENE_SAKURA_SHRINE (Đền Thần Hoàng Hôn):
        for (int y = 0; y < 265; y += 8) {
          uint8_t r = 24 + y * 120 / 265;
          uint8_t g = 12 + y * 45 / 265;
          uint8_t b = 48 - y * 12 / 265;
          spr->fillRect(0, y, SCREEN_WIDTH, 8, lgfx::color565(r, g, b));
        }
        // Vầng trăng khuyết tĩnh lặng trên góc
        spr->fillCircle(142, 38, 8, lgfx::color565(255, 251, 230));
        spr->fillCircle(139, 36, 7, lgfx::color565(26, 13, 51));
        // Cổng Torii thần đạo neo chặt ở góc đáy (Y = 265 - 320)
        spr->fillRect(128, 270, 5, 50, lgfx::color565(185, 28, 28));
        spr->fillRect(152, 270, 5, 50, lgfx::color565(185, 28, 28));
        spr->fillRect(122, 271, 39, 4, 0x0000); // Mái đen
        spr->fillRect(125, 276, 33, 3, lgfx::color565(239, 68, 68)); // Xà đỏ
        break;
      }

      case 2: {
        // SCENE_CYBER_RAIN (Mưa Neon Cyberpunk Siêu Mượt 1:1 Toàn Màn Hình):
        // KHÔI PHỤC FULL MÀN HÌNH THEO YÊU CẦU NGƯỜI DÙNG: X = 0..172, Y = 0..320
        for (int i = 0; i < 36; i++) {
          int rx = (i * 19 + 7) % SCREEN_WIDTH;
          int speed = 260 + (i % 7) * 35;
          int ry = (int)((millis() * speed / 1000 + i * 29) % (SCREEN_HEIGHT + 30)) - 15;
          int len = 8 + (i % 5) * 3;
          uint16_t rainColor = (i % 3 == 0) ? 0x07FF : ((i % 3 == 1) ? 0x05DF : 0x035B);
          spr->drawFastVLine(rx, ry, len, rainColor);
          spr->drawPixel(rx, ry + len - 1, TFT_WHITE); // Hạt đầu mưa sáng trắng
        }
        break;
      }

      case 3: {
        // SCENE_MAGIC_FOREST (Rừng Đom Đóm Phát Quang Sinh Học):
        for (int y = 0; y < 275; y += 8) {
          uint8_t g = 16 + y * 32 / 275;
          spr->fillRect(0, y, SCREEN_WIDTH, 8, lgfx::color565(2, g, 14));
        }
        // Thảm rêu ở đáy (Y = 275 - 320)
        spr->fillRect(0, 275, SCREEN_WIDTH, 45, lgfx::color565(6, 36, 22));
        // Cây cổ thụ góc trái đáy
        spr->fillRect(0, 245, 14, 75, lgfx::color565(11, 26, 18));
        // Nấm phát quang sinh học ở đáy
        spr->fillCircle(38, 286, 6, 0x07FF);
        spr->fillRect(36, 286, 4, 7, TFT_WHITE);
        spr->fillCircle(130, 292, 5, 0xEC93);
        spr->fillRect(128, 292, 4, 5, TFT_WHITE);
        break;
      }

      case 4: {
        // SCENE_OCEAN_SUNSET (Biển Chiều Hoàng Hôn):
        for (int y = 0; y < 260; y += 8) {
          uint8_t r = 40 + y * 180 / 260;
          uint8_t g = 8 + y * 130 / 260;
          uint8_t b = 70 - y * 65 / 260;
          spr->fillRect(0, y, SCREEN_WIDTH, 8, lgfx::color565(r, g, b));
        }
        // Mặt trời lặn chạm đường chân trời đáy (Y = 255)
        spr->fillCircle(86, 255, 18, lgfx::color565(254, 240, 138));
        // Đại dương ở đáy (Y = 260 - 320)
        spr->fillRect(0, 260, SCREEN_WIDTH, 60, lgfx::color565(12, 18, 36));
        // Sóng phản chiếu ánh vàng
        for (int layer = 0; layer < 3; layer++) {
          int yBase = 270 + layer * 16;
          for (int x = 20; x < 152; x += 14) {
            int wy = yBase + (int)(sinf(timeAngle * 2.5f + x * 0.1f + layer) * 2.0f);
            spr->drawFastHLine(x, wy, 8, 0xFE40);
          }
        }
        break;
      }

      case 5: {
        // SCENE_EARTH_ORBIT (Quỹ Đạo Trái Đất 3D - CHUẨN GROUNDED BOTTOM Y >= 250):
        // 1. Bầu trời không gian sâu thẳm tĩnh lặng (Y = 0 - 250):
        for (int y = 0; y < 255; y += 8) {
          uint8_t b = 12 + y * 28 / 255;
          spr->fillRect(0, y, SCREEN_WIDTH, 8, lgfx::color565(1, 3, b));
        }
        // 2. Toàn bộ Địa Cầu Trái Đất 3D neo chặt dưới đáy (Tâm eCy = 385, Bán kính R = 125):
        // Vành khí quyển tán xạ Rayleigh xanh ngọc rực rỡ ở đường chân trời đáy
        spr->fillCircle(86, 385, 142, lgfx::color565(0, 50, 140));
        spr->fillCircle(86, 385, 134, lgfx::color565(0, 130, 240));
        spr->fillCircle(86, 385, 127, lgfx::color565(0, 230, 255)); // Vành ngọc lam phát quang
        spr->fillCircle(86, 385, 122, lgfx::color565(8, 32, 75));   // Đại dương sâu thẳm
        // Các mảng lục địa xanh rừng trôi dạt ở đáy
        int drift = (int)(timeAngle * 8.0f) % 160;
        spr->fillEllipse(86 - 35 + drift - 80, 288, 28, 12, lgfx::color565(25, 95, 45));
        spr->fillEllipse(86 + 30 + drift - 80, 302, 24, 10, lgfx::color565(30, 115, 55));
        // Vệt nắng bình minh lóe sáng ở góc chân trời
        spr->fillCircle(142, 260, 4, TFT_WHITE);
        spr->drawFastHLine(126, 260, 32, 0xFFE0);
        spr->drawFastVLine(142, 244, 32, 0xFFE0);
        break;
      }

      case 6: {
        // SCENE_AURORA_BOREALIS (Cực Quang Vùng Cực - GROUNDED BOTTOM Y >= 265):
        for (int y = 0; y < 265; y += 8) {
          uint8_t g = 3 + y * 18 / 265;
          spr->fillRect(0, y, SCREEN_WIDTH, 8, lgfx::color565(6, g, 22));
        }
        // Dải lụa cực quang uốn lượn mượt mà ở tầng trời xa
        for (int x = 0; x < SCREEN_WIDTH; x += 3) {
          int ay1 = 70 + (int)(sinf(timeAngle * 1.4f + (float)x * 0.035f) * 16.0f);
          spr->drawFastVLine(x, ay1, 18, lgfx::color565(0, 255, 140));
        }
        // Dãy núi tuyết nhấp nhô neo ở đáy (Y = 265 - 320)
        spr->fillTriangle(0, 320, 25, 262, 55, 320, lgfx::color565(14, 20, 36));
        spr->fillTriangle(45, 320, 86, 250, 125, 320, lgfx::color565(14, 20, 36));
        spr->fillTriangle(115, 320, 145, 256, 172, 320, lgfx::color565(14, 20, 36));
        spr->fillRect(0, 285, SCREEN_WIDTH, 35, lgfx::color565(10, 22, 34)); // Hồ băng đáy
        // Chóp tuyết trắng
        spr->fillTriangle(86, 250, 78, 262, 94, 262, 0xDEFF);
        spr->fillTriangle(25, 262, 19, 272, 31, 272, 0xDEFF);
        spr->fillTriangle(145, 256, 137, 266, 153, 266, 0xDEFF);
        break;
      }

      case 7: {
        // SCENE_MT_FUJI_SAKURA (Mùa Xuân Núi Phú Sĩ Ukiyo-e - GROUNDED BOTTOM Y >= 250):
        for (int y = 0; y < 250; y += 6) {
          uint8_t r = 20 + y * 215 / 250;
          uint8_t g = 9 + y * 125 / 250;
          uint8_t b = 40 - y * 36 / 250;
          spr->fillRect(0, y, SCREEN_WIDTH, 6, lgfx::color565(r, g, b));
        }
        // Vầng thái dương Asahi đỏ rực ở chân trời thấp (Y = 248)
        spr->fillCircle(86, 248, 24, lgfx::color565(230, 35, 45));
        // Nón núi tuyết Phú Sĩ neo chặt ở đáy (Y = 252 - 320)
        spr->fillTriangle(0, 320, 86, 252, 172, 320, lgfx::color565(34, 37, 63));
        spr->fillTriangle(86, 252, 66, 274, 106, 274, TFT_WHITE); // Chóp tuyết trắng
        break;
      }

      case 8: {
        // SCENE_TOKYO_NIGHT (Đêm Tokyo Mưa Cyber - GROUNDED BOTTOM Y >= 265):
        for (int y = 0; y < 265; y += 8) {
          spr->fillRect(0, y, SCREEN_WIDTH, 8, lgfx::color565(11, 12, 28));
        }
        // Chân trời cao ốc Tokyo neo ở đáy (Y = 265 - 320)
        const int bldgs[6][3] = {{0, 26, 50}, {24, 22, 45}, {44, 32, 55}, {74, 26, 48}, {98, 28, 52}, {124, 48, 46}};
        for (int b = 0; b < 6; b++) {
          int bx = bldgs[b][0], bw = bldgs[b][1], bh = bldgs[b][2];
          spr->fillRect(bx, 320 - bh, bw, bh, lgfx::color565(15, 18, 36));
          spr->drawPixel(bx + bw / 2, 320 - bh - 2, 0xF800); // Đèn đỏ
          for (int wy = 320 - bh + 6; wy < 312; wy += 8) {
            for (int wx = bx + 4; wx < bx + bw - 3; wx += 6) {
              if ((wx + wy) % 3 == 0) spr->drawPixel(wx, wy, 0xFE40); // Cửa sổ vàng
            }
          }
        }
        // Tháp Tokyo vươn nhẹ từ đáy
        spr->drawFastVLine(86, 255, 65, lgfx::color565(239, 68, 68));
        spr->drawLine(70, 320, 86, 265, lgfx::color565(239, 68, 68));
        spr->drawLine(102, 320, 86, 265, lgfx::color565(239, 68, 68));
        break;
      }
    }
  }

  void renderTopTypography(LGFX_Sprite* spr) {
    String fullText = (customQuote.length() > 0) ? customQuote : String(getThemeDefaultQuote(currentSpriteIdx));

    spr->setFont(&fonts::fontVietnamese);
    spr->setTextSize(1);
    spr->setTextDatum(textdatum_t::top_left);

    const int maxLineWidth = SCREEN_WIDTH - 16; // 156px (x=8 đến 164)
    const int maxLines = 4;
    const int lineHeight = 15;
    const int startY = 14;

    std::vector<String> lines;
    if (fullText.indexOf('\n') != -1) {
      int lineStart = 0;
      int tLen = fullText.length();
      for (int i = 0; i <= tLen; i++) {
        if (i == tLen || fullText[i] == '\n') {
          if (lines.size() < (size_t)maxLines) {
            String l = fullText.substring(lineStart, i);
            l.trim();
            lines.push_back(l);
          }
          lineStart = i + 1;
        }
      }
    } else {
      // Tách chuỗi thành các từ (Word-Wrap)
      std::vector<String> words;
      int strLen = fullText.length();
      int wordStart = 0;
      for (int i = 0; i <= strLen; i++) {
        if (i == strLen || fullText[i] == ' ') {
          if (i > wordStart) {
            words.push_back(fullText.substring(wordStart, i));
          }
          wordStart = i + 1;
        }
      }

      // Gom từ vào tối đa 4 dòng theo độ rộng pixel thực tế
      String curLine = "";
      for (size_t i = 0; i < words.size(); i++) {
        String testLine = (curLine.length() == 0) ? words[i] : (curLine + " " + words[i]);
        if (spr->textWidth(testLine.c_str()) <= maxLineWidth) {
          curLine = testLine;
        } else {
          if (curLine.length() > 0) lines.push_back(curLine);
          curLine = words[i];
          if (lines.size() >= (size_t)(maxLines - 1)) break;
        }
      }
      if (curLine.length() > 0 && lines.size() < (size_t)maxLines) {
        lines.push_back(curLine);
      }
    }

    // Đếm tổng số ký tự UTF-8 để tính toán chu kỳ Typewriter
    int totalChars = 0;
    for (size_t i = 0; i < lines.size(); i++) {
      int bIdx = 0, lBytes = lines[i].length();
      const char* raw = lines[i].c_str();
      while (bIdx < lBytes) {
        uint8_t c = (uint8_t)raw[bIdx];
        bIdx += ((c & 0xE0) == 0xC0) ? 2 : (((c & 0xF0) == 0xE0) ? 3 : (((c & 0xF8) == 0xF0) ? 4 : 1));
        totalChars++;
      }
    }

    // Tốc độ đánh máy: Chậm lại bằng 2/3 hiện tại (65ms/ký tự), dừng đọc 4000ms sau khi gõ xong
    uint32_t charDelay = 65;
    uint32_t holdTime = 4000;
    uint32_t cycle = (totalChars * charDelay) + holdTime;
    uint32_t progress = (cycle > 0) ? (millis() % cycle) : 0;
    int visibleCount = (progress < (uint32_t)(totalChars * charDelay)) ? (int)(progress / charDelay) : totalChars;

    // Vẽ từng dòng chữ (Căn giữa mỗi dòng cân đối)
    int charsDrawn = 0;
    for (size_t i = 0; i < lines.size(); i++) {
      if (charsDrawn >= visibleCount) break;

      int charsLeft = visibleCount - charsDrawn;
      int bIdx = 0, charCount = 0, lBytes = lines[i].length();
      const char* raw = lines[i].c_str();

      while (bIdx < lBytes && charCount < charsLeft) {
        uint8_t c = (uint8_t)raw[bIdx];
        bIdx += ((c & 0xE0) == 0xC0) ? 2 : (((c & 0xF0) == 0xE0) ? 3 : (((c & 0xF8) == 0xF0) ? 4 : 1));
        charCount++;
      }

      String lineToDraw = lines[i].substring(0, bIdx);
      charsDrawn += charCount;

      int lineY = startY + (int)i * lineHeight;
      int lw = spr->textWidth(lineToDraw.c_str());
      int lx = (SCREEN_WIDTH - lw) / 2;

      // Đổ bóng đen phía sau (Vẽ trong suốt, không đè hộp đen lên chân dòng trên)
      spr->setTextDatum(textdatum_t::top_left);
      spr->setTextColor(0x0000);
      spr->drawString(lineToDraw.c_str(), lx + 1, lineY + 1);

      // Chữ màu chính (Vẽ trong suốt)
      spr->setTextColor(currentTextColor);
      spr->drawString(lineToDraw.c_str(), lx, lineY);
    }
  }

  // MÀN HÌNH CẤU HÌNH WI-FI & THÔNG TIN HỆ THỐNG (Chỉ hiện khi giữ nút >= 2.5s)
  void renderQRScreen() {
    sprite.fillScreen(TFT_BLACK);
    sprite.setFont(&fonts::Font2);
    sprite.setTextDatum(textdatum_t::top_center);

    sprite.setTextColor(TFT_BLACK, TFT_BLACK);
    sprite.drawString("CAU HINH WI-FI", SCREEN_WIDTH / 2 + 1, 15);
    sprite.setTextColor(0xFFE0, TFT_BLACK);
    sprite.drawString("CAU HINH WI-FI", SCREEN_WIDTH / 2, 14);

    // Vẽ mã QR ở chính giữa màn hình (172x320)
    sprite.qrcode("WIFI:S:Love_Keychain;T:nopass;;", (SCREEN_WIDTH - 110) / 2, 48, 110, 3);

    sprite.setFont(&fonts::Font0);
    sprite.setTextColor(TFT_CYAN, TFT_BLACK);
    sprite.drawString("SSID: Love_Keychain", SCREEN_WIDTH / 2, 172);

    sprite.setTextColor(TFT_GREEN, TFT_BLACK);
    sprite.drawString("IP: 192.168.4.1", SCREEN_WIDTH / 2, 186);

    sprite.setTextColor(0xFD20, TFT_BLACK);
    sprite.drawString("app.signsafevn.online", SCREEN_WIDTH / 2, 202);

    sprite.drawFastHLine(16, 224, SCREEN_WIDTH - 32, 0x4A69);

    sprite.setTextColor(TFT_WHITE, TFT_BLACK);
    sprite.drawString("Trang thai:", SCREEN_WIDTH / 2, 234);

    if (isWifiConnected) {
      sprite.setTextColor(0x07E0, TFT_BLACK);
      sprite.drawString("Wi-Fi: ONLINE", SCREEN_WIDTH / 2, 248);
    } else {
      sprite.setTextColor(TFT_RED, TFT_BLACK);
      sprite.drawString("Wi-Fi: MAT KET NOI", SCREEN_WIDTH / 2, 248);
    }

    if (isCloudConnected) {
      sprite.setTextColor(0x07FF, TFT_BLACK);
      sprite.drawString("Cloud WS: HOAT DONG", SCREEN_WIDTH / 2, 262);
    } else {
      sprite.setTextColor(TFT_YELLOW, TFT_BLACK);
      sprite.drawString("Cloud WS: DANG KET NOI", SCREEN_WIDTH / 2, 262);
    }

    sprite.setTextColor(0x8410, TFT_BLACK);
    sprite.drawString("Nhan 1 lan de quay lai", SCREEN_WIDTH / 2, 290);

    sprite.pushSprite(0, 0);
  }

  void renderFrame() {
    checkDelayedSave();

    // Đo đạc FPS thực tế
    frameCount++;
    unsigned long now = millis();
    if (now - lastFpsTime >= 1000) {
      currentFps = frameCount;
      frameCount = 0;
      lastFpsTime = now;
    }

    if (isQRMode) {
      renderQRScreen();
      return;
    }

    // 1. Nền đen thuần AMOLED #000000
    sprite.fillScreen(TFT_BLACK);

    // 2. LAYER 0: Bối cảnh phong cảnh sống (5 Living Dioramas)
    renderLivingScenery(&sprite, floatAngle);

    // 3. LAYER 1: VÔ HIỆU HÓA HOÀN TOÀN HẠT BỤI RƠI THEO YÊU CẦU NGƯỜI DÙNG
    // Giữ màn hình trong suốt, tĩnh tại và siêu nét (Clear 100%), không gây rối mắt chữ và nhân vật.

    // 4. LAYER 2: Sân khấu chính trung tâm
    float centerY = (currentSpriteIdx == 12) ? (182.0f + sinf(floatAngle) * 4.0f) : (160.0f + sinf(floatAngle) * 6.0f);
    float breath = (sinf(breathAngle) + 1.0f) * 0.5f;

    int cx = SCREEN_WIDTH / 2; // 86
    int cy = (int)centerY;

    // Bóng tiếp xúc chỉ vẽ khi nhân vật đứng đất (không vẽ cho kiếm thánh hoặc mưa cyber)
    if (currentSpriteIdx != 12 && currentSceneryId != 2) {
      float hover = -sinf(floatAngle); // > 0 khi bay cao
      int rx = (int)(22.0f - hover * 5.0f);
      int ry = (int)(5.0f - hover * 1.5f);
      uint16_t shadowCol = (hover > 0.1f) ? 0x0841 : 0x18C3;
      sprite.fillEllipse(cx, 202, rx, ry, shadowCol);
    }

    // Vẽ Theme Animation 2.5D Volumetric Hero Scale
    SpriteRenderer::drawTheme(&sprite, currentSpriteIdx, cx, cy, breath, floatAngle);

    // 5. LAYER 3: CHỮ NỔI Ở ĐỈNH (Y = 8 - 28) CÓ DẤU 100%
    renderTopTypography(&sprite);

    // 6. Đẩy Framebuffer ra ST7789 qua DMA SPI 40MHz
    sprite.pushSprite(0, 0);

    floatAngle += 0.045f;
    breathAngle += 0.08f;
  }
};

extern DisplayEngine engine;
inline DisplayEngine& DisplayEngine::getInstance() {
  return engine;
}
