# HƯỚNG DẪN KẾT NỐI VPS & CẤU HÌNH DOMAIN CHO DỰ ÁN SMART KEYCHAIN (ESP32 IoT)

> **Mục đích tài liệu:** Cung cấp đầy đủ toàn bộ thông tin về máy chủ VPS, SSH Key, Domain, phân bổ cổng (Port) và phương thức kết nối/triển khai từ A-Z dành cho phiên làm việc của dự án **Smart Keychain (Móc khóa thông minh ESP32)** hoặc bất kỳ cộng sự/AI nào tiếp quản.

---

## 1. Thông Tin Chi Tiết Máy Chủ VPS

| Thuộc tính | Giá trị chi tiết | Ghi chú |
| :--- | :--- | :--- |
| **Địa chỉ IP Public** | **`161.118.196.170`** | Địa chỉ IP tĩnh của máy chủ |
| **Hệ điều hành** | **Ubuntu 22.04 LTS (x86_64)** | Đã cài sẵn Docker, Docker Compose, Python3, Git, Nginx |
| **Tài khoản SSH (User)** | **`ubuntu`** | Có quyền `sudo` toàn quyền (Passwordless) |
| **Cấu hình phần cứng** | **12 GB RAM / 200 GB SSD** | Dung lượng trống > 165 GB SSD, chạy rất mượt |
| **Trạng thái hiện tại** | **Sẵn sàng 100%** | Dự án cũ (SigSafe) đã được dọn sạch hoàn toàn khỏi VPS, giải phóng toàn bộ Port 80, 443 |

---

## 2. Thông Tin SSH Private Key & Đường Dẫn File

Hệ thống sử dụng xác thực bằng **SSH Private Key** (không dùng mật khẩu). File key đã được lưu sẵn trên máy cục bộ của bạn tại các đường dẫn sau:

### 📁 Đường dẫn file SSH Key trên Windows:
* **Đường dẫn chính:**
  ```text
  C:\Users\ADMIN\Downloads\SigSafe\ssh-key-2026-03-18.key
  ```
* **Đường dẫn dự phòng:**
  ```text
  C:\Users\ADMIN\Downloads\Open-claw-2\ssh-key-2026-03-18.key
  ```
* **File Public Key:**
  ```text
  C:\Users\ADMIN\Downloads\SigSafe\ssh-key-2026-03-18.key.pub
  ```

---

## 3. Lệnh Kết Nối & Thao Tác Với VPS (Dành Cho Terminal / PowerShell / AI)

### A. Kết nối SSH vào VPS (Mở Terminal / PowerShell):
```powershell
ssh -i "C:\Users\ADMIN\Downloads\SigSafe\ssh-key-2026-03-18.key" -o StrictHostKeyChecking=no ubuntu@161.118.196.170
```

### B. Chạy lệnh trực tiếp từ xa (Remote Command Execution):
```powershell
# Kiểm tra tài nguyên và docker đang chạy
ssh -i "C:\Users\ADMIN\Downloads\SigSafe\ssh-key-2026-03-18.key" -o StrictHostKeyChecking=no ubuntu@161.118.196.170 "docker ps; df -h"
```

### C. Copy thư mục / file mã nguồn hoặc asset từ máy tính lên VPS:
```powershell
# Ví dụ copy thư mục backend của smart keychain lên VPS:
scp -i "C:\Users\ADMIN\Downloads\SigSafe\ssh-key-2026-03-18.key" -r "C:\Users\ADMIN\Downloads\smart keychain\server" ubuntu@161.118.196.170:/home/ubuntu/smart_keychain/
```

### D. Tải dữ liệu từ VPS về máy tính:
```powershell
scp -i "C:\Users\ADMIN\Downloads\SigSafe\ssh-key-2026-03-18.key" -r ubuntu@161.118.196.170:/home/ubuntu/smart_keychain/data "C:\Users\ADMIN\Downloads\smart keychain\data_backup\"
```

---

## 4. Thông Tin Tên Miền (Domain) & Cấu Hình DNS

* **Tên miền sở hữu:** **`signsafevn.online`**
* **Nhà cung cấp quản lý DNS:** **Namecheap** (Tài khoản người dùng).
* **Hạn sử dụng:** Đến ngày **20/03/2027** (Hoàn toàn thoải mái sử dụng dài hạn).

### 🌐 Cách trỏ Subdomain cho dự án Smart Keychain:
Bạn có thể tận dụng tên miền này để tạo các subdomain chuyên nghiệp cho móc khóa thông minh:
1. Đăng nhập vào trang quản trị Namecheap ➔ Chọn domain `signsafevn.online` ➔ **Advanced DNS**.
2. Thêm các bản ghi **A Record** trỏ về IP VPS `161.118.196.170`:

| Loại Record (Type) | Host (Tên gợi nhớ) | Giá trị (Value / IP) | Mục đích sử dụng |
| :--- | :--- | :--- | :--- |
| **A Record** | **`keychain`** | `161.118.196.170` | Web Portal đổi ảnh/gửi tin nhắn (`https://keychain.signsafevn.online`) |
| **A Record** | **`api`** | `161.118.196.170` | REST API / WebSocket cho ESP32 (`https://api.signsafevn.online`) |
| **A Record** | **`mqtt`** *(Tùy chọn)* | `161.118.196.170` | Broker MQTT thời gian thực (`mqtt.signsafevn.online`) |
| **A Record** | **`@`** *(Tùy chọn)* | `161.118.196.170` | Tên miền gốc `signsafevn.online` |

---

## 5. Tình Trạng Phân Bổ Cổng (Port Mapping) Trên VPS

| Port | Trạng thái | Mục đích đề xuất cho Smart Keychain |
| :--- | :--- | :--- |
| **80 / 443** | **Đang TRỐNG (100% Free)** | Chạy **Nginx Reverse Proxy** + Cấp chứng chỉ SSL HTTPS miễn phí (Let's Encrypt). Phục vụ Web Dashboard cho người dùng quét mã đổi ảnh. |
| **8000** | **Đang TRỐNG (Free)** | Chạy Backend API (FastAPI Python / Express Node.js) nhận upload ảnh GIF/PNG, convert sang RGB565 và trả JSON cho ESP32. |
| **1883 / 8883** | **Đang TRỐNG (Free)** | Cổng chuẩn chạy **Eclipse Mosquitto (MQTT Broker)** nếu ESP32 dùng giao thức MQTT để nhận thông báo tức thì (Push Notification). |
| **9001** | **Đang TRỐNG (Free)** | Cổng WebSocket cho MQTT (nếu giao diện Web muốn subscribe trực tiếp topic của móc khóa). |

*(Lưu ý: Các port 3001, 5434, 6379, 8001 thuộc một service phụ nền cũ aegisnode, hoàn toàn độc lập và không ảnh hưởng đến các port 80/443/8000/1883 của Smart Keychain).*

---

## 6. Kiến Trúc Đề Xuất Cho Hệ Thống Smart Keychain Cloud Sync (Mode 2)

```
       [ Người Dùng / Bạn Gái ]
                 │
                 │ (Truy cập Web / Mobile Browser)
                 ▼
    ┌────────────────────────────────────────────────────────┐
    │              VPS Ubuntu (161.118.196.170)              │
    │                                                        │
    │   ┌────────────────────────────────────────────────┐   │
    │   │  Nginx Reverse Proxy (Port 80/443 SSL HTTPS)   │   │
    │   └───────────────┬─────────────────┬──────────────┘   │
    │                   │                 │                  │
    │                   ▼                 ▼                  │
    │      ┌─────────────────────┐   ┌───────────────────┐   │
    │      │  Web Portal Frontend│   │  API Backend Core │   │
    │      │  (Giao diện gửi ảnh │   │  (FastAPI / Node) │   │
    │      │   & lời nhắn tình   │   │  - Xử lý ảnh sang │   │
    │      │   cảm Pixel Art)    │   │    RGB565 / BIN   │   │
    │      └─────────────────────┘   │  - REST/WebSocket │   │
    │                                └─────────┬─────────┘   │
    │                                          │             │
    └──────────────────────────────────────────┼─────────────┘
                                               │
                                               │ (Wi-Fi 2.4GHz / HTTP GET / WebSocket)
                                               ▼
                              ┌──────────────────────────────────┐
                              │  Móc Khóa ESP32 DevKit V1        │
                              │  - Chip: ESP32-WROOM-32          │
                              │  - Màn hình: 1.47" ST7789 IPS    │
                              │  - Lưu cache vào LittleFS/Flash  │
                              │  - Render Double-Buffer 60 FPS   │
                              └──────────────────────────────────┘
```

---

## 7. Mẫu Docker Compose Backend & Nginx Chuẩn Cho Smart Keychain

Khi session Smart Keychain bắt tay vào làm phần Cloud Server, bạn chỉ cần tạo thư mục `/home/ubuntu/smart_keychain` trên VPS và dùng cấu hình mẫu sau:

```yaml
# /home/ubuntu/smart_keychain/docker-compose.yml
services:
  keychain-api:
    build: ./backend
    container_name: keychain_api
    restart: unless-stopped
    ports:
      - "8000:8000"
    volumes:
      - ./uploads:/app/uploads

  mosquitto:
    image: eclipse-mosquitto:2
    container_name: keychain_mqtt
    restart: unless-stopped
    ports:
      - "1883:1883"
      - "9001:9001"
    volumes:
      - ./mosquitto/config:/mosquitto/config
      - ./mosquitto/data:/mosquitto/data

  nginx:
    image: nginx:alpine
    container_name: keychain_nginx
    restart: unless-stopped
    ports:
      - "80:80"
      - "443:443"
    volumes:
      - ./nginx.conf:/etc/nginx/nginx.conf:ro
      - ./certbot/conf:/etc/letsencrypt:ro
      - ./certbot/www:/var/www/certbot:ro
    depends_on:
      - keychain-api
```

---

## 8. Checklist Quan Trọng Khi Bắt Đầu Dự Án Mới
1. **Lệnh test kết nối đầu tiên:**
   Chạy lệnh ở mục `3.A` trên máy Windows để đảm bảo SSH thông suốt.
2. **Cập nhật DNS:**
   Thêm record `keychain` hoặc `api` trong Namecheap trỏ về `161.118.196.170`.
3. **Mã nguồn ESP32 Firmware:**
   Các thư viện nạp trên ESP32: `LovyanGFX` hoặc `TFT_eSPI` (với ST7789 172x320), `HTTPClient.h`, `ArduinoJson.h`, `LittleFS.h`.
4. **An toàn bảo mật:**
   Không commit file `*.key` hay `*.pem` lên GitHub public repository.
