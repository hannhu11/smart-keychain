#pragma once
#include <Arduino.h>

// ==========================================
// CẤU HÌNH CHÂN PHẦN CỨNG ESP32S (30 CHÂN)
// ==========================================
#define TFT_MOSI_PIN   23  // D23 -> SDA trên màn hình 1.47"
#define TFT_SCLK_PIN   18  // D18 -> SCL trên màn hình 1.47"
#define TFT_DC_PIN     2   // D2  -> DC trên màn hình 1.47"
#define TFT_RST_PIN    4   // D4  -> RES trên màn hình 1.47"
#define TFT_CS_PIN     15  // D15 -> CS trên màn hình 1.47"
#define TFT_BL_PIN     32  // D32 -> BL/BLK (Điều khiển PWM đèn nền)

#define BTN_PIN        33  // D33 -> Nút bấm đa năng (INPUT_PULLUP)
#define BAT_ADC_PIN    35  // D35 -> Cầu phân áp đo Pin 3.7V

// ==========================================
// THÔNG SỐ HIỂN THỊ MÀN HÌNH 1.47" ST7789
// ==========================================
#define SCREEN_WIDTH   172
#define SCREEN_HEIGHT  320
#define SCREEN_OFFSET_X 34  // Khử sọc mép chuẩn cho 1.47"
#define SCREEN_OFFSET_Y 0

// ==========================================
// CẤU HÌNH MẠNG WI-FI NỘI BỘ & CLOUD VPS
// ==========================================
#define AP_SSID          "Love_Keychain"
#define AP_PASSWORD      ""           // Để trống cho phép kết nối tự động
#define AP_TIMEOUT_SEC   180          // 3 phút tự động tắt chế độ hiển thị AP

// Wi-Fi gia đình (STA Mode)
#define HOME_WIFI_SSID   "Tuan Anh 1"
#define HOME_WIFI_PASS   "27011980"
#define HOME_WIFI_SSID_2 "Tuan Anh 2"
#define HOME_WIFI_PASS_2 "27011980"

// Cloud VPS Backend
#define CLOUD_HOST       "app.signsafevn.online"
#define CLOUD_PORT       443
#define CLOUD_WS_PATH    "/ws/keychain"
#define CLOUD_IP_BACKUP  "161.118.196.170"
#define CLOUD_PORT_BACKUP 8000
