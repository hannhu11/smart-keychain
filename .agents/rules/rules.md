# 📜 QUY TẮC VẬN HÀNH & NGUYÊN TẮC THIẾT KẾ (SYSTEM RULES)

## 1. NGUYÊN TẮC BẮT BUỘC ĐỌC TRƯỚC MỖI PHIÊN (SESSION INITIALIZATION)
1. **Đọc Bộ Nhớ Đầu Tiên:** Mọi phiên làm việc bắt đầu bằng việc đọc file `.agents/rules/memory.md` để nắm bắt trạng thái dự án, các lỗi đã xử lý và hướng đi.
2. **Quy Trình Kiểm Tra Chéo (Cross-Checking):** Mọi tính năng phải có Checklist nghiệm thu rõ ràng, kiểm tra độc lập từng tiêu chí trước khi thông báo hoàn tất.
3. **Trải Nghiệm Người Dùng Là Tối Thượng (Human-First UI/UX):** Đặt suy nghĩ vào người nhận (bạn gái / người dùng non-tech) để giảm thiểu mọi rào cản thao tác.

---

## 2. TUYÊN NGÔN THIẾT KẾ ANTI-AI-SLOP (20 ĐIỀU CẤM KỴ)
Khi thiết kế giao diện Web, Mobile App hoặc đồ họa hiển thị:
1. ❌ KHÔNG dùng nền gradient tím - xanh đại trà (Purple-to-Blue generic gradient).
2. ❌ KHÔNG dùng chữ tiêu đề gradient hào nhoáng giả tạo.
3. ❌ KHÔNG lạm dụng icon cảm xúc (emoji) tràn lan trong tiêu đề.
4. ❌ KHÔNG dùng font Inter lười biếng ở mọi nơi. Sử dụng typography có cá tính (Pixel Retro / Space Grotesk / JetBrains Mono / Syne).
5. ❌ KHÔNG dùng khung viền thẻ màu cầu vồng (Rainbow border cards).
6. ❌ KHÔNG dùng hiệu ứng kính mờ (Glassmorphism) tương phản kém gây khó đọc.
7. ❌ KHÔNG dùng nền xám đục. Sử dụng nền đen sâu AMOLED thuần túy (`#000000`, `#0A0A0A`) với điểm nhấn neon sắc sảo.
8. ❌ KHÔNG dùng bố cục 3 hộp tính năng nhàm chán lặp lại.
9. ❌ KHÔNG dùng huy hiệu bo tròn (Pill badges) lơ lửng vô nghĩa.
10. ❌ KHÔNG gắn icon Lucide bừa bãi.
11. ❌ KHÔNG copy-paste giao diện Shadcn UI thô sơ chưa tùy biến.
12. ❌ KHÔNG dùng hiệu ứng cuộn mờ dần gây phân tâm.
13. ❌ KHÔNG dùng chùm sáng laser chạy theo con trỏ chuột.
14. ❌ KHÔNG dùng nút bấm đổi màu mờ nhạt thiếu dứt khoát.
15. ❌ KHÔNG dùng khoảng cách lộn xộn (tuân thủ nghiêm ngặt lưới 4px / 8px).
16. ❌ KHÔNG lạm dụng dấu gạch ngang dài (—) trong văn phong.
17. ❌ KHÔNG dùng từ ngữ sáo rỗng ("Nâng tầm trải nghiệm", "Đổi mới đột phá").
18. ❌ KHÔNG dùng font serif nghiêng gượng gạo trong tiêu đề công nghệ hiện đại.
19. ❌ KHÔNG ghép font tùy tiện thiếu tính nghệ thuật.
20. ❌ KHÔNG phủ hạt nhiễu giả (Fake grain) lên các mảng màu gradient rẻ tiền.

---

## 3. QUY TRÌNH /grill-me TRƯỚC KHI THAY ĐỔI KIẾN TRÚC
Trước khi thực hiện các đợt tái cấu trúc lớn hoặc bổ sung tính năng phức tạp:
1. Đọc kỹ `.agents/rules/memory.md`.
2. Đặt ra từ 3 đến 8 câu hỏi phản biện, làm rõ yêu cầu, góc khuất kỹ thuật (Edge cases) và luồng trải nghiệm cho người dùng.
3. Chờ người dùng xác nhận và thống nhất phương án trước khi triển khai mã nguồn.
