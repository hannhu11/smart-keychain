#pragma once
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class SpriteRenderer {
public:
  static void drawTheme(LGFX_Sprite* spr, int id, int cx, int cy, float breath, float angle) {
    id = (id >= 0) ? (id % 50) : 0;

    switch (id) {
      // =======================================================================
      // NHÓM 1: THÁNH KHÍ HUYỀN THOẠI (ID 0)
      // =======================================================================
      case 0: { // Excalibur - Thánh Kiếm Bàn Tròn (The Holy Claymore 1:1 Khớp Ảnh Móc Khóa Thật)
        int shadowW = 32 - (int)(sinf(angle * 2.5f) * 4.0f);
        spr->fillEllipse(cx, cy + 54, shadowW, 6, lgfx::color565(5, 10, 20));

        const float cosA = 0.70710678f, sinA = -0.70710678f;
        auto tX = [&](int u, int v) -> int { return cx + (int)roundf(u * cosA - v * sinA); };
        auto tY = [&](int u, int v) -> int { return (cy - 4) + (int)roundf(u * sinA + v * cosA); };

        auto dPoly = [&](const int pts[][2], int n, uint16_t fill) {
          if (n == 4) {
            int x0 = tX(pts[0][0], pts[0][1]), y0 = tY(pts[0][0], pts[0][1]);
            int x1 = tX(pts[1][0], pts[1][1]), y1 = tY(pts[1][0], pts[1][1]);
            int x2 = tX(pts[2][0], pts[2][1]), y2 = tY(pts[2][0], pts[2][1]);
            int x3 = tX(pts[3][0], pts[3][1]), y3 = tY(pts[3][0], pts[3][1]);
            spr->fillTriangle(x0, y0, x1, y1, x2, y2, fill);
            spr->fillTriangle(x0, y0, x2, y2, x3, y3, fill);
          } else if (n == 5) {
            int x0 = tX(pts[0][0], pts[0][1]), y0 = tY(pts[0][0], pts[0][1]);
            int x1 = tX(pts[1][0], pts[1][1]), y1 = tY(pts[1][0], pts[1][1]);
            int x2 = tX(pts[2][0], pts[2][1]), y2 = tY(pts[2][0], pts[2][1]);
            int x3 = tX(pts[3][0], pts[3][1]), y3 = tY(pts[3][0], pts[3][1]);
            int x4 = tX(pts[4][0], pts[4][1]), y4 = tY(pts[4][0], pts[4][1]);
            spr->fillTriangle(x0, y0, x1, y1, x2, y2, fill);
            spr->fillTriangle(x0, y0, x2, y2, x3, y3, fill);
            spr->fillTriangle(x0, y0, x3, y3, x4, y4, fill);
          }
        };

        const int outBlade[5][2] = {{-16, -18}, {52, -18}, {66, 0}, {52, 18}, {-16, 18}};
        const int outGuard[4][2] = {{-26, -30}, {-16, -30}, {-16, 30}, {-26, 30}};
        const int outGrip[4][2]  = {{-50, -7},  {-26, -7},  {-26, 7},  {-50, 7}};
        const int outPom[5][2]   = {{-62, -12}, {-48, -12}, {-48, 12}, {-62, 12}, {-66, 0}};
        dPoly(outBlade, 5, TFT_WHITE);
        dPoly(outGuard, 4, TFT_WHITE);
        dPoly(outGrip, 4, TFT_WHITE);
        dPoly(outPom, 5, TFT_WHITE);

        const int cyBlade[5][2] = {{-15, -15}, {50, -15}, {62, 0}, {50, 15}, {-15, 15}};
        const int cyGuard[4][2] = {{-24, -27}, {-17, -27}, {-17, 27}, {-24, 27}};
        dPoly(cyBlade, 5, 0x07FF);
        dPoly(cyGuard, 4, 0x07FF);

        const int inBlade[5][2] = {{-14, -10}, {46, -10}, {54, 0}, {46, 10}, {-14, 10}};
        dPoly(inBlade, 5, 0x29B5);

        spr->drawLine(tX(-12, 0), tY(-12, 0), tX(48, 0), tY(48, 0), TFT_WHITE);
        const int runes[3] = {-4, 14, 30};
        for (int ru : runes) {
          const int rPts[4][2] = {{ru - 3, 0}, {ru, -4}, {ru + 3, 0}, {ru, 4}};
          dPoly(rPts, 4, TFT_WHITE);
        }

        const int cDiamondOut[4][2] = {{-22, -6}, {-17, 0}, {-22, 6}, {-27, 0}};
        const int cDiamondIn[4][2]  = {{-22, -3}, {-19, 0}, {-22, 3}, {-25, 0}};
        dPoly(cDiamondOut, 4, TFT_WHITE);
        dPoly(cDiamondIn, 4, 0x07FF);

        const int inGrip[4][2] = {{-48, -4}, {-26, -4}, {-26, 4}, {-48, 4}};
        dPoly(inGrip, 4, 0x10A2);
        const int inPom[4][2] = {{-58, -8}, {-50, -8}, {-50, 8}, {-58, 8}};
        const int inPomGem[4][2] = {{-56, -4}, {-52, -4}, {-52, 4}, {-56, 4}};
        dPoly(inPom, 4, 0x07FF);
        dPoly(inPomGem, 4, TFT_WHITE);
        break;
      }

      // =======================================================================
      // NHÓM 2: SIÊU THÚ CƯNG 3D ART-TOY & POP MART (IDs 1..15)
      // =======================================================================
      case 1: { // Yobao - Bé Hoa Cải Vàng (Mô phỏng 1:1 Hubei Rapeseed Festival)
        int by = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        spr->fillEllipse(cx, by + 34, 24, 5, lgfx::color565(15, 12, 5));

        // 1. Mũ cánh hoa cải vàng nở 3D
        spr->fillCircle(cx, by - 24, 13, 0xFDE0);
        spr->fillCircle(cx - 18, by - 18, 11, 0xFDE0);
        spr->fillCircle(cx + 18, by - 18, 11, 0xFDE0);
        spr->fillCircle(cx - 24, by - 8, 9, 0xFDE0);
        spr->fillCircle(cx + 24, by - 8, 9, 0xFDE0);
        spr->fillRect(cx - 2, by - 36, 4, 12, 0x2DE4); // Cuống lá xanh
        spr->fillCircle(cx + 2, by - 36, 3, 0x56E8);

        // 2. Thân tròn vàng phúng phính & bụng 3D
        spr->fillRoundRect(cx - 18, by - 12, 36, 32, 10, 0xFDE0);
        spr->fillRoundRect(cx - 14, by - 8, 28, 24, 8, 0xFFE0); // Highlight

        // 3. Đôi mắt đen hạt tiêu & đốm sáng
        spr->fillCircle(cx - 8, by - 2, 3, 0x4120);
        spr->fillCircle(cx + 8, by - 2, 3, 0x4120);
        spr->drawPixel(cx - 9, by - 3, TFT_WHITE);
        spr->drawPixel(cx + 7, by - 3, TFT_WHITE);

        // 4. Má hồng cam đào
        spr->fillCircle(cx - 13, by + 4, 4, 0xFCE0);
        spr->fillCircle(cx + 13, by + 4, 4, 0xFCE0);

        // 5. Miệng cười nhỏ
        spr->drawPixel(cx - 1, by + 4, 0x4120);
        spr->drawPixel(cx, by + 5, 0x4120);
        spr->drawPixel(cx + 1, by + 4, 0x4120);

        // 6. Hai tay ôm bông hoa vàng
        spr->fillCircle(cx, by + 14, 6, TFT_YELLOW);
        spr->drawPixel(cx, by + 14, 0xFA60);
        spr->fillRect(cx - 1, by + 19, 2, 8, 0x2DE4);
        break;
      }

      case 2: { // Raya - Tinh Linh Rừng Xanh (Mô phỏng 1:1 Raya Forest Heart)
        int ry = cy + (int)(sinf(angle * 3.0f) * 3.0f);
        spr->fillEllipse(cx, ry + 36, 26, 5, lgfx::color565(5, 20, 15));

        // 1. Cánh lá sau lưng vỗ nhẹ
        int lFlap = (int)(sinf(angle * 4.5f) * 3.0f);
        spr->fillTriangle(cx - 16, ry + 2, cx - 28, ry - 14 + lFlap, cx - 12, ry + 12, 0x2DE4);
        spr->fillTriangle(cx + 16, ry + 2, cx + 28, ry - 14 + lFlap, cx + 12, ry + 12, 0x2DE4);

        // 2. Thân xanh mint & tóc lá
        spr->fillRoundRect(cx - 18, ry - 14, 36, 34, 12, lgfx::color565(167, 243, 208));
        // Tóc lá nhọn trên đỉnh
        spr->fillTriangle(cx - 12, ry - 14, cx, ry - 32, cx + 12, ry - 14, 0x5EEA);
        spr->fillTriangle(cx - 22, ry - 8, cx - 14, ry - 24, cx - 6, ry - 8, 0x5EEA);
        spr->fillTriangle(cx + 6, ry - 8, cx + 14, ry - 24, cx + 22, ry - 8, 0x5EEA);

        // 3. Họa tiết dạ quang neon trắng phát sáng trên trán
        spr->drawFastVLine(cx, ry - 22, 10, TFT_WHITE);
        spr->drawLine(cx - 6, ry - 18, cx - 2, ry - 10, TFT_WHITE);
        spr->drawLine(cx + 6, ry - 18, cx + 2, ry - 10, TFT_WHITE);

        // 4. Mắt to đen nháy chớp mắt
        bool blink = (millis() % 3500 < 160);
        if (!blink) {
          spr->fillCircle(cx - 8, ry - 4, 4, 0x1082);
          spr->fillCircle(cx + 8, ry - 4, 4, 0x1082);
          spr->drawPixel(cx - 9, ry - 5, TFT_WHITE);
          spr->drawPixel(cx + 7, ry - 5, TFT_WHITE);
        } else {
          spr->drawFastHLine(cx - 11, ry - 4, 6, 0x1082);
          spr->drawFastHLine(cx + 5, ry - 4, 6, 0x1082);
        }

        // 5. Miệng cười tươi rộng mở & má hồng
        spr->fillRoundRect(cx - 4, ry + 4, 8, 4, 2, 0xF800);
        spr->fillCircle(cx - 12, ry + 3, 3, 0xFBAE);
        spr->fillCircle(cx + 12, ry + 3, 3, 0xFBAE);
        break;
      }

      case 3: { // Bloomy [Yoona] - Ong Bắp Cày Hoa Anh Đào (Mô phỏng 1:1 NXU Bloomy)
        int by = cy + (int)(sinf(angle * 3.5f) * 3.0f);
        spr->fillEllipse(cx, by + 34, 28, 5, lgfx::color565(15, 12, 10));

        // 1. Cánh ong trắng mờ vỗ rung rinh
        int wShimmer = (int)(sinf(angle * 12.0f) * 4.0f);
        spr->fillEllipse(cx - 24, by - 8 + wShimmer, 12, 6, TFT_WHITE);
        spr->fillEllipse(cx + 24, by - 8 - wShimmer, 12, 6, TFT_WHITE);

        // 2. Thân ong vàng tròn lông xù
        spr->fillRoundRect(cx - 20, by - 16, 40, 36, 14, 0xFDE0);
        // Sọc nâu ấm
        spr->fillRoundRect(cx - 19, by + 4, 38, 7, 3, 0x61A2);
        spr->fillRoundRect(cx - 17, by + 14, 34, 5, 2, 0x61A2);

        // 3. Vòng hoa anh đào pha lê quanh cổ (5 bông hoa hồng pha lê)
        const int fX[5] = {-16, -8, 0, 8, 16};
        const int fY[5] = {-4, 2, 5, 2, -4};
        for (int i = 0; i < 5; i++) {
          spr->fillCircle(cx + fX[i], by + fY[i], 4, 0xFCDE);
          spr->drawPixel(cx + fX[i], by + fY[i], TFT_WHITE);
        }

        // 4. Mắt to đen long lanh
        spr->fillCircle(cx - 8, by - 6, 4, 0x1082);
        spr->fillCircle(cx + 8, by - 6, 4, 0x1082);
        spr->drawPixel(cx - 9, by - 7, TFT_WHITE);
        spr->drawPixel(cx + 7, by - 7, TFT_WHITE);
        spr->fillCircle(cx - 13, by - 1, 3, 0xFBAE);
        spr->fillCircle(cx + 13, by - 1, 3, 0xFBAE);
        break;
      }

      case 4: { // Ember [Chae-on] - Cáo Lửa Pha Lê Có Cánh (Mô phỏng 1:1 NXU Ember)
        int fy = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        spr->fillEllipse(cx, fy + 36, 28, 5, lgfx::color565(20, 10, 5));

        // 1. Cánh cam thiên thần sải rộng
        spr->fillTriangle(cx - 14, fy, cx - 34, fy - 16, cx - 14, fy - 22, 0xFB80);
        spr->fillTriangle(cx + 14, fy, cx + 34, fy - 16, cx + 14, fy - 22, 0xFB80);

        // 2. Thân cáo cam lông xù & ức trắng
        spr->fillRoundRect(cx - 18, fy - 14, 36, 34, 10, 0xFA60);
        spr->fillRoundRect(cx - 10, fy + 2, 20, 16, 6, TFT_WHITE); // Ức trắng

        // 3. Tai cáo nhọn viền nâu
        spr->fillTriangle(cx - 16, fy - 12, cx - 12, fy - 30, cx - 4, fy - 12, 0x5140);
        spr->fillTriangle(cx + 4, fy - 12, cx + 12, fy - 30, cx + 16, fy - 12, 0x5140);

        // 4. Vương miện tinh thể hổ phách trên trán
        spr->fillTriangle(cx - 6, fy - 16, cx, fy - 24, cx + 6, fy - 16, 0xFDE0);
        spr->drawPixel(cx, fy - 24, TFT_WHITE);

        // 5. Mắt cáo đen to tròn & má hồng
        spr->fillCircle(cx - 7, fy - 4, 3, 0x1082);
        spr->fillCircle(cx + 7, fy - 4, 3, 0x1082);
        spr->drawPixel(cx - 8, fy - 5, TFT_WHITE);
        spr->drawPixel(cx + 6, fy - 5, TFT_WHITE);
        spr->fillCircle(cx - 12, fy + 2, 3, 0xFCE0);
        spr->fillCircle(cx + 12, fy + 2, 3, 0xFCE0);
        break;
      }

      case 5: { // Aurelle [Seorin] - Sư Tử Nhí Vương Giả (Mô phỏng 1:1 NXU Aurelle)
        int ly = cy + (int)(sinf(angle * 2.0f) * 2.5f);
        spr->fillEllipse(cx, ly + 36, 32, 5, lgfx::color565(18, 12, 12));

        // 1. Bờm sư tử tròn màu hồng đào viền sao kim cương
        spr->fillCircle(cx, ly, 25, 0xFCDE);
        for (int a = 0; a < 6; a++) {
          float rad = a * 1.047f;
          int sx = cx + (int)(cosf(rad) * 23);
          int sy = ly + (int)(sinf(rad) * 23);
          spr->drawPixel(sx, sy, TFT_WHITE); // Sao kim cương
        }

        // 2. Khuôn mặt vàng ấm
        spr->fillCircle(cx, ly + 2, 16, 0xFEE0);
        // Vương miện nhỏ trên đỉnh đầu
        spr->fillTriangle(cx - 6, ly - 18, cx, ly - 26, cx + 6, ly - 18, 0xFDE0);
        spr->drawPixel(cx, ly - 26, TFT_WHITE);

        // 3. Mắt nâu hổ phách to tròn
        spr->fillCircle(cx - 6, ly + 1, 3, 0x61A2);
        spr->fillCircle(cx + 6, ly + 1, 3, 0x61A2);
        spr->drawPixel(cx - 7, ly, TFT_WHITE);
        spr->drawPixel(cx + 5, ly, TFT_WHITE);

        // 4. Răng khểnh nhỏ đáng yêu
        spr->drawPixel(cx - 3, ly + 8, TFT_WHITE);
        spr->drawPixel(cx + 3, ly + 8, TFT_WHITE);
        spr->fillCircle(cx - 11, ly + 6, 3, 0xFBAE);
        spr->fillCircle(cx + 11, ly + 6, 3, 0xFBAE);
        break;
      }

      case 6: { // Kairo [Yiseo] - Rồng Dơi Hồng Tinh Nghịch (Mô phỏng 1:1 NXU Kairo)
        int ky = cy + (int)(sinf(angle * 2.8f) * 3.0f);
        spr->fillEllipse(cx, ky + 36, 28, 5, lgfx::color565(16, 10, 16));

        // 1. Cánh dơi hồng mềm mại mở rộng
        spr->fillTriangle(cx - 12, ky, cx - 36, ky - 10, cx - 18, ky - 20, 0xFCDE);
        spr->fillTriangle(cx + 12, ky, cx + 36, ky - 10, cx + 18, ky - 20, 0xFCDE);

        // 2. Thân rồng dơi lông hồng
        spr->fillRoundRect(cx - 18, ky - 14, 36, 34, 12, 0xFBAE);

        // 3. Cặp sừng cong nhỏ xíu trên đầu
        spr->fillTriangle(cx - 14, ky - 14, cx - 18, ky - 26, cx - 8, ky - 14, 0xFFE0);
        spr->fillTriangle(cx + 8, ky - 14, cx + 18, ky - 26, cx + 14, ky - 14, 0xFFE0);

        // 4. Mắt đen to & răng nanh ma cà rồng nhí
        spr->fillCircle(cx - 7, ky - 2, 4, 0x1082);
        spr->fillCircle(cx + 7, ky - 2, 4, 0x1082);
        spr->drawPixel(cx - 8, ky - 3, TFT_WHITE);
        spr->drawPixel(cx + 6, ky - 3, TFT_WHITE);
        spr->drawPixel(cx - 3, ky + 6, TFT_WHITE);
        spr->drawPixel(cx + 3, ky + 6, TFT_WHITE);
        break;
      }

      case 7: { // Lumori - Nấm Rừng Phát Quang Cổ Đại (Mô phỏng 1:1 Lumori)
        int my = cy + (int)(sinf(angle * 2.2f) * 2.5f);
        spr->fillEllipse(cx, my + 36, 26, 5, lgfx::color565(5, 15, 25));

        // 1. Mũ ngủ nấm chóp dài màu lam
        spr->fillCircle(cx, my - 14, 20, 0x3CF7);
        spr->fillTriangle(cx - 16, my - 16, cx + 22, my - 34, cx + 14, my - 14, 0x3CF7);
        spr->fillCircle(cx + 22, my - 34, 4, 0xFDE0); // Quả chuông sáng ở chóp

        // 2. Thân trắng sứ & bụng phát sáng xoắn ốc
        spr->fillRoundRect(cx - 16, my - 6, 32, 28, 10, TFT_WHITE);
        spr->fillCircle(cx, my + 10, 7, 0xFDE0); // Bụng phát sáng
        spr->drawPixel(cx, my + 10, 0xFA60);

        // 3. Mắt to trong veo & má hồng
        spr->fillCircle(cx - 7, my + 2, 3, 0x1082);
        spr->fillCircle(cx + 7, my + 2, 3, 0x1082);
        spr->drawPixel(cx - 8, my + 1, TFT_WHITE);
        spr->drawPixel(cx + 6, my + 1, TFT_WHITE);
        spr->fillCircle(cx - 11, my + 6, 2, 0xFCE0);
        spr->fillCircle(cx + 11, my + 6, 2, 0xFCE0);
        break;
      }

      case 8: { // Lumio - Ngọn Lửa Vũ Trụ Tinh Nghịch (Mô phỏng 1:1 Lumio)
        int ly = cy + (int)(sinf(angle * 2.8f) * 3.0f);
        spr->fillEllipse(cx, ly + 36, 26, 5, lgfx::color565(10, 8, 20));

        // 1. Mái tóc ngọn lửa uốn lượn màu hồng - tím - cyan
        spr->fillTriangle(cx - 14, ly - 8, cx, ly - 34, cx + 14, ly - 8, 0xF81F);
        spr->fillTriangle(cx - 10, ly - 8, cx + 2, ly - 32, cx + 10, ly - 8, 0x07FF);

        // 2. Thân áo choàng phù thủy màu tím đêm sao
        spr->fillRoundRect(cx - 14, ly - 10, 28, 30, 8, 0x2124);
        spr->fillCircle(cx, ly + 8, 5, 0xFDE0); // Biểu tượng xoắn ốc sáng

        // 3. Mắt xanh sapphire to tròn
        spr->fillCircle(cx - 6, ly - 2, 3, 0x07FF);
        spr->fillCircle(cx + 6, ly - 2, 3, 0x07FF);
        spr->drawPixel(cx - 7, ly - 3, TFT_WHITE);
        spr->drawPixel(cx + 5, ly - 3, TFT_WHITE);
        break;
      }

      case 9: { // Cute Bunny - Thỏ Hoodie Mint Pastel (Mô phỏng 1:1 Cute Bunny)
        int by = cy + (int)(sinf(angle * 2.4f) * 3.0f);
        spr->fillEllipse(cx, by + 36, 26, 5, lgfx::color565(12, 18, 16));

        // 1. Tai cọc cạch (Tai trái hồng, tai phải xanh mint)
        spr->fillRoundRect(cx - 14, by - 36, 8, 22, 4, 0xFCDE);
        spr->fillRoundRect(cx + 6, by - 36, 8, 22, 4, 0x87F5);

        // 2. Mũ hoodie xanh bạc hà & mặt trắng
        spr->fillRoundRect(cx - 20, by - 16, 40, 34, 14, 0x87F5);
        spr->fillRoundRect(cx - 14, by - 10, 28, 24, 10, TFT_WHITE);

        // 3. Mắt đen, mũi hồng và miệng số 3
        spr->fillCircle(cx - 7, by - 2, 3, 0x1082);
        spr->fillCircle(cx + 7, by - 2, 3, 0x1082);
        spr->drawPixel(cx, by + 1, 0xFBAE); // Mũi hồng
        spr->fillCircle(cx - 10, by + 4, 3, 0xFBAE);
        spr->fillCircle(cx + 10, by + 4, 3, 0xFBAE);
        break;
      }

      case 10: { // Star Sprite - Bé Sao Băng Áo Choàng Vàng
        int sy = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        spr->fillEllipse(cx, sy + 36, 26, 5, lgfx::color565(20, 18, 5));
        // Mũ sao vàng 5 cánh
        spr->fillCircle(cx, sy - 6, 22, 0xFDE0);
        spr->fillRoundRect(cx - 14, sy - 2, 28, 20, 8, 0xFFF2);
        spr->fillCircle(cx - 6, sy + 4, 3, 0x1082);
        spr->fillCircle(cx + 6, sy + 4, 3, 0x1082);
        spr->fillCircle(cx - 10, sy + 8, 2, 0xFCE0);
        spr->fillCircle(cx + 10, sy + 8, 2, 0xFCE0);
        break;
      }

      case 11: { // Lotus Frog - Ếch Xanh Đội Lá Sen
        int fy = cy + (int)(sinf(angle * 2.0f) * 2.5f);
        spr->fillEllipse(cx, fy + 36, 28, 5, lgfx::color565(6, 20, 10));
        // Ô lá sen xanh mướt
        spr->fillEllipse(cx, fy - 26, 24, 8, 0x2DE4);
        spr->drawFastVLine(cx + 12, fy - 26, 24, 0x1AE2);
        // Thân ếch xanh tròn
        spr->fillCircle(cx, fy + 6, 18, 0x56E8);
        spr->fillCircle(cx - 10, fy - 8, 6, 0x56E8); // Mắt ếch lồi
        spr->fillCircle(cx + 10, fy - 8, 6, 0x56E8);
        spr->fillCircle(cx - 10, fy - 8, 3, 0x1082);
        spr->fillCircle(cx + 10, fy - 8, 3, 0x1082);
        spr->drawPixel(cx - 11, fy - 9, TFT_WHITE);
        spr->drawPixel(cx + 9, fy - 9, TFT_WHITE);
        break;
      }

      case 12: { // Spore Fairy - Nấm Hồng Dạo Phố
        int ny = cy + (int)(sinf(angle * 2.6f) * 3.0f);
        spr->fillEllipse(cx, ny + 36, 26, 5, lgfx::color565(18, 10, 12));
        // Mũ nấm chấm bi trắng
        spr->fillCircle(cx, ny - 10, 22, 0xFBAE);
        spr->fillCircle(cx - 10, ny - 16, 3, TFT_WHITE);
        spr->fillCircle(cx + 8, ny - 18, 4, TFT_WHITE);
        spr->fillRoundRect(cx - 12, ny, 24, 20, 8, TFT_WHITE);
        spr->fillCircle(cx - 5, ny + 6, 2, 0x1082);
        spr->fillCircle(cx + 5, ny + 6, 2, 0x1082);
        break;
      }

      case 13: { // Clover Sprout - Mầm Cây May Mắn 4 Lá
        int cy_s = cy + (int)(sinf(angle * 2.2f) * 2.5f);
        spr->fillEllipse(cx, cy_s + 36, 24, 5, lgfx::color565(6, 18, 10));
        // Cỏ 4 lá xoay tròn trên đầu
        spr->fillCircle(cx - 5, cy_s - 26, 4, 0x2DE4);
        spr->fillCircle(cx + 5, cy_s - 26, 4, 0x2DE4);
        spr->fillCircle(cx, cy_s - 31, 4, 0x2DE4);
        spr->fillCircle(cx, cy_s - 21, 4, 0x2DE4);
        spr->drawFastVLine(cx, cy_s - 21, 8, 0x1AE2);
        spr->fillRoundRect(cx - 16, cy_s - 6, 32, 28, 10, TFT_WHITE);
        spr->fillCircle(cx - 6, cy_s + 2, 3, 0x1082);
        spr->fillCircle(cx + 6, cy_s + 2, 3, 0x1082);
        break;
      }

      case 14: { // Berry Fox - Cáo Dâu Tây Ngọt Ngào
        int by = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        spr->fillEllipse(cx, by + 36, 26, 5, lgfx::color565(20, 6, 10));
        // Mũ cuống dâu tây xanh
        spr->fillTriangle(cx - 8, by - 24, cx, by - 34, cx + 8, by - 24, 0x2DE4);
        spr->fillRoundRect(cx - 18, by - 16, 36, 34, 12, 0xF800);
        spr->drawPixel(cx - 8, by - 6, TFT_YELLOW); // Hạt dâu tây
        spr->drawPixel(cx + 8, by - 6, TFT_YELLOW);
        spr->drawPixel(cx, by + 8, TFT_YELLOW);
        spr->fillCircle(cx - 7, by, 3, TFT_WHITE);
        spr->fillCircle(cx + 7, by, 3, TFT_WHITE);
        spr->fillCircle(cx - 7, by, 2, 0x1082);
        spr->fillCircle(cx + 7, by, 2, 0x1082);
        break;
      }

      case 15: { // Cloud Sheep - Cừu Mây Bồng Bềnh
        int sy = cy + (int)(sinf(angle * 2.0f) * 3.0f);
        spr->fillEllipse(cx, sy + 36, 28, 5, lgfx::color565(14, 10, 22));
        // Lông cừu xoắn ốc tím oải hương
        spr->fillCircle(cx, sy - 2, 20, 0xCE5F);
        spr->fillCircle(cx - 14, sy - 2, 10, 0xCE5F);
        spr->fillCircle(cx + 14, sy - 2, 10, 0xCE5F);
        spr->fillRoundRect(cx - 10, sy + 2, 20, 16, 6, 0xFFE0); // Mặt
        spr->fillCircle(cx - 5, sy + 6, 2, 0x1082);
        spr->fillCircle(cx + 5, sy + 6, 2, 0x1082);
        break;
      }

      // =======================================================================
      // NHÓM 3: AXOLOTL KỲ NHÔNG KAWAII 2.5D (IDs 16..25)
      // =======================================================================
      case 16: // Axolotl Hồng Đào Ngọt Ngào
      case 17: // Axolotl Thổi Bong Bóng
      case 18: // Axolotl Ngủ Mơ Kẹo Bông
      case 19: // Axolotl Hoàng Tử Vương Giả
      case 20: // Axolotl Game Thủ Neon
      case 21: // Axolotl Bát Mì Ramen
      case 22: // Axolotl Thiên Sứ Đôi Cánh
      case 23: // Axolotl Hoa Anh Đào Sakura
      case 24: // Axolotl Du Hành Không Gian
      case 25: { // Axolotl Matcha Bánh Trôi
        int sub = id - 16;
        int ay = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        int shadowW = 28 - (int)(sinf(angle * 2.5f) * 4.0f);
        spr->fillEllipse(cx, ay + 36, shadowW, 5, lgfx::color565(12, 10, 16));

        // Màu thân theo từng phân loại
        uint16_t bodyCol = (sub == 9) ? lgfx::color565(134, 239, 172) : lgfx::color565(255, 175, 195);
        uint16_t gillCol = (sub == 9) ? lgfx::color565(34, 197, 94) : lgfx::color565(255, 105, 150);

        // 1. Thân Axolotl 2.5D
        spr->fillRoundRect(cx - 22, ay - 16, 44, 34, 12, bodyCol);
        spr->fillRoundRect(cx - 18, ay - 12, 36, 26, 10, bodyCol + 0x0821);

        // 2. 6 mang tai xòe vẫy sóng
        int fw = (int)(sinf(angle * 3.5f) * 2.5f);
        spr->fillRoundRect(cx - 32 + fw, ay - 18, 12, 6, 3, gillCol);
        spr->fillRoundRect(cx - 34 + fw, ay - 8, 14, 6, 3, gillCol);
        spr->fillRoundRect(cx - 30 + fw, ay + 2, 10, 5, 2, gillCol);
        spr->fillRoundRect(cx + 20 - fw, ay - 18, 12, 6, 3, gillCol);
        spr->fillRoundRect(cx + 20 - fw, ay - 8, 14, 6, 3, gillCol);
        spr->fillRoundRect(cx + 20 - fw, ay + 2, 10, 5, 2, gillCol);

        // 3. Mắt chớp sinh học 3.5s
        bool blink = ((millis() % 3500) < 160) || (sub == 2); // sub 2 ngủ mơ
        if (!blink) {
          spr->fillCircle(cx - 10, ay - 4, 5, 0x18C3);
          spr->fillCircle(cx + 10, ay - 4, 5, 0x18C3);
          spr->fillCircle(cx - 11, ay - 6, 2, TFT_WHITE);
          spr->fillCircle(cx + 9, ay - 6, 2, TFT_WHITE);
        } else {
          spr->drawFastHLine(cx - 14, ay - 4, 8, 0x18C3);
          spr->drawFastHLine(cx + 6, ay - 4, 8, 0x18C3);
        }

        // 4. Má hồng & miệng
        spr->fillCircle(cx - 14, ay + 4, 3, gillCol);
        spr->fillCircle(cx + 14, ay + 4, 3, gillCol);
        spr->drawPixel(cx, ay + 4, 0x8800);

        // 5. Phụ kiện độc bản từng loại
        if (sub == 1) { // Thổi bong bóng
          int by1 = ay - ((millis() / 20) % 50);
          spr->drawCircle(cx + 16, by1, 4, 0x07FF);
          spr->drawPixel(cx + 15, by1 - 1, TFT_WHITE);
        } else if (sub == 3) { // Hoàng tử
          spr->fillTriangle(cx - 8, ay - 20, cx, ay - 28, cx + 8, ay - 20, 0xFDE0);
        } else if (sub == 4) { // Game thủ
          spr->drawCircle(cx, ay - 4, 22, 0x07FF);
          spr->fillRect(cx - 24, ay - 9, 4, 10, 0xF81F);
          spr->fillRect(cx + 20, ay - 9, 4, 10, 0xF81F);
        } else if (sub == 6) { // Thiên sứ
          spr->drawCircle(cx, ay - 22, 10, 0xFDE0); // Halo
        }
        break;
      }

      // =======================================================================
      // NHÓM 4: THÚ CƯNG ĐÁNG YÊU & LÃNG MẠN (IDs 26..39)
      // =======================================================================
      case 26: { // Mèo Ba Tư Hoàng Đế (Heterochromia 2 màu mắt)
        int my = cy + (int)(sinf(angle * 2.0f) * 2.5f);
        spr->fillEllipse(cx, my + 36, 28, 5, lgfx::color565(12, 12, 16));
        spr->fillRoundRect(cx - 20, my - 14, 40, 32, 12, TFT_WHITE);
        spr->fillTriangle(cx - 18, my - 12, cx - 12, my - 26, cx - 4, my - 12, TFT_WHITE);
        spr->fillTriangle(cx + 4, my - 12, cx + 12, my - 26, cx + 18, my - 12, TFT_WHITE);
        // Mắt 2 màu: Trái xanh lam 0x07FF, Phải vàng hổ phách 0xFDE0
        spr->fillCircle(cx - 8, my - 2, 4, 0x07FF);
        spr->fillCircle(cx + 8, my - 2, 4, 0xFDE0);
        spr->drawPixel(cx - 9, my - 3, TFT_WHITE);
        spr->drawPixel(cx + 7, my - 3, TFT_WHITE);
        spr->fillCircle(cx, my + 16, 4, 0xF800); // Vòng cổ ruby đỏ
        break;
      }

      case 27: { // Mèo Tam Thể Nữ Hoàng
        int my = cy + (int)(sinf(angle * 2.0f) * 2.5f);
        spr->fillEllipse(cx, my + 36, 28, 5, lgfx::color565(12, 12, 16));
        spr->fillRoundRect(cx - 20, my - 14, 40, 32, 12, TFT_WHITE);
        spr->fillCircle(cx - 10, my - 8, 8, 0xFA60); // Đốm cam
        spr->fillCircle(cx + 10, my - 8, 8, 0x2124); // Đốm đen
        spr->drawFastHLine(cx - 13, my - 2, 6, TFT_BLACK);
        spr->drawFastHLine(cx + 7, my - 2, 6, TFT_BLACK);
        break;
      }

      case 28: { // Mèo Thần Tài Maneki Neko (Vẫy tay 60 FPS)
        int my = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillEllipse(cx, my + 36, 28, 5, lgfx::color565(18, 14, 8));
        spr->fillRoundRect(cx - 18, my - 14, 36, 32, 10, TFT_WHITE);
        spr->drawFastHLine(cx - 12, my - 2, 5, TFT_BLACK);
        spr->drawFastHLine(cx + 7, my - 2, 5, TFT_BLACK);
        // Tay trái vẫy liên tục
        int wWave = (int)(sinf(angle * 8.0f) * 5.0f);
        spr->fillRoundRect(cx - 24, my - 2 + wWave, 8, 16, 4, TFT_WHITE);
        spr->fillCircle(cx, my + 16, 4, 0xFDE0); // Chuông vàng
        break;
      }

      case 29: { // Mèo Con Trong Hộp Giấy Cạc-tông
        int ky = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillRoundRect(cx - 22, ky, 44, 28, 4, 0xB482); // Thùng carton nâu
        spr->drawRoundRect(cx - 22, ky, 44, 28, 4, 0x82C0);
        spr->fillRoundRect(cx - 16, ky - 14, 32, 20, 8, 0xFA60); // Đầu mèo thò ra
        spr->fillCircle(cx - 7, ky - 4, 3, 0x1082);
        spr->fillCircle(cx + 7, ky - 4, 3, 0x1082);
        break;
      }

      case 30: { // Shiba Inu Má Bánh Bao
        int sy = cy + (int)(sinf(angle * 2.2f) * 2.5f);
        spr->fillEllipse(cx, sy + 36, 28, 5, lgfx::color565(18, 12, 6));
        spr->fillRoundRect(cx - 22, sy - 14, 44, 32, 12, 0xFA60);
        spr->fillCircle(cx - 12, sy + 4, 8, TFT_WHITE); // Má bánh bao trắng
        spr->fillCircle(cx + 12, sy + 4, 8, TFT_WHITE);
        spr->fillCircle(cx - 8, sy - 4, 3, 0x1082);
        spr->fillCircle(cx + 8, sy - 4, 3, 0x1082);
        spr->fillCircle(cx, sy + 2, 2, 0x1082); // Mũi đen
        break;
      }

      case 31: { // Corgi Mông Trái Tim
        int cy_c = cy + (int)(sinf(angle * 2.5f) * 2.5f);
        spr->fillEllipse(cx, cy_c + 36, 28, 5, lgfx::color565(18, 12, 6));
        spr->fillCircle(cx, cy_c + 4, 18, 0xFA60); // Mông tròn
        spr->fillCircle(cx - 4, cy_c + 4, 8, TFT_WHITE); // Trái tim đào
        spr->fillCircle(cx + 4, cy_c + 4, 8, TFT_WHITE);
        spr->fillTriangle(cx - 10, cy_c + 6, cx, cy_c + 16, cx + 10, cy_c + 6, TFT_WHITE);
        break;
      }

      case 32: { // Thỏ Mặt Trăng Ngọc Thỏ (Giã cối bánh mochi)
        int ty = cy + (int)(sinf(angle * 2.2f) * 2.5f);
        spr->fillRoundRect(cx - 14, ty - 28, 6, 18, 3, TFT_WHITE); // Tai thỏ
        spr->fillRoundRect(cx + 8, ty - 28, 6, 18, 3, TFT_WHITE);
        spr->fillRoundRect(cx - 16, ty - 12, 32, 26, 10, TFT_WHITE);
        spr->fillCircle(cx - 6, ty - 2, 2, 0xF800); // Mắt đỏ ngọc
        spr->fillCircle(cx + 6, ty - 2, 2, 0xF800);
        spr->fillRect(cx + 14, ty + 4, 16, 14, 0x82C0); // Cối đá
        break;
      }

      case 33: { // Gấu Trúc Gặm Trúc Non
        int py = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillRoundRect(cx - 18, py - 14, 36, 32, 10, TFT_WHITE);
        spr->fillCircle(cx - 14, py - 14, 5, 0x1082); // Tai đen
        spr->fillCircle(cx + 14, py - 14, 5, 0x1082);
        spr->fillCircle(cx - 7, py - 2, 4, 0x1082); // Quầng mắt đen
        spr->fillCircle(cx + 7, py - 2, 4, 0x1082);
        spr->drawPixel(cx - 7, py - 2, TFT_WHITE);
        spr->drawPixel(cx + 7, py - 2, TFT_WHITE);
        spr->fillRect(cx - 2, py, 4, 20, 0x2DE4); // Nhành trúc xanh
        break;
      }

      case 34: { // Chim Cánh Cụt Khăn Len Đỏ
        int cy_p = cy + (int)(sinf(angle * 2.4f) * 2.5f);
        spr->fillRoundRect(cx - 16, cy_p - 14, 32, 32, 12, 0x10A2);
        spr->fillRoundRect(cx - 10, cy_p - 8, 20, 24, 8, TFT_WHITE);
        spr->fillRect(cx - 16, cy_p + 4, 32, 6, 0xF800); // Khăn len đỏ
        spr->fillCircle(cx - 5, cy_p - 4, 2, 0x1082);
        spr->fillCircle(cx + 5, cy_p - 4, 2, 0x1082);
        spr->fillTriangle(cx - 3, cy_p, cx, cy_p + 3, cx + 3, cy_p, 0xFDE0); // Mỏ vàng
        break;
      }

      case 35: { // Rái Cá Biển Nắm Tay
        int oy = cy + (int)(sinf(angle * 2.0f) * 2.5f);
        spr->fillRoundRect(cx - 18, oy - 12, 36, 28, 10, 0x61A2);
        spr->fillRoundRect(cx - 12, oy - 6, 24, 20, 8, 0xD6BA);
        spr->fillCircle(cx - 6, oy - 2, 2, 0x1082);
        spr->fillCircle(cx + 6, oy - 2, 2, 0x1082);
        spr->fillCircle(cx, oy + 8, 5, 0xCE7F); // Hòn đá cuội sáng
        break;
      }

      case 36: { // Rồng Con Sấm Sét Chibi
        int dy = cy + (int)(sinf(angle * 2.6f) * 3.0f);
        spr->fillCircle(cx, dy, 18, 0x3CF7);
        spr->fillCircle(cx - 6, dy - 2, 3, 0x1082);
        spr->fillCircle(cx + 6, dy - 2, 3, 0x1082);
        int wFlap = (int)(sinf(angle * 6.0f) * 3.0f);
        spr->fillTriangle(cx - 16, dy, cx - 26, dy - 8 + wFlap, cx - 12, dy + 6, 0x07FF);
        spr->fillTriangle(cx + 16, dy, cx + 26, dy - 8 + wFlap, cx + 12, dy + 6, 0x07FF);
        break;
      }

      case 37: { // Kỳ Lân Cầu Vồng Nhí
        int uy = cy + (int)(sinf(angle * 2.4f) * 3.0f);
        spr->fillRoundRect(cx - 16, uy - 12, 32, 28, 10, TFT_WHITE);
        spr->fillTriangle(cx - 3, uy - 12, cx, uy - 28, cx + 3, uy - 12, 0xFDE0); // Sừng vàng
        spr->fillCircle(cx - 6, uy - 2, 3, 0xFCDE); // Mắt tím
        spr->fillCircle(cx + 6, uy - 2, 3, 0xFCDE);
        break;
      }

      case 38: { // Đôi Mèo Uyên Ương Lãng Mạn (Đuôi hình trái tim)
        int my = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillCircle(cx - 8, my, 12, TFT_WHITE); // Mèo trắng
        spr->fillCircle(cx + 8, my, 12, 0x1082);    // Mèo đen
        spr->drawCircle(cx, my - 14, 6, 0xF800);    // Trái tim tình yêu
        break;
      }

      case 39: { // Cún Cứu Hộ Saint Bernard
        int by = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillRoundRect(cx - 20, by - 14, 40, 32, 10, 0x8240);
        spr->fillRoundRect(cx - 12, by - 6, 24, 24, 8, TFT_WHITE);
        spr->fillRect(cx - 6, by + 14, 12, 8, 0x61A2); // Bình rượu gỗ
        break;
      }

      // =======================================================================
      // NHÓM 5: ĐỊA CẦU & THIÊN VĂN 3D (IDs 40..49)
      // =======================================================================
      case 40: { // Địa Cầu Xanh Quỹ Đạo ISS (Blue Marble 3D)
        spr->fillCircle(cx, cy, 36, lgfx::color565(0, 70, 180));
        spr->fillCircle(cx, cy, 33, lgfx::color565(0, 140, 255));
        spr->fillCircle(cx, cy, 30, lgfx::color565(0, 220, 255)); // Vành khí quyển
        spr->fillCircle(cx, cy, 28, lgfx::color565(8, 32, 75));   // Đại dương
        int dX = (int)(angle * 8.0f) % 60;
        spr->fillEllipse(cx - 18 + dX - 30, cy - 6, 12, 8, lgfx::color565(25, 115, 55));
        spr->fillEllipse(cx + 10 + dX - 30, cy + 8, 14, 7, lgfx::color565(30, 135, 65));
        spr->fillCircle(cx + 20, cy - 16, 3, TFT_WHITE); // Sunburst
        spr->drawFastHLine(cx + 12, cy - 16, 16, 0xFFE0);
        spr->drawFastVLine(cx + 20, cy - 24, 16, 0xFFE0);
        break;
      }

      case 41: { // Bão Xoáy Cực Băng Nam Cực
        spr->fillCircle(cx, cy, 32, lgfx::color565(8, 32, 75));
        for (int a = 0; a < 4; a++) {
          float rad = a * 1.57f + angle * 2.0f;
          spr->drawEllipse(cx + (int)(cosf(rad)*8), cy + (int)(sinf(rad)*8), 16, 8, TFT_WHITE);
        }
        break;
      }

      case 42: { // Rạn San Hô Phát Quang Rãnh Sâu
        spr->fillRect(cx - 24, cy + 12, 48, 20, 0x05DF);
        spr->fillCircle(cx - 12, cy + 6, 8, 0xF81F);
        spr->fillCircle(cx + 12, cy + 4, 10, 0x07FF);
        break;
      }

      case 43: { // Sa Mạc Sahara Ánh Hoàng Hôn
        spr->fillCircle(cx, cy - 10, 18, 0xF800); // Mặt trời đỏ
        spr->fillTriangle(cx - 36, cy + 28, cx, cy + 8, cx + 36, cy + 28, 0xFDE0); // Đụn cát
        break;
      }

      case 44: { // Rừng Mưa Nhiệt Đới Amazon Mây Mù
        spr->fillCircle(cx - 14, cy + 8, 16, 0x1AE2);
        spr->fillCircle(cx + 14, cy + 6, 18, 0x1AE2);
        spr->fillRoundRect(cx - 20, cy - 4, 40, 8, 4, TFT_WHITE); // Sương mù
        break;
      }

      case 45: { // Cực Quang Aurora Vùng Cực
        for (int x = -28; x <= 28; x += 4) {
          int ay = cy - 10 + (int)(sinf(angle * 3.0f + x * 0.1f) * 12.0f);
          spr->drawFastVLine(cx + x, ay, 18, 0x07E0);
        }
        break;
      }

      case 46: { // Hố Đen Siêu Khối Lượng Gargantua
        spr->drawEllipse(cx, cy, 40, 12, 0xFDE0); // Đĩa bồi tụ
        spr->fillCircle(cx, cy, 18, TFT_BLACK);   // Chân trời sự kiện
        spr->drawCircle(cx, cy, 19, 0xFDE0);
        break;
      }

      case 47: { // Sao Thổ Chúa Tể Vành Đai 3D
        spr->fillCircle(cx, cy, 20, 0xFDE0);
        spr->drawEllipse(cx, cy, 38, 12, 0xD6BA);
        spr->drawEllipse(cx, cy, 34, 10, 0xCE7F);
        break;
      }

      case 48: { // Mặt Trời Thái Dương Hợp Hạch 3D
        spr->fillCircle(cx, cy, 26, 0xF800);
        spr->fillCircle(cx, cy, 22, 0xFA60);
        spr->fillCircle(cx, cy, 16, TFT_YELLOW);
        break;
      }

      case 49: // Nguyệt Cầu Trăng Tròn Cổ Đại
      default: {
        spr->fillCircle(cx, cy, 26, 0xD6BA);
        spr->fillCircle(cx - 8, cy - 6, 5, 0x94B2); // Hố va chạm
        spr->fillCircle(cx + 10, cy + 4, 7, 0x94B2);
        spr->fillCircle(cx - 4, cy + 12, 4, 0x94B2);
        break;
      }
    }
  }
};
