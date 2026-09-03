#pragma once
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class SpriteRenderer {
public:
  static void drawTheme(LGFX_Sprite* spr, int id, int cx, int cy, float breath, float angle, float scale = 1.0f) {
    if (scale < 0.5f) scale = 0.5f;
    if (scale > 2.2f) scale = 2.2f;
    id = (id >= 0) ? (id % 50) : 0;
    bool blink = (millis() % 3500 < 160);

    switch (id) {
      // -------------------------------------------------------------
      // ID 0: THE HOLY CLAYMORE (EXCALIBUR 1:1 HARDWARE MATCH)
      // -------------------------------------------------------------
      case 0: {
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

      // -------------------------------------------------------------
      // ID 1: YOBAO - BÉ HOA CẢI VÀNG (HUBEI FLOWER FESTIVAL)
      // -------------------------------------------------------------
      case 1: {
        int by = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        // Mũ cánh hoa cải vàng nở 3D
        spr->fillCircle(cx, by - 24, 13, 0xFDE0);
        spr->fillCircle(cx - 18, by - 18, 11, 0xFDE0);
        spr->fillCircle(cx + 18, by - 18, 11, 0xFDE0);
        spr->fillCircle(cx - 24, by - 8, 9, 0xFDE0);
        spr->fillCircle(cx + 24, by - 8, 9, 0xFDE0);
        spr->fillRect(cx - 2, by - 36, 4, 12, 0x2DE4);
        spr->fillCircle(cx + 2, by - 36, 3, 0x56E8);
        // Thân tròn vàng & bụng
        spr->fillRoundRect(cx - 18, by - 12, 36, 32, 10, 0xFDE0);
        spr->fillRoundRect(cx - 14, by - 8, 28, 24, 8, 0xFFE0);
        // Mắt & đốm sáng
        spr->fillCircle(cx - 8, by - 2, 3, 0x4120);
        spr->fillCircle(cx + 8, by - 2, 3, 0x4120);
        spr->drawPixel(cx - 9, by - 3, TFT_WHITE);
        spr->drawPixel(cx + 7, by - 3, TFT_WHITE);
        // Má hồng đào
        spr->fillCircle(cx - 13, by + 4, 4, 0xFCE0);
        spr->fillCircle(cx + 13, by + 4, 4, 0xFCE0);
        // Miệng cười
        spr->drawPixel(cx - 1, by + 4, 0x4120);
        spr->drawPixel(cx, by + 5, 0x4120);
        spr->drawPixel(cx + 1, by + 4, 0x4120);
        // Đóa hoa vàng cầm tay
        spr->fillCircle(cx, by + 14, 6, TFT_YELLOW);
        spr->drawPixel(cx, by + 14, 0xFA60);
        spr->fillRect(cx - 1, by + 19, 2, 8, 0x2DE4);
        break;
      }

      // -------------------------------------------------------------
      // ID 2: RAYA - TINH LINH RỪNG XANH (FOREST HEART)
      // -------------------------------------------------------------
      case 2: {
        int ry = cy + (int)(sinf(angle * 3.0f) * 3.0f);
        // Cánh lá sau lưng
        int lFlap = (int)(sinf(angle * 4.5f) * 3.0f);
        spr->fillTriangle(cx - 16, ry + 2, cx - 28, ry - 14 + lFlap, cx - 12, ry + 12, 0x2DE4);
        spr->fillTriangle(cx + 16, ry + 2, cx + 28, ry - 14 + lFlap, cx + 12, ry + 12, 0x2DE4);
        // Thân xanh mint & tóc lá
        spr->fillRoundRect(cx - 18, ry - 14, 36, 34, 12, lgfx::color565(167, 243, 208));
        spr->fillTriangle(cx - 12, ry - 14, cx, ry - 32, cx + 12, ry - 14, 0x5EEA);
        spr->fillTriangle(cx - 22, ry - 8, cx - 14, ry - 24, cx - 6, ry - 8, 0x5EEA);
        spr->fillTriangle(cx + 6, ry - 8, cx + 14, ry - 24, cx + 22, ry - 8, 0x5EEA);
        // Viền dạ quang neon trắng
        spr->drawFastVLine(cx, ry - 22, 10, TFT_WHITE);
        spr->drawLine(cx - 6, ry - 18, cx - 2, ry - 10, TFT_WHITE);
        spr->drawLine(cx + 6, ry - 18, cx + 2, ry - 10, TFT_WHITE);
        // Mắt chớp
        if (!blink) {
          spr->fillCircle(cx - 8, ry - 4, 4, 0x1082);
          spr->fillCircle(cx + 8, ry - 4, 4, 0x1082);
          spr->drawPixel(cx - 9, ry - 5, TFT_WHITE);
          spr->drawPixel(cx + 7, ry - 5, TFT_WHITE);
        } else {
          spr->drawFastHLine(cx - 11, ry - 4, 6, 0x1082);
          spr->drawFastHLine(cx + 5, ry - 4, 6, 0x1082);
        }
        // Miệng cười tươi & má hồng
        spr->fillRoundRect(cx - 4, ry + 4, 8, 4, 2, 0xF800);
        spr->fillCircle(cx - 12, ry + 3, 3, 0xFBAE);
        spr->fillCircle(cx + 12, ry + 3, 3, 0xFBAE);
        break;
      }

      // -------------------------------------------------------------
      // ID 3: BLOOMY [YOONA] - ONG BẮP CÀY HOA ANH ĐÀO (NXU PROJECT)
      // -------------------------------------------------------------
      case 3: {
        int by = cy + (int)(sinf(angle * 3.5f) * 3.0f);
        // Cánh ong trắng mờ
        int wShimmer = (int)(sinf(angle * 12.0f) * 4.0f);
        spr->fillEllipse(cx - 24, by - 8 + wShimmer, 12, 6, TFT_WHITE);
        spr->fillEllipse(cx + 24, by - 8 - wShimmer, 12, 6, TFT_WHITE);
        // Thân ong vàng tròn
        spr->fillRoundRect(cx - 20, by - 16, 40, 36, 14, 0xFDE0);
        spr->fillRoundRect(cx - 19, by + 4, 38, 7, 3, 0x61A2);
        spr->fillRoundRect(cx - 17, by + 14, 34, 5, 2, 0x61A2);
        // Vòng hoa anh đào pha lê
        const int fX[5] = {-16, -8, 0, 8, 16};
        const int fY[5] = {-4, 2, 5, 2, -4};
        for (int i = 0; i < 5; i++) {
          spr->fillCircle(cx + fX[i], by + fY[i], 4, 0xFCDE);
          spr->drawPixel(cx + fX[i], by + fY[i], TFT_WHITE);
        }
        // Mắt to long lanh
        spr->fillCircle(cx - 8, by - 6, 4, 0x1082);
        spr->fillCircle(cx + 8, by - 6, 4, 0x1082);
        spr->drawPixel(cx - 9, by - 7, TFT_WHITE);
        spr->drawPixel(cx + 7, by - 7, TFT_WHITE);
        spr->fillCircle(cx - 13, by - 1, 3, 0xFBAE);
        spr->fillCircle(cx + 13, by - 1, 3, 0xFBAE);
        break;
      }

      // -------------------------------------------------------------
      // ID 4: EMBER [CHAE-ON] - CÁO LỬA PHA LÊ CÓ CÁNH (NXU PROJECT)
      // -------------------------------------------------------------
      case 4: {
        int fy = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        // Cánh cam thiên thần
        spr->fillTriangle(cx - 14, fy, cx - 34, fy - 16, cx - 14, fy - 22, 0xFB80);
        spr->fillTriangle(cx + 14, fy, cx + 34, fy - 16, cx + 14, fy - 22, 0xFB80);
        // Thân cáo cam & ức trắng
        spr->fillRoundRect(cx - 18, fy - 14, 36, 34, 10, 0xFA60);
        spr->fillRoundRect(cx - 10, fy + 2, 20, 16, 6, TFT_WHITE);
        // Tai cáo nhọn
        spr->fillTriangle(cx - 16, fy - 12, cx - 12, fy - 30, cx - 4, fy - 12, 0x5140);
        spr->fillTriangle(cx + 4, fy - 12, cx + 12, fy - 30, cx + 16, fy - 12, 0x5140);
        // Tinh thể hổ phách trên trán
        spr->fillTriangle(cx - 6, fy - 16, cx, fy - 24, cx + 6, fy - 16, 0xFDE0);
        spr->drawPixel(cx, fy - 24, TFT_WHITE);
        // Mắt & má hồng
        spr->fillCircle(cx - 7, fy - 4, 3, 0x1082);
        spr->fillCircle(cx + 7, fy - 4, 3, 0x1082);
        spr->drawPixel(cx - 8, fy - 5, TFT_WHITE);
        spr->drawPixel(cx + 6, fy - 5, TFT_WHITE);
        spr->fillCircle(cx - 12, fy + 2, 3, 0xFCE0);
        spr->fillCircle(cx + 12, fy + 2, 3, 0xFCE0);
        break;
      }

      // -------------------------------------------------------------
      // ID 5: AURELLE [SEORIN] - SƯ TỬ NHÍ VƯƠNG GIẢ (NXU PROJECT)
      // -------------------------------------------------------------
      case 5: {
        int ly = cy + (int)(sinf(angle * 2.0f) * 2.5f);
        // Bờm hồng đính sao kim cương
        spr->fillCircle(cx, ly, 25, 0xFCDE);
        for (int a = 0; a < 6; a++) {
          float rad = a * 1.047f;
          int sx = cx + (int)(cosf(rad) * 23);
          int sy = ly + (int)(sinf(rad) * 23);
          spr->drawPixel(sx, sy, TFT_WHITE);
        }
        // Khuôn mặt vàng ấm
        spr->fillCircle(cx, ly + 2, 16, 0xFEE0);
        spr->fillTriangle(cx - 6, ly - 18, cx, ly - 26, cx + 6, ly - 18, 0xFDE0);
        spr->drawPixel(cx, ly - 26, TFT_WHITE);
        // Mắt & răng khểnh
        spr->fillCircle(cx - 6, ly + 1, 3, 0x61A2);
        spr->fillCircle(cx + 6, ly + 1, 3, 0x61A2);
        spr->drawPixel(cx - 7, ly, TFT_WHITE);
        spr->drawPixel(cx + 5, ly, TFT_WHITE);
        spr->drawPixel(cx - 3, ly + 8, TFT_WHITE);
        spr->drawPixel(cx + 3, ly + 8, TFT_WHITE);
        spr->fillCircle(cx - 11, ly + 6, 3, 0xFBAE);
        spr->fillCircle(cx + 11, ly + 6, 3, 0xFBAE);
        break;
      }

      // -------------------------------------------------------------
      // ID 6: KAIRO [YISEO] - RỒNG DƠI HỒNG TINH NGHỊCH (NXU PROJECT)
      // -------------------------------------------------------------
      case 6: {
        int ky = cy + (int)(sinf(angle * 2.8f) * 3.0f);
        // Cánh dơi hồng mở rộng
        spr->fillTriangle(cx - 12, ky, cx - 36, ky - 10, cx - 18, ky - 20, 0xFCDE);
        spr->fillTriangle(cx + 12, ky, cx + 36, ky - 10, cx + 18, ky - 20, 0xFCDE);
        // Thân rồng dơi lông hồng
        spr->fillRoundRect(cx - 18, ky - 14, 36, 34, 12, 0xFBAE);
        spr->fillTriangle(cx - 14, ky - 14, cx - 18, ky - 26, cx - 8, ky - 14, 0xFFE0);
        spr->fillTriangle(cx + 8, ky - 14, cx + 18, ky - 26, cx + 14, ky - 14, 0xFFE0);
        // Mắt & răng nanh
        spr->fillCircle(cx - 7, ky - 2, 4, 0x1082);
        spr->fillCircle(cx + 7, ky - 2, 4, 0x1082);
        spr->drawPixel(cx - 8, ky - 3, TFT_WHITE);
        spr->drawPixel(cx + 6, ky - 3, TFT_WHITE);
        spr->drawPixel(cx - 3, ky + 6, TFT_WHITE);
        spr->drawPixel(cx + 3, ky + 6, TFT_WHITE);
        break;
      }

      // -------------------------------------------------------------
      // ID 7: LUMORI - NẤM RỪNG PHÁT QUANG CỔ ĐẠI (LUMORI)
      // -------------------------------------------------------------
      case 7: {
        int my = cy + (int)(sinf(angle * 2.2f) * 2.5f);
        // Mũ ngủ nấm chóp dài màu lam
        spr->fillCircle(cx, my - 14, 20, 0x3CF7);
        spr->fillTriangle(cx - 16, my - 16, cx + 22, my - 34, cx + 14, my - 14, 0x3CF7);
        spr->fillCircle(cx + 22, my - 34, 4, 0xFDE0);
        // Thân trắng & bụng phát sáng xoắn ốc
        spr->fillRoundRect(cx - 16, my - 6, 32, 28, 10, TFT_WHITE);
        spr->fillCircle(cx, my + 10, 7, 0xFDE0);
        spr->drawPixel(cx, my + 10, 0xFA60);
        // Mắt & má hồng
        spr->fillCircle(cx - 7, my + 2, 3, 0x1082);
        spr->fillCircle(cx + 7, my + 2, 3, 0x1082);
        spr->drawPixel(cx - 8, my + 1, TFT_WHITE);
        spr->drawPixel(cx + 6, my + 1, TFT_WHITE);
        spr->fillCircle(cx - 11, my + 6, 2, 0xFCE0);
        spr->fillCircle(cx + 11, my + 6, 2, 0xFCE0);
        break;
      }

      // -------------------------------------------------------------
      // ID 8: LUMIO - NGỌN LỬA VŨ TRỤ TINH NGHỊCH (LUMIO)
      // -------------------------------------------------------------
      case 8: {
        int ly = cy + (int)(sinf(angle * 2.8f) * 3.0f);
        // Mái tóc ngọn lửa gradient hồng - cyan
        spr->fillTriangle(cx - 14, ly - 8, cx, ly - 34, cx + 14, ly - 8, 0xF81F);
        spr->fillTriangle(cx - 10, ly - 8, cx + 2, ly - 32, cx + 10, ly - 8, 0x07FF);
        // Thân áo choàng tím sao đêm
        spr->fillRoundRect(cx - 14, ly - 10, 28, 30, 8, 0x2124);
        spr->fillCircle(cx, ly + 8, 5, 0xFDE0);
        // Mắt xanh sapphire
        spr->fillCircle(cx - 6, ly - 2, 3, 0x07FF);
        spr->fillCircle(cx + 6, ly - 2, 3, 0x07FF);
        spr->drawPixel(cx - 7, ly - 3, TFT_WHITE);
        spr->drawPixel(cx + 5, ly - 3, TFT_WHITE);
        break;
      }

      // -------------------------------------------------------------
      // ID 9: CUTE BUNNY - THỎ HOODIE MINT PASTEL (CUTE BUNNY)
      // -------------------------------------------------------------
      case 9: {
        int by = cy + (int)(sinf(angle * 2.4f) * 3.0f);
        // Tai cọc cạch (hồng & mint)
        spr->fillRoundRect(cx - 14, by - 36, 8, 22, 4, 0xFCDE);
        spr->fillRoundRect(cx + 6, by - 36, 8, 22, 4, 0x87F5);
        // Mũ hoodie mint & mặt trắng
        spr->fillRoundRect(cx - 20, by - 16, 40, 34, 14, 0x87F5);
        spr->fillRoundRect(cx - 14, by - 10, 28, 24, 10, TFT_WHITE);
        // Mắt, mũi hồng, má hồng
        spr->fillCircle(cx - 7, by - 2, 3, 0x1082);
        spr->fillCircle(cx + 7, by - 2, 3, 0x1082);
        spr->drawPixel(cx, by + 1, 0xFBAE);
        spr->fillCircle(cx - 10, by + 4, 3, 0xFBAE);
        spr->fillCircle(cx + 10, by + 4, 3, 0xFBAE);
        break;
      }

      // -------------------------------------------------------------
      // ID 10: STAR SPRITE - BÉ SAO BĂNG ÁO CHOÀNG VÀNG
      // -------------------------------------------------------------
      case 10: {
        int sy = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        spr->fillCircle(cx, sy - 6, 22, 0xFDE0);
        spr->fillRoundRect(cx - 14, sy - 2, 28, 20, 8, 0xFFF2);
        spr->fillCircle(cx - 6, sy + 4, 3, 0x1082);
        spr->fillCircle(cx + 6, sy + 4, 3, 0x1082);
        spr->fillCircle(cx - 10, sy + 8, 2, 0xFCE0);
        spr->fillCircle(cx + 10, sy + 8, 2, 0xFCE0);
        break;
      }

      // -------------------------------------------------------------
      // ID 11: LOTUS FROG - ẾCH XANH ĐỘI LÁ SEN
      // -------------------------------------------------------------
      case 11: {
        int fy = cy + (int)(sinf(angle * 2.0f) * 2.5f);
        spr->fillEllipse(cx, fy - 26, 24, 8, 0x2DE4);
        spr->drawFastVLine(cx + 12, fy - 26, 24, 0x1AE2);
        spr->fillCircle(cx, fy + 6, 18, 0x56E8);
        spr->fillCircle(cx - 10, fy - 8, 6, 0x56E8);
        spr->fillCircle(cx + 10, fy - 8, 6, 0x56E8);
        spr->fillCircle(cx - 10, fy - 8, 3, 0x1082);
        spr->fillCircle(cx + 10, fy - 8, 3, 0x1082);
        spr->drawPixel(cx - 11, fy - 9, TFT_WHITE);
        spr->drawPixel(cx + 9, fy - 9, TFT_WHITE);
        break;
      }

      // -------------------------------------------------------------
      // ID 12: SPORE FAIRY - NẤM HỒNG DẠO PHỐ
      // -------------------------------------------------------------
      case 12: {
        int ny = cy + (int)(sinf(angle * 2.6f) * 3.0f);
        spr->fillCircle(cx, ny - 10, 22, 0xFBAE);
        spr->fillCircle(cx - 10, ny - 16, 3, TFT_WHITE);
        spr->fillCircle(cx + 8, ny - 18, 4, TFT_WHITE);
        spr->fillRoundRect(cx - 12, ny, 24, 20, 8, TFT_WHITE);
        spr->fillCircle(cx - 5, ny + 6, 2, 0x1082);
        spr->fillCircle(cx + 5, ny + 6, 2, 0x1082);
        break;
      }

      // -------------------------------------------------------------
      // ID 13: CLOVER SPROUT - MẦM CÂY MAY MẮN 4 LÁ
      // -------------------------------------------------------------
      case 13: {
        int cy_s = cy + (int)(sinf(angle * 2.2f) * 2.5f);
        // Cỏ 4 lá xoay nhẹ
        int ro = (int)(sinf(angle * 4.0f) * 2.0f);
        spr->fillCircle(cx - 5 + ro, cy_s - 26, 4, 0x2DE4);
        spr->fillCircle(cx + 5 - ro, cy_s - 26, 4, 0x2DE4);
        spr->fillCircle(cx, cy_s - 31, 4, 0x2DE4);
        spr->fillCircle(cx, cy_s - 21, 4, 0x2DE4);
        spr->drawFastVLine(cx, cy_s - 21, 8, 0x1AE2);
        // Thân mầm cây trắng tròn
        spr->fillRoundRect(cx - 16, cy_s - 6, 32, 28, 10, TFT_WHITE);
        spr->fillCircle(cx - 6, cy_s + 2, 3, 0x1082);
        spr->fillCircle(cx + 6, cy_s + 2, 3, 0x1082);
        spr->drawPixel(cx - 7, cy_s + 1, TFT_WHITE);
        spr->drawPixel(cx + 5, cy_s + 1, TFT_WHITE);
        spr->fillCircle(cx - 10, cy_s + 6, 2, 0xFBAE);
        spr->fillCircle(cx + 10, cy_s + 6, 2, 0xFBAE);
        break;
      }

      // -------------------------------------------------------------
      // ID 14: BERRY FOX - CÁO DÂU TÂY NGỌT NGÀO
      // -------------------------------------------------------------
      case 14: {
        int by = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        spr->fillTriangle(cx - 8, by - 24, cx, by - 34, cx + 8, by - 24, 0x2DE4);
        spr->fillRoundRect(cx - 18, by - 16, 36, 34, 12, 0xF800);
        spr->drawPixel(cx - 8, by - 6, TFT_YELLOW);
        spr->drawPixel(cx + 8, by - 6, TFT_YELLOW);
        spr->drawPixel(cx, by + 8, TFT_YELLOW);
        spr->fillCircle(cx - 7, by, 3, TFT_WHITE);
        spr->fillCircle(cx + 7, by, 3, TFT_WHITE);
        spr->fillCircle(cx - 7, by, 2, 0x1082);
        spr->fillCircle(cx + 7, by, 2, 0x1082);
        break;
      }

      // -------------------------------------------------------------
      // ID 15: CLOUD SHEEP - CỪU MÂY BỒNG BỀNH
      // -------------------------------------------------------------
      case 15: {
        int sy = cy + (int)(sinf(angle * 2.0f) * 3.0f);
        spr->fillCircle(cx, sy - 2, 20, 0xCE5F);
        spr->fillCircle(cx - 14, sy - 2, 10, 0xCE5F);
        spr->fillCircle(cx + 14, sy - 2, 10, 0xCE5F);
        spr->fillRoundRect(cx - 10, sy + 2, 20, 16, 6, 0xFFE0);
        spr->fillCircle(cx - 5, sy + 6, 2, 0x1082);
        spr->fillCircle(cx + 5, sy + 6, 2, 0x1082);
        break;
      }

      // -------------------------------------------------------------
      // IDs 16..25: AXOLOTL KỲ NHÔNG KAWAII 2.5D (10 PHÂN LOẠI)
      // -------------------------------------------------------------
      case 16: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 24: case 25: {
        int sub = id - 16;
        int ay = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        uint16_t bodyCol = (sub == 9) ? lgfx::color565(134, 239, 172) : lgfx::color565(255, 175, 195);
        uint16_t gillCol = (sub == 9) ? lgfx::color565(34, 197, 94) : lgfx::color565(255, 105, 150);

        spr->fillRoundRect(cx - 22, ay - 16, 44, 34, 12, bodyCol);
        spr->fillRoundRect(cx - 18, ay - 12, 36, 26, 10, bodyCol + 0x0821);

        int fw = (int)(sinf(angle * 3.5f) * 2.5f);
        spr->fillRoundRect(cx - 32 + fw, ay - 18, 12, 6, 3, gillCol);
        spr->fillRoundRect(cx - 34 + fw, ay - 8, 14, 6, 3, gillCol);
        spr->fillRoundRect(cx - 30 + fw, ay + 2, 10, 5, 2, gillCol);
        spr->fillRoundRect(cx + 20 - fw, ay - 18, 12, 6, 3, gillCol);
        spr->fillRoundRect(cx + 20 - fw, ay - 8, 14, 6, 3, gillCol);
        spr->fillRoundRect(cx + 20 - fw, ay + 2, 10, 5, 2, gillCol);

        if (!blink && sub != 2) {
          spr->fillCircle(cx - 10, ay - 4, 5, 0x18C3);
          spr->fillCircle(cx + 10, ay - 4, 5, 0x18C3);
          spr->fillCircle(cx - 11, ay - 6, 2, TFT_WHITE);
          spr->fillCircle(cx + 9, ay - 6, 2, TFT_WHITE);
        } else {
          spr->drawFastHLine(cx - 14, ay - 4, 8, 0x18C3);
          spr->drawFastHLine(cx + 6, ay - 4, 8, 0x18C3);
        }

        spr->fillCircle(cx - 14, ay + 4, 3, gillCol);
        spr->fillCircle(cx + 14, ay + 4, 3, gillCol);
        spr->drawPixel(cx, ay + 4, 0x8800);

        if (sub == 1) { // Bong bóng
          int by1 = ay - ((millis() / 20) % 50);
          spr->drawCircle(cx + 16, by1, 4, 0x07FF);
        } else if (sub == 3) { // Hoàng tử
          spr->fillTriangle(cx - 8, ay - 20, cx, ay - 28, cx + 8, ay - 20, 0xFDE0);
        } else if (sub == 4) { // Gamer RGB
          spr->drawCircle(cx, ay - 4, 22, 0x07FF);
          spr->fillRect(cx - 24, ay - 9, 4, 10, 0xF81F);
          spr->fillRect(cx + 20, ay - 9, 4, 10, 0xF81F);
        } else if (sub == 6) { // Thiên sứ
          spr->drawCircle(cx, ay - 22, 10, 0xFDE0);
        }
        break;
      }

      // -------------------------------------------------------------
      // IDs 26..39: THÚ CƯNG ĐÁNG YÊU & LÃNG MẠN (14 TÁC PHẨM ĐỘC BẢN)
      // -------------------------------------------------------------
      case 26: { // Mèo Ba Tư Hoàng Đế (Heterochromia)
        int my = cy + (int)(sinf(angle * 2.0f) * 2.5f);
        spr->fillRoundRect(cx - 20, my - 14, 40, 32, 12, TFT_WHITE);
        spr->fillTriangle(cx - 18, my - 12, cx - 12, my - 26, cx - 4, my - 12, TFT_WHITE);
        spr->fillTriangle(cx + 4, my - 12, cx + 12, my - 26, cx + 18, my - 12, TFT_WHITE);
        spr->fillCircle(cx - 8, my - 2, 4, 0x07FF); // Mắt xanh
        spr->fillCircle(cx + 8, my - 2, 4, 0xFDE0); // Mắt vàng
        spr->drawPixel(cx - 9, my - 3, TFT_WHITE);
        spr->drawPixel(cx + 7, my - 3, TFT_WHITE);
        spr->fillCircle(cx, my + 16, 4, 0xF800);
        break;
      }

      case 27: { // Mèo Tam Thể Nữ Hoàng
        int my = cy + (int)(sinf(angle * 2.0f) * 2.5f);
        spr->fillRoundRect(cx - 20, my - 14, 40, 32, 12, TFT_WHITE);
        spr->fillCircle(cx - 10, my - 8, 8, 0xFA60);
        spr->fillCircle(cx + 10, my - 8, 8, 0x2124);
        spr->drawFastHLine(cx - 13, my - 2, 6, TFT_BLACK);
        spr->drawFastHLine(cx + 7, my - 2, 6, TFT_BLACK);
        break;
      }

      case 28: { // Mèo Thần Tài Maneki Neko (Vẫy tay 60 FPS)
        int my = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillRoundRect(cx - 18, my - 14, 36, 32, 10, TFT_WHITE);
        spr->drawFastHLine(cx - 12, my - 2, 5, TFT_BLACK);
        spr->drawFastHLine(cx + 7, my - 2, 5, TFT_BLACK);
        int wWave = (int)(sinf(angle * 8.0f) * 5.0f);
        spr->fillRoundRect(cx - 24, my - 2 + wWave, 8, 16, 4, TFT_WHITE);
        spr->fillCircle(cx, my + 16, 4, 0xFDE0);
        break;
      }

      case 29: { // Mèo Con Trong Hộp Giấy Cạc-tông
        int ky = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillRoundRect(cx - 22, ky, 44, 28, 4, 0xB482);
        spr->drawRoundRect(cx - 22, ky, 44, 28, 4, 0x82C0);
        spr->fillRoundRect(cx - 16, ky - 14, 32, 20, 8, 0xFA60);
        spr->fillCircle(cx - 7, ky - 4, 3, 0x1082);
        spr->fillCircle(cx + 7, ky - 4, 3, 0x1082);
        spr->drawPixel(cx - 8, ky - 5, TFT_WHITE);
        spr->drawPixel(cx + 6, ky - 5, TFT_WHITE);
        break;
      }

      case 30: { // Shiba Inu Má Bánh Bao
        int sy = cy + (int)(sinf(angle * 2.2f) * 2.5f);
        spr->fillRoundRect(cx - 22, sy - 14, 44, 32, 12, 0xFA60);
        spr->fillCircle(cx - 12, sy + 4, 8, TFT_WHITE);
        spr->fillCircle(cx + 12, sy + 4, 8, TFT_WHITE);
        spr->fillCircle(cx - 8, sy - 4, 3, 0x1082);
        spr->fillCircle(cx + 8, sy - 4, 3, 0x1082);
        spr->fillCircle(cx, sy + 2, 2, 0x1082);
        // Đuôi cuộn lắc lư
        int tw = (int)(sinf(angle * 6.0f) * 4.0f);
        spr->fillCircle(cx + 20, sy - 8 + tw, 6, 0xFA60);
        break;
      }

      case 31: { // Corgi Mông Trái Tim
        int cy_c = cy + (int)(sinf(angle * 2.5f) * 2.5f);
        spr->fillCircle(cx, cy_c + 4, 18, 0xFA60);
        spr->fillCircle(cx - 4, cy_c + 4, 8, TFT_WHITE);
        spr->fillCircle(cx + 4, cy_c + 4, 8, TFT_WHITE);
        spr->fillTriangle(cx - 10, cy_c + 6, cx, cy_c + 16, cx + 10, cy_c + 6, TFT_WHITE);
        break;
      }

      case 32: { // Thỏ Mặt Trăng Ngọc Thỏ (Giã mochi)
        int ty = cy + (int)(sinf(angle * 2.2f) * 2.5f);
        spr->fillRoundRect(cx - 14, ty - 28, 6, 18, 3, TFT_WHITE);
        spr->fillRoundRect(cx + 8, ty - 28, 6, 18, 3, TFT_WHITE);
        spr->fillRoundRect(cx - 16, ty - 12, 32, 26, 10, TFT_WHITE);
        spr->fillCircle(cx - 6, ty - 2, 2, 0xF800);
        spr->fillCircle(cx + 6, ty - 2, 2, 0xF800);
        spr->fillRect(cx + 14, ty + 4, 16, 14, 0x82C0);
        break;
      }

      case 33: { // Gấu Trúc Gặm Trúc Non
        int py = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillRoundRect(cx - 18, py - 14, 36, 32, 10, TFT_WHITE);
        spr->fillCircle(cx - 14, py - 14, 5, 0x1082);
        spr->fillCircle(cx + 14, py - 14, 5, 0x1082);
        spr->fillCircle(cx - 7, py - 2, 4, 0x1082);
        spr->fillCircle(cx + 7, py - 2, 4, 0x1082);
        spr->drawPixel(cx - 7, py - 2, TFT_WHITE);
        spr->drawPixel(cx + 7, py - 2, TFT_WHITE);
        spr->fillRect(cx - 2, py, 4, 20, 0x2DE4);
        break;
      }

      case 34: { // Chim Cánh Cụt Khăn Len Đỏ
        int cy_p = cy + (int)(sinf(angle * 2.4f) * 2.5f);
        spr->fillRoundRect(cx - 16, cy_p - 14, 32, 32, 12, 0x10A2);
        spr->fillRoundRect(cx - 10, cy_p - 8, 20, 24, 8, TFT_WHITE);
        spr->fillRect(cx - 16, cy_p + 4, 32, 6, 0xF800);
        spr->fillCircle(cx - 5, cy_p - 4, 2, 0x1082);
        spr->fillCircle(cx + 5, cy_p - 4, 2, 0x1082);
        spr->fillTriangle(cx - 3, cy_p, cx, cy_p + 3, cx + 3, cy_p, 0xFDE0);
        break;
      }

      case 35: { // Rái Cá Biển Nắm Tay (Ôm đá cuội)
        int oy = cy + (int)(sinf(angle * 2.0f) * 2.5f);
        spr->fillRoundRect(cx - 18, oy - 12, 36, 28, 10, 0x61A2);
        spr->fillRoundRect(cx - 12, oy - 6, 24, 20, 8, 0xD6BA);
        spr->fillCircle(cx - 6, oy - 2, 2, 0x1082);
        spr->fillCircle(cx + 6, oy - 2, 2, 0x1082);
        spr->drawPixel(cx - 7, oy - 3, TFT_WHITE);
        spr->drawPixel(cx + 5, oy - 3, TFT_WHITE);
        spr->fillCircle(cx, oy + 8, 5, 0xCE7F); // Hòn đá cuội
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
        spr->fillTriangle(cx - 3, uy - 12, cx, uy - 28, cx + 3, uy - 12, 0xFDE0);
        spr->fillCircle(cx - 6, uy - 2, 3, 0xFCDE);
        spr->fillCircle(cx + 6, uy - 2, 3, 0xFCDE);
        break;
      }

      case 38: { // Đôi Mèo Uyên Ương Lãng Mạn
        int my = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillCircle(cx - 8, my, 12, TFT_WHITE);
        spr->fillCircle(cx + 8, my, 12, 0x1082);
        spr->drawCircle(cx, my - 14, 6, 0xF800);
        break;
      }

      case 39: { // Cún Cứu Hộ Saint Bernard
        int by = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillRoundRect(cx - 20, by - 14, 40, 32, 10, 0x8240);
        spr->fillRoundRect(cx - 12, by - 6, 24, 24, 8, TFT_WHITE);
        spr->fillRect(cx - 6, by + 14, 12, 8, 0x61A2);
        break;
      }

      // -------------------------------------------------------------
      // IDs 40..49: ĐỊA CẦU & THIÊN VĂN 3D
      // -------------------------------------------------------------
      case 40: { // Quỹ Đạo ISS Blue Marble 3D
        spr->fillCircle(cx, cy, 36, lgfx::color565(0, 70, 180));
        spr->fillCircle(cx, cy, 33, lgfx::color565(0, 140, 255));
        spr->fillCircle(cx, cy, 30, lgfx::color565(0, 220, 255));
        spr->fillCircle(cx, cy, 28, lgfx::color565(8, 32, 75));
        int dX = (int)(angle * 8.0f) % 60;
        spr->fillEllipse(cx - 18 + dX - 30, cy - 6, 12, 8, lgfx::color565(25, 115, 55));
        spr->fillEllipse(cx + 10 + dX - 30, cy + 8, 14, 7, lgfx::color565(30, 135, 65));
        spr->fillCircle(cx + 20, cy - 16, 3, TFT_WHITE);
        spr->drawFastHLine(cx + 12, cy - 16, 16, 0xFFE0);
        spr->drawFastVLine(cx + 20, cy - 24, 16, 0xFFE0);
        break;
      }

      case 41: { // Bão Xoáy Nam Cực
        spr->fillCircle(cx, cy, 32, lgfx::color565(8, 32, 75));
        for (int a = 0; a < 4; a++) {
          float rad = a * 1.57f + angle * 2.0f;
          spr->drawEllipse(cx + (int)(cosf(rad)*8), cy + (int)(sinf(rad)*8), 16, 8, TFT_WHITE);
        }
        break;
      }

      case 42: { // Mariana Bioluminescence
        spr->fillRect(cx - 24, cy + 12, 48, 20, 0x05DF);
        spr->fillCircle(cx - 12, cy + 6, 8, 0xF81F);
        spr->fillCircle(cx + 12, cy + 4, 10, 0x07FF);
        break;
      }

      case 43: { // Sahara Sunset
        spr->fillCircle(cx, cy - 10, 18, 0xF800);
        spr->fillTriangle(cx - 36, cy + 28, cx, cy + 8, cx + 36, cy + 28, 0xFDE0);
        break;
      }

      case 44: { // Amazon Rainforest
        spr->fillCircle(cx - 14, cy + 8, 16, 0x1AE2);
        spr->fillCircle(cx + 14, cy + 6, 18, 0x1AE2);
        spr->fillRoundRect(cx - 20, cy - 4, 40, 8, 4, TFT_WHITE);
        break;
      }

      case 45: { // Aurora
        for (int x = -28; x <= 28; x += 4) {
          int ay = cy - 10 + (int)(sinf(angle * 3.0f + x * 0.1f) * 12.0f);
          spr->drawFastVLine(cx + x, ay, 18, 0x07E0);
        }
        break;
      }

      case 46: { // Gargantua Black Hole
        spr->drawEllipse(cx, cy, 40, 12, 0xFDE0);
        spr->fillCircle(cx, cy, 18, TFT_BLACK);
        spr->drawCircle(cx, cy, 19, 0xFDE0);
        break;
      }

      case 47: { // Saturn 3D
        spr->fillCircle(cx, cy, 20, 0xFDE0);
        spr->drawEllipse(cx, cy, 38, 12, 0xD6BA);
        spr->drawEllipse(cx, cy, 34, 10, 0xCE7F);
        break;
      }

      case 48: { // Sun Plasma
        spr->fillCircle(cx, cy, 26, 0xF800);
        spr->fillCircle(cx, cy, 22, 0xFA60);
        spr->fillCircle(cx, cy, 16, TFT_YELLOW);
        break;
      }

      case 49: default: { // Moon Craters
        spr->fillCircle(cx, cy, 26, 0xD6BA);
        spr->fillCircle(cx - 8, cy - 6, 5, 0x94B2);
        spr->fillCircle(cx + 10, cy + 4, 7, 0x94B2);
        spr->fillCircle(cx - 4, cy + 12, 4, 0x94B2);
        break;
      }
    }
  }
};
