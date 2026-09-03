# 🧠 TRI THỨC & BỘ NHỚ DÀI HẠN (LONG-TERM KNOWLEDGE MEMORY)
# DỰ ÁN: SMART DIGITAL PIXEL KEYCHAIN (IoT LOVE COMPANION)

> **QUY TẮC CỐT LÕI (BẮT BUỘC ĐỌC ĐẦU TIÊN MỖI PHIÊN LÀM VIỆC):**
> 1. Mỗi khi bắt đầu bất kỳ đoạn chat, phiên làm việc hay task mới, Agent **BẮT BUỘC PHẢI ĐỌC FILE NÀY TRƯỚC TIÊN** (`.agents/rules/memory.md`).
> 2. Mọi giải pháp kỹ thuật phải đặt **TRẢI NGHIỆM NGƯỜI DÙNG (UI/UX)** lên hàng đầu (Zero-Friction cho người dùng non-tech).
> 3. Tuyệt đối **KHÔNG SỬ DỤNG EMOJI RẺ TIỀN / ICON FACEBOOK / AI SLOP GRADIENTS** trong thiết kế UI/UX; không làm animation chung chung qua loa mà bắt buộc phải thiết kế **RIÊNG BIỆT 100% CHI TIẾT** cho từng nhân vật / vũ khí / thú cưng / hiệu ứng.
> 4. Áp dụng chuẩn thiết kế **Modern Split-Screen Studio (1360px 2-Column)**: Cột trái ghim thiết bị mô phỏng 60 FPS + điều khiển nhanh; Cột phải là kho 50 Themes + Thanh gợi ý 1-Chạm Gửi Ngay (*"I love you 3000"*, *"Nhớ em nhiều"*...).
> 5. Mọi thay đổi hay xử lý lỗi phải có **BẢNG KIỂM TRA CHÉO (CROSS-CHECKING CHECKLIST)** rõ ràng để đánh giá và theo dõi.

---

## 1. BỐI CẢNH DỰ ÁN & HẠ TẦNG TOÀN DIỆN
- **Vi điều khiển chính:** ESP32S (30 chân, CP2102, Dual-Core 240MHz, 520KB SRAM).
- **Màn hình hiển thị:** 1.47" TFT IPS ST7789 ($172 \times 320$, SPI 40MHz qua `LovyanGFX` DMA Double-Buffer).
- **Hệ Thống Wi-Fi Auto-Cycling:**
  * Tự động quét và kết nối luân phiên qua: `Tuan Anh 2.4G` $\to$ `Tuan Anh` $\to$ `Tuan Anh 1` $\to$ `Tuan Anh 2` (Mật khẩu chung: `27011980`).
- **Giao Diện Web Studio Hiện Đại (Split-Screen Master-Detail):**
  * **Cột Trái (Sticky Simulator):** Màn hình Móc Khóa mô phỏng tương tác (chạm vào để đổi Theme), 6 viên kim cương chọn bảng màu, thanh gạt độ sáng 25-255.
  * **Cột Phải (Gallery & Quick Actions):** Khung tìm kiếm thời gian thực, 6 Tabs phân loại, và hàng nút Lời Nhắn Nhanh 1-Chạm gửi tức thì qua WebSocket + HTTP Push.
  * **Thanh Header Telemetry:** Hiển thị `🟢 CLOUD SYNC: 0ms &bull; 50 THEMES READY`.

---

## 2. BẢNG TIÊU CHUẨN KIỂM TRA CHÉO ĐÃ NGHIỆM THU (VERIFIED CHECKLIST)

- [x] **Tiêu chuẩn 1 (Bố cục 2 Cột Split-Screen):** Không còn bị trống đen 2 bên, ghim simulator cố định cực kỳ tiện dụng.
- [x] **Tiêu chuẩn 2 (Gợi ý 1-Chạm Gửi Nhanh):** 7 mẫu lời nhắn tình yêu phổ biến chạm phát gửi ngay.
- [x] **Tiêu chuẩn 3 (Card Cyber Glass):** Viền sáng neon, nhãn "ĐANG CHIẾU" nổi bật khi theme được kích hoạt.
- [x] **Tiêu chuẩn 4 (Tương Tác Chạm Trên Simulator):** Click vào màn hình mô phỏng tự động nhảy Theme kế tiếp.
- [x] **Tiêu chuẩn 5 (Deploy VPS Hoàn Tất):** Server VPS `161.118.196.170` đã chạy bản Studio mới nhất 100%.
