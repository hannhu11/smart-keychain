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
        // Bầu trời đêm dải Ngân Hà sâu thẳm
        for (int y = 0; y < 260; y += 6) {
          uint8_t r = 3 + y * 18 / 260;
          uint8_t g = 5 + y * 10 / 260;
          uint8_t b = 20 + y * 14 / 260;
          spr->fillRect(0, y, SCREEN_WIDTH, 6, lgfx::color565(r, g, b));
        }
        // Trường sao lấp lánh
        for (int i = 0; i < 35; i++) {
          int sx = (i * 31 + 7) % SCREEN_WIDTH;
          int sy = (i * 19 + 5) % 220;
          float alpha = 0.5f + 0.5f * sinf(timeAngle * 2.0f + i * 1.5f);
          if (alpha > 0.35f) {
            spr->drawPixel(sx, sy, (i % 3 == 0) ? 0xFFE0 : TFT_WHITE);
          }
        }
        // Rừng thông bạt ngàn ở chân trời
        for (int tr = 0; tr < 8; tr++) {
          int tx = tr * 24 - 8;
          spr->fillTriangle(tx, 260, tx + 16, 215, tx + 32, 260, lgfx::color565(10, 16, 29));
        }
        // Mặt đất đồi cỏ đêm
        spr->fillRect(0, 260, SCREEN_WIDTH, 60, lgfx::color565(15, 23, 16));
        // Vầng sáng ấm của đống lửa trại
        spr->fillCircle(86, 265, 45, lgfx::color565(60, 30, 0));
        spr->fillCircle(86, 265, 30, lgfx::color565(100, 50, 0));
        // Khúc gỗ sồi
        spr->fillRect(72, 266, 28, 6, lgfx::color565(62, 39, 35));
        // Lửa trại 3 tầng khí động học
        int fFlap = (int)(sinf(timeAngle * 8.0f) * 3.0f);
        spr->fillTriangle(76, 266, 86 + fFlap, 238, 96, 266, 0xF800); // Đỏ ngoài
        spr->fillTriangle(79, 266, 86 + fFlap / 2, 244, 93, 266, 0xFE40); // Vàng giữa
        spr->fillTriangle(82, 266, 86, 252, 90, 266, TFT_WHITE); // Tâm trắng
        // Đốm lửa tàn tro bay
        for (int s = 0; s < 8; s++) {
          int spkY = 250 - (int)((millis() / 15 + s * 30) % 120);
          int spkX = 86 + (int)(sinf(timeAngle * 3.0f + s) * 14.0f);
          spr->drawPixel(spkX, spkY, (s % 2 == 0) ? 0xFE40 : 0xF9A0);
        }
        break;
      }

      case 1: {
        // SCENE_SAKURA_SHRINE (Đền Thần Anh Đào Hoàng Hôn):
        for (int y = 0; y < 260; y += 6) {
          uint8_t r = 26 + y * 140 / 260;
          uint8_t g = 13 + y * 50 / 260;
          uint8_t b = 51 - y * 10 / 260;
          spr->fillRect(0, y, SCREEN_WIDTH, 6, lgfx::color565(r, g, b));
        }
        // Trăng khuyết đầu tháng
        spr->fillCircle(140, 50, 10, lgfx::color565(255, 251, 232));
        spr->fillCircle(137, 48, 9, lgfx::color565(26, 13, 51));
        // Cổng Torii thần đạo
        spr->fillRect(125, 255, 6, 65, lgfx::color565(185, 28, 28));
        spr->fillRect(155, 255, 6, 65, lgfx::color565(185, 28, 28));
        spr->fillRect(118, 256, 49, 5, 0x0000); // Mái xà đen
        spr->fillRect(122, 263, 42, 4, lgfx::color565(239, 68, 68)); // Xà đỏ
        // Cánh hoa anh đào rơi
        for (int i = 0; i < 12; i++) {
          int px = (int)(sinf(timeAngle * 0.8f + i * 1.3f) * 35.0f + 20.0f * i + 172.0f) % SCREEN_WIDTH;
          int py = (int)(timeAngle * 26.0f + i * 40) % SCREEN_HEIGHT;
          spr->fillCircle(px, py, 2, lgfx::color565(255, 117, 151));
        }
        break;
      }

      case 2: {
        // SCENE_CYBER_RAIN (Mưa Neon Cyberpunk Siêu Mượt 1:1 Phần Cứng):
        for (int i = 0; i < 36; i++) {
          int rx = (i * 17 + 5) % SCREEN_WIDTH;
          int speed = 260 + (i % 6) * 40;
          int ry = (int)((millis() * speed / 1000 + i * 31) % (SCREEN_HEIGHT + 24)) - 12;
          int len = 7 + (i % 4) * 4;
          uint16_t rainColor = (i % 3 == 0) ? 0x07FF : ((i % 2 == 0) ? 0x05DF : 0x035B);
          spr->drawFastVLine(rx, ry, len, rainColor);
          spr->drawPixel(rx, ry + len - 1, TFT_WHITE);
        }
        break;
      }

      case 3: {
        // SCENE_MAGIC_FOREST (Rừng Đom Đóm Phát Quang Sinh Học):
        for (int y = 0; y < 270; y += 6) {
          uint8_t g = 18 + y * 38 / 270;
          spr->fillRect(0, y, SCREEN_WIDTH, 6, lgfx::color565(2, g, 14));
        }
        spr->fillRect(0, 270, SCREEN_WIDTH, 50, lgfx::color565(6, 41, 26)); // Đất rêu
        // Thân cây cổ thụ
        spr->fillRect(0, 180, 20, 140, lgfx::color565(11, 29, 20));
        spr->fillRect(0, 200, 35, 16, lgfx::color565(11, 29, 20));
        // Nấm phát quang
        spr->fillCircle(38, 285, 7, 0x07FF);
        spr->fillRect(36, 285, 4, 8, TFT_WHITE);
        spr->fillCircle(130, 290, 6, 0xEC93);
        spr->fillRect(128, 290, 4, 6, TFT_WHITE);
        // Đom đóm bay lượn
        for (int i = 0; i < 10; i++) {
          int fx = (int)(cosf(timeAngle * 0.7f + i * 1.4f) * 55.0f + 86.0f);
          int fy = (int)(sinf(timeAngle * 0.5f + i * 1.8f) * 50.0f + 170.0f);
          float glow = (sinf(timeAngle * 3.0f + i * 2.0f) + 1.0f) * 0.5f;
          if (glow > 0.25f) {
            spr->fillCircle(fx, fy, 2, (i % 2 == 0) ? 0xFDE0 : 0x07FF);
          }
        }
        break;
      }

      case 4: {
        // SCENE_OCEAN_SUNSET (Biển Chiều Hoàng Hôn):
        for (int y = 0; y < 235; y += 6) {
          uint8_t r = 46 + y * 199 / 235;
          uint8_t g = 8 + y * 145 / 235;
          uint8_t b = 84 - y * 73 / 235;
          spr->fillRect(0, y, SCREEN_WIDTH, 6, lgfx::color565(r, g, b));
        }
        // Mặt trời lặn
        spr->fillCircle(86, 230, 22, lgfx::color565(254, 240, 138));
        // Đại dương
        spr->fillRect(0, 235, SCREEN_WIDTH, 85, lgfx::color565(15, 23, 42));
        // Sóng phản chiếu
        for (int layer = 0; layer < 4; layer++) {
          int yBase = 245 + layer * 18;
          for (int x = 20; x < 152; x += 12) {
            int wy = yBase + (int)(sinf(timeAngle * 2.5f + x * 0.1f + layer) * 2.5f);
            spr->drawFastHLine(x, wy, 8, 0xFE40);
          }
        }
        break;
      }

      case 5: {
        // SCENE_EARTH_ORBIT (Quỹ Đạo Trái Đất 3D Siêu Chân Thực):
        // Không gian sâu thẳm
        for (int y = 0; y < 240; y += 6) {
          uint8_t b = 13 + y * 34 / 240;
          spr->fillRect(0, y, SCREEN_WIDTH, 6, lgfx::color565(1, 3, b));
        }
        // Trường sao Parallax
        for (int i = 0; i < 35; i++) {
          int sx = (i * 37 + 11) % SCREEN_WIDTH;
          int sy = (i * 23 + 7) % 220;
          float alpha = 0.5f + 0.5f * sinf(timeAngle * 2.0f + i * 1.7f);
          if (alpha > 0.4f) {
            spr->drawPixel(sx, sy, (i % 3 == 0) ? 0xFFE0 : TFT_WHITE);
          }
        }
        // Đĩa Trái Đất 3D với vành khí quyển Rayleigh
        spr->fillCircle(86, 345, 155, lgfx::color565(0, 40, 120));
        spr->fillCircle(86, 345, 148, lgfx::color565(0, 100, 220));
        spr->fillCircle(86, 345, 140, lgfx::color565(0, 220, 255)); // Vành ngọc lam
        spr->fillCircle(86, 345, 135, lgfx::color565(7, 28, 65));  // Đại dương xanh thẳm
        // Lục địa trôi
        int drift = (int)(timeAngle * 10.0f) % 180;
        spr->fillEllipse(86 - 40 + drift - 90, 300, 32, 18, lgfx::color565(25, 95, 45));
        spr->fillEllipse(86 + 30 + drift - 90, 315, 26, 15, lgfx::color565(30, 115, 55));
        // Mây tầng
        spr->drawEllipse(86 - 20, 290, 52, 9, lgfx::color565(200, 225, 255));
        spr->drawEllipse(86 + 35, 310, 44, 11, lgfx::color565(200, 225, 255));
        // Sunburst lóe sáng bình minh
        spr->fillCircle(138, 222, 5, TFT_WHITE);
        spr->drawFastHLine(118, 222, 40, 0xFFE0);
        spr->drawFastVLine(138, 202, 40, 0xFFE0);
        break;
      }

      case 6: {
        // SCENE_AURORA_BOREALIS (Cực Quang Trái Đất Tuyệt Đỉnh):
        for (int y = 0; y < 240; y += 6) {
          uint8_t g = 3 + y * 20 / 240;
          spr->fillRect(0, y, SCREEN_WIDTH, 6, lgfx::color565(6, g, 23));
        }
        // Sao vùng cực
        for (int i = 0; i < 25; i++) {
          spr->drawPixel((i * 29 + 5) % SCREEN_WIDTH, (i * 19 + 3) % 180, TFT_WHITE);
        }
        // Dải lụa cực quang uốn lượn đa tần
        for (int x = 0; x < SCREEN_WIDTH; x += 2) {
          int ay1 = 70 + (int)(sinf(timeAngle * 1.5f + (float)x * 0.035f) * 20.0f);
          int ay2 = 95 + (int)(sinf(timeAngle * 1.2f + (float)x * 0.045f + 1.2f) * 18.0f);
          spr->drawFastVLine(x, ay1, 24, lgfx::color565(0, 255, 140));
          spr->drawFastVLine(x, ay2, 20, lgfx::color565(180, 80, 255));
        }
        // Rặng núi tuyết
        spr->fillTriangle(0, 320, 25, 242, 60, 320, lgfx::color565(14, 20, 36));
        spr->fillTriangle(45, 320, 80, 232, 120, 320, lgfx::color565(14, 20, 36));
        spr->fillTriangle(105, 320, 138, 236, 172, 320, lgfx::color565(14, 20, 36));
        spr->fillRect(0, 275, SCREEN_WIDTH, 45, lgfx::color565(10, 22, 34)); // Hồ băng
        // Đỉnh tuyết
        spr->fillTriangle(25, 242, 18, 252, 32, 252, 0xDEFF);
        spr->fillTriangle(80, 232, 70, 246, 92, 246, 0xDEFF);
        spr->fillTriangle(138, 236, 128, 248, 148, 248, 0xDEFF);
        // Phản chiếu trên hồ
        for (int r = 0; r < 5; r++) {
          spr->drawFastHLine(35 + r * 6, 285 + r * 6, 50, lgfx::color565(0, 180, 100));
        }
        break;
      }

      case 7: {
        // SCENE_MT_FUJI_SAKURA (Mùa Xuân Núi Phú Sĩ Ukiyo-e):
        for (int y = 0; y < 220; y += 4) {
          uint8_t r = 21 + y * 220 / 220;
          uint8_t g = 9 + y * 130 / 220;
          uint8_t b = 42 - y * 38 / 220;
          spr->fillRect(0, y, SCREEN_WIDTH, 4, lgfx::color565(r, g, b));
        }
        // Vầng thái dương đỏ
        spr->fillCircle(86, 185, 32, lgfx::color565(230, 35, 45));
        // Nón núi tuyết Phú Sĩ
        spr->fillTriangle(0, 320, 86, 192, 172, 320, lgfx::color565(34, 37, 63));
        spr->fillTriangle(86, 192, 60, 225, 112, 225, TFT_WHITE);
        // Sương sớm
        int mx = (int)(timeAngle * 15.0f) % 200 - 30;
        spr->drawFastHLine(mx, 255, 80, lgfx::color565(250, 230, 235));
        spr->drawFastHLine(mx - 40, 275, 70, lgfx::color565(250, 230, 235));
        // Cánh hoa anh đào rơi
        for (int p = 0; p < 12; p++) {
          int px = (int)(sinf(timeAngle + p) * 25.0f + p * 16) % SCREEN_WIDTH;
          int py = (int)(millis() * 0.025f + p * 32) % SCREEN_HEIGHT;
          spr->fillCircle(px, py, 2, lgfx::color565(255, 117, 151));
        }
        break;
      }

      case 8: {
        // SCENE_TOKYO_NIGHT (Đêm Tokyo Mưa Cyber):
        for (int y = 0; y < 320; y += 8) {
          spr->fillRect(0, y, SCREEN_WIDTH, 8, lgfx::color565(11 + y * 10 / 320, 12, 27 + y * 12 / 320));
        }
        // Cao ốc
        const int bldgs[8][3] = {{0, 24, 90}, {22, 18, 120}, {38, 28, 75}, {64, 20, 135}, {82, 25, 105}, {105, 22, 80}, {125, 30, 125}, {153, 22, 95}};
        for (int b = 0; b < 8; b++) {
          int bx = bldgs[b][0], bw = bldgs[b][1], bh = bldgs[b][2];
          spr->fillRect(bx, 320 - bh, bw, bh, lgfx::color565(15, 18, 36));
          spr->drawPixel(bx + bw / 2, 320 - bh - 2, 0xF800); // Đèn hải đăng
          for (int wy = 320 - bh + 10; wy < 300; wy += 8) {
            for (int wx = bx + 4; wx < bx + bw - 3; wx += 6) {
              if ((wx * 7 + wy * 13) % 5 > 1) {
                uint16_t wcol = ((wx + wy) % 4 == 0) ? 0xFE40 : ((wx % 3 == 0) ? 0x07FF : TFT_WHITE);
                spr->drawPixel(wx, wy, wcol);
              }
            }
          }
        }
        // Tháp Tokyo
        spr->drawFastVLine(86, 170, 150, lgfx::color565(239, 68, 68));
        spr->drawLine(64, 320, 86, 185, lgfx::color565(239, 68, 68));
        spr->drawLine(108, 320, 86, 185, lgfx::color565(239, 68, 68));
        spr->fillRect(76, 245, 20, 5, TFT_WHITE);
        spr->fillRect(78, 246, 16, 3, lgfx::color565(239, 68, 68));
        // Mưa cyber
        for (int i = 0; i < 22; i++) {
          int rx = (i * 17 + 5) % SCREEN_WIDTH;
          int ry = (int)((millis() * 320 / 1000 + i * 29) % (SCREEN_HEIGHT + 20)) - 10;
          spr->drawFastVLine(rx, ry, 9, (i % 2 == 0) ? 0x07FF : 0xF81F);
        }
        break;
      }
    }
  }

  // 2. CHỮ TYPEWRITER ĐA HÀNG (MULTI-LINE WORD-WRAP TYPEWRITER ENGINE - CHUẨN 1:1 ẢNH THẬT)
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

    // 3. LAYER 1: Hiệu ứng hạt bụi sao kim cương Bling Bling (Chỉ chạy ở cảnh không có mưa)
    if (currentSceneryId != 2) {
      particles.updateAndRender(&sprite);
    }

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
