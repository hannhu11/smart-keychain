#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include "config.h"

class CloudClient {
private:
  WebSocketsClient webSocket;
  WiFiClientSecure secClient;
  bool isConnected = false;
  unsigned long lastPollTime = 0;
  unsigned long lastPingTime = 0;
  
  int lastKnownSprite = -1;
  int lastKnownPalette = -1;
  int lastKnownBrightness = -1;
  String lastKnownQuote = "";
  bool lastKnownQR = false;

  std::function<void(int)> onSpriteChange;
  std::function<void(int)> onPaletteChange;
  std::function<void(String)> onQuoteChange;
  std::function<void(int)> onBrightnessChange;
  std::function<void(bool)> onQRChange;

  const char* BROWSER_UA = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36";

public:
  void setCallbacks(
    std::function<void(int)> fnSprite,
    std::function<void(int)> fnPalette,
    std::function<void(String)> fnQuote,
    std::function<void(int)> fnBrightness,
    std::function<void(bool)> fnQR = nullptr
  ) {
    onSpriteChange = fnSprite;
    onPaletteChange = fnPalette;
    onQuoteChange = fnQuote;
    onBrightnessChange = fnBrightness;
    onQRChange = fnQR;
  }

  void begin() {
    Serial.printf("[CLOUD] Khởi tạo kết nối IoT WebSocket tới ws://%s:80/ws/keychain?client=esp32 (Kênh Kép 0ms TLS)...\n", CLOUD_IP_BACKUP);
    
    // Kết nối trực tiếp Port 80 tới IP VPS (Không tốn 45KB RAM cho TLS, không bị Cloudflare WAF chặn)
    webSocket.begin(CLOUD_IP_BACKUP, 80, "/ws/keychain?client=esp32", "");

    webSocket.onEvent([this](WStype_t type, uint8_t * payload, size_t length) {
      switch (type) {
        case WStype_DISCONNECTED:
          if (isConnected) {
            Serial.println("[CLOUD WS] Mất kết nối WS, đang tự động tái kết nối...");
          }
          isConnected = false;
          break;

        case WStype_CONNECTED:
          isConnected = true;
          Serial.println("\n**************************************************");
          Serial.println("   >>> ĐÃ KẾT NỐI WEBSOCKET CLOUD REALTIME <15MS! <<<");
          Serial.println("**************************************************\n");
          {
            String reg = "{\"action\":\"REGISTER_DEVICE\",\"device\":\"ESP32S\",\"ip\":\"" + WiFi.localIP().toString() + "\"}";
            webSocket.sendTXT(reg);
          }
          break;

        case WStype_TEXT: {
          DynamicJsonDocument doc(1024);
          DeserializationError error = deserializeJson(doc, payload, length);
          if (!error) {
            JsonObject data = doc.containsKey("data") ? doc["data"] : doc.as<JsonObject>();
            applyData(data);
          }
          break;
        }

        case WStype_ERROR:
          Serial.printf("[CLOUD WS] Lỗi WS Handshake: %s\n", (payload != NULL && length > 0) ? (char*)payload : "TCP Error");
          break;

        case WStype_PONG:
          break;

        default:
          break;
      }
    });

    webSocket.setReconnectInterval(2000);
    webSocket.enableHeartbeat(15000, 4000, 2); // Ping mỗi 15s để giữ đường truyền WS trường tồn
  }

  void applyData(JsonObject& data) {
    if (data.containsKey("sprite_id")) {
      int sid = data["sprite_id"];
      if (sid != lastKnownSprite) {
        lastKnownSprite = sid;
        Serial.printf("[CLOUD REALTIME] >>> ĐỔI THEME TỪ WEB: ID %d <<<\n", sid + 1);
        if (onSpriteChange) onSpriteChange(sid);
      }
    }
    if (data.containsKey("palette_id")) {
      int pid = data["palette_id"];
      if (pid != lastKnownPalette) {
        lastKnownPalette = pid;
        Serial.printf("[CLOUD REALTIME] >>> ĐỔI BẢNG MÀU: ID %d <<<\n", pid);
        if (onPaletteChange) onPaletteChange(pid);
      }
    }
    if (data.containsKey("quote")) {
      String q = data["quote"].as<String>();
      if (q != lastKnownQuote) {
        lastKnownQuote = q;
        Serial.printf("[CLOUD REALTIME] >>> CẬP NHẬT LỜI NHẮN: %s <<<\n", q.c_str());
        if (onQuoteChange) onQuoteChange(q);
      }
    }
    if (data.containsKey("brightness")) {
      int br = data["brightness"];
      if (br != lastKnownBrightness) {
        lastKnownBrightness = br;
        Serial.printf("[CLOUD REALTIME] >>> ĐỔI ĐỘ SÁNG: %d <<<\n", br);
        if (onBrightnessChange) onBrightnessChange(br);
      }
    }
    if (data.containsKey("qr_mode")) {
      bool qr = data["qr_mode"];
      if (qr != lastKnownQR) {
        lastKnownQR = qr;
        Serial.printf("[CLOUD REALTIME] >>> ĐIỀU KHIỂN QR TỪ WEB: %s <<<\n", qr ? "BẬT" : "TẮT");
        if (onQRChange) onQRChange(qr);
      }
    }
    if (data.containsKey("text_color")) {
      String colHex = data["text_color"].as<String>();
      Serial.printf("[CLOUD REALTIME] >>> ĐỔI MÀU CHỮ: %s <<<\n", colHex.c_str());
      DisplayEngine::getInstance().setTextColor(parseHexColor565(colHex));
    }
    if (data.containsKey("text_size")) {
      uint8_t sz = data["text_size"].as<uint8_t>();
      Serial.printf("[CLOUD REALTIME] >>> ĐỔI CỠ CHỮ: %d <<<\n", sz);
      DisplayEngine::getInstance().setTextSize(sz);
    }
    if (data.containsKey("scenery_id")) {
      uint8_t sc = data["scenery_id"].as<uint8_t>();
      Serial.printf("[CLOUD REALTIME] >>> ĐỔI BỐI CẢNH SCENERY: %d <<<\n", sc);
      DisplayEngine::getInstance().setScenery(sc);
    }
    if (data.containsKey("sprite_scale")) {
      float sc = data["sprite_scale"].as<float>();
      Serial.printf("[CLOUD REALTIME] >>> ĐỔI KÍCH THƯỚC SCALE: %.2f <<<\n", sc);
      DisplayEngine::getInstance().setSpriteScale(sc);
    }
    if (data.containsKey("typewriter_speed")) {
      uint32_t spd = data["typewriter_speed"].as<uint32_t>();
      Serial.printf("[CLOUD REALTIME] >>> ĐỔI TỐC ĐỘ GÕ: %u ms <<<\n", spd);
      DisplayEngine::getInstance().setTypewriterSpeed(spd);
    }
    if (data.containsKey("hold_time")) {
      uint32_t ht = data["hold_time"].as<uint32_t>();
      Serial.printf("[CLOUD REALTIME] >>> ĐỔI THỜI GIAN DỪNG: %u ms <<<\n", ht);
      DisplayEngine::getInstance().setHoldTime(ht);
    }
    if (data.containsKey("freeze_text")) {
      bool frz = data["freeze_text"].as<bool>();
      Serial.printf("[CLOUD REALTIME] >>> CHẾ ĐỘ DỪNG CHỮ: %s <<<\n", frz ? "BẬT" : "TẮT");
      DisplayEngine::getInstance().setFreezeText(frz);
    }
    if (data.containsKey("auto_quote_cycle")) {
      bool aq = data["auto_quote_cycle"].as<bool>();
      Serial.printf("[CLOUD REALTIME] >>> TỰ ĐỔI QUOTES 2 PHÚT: %s <<<\n", aq ? "BẬT" : "TẮT");
      DisplayEngine::getInstance().setAutoQuoteCycle(aq);
    }
    if (data.containsKey("quote_cycle_interval")) {
      uint32_t itv = data["quote_cycle_interval"].as<uint32_t>();
      DisplayEngine::getInstance().setQuoteCycleInterval(itv);
    }
  }

  void loop() {
    if (WiFi.status() == WL_CONNECTED) {
      webSocket.loop();

      // Dual-Sync Poller an toàn (mỗi 3.5s nếu WS chưa kết nối)
      unsigned long now = millis();
      if (!isConnected && (now - lastPollTime >= 3500)) {
        lastPollTime = now;
        pollCloudState();
      }
    }
  }

  void pollCloudState() {
    WiFiClient pollClient;
    HTTPClient http;
    http.begin(pollClient, "http://161.118.196.170/api/state");
    http.setTimeout(1200);
    int code = http.GET();
    if (code == 200) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      DeserializationError err = deserializeJson(doc, payload);
      if (!err) {
        JsonObject data = doc.as<JsonObject>();
        applyData(data);
      }
    }
    http.end();
  }

  bool connected() const {
    return isConnected;
  }
};
