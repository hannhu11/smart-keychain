#pragma once
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class SpriteRenderer {
public:
  static void drawTheme(LGFX_Sprite* spr, int id, int cx, int cy, float breath, float angle) {
    id = (id >= 0) ? (id % 250) : 0;

    switch (id) {
      // =========================================================================
      // 1. ANIME & GENSHIN (0..11) - 3-LAYER SHADING & ELEMENTAL AURAS
      // =========================================================================

      case 0: // Hu Tao & Boo Tao
        // Tóc twintails bồng bềnh 3 lớp màu (bóng đổ 0x2800 -> nâu đỏ 0x5100 -> ngọn cam 0xA960)
        spr->fillRoundRect(cx - 36, cy - 18 + (int)(sin(breath * 6.28f) * 4), 14, 46, 6, 0x2800);
        spr->fillRoundRect(cx - 34, cy - 16 + (int)(sin(breath * 6.28f) * 4), 10, 42, 5, 0x5100);
        spr->fillRoundRect(cx + 22, cy - 18 + (int)(sin(breath * 6.28f + 1.2f) * 4), 14, 46, 6, 0x2800);
        spr->fillRoundRect(cx + 24, cy - 16 + (int)(sin(breath * 6.28f + 1.2f) * 4), 10, 42, 5, 0x5100);

        // Khuôn mặt anime & bóng cổ
        spr->fillRoundRect(cx - 18, cy - 14, 36, 30, 6, 0xFFF2);
        spr->fillRect(cx - 14, cy + 12, 28, 4, 0xFCE0); // Bóng cằm

        // Mũ Bát Phương (Porkpie Hat) + Hoa Mận Đỏ thêu viền vàng
        spr->fillRoundRect(cx - 26, cy - 38, 52, 24, 6, 0x18C3);
        spr->drawRoundRect(cx - 26, cy - 38, 52, 24, 6, 0x0841);
        spr->fillCircle(cx - 12, cy - 28, 5, 0xF800); // Hoa mận đỏ
        spr->drawPixel(cx - 12, cy - 28, TFT_YELLOW); // Nhụy vàng
        spr->drawPixel(cx - 14, cy - 28, 0xF9E0);
        spr->drawPixel(cx - 10, cy - 28, 0xF9E0);

        // Đôi mắt hoa đào (Đỏ mận + đồng tử sao + đốm sáng trắng)
        spr->fillRoundRect(cx - 14, cy - 6, 9, 11, 3, 0xB800);
        spr->fillRoundRect(cx + 5, cy - 6, 9, 11, 3, 0xB800);
        spr->fillRect(cx - 12, cy - 5, 5, 8, TFT_RED);
        spr->fillRect(cx + 7, cy - 5, 5, 8, TFT_RED);
        spr->drawPixel(cx - 11, cy - 4, TFT_WHITE); // Anime shine
        spr->drawPixel(cx + 8, cy - 4, TFT_WHITE);
        spr->fillCircle(cx - 10, cy + 6, 2, 0xFCAE); // Má hồng
        spr->fillCircle(cx + 10, cy + 6, 2, 0xFCAE);

        // Hồn ma Boo Tao bay lượn quanh chủ nhân
        {
          int gx = cx + 34 + (int)(cos(angle * 2.2f) * 10);
          int gy = cy - 28 + (int)(sin(angle * 2.2f) * 10);
          spr->fillCircle(gx, gy, 12, TFT_WHITE);
          spr->fillTriangle(gx - 8, gy + 4, gx + 8, gy + 4, gx, gy + 16, TFT_WHITE); // Đuôi ma
          spr->fillCircle(gx - 4, gy - 3, 2, TFT_BLACK); // Mắt ma
          spr->fillCircle(gx + 4, gy - 3, 2, TFT_BLACK);
          spr->fillRoundRect(gx - 3, gy + 2, 6, 3, 1, 0xF800); // Miệng cười mở
          spr->drawPixel(gx + (int)(sin(angle * 4) * 5), gy - 12, 0xFA60);
        }
        break;

      case 1: // Anya Forger (Waku Waku)
        // Mái tóc hồng pastel bồng bềnh + bóng khối
        spr->fillRoundRect(cx - 26, cy - 36, 52, 48, 9, 0xFDB8);
        spr->fillRoundRect(cx - 20, cy - 16, 40, 28, 6, 0xFFF2); // Mặt trắng hồng

        // Cặp sừng trang sức đen viền vàng Chimera
        spr->fillTriangle(cx - 26, cy - 30, cx - 17, cy - 50, cx - 8, cy - 30, TFT_BLACK);
        spr->drawTriangle(cx - 26, cy - 30, cx - 17, cy - 50, cx - 8, cy - 30, 0xFFE0);
        spr->fillTriangle(cx + 8, cy - 30, cx + 17, cy - 50, cx + 26, cy - 30, TFT_BLACK);
        spr->drawTriangle(cx + 8, cy - 30, cx + 17, cy - 50, cx + 26, cy - 30, 0xFFE0);

        // Mắt Waku Waku long lanh (Xanh lục bảo + đốm sáng 4 cánh sao)
        spr->fillRoundRect(cx - 15, cy - 9, 10, 13, 3, 0x04C0);
        spr->fillRoundRect(cx + 5, cy - 9, 10, 13, 3, 0x04C0);
        spr->fillRect(cx - 13, cy - 7, 6, 8, 0x07E0);
        spr->fillRect(cx + 7, cy - 7, 6, 8, 0x07E0);
        spr->fillRect(cx - 13, cy - 7, 3, 3, TFT_WHITE); // Star shine
        spr->fillRect(cx + 7, cy - 7, 3, 3, TFT_WHITE);
        spr->fillCircle(cx - 11, cy + 6, 3, 0xFBAE); // Má hồng to
        spr->fillCircle(cx + 11, cy + 6, 3, 0xFBAE);

        // Hạt sao lấp lánh Waku Waku bay quanh
        spr->drawPixel(cx + 30 + (int)(cos(angle * 3) * 4), cy - 24, TFT_YELLOW);
        spr->drawPixel(cx - 30 + (int)(sin(angle * 3) * 4), cy - 20, TFT_YELLOW);
        break;

      case 2: // Raiden Shogun (Tia Sét Vĩnh Cửu)
        // Mái tóc tím thắt bím dài + Trâm cài Kanzashi hoa vàng
        spr->fillRoundRect(cx - 24, cy - 32, 48, 40, 7, 0x4810);
        spr->fillRoundRect(cx - 20, cy - 28, 40, 36, 6, 0x6915);
        spr->fillRoundRect(cx - 16, cy - 14, 32, 28, 6, 0xFFF2);
        spr->drawLine(cx + 10, cy - 34, cx + 22, cy - 42, TFT_YELLOW);

        // Vòng sấm sét 3-Tomoe (Chakra Desiderata) sau lưng
        {
          int ringR = 40 + (int)(breath * 6);
          spr->drawCircle(cx, cy, ringR, 0x981F);
          spr->drawCircle(cx, cy, ringR + 1, 0xDFFF);
          for (int i = 0; i < 3; i++) {
            float a = i * 2.094f + angle * 1.5f;
            int tx = cx + (int)(cos(a) * ringR);
            int ty = cy + (int)(sin(a) * ringR);
            spr->fillCircle(tx, ty, 3, 0xE7FF);
          }
        }

        // Mắt Lôi Thần tím sáng
        spr->fillRect(cx - 12, cy - 6, 7, 9, 0x82DF);
        spr->fillRect(cx + 5, cy - 6, 7, 9, 0x82DF);
        spr->drawPixel(cx - 10, cy - 5, TFT_WHITE);
        spr->drawPixel(cx + 7, cy - 5, TFT_WHITE);
        break;

      case 3: // Furina Fontaine (Sân Khấu Thủy Thần)
        // Mũ quý tộc chóp cao xanh biển + viền ruy băng trắng
        spr->fillRoundRect(cx - 24, cy - 44, 48, 28, 6, 0x0210);
        spr->fillRect(cx - 30, cy - 18, 60, 6, TFT_WHITE); // Vành nón
        spr->fillRoundRect(cx - 20, cy - 14, 40, 34, 6, 0xDEFB); // Tóc xanh nhạt gợn sóng
        spr->fillRoundRect(cx - 15, cy - 10, 30, 24, 5, 0xFFF2); // Mặt

        // Mắt Thủy Thần dị sắc (Xanh lam & xanh dương đậm)
        spr->fillRect(cx - 11, cy - 5, 7, 8, 0x05FF);
        spr->fillRect(cx + 4, cy - 5, 7, 8, 0x02DF);
        spr->drawPixel(cx - 9, cy - 4, TFT_WHITE);
        spr->drawPixel(cx + 6, cy - 4, TFT_WHITE);

        // Bong bóng nước nổi lững lờ
        for (int i = 0; i < 4; i++) {
          int bx = cx - 28 + i * 18 + (int)(sin(angle * 2 + i) * 6);
          int by = cy - 20 + (int)(cos(angle * 2 + i) * 12);
          spr->drawCircle(bx, by, 4, 0x07FF);
          spr->drawPixel(bx - 1, by - 1, TFT_WHITE);
        }
        break;

      case 4: // Nahida Dendro (Thảo Thần)
        // Mái tóc trắng xanh mầm cây + lá sen
        spr->fillRoundRect(cx - 24, cy - 34, 48, 38, 7, 0xF7BE);
        spr->fillRoundRect(cx - 28, cy - 24, 12, 22, 4, 0x05E0); // Lọn tóc xanh
        spr->fillRoundRect(cx - 16, cy - 12, 32, 26, 5, 0xFFF2);

        // Đôi mắt Thảo thần màu ngọc bích lục bảo
        spr->fillRect(cx - 12, cy - 5, 8, 9, 0x07E0);
        spr->fillRect(cx + 4, cy - 5, 8, 9, 0x07E0);
        spr->drawPixel(cx - 10, cy - 4, TFT_WHITE);
        spr->drawPixel(cx + 6, cy - 4, TFT_WHITE);

        // Bàn phím số Ma trận Thảo (Sanctuary Grid)
        spr->drawRect(cx - 24, cy + 22, 48, 6, 0x07E0);
        for (int x = -20; x <= 20; x += 10) spr->drawFastVLine(cx + x, cy + 22, 6, 0xA7E0);
        break;

      case 5: // Xiao Vigilant Yaksha (Dạ Xoa Giáng Ma)
        // Tóc xanh lục đậm phong lôi + Vệt highlight xanh ngọc
        spr->fillRoundRect(cx - 24, cy - 34, 48, 38, 6, 0x028A);
        spr->fillRoundRect(cx - 16, cy - 14, 32, 26, 5, 0xFFF2);

        // Mắt vàng hổ phách sắc bén + viền đỏ đuôi mắt
        spr->fillRect(cx - 12, cy - 6, 8, 7, 0xFDA0);
        spr->fillRect(cx + 4, cy - 6, 8, 7, 0xFDA0);
        spr->drawFastHLine(cx - 14, cy - 7, 10, 0xF800); // Eyeliner đỏ
        spr->drawFastHLine(cx + 4, cy - 7, 10, 0xF800);

        // Mặt nạ Dạ Xoa Dạ Xoa bên hông
        spr->fillRoundRect(cx + 16, cy - 26, 18, 22, 4, 0x0375);
        spr->drawPixel(cx + 20, cy - 20, TFT_RED);
        spr->drawPixel(cx + 28, cy - 20, TFT_RED);

        // Hòa Diệp Thương (Primordial Jade Spear) phóng tia sáng
        spr->drawLine(cx - 36, cy + 36, cx - 22, cy - 42, 0x07FF);
        spr->drawLine(cx - 35, cy + 36, cx - 21, cy - 42, 0xFFFF);
        break;

      case 6: // Gojo Satoru (Vô Hạ Hạn)
        // Mái tóc trắng nhọn dựng đặc trưng
        spr->fillRoundRect(cx - 24, cy - 40, 48, 34, 6, TFT_WHITE);
        spr->drawRoundRect(cx - 24, cy - 40, 48, 34, 6, 0xCE59);
        spr->fillRoundRect(cx - 16, cy - 14, 32, 26, 5, 0xFFF2);

        // Bịt mắt đen huyền thoại
        spr->fillRect(cx - 18, cy - 12, 36, 12, 0x10A2);
        spr->drawFastHLine(cx - 18, cy - 6, 36, 0x3186);

        // Quả cầu Hách (Đỏ) và Xanh (Lam) Vô Hạ Hạn xoay tròn
        {
          int ox = (int)(cos(angle * 3.0f) * 32.0f);
          int oy = (int)(sin(angle * 3.0f) * 16.0f);
          spr->fillCircle(cx - ox, cy + oy, 9, TFT_BLUE);
          spr->fillCircle(cx - ox, cy + oy, 5, 0x7FFF);
          spr->fillCircle(cx + ox, cy - oy, 9, TFT_RED);
          spr->fillCircle(cx + ox, cy - oy, 5, 0xFCAE);
        }
        break;

      case 7: // Nezuko Kamado (Huyết Quỷ Thuật)
        // Mái tóc đen dài uốn lượn + Ngọn tóc chuyển màu cam lửa
        spr->fillRoundRect(cx - 24, cy - 36, 48, 44, 6, 0x10A2);
        spr->fillRect(cx - 24, cy + 4, 14, 24, 0xFA60); // Đuôi tóc cam
        spr->fillRect(cx + 10, cy + 4, 14, 24, 0xFA60);
        spr->fillRoundRect(cx - 16, cy - 14, 32, 26, 5, 0xFFF2);

        // Mắt hồng ngọc lấp lánh
        spr->fillRect(cx - 12, cy - 6, 8, 8, 0xFA8F);
        spr->fillRect(cx + 4, cy - 6, 8, 8, 0xFA8F);

        // Ống tre ngậm miệng + Dây buộc đỏ
        spr->fillRoundRect(cx - 14, cy + 3, 28, 10, 3, 0x05E0);
        spr->drawRoundRect(cx - 14, cy + 3, 28, 10, 3, 0x0360);
        spr->drawFastVLine(cx - 4, cy + 3, 10, 0x0360);
        spr->drawFastVLine(cx + 4, cy + 3, 10, 0x0360);
        spr->drawFastHLine(cx - 18, cy + 8, 4, TFT_RED);
        spr->drawFastHLine(cx + 14, cy + 8, 4, TFT_RED);
        break;

      case 8: // Tanjiro Kamado (Hỏa Thần Điệu Múa)
        // Tóc nâu đỏ vuốt ngược + Vết sẹo Hỏa Thần trên trán
        spr->fillRoundRect(cx - 24, cy - 36, 48, 34, 6, 0x6182);
        spr->fillRoundRect(cx - 16, cy - 14, 32, 26, 5, 0xFFF2);
        spr->fillRect(cx - 14, cy - 12, 6, 6, 0xA000);

        // Hoa tai Hanafuda đung đưa
        spr->fillRect(cx - 20, cy - 2, 4, 12, TFT_WHITE);
        spr->drawPixel(cx - 18, cy + 4, TFT_RED);

        // Vòng Rồng Lửa Hinokami Kagura cuốn quanh người
        {
          int arcR = 42 + (int)(breath * 4);
          spr->drawCircle(cx, cy, arcR, 0xFA60);
          spr->drawCircle(cx, cy, arcR + 1, TFT_YELLOW);
          spr->drawCircle(cx, cy, arcR + 2, TFT_WHITE);
          spr->drawPixel(cx + (int)(cos(angle * 5) * arcR), cy + (int)(sin(angle * 5) * arcR), TFT_YELLOW);
        }
        break;

      case 9: // Roronoa Zoro (Tam Kiếm Phái)
        // Tóc xanh rêu + Băng đeo tay xanh đen
        spr->fillRoundRect(cx - 22, cy - 34, 44, 30, 6, 0x04C0);
        spr->fillRoundRect(cx - 16, cy - 10, 32, 26, 5, 0xFFF2);
        spr->drawLine(cx - 10, cy - 8, cx - 10, cy - 1, TFT_BLACK);

        // 3 Thanh Kiếm (Wado Ichimonji, Sandai Kitetsu, Enma)
        spr->drawLine(cx - 40, cy - 34, cx + 40, cy + 34, 0x07E0);
        spr->drawLine(cx - 39, cy - 34, cx + 41, cy + 34, TFT_WHITE);
        spr->drawLine(cx - 40, cy + 34, cx + 40, cy - 34, 0x07E0);
        spr->drawLine(cx - 39, cy + 34, cx + 41, cy - 34, TFT_WHITE);
        spr->drawFastHLine(cx - 30, cy + 4, 60, TFT_YELLOW);
        break;

      case 10: // Luffy Gear 5 Nika (Thần Mặt Trời)
        // Tóc mây trắng cuồn cuộn bay phấp phới
        spr->fillRoundRect(cx - 28, cy - 42, 56, 42, 10, TFT_WHITE);
        spr->drawRoundRect(cx - 28, cy - 42, 56, 42, 10, 0xDEFB);
        spr->fillRoundRect(cx - 16, cy - 10, 32, 26, 5, 0xFFF2);

        // Mắt xoắn ốc vui tươi đặc trưng Nika
        spr->drawCircle(cx - 8, cy - 3, 5, 0xFA60);
        spr->drawCircle(cx + 8, cy - 3, 5, 0xFA60);
        spr->fillCircle(cx - 8, cy - 3, 2, TFT_BLACK);
        spr->fillCircle(cx + 8, cy - 3, 2, TFT_BLACK);

        // Dải mây vũ y Hagoromo lượn quanh cổ
        spr->drawArc(cx, cy + 16, 26, 28, 40, 140, TFT_WHITE);
        spr->drawArc(cx, cy + 16, 28, 30, 40, 140, 0xDEFB);
        break;

      case 11: // Naruto Sage Mode (Hiền Nhân Cửu Vĩ)
        // Mái tóc vàng nhọn + Băng trán Konoha lá bạc
        spr->fillRoundRect(cx - 24, cy - 40, 48, 34, 6, TFT_YELLOW);
        spr->fillRect(cx - 18, cy - 18, 36, 8, 0x7BEF);
        spr->drawPixel(cx, cy - 14, TFT_WHITE);
        spr->fillRoundRect(cx - 16, cy - 10, 32, 26, 5, 0xFFF2);

        // Mắt Hiền Nhân cam + Đồng tử cóc ngang
        spr->fillRect(cx - 15, cy - 6, 10, 9, 0xFA60);
        spr->fillRect(cx + 5, cy - 6, 10, 9, 0xFA60);
        spr->drawFastHLine(cx - 13, cy - 2, 6, TFT_BLACK);
        spr->drawFastHLine(cx + 7, cy - 2, 6, TFT_BLACK);

        // Quả cầu Rasengan xoáy tốc độ cao
        {
          int rx = cx + 30;
          int ry = cy + 14;
          spr->fillCircle(rx, ry, 12, 0x07FF);
          spr->drawCircle(rx, ry, 13, TFT_WHITE);
          for (int i = 0; i < 4; i++) {
            float a = angle * 6.0f + i * 1.57f;
            spr->drawPixel(rx + (int)(cos(a) * 10), ry + (int)(sin(a) * 10), TFT_WHITE);
          }
        }
        break;

      // =========================================================================
      // 2. VŨ KHÍ & CYBERPUNK (12..21) - REAL 3D ISOMETRIC BEVELS & LIGHT GLOW
      // =========================================================================

      case 12: // Thần Kiếm Tuyệt Phẩm (The Holy Claymore / Excalibur - Chuẩn 1:1 Ảnh Chụp Thật)
        {
          float cosA = 0.70710678f;
          float sinA = -0.70710678f;
          
          auto toX = [=](float u, float v) -> int {
            return (int)roundf(cx + u * cosA - v * sinA);
          };
          auto toY = [=](float u, float v) -> int {
            return (int)roundf(cy + u * sinA + v * cosA);
          };

          auto drawTiltedQuad = [&](float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4, uint16_t col) {
            spr->fillTriangle(toX(u1,v1), toY(u1,v1), toX(u2,v2), toY(u2,v2), toX(u3,v3), toY(u3,v3), col);
            spr->fillTriangle(toX(u1,v1), toY(u1,v1), toX(u3,v3), toY(u3,v3), toX(u4,v4), toY(u4,v4), col);
          };

          uint16_t colAura = TFT_WHITE;
          uint16_t colCyan = lgfx::color565(0, 240, 255);
          uint16_t colBlade = lgfx::color565(44, 54, 94);
          uint16_t colGrip = lgfx::color565(20, 25, 45);

          // 1. Hào quang Aura trắng phát sáng viền ngoài (Outer White Aura)
          drawTiltedQuad(-16, -18, 52, -18, 52, 18, -16, 18, colAura);
          spr->fillTriangle(toX(52, -18), toY(52, -18), toX(66, 0), toY(66, 0), toX(52, 18), toY(52, 18), colAura);
          drawTiltedQuad(-28, -32, -16, -32, -16, 32, -28, 32, colAura);
          // Cánh chim chuôi kiếm xòe ra sau
          drawTiltedQuad(-32, -28, -20, -32, -18, -24, -30, -20, colAura);
          drawTiltedQuad(-32, 28, -20, 32, -18, 24, -30, 20, colAura);

          drawTiltedQuad(-50, -7, -26, -7, -26, 7, -50, 7, colAura);
          drawTiltedQuad(-64, -14, -48, -14, -48, 14, -64, 14, colAura);
          spr->fillTriangle(toX(-64, -14), toY(-64, -14), toX(-68, 0), toY(-68, 0), toX(-64, 14), toY(-64, 14), colAura);

          // 2. Viền lưỡi Neon Cyan
          drawTiltedQuad(-15, -15, 50, -15, 50, 15, -15, 15, colCyan);
          spr->fillTriangle(toX(50, -15), toY(50, -15), toX(62, 0), toY(62, 0), toX(50, 15), toY(50, 15), colCyan);
          drawTiltedQuad(-25, -28, -17, -28, -17, 28, -25, 28, colCyan);

          // 3. Thân kiếm Thép Tím Chàm (Deep Slate Indigo)
          drawTiltedQuad(-14, -10, 46, -10, 46, 10, -14, 10, colBlade);
          spr->fillTriangle(toX(46, -10), toY(46, -10), toX(54, 0), toY(54, 0), toX(46, 10), toY(46, 10), colBlade);

          // 4. Lõi Ngọc Trung Tâm (Central Power Core Jewel) & Cổ tự Kim Cương
          spr->drawLine(toX(-12, 0), toY(-12, 0), toX(48, 0), toY(48, 0), colAura);
          // Lõi ngọc phát quang lớn ở thân kiếm
          drawTiltedQuad(10, -7, 20, 0, 10, 7, 0, 0, colAura);
          drawTiltedQuad(10, -4, 17, 0, 10, 4, 3, 0, colCyan);
          spr->fillCircle(toX(10, 0), toY(10, 0), 2, TFT_WHITE);

          for (float ru : {-3.0f, 32.0f}) {
            drawTiltedQuad(ru - 3, 0, ru, -4, ru + 3, 0, ru, 4, colAura);
          }

          // 5. Chuôi kiếm hoa văn cánh chim & Ngọc trung tâm
          drawTiltedQuad(-22, -8, -16, 0, -22, 8, -28, 0, colAura);
          drawTiltedQuad(-22, -4, -18, 0, -22, 4, -26, 0, colCyan);
          spr->drawPixel(toX(-22, 0), toY(-22, 0), TFT_WHITE);

          // 6. Cán kiếm quấn dây da xanh hoàng gia
          drawTiltedQuad(-48, -4, -26, -4, -26, 4, -48, 4, colGrip);
          for (float gu = -46; gu <= -26; gu += 4.5f) {
            spr->drawLine(toX(gu, -4), toY(gu, -4), toX(gu + 2, 4), toY(gu + 2, 4), colCyan);
          }

          // 7. Quả táo đuôi Pommel & Ngọc Lam Bảo
          drawTiltedQuad(-58, -8, -50, -8, -50, 8, -58, 8, colCyan);
          drawTiltedQuad(-56, -4, -52, -4, -52, 4, -56, 4, colAura);
        }
        break;

      case 13: // Huyết Kiếm Muramasa
        // Lưỡi katana cong vát 3D Huyết Nguyệt
        spr->fillTriangle(cx - 2, cy - 56, cx - 6, cy + 20, cx, cy + 20, 0xF800);
        spr->fillTriangle(cx - 2, cy - 56, cx, cy + 20, cx + 5, cy + 20, 0x8000);
        spr->drawLine(cx, cy - 50, cx, cy + 18, 0xFC00);

        // Tsuba tròn vàng + Cán kiếm quấn dây đen Ito
        spr->fillCircle(cx, cy + 22, 10, 0xC618);
        spr->fillRect(cx - 4, cy + 24, 8, 26, TFT_BLACK);
        for (int y = 26; y <= 46; y += 5) spr->drawFastHLine(cx - 3, cy + y, 6, 0xFA60);

        // Vệt chém huyết ảnh xoay quanh lưỡi kiếm
        spr->drawArc(cx, cy - 16, 28, 30, 200, 340, 0xF800);
        break;

      case 14: // Cyberpunk Thermal Katana (3000°C Plasma)
        // Lưỡi kiếm sợi Carbon đen bóng + Cạnh nhiệt Plasma phát quang
        spr->fillRect(cx - 5, cy - 54, 6, 74, 0x10A2);
        spr->drawFastVLine(cx + 1, cy - 52, 70, TFT_CYAN);
        spr->drawFastVLine(cx + 2, cy - 50, 66, 0xFD14);
        spr->fillRect(cx - 14, cy + 20, 28, 8, 0x2945);
        spr->fillRect(cx - 4, cy + 28, 8, 24, 0x18C3);
        break;

      case 15: // Plasma Buster Cannon
        // Khẩu pháo năng lượng hạng nặng 2 nòng Isometric
        spr->fillRoundRect(cx - 24, cy - 24, 48, 44, 6, 0x2124);
        spr->drawRoundRect(cx - 24, cy - 24, 48, 44, 6, 0x4A69);
        spr->fillRect(cx - 16, cy - 46, 12, 24, 0x3186);
        spr->fillRect(cx + 4, cy - 46, 12, 24, 0x3186);

        // Lõi sạc Plasma phát sáng ở tâm pháo
        spr->fillCircle(cx, cy - 2, 14 + (int)(breath * 4), 0x07FF);
        spr->fillCircle(cx, cy - 2, 7, TFT_WHITE);
        break;

      case 16: // Frostmourne Rune Blade (Tử Khí Băng Giá)
        // Lưỡi kiếm runic băng khắc chữ cổ
        spr->fillTriangle(cx, cy - 56, cx - 8, cy + 18, cx, cy + 18, 0xDEFB);
        spr->fillTriangle(cx, cy - 56, cx, cy + 18, cx + 8, cy + 18, 0x4A69);
        for (int y = -36; y <= 8; y += 12) spr->drawPixel(cx, cy + y, 0x07FF);

        // Đầu lâu Ram Skull ở cán kiếm
        spr->fillRoundRect(cx - 16, cy + 18, 32, 14, 4, 0x6B4D);
        spr->fillCircle(cx - 6, cy + 24, 2, 0x07FF);
        spr->fillCircle(cx + 6, cy + 24, 2, 0x07FF);
        spr->fillRect(cx - 4, cy + 32, 8, 22, 0x18C3);
        break;

      case 17: // Búa Sấm Sét Mjolnir (Asgardian Uru Metal)
        // Đầu búa Isometric đúc kim loại Uru
        spr->fillRoundRect(cx - 28, cy - 38, 56, 36, 6, 0x7BEF);
        spr->drawRoundRect(cx - 28, cy - 38, 56, 36, 6, 0x4A69);
        spr->drawRect(cx - 22, cy - 32, 44, 24, 0x9CD3);

        // Cán búa quấn dây da nâu + Vòng cổ tay
        spr->fillRect(cx - 5, cy - 2, 10, 44, 0x8A22);
        spr->drawCircle(cx, cy + 44, 4, 0x8A22);

        // Tia sét điện quang nứt nẻ từ các góc búa
        spr->drawLine(cx - 28, cy - 38, cx - 40, cy - 52, TFT_CYAN);
        spr->drawLine(cx + 28, cy - 38, cx + 38, cy - 48, TFT_WHITE);
        break;

      case 18: // Hắc Kiếm Darksaber (Mandalorian Beskar)
        // Lưỡi kiếm đen tuyền góc cạnh + Vầng hào quang trắng rung động
        spr->fillTriangle(cx, cy - 58, cx - 6, cy + 20, cx + 6, cy + 20, TFT_BLACK);
        spr->drawLine(cx, cy - 58, cx - 6, cy + 20, TFT_WHITE);
        spr->drawLine(cx, cy - 58, cx + 6, cy + 20, TFT_WHITE);
        spr->drawLine(cx, cy - 58, cx, cy + 20, 0xCE59);

        // Chuôi kiếm hình chữ nhật Beskar truyền thống
        spr->fillRect(cx - 8, cy + 20, 16, 28, 0x7BEF);
        spr->drawRect(cx - 8, cy + 20, 16, 28, 0x18C3);
        break;

      case 19: // Song Đao Năng Lượng Laser (Dual Blades)
        // Hai thanh đao chéo góc chữ X tỏa hào quang Cyan & Magenta
        spr->drawLine(cx - 38, cy - 38, cx + 38, cy + 38, TFT_CYAN);
        spr->drawLine(cx - 37, cy - 38, cx + 39, cy + 38, TFT_WHITE);
        spr->drawLine(cx - 38, cy + 38, cx + 38, cy - 38, 0xF81F);
        spr->drawLine(cx - 37, cy + 38, cx + 39, cy - 38, TFT_WHITE);
        spr->fillCircle(cx, cy, 7, 0x18C3);
        break;

      case 20: // Lưỡi Hái Tử Thần Reaper (Soul Harvest)
        // Cán dài kim loại hắc ám
        spr->drawLine(cx, cy - 54, cx, cy + 50, 0x3186);
        spr->drawLine(cx + 1, cy - 54, cx + 1, cy + 50, 0x528A);

        // Lưỡi hái cong hình trăng khuyết tím phát sáng
        spr->drawArc(cx - 4, cy - 16, 36, 42, 220, 360, 0x981F);
        spr->drawArc(cx - 4, cy - 16, 38, 40, 220, 360, TFT_WHITE);
        spr->fillCircle(cx - 32, cy - 32, 4, 0x07FF);
        break;

      case 21: // Laser Railgun Sniper (Ngắm Bắn Chính Xác)
        // Thân súng bắn tỉa công nghệ cao + Vòng gia tốc từ trường
        spr->fillRect(cx - 34, cy - 14, 68, 20, 0x18C3);
        spr->drawRect(cx - 34, cy - 14, 68, 20, TFT_CYAN);
        for (int x = -24; x <= 24; x += 16) {
          spr->drawCircle(cx + x, cy - 4, 9, TFT_CYAN);
        }
        // Tâm ngắm hồng ngoại Laser Scope
        spr->drawCircle(cx + 28, cy - 4, 5, TFT_RED);
        spr->drawFastHLine(cx + 20, cy - 4, 16, TFT_RED);
        break;

      // =========================================================================
      // 3. TÌNH YÊU & BLING (22..31) - FACETED GEMS & LUXURY ROMANCE
      // =========================================================================

      case 22: // Trái Tim Pha Lê Diamond (8 Mặt Cắt Phản Chiếu)
        {
          int s = 34 + (int)(breath * 8.0f);
          spr->fillCircle(cx - s/2, cy - s/3, s/2, 0xF800);
          spr->fillCircle(cx + s/2, cy - s/3, s/2, 0xF800);
          spr->fillTriangle(cx - s + 4, cy - s/4, cx + s - 4, cy - s/4, cx, cy + s, 0xF800);

          spr->drawLine(cx, cy - s/3, cx - s/2, cy + s/3, 0xFCAE);
          spr->drawLine(cx, cy - s/3, cx + s/2, cy + s/3, 0xFCAE);
          spr->drawLine(cx, cy - s/3, cx, cy + s, 0xFFFF);
          spr->drawLine(cx - s/2, cy - s/3, cx, cy - s/3, 0xFFFF);
          spr->drawLine(cx + s/2, cy - s/3, cx, cy - s/3, 0xFFFF);
          spr->drawPixel(cx - s/2 - 2, cy - s/3 - 4, TFT_WHITE);
        }
        break;

      case 23: // Song Tâm Lồng Nhau (Dual Hearts Interlocked)
        spr->fillCircle(cx - 16, cy - 8, 14, 0x07FF);
        spr->fillTriangle(cx - 30, cy - 6, cx - 2, cy - 6, cx - 16, cy + 18, 0x07FF);
        spr->fillCircle(cx + 16, cy + 4, 14, 0xF81F);
        spr->fillTriangle(cx + 2, cy + 6, cx + 30, cy + 6, cx + 16, cy + 30, 0xF81F);
        spr->drawPixel(cx, cy + 2, TFT_WHITE);
        break;

      case 24: // Nhịp Tim Điện Tâm Đồ ECG (Live Heartbeat Wave)
        for (int y = -24; y <= 24; y += 12) spr->drawFastHLine(cx - 42, cy + y, 84, 0x0180);
        spr->drawLine(cx - 42, cy, cx - 18, cy, 0x07E0);
        spr->drawLine(cx - 18, cy, cx - 10, cy - 30, 0x07E0);
        spr->drawLine(cx - 10, cy - 30, cx, cy + 32, TFT_WHITE);
        spr->drawLine(cx, cy + 32, cx + 10, cy - 16, 0x07E0);
        spr->drawLine(cx + 10, cy - 16, cx + 42, cy, 0x07E0);
        spr->fillCircle(cx, cy + 32, 3, TFT_RED);
        break;

      case 25: // Thư Tình Có Cánh (Winged Love Letter)
        spr->fillRoundRect(cx - 24, cy - 14, 48, 30, 4, 0xFFF2);
        spr->drawRoundRect(cx - 24, cy - 14, 48, 30, 4, 0xCE59);
        spr->drawLine(cx - 24, cy - 14, cx, cy + 2, 0xCE59);
        spr->drawLine(cx + 24, cy - 14, cx, cy + 2, 0xCE59);
        spr->fillCircle(cx, cy + 2, 5, TFT_RED);

        {
          int wy = (int)(sin(angle * 4.0f) * 6.0f);
          spr->drawArc(cx - 28, cy - 8 + wy, 16, 20, 160, 320, TFT_WHITE);
          spr->drawArc(cx + 28, cy - 8 + wy, 16, 20, 220, 380, TFT_WHITE);
        }
        break;

      case 26: // Biểu Tượng Vô Cực Infinity (Endless Love)
        spr->drawCircle(cx - 20, cy, 20, 0x07FF);
        spr->drawCircle(cx + 20, cy, 20, 0xF81F);
        spr->drawCircle(cx - 20, cy, 18, TFT_WHITE);
        spr->drawCircle(cx + 20, cy, 18, TFT_WHITE);
        {
          int lx = cx + (int)(cos(angle * 2.0f) * 20.0f) * ((sin(angle * 2.0f) > 0) ? 1 : -1);
          int ly = cy + (int)(sin(angle * 2.0f) * 16.0f);
          spr->fillCircle(lx, ly, 3, TFT_YELLOW);
        }
        break;

      case 27: // Hoa Hồng Pha Lê (Crystal Rose)
        spr->fillCircle(cx, cy - 12, 18, 0xF800);
        spr->drawCircle(cx, cy - 12, 14, 0xFC00);
        spr->fillCircle(cx - 8, cy + 2, 10, 0xD800);
        spr->fillCircle(cx + 8, cy + 2, 10, 0xD800);
        spr->drawPixel(cx - 4, cy - 16, TFT_WHITE);

        spr->fillRect(cx - 3, cy + 12, 6, 32, 0x05E0);
        spr->fillTriangle(cx - 3, cy + 20, cx - 14, cy + 16, cx - 3, cy + 26, 0x07E0);
        spr->fillTriangle(cx + 3, cy + 26, cx + 14, cy + 22, cx + 3, cy + 32, 0x07E0);
        break;

      case 28: // Mũi Tên Thần Cupid (Star Trail Arrow)
        spr->fillCircle(cx - 10, cy - 6, 12, 0xF81F);
        spr->fillCircle(cx + 10, cy - 6, 12, 0xF81F);
        spr->fillTriangle(cx - 22, cy - 4, cx + 22, cy - 4, cx, cy + 20, 0xF81F);

        spr->drawLine(cx - 38, cy - 38, cx + 38, cy + 38, TFT_YELLOW);
        spr->drawLine(cx - 37, cy - 38, cx + 39, cy + 38, TFT_WHITE);
        spr->fillTriangle(cx + 38, cy + 38, cx + 28, cy + 36, cx + 36, cy + 28, TFT_YELLOW);
        break;

      case 29: // Chòm Sao Đôi Tình Nhân (Lovers Constellation)
        {
          int pts[6][2] = {{-30, -20}, {-10, -32}, {16, -26}, {32, -8}, {10, 14}, {-18, 18}};
          for (int i = 0; i < 5; i++) {
            spr->drawLine(cx + pts[i][0], cy + pts[i][1], cx + pts[i+1][0], cy + pts[i+1][1], 0x4A69);
          }
          spr->drawLine(cx + pts[5][0], cy + pts[5][1], cx + pts[0][0], cy + pts[0][1], 0x4A69);
          for (int i = 0; i < 6; i++) {
            spr->fillCircle(cx + pts[i][0], cy + pts[i][1], 3, TFT_YELLOW);
            spr->drawPixel(cx + pts[i][0], cy + pts[i][1], TFT_WHITE);
          }
        }
        break;

      case 30: // Đống Lửa Trại Ấm Áp (Cozy Campfire)
        spr->fillRect(cx - 26, cy + 18, 52, 10, 0x8A22);
        spr->fillRect(cx - 20, cy + 22, 40, 8, 0x5140);
        {
          int fy = (int)(sin(angle * 6.0f) * 4.0f);
          spr->fillTriangle(cx - 20, cy + 18, cx + 20, cy + 18, cx, cy - 32 + fy, 0xF800);
          spr->fillTriangle(cx - 14, cy + 18, cx + 14, cy + 18, cx, cy - 22 + fy, 0xFA60);
          spr->fillTriangle(cx - 8, cy + 18, cx + 8, cy + 18, cx, cy - 12 + fy, TFT_YELLOW);
          spr->drawPixel(cx - 4, cy - 38 + fy, TFT_YELLOW);
          spr->drawPixel(cx + 8, cy - 44 + fy, 0xFA60);
        }
        break;

      case 31: // Bình Thuốc Tình Yêu Magic (Love Potion)
        spr->fillCircle(cx, cy + 6, 22, 0x2945);
        spr->fillCircle(cx, cy + 6, 18, 0xF81F);
        spr->fillRect(cx - 8, cy - 24, 16, 12, 0x2945);
        spr->fillRect(cx - 6, cy - 30, 12, 8, 0x8A22);
        spr->fillCircle(cx - 4, cy + 2 + (int)(sin(angle * 3) * 6), 3, TFT_WHITE);
        spr->fillCircle(cx + 6, cy - 8 + (int)(cos(angle * 3) * 6), 2, TFT_WHITE);
        break;

      // =========================================================================
      // 4. THÚ CƯNG VŨ TRỤ (32..41) - KAWAII PIXEL PETS & INTERACTION
      // =========================================================================

      case 32: // Mèo Con Cuộn Tròn 2.5D (Cosmic Sleeping Kitty)
        {
          bool blink = ((millis() % 3500) >= 3350);
          float tailWave = sinf(angle * 3.5f) * 6.0f;
          float earTwitch = sinf(angle * 7.0f) * 2.0f;

          // Đuôi ngoáy nhịp nhàng phía sau
          spr->drawArc(cx + 18, cy + 8, 14, 16, 260 + (int)tailWave, 360 + (int)tailWave, 0xED80);
          spr->fillCircle(cx + 18 + (int)(cosf((360+tailWave)*0.0174f)*15.0f), 
                          cy + 8 + (int)(sinf((360+tailWave)*0.0174f)*15.0f), 3, TFT_WHITE);

          // Khối thân cuộn tròn ngủ 2.5D (Shadow -> Midtone -> Highlight)
          spr->fillCircle(cx, cy + 4, 24, 0x8B00); // Shadow viền
          spr->fillCircle(cx, cy + 3, 23, 0xED80); // Midtone cam vàng
          spr->fillCircle(cx - 4, cy, 15, 0xFFA0);  // Highlight lưng

          // Tai mèo vẫy nghe ngóng
          spr->fillTriangle(cx - 18, cy - 14, cx - 12 + (int)earTwitch, cy - 28, cx - 4, cy - 14, 0xED80);
          spr->fillTriangle(cx - 16, cy - 14, cx - 12 + (int)earTwitch, cy - 25, cx - 6, cy - 14, 0xFBAE);

          spr->fillTriangle(cx + 4, cy - 14, cx + 12 - (int)earTwitch, cy - 28, cx + 18, cy - 14, 0xED80);
          spr->fillTriangle(cx + 6, cy - 14, cx + 12 - (int)earTwitch, cy - 25, cx + 16, cy - 14, 0xFBAE);

          // Mặt bầu bĩnh
          spr->fillCircle(cx - 12, cy + 2, 11, 0xED80);
          spr->fillCircle(cx - 12, cy + 5, 8, TFT_WHITE);

          // Mắt nhắm ngủ hoặc chớp nhẹ
          if (blink) {
            spr->fillCircle(cx - 14, cy - 1, 3, TFT_BLACK);
          } else {
            spr->drawArc(cx - 14, cy - 1, 4, 3, 180, 360, 0x3000);
          }

          // Mũi và ria mép
          spr->fillTriangle(cx - 19, cy + 2, cx - 17, cy + 2, cx - 18, cy + 4, 0xFBAE);
          spr->drawFastHLine(cx - 24, cy + 1, 4, 0x8B00);
          spr->drawFastHLine(cx - 24, cy + 4, 4, 0x8B00);
        }
        break;

      case 33: // Cún Cyber Shiba Inu 2.5D Volumetric
        {
          bool blink = ((millis() % 3500) >= 3350);
          float tailWave = sinf(angle * 6.0f) * 4.0f;

          // Đuôi cuộn ngoáy tít
          spr->drawArc(cx + 22, cy - 4, 8, 10, 0, 240, 0xFDB0);
          spr->fillCircle(cx + 26 + (int)tailWave, cy - 6, 4, TFT_WHITE);

          // Thân và đầu 2.5D
          spr->fillRoundRect(cx - 24, cy - 18, 48, 36, 12, 0xC440); // Shadow
          spr->fillRoundRect(cx - 23, cy - 19, 46, 35, 11, 0xFDB0); // Midtone vàng cam Shiba
          spr->fillRoundRect(cx - 16, cy - 2, 32, 18, 6, TFT_WHITE); // Bụng & má trắng

          // Tai tam giác vẫy
          spr->fillTriangle(cx - 22, cy - 18, cx - 16, cy - 34, cx - 8, cy - 18, 0xFDB0);
          spr->fillTriangle(cx - 20, cy - 18, cx - 16, cy - 31, cx - 10, cy - 18, 0xFBAE);
          spr->fillTriangle(cx + 8, cy - 18, cx + 16, cy - 34, cx + 22, cy - 18, 0xFDB0);
          spr->fillTriangle(cx + 10, cy - 18, cx + 16, cy - 31, cx + 20, cy - 18, 0xFBAE);

          // Kính visor Cyber phát sáng
          spr->fillRoundRect(cx - 18, cy - 8, 36, 8, 3, TFT_CYAN);
          spr->drawFastHLine(cx - 16, cy - 5, 32, TFT_WHITE);

          // Mũi đen nhỏ xinh
          spr->fillCircle(cx, cy + 4, 2, TFT_BLACK);
        }
        break;

      case 34: // Kỳ Nhông Axolotl 2.5D Volumetric Glow
        {
          bool blink = ((millis() % 3500) >= 3350);
          float wave = sinf(angle * 4.0f);
          float tailW = sinf(angle * 3.0f);

          // 1. Đuôi uốn lượn 2.5D phía sau
          int tx = cx + (int)(tailW * 10.0f);
          spr->fillTriangle(cx - 8, cy + 10, cx + 8, cy + 10, tx, cy + 34, 0xFD15);
          spr->fillTriangle(cx - 4, cy + 10, cx + 4, cy + 10, tx, cy + 32, 0xFBAE);

          // 2. Thân tròn mịn 2.5D với 3 dải màu Volumetric (Shadow -> Midtone -> Highlight)
          spr->fillRoundRect(cx - 24, cy - 18, 48, 36, 14, 0xC26E); // Shadow viền dưới
          spr->fillRoundRect(cx - 23, cy - 20, 46, 35, 13, 0xFBAE); // Midtone hồng phấn
          spr->fillRoundRect(cx - 18, cy - 22, 36, 18, 9, 0xFF75);  // Highlight đỉnh đầu

          // 3. 3 Nhánh mang xòe mềm mại cử động nhịp nhàng mỗi bên (Gills waving)
          for (int g = 0; g < 3; g++) {
            float gAngle = wave + g * 0.5f;
            int gxL = cx - 24 - (int)(cosf(gAngle) * 8.0f);
            int gyL = cy - 14 + g * 8 + (int)(sinf(gAngle) * 4.0f);
            spr->fillCircle(gxL, gyL, 5 - g, 0xF81F);
            spr->fillCircle(gxL + 2, gyL, 3, 0xFD15);

            int gxR = cx + 24 + (int)(cosf(gAngle) * 8.0f);
            int gyR = cy - 14 + g * 8 + (int)(sinf(gAngle) * 4.0f);
            spr->fillCircle(gxR, gyR, 5 - g, 0xF81F);
            spr->fillCircle(gxR - 2, gyR, 3, 0xFD15);
          }

          // 4. Bụng mềm màu kem pastel
          spr->fillRoundRect(cx - 14, cy - 2, 28, 16, 7, 0xFFF8);

          // 5. Mắt long lanh có hạt phản quang & nhịp chớp mắt sinh học (Blink cycle 3.5s)
          if (blink) {
            spr->drawFastHLine(cx - 14, cy - 8, 8, 0x3000);
            spr->drawFastHLine(cx + 6, cy - 8, 8, 0x3000);
          } else {
            spr->fillCircle(cx - 10, cy - 8, 5, TFT_BLACK);
            spr->fillCircle(cx - 11, cy - 10, 2, TFT_WHITE);
            spr->drawPixel(cx - 8, cy - 6, TFT_WHITE);

            spr->fillCircle(cx + 10, cy - 8, 5, TFT_BLACK);
            spr->fillCircle(cx + 9, cy - 10, 2, TFT_WHITE);
            spr->drawPixel(cx + 12, cy - 6, TFT_WHITE);
          }

          // 6. Má hồng phấn thẹn thùng & Miệng cười chúm chím
          spr->fillCircle(cx - 16, cy - 1, 3, 0xF81F);
          spr->fillCircle(cx + 16, cy - 1, 3, 0xF81F);
          spr->drawArc(cx, cy - 2, 4, 3, 0, 180, 0x8000);

          // 7. Chân bơi chèo nhỏ nhắn
          spr->fillCircle(cx - 16, cy + 14, 4, 0xFBAE);
          spr->fillCircle(cx + 16, cy + 14, 4, 0xFBAE);
        }
        break;

      case 35: // Thỏ Ngọc Cung Trăng (Moon Rabbit)
        spr->fillCircle(cx + 12, cy - 10, 26, TFT_YELLOW);
        spr->fillCircle(cx + 6, cy - 14, 24, TFT_BLACK);
        spr->fillRoundRect(cx - 20, cy - 10, 32, 28, 7, TFT_WHITE);
        spr->fillRoundRect(cx - 16, cy - 38, 8, 30, 4, TFT_WHITE);
        spr->fillRoundRect(cx - 4, cy - 38, 8, 30, 4, TFT_WHITE);
        spr->fillRect(cx - 14, cy - 34, 4, 22, 0xFCAE);
        spr->fillRect(cx - 2, cy - 34, 4, 22, 0xFCAE);
        spr->fillCircle(cx - 12, cy - 2, 2, 0xF800);
        break;

      case 36: // Pixel Corgi Tung Tăng (Heart Butt Corgi)
        spr->fillCircle(cx - 14, cy, 18, 0xFDB0);
        spr->fillCircle(cx + 14, cy, 18, 0xFDB0);
        spr->fillCircle(cx - 8, cy + 4, 10, TFT_WHITE);
        spr->fillCircle(cx + 8, cy + 4, 10, TFT_WHITE);
        spr->fillCircle(cx, cy - 8 + (int)(sin(angle * 10) * 3), 4, 0xFDB0);
        spr->fillCircle(cx, cy - 22, 5, TFT_RED);
        break;

      case 37: // Ma Nhỏ Cute Boo Spook
        {
          int my = cy + (int)(sin(angle * 3) * 6);
          spr->fillRoundRect(cx - 20, my - 24, 40, 42, 10, TFT_WHITE);
          for (int x = -16; x <= 16; x += 8) {
            spr->fillCircle(cx + x, my + 18, 4, TFT_WHITE);
          }
          spr->fillCircle(cx - 8, my - 6, 4, TFT_BLACK);
          spr->fillCircle(cx + 8, my - 6, 4, TFT_BLACK);
          spr->drawPixel(cx - 7, my - 7, TFT_WHITE);
          spr->drawPixel(cx + 9, my - 7, TFT_WHITE);
          spr->fillCircle(cx - 12, my, 3, 0xFCAE);
          spr->fillCircle(cx + 12, my, 3, 0xFCAE);
        }
        break;

      case 38: // Rồng Con Thở Lửa (Baby Dragon)
        spr->fillRoundRect(cx - 20, cy - 16, 40, 36, 8, 0x05E0);
        spr->fillTriangle(cx - 18, cy - 16, cx - 12, cy - 30, cx - 6, cy - 16, 0x07E0);
        spr->fillTriangle(cx + 6, cy - 16, cx + 12, cy - 30, cx + 18, cy - 16, 0x07E0);
        {
          int fx = cx + 22 + (int)(sin(angle * 6) * 4);
          spr->fillCircle(fx, cy - 4, 6, 0xFA60);
          spr->fillCircle(fx + 6, cy - 4, 4, TFT_YELLOW);
        }
        break;

      case 39: // Chuột Hamster Phi Hành Gia (Space Hamster)
        spr->drawCircle(cx, cy, 30, 0x07FF);
        spr->fillCircle(cx, cy + 2, 22, 0xED80);
        spr->fillCircle(cx - 16, cy + 8, 9, 0xFA80);
        spr->fillCircle(cx + 16, cy + 8, 9, 0xFA80);
        spr->fillCircle(cx - 7, cy, 3, TFT_BLACK);
        spr->fillCircle(cx + 7, cy, 3, TFT_BLACK);
        break;

      case 40: // Gấu Trúc Đỏ Cyber Red Panda
        spr->fillRoundRect(cx - 24, cy - 20, 48, 38, 8, 0xFA60);
        spr->fillRoundRect(cx - 16, cy - 4, 32, 20, 6, TFT_WHITE);
        spr->fillCircle(cx - 22, cy - 24, 8, 0x8080);
        spr->fillCircle(cx + 22, cy - 24, 8, 0x8080);
        spr->fillRoundRect(cx - 26, cy + 12, 52, 12, 4, 0x8A22);
        for (int x = -20; x <= 20; x += 12) spr->drawFastVLine(cx + x, cy + 12, 12, 0xFA60);
        break;

      case 41: // Cáo Sao Say Giấc Star Fox
        spr->fillCircle(cx, cy, 26, 0xFA60);
        spr->fillCircle(cx + 10, cy, 18, 0x8A22);
        spr->drawArc(cx - 10, cy - 2, 6, 4, 0, 180, TFT_BLACK);
        spr->drawArc(cx + 6, cy - 2, 6, 4, 0, 180, TFT_BLACK);
        spr->fillCircle(cx, cy - 32, 4, TFT_YELLOW);
        break;

      // =========================================================================
      // 5. GAME & SCI-FI HUD (42..49) - PROCEDURAL SCI-FI RETRO GIZMOS
      // =========================================================================

      case 42: // Lò Phản Ứng Arc Reactor 3000 (Iron Man)
        spr->drawCircle(cx, cy, 34, 0x7BEF);
        spr->drawCircle(cx, cy, 32, TFT_CYAN);
        spr->drawCircle(cx, cy, 22, 0x07FF);
        for (int i = 0; i < 10; i++) {
          float a = i * 0.628f + angle;
          int bx = cx + (int)(cos(a) * 27.0f);
          int by = cy + (int)(sin(a) * 27.0f);
          spr->fillCircle(bx, by, 3, 0x8A22);
        }
        spr->fillCircle(cx, cy, 12 + (int)(breath * 3), TFT_WHITE);
        spr->drawCircle(cx, cy, 14 + (int)(breath * 3), TFT_CYAN);
        break;

      case 43: // Cyberpunk Radar HUD (Quét Mục Tiêu)
        spr->drawCircle(cx, cy, 36, 0x07E0);
        spr->drawCircle(cx, cy, 24, 0x05E0);
        spr->drawCircle(cx, cy, 12, 0x03E0);
        spr->drawFastHLine(cx - 36, cy, 72, 0x03E0);
        spr->drawFastVLine(cx, cy - 36, 72, 0x03E0);
        {
          int rx = cx + (int)(cos(angle * 2.5f) * 36.0f);
          int ry = cy + (int)(sin(angle * 2.5f) * 36.0f);
          spr->drawLine(cx, cy, rx, ry, TFT_WHITE);
          spr->fillCircle(cx + 14, cy - 16, 3, TFT_RED);
          spr->drawCircle(cx + 14, cy - 16, 6, TFT_RED);
        }
        break;

      case 44: // Máy Game Boy Cổ Điển (Retro Handheld)
        spr->fillRoundRect(cx - 26, cy - 42, 52, 84, 8, 0xCE59);
        spr->drawRoundRect(cx - 26, cy - 42, 52, 84, 8, 0x7BEF);
        spr->fillRect(cx - 20, cy - 34, 40, 36, 0x8640);
        spr->fillRect(cx - 16, cy - 30, 32, 28, 0x9EC0);
        spr->drawRect(cx - 10, cy - 20, 20, 10, 0x3340);
        spr->fillRect(cx - 18, cy + 14, 14, 5, TFT_BLACK);
        spr->fillRect(cx - 14, cy + 10, 5, 14, TFT_BLACK);
        spr->fillCircle(cx + 10, cy + 20, 4, 0x8000);
        spr->fillCircle(cx + 18, cy + 14, 4, 0x8000);
        break;

      case 45: // Bình Máu Pixel 8-Bit Zelda (Health Potion)
        spr->fillRect(cx - 18, cy - 12, 36, 44, TFT_BLACK);
        spr->fillRect(cx - 14, cy - 8, 28, 38, 0xF800);
        spr->fillRect(cx - 8, cy - 24, 16, 12, TFT_BLACK);
        spr->fillRect(cx - 4, cy - 22, 8, 10, 0xCE59);
        spr->drawFastVLine(cx - 10, cy - 4, 28, TFT_WHITE);
        spr->drawFastVLine(cx - 8, cy - 4, 28, TFT_WHITE);
        break;

      case 46: // Băng Cát-sét Synthwave (80s Neon Tape)
        spr->fillRoundRect(cx - 36, cy - 22, 72, 44, 4, 0x18C3);
        spr->drawRoundRect(cx - 36, cy - 22, 72, 44, 4, 0xF81F);
        spr->fillRect(cx - 28, cy - 16, 56, 24, 0xFA60);
        spr->fillCircle(cx - 14, cy - 4, 7, TFT_WHITE);
        spr->fillCircle(cx + 14, cy - 4, 7, TFT_WHITE);
        spr->fillCircle(cx - 14, cy - 4, 3, TFT_BLACK);
        spr->fillCircle(cx + 14, cy - 4, 3, TFT_BLACK);
        break;

      case 47: // Đầu Lâu Glitch Hologram (Cyber Skull)
        spr->drawCircle(cx, cy - 10, 22, TFT_CYAN);
        spr->fillRect(cx - 12, cy + 8, 24, 14, TFT_BLACK);
        spr->drawRect(cx - 12, cy + 8, 24, 14, TFT_CYAN);
        spr->fillCircle(cx - 8, cy - 8, 5, TFT_CYAN);
        spr->fillCircle(cx + 8, cy - 8, 5, TFT_CYAN);
        for (int y = -28; y <= 28; y += 8) {
          int offset = (int)(sin(angle * 8 + y) * 4);
          spr->drawFastHLine(cx - 30 + offset, cy + y, 60, 0x07FF);
        }
        break;

      case 48: // Cơn Mưa Ký Tự Matrix Code Rain
        for (int col = 0; col < 7; col++) {
          int px = cx - 36 + col * 12;
          for (int row = 0; row < 6; row++) {
            int py = cy - 36 + ((row * 14 + (int)(angle * 20.0f + col * 15)) % 80);
            uint16_t clr = (row == 5) ? TFT_WHITE : (row > 3 ? 0x07E0 : 0x03E0);
            spr->drawRect(px, py, 4, 6, clr);
          }
        }
        break;

      case 49: // Lõi Lượng Tử Quantum Core (3 Trục Gyro)
        spr->drawCircle(cx, cy, 34, 0x981F);
        spr->drawEllipse(cx, cy, 30, 16 + (int)(sin(angle * 2) * 10), 0x07FF);
        spr->drawEllipse(cx, cy, 16 + (int)(cos(angle * 2) * 10), 30, TFT_YELLOW);
        spr->fillCircle(cx, cy, 8 + (int)(breath * 4), TFT_WHITE);
        spr->drawCircle(cx, cy, 10 + (int)(breath * 4), 0xF81F);
        break;

      // =========================================================================
      // NHÓM 2: 50 THÁNH KHÍ & VŨ KHÍ THẦN THOẠI (ID 50..99)
      // =========================================================================
      default: {
        if (id >= 50 && id < 100) {
          int sub = (id - 50);
          if (sub < 20) {
            // 50-69: CÁC THÁNH KIẾM (Excalibur, Clarent, Dáinsleif, Gram, Spitfire, Caladbolg...)
            // Lưỡi kiếm nghiêng 45 độ phong cách anh hùng
            int bx = cx - 18, by = cy - 24;
            // Vòng hào quang phát sáng
            spr->drawCircle(cx, cy - 6, 28 + (int)(breath * 3), 0x07FF);
            // Lưỡi kiếm bạc sáng bóng
            spr->fillTriangle(bx, by, bx + 36, by - 36, bx + 12, by + 12, 0xFFFF);
            spr->fillTriangle(bx + 36, by - 36, bx + 42, by - 30, bx + 12, by + 12, 0xCE7F);
            // Rãnh rune phát quang xanh/vàng chạy dọc lưỡi kiếm
            uint16_t runeCol = (sub % 2 == 0) ? 0x07FF : 0xFDE0;
            spr->drawLine(bx + 4, by - 4, bx + 32, by - 32, runeCol);
            // Đốc kiếm & chuôi vàng Kinpaku
            spr->fillRoundRect(bx - 6, by + 10, 18, 6, 2, 0xFDE0);
            spr->fillRect(bx - 12, by + 16, 8, 14, 0x2124);
            spr->fillCircle(bx - 14, by + 32, 4, 0xFDE0); // Viên ngọc chuôi
            // Hạt hào quang lấp lánh chạy dọc lưỡi
            int sh = (int)(angle * 15.0f) % 35;
            spr->drawPixel(bx + sh, by - sh, 0xFFFF);
          } else if (sub < 30) {
            // 70-79: CÁC THẦN CUNG (Fail-Not, Gandiva, Pinaka, Cung Mặt Trời, Cung Mặt Trăng...)
            // Cánh cung uốn lượn đôi cánh vàng/bạc
            spr->drawEllipse(cx, cy, 14, 38, 0xFDE0);
            spr->drawEllipse(cx - 2, cy, 12, 36, 0xD6BA);
            // Dây cung năng lượng photon
            spr->drawLine(cx - 10, cy - 36, cx - 10, cy + 36, 0xFFFF);
            // Mũi tên ánh sáng đang giương cung
            spr->drawLine(cx - 24, cy, cx + 24, cy, 0x07FF);
            spr->fillTriangle(cx + 24, cy, cx + 18, cy - 4, cx + 18, cy + 4, 0x07FF); // Đầu tên
            spr->drawCircle(cx, cy, 8 + (int)(breath * 3), 0x07FF); // Vầng tụ năng
          } else if (sub < 40) {
            // 80-89: CÁC THẦN THƯƠNG & GIÁO (Gungnir, Rhongomyniad, Gáe Bulg, Longinus...)
            // Cán giáo dài bằng thép đen viền vàng
            spr->drawLine(cx - 30, cy + 30, cx + 30, cy - 30, 0x52AA);
            // Mũi thương bản rộng thần thoại
            spr->fillTriangle(cx + 18, cy - 18, cx + 38, cy - 38, cx + 28, cy - 16, 0xFFFF);
            spr->fillTriangle(cx + 18, cy - 18, cx + 38, cy - 38, cx + 16, cy - 28, 0x07FF);
            // Dải lụa đỏ bay phấp phới ở cổ giáo
            int fy = (int)(sinf(angle * 4.0f) * 4.0f);
            spr->fillTriangle(cx + 16, cy - 16, cx + 10, cy - 10 + fy, cx + 12, cy - 4, 0xF800);
          } else if (sub < 45) {
            // 90-94: KHIÊN THẦN (Aegis, Svalinn, Ancile, Gương Bát Chỉ...)
            // Thân khiên hình thoi kim loại cổ đại viền vàng
            spr->fillRoundRect(cx - 22, cy - 26, 44, 52, 10, 0x2145);
            spr->drawRoundRect(cx - 22, cy - 26, 44, 52, 10, 0xFDE0);
            spr->drawRoundRect(cx - 18, cy - 22, 36, 44, 8, 0x07FF);
            // Biểu tượng mặt trời/rồng ở trung tâm
            spr->fillCircle(cx, cy, 10, 0xFDE0);
            spr->drawCircle(cx, cy, 8, 0xF800);
            // Trường lực phòng hộ phát quang
            spr->drawCircle(cx, cy, 32 + (int)(breath * 4), 0x07FF);
          } else {
            // 95-99: THÁNH TÍCH (Chén Thánh San Greal, Hòm Bia Giao Ước, Hòn Đá Triết Gia...)
            // Chén Thánh mạ vàng lộng lẫy
            spr->fillRoundRect(cx - 16, cy - 16, 32, 20, 6, 0xFDE0);
            spr->fillRect(cx - 4, cy + 4, 8, 16, 0xFDE0); // Chân chén
            spr->fillRoundRect(cx - 14, cy + 20, 28, 6, 2, 0xFDE0); // Đế chén
            // Rượu vang thánh thần phát quang đỏ ruby bên trong
            spr->fillRoundRect(cx - 12, cy - 14, 24, 10, 3, 0xF800);
            // Hào quang thánh tích tỏa sáng lên trên
            for (int r = 0; r < 4; r++) {
              int ry = cy - 22 - r * 6;
              spr->drawFastHLine(cx - 8 + r * 2, ry, 16 - r * 4, 0xFFFF);
            }
          }
        }
        // =========================================================================
        // NHÓM 3: 50 CƠ GIÁP CYBER & VŨ KHÍ KHÔNG GIAN (ID 100..149)
        // =========================================================================
        else if (id >= 100 && id < 150) {
          int sub = (id - 100);
          if (sub < 15) {
            // 100-114: TACTICAL RADAR HUD & LA BÀN THIÊN HÀ (Khắc phục lỗi màn hình đen)
            // 3 vòng tròn HUD chiến thuật màu Cyan
            spr->drawCircle(cx, cy, 14, 0x07FF);
            spr->drawCircle(cx, cy, 26, 0x05DF);
            spr->drawCircle(cx, cy, 36, 0x035B);
            // Tia quét Radar xoay tròn 60 FPS
            float sw = angle * 2.8f;
            spr->drawLine(cx, cy, cx + (int)(cosf(sw) * 36.0f), cy + (int)(sinf(sw) * 36.0f), 0x07FF);
            // 3 mục tiêu chiến thuật nhấp nháy
            spr->fillCircle(cx + 16, cy - 12, 2, 0xF800);
            spr->fillCircle(cx - 18, cy + 14, 2, 0x07E0);
            spr->fillCircle(cx + 10, cy + 18, 2, 0xFDE0);
            // Khung khóa mục tiêu 4 góc [ + ]
            spr->drawRect(cx - 6, cy - 6, 12, 12, 0xFFFF);
            spr->drawFastHLine(cx - 10, cy, 20, 0x07FF);
            spr->drawFastVLine(cx, cy - 10, 20, 0x07FF);
          } else if (sub < 30) {
            // 115-129: PHÁO RAY ĐIỆN TỪ & DAO GĂM CAO TẦN (Railgun, Murasama)
            // Khung nòng pháo đôi song song
            spr->fillRect(cx - 24, cy - 8, 48, 4, 0x31A6);
            spr->fillRect(cx - 24, cy + 4, 48, 4, 0x31A6);
            // Cuộn cảm ứng từ phát quang
            for (int c = 0; c < 5; c++) {
              spr->fillRect(cx - 18 + c * 8, cy - 6, 4, 12, 0x07FF);
            }
            // Tia hồ quang điện phóng ở giữa nòng
            spr->drawLine(cx - 16, cy, cx + 22, cy, 0xFFFF);
            // Quả cầu plasma ở đầu nòng tụ năng
            spr->fillCircle(cx + 26, cy, 6 + (int)(breath * 3), 0x07FF);
            spr->fillCircle(cx + 26, cy, 3, 0xFFFF);
          } else {
            // 130-149: DRONE TRINH SÁT TÀNG HÌNH & KHIÊN LỤC GIÁC NANITE
            // Thân drone lục giác góc cạnh
            int dy = (int)(sinf(angle * 3.0f) * 3.0f);
            spr->fillRoundRect(cx - 18, cy - 10 + dy, 36, 20, 6, 0x2124);
            spr->drawRoundRect(cx - 18, cy - 10 + dy, 36, 20, 6, 0x07FF);
            // Mắt cảm biến quang học Cyan ở tâm
            spr->fillCircle(cx, cy + dy, 5, 0x07FF);
            spr->drawPixel(cx, cy + dy, 0xFFFF);
            // 4 động cơ đẩy ion ở 4 góc cánh
            spr->fillRect(cx - 24, cy - 12 + dy, 6, 4, 0x05DF);
            spr->fillRect(cx + 18, cy - 12 + dy, 6, 4, 0x05DF);
            spr->fillRect(cx - 24, cy + 8 + dy, 6, 4, 0x05DF);
            spr->fillRect(cx + 18, cy + 8 + dy, 6, 4, 0x05DF);
            // Vòng khiên lục giác bao bọc
            spr->drawCircle(cx, cy + dy, 30 + (int)(breath * 3), 0x07FF);
          }
        }
        // =========================================================================
        // NHÓM 4: 50 THÚ CƯNG PIXEL 2.5D & ANIME KAWAII (ID 150..199)
        // =========================================================================
        else if (id >= 150 && id < 200) {
          int sub = (id - 150);
          if (sub < 20) {
            // 150-169: CÁC LOẠI AXOLOTL (Kỳ nhông hồng đào, thổi bong bóng, game thủ, ramen...)
            // 1. Thân Axolotl tròn bầu bĩnh hồng phấn 2.5D
            int ay = cy + (int)(sinf(angle * 2.5f) * 3.0f);
            spr->fillRoundRect(cx - 22, ay - 16, 44, 34, 12, lgfx::color565(255, 175, 195));
            spr->fillRoundRect(cx - 18, ay - 12, 36, 26, 10, lgfx::color565(255, 195, 210)); // Lưng 3D
            // 2. Cặp mang tai xòe đặc trưng (3 nhánh mỗi bên) ve vẩy theo nhịp thở
            int fw = (int)(sinf(angle * 3.5f) * 2.5f);
            // Mang trái
            spr->fillRoundRect(cx - 32 + fw, ay - 18, 12, 6, 3, lgfx::color565(255, 105, 150));
            spr->fillRoundRect(cx - 34 + fw, ay - 8, 14, 6, 3, lgfx::color565(255, 105, 150));
            spr->fillRoundRect(cx - 30 + fw, ay + 2, 10, 5, 2, lgfx::color565(255, 105, 150));
            // Mang phải
            spr->fillRoundRect(cx + 20 - fw, ay - 18, 12, 6, 3, lgfx::color565(255, 105, 150));
            spr->fillRoundRect(cx + 20 - fw, ay - 8, 14, 6, 3, lgfx::color565(255, 105, 150));
            spr->fillRoundRect(cx + 20 - fw, ay + 2, 10, 5, 2, lgfx::color565(255, 105, 150));
            // 3. Đôi mắt Anime tròn to chớp mắt
            bool blink = ((millis() % 3500) < 160);
            if (!blink) {
              spr->fillCircle(cx - 10, ay - 4, 5, 0x18C3);
              spr->fillCircle(cx + 10, ay - 4, 5, 0x18C3);
              spr->fillCircle(cx - 11, ay - 6, 2, 0xFFFF); // Highlight sao
              spr->fillCircle(cx + 9, ay - 6, 2, 0xFFFF);
            } else {
              spr->drawFastHLine(cx - 14, ay - 4, 8, 0x18C3); // Chớp mắt hình ^
              spr->drawFastHLine(cx + 6, ay - 4, 8, 0x18C3);
            }
            // 4. Má hồng phúng phính
            spr->fillCircle(cx - 14, ay + 4, 3, lgfx::color565(255, 120, 150));
            spr->fillCircle(cx + 14, ay + 4, 3, lgfx::color565(255, 120, 150));
            // 5. Miệng cười nhỏ ngọt ngào
            spr->drawPixel(cx - 1, ay + 4, 0x8800);
            spr->drawPixel(cx, ay + 5, 0x8800);
            spr->drawPixel(cx + 1, ay + 4, 0x8800);
            // 6. Bong bóng nước nổi lên xung quanh
            int b1y = ay + 24 - ((millis() / 20) % 70);
            int b2y = ay + 36 - (((millis() + 400) / 25) % 80);
            spr->drawCircle(cx + 24, b1y, 4, 0xCE7F);
            spr->drawPixel(cx + 23, b1y - 1, 0xFFFF);
            spr->drawCircle(cx - 26, b2y, 3, 0xCE7F);
          } else if (sub < 35) {
            // 170-184: MÈO HOÀNG GIA & TINH LINH RỪNG KODAMA
            int cy_m = cy + (int)(sinf(angle * 2.0f) * 2.0f);
            // Khuôn mặt mèo tròn trắng muốt
            spr->fillRoundRect(cx - 20, cy_m - 14, 40, 30, 10, 0xFFFF);
            // Tai mèo tam giác có lòng tai hồng
            spr->fillTriangle(cx - 18, cy_m - 12, cx - 12, cy_m - 26, cx - 4, cy_m - 12, 0xFFFF);
            spr->fillTriangle(cx - 16, cy_m - 12, cx - 12, cy_m - 22, cx - 6, cy_m - 12, lgfx::color565(255, 180, 200));
            spr->fillTriangle(cx + 4, cy_m - 12, cx + 12, cy_m - 26, cx + 18, cy_m - 12, 0xFFFF);
            spr->fillTriangle(cx + 6, cy_m - 12, cx + 12, cy_m - 22, cx + 16, cy_m - 12, lgfx::color565(255, 180, 200));
            // Mắt cười híp tít vui vẻ
            spr->drawFastHLine(cx - 13, cy_m - 2, 6, 0x0000);
            spr->drawFastHLine(cx + 7, cy_m - 2, 6, 0x0000);
            // Râu mèo 2 bên
            spr->drawFastHLine(cx - 26, cy_m + 2, 6, 0x94B2);
            spr->drawFastHLine(cx + 20, cy_m + 2, 6, 0x94B2);
            // Chuông cổ vàng Maneki
            spr->fillCircle(cx, cy_m + 16, 4, 0xFDE0);
          } else {
            // 185-199: RỒNG CON & THIÊN CẦU CHIBI
            spr->fillCircle(cx, cy, 22 + (int)(breath * 3), lgfx::color565(90, 180, 255));
            spr->fillCircle(cx - 6, cy - 6, 3, 0xFFFF);
            spr->fillCircle(cx + 6, cy - 6, 3, 0xFFFF);
            spr->drawCircle(cx, cy, 32, 0xFDE0);
          }
        }
        // =========================================================================
        // NHÓM 5: 50 LÕI NĂNG LƯỢNG PLASMA & MA TRẬN CYBER (ID 200..249)
        // =========================================================================
        else {
          int sub = (id - 200);
          if (sub < 20) {
            // 200-219: LÕI HỢP HẠCH TOKAMAK & TINH THỂ SIÊU DẪN
            // Vành từ trường Tokamak đa lớp xoay
            spr->drawCircle(cx, cy, 28, 0xFDE0);
            spr->drawCircle(cx, cy, 20, 0x07FF);
            spr->drawCircle(cx, cy, 12, 0xF800);
            // Luồng hạt Plasma siêu nóng ở tâm
            spr->fillCircle(cx, cy, 6 + (int)(breath * 3), 0xFFFF);
            // 8 chấu từ trường cố định
            for (int a = 0; a < 8; a++) {
              float rad = a * 0.785398f + angle * 2.0f;
              spr->drawLine(cx + (int)(cosf(rad)*14), cy + (int)(sinf(rad)*14), cx + (int)(cosf(rad)*28), cy + (int)(sinf(rad)*28), 0x07FF);
            }
          } else {
            // 220-249: MA TRẬN LƯỚI THẦN KINH & PIN ZERO-POINT
            spr->drawRect(cx - 18, cy - 26, 36, 52, 0x07FF);
            spr->fillRect(cx - 14, cy - 22, 28, 44, 0x10A2);
            int pHeight = 8 + (int)(breath * 24.0f);
            spr->fillRect(cx - 12, cy + 20 - pHeight, 24, pHeight, 0x07FF);
            spr->drawFastHLine(cx - 10, cy, 20, 0xFFFF);
          }
        }
        break;
      }
    }
  }
};
