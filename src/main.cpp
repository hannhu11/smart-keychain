#include <Arduino.h>
#include <Preferences.h>
#include "config.h"
#include "display_engine.h"
#include "button_manager.h"
#include "web_portal.h"
#include "cloud_client.h"

DisplayEngine engine;
ButtonManager btnManager(BTN_PIN);
WebPortal portal;
CloudClient cloud;
TaskHandle_t NetworkTaskHandle = NULL;
Preferences wifiPrefs;

const char* KNOWN_SSIDS[] = {"Tuan Anh 2.4G", "Tuan Anh", "Tuan Anh 1", "Tuan Anh 2"};
const int NUM_KNOWN_SSIDS = 4;
int currentSsidIndex = 0;

String currentWifiSSID = "Tuan Anh 2.4G";
String currentWifiPass = "27011980";
bool needWifiReconnect = false;

void onSingleClick() {
  engine.nextSprite();
}

void onQREnter() {
  Serial.println("[NÚT BẤM] Giữ phím >= 2.5s -> Mở mã QR cấu hình!");
  engine.setQRMode(true);
}

void onHoldPalette() {
  Serial.println("[NÚT BẤM] Đổi Bảng Màu Kim Cương!");
  engine.cyclePalette();
}

void onQRExitClick() {
  Serial.println("[NÚT BẤM] Thoát mã QR -> Trở về Animation ngay lập tức!");
  engine.setQRMode(false);
}

// Task Mạng chạy độc lập trên Core 0 (Đảm bảo Core 1 không bao giờ bị nghẽn)
void TaskNetwork(void *pvParameters) {
  Serial.println("[FreeRTOS] Task Mạng Dual-Mode (SoftAP + Cloud WebSocket) khởi chạy trên Core 0");

  // 1. Kích hoạt chế độ Wi-Fi kép WIFI_AP_STA
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  WiFi.setSleep(false);
  
  // 2. Kết nối Wi-Fi gia đình Tuan Anh 2.4G / Tuan Anh / Tuan Anh 1 / Tuan Anh 2
  WiFi.disconnect();
  WiFi.begin(currentWifiSSID.c_str(), currentWifiPass.c_str());
  Serial.printf("[Wi-Fi STA] Đang kết nối tới Wi-Fi Internet: %s\n", currentWifiSSID.c_str());

  portal.start();
  bool cloudStarted = false;

  unsigned long lastBatCheck = 0;
  unsigned long lastWifiStatusCheck = 0;
  unsigned long staConnectStartTime = millis();

  for (;;) {
    portal.loop();

    if (WiFi.status() == WL_CONNECTED) {
      if (!cloudStarted) {
        cloud.begin();
        cloudStarted = true;
      }
      cloud.loop();
    }

    if (needWifiReconnect) {
      needWifiReconnect = false;
      staConnectStartTime = millis();
      cloudStarted = false;
      Serial.printf("[Wi-Fi STA] Tái kết nối với cấu hình mới: %s\n", currentWifiSSID.c_str());
      WiFi.disconnect();
      WiFi.begin(currentWifiSSID.c_str(), currentWifiPass.c_str());
    }
    
    engine.isWifiActive = portal.active();
    engine.isWifiConnected = (WiFi.status() == WL_CONNECTED);
    engine.isCloudConnected = cloud.connected();
    engine.wifiSecondsLeft = portal.getSecondsRemaining();

    // Định kỳ kiểm tra trạng thái kết nối Internet (3s/lần)
    if (millis() - lastWifiStatusCheck > 3000) {
      lastWifiStatusCheck = millis();
      if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("[Wi-Fi STA] ĐÃ KẾT NỐI INTERNET! SSID: %s | IP: %s | Cloud WebSocket: %s\n", 
          WiFi.SSID().c_str(), WiFi.localIP().toString().c_str(), cloud.connected() ? "ONLINE (CONNECTED)" : "CONNECTING...");
      } else {
        Serial.printf("[Wi-Fi STA] Đang đợi kết nối tới %s...\n", currentWifiSSID.c_str());
        // Nếu sau 14s không kết nối được -> Tự động chuyển qua SSID 2.4G tiếp theo trong danh sách
        if (millis() - staConnectStartTime > 14000) {
          staConnectStartTime = millis();
          currentSsidIndex = (currentSsidIndex + 1) % NUM_KNOWN_SSIDS;
          currentWifiSSID = KNOWN_SSIDS[currentSsidIndex];
          Serial.printf("[Wi-Fi STA Fallback] Đổi sang Wi-Fi: %s (Mật khẩu: %s)...\n", currentWifiSSID.c_str(), currentWifiPass.c_str());
          WiFi.disconnect();
          WiFi.begin(currentWifiSSID.c_str(), currentWifiPass.c_str());
        }
      }
    }

    if (millis() - lastBatCheck > 2000) {
      lastBatCheck = millis();
      int adc = analogRead(BAT_ADC_PIN);
      engine.updateBattery(adc);
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("\n==================================================");
  Serial.println("   SMART DIGITAL PIXEL KEYCHAIN - ESP32S (30P)");
  Serial.println("   Ultra-Minimalist AMOLED + Tuan Anh Auto-Cycle");
  Serial.println("==================================================");

  // 1. Nạp Wi-Fi Preferences
  wifiPrefs.begin("keychain_net", false);
  String savedSSID = wifiPrefs.getString("ssid", "");
  String savedPass = wifiPrefs.getString("pass", "");
  if (savedSSID.length() > 0) {
    currentWifiSSID = savedSSID;
    currentWifiPass = (savedPass.length() > 0) ? savedPass : "27011980";
    Serial.printf("[NVS] Nạp Wi-Fi từ Flash: %s\n", currentWifiSSID.c_str());
  } else {
    currentWifiSSID = "Tuan Anh 2.4G";
    currentWifiPass = "27011980";
  }

  // 2. Cấu hình Nút Bấm Hardware Interrupt (0ms Instant Click + >=2.5s QR)
  btnManager.init(onSingleClick, onQREnter, onQRExitClick, onHoldPalette);

  // 3. Khởi tạo Engine Màn hình ST7789 60 FPS
  engine.init();

  // 4. Thiết lập Callbacks cho Web Cloud Realtime
  cloud.setCallbacks(
    [](int spriteId) {
      engine.setSprite(spriteId);
      btnManager.setState(STATE_ANIMATION);
    },
    [](int paletteId) {
      engine.particles.setPalette(paletteId);
      btnManager.setState(STATE_ANIMATION);
    },
    [](String quote) {
      engine.setCustomQuote(quote);
      btnManager.setState(STATE_ANIMATION);
    },
    [](int brightness) {
      engine.setBrightness(brightness);
    },
    [](bool qrMode) {
      engine.setQRMode(qrMode);
      btnManager.setState(qrMode ? STATE_QR_CONFIG : STATE_ANIMATION);
    }
  );

  // 5. Khởi tạo WebPortal Callbacks
  portal.setCallbacks(
    [](int spriteId) {
      engine.setSprite(spriteId);
      btnManager.setState(STATE_ANIMATION);
    },
    [](int paletteId) {
      engine.particles.setPalette(paletteId);
      btnManager.setState(STATE_ANIMATION);
    },
    [](String quote) {
      engine.setCustomQuote(quote);
      btnManager.setState(STATE_ANIMATION);
    },
    [](int brightness) {
      engine.setBrightness(brightness);
    },
    [](String ssid, String pass) {
      currentWifiSSID = ssid;
      currentWifiPass = pass;
      wifiPrefs.putString("ssid", ssid);
      wifiPrefs.putString("pass", pass);
      needWifiReconnect = true;
    }
  );

  // 6. Chạy Task Mạng trên Core 0
  xTaskCreatePinnedToCore(
    TaskNetwork,
    "NetworkTask",
    8192,
    NULL,
    1,
    &NetworkTaskHandle,
    0
  );

  Serial.println("[HỆ THỐNG] Khởi tạo hoàn tất, bắt đầu Render 60 FPS trên Core 1!");
}

void loop() {
  // 1. Kiểm tra lệnh Serial (#DUMP_SCREEN, #SET_SPRITE, #NEXT_THEME)
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "#DUMP_SCREEN") {
      engine.dumpFramebuffer();
    } else if (cmd.startsWith("#SET_SPRITE ")) {
      int sid = cmd.substring(12).toInt();
      engine.setSprite(sid);
      btnManager.setState(STATE_ANIMATION);
      Serial.printf("[SERIAL] Chuyển sang Theme ID: %d\n", sid + 1);
    } else if (cmd == "#NEXT_THEME") {
      engine.nextSprite();
      btnManager.setState(STATE_ANIMATION);
      Serial.printf("[SERIAL] Next Theme -> ID: %d\n", engine.currentSpriteIdx + 1);
    } else if (cmd.startsWith("#SET_SCALE ")) {
      float sc = cmd.substring(11).toFloat();
      engine.setSpriteScale(sc);
    } else if (cmd.startsWith("#SET_TEXT_SIZE ")) {
      uint8_t sz = cmd.substring(15).toInt();
      engine.setTextSize(sz);
    } else if (cmd.startsWith("#SET_QR ")) {
      bool qr = (cmd.substring(8).toInt() != 0);
      engine.setQRMode(qr);
      btnManager.setState(qr ? STATE_QR_CONFIG : STATE_ANIMATION);
    } else if (cmd.startsWith("#SET_BRIGHTNESS ")) {
      int br = cmd.substring(16).toInt();
      engine.setBrightness(br);
    } else if (cmd.startsWith("#SET_FREEZE ")) {
      bool frz = (cmd.substring(12).toInt() != 0);
      engine.setFreezeText(frz);
    } else if (cmd.startsWith("#SET_SPEED ")) {
      uint32_t spd = cmd.substring(11).toInt();
      engine.setTypewriterSpeed(spd);
    } else if (cmd.startsWith("#SET_HOLD ")) {
      uint32_t ht = cmd.substring(10).toInt();
      engine.setHoldTime(ht);
    } else if (cmd == "#TEST_PIN") {
      for (int i = 0; i < 5; i++) {
        Serial.printf("[PIN_LOG] GPIO33=%d | GPIO0=%d | GPIO32=%d | GPIO35=%d\n",
          digitalRead(33), digitalRead(0), digitalRead(32), digitalRead(35));
        delay(100);
      }
    }
  }

  // 2. Hardware Interrupt Button Tick (<10ms phản hồi)
  btnManager.tick();

  // 3. Render đồ họa 60 FPS
  engine.renderFrame();

  // 4. Telemetry Heartbeat (chu kỳ 2 giây/lần)
  static unsigned long lastTelemetry = 0;
  if (millis() - lastTelemetry >= 2000) {
    lastTelemetry = millis();
    Serial.printf("[TELEMETRY] FPS: %d | Free Heap: %d KB | Min Heap: %d KB | WiFi: %s | IP: %s | WS: %s\n",
      engine.getFPS(),
      ESP.getFreeHeap() / 1024,
      ESP.getMinFreeHeap() / 1024,
      (WiFi.status() == WL_CONNECTED) ? WiFi.SSID().c_str() : "DISCONNECTED",
      (WiFi.status() == WL_CONNECTED) ? WiFi.localIP().toString().c_str() : "0.0.0.0",
      cloud.connected() ? "ONLINE" : "OFFLINE"
    );
  }

  delay(1);
}
