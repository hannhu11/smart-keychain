# 📦 DANH MỤC TOÀN BỘ VẬT LIỆU & LINH KIỆN ĐÃ TỔNG HỢP (INVENTORY DATABASE)

> **Ghi chú cập nhật:** Bản tổng hợp đầy đủ từ 2 hóa đơn PDF (Đơn Shopee & Hóa đơn Linh Kiện Điện Tử 3M #3M-153848), đơn hàng linh kiện cảm biến ảnh #102548 và các thiết bị phần cứng thực tế trên bàn làm việc.

---

## 1. ⚡ Vi điều khiển & Mạch nạp chương trình (Microcontrollers & Programmers)

| STT | Tên thiết bị / Model | Chip vi xử lý & Thông số kỹ thuật | Số lượng | Nguồn gốc / Tình trạng |
| :---: | :--- | :--- | :---: | :--- |
| 1 | **ESP32 NodeMCU DevKit V1 (30 chân)** | ESP-WROOM-32 (Dual-Core 240MHz, Wi-Fi 2.4GHz & Bluetooth BLE), UART CP2102 | **2** | 1 bo mới LuaNode32 (Đơn 3M) + 1 bo đang test |
| 2 | **ESP32-CAM (Kèm Camera OV2640)** | ESP32-S, 8MB PSRAM, Camera 2MP OV2640, Flash LED, khe MicroSD | **1** | Đơn đặt hàng #102548 |
| 3 | **Đế nạp chương trình ESP32-CAM-MB** | Mạch đế nạp nạp code trực tiếp qua cổng Micro-USB cho ESP32-CAM | **2** | 1 chiếc (Đơn Đông Quân) + 1 chiếc (Đơn 3M) |
| 4 | **NodeMCU ESP8266 ESP-12E (Cổng Type-C)** | ESP8266 (Single-core 80/160MHz, Wi-Fi 2.4GHz), chip nạp CH340, Type-C | **1** | Đơn Linh Kiện 3M |
| 5 | **NodeMCU ESP8266 ESP-12E (Cổng Micro-USB)** | ESP8266 (Bản Amica đáy trắng), chip nạp CP2102 | **1** | Đơn Linh Kiện 3M |
| 6 | **Kit Arduino Uno R3 (Bản Chip Cắm DIP)** | ATmega328P (16MHz), kèm cáp kết nối USB-B | **1** | Đơn Linh Kiện 3M |

---

## 2. 📺 Màn hình hiển thị & Mạch điều khiển (Displays & Drivers)

| STT | Tên thiết bị / Linh kiện | Thông số kỹ thuật & Giao tiếp | Số lượng | Nguồn gốc / Ứng dụng |
| :---: | :--- | :--- | :---: | :--- |
| 1 | **Màn hình TFT IPS 1.47 inch ST7789** | Độ phân giải $172 \times 320$, chuẩn giao tiếp SPI, module `GMT147SPI` | **1** | Có sẵn (Dùng cho Móc khóa Pixel Art) |
| 2 | **Màn hình TFT IPS 1.9 inch ST7789** | Độ phân giải $170 \times 320$, chuẩn giao tiếp SPI, góc nhìn rộng | **1** | Có sẵn trên bàn |
| 3 | **Màn hình LCD 1602 (Màu xanh lá)** | Màn hình 16 ký tự x 2 dòng, điện áp 5V | **2** | Đơn Linh Kiện 3M |
| 4 | **Module Chuyển đổi I2C cho LCD 1602/2004** | Chip PCF8574 chuyển bus song song sang I2C 2 dây | **2** | Đơn Linh Kiện 3M |

---

## 3. 📡 Cảm biến, Thời gian thực & Không dây (Sensors, RTC & Wireless)

| STT | Tên Module / Cảm biến | Chuẩn giao tiếp / Đặc tính kỹ thuật | Số lượng | Nguồn gốc |
| :---: | :--- | :--- | :---: | :--- |
| 1 | **Cảm biến khoảng cách Laser ToF VL53L0X V2** | Đo khoảng cách laser chính xác cao phạm vi 2m + Tấm che quang học, I2C | **1** | Đơn đặt hàng #102548 |
| 2 | **Cảm biến siêu âm HC-SR04** | Đo khoảng cách bằng sóng âm ($2\text{cm} - 400\text{cm}$) | **5** | Đơn Linh Kiện 3M |
| 3 | **Gá đỡ / Đế mica cho cảm biến HC-SR04** | Giá đỡ cố định cảm biến siêu âm lên mô hình / xe | **1** | Đơn đặt hàng #102548 |
| 4 | **Module thu phát hồng ngoại V1 (IR Sensor)** | Cặp LED phát & thu hồng ngoại, điều chỉnh độ nhạy qua biến trở | **3** | Đơn Linh Kiện 3M |
| 5 | **Module RTC thời gian thực DS3231 + AT24C32** | Đồng hồ thời gian thực siêu chính xác, pin nuôi CR2032, giao tiếp I2C | **1** | Đơn Linh Kiện 3M |
| 6 | **Module RFID PN532 NFC** | Đọc/ghi thẻ RFID/NFC 13.56MHz tầm xa $5 - 7\text{cm}$ (I2C/SPI/UART) | **1** | Đơn Linh Kiện 3M |
| 7 | **Module RFID RC522 (13.56MHz)** | Đọc thẻ RFID Mifare chuẩn SPI | **1** | Đơn Linh Kiện 3M |
| 8 | **Thẻ trắng RFID FM1108IC (13.56MHz)** | Thẻ dạng card trắng mỏng dùng cho RC522 / PN532 | **5** | Đơn Linh Kiện 3M |
| 9 | **Module LoRa Ra-01 (Ai-Thinker SX1278)** | Truyền thông không dây tầm xa 433MHz SPI, kèm ăng-ten lò xo | **1** | Có sẵn trên bàn |
| 10 | **Remote phát sóng RF 4 kênh (Móc khóa)** | 315MHz / 433MHz (4 nút bấm A, B, C, D nắp trượt kim loại) | **1** | Có sẵn trên bàn |
| 11 | **Remote điều khiển Hồng ngoại (IR Remote)** | Remote dẹt nhiều nút bấm phát sóng 38kHz | **1** | Có sẵn trên bàn |

---

## 4. ⚙️ Cơ cấu chấp hành, Đóng ngắt & Âm thanh (Actuators & Relays)

| STT | Tên thiết bị / Module | Thông số kỹ thuật | Số lượng | Nguồn gốc |
| :---: | :--- | :--- | :---: | :--- |
| 1 | **Động cơ Micro Servo SG90 (9g)** | Góc quay 180 độ, điện áp 4.8V - 6V, kèm bộ cánh servo | **3** | Đơn Linh Kiện 3M |
| 2 | **Module 4 Relay 5VDC (Opto cách ly)** | 4 kênh đóng ngắt 250VAC/30VDC 10A, kích mức thấp/cao | **1** | Đơn đặt hàng #102548 |
| 3 | **Module Tạo trễ - Chuyển mạch Relay 5V V2** | Mạch hẹn giờ đóng ngắt relay có màn hình LED hiển thị thời gian | **1** | Đơn Linh Kiện 3M |
| 4 | **Module Còi Chíp Buzzer 5V** | Còi báo động phát tiếng kêu bíp 5V tích hợp transistor kích | **5** | 2 chiếc (Shopee Linh Kiện 024) + 3 chiếc (Đơn 3M) |

---

## 5. 🔌 Linh kiện điện tử rời & Nguồn (Electronic Components & Power)

| STT | Loại linh kiện | Thông số chi tiết | Số lượng | Nguồn gốc |
| :---: | :--- | :--- | :---: | :--- |
| 1 | **IC Ghi dịch 74HC595 (DIP-16)** | 8-bit Serial-In / Parallel-Out Shift Register (mở rộng GPIO) | **5 con** | Đơn Linh Kiện 3M |
| 2 | **LED RGB Đục Ø5mm (Anot chung)** | Đèn LED 3 màu Dương chung | **2 con** | Đơn Linh Kiện 3M |
| 3 | **LED RGB Đục Ø5mm (Katot chung)** | Đèn LED 3 màu Âm chung | **2 con** | Đơn Linh Kiện 3M |
| 4 | **LED đơn phủ màu Ø3mm (Đỏ)** | Gói 10 con LED Ø3mm màu Đỏ | **1 gói (10 con)** | Đơn Linh Kiện 3M |
| 5 | **LED đơn phủ màu Ø3mm (Xanh Lá)** | Gói 10 con LED Ø3mm màu Xanh Lá | **1 gói (10 con)** | Đơn Linh Kiện 3M |
| 6 | **LED đơn phủ màu Ø3mm (Xanh Dương)**| Gói 10 con LED Ø3mm màu Xanh Dương | **1 gói (10 con)** | Đơn Linh Kiện 3M |
| 7 | **LED đơn phủ màu Ø3mm (Vàng)** | Gói 10 con LED Ø3mm màu Vàng | **1 gói (10 con)** | Đơn Linh Kiện 3M |
| 8 | **Điện trở vạch 1/4W 5% (1kΩ)** | Trở cắm 1kΩ | **2 gói/dây** | Đơn Linh Kiện 3M |
| 9 | **Điện trở vạch 1/4W 5% (2.2kΩ)** | Trở cắm 2.2kΩ (50 con / gói) | **2 gói (100 con)** | Đơn Linh Kiện 3M |
| 10 | **Điện trở vạch 1/4W 5% (10kΩ)** | Trở cắm 10kΩ (50 con / gói) | **1 gói (50 con)** | Đơn Linh Kiện 3M |
| 11 | **Nút nhấn 4 chân 12x12x7.2mm** | Nút bấm cơ học tactile switch | **4 chiếc** | Đơn Linh Kiện 3M |
| 12 | **Vỏ / Nắp chụp nút nhấn B3F 12x12** | 4 màu: Đỏ (1), Xanh Lá (1), Xanh Dương (1), Vàng (1) | **4 chiếc** | Đơn Linh Kiện 3M |
| 13 | **Thanh Jump Cái đơn 1x40P (2.54mm)** | Header cái đơn 40 chân màu đen | **1 thanh** | Đơn Linh Kiện 3M |
| 14 | **Pin vuông LI FENG 9V** | Pin nguồn 9V đa năng | **1 viên** | Đơn Linh Kiện 3M |
| 15 | **Dây nối pin 9V sang Jack DC 5.5x2.1mm**| Đầu cắm cấp nguồn DC cho Arduino Uno / Relay | **1 dây** | Đơn Linh Kiện 3M |

---

## 6. 🛠️ Breadboard, Dây cắm & Dụng cụ chế tạo (Tools & Prototyping)

| STT | Tên vật tư / Dụng cụ | Quy cách & Kích thước | Số lượng | Nguồn gốc |
| :---: | :--- | :--- | :---: | :--- |
| 1 | **Board Test mạch lớn MB-102** | Kích thước $16.5 \times 5.5\text{cm}$ (830 lỗ) | **2 bo** | Đơn Linh Kiện 3M |
| 2 | **Bo Test mạch nhỏ SYB-170** | Màu Trắng (170 lỗ) | **4 bo** | Đơn Linh Kiện 3M |
| 3 | **Dây cắm Breadboard Đực - Cái 20cm** | Bó dây 7 màu | **50 sợi** (1 bó 40 + 1 tép 10) | Đơn Linh Kiện 3M |
| 4 | **Dây cắm Breadboard Đực - Đực 20cm** | Bó dây 7 màu | **90 sợi** (1 bó 40 + 5 tép 10) | Đơn Linh Kiện 3M |
| 5 | **Dây cắm Breadboard Đực - Cái 10cm** | Bó dây 7 màu ngắn gọn | **40 sợi** (1 bó) | Đơn Linh Kiện 3M |
| 6 | **Dây cắm Breadboard Đực - Đực 10cm** | Bó dây 7 màu ngắn gọn | **40 sợi** (1 bó) | Đơn Linh Kiện 3M |
| 7 | **Cáp sạc / Nạp dữ liệu USB-A sang Micro-B**| Chiều dài 0.5m | **1 sợi** | Shopee Linh kiện 1688s |
| 8 | **Thiếc hàn không chì cao cấp 99.3%** | Cuộn 50g, sợi 0.8mm mối hàn bóng đẹp | **1 cuộn** | Đơn Linh Kiện 3M |
| 9 | **Hộp làm sạch mũi hàn sợi đồng** | Vệ sinh đầu mỏ hàn không làm tụt nhiệt | **1 hộp** | Đơn Linh Kiện 3M |
| 10 | **Nhựa thông lỏng (Flux lỏng 30ml)** | Chất trợ hàn giúp thiếc ngấu sâu vào chân linh kiện | **1 chai** | Đơn Linh Kiện 3M |
| 11 | **Bộ 3 kẹp gắp linh kiện điện tử vàng** | Nhíp gắp linh kiện điện tử & linh kiện dán SMD | **1 bộ** | Đơn Linh Kiện 3M |
| 12 | **Dao trổ cắt tỉa mô hình (Kèm 5 lưỡi)** | Cán dao trổ kim loại tiện lợi | **1 bộ** | Shopee Mô Hình Tăm Tre |
| 13 | **Keo dán siêu dính đa năng 502 (Chai lớn 100ml)**| Keo dán mô hình, mica, formex | **2 chai** | Shopee Mô Hình Tăm Tre |

---

## 7. 🚗 Mô hình xe, Bìa Formex & Decal Biển số (Model Car & Foam Materials)

| STT | Tên vật liệu / Mô hình | Phân loại / Quy cách | Số lượng | Nguồn gốc |
| :---: | :--- | :--- | :---: | :--- |
| 1 | **Bìa Formex trắng 30x30cm (Dày 3mm)** | Bìa Foam PVC làm khung vỏ handmade | **4 tấm** | Shopee Mô Hình Tăm Tre |
| 2 | **Bìa Formex trắng 30x30cm (Dày 5mm)** | Bìa Foam PVC dày vừa | **5 tấm** | Shopee Mô Hình Tăm Tre |
| 3 | **Bìa Formex trắng 30x30cm (Dày 8mm)** | Bìa Foam PVC chịu lực | **4 tấm** | Shopee Mô Hình Tăm Tre |
| 4 | **Bìa Formex đen 20x30cm (Dày 3mm)** | Bìa Foam màu đen làm vỏ thiết bị | **4 tấm** | Shopee Vật Liệu Quảng Cáo |
| 5 | **Bìa Formex đen 20x30cm (Dày 5mm)** | Bìa Foam màu đen làm khung vỏ | **5 tấm** | Shopee Vật Liệu Quảng Cáo |
| 6 | **Bìa Formex đen 20x30cm (Dày 8mm)** | Bìa Foam màu đen tấm dày | **4 tấm** | Shopee Vật Liệu Quảng Cáo |
| 7 | **Xe mô hình Lexus LX570 tỉ lệ 1:36 (Mở 4 cửa)**| Màu: Tesla Xanh | **1 chiếc**| Shopee Toy Mart |
| 8 | **Xe mô hình Mercedes G63 tỉ lệ 1:36 (Mở 4 cửa)** | Màu: Đen | **1 chiếc**| Shopee Toy Mart |
| 9 | **Xe mô hình Mercedes G63 tỉ lệ 1:36 (Mở 4 cửa)** | Màu: Xanh | **1 chiếc**| Shopee Toy Mart |
| 10 | **Xe mô hình Land Rover Defender kim loại 1:36** | Màu: Xanh dương | **1 chiếc**| Shopee Toy Mart |
| 11 | **Xe mô hình Land Rover Defender kim loại 1:36** | Màu: Xanh lá | **1 chiếc**| Shopee Toy Mart |
| 12 | **Bộ 10 cặp biển số mô hình tỉ lệ 1:24 ép plastic**| Trắng cờ ngẫu nhiên (HCM, HN, ĐN...) | **1 bộ** | Shopee Đồ Chơi KMK |
| 13 | **Phụ kiện biển số mô hình tỉ lệ 1:24 ép plastic** | Phân loại: Biển trắng ngẫu nhiên | **1 bộ** | Shopee Đồ Chơi KMK |
| 14 | **Phụ kiện biển số mô hình tỉ lệ 1:24 ép plastic** | Phân loại: Biển xanh ngẫu nhiên | **1 bộ** | Shopee Đồ Chơi KMK |
| 15 | **Phụ kiện biển số mô hình tỉ lệ 1:24 ép plastic** | Phân loại: Biển vàng ngẫu nhiên | **1 bộ** | Shopee Đồ Chơi KMK |
| 16 | **Phụ kiện biển số mô hình tỉ lệ 1:24 ép plastic** | Phân loại: Trắng cờ ngẫu nhiên | **1 bộ** | Shopee Đồ Chơi KMK |
| 17 | **Mô hình biển số xe ô tô tỉ lệ 1:32** | Phân loại: 5 cặp biển số Hồ Chí Minh | **1 bộ** | Shopee Đồ Chơi KMK |