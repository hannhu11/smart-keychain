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
    currentSceneryId = sc % 5;
    needSavePrefs = true;
    savePrefsTimer = millis() + 3000;
  }

  void setQRMode(bool qr) {
    isQRMode = qr;
    qrScreenRendered = false;
  }

  void toggleQRMode() {
    isQRMode = !isQRMode;
    qrScreenRendered = false;
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

  // 1. LAYER 0: HỆ THỐNG 5 LIVING DIORAMAS ĐA TẦNG (0 VẬT THỂ LẠ, 0 RADAR)
  void renderLivingScenery(LGFX_Sprite* spr, float timeAngle) {
    switch (currentSceneryId) {
      case 0: {
        // SCENE_COZY_BEDROOM (Phòng ngủ ấm áp):


        // Hạt bụi nắng ấm & làn khói trà thơm bay lượn từ dưới lên
        for (int i = 0; i < 6; i++) {
          int px = 20 + i * 24 + (int)(sin(timeAngle * 0.5f + i) * 6.0f);
          int py = 300 - (int)((millis() / 30 + i * 40) % 240);
          spr->drawPixel(px, py, 0xFDE0);
          if (i % 2 == 0) spr->drawPixel(px + 1, py, 0xFCA0);
        }
        break;
      }

      case 1: {
        // SCENE_SAKURA_DUSK (Hoàng hôn Anh Đào):
        // Bầu trời chuyển sắc hoàng hôn tím huyền ảo
        spr->fillRect(0, 260, SCREEN_WIDTH, 60, 0x2004);
        spr->fillRect(0, 285, SCREEN_WIDTH, 35, 0x1803);

        // Rặng núi xa mờ ở chân trời đáy
        spr->fillTriangle(0, 320, 50, 275, 110, 320, 0x2945);
        spr->fillTriangle(70, 320, 130, 265, 172, 320, 0x18C3);

        // Cổng Torii cổ kính ở góc phải đáy
        spr->fillRect(135, 275, 4, 35, 0xB000);
        spr->fillRect(155, 275, 4, 35, 0xB000);
        spr->fillRect(130, 278, 34, 4, 0xF800);
        spr->fillRect(132, 272, 30, 3, 0xD000);

        // Cánh hoa anh đào rơi chao đảo đa vận tốc theo gió hình sin
        for (int i = 0; i < 8; i++) {
          int px = (int)(sin(timeAngle * 0.7f + i * 1.3f) * 35.0f + 22.0f * i) % SCREEN_WIDTH;
          int py = (int)(timeAngle * 26.0f + i * 45) % SCREEN_HEIGHT;
          spr->drawPixel(px, py, 0xFD14);
          spr->drawPixel(px + 1, py, 0xFF96);
        }
        break;
      }

      case 2: {
        // SCENE_CYBER_RAIN (Mưa Neon Cyberpunk Siêu Mượt - Chuẩn 1:1 Ảnh Móc Khóa Thật):
        // Mưa số rơi thẳng đứng xuyên suốt toàn màn hình (Y = 0 -> 320), không có thanh chân trời chắn đáy
        for (int i = 0; i < 36; i++) {
          int rx = (i * 17 + 5) % SCREEN_WIDTH;
          int speed = 260 + (i % 6) * 40; // 260 - 460 px/s
          int ry = (int)((millis() * speed / 1000 + i * 31) % (SCREEN_HEIGHT + 24)) - 12;
          int len = 7 + (i % 4) * 4; // 7 - 19px
          
          uint16_t rainColor = (i % 3 == 0) ? 0x07FF : ((i % 2 == 0) ? 0x05DF : 0x035B);
          spr->drawFastVLine(rx, ry, len, rainColor);
          spr->drawPixel(rx, ry + len - 1, TFT_WHITE); // Giọt đầu mưa sáng trắng rực rỡ
        }
        break;
      }

      case 3: {
        // SCENE_MAGIC_FOREST (Rừng đom đóm cổ tích):
        // Nền rừng tĩnh mịch ở đáy
        spr->fillRect(0, 275, SCREEN_WIDTH, 45, 0x01A0);
        spr->fillRect(0, 295, SCREEN_WIDTH, 25, 0x0120);

        // Thân cây cổ thụ uốn lượn ở góc trái
        spr->fillRect(0, 230, 16, 90, 0x3180);
        spr->fillRect(16, 245, 12, 12, 0x4200);

        // Nấm phát quang sinh học xanh ngọc
        spr->fillCircle(38, 298, 5, 0x07FF);
        spr->drawFastVLine(38, 298, 7, TFT_WHITE);
        spr->fillCircle(128, 304, 4, 0x07E0);
        spr->drawFastVLine(128, 304, 6, TFT_WHITE);

        // Bầy đom đóm lập lòe phát sáng nhịp nhàng với chu kỳ độc lập
        for (int i = 0; i < 7; i++) {
          int fx = (int)(cos(timeAngle * 0.7f + i * 1.4f) * 45.0f + 86.0f);
          int fy = (int)(sin(timeAngle * 0.5f + i * 1.8f) * 40.0f + 160.0f);
          float glow = (sin(timeAngle * 3.0f + i * 2.0f) + 1.0f) * 0.5f;
          if (glow > 0.3f) {
            spr->drawPixel(fx, fy, (i % 2 == 0) ? 0xFFE0 : 0x07FF);
          }
        }
        break;
      }

      case 4: {
        // SCENE_OCEAN_SUNSET (Biển chiều hoàng hôn):
        // Bầu trời chuyển sắc cam đỏ
        spr->fillRect(0, 240, SCREEN_WIDTH, 80, 0x8140);
        spr->fillRect(0, 260, SCREEN_WIDTH, 60, 0x40A0);

        // Mặt trời cam đỏ lặn dần xuống mép chân trời biển (Y = 245)
        spr->fillCircle(86, 245, 20, 0xFA40);
        spr->drawFastHLine(0, 245, SCREEN_WIDTH, 0xFD20);

        // 3 tầng sóng biển dập dềnh phản chiếu ánh hoàng hôn
        for (int layer = 0; layer < 3; layer++) {
          int yBase = 255 + layer * 18;
          uint16_t waveCol = (layer == 0) ? 0x0210 : ((layer == 1) ? 0x018C : 0x00E8);
          spr->fillRect(0, yBase, SCREEN_WIDTH, 20, waveCol);
          for (int x = 0; x < SCREEN_WIDTH; x += 8) {
            int wy = yBase + (int)(sin(timeAngle * 2.0f + x * 0.08f + layer) * 3.0f);
            spr->drawFastHLine(x, wy, 5, 0xFDE0);
          }
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

    const int maxLineWidth = SCREEN_WIDTH - 16; // 156px (x=8 đến 164)
    const int maxLines = 4;
    const int lineHeight = 13;
    const int startY = 16;

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

    // Tốc độ đánh máy: 40ms/ký tự, dừng 3500ms sau khi gõ xong
    uint32_t charDelay = 40;
    uint32_t holdTime = 3500;
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

      // Đổ bóng đen phía sau
      spr->setTextColor(TFT_BLACK, TFT_BLACK);
      spr->drawString(lineToDraw.c_str(), lx + 1, lineY + 1);

      // Chữ màu chính (Trắng/Vàng kim/Cyan)
      spr->setTextColor(currentTextColor, TFT_BLACK);
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
