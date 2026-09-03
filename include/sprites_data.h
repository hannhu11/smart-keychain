#pragma once
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class SpriteRenderer {
public:
  static void drawTheme(LGFX_Sprite* spr, int id, int cx, int cy, float breath, float angle) {
    id = (id >= 0) ? (id % 250) : 0;

    // =========================================================================
    // TRƯỜNG HỢP ĐẶC BIỆT: THE HOLY CLAYMORE 1:1 (ID 0 & ID 12 - KHỚP ẢNH MÓC KHÓA THẬT)
    // =========================================================================
    if (id == 0 || id == 12) {
      // 1. Dynamic Contact Shadow dưới chân kiếm (Bóng tiếp xúc mặt sàn)
      int shadowW = 32 - (int)(sinf(angle * 2.5f) * 4.0f);
      spr->fillEllipse(cx, cy + 54, shadowW, 6, lgfx::color565(5, 10, 20));

      // 2. Tọa độ xoay 45 độ chuẩn xác không rung lắc
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

      // TẦNG 1: LƯỚI HÀO QUANG AURA TRẮNG BẢO VỆ
      const int outBlade[5][2] = {{-16, -18}, {52, -18}, {66, 0}, {52, 18}, {-16, 18}};
      const int outGuard[4][2] = {{-26, -30}, {-16, -30}, {-16, 30}, {-26, 30}};
      const int outGrip[4][2]  = {{-50, -7},  {-26, -7},  {-26, 7},  {-50, 7}};
      const int outPom[5][2]   = {{-62, -12}, {-48, -12}, {-48, 12}, {-62, 12}, {-66, 0}};
      dPoly(outBlade, 5, TFT_WHITE);
      dPoly(outGuard, 4, TFT_WHITE);
      dPoly(outGrip, 4, TFT_WHITE);
      dPoly(outPom, 5, TFT_WHITE);

      // TẦNG 2: VIỀN NĂNG LƯỢNG CYAN NEON PHÁT QUANG
      const int cyBlade[5][2] = {{-15, -15}, {50, -15}, {62, 0}, {50, 15}, {-15, 15}};
      const int cyGuard[4][2] = {{-24, -27}, {-17, -27}, {-17, 27}, {-24, 27}};
      dPoly(cyBlade, 5, 0x07FF);
      dPoly(cyGuard, 4, 0x07FF);

      // TẦNG 3: LƯỠI THÉP XANH SẪM VÁT BEVEL 3D
      const int inBlade[5][2] = {{-14, -10}, {46, -10}, {54, 0}, {46, 10}, {-14, 10}};
      dPoly(inBlade, 5, 0x29B5);

      // TẦNG 4: SỐNG KIẾM BẠC & RÃNH RUNE KIM CƯƠNG PHÁT SÁNG
      spr->drawLine(tX(-12, 0), tY(-12, 0), tX(48, 0), tY(48, 0), TFT_WHITE);
      const int runes[3] = {-4, 14, 30};
      for (int ru : runes) {
        const int rPts[4][2] = {{ru - 3, 0}, {ru, -4}, {ru + 3, 0}, {ru, 4}};
        dPoly(rPts, 4, TFT_WHITE);
      }

      // TẦNG 5: TRÁI TIM NĂNG LƯỢNG ĐỐC KIẾM & CHUÔI CẦM
      const int cDiamondOut[4][2] = {{-22, -6}, {-17, 0}, {-22, 6}, {-27, 0}};
      const int cDiamondIn[4][2]  = {{-22, -3}, {-19, 0}, {-22, 3}, {-25, 0}};
      dPoly(cDiamondOut, 4, TFT_WHITE);
      dPoly(cDiamondIn, 4, 0x07FF);

      // Chuôi cầm bọc da thép & Pommel
      const int inGrip[4][2] = {{-48, -4}, {-26, -4}, {-26, 4}, {-48, 4}};
      dPoly(inGrip, 4, 0x10A2);
      const int inPom[4][2] = {{-58, -8}, {-50, -8}, {-50, 8}, {-58, 8}};
      const int inPomGem[4][2] = {{-56, -4}, {-52, -4}, {-52, 4}, {-56, 4}};
      dPoly(inPom, 4, 0x07FF);
      dPoly(inPomGem, 4, TFT_WHITE);
      return;
    }

    // =========================================================================
    // NHÓM 1: THÁNH KHÍ & VŨ KHÍ THẦN THOẠI (IDs 0..49)
    // =========================================================================
    if (id < 50) {
      int sub = id;
      // Dynamic Contact Shadow
      spr->fillEllipse(cx, cy + 48, 28, 5, lgfx::color565(8, 12, 22));

      if (sub < 20) {
        // 0-19: CÁC THÁNH KIẾM (Clarent, Dáinsleif, Gram, Kusanagi, Tyrfing...)
        int bx = cx - 16, by = cy - 20;
        // Vòng hào quang phát sáng
        spr->drawCircle(cx, cy - 4, 28 + (int)(breath * 3.0f), 0x07FF);
        // Lưỡi kiếm bạc vát 3D
        spr->fillTriangle(bx, by, bx + 36, by - 36, bx + 12, by + 12, TFT_WHITE);
        spr->fillTriangle(bx + 36, by - 36, bx + 42, by - 30, bx + 12, by + 12, 0xCE7F);
        // Rãnh rune phát quang màu riêng biệt cho từng thanh kiếm
        uint16_t runeCol = (sub % 4 == 0) ? 0x07FF : ((sub % 4 == 1) ? 0xF800 : ((sub % 4 == 2) ? 0x981F : 0x07E0));
        spr->drawLine(bx + 4, by - 4, bx + 32, by - 32, runeCol);
        // Đốc kiếm mạ vàng Kinpaku
        spr->fillRoundRect(bx - 6, by + 10, 18, 6, 2, 0xFDE0);
        spr->fillRect(bx - 12, by + 16, 8, 14, 0x2124);
        spr->fillCircle(bx - 14, by + 32, 4, 0xFDE0); // Ngọc chuôi
        // Hạt ánh sáng kim cương chạy dọc lưỡi
        int sh = (int)(angle * 16.0f) % 35;
        spr->drawPixel(bx + sh, by - sh, TFT_WHITE);
      } else if (sub < 30) {
        // 20-29: CÁC THẦN CUNG (Fail-Not, Gandiva, Pinaka, Cung Mặt Trời, Cung Mặt Trăng...)
        spr->drawEllipse(cx, cy, 14, 38, 0xFDE0);
        spr->drawEllipse(cx - 2, cy, 12, 36, 0xD6BA);
        spr->drawLine(cx - 10, cy - 36, cx - 10, cy + 36, TFT_WHITE); // Dây cung
        spr->drawLine(cx - 24, cy, cx + 24, cy, 0x07FF); // Mũi tên photon
        spr->fillTriangle(cx + 24, cy, cx + 18, cy - 4, cx + 18, cy + 4, 0x07FF);
        spr->drawCircle(cx, cy, 8 + (int)(breath * 3.0f), 0x07FF);
      } else if (sub < 40) {
        // 30-39: CÁC THẦN THƯƠNG & GIÁO (Gungnir, Rhongomyniad, Gáe Bulg, Longinus...)
        spr->drawLine(cx - 30, cy + 30, cx + 30, cy - 30, 0x52AA);
        spr->fillTriangle(cx + 18, cy - 18, cx + 38, cy - 38, cx + 28, cy - 16, TFT_WHITE);
        spr->fillTriangle(cx + 18, cy - 18, cx + 38, cy - 38, cx + 16, cy - 28, 0x07FF);
        int fy = (int)(sinf(angle * 4.0f) * 4.0f);
        spr->fillTriangle(cx + 16, cy - 16, cx + 10, cy - 10 + fy, cx + 12, cy - 4, 0xF800); // Lụa đỏ
      } else if (sub < 45) {
        // 40-44: KHIÊN THẦN (Aegis, Svalinn, Ancile...)
        spr->fillRoundRect(cx - 22, cy - 26, 44, 52, 10, 0x2145);
        spr->drawRoundRect(cx - 22, cy - 26, 44, 52, 10, 0xFDE0);
        spr->drawRoundRect(cx - 18, cy - 22, 36, 44, 8, 0x07FF);
        spr->fillCircle(cx, cy, 10, 0xFDE0);
        spr->drawCircle(cx, cy, 8, 0xF800);
        spr->drawCircle(cx, cy, 32 + (int)(breath * 4.0f), 0x07FF);
      } else {
        // 45-49: THÁNH TÍCH (Chén Thánh San Greal, Hòm Bia Giao Ước...)
        spr->fillRoundRect(cx - 16, cy - 16, 32, 20, 6, 0xFDE0);
        spr->fillRect(cx - 4, cy + 4, 8, 16, 0xFDE0);
        spr->fillRoundRect(cx - 14, cy + 20, 28, 6, 2, 0xFDE0);
        spr->fillRoundRect(cx - 12, cy - 14, 24, 10, 3, 0xF800);
        for (int r = 0; r < 4; r++) {
          int ry = cy - 22 - r * 6;
          spr->drawFastHLine(cx - 8 + r * 2, ry, 16 - r * 4, TFT_WHITE);
        }
      }
      return;
    }

    // =========================================================================
    // NHÓM 2: CƠ GIÁP CYBER & KHÔNG GIAN (IDs 50..99)
    // =========================================================================
    if (id >= 50 && id < 100) {
      int sub = id - 50;
      // Dynamic Contact Shadow
      spr->fillEllipse(cx, cy + 46, 32, 5, lgfx::color565(6, 16, 26));

      if (sub < 15) {
        // 50-64: PHÁO RAY ĐIỆN TỪ SONG NÒNG & HUYẾT ĐAO CAO TẦN MURASAMA
        // Khung tháp pháo nòng đôi
        spr->fillRect(cx - 24, cy - 9, 48, 5, 0x31A6);
        spr->fillRect(cx - 24, cy + 4, 48, 5, 0x31A6);
        // Cuộn cảm ứng từ phát quang
        for (int c = 0; c < 5; c++) {
          spr->fillRect(cx - 18 + c * 8, cy - 7, 4, 14, 0x07FF);
        }
        // Tia hồ quang điện phóng ở giữa 2 nòng
        spr->drawLine(cx - 16, cy, cx + 22, cy, TFT_WHITE);
        // Quả cầu plasma ở đầu nòng nạp năng lượng
        spr->fillCircle(cx + 26, cy, 7 + (int)(breath * 3.0f), 0x07FF);
        spr->fillCircle(cx + 26, cy, 3, TFT_WHITE);
      } else if (sub < 30) {
        // 65-79: TACTICAL RADAR HUD & LA BÀN THIÊN HÀ
        // 3 vòng tròn HUD chiến thuật
        spr->drawCircle(cx, cy, 14, 0x07FF);
        spr->drawCircle(cx, cy, 26, 0x05DF);
        spr->drawCircle(cx, cy, 36, 0x035B);
        // Tia quét Radar xoay tròn 60 FPS
        float sw = angle * 2.8f;
        spr->drawLine(cx, cy, cx + (int)(cosf(sw) * 36.0f), cy + (int)(sinf(sw) * 36.0f), 0x07FF);
        // 3 mục tiêu nhấp nháy
        spr->fillCircle(cx + 16, cy - 12, 2, 0xF800);
        spr->fillCircle(cx - 18, cy + 14, 2, 0x07E0);
        spr->fillCircle(cx + 10, cy + 18, 2, 0xFDE0);
        // Khung ngắm mục tiêu [ + ]
        spr->drawRect(cx - 6, cy - 6, 12, 12, TFT_WHITE);
        spr->drawFastHLine(cx - 10, cy, 20, 0x07FF);
        spr->drawFastVLine(cx, cy - 10, 20, 0x07FF);
      } else {
        // 80-99: DRONE TRINH SÁT NANITE & KHIÊN LỤC GIÁC
        int dy = (int)(sinf(angle * 3.0f) * 3.0f);
        spr->fillRoundRect(cx - 18, cy - 10 + dy, 36, 20, 6, 0x2124);
        spr->drawRoundRect(cx - 18, cy - 10 + dy, 36, 20, 6, 0x07FF);
        spr->fillCircle(cx, cy + dy, 5, 0x07FF);
        spr->drawPixel(cx, cy + dy, TFT_WHITE);
        spr->fillRect(cx - 24, cy - 12 + dy, 6, 4, 0x05DF);
        spr->fillRect(cx + 18, cy - 12 + dy, 6, 4, 0x05DF);
        spr->fillRect(cx - 24, cy + 8 + dy, 6, 4, 0x05DF);
        spr->fillRect(cx + 18, cy + 8 + dy, 6, 4, 0x05DF);
        spr->drawCircle(cx, cy + dy, 30 + (int)(breath * 3.0f), 0x07FF);
      }
      return;
    }

    // =========================================================================
    // NHÓM 3: THÚ CƯNG PIXEL & ANIME KAWAII (IDs 100..149)
    // =========================================================================
    if (id >= 100 && id < 150) {
      int sub = id - 100;
      // Dynamic Contact Shadow co giãn theo nhịp bay
      int shadowW = 28 - (int)(sinf(angle * 2.5f) * 4.0f);
      spr->fillEllipse(cx, cy + 44, shadowW, 6, lgfx::color565(12, 10, 16));

      if (sub < 15) {
        // 100-114: CÁC LOẠI AXOLOTL KỲ NHÔNG KAWAII (Hồng đào, thổi bong bóng, game thủ, ramen...)
        int ay = cy + (int)(sinf(angle * 2.5f) * 3.0f);

        // 1. Thân Axolotl tròn bầu bĩnh hồng phấn 2.5D
        spr->fillRoundRect(cx - 22, ay - 16, 44, 34, 12, lgfx::color565(255, 175, 195));
        spr->fillRoundRect(cx - 18, ay - 12, 36, 26, 10, lgfx::color565(255, 195, 210)); // Lưng 3D sáng

        // 2. Cặp mang tai xòe 3 nhánh mỗi bên ve vẩy theo nhịp thở hữu cơ
        int fw = (int)(sinf(angle * 3.5f) * 2.5f);
        // Mang trái
        spr->fillRoundRect(cx - 32 + fw, ay - 18, 12, 6, 3, lgfx::color565(255, 105, 150));
        spr->fillRoundRect(cx - 34 + fw, ay - 8, 14, 6, 3, lgfx::color565(255, 105, 150));
        spr->fillRoundRect(cx - 30 + fw, ay + 2, 10, 5, 2, lgfx::color565(255, 105, 150));
        // Mang phải
        spr->fillRoundRect(cx + 20 - fw, ay - 18, 12, 6, 3, lgfx::color565(255, 105, 150));
        spr->fillRoundRect(cx + 20 - fw, ay - 8, 14, 6, 3, lgfx::color565(255, 105, 150));
        spr->fillRoundRect(cx + 20 - fw, ay + 2, 10, 5, 2, lgfx::color565(255, 105, 150));

        // 3. Cửa sổ chớp mắt sinh học chu kỳ 3.5s
        bool blink = ((millis() % 3500) < 160);
        if (!blink) {
          spr->fillCircle(cx - 10, ay - 4, 5, 0x18C3);
          spr->fillCircle(cx + 10, ay - 4, 5, 0x18C3);
          spr->fillCircle(cx - 11, ay - 6, 2, TFT_WHITE); // Highlight sao 1
          spr->fillCircle(cx + 9, ay - 6, 2, TFT_WHITE);
          spr->drawPixel(cx - 9, ay - 2, TFT_WHITE);      // Highlight sao 2
          spr->drawPixel(cx + 11, ay - 2, TFT_WHITE);
        } else {
          spr->drawFastHLine(cx - 14, ay - 4, 8, 0x18C3);
          spr->drawFastHLine(cx + 6, ay - 4, 8, 0x18C3);
        }

        // 4. Má hồng phúng phính & miệng cười ngọt ngào
        spr->fillCircle(cx - 14, ay + 4, 3, lgfx::color565(255, 120, 150));
        spr->fillCircle(cx + 14, ay + 4, 3, lgfx::color565(255, 120, 150));
        spr->drawPixel(cx - 1, ay + 4, 0x8800);
        spr->drawPixel(cx, ay + 5, 0x8800);
        spr->drawPixel(cx + 1, ay + 4, 0x8800);

        // 5. Bong bóng nước nổi lên xung quanh
        int b1y = ay + 24 - ((millis() / 20) % 70);
        int b2y = ay + 36 - (((millis() + 400) / 25) % 80);
        spr->drawCircle(cx + 24, b1y, 4, 0xCE7F);
        spr->drawPixel(cx + 23, b1y - 1, TFT_WHITE);
        spr->drawCircle(cx - 26, b2y, 3, 0xCE7F);

        // 6. Phụ kiện độc bản cho từng theme Axolotl
        if (sub == 3) {
          // Hoàng Tử: Vương miện vàng
          spr->fillTriangle(cx - 8, ay - 20, cx, ay - 27, cx + 8, ay - 20, 0xFDE0);
        } else if (sub == 5) {
          // Game Thủ: Tai nghe neon
          spr->drawCircle(cx, ay - 4, 22, 0x07FF);
          spr->fillRect(cx - 24, ay - 9, 4, 10, 0xF81F);
          spr->fillRect(cx + 20, ay - 9, 4, 10, 0xF81F);
        }
      } else if (sub < 30) {
        // 115-129: MÈO HOÀNG GIA & MANEKI NEKO
        int my = cy + (int)(sinf(angle * 2.0f) * 2.0f);
        spr->fillRoundRect(cx - 20, my - 14, 40, 30, 10, TFT_WHITE);
        spr->fillTriangle(cx - 18, my - 12, cx - 12, my - 26, cx - 4, my - 12, TFT_WHITE);
        spr->fillTriangle(cx - 16, my - 12, cx - 12, my - 22, cx - 6, my - 12, lgfx::color565(255, 180, 200));
        spr->fillTriangle(cx + 4, my - 12, cx + 12, my - 26, cx + 18, my - 12, TFT_WHITE);
        spr->fillTriangle(cx + 6, my - 12, cx + 12, my - 22, cx + 16, my - 12, lgfx::color565(255, 180, 200));
        spr->drawFastHLine(cx - 13, my - 2, 6, TFT_BLACK);
        spr->drawFastHLine(cx + 7, my - 2, 6, TFT_BLACK);
        spr->drawFastHLine(cx - 26, my + 2, 6, 0x94B2);
        spr->drawFastHLine(cx + 20, my + 2, 6, 0x94B2);
        spr->fillCircle(cx, my + 16, 4, 0xFDE0); // Chuông vàng
      } else {
        // 130-149: RỒNG CON & TINH LINH KODAMA
        int ry = cy + (int)(sinf(angle * 2.5f) * 3.0f);
        spr->fillCircle(cx, ry, 20, lgfx::color565(110, 190, 255));
        spr->fillCircle(cx - 7, ry - 3, 4, 0x10A2);
        spr->fillCircle(cx + 7, ry - 3, 4, 0x10A2);
        spr->fillCircle(cx - 8, ry - 5, 2, TFT_WHITE);
        spr->fillCircle(cx + 6, ry - 5, 2, TFT_WHITE);
        // Cánh rồng nhỏ vỗ
        int wFlap = (int)(sinf(angle * 6.0f) * 3.0f);
        spr->fillTriangle(cx - 18, ry - 2, cx - 28, ry - 12 + wFlap, cx - 14, ry + 6, lgfx::color565(90, 150, 230));
        spr->fillTriangle(cx + 18, ry - 2, cx + 28, ry - 12 + wFlap, cx + 14, ry + 6, lgfx::color565(90, 150, 230));
      }
      return;
    }

    // =========================================================================
    // NHÓM 4: BỐI CẢNH TRÁI ĐẤT & THIÊN VĂN 3D (IDs 150..199)
    // =========================================================================
    if (id >= 150 && id < 200) {
      int sub = id - 150;
      if (sub < 25) {
        // 150-174: ĐỊA CẦU XANH QUỸ ĐẠO ISS 3D (3D Volumetric Blue Marble)
        // Vành khí quyển tán xạ Rayleigh xanh ngọc rực rỡ
        spr->fillCircle(cx, cy, 36, lgfx::color565(0, 70, 180));
        spr->fillCircle(cx, cy, 33, lgfx::color565(0, 140, 255));
        spr->fillCircle(cx, cy, 30, lgfx::color565(0, 220, 255)); // Vành ngọc sáng
        spr->fillCircle(cx, cy, 28, lgfx::color565(8, 32, 75));   // Đáy đại dương sâu
        // Mảng lục địa xanh rừng trôi dạt 3D
        int dX = (int)(angle * 8.0f) % 60;
        spr->fillEllipse(cx - 18 + dX - 30, cy - 6, 12, 8, lgfx::color565(25, 115, 55));
        spr->fillEllipse(cx + 10 + dX - 30, cy + 8, 14, 7, lgfx::color565(30, 135, 65));
        // Đốm nắng bình minh lóe sáng
        spr->fillCircle(cx + 20, cy - 16, 3, TFT_WHITE);
        spr->drawFastHLine(cx + 12, cy - 16, 16, 0xFFE0);
        spr->drawFastVLine(cx + 20, cy - 24, 16, 0xFFE0);
      } else {
        // 175-199: HỐ ĐEN GARGANTUA & SAO THỔ VÀNH ĐAI 3D
        // Quả cầu hành tinh
        spr->fillCircle(cx, cy, 22, lgfx::color565(220, 180, 120));
        // Đĩa vành đai nghiêng 3D
        spr->drawEllipse(cx, cy, 40, 14, 0xFDE0);
        spr->drawEllipse(cx, cy, 36, 11, 0xD6BA);
        spr->drawEllipse(cx, cy, 32, 8, 0xCE7F);
        // Vệt sáng vành đai
        spr->drawPixel(cx - 36, cy, TFT_WHITE);
        spr->drawPixel(cx + 36, cy, TFT_WHITE);
      }
      return;
    }

    // =========================================================================
    // NHÓM 5: LÕI NĂNG LƯỢNG PLASMA & MA TRẬN CYBER (IDs 200..249)
    // =========================================================================
    if (id >= 200 && id < 250) {
      int sub = id - 200;
      if (sub < 25) {
        // 200-224: LÕI HỢP HẠCH TOKAMAK NÉN TỪ TRƯỜNG TORUS
        spr->drawCircle(cx, cy, 28, 0xFDE0);
        spr->drawCircle(cx, cy, 20, 0x07FF);
        spr->drawCircle(cx, cy, 12, 0xF800);
        spr->fillCircle(cx, cy, 6 + (int)(breath * 3.0f), TFT_WHITE);
        // 8 chấu từ trường cố định
        for (int a = 0; a < 8; a++) {
          float rad = a * 0.785398f + angle * 2.0f;
          spr->drawLine(cx + (int)(cosf(rad)*14), cy + (int)(sinf(rad)*14), cx + (int)(cosf(rad)*28), cy + (int)(sinf(rad)*28), 0x07FF);
        }
      } else {
        // 225-249: TINH THỂ LẬP PHƯƠNG LƯỢNG TỬ & MA TRẬN NEURAL
        spr->drawRect(cx - 18, cy - 26, 36, 52, 0x07FF);
        spr->fillRect(cx - 14, cy - 22, 28, 44, 0x10A2);
        int pHeight = 8 + (int)(breath * 24.0f);
        spr->fillRect(cx - 12, cy + 20 - pHeight, 24, pHeight, 0x07FF);
        spr->drawFastHLine(cx - 10, cy, 20, TFT_WHITE);
      }
      return;
    }
  }
};
