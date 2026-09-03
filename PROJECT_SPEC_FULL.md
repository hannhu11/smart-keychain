# FULL PROJECT SPECIFICATION: SMART DIGITAL PIXEL KEYCHAIN (IoT LOVE COMPANION)

## 1. System Overview & Philosophy
Thiết bị móc khóa thông minh dạng Pixel Art bỏ túi, thiết kế nguyên khối siêu nhỏ gọn. 
Hệ thống được thiết kế theo triết lý "Zero-Friction UX" (Trải nghiệm không rào cản cho người dùng non-tech), cho phép thay đổi giao diện, màu sắc, ảnh động và lời nhắn bằng 3 phương thức linh hoạt:
1. Nút bấm vật lý trực tiếp (One-click toggle).
2. Trang Web nội bộ không cần Internet (Offline QR-Code Captive Portal).
3. Trang Web đám mây đồng bộ từ xa (Cloud Sync via VPS & Domain WebSocket/MQTT).

---

## 2. Hardware Architecture & Pinout Mapping

### A. Core Electronics
- **Main MCU:** ESP32 NodeMCU DevKit V1 (ESP-WROOM-32 Dual-Core 240MHz) / ESP32-C3 SuperMini.
- **Display Module:** 1.47" TFT IPS LCD (ST7789P3 driver, 172x320 px, 247 PPI, 16-bit RGB565).
- **Power System (Module hóa gắn sau):**
  - Pin LiPo 3.7V (500mAh mã 602535 hoặc 800mAh mã 802540).
  - Mạch sạc/bảo vệ Type-C mini TP4056 (DW01A + FS8205A chống xả cạn/quá nạp).
  - Công tắc gạt nguồn cơ khí SS12D00 SPDT.
- **Interaction:** 
  - Nút bấm Tactile Switch 4 chân / Nút cảm ứng Touch.
  - (Tùy chọn tương lai) Cảm biến gia tốc MPU6050 để nhận diện thao tác lắc đổi hình.

### B. Pinout Configuration (ESP32)
| Component Pin | ESP32 GPIO | Mode / Signal | Function Description |
| :--- | :--- | :--- | :--- |
| **TFT_SCL** | GPIO 18 | VSPI SCK | Xung nhịp đồng bộ SPI (40MHz) |
| **TFT_SDA** | GPIO 23 | VSPI MOSI | Đường truyền dữ liệu hình ảnh |
| **TFT_RES** | GPIO 4 | Output | Reset phần cứng màn hình |
| **TFT_DC** | GPIO 2 | Output | Lệnh (Command) / Dữ liệu (Data) |
| **TFT_CS** | GPIO 15 | Output | Chip Select cố định frame |
| **TFT_BLK** | GPIO 32 (hoặc 3V3) | PWM Output | Điều chỉnh độ sáng đèn nền mượt |
| **BTN_MULTI** | GPIO 33 | INPUT_PULLUP | Nút bấm đa năng chuyển hình & cấu hình |
| **BAT_SENSE** | GPIO 35 | ADC Input | Đo điện áp pin qua cầu trở 100k/100k |

---

## 3. Graphics Rendering Engine (Locked 60 FPS)

Hệ thống đồ họa chạy qua thư viện **LovyanGFX** sử dụng kỹ thuật **Sprite Double-Buffering** (Vẽ toàn bộ lên RAM trước khi đẩy ra màn hình qua DMA) để loại bỏ hoàn toàn hiện tượng nhấp nháy, sọc mép hay xé hình:

### Layer Pipeline (Từ dưới lên trên):
1. **Layer 0 (Background):** Nền đen kịt (RGB565 `0x0000`) khử toàn bộ viền màn hình LCD.
2. **Layer 1 (Particle Emitter):** 35-50 hạt pixel mưa rơi/bụi sao ma trận chuyển động ngẫu nhiên theo vận tốc $v_y \in [2.0, 6.0]$, vệt đuôi mờ Alpha.
3. **Layer 2 (Floating Pixel Sprite):** 
   - Vật thể Pixel Art (Thanh kiếm pha lê, Trái tim Cyberpunk, Mèo lơ lửng).
   - Tọa độ dao động hình sin: $y(t) = y_{center} + A \cdot \sin(\omega t)$ kết hợp hiệu ứng Breathing Glow (phát sáng theo nhịp thở).
4. **Layer 3 (Typewriter Text Quote):** Lời nhắn/quote chạy từng ký tự kiểu máy đánh chữ ($50\text{ms}$/ký tự), tự động xuống dòng và tự chuyển quote sau 3.5 giây.
5. **Layer 4 (HUD / System UI):** Thanh pin mini và icon trạng thái kết nối Wi-Fi/Cloud.

---

## 4. Multi-Mode Interaction & UX Workflow