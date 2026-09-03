#pragma once
// ============================================================================
// MAHOUKARP OCEAN GALAXY SPRITE SUITE - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 / ESP32-C3 + ST7789P3 LCD (172x320 60FPS DMA)
// Stylistic Origin: Artist @Mahoukarp (X) Pastel Celestial Ocean Aesthetic
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace MahoukarpOcean {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// =============================================================
// ID 0: CÁ VOI XANH THIÊN HÀ PASTEL (MAHOUKARP GALAXY BLUE WHALE)
// 100% Khớp ảnh mẫu download (9).jpg "Blue Whale" & Mahoukarp
// =============================================================
static void drawMahoukarpBlueWhale(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale) {
  // 1. Squash & Stretch 5% bảo toàn diện tích (Area-preserving elasticity)
  float sy = 1.0f + 0.05f * sinf(angle);
  float sx = 1.0f - 0.025f * sinf(angle);
  int by = cy + (int)(sinf(angle) * 3.5f);

  // 2. Trễ pha động học (Kinematic Phase Lag)
  float tailAngle = sinf(angle - 0.75f);
  float finAngle  = sinf(angle - 0.40f);
  int tailOffsetY = (int)(tailAngle * 6.0f);
  int finOffsetY  = (int)(finAngle * 3.0f);

  // 3. Đuôi cá voi (Whale Fluke Tail) - Trễ pha đập nước phía sau
  int tailBaseX = cx + (int)(46 * sx);
  int tailBaseY = by - (int)(2 * sy) + tailOffsetY;
  // Cuống đuôi
  spr->fillTriangle(cx + (int)(30 * sx), by + (int)(4 * sy),
                    cx + (int)(32 * sx), by - (int)(10 * sy),
                    tailBaseX, tailBaseY, 0xBD3D);
  // 2 Thùy đuôi xòe cong mềm mại
  spr->fillEllipse(tailBaseX + 8, tailBaseY - 9, 10, 6, 0xBD3D);
  spr->fillEllipse(tailBaseX + 8, tailBaseY + 8, 10, 6, 0x9CFD);
  spr->fillCircle(tailBaseX + 13, tailBaseY - 11, 4, 0xBD3D);
  spr->fillCircle(tailBaseX + 13, tailBaseY + 10, 4, 0x9CFD);
  // Vết khuyết đuôi trung tâm (Center fluke notch)
  spr->fillTriangle(tailBaseX + 11, tailBaseY, tailBaseX + 18, tailBaseY - 6, tailBaseX + 18, tailBaseY + 6, 0x0000);

  // 4. Khối thân chính (Main Body Hull) - Gradient tím lam pastel
  // Lưng cá voi (Dorsal Lavender / Periwinkle)
  spr->fillEllipse(cx - (int)(2 * sx), by, (int)(48 * sx), (int)(26 * sy), 0x7376); // Viền bóng tím sâu
  spr->fillEllipse(cx - (int)(2 * sx), by - 1, (int)(46 * sx), (int)(24 * sy), 0x9CFD); // Thân lam pastel
  spr->fillEllipse(cx - (int)(4 * sx), by - 4, (int)(42 * sx), (int)(20 * sy), 0xBD3D); // Vòm lưng tím lilac

  // 5. Bụng trắng sữa & Nếp gấp thanh quản (Creamy Underbelly & Pleat Grooves)
  // Bụng trắng cong vòng từ cằm tới đuôi
  spr->fillEllipse(cx - (int)(10 * sx), by + (int)(10 * sy), (int)(36 * sx), (int)(15 * sy), 0xFFFF);
  spr->fillEllipse(cx - (int)(10 * sx), by + (int)(12 * sy), (int)(34 * sx), (int)(12 * sy), 0xFFDF);
  // 3 Đường rãnh nếp gấp bụng uốn lượn (Ventral throat grooves)
  spr->drawEllipse(cx - (int)(10 * sx), by + (int)(10 * sy), (int)(32 * sx), (int)(10 * sy), 0xD73F);
  spr->drawEllipse(cx - (int)(12 * sx), by + (int)(13 * sy), (int)(28 * sx), (int)(7 * sy), 0xD73F);
  spr->drawEllipse(cx - (int)(14 * sx), by + (int)(16 * sy), (int)(22 * sx), (int)(5 * sy), 0xD73F);

  // 6. Vây bơi chèo (Pectoral Flipper) với độ trễ chuyển động
  int finX = cx - (int)(12 * sx);
  int finY = by + (int)(12 * sy) + finOffsetY;
  spr->fillEllipse(finX, finY, (int)(11 * sx), (int)(5 * sy), 0x9CFD);
  spr->fillCircle(finX + (int)(6 * sx), finY + 2, 3, 0xBD3D);

  // 7. Chùm hoa sao dập nổi trên lưng (Dorsal Star-Flower Blossoms)
  // Hoa sao hồng 1 (Pink Blossom 1)
  int f1x = cx + (int)(8 * sx), f1y = by - (int)(14 * sy);
  spr->fillCircle(f1x, f1y - 2, 2, 0xFDDA);
  spr->fillCircle(f1x, f1y + 2, 2, 0xFDDA);
  spr->fillCircle(f1x - 2, f1y, 2, 0xFDDA);
  spr->fillCircle(f1x + 2, f1y, 2, 0xFDDA);
  spr->fillCircle(f1x, f1y, 2, 0xFFFF); // Nhụy trắng
  // Hoa sao hồng 2 (Pink Blossom 2)
  int f2x = cx + (int)(24 * sx), f2y = by - (int)(9 * sy);
  spr->fillCircle(f2x, f2y - 2, 2, 0xFDDA);
  spr->fillCircle(f2x, f2y + 2, 2, 0xFDDA);
  spr->fillCircle(f2x - 2, f2y, 2, 0xFDDA);
  spr->fillCircle(f2x + 2, f2y, 2, 0xFDDA);
  spr->fillCircle(f2x, f2y, 2, 0xFFFF);
  // Hoa sao trắng lớn (Ivory Star Blossom)
  int f3x = cx + (int)(18 * sx), f3y = by - (int)(3 * sy);
  spr->fillCircle(f3x, f3y - 3, 2, 0xFFFF);
  spr->fillCircle(f3x, f3y + 3, 2, 0xFFFF);
  spr->fillCircle(f3x - 3, f3y, 2, 0xFFFF);
  spr->fillCircle(f3x + 3, f3y, 2, 0xFFFF);
  spr->fillCircle(f3x, f3y, 2, 0xFEFE);
  // Ngôi sao xanh thiên hà nhỏ (Tiny Cosmic Star Gem)
  int f4x = cx - (int)(6 * sx), f4y = by - (int)(12 * sy);
  spr->fillRect(f4x - 1, f4y - 1, 3, 3, 0x9EBF);
  spr->drawPixel(f4x, f4y - 2, 0xFFFF);
  spr->drawPixel(f4x, f4y + 2, 0xFFFF);
  spr->drawPixel(f4x - 2, f4y, 0xFFFF);
  spr->drawPixel(f4x + 2, f4y, 0xFFFF);

  // 8. Má hồng phớt to tròn & Vầng sáng má (Cheek Glow & Big Soft Blush)
  int chkX = cx - (int)(22 * sx), chkY = by + (int)(4 * sy);
  spr->fillCircle(chkX, chkY, 7, 0xFFFF);     // Vầng hào quang trắng quanh má
  spr->fillEllipse(chkX, chkY, 5, 4, 0xFD79); // Má hồng anh đào ngọt ngào

  // 9. MẮT PHA LÊ 3 ĐIỂM SÁNG (Crystal Kawaii Eye with 3 Catchlights)
  int eyeX = cx - (int)(32 * sx), eyeY = by + (int)(2 * sy);
  bool blink = (millis() % 4000 < 140);
  if (blink) {
    // Mi cong nhắm mắt khi chớp (Kawaii happy crescent arc)
    spr->drawLine(eyeX - 4, eyeY + 1, eyeX, eyeY + 3, 0x0884);
    spr->drawLine(eyeX, eyeY + 3, eyeX + 4, eyeY + 1, 0x0884);
  } else {
    // Tròng mắt đen chàm sâu
    spr->fillCircle(eyeX, eyeY, 4, 0x0884);
    // Điểm 1: Vệt sáng chính góc trên trái (Main Catchlight)
    spr->fillCircle(eyeX - 1, eyeY - 2, 2, 0xFFFF);
    // Điểm 2: Điểm sáng phụ góc dưới phải (Secondary Bounce Catchlight)
    spr->fillCircle(eyeX + 2, eyeY + 1, 1, 0xFFFF);
    // Điểm 3: Hạt tinh thể vi mô lấp lánh mép phải (Micro Twinkle Glint)
    spr->drawPixel(eyeX + 2, eyeY - 1, 0xD71E);
  }

  // 10. Miệng cười kawaii nhẹ nhàng
  spr->drawPixel(cx - (int)(40 * sx), by + (int)(6 * sy), 0x7376);
  spr->drawPixel(cx - (int)(39 * sx), by + (int)(7 * sy), 0x7376);
  spr->drawPixel(cx - (int)(38 * sx), by + (int)(6 * sy), 0x7376);

  // 11. Hạt nước phun lỗ thở trôi bồng bềnh (Spout Blowhole Water Bubbles)
  float spoutLag = sinf(angle - 0.90f);
  int spY = by - (int)(28 * sy) + (int)(spoutLag * 2.0f);
  spr->fillCircle(cx - (int)(18 * sx), spY, 2, 0x9EBF);
  spr->fillCircle(cx - (int)(15 * sx), spY - 5, 3, 0xFFFF);
  spr->fillCircle(cx - (int)(11 * sx), spY - 2, 2, 0xBD3D);
}

// =============================================================
// ID 1: CÁ MẬP ĐỐM SAO THIÊN HÀ (MAHOUKARP STARRY WHALE SHARK)
// 100% Khớp ảnh mẫu Artist_ @Mahoukarp (X) _ 10 sheets.jpg (Top Right)
// =============================================================
static void drawMahoukarpWhaleShark(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale) {
  // 1. Squash & Stretch 5% trên trục bơi uốn cong
  float sx = 1.0f + 0.05f * cosf(angle);
  float sy = 1.0f - 0.025f * cosf(angle);
  int by = cy + (int)(sinf(angle) * 3.0f);

  // 2. Trễ pha vây đuôi và vây lưng
  float tailAngle = sinf(angle - 1.10f);
  float finAngle  = sinf(angle - 0.45f);
  int tailOffset = (int)(tailAngle * 7.0f);
  int finOffset  = (int)(finAngle * 3.5f);

  // 3. Vây đuôi cá mập (Shark Caudal Fin) - Dáng lưỡi liềm 2 thùy không đối xứng
  int tailX = cx - (int)(36 * sx);
  int tailY = by - (int)(16 * sy) + tailOffset;
  spr->fillTriangle(tailX, tailY, tailX - 18, tailY - 14, tailX - 6, tailY + 2, 0x3B76);
  spr->fillTriangle(tailX, tailY, tailX - 14, tailY + 12, tailX - 4, tailY - 2, 0x3B76);
  spr->fillCircle(tailX - 16, tailY - 12, 4, 0x6DDE); // Điểm sáng đầu thùy trên
  spr->fillCircle(tailX - 12, tailY + 10, 3, 0x6DDE); // Điểm sáng đầu thùy dưới

  // 4. Vây lưng cá mập (Dorsal Fin)
  int dorX = cx - (int)(12 * sx);
  int dorY = by - (int)(22 * sy) + (int)(finAngle * 2.0f);
  spr->fillTriangle(dorX - 10, dorY + 8, dorX + 4, dorY + 8, dorX - 2, dorY - 8, 0x3B76);
  spr->fillCircle(dorX - 2, dorY - 7, 3, 0x6DDE);

  // 5. Thân cong chữ C đặc trưng Mahoukarp (Isometric Curving Body)
  // Lớp nền thân xanh thẫm
  spr->fillEllipse(cx, by, (int)(44 * sx), (int)(28 * sy), 0x3B76);
  // Lớp vòm chuyển màu lam sáng
  spr->fillEllipse(cx + (int)(4 * sx), by + (int)(2 * sy), (int)(40 * sx), (int)(25 * sy), 0x6DDE);

  // 6. Hai vây ngực dang rộng (Wide Pectoral Wings)
  // Vây ngực trái (trên)
  int fLX = cx - (int)(18 * sx), fLY = by - (int)(6 * sy) + finOffset;
  spr->fillEllipse(fLX, fLY, 14, 7, 0x3B76);
  spr->fillCircle(fLX - 8, fLY, 3, 0x6DDE);
  // Vây ngực phải (dưới)
  int fRX = cx + (int)(32 * sx), fRY = by + (int)(14 * sy) - finOffset;
  spr->fillEllipse(fRX, fRY, 14, 8, 0x6DDE);
  spr->fillCircle(fRX + 8, fRY + 2, 3, 0xFFFF);

  // 7. Vòm miệng cười hồng rộng mở (Wide Open Chibi Mouth)
  // Khoang miệng mở tròn đặc trưng mập voi Mahoukarp
  int mX = cx + (int)(24 * sx), mY = by + (int)(10 * sy);
  spr->fillEllipse(mX, mY, (int)(16 * sx), (int)(10 * sy), 0xFFFF); // Mép môi trắng
  spr->fillEllipse(mX, mY, (int)(14 * sx), (int)(8 * sy), 0xFD17);  // Viền hồng phấn
  spr->fillEllipse(mX, mY + 1, (int)(11 * sx), (int)(6 * sy), 0xEAE1); // Vòm họng hồng thẫm ngọt ngào
  // Chiếc lưỡi nhỏ mỉm cười
  spr->fillCircle(mX, mY + 3, 4, 0xFD17);

  // 8. Dải chòm sao kim cương & đốm sao trên lưng (Star Constellation Pattern)
  // Ma trận sao kim cương 4 cánh và sao 5 cánh dập nổi
  auto drawStar = [&](int px, int py, uint16_t col) {
    spr->fillTriangle(px, py - 3, px - 2, py, px + 2, py, col);
    spr->fillTriangle(px, py + 3, px - 2, py, px + 2, py, col);
    spr->drawPixel(px, py, 0xFFFF);
  };
  drawStar(cx - (int)(16 * sx), by - (int)(8 * sy), 0xFFFF);
  drawStar(cx - (int)(6 * sx),  by - (int)(14 * sy), 0xFEFE);
  drawStar(cx + (int)(6 * sx),  by - (int)(10 * sy), 0xFFFF);
  drawStar(cx - (int)(8 * sx),  by,                  0xFFFF);
  drawStar(cx + (int)(4 * sx),  by - (int)(2 * sy),  0xFEFE);
  drawStar(cx + (int)(14 * sx), by - (int)(6 * sy),  0xFFFF);
  drawStar(cx - (int)(22 * sx), by - (int)(2 * sy),  0xFEFE);
  drawStar(cx - (int)(2 * sx),  by + (int)(8 * sy),  0xFFFF);
  // Đốm sao tròn nhỏ lấp lánh xung quanh
  spr->fillCircle(cx - (int)(12 * sx), by + (int)(4 * sy), 2, 0xFFFF);
  spr->fillCircle(cx + (int)(10 * sx), by + (int)(3 * sy), 2, 0xFFFF);
  spr->fillCircle(cx + (int)(18 * sx), by - (int)(12 * sy), 2, 0xFFFF);

  // 9. MẮT PHA LÊ 3 ĐIỂM SÁNG (Crystal Kawaii Eye)
  int eyeX = cx + (int)(34 * sx), eyeY = by - (int)(2 * sy);
  bool blink = (millis() % 3800 < 130);
  if (blink) {
    spr->drawLine(eyeX - 3, eyeY, eyeX + 3, eyeY, 0x08A4);
  } else {
    spr->fillCircle(eyeX, eyeY, 4, 0x08A4);
    // Điểm 1: Vệt sáng chính góc trên trái
    spr->fillCircle(eyeX - 1, eyeY - 2, 2, 0xFFFF);
    // Điểm 2: Điểm phản quang phụ góc dưới phải
    spr->fillCircle(eyeX + 1, eyeY + 1, 1, 0xFFFF);
    // Điểm 3: Vi hạt lấp lánh mép trên
    spr->drawPixel(eyeX + 2, eyeY - 1, 0x6DDE);
  }

  // 10. Má hồng phớt cạnh khóe miệng
  spr->fillCircle(cx + (int)(38 * sx), by + (int)(6 * sy), 4, 0xFD79);
}

// =============================================================
// ID 2: SỨA MẶT TRĂNG VƯƠNG MIỆN PHÁT QUANG (MOON JELLYFISH)
// 100% Khớp ảnh mẫu Artist_ @Mahoukarp (X) & download (9).jpg "Moon"
// =============================================================
static void drawMahoukarpMoonJelly(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale) {
  // 1. Nhịp phản lực đẩy sứa (Asymmetric Jet Pulse): Co thắt nhanh, dãn nở lướt chậm
  float pulse = sinf(angle);
  float sy = (pulse > 0) ? (1.0f + 0.06f * pulse) : (1.0f + 0.12f * pulse); // Co nén khi đẩy
  float sx = 1.0f / sqrtf(sy);
  int by = cy + (int)(sinf(angle) * 4.0f);

  // 2. Tán dù sứa phát quang đa lớp (Multi-layer Bioluminescent Bell)
  // Viền hào quang tỏa sáng bên ngoài (Outer Bloom Aura)
  spr->fillEllipse(cx, by - (int)(6 * sy), (int)(36 * sx), (int)(28 * sy), 0x3376);
  spr->fillEllipse(cx, by - (int)(6 * sy), (int)(34 * sx), (int)(26 * sy), 0x767F);
  spr->fillEllipse(cx, by - (int)(8 * sy), (int)(30 * sx), (int)(22 * sy), 0xD7BF);

  // 3. VƯƠNG MIỆN TRĂNG KHUYẾT PHÁT QUANG (Glowing Crescent Moon Crown)
  // Biểu tượng đặc trưng trong ảnh mẫu Mahoukarp
  int mY = by - (int)(16 * sy);
  // Trăng khuyết trung tâm phát sáng
  spr->fillCircle(cx, mY, 9, 0xFFFF);
  spr->fillCircle(cx, mY - 3, 8, 0x767F); // Cắt khuyết tạo hình lưỡi liềm ngửa
  spr->fillCircle(cx, mY + 1, 3, 0xFFFF); // Nhụy sao trăng
  // 2 Vầng trăng cánh phụ 2 bên
  spr->fillCircle(cx - 15, mY + 3, 6, 0xD7BF);
  spr->fillCircle(cx - 15, mY + 1, 5, 0x767F);
  spr->fillCircle(cx + 15, mY + 3, 6, 0xD7BF);
  spr->fillCircle(cx + 15, mY + 1, 5, 0x767F);

  // 4. Vành bèo chân dù sứa nhấp nhô (Scalloped Bell Margin)
  int rimY = by + (int)(12 * sy);
  spr->fillRect(cx - (int)(30 * sx), rimY - 2, (int)(60 * sx), 5, 0x3376);
  for (int rx = -24; rx <= 24; rx += 8) {
    spr->fillCircle(cx + (int)(rx * sx), rimY + 2, 4, 0x767F);
  }

  // 5. MẮT PHA LÊ 3 ĐIỂM SÁNG & KHUÔN MẶT KAWAII (Kawaii Chibi Face)
  int eyeL = cx - (int)(12 * sx), eyeR = cx + (int)(12 * sx);
  int eyeY = by + (int)(2 * sy);
  bool blink = (millis() % 3500 < 130);

  if (blink) {
    spr->drawLine(eyeL - 3, eyeY, eyeL + 3, eyeY, 0x08C6);
    spr->drawLine(eyeR - 3, eyeY, eyeR + 3, eyeY, 0x08C6);
  } else {
    // Mắt trái
    spr->fillCircle(eyeL, eyeY, 4, 0x08C6);
    spr->fillCircle(eyeL - 1, eyeY - 2, 2, 0xFFFF);
    spr->fillCircle(eyeL + 1, eyeY + 1, 1, 0xFFFF);
    spr->drawPixel(eyeL + 2, eyeY - 1, 0xD7BF);
    // Mắt phải
    spr->fillCircle(eyeR, eyeY, 4, 0x08C6);
    spr->fillCircle(eyeR - 1, eyeY - 2, 2, 0xFFFF);
    spr->fillCircle(eyeR + 1, eyeY + 1, 1, 0xFFFF);
    spr->drawPixel(eyeR + 2, eyeY - 1, 0xD7BF);
  }

  // Miệng mèo 'w' chibi uốn lượn
  spr->drawPixel(cx - 3, eyeY + 4, 0x08C6);
  spr->drawPixel(cx - 2, eyeY + 5, 0x08C6);
  spr->drawPixel(cx - 1, eyeY + 4, 0x08C6);
  spr->drawPixel(cx,     eyeY + 5, 0x08C6);
  spr->drawPixel(cx + 1, eyeY + 4, 0x08C6);
  spr->drawPixel(cx + 2, eyeY + 5, 0x08C6);
  spr->drawPixel(cx + 3, eyeY + 4, 0x08C6);

  // Đôi má hồng tròn xoe phát sáng ngọt ngào
  spr->fillCircle(cx - (int)(18 * sx), eyeY + 3, 4, 0xFC56);
  spr->fillCircle(cx + (int)(18 * sx), eyeY + 3, 4, 0xFC56);

  // 6. 6 DẢI XÚC TU LỤA UỐN LƯỢN TRỄ PHA (6 Phase-Lag Ribbon Tentacles)
  int tBaseY = rimY + 4;
  const int tOffsets[6] = {-20, -12, -4, 4, 12, 20};
  const float tPhase[6] = {0.0f, 0.4f, 0.8f, 1.2f, 1.6f, 2.0f};

  for (int t = 0; t < 6; t++) {
    int curX = cx + (int)(tOffsets[t] * sx);
    uint16_t tCol = (t % 2 == 0) ? 0x767F : 0x83FC;
    for (int seg = 0; seg < 18; seg++) {
      float segLag = sinf(angle - seg * 0.22f + tPhase[t]);
      int nextX = cx + (int)(tOffsets[t] * sx) + (int)(segLag * 6.5f);
      int segY = tBaseY + seg * 2;
      spr->drawLine(curX, segY, nextX, segY + 2, tCol);
      curX = nextX;
    }
    // Hạt ngọc phát quang ở đầu mút xúc tu
    spr->fillCircle(curX, tBaseY + 38, 2, 0xFFFF);
  }
}

// =============================================================
// ID 3: CÁ LỒNG ĐÈN NƯỚC SÂU ANGLER (MAHOUKARP ABYSSAL ANGLER)
// 100% Khớp ảnh mẫu download (9).jpg "Angler" & Biển Sâu Phát Quang
// =============================================================
static void drawMahoukarpAbyssalAngler(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale) {
  // 1. Squash & Stretch 5% theo nhịp thở đáy vực
  float sy = 1.0f + 0.05f * sinf(angle);
  float sx = 1.0f - 0.025f * sinf(angle);
  int by = cy + (int)(sinf(angle) * 3.0f);

  // 2. Dao động con lắc của đèn lồng (Esca Pendulum Lag)
  float lanternLag = sinf(angle - 1.20f);
  int lanternX = cx + (int)(32 * sx) + (int)(lanternLag * 5.0f);
  int lanternY = by - (int)(24 * sy) + (int)(lanternLag * 4.0f);

  // 3. Đuôi cá lồng đèn (Ribbed Fan Tail)
  int tailX = cx - (int)(32 * sx), tailY = by;
  float tailLag = sinf(angle - 0.80f);
  spr->fillTriangle(tailX, tailY, tailX - 16, tailY - 12 + (int)(tailLag * 5.0f), tailX - 16, tailY + 12 + (int)(tailLag * 5.0f), 0x29CD);
  spr->drawLine(tailX, tailY, tailX - 16, tailY - 12 + (int)(tailLag * 5.0f), 0x973F);
  spr->drawLine(tailX, tailY, tailX - 16, tailY + (int)(tailLag * 5.0f), 0x973F);
  spr->drawLine(tailX, tailY, tailX - 16, tailY + 12 + (int)(tailLag * 5.0f), 0x973F);

  // 4. Gai lưng phát sáng (Radiating Dorsal Spines)
  for (int s = 0; s < 5; s++) {
    int spBaseX = cx - (int)((14 - s * 7) * sx);
    int spBaseY = by - (int)(18 * sy);
    int spTipX  = spBaseX - 3;
    int spTipY  = spBaseY - (8 + s * 2);
    spr->drawLine(spBaseX, spBaseY, spTipX, spTipY, 0x4B56);
    spr->fillCircle(spTipX, spTipY, 2, 0x579D); // Hạt dạ quang đầu gai
  }

  // 5. Thân tròn xoe đen chàm bóng bẩy (Midnight Abyss Hull)
  spr->fillCircle(cx, by, (int)(26 * sx), 0x1908); // Lõi thẳm đen
  spr->fillCircle(cx - 2, by - 2, (int)(24 * sx), 0x29CD); // Lớp lam đêm
  spr->fillCircle(cx - 4, by - 4, (int)(20 * sx), 0x4B56); // Vòm sáng lưng

  // 6. Hàm dưới pastel & Răng cưa chibi zigzag (Pastel Cyan Jaw & Chibi Zigzag Teeth)
  int jawY = by + (int)(8 * sy);
  spr->fillEllipse(cx + (int)(8 * sx), jawY, (int)(18 * sx), (int)(12 * sy), 0x973F);
  // Hàm răng cưa zigzag đáng yêu vô hại
  for (int t = 0; t < 4; t++) {
    int tx = cx + (int)((-2 + t * 6) * sx);
    spr->fillTriangle(tx, jawY - 4, tx + 3, jawY, tx - 3, jawY, 0xFFFF);
  }

  // 7. Cần câu uốn lượn (Flexible Illucium Stalk)
  int stalkBaseX = cx + (int)(4 * sx), stalkBaseY = by - (int)(24 * sy);
  int ctrlX = cx + (int)(22 * sx), ctrlY = by - (int)(38 * sy);
  spr->drawLine(stalkBaseX, stalkBaseY, ctrlX, ctrlY, 0x66BE);
  spr->drawLine(ctrlX, ctrlY, lanternX, lanternY, 0x66BE);

  // 8. ĐÈN LỒNG DẠ QUANG PHÁT SÁNG (Bioluminescent Glowing Esca Orb)
  // Quầng hào quang tỏa sáng (Multi-stage Neon Cyan Bloom)
  spr->fillCircle(lanternX, lanternY, 9, 0x579D);
  spr->fillCircle(lanternX, lanternY, 6, 0x079F);
  spr->fillCircle(lanternX, lanternY, 3, 0xFFFF); // Lõi sáng trắng rực rỡ

  // 9. Dãy đốm sao dạ quang dọc sườn (Flank Bioluminescent Constellation)
  spr->fillCircle(cx - (int)(14 * sx), by - (int)(2 * sy), 2, 0x579D);
  spr->fillCircle(cx - (int)(8 * sx),  by + (int)(4 * sy), 2, 0x579D);
  spr->fillCircle(cx,                  by - (int)(6 * sy), 2, 0x579D);
  spr->fillCircle(cx + (int)(8 * sx),  by - (int)(2 * sy), 2, 0x579D);
  spr->fillCircle(cx + (int)(14 * sx), by - (int)(8 * sy), 2, 0x579D);

  // 10. MẮT PHA LÊ 3 ĐIỂM SÁNG (Abyssal Crystal Eye)
  int eyeX = cx + (int)(16 * sx), eyeY = by - (int)(4 * sy);
  bool blink = (millis() % 3600 < 130);
  if (blink) {
    spr->drawLine(eyeX - 4, eyeY, eyeX + 4, eyeY, 0x08A5);
  } else {
    spr->fillCircle(eyeX, eyeY, 4, 0x08A5);
    spr->fillCircle(eyeX - 1, eyeY - 2, 2, 0xFFFF); // Điểm sáng chính
    spr->fillCircle(eyeX + 2, eyeY + 1, 1, 0xFFFF); // Điểm nảy phụ
    spr->drawPixel(eyeX + 2, eyeY - 1, 0x579D);    // Hạt dạ quang
  }

  // Má hồng dạ quang
  spr->fillCircle(cx + (int)(22 * sx), by + (int)(4 * sy), 4, 0xFD79);
}

// =============================================================
// ID 4: CÁ ĐUỐI CÁNH TIÊN BIỂN SÂU (FAIRY-WING STINGRAY)
// 100% Khớp ảnh mẫu Artist_ @Mahoukarp (X) (Center Right) & download (10).jpg
// =============================================================
static void drawMahoukarpStingray(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale) {
  // 1. Squash & Stretch 5% theo nhịp vỗ cánh tiên
  float sx = 1.0f + 0.05f * sinf(angle);
  float sy = 1.0f - 0.025f * sinf(angle);
  int by = cy + (int)(sinf(angle) * 3.5f);

  // 2. Dao động uốn cánh và trễ pha đuôi roi (Wing Flap & Tail Lag)
  float wingFlap = sinf(angle - 0.50f);
  int wingTipOffsetY = (int)(wingFlap * 6.5f);

  // 3. Đuôi roi thanh mảnh uốn lượn (Kinematic Whip Tail)
  int tailBaseX = cx + (int)(32 * sx), tailBaseY = by + (int)(6 * sy);
  for (int seg = 0; seg < 16; seg++) {
    float segLag = sinf(angle - seg * 0.28f);
    int curX  = tailBaseX + seg * 3;
    int nextX = tailBaseX + (seg + 1) * 3;
    int curY  = tailBaseY + (int)(sinf(angle - (seg) * 0.28f) * 5.0f);
    int nextY = tailBaseY + (int)(sinf(angle - (seg + 1) * 0.28f) * 5.0f);
    spr->drawLine(curX, curY, nextX, nextY, 0x765E);
  }
  // Hạt ngọc thiên hà đính đầu mút đuôi
  spr->fillCircle(tailBaseX + 48, tailBaseY + (int)(sinf(angle - 4.48f) * 5.0f), 2, 0xFFFF);

  // 4. Đôi cánh tiên dạng diều xòe rộng (Fairy Wing Pectoral Hull)
  // Cánh trên (Dorsal Violet / Azure Wingtips)
  int wLX = cx - (int)(36 * sx), wLY = by - (int)(12 * sy) + wingTipOffsetY;
  int wRX = cx + (int)(34 * sx), wRY = by - (int)(16 * sy) - wingTipOffsetY;
  spr->fillTriangle(cx, by - (int)(18 * sy), wLX, wLY, cx, by + (int)(14 * sy), 0x7BDA);
  spr->fillTriangle(cx, by - (int)(18 * sy), wRX, wRY, cx, by + (int)(14 * sy), 0x765E);
  // Chóp cánh phớt hồng tiên cảnh
  spr->fillCircle(wLX, wLY, 6, 0xF559);
  spr->fillCircle(wRX, wRY, 7, 0xF559);

  // 5. Bụng trắng muốt ngọc trai & Mặt cười (Pearl White Underbelly & Smile)
  // Khối bụng tròn xoe trắng ngọc trai
  spr->fillEllipse(cx - (int)(4 * sx), by + (int)(2 * sy), (int)(26 * sx), (int)(20 * sy), 0xFFFF);

  // 6. Miệng cười hé mở hồng ngọt ngào (Happy Open Chibi Mouth)
  int mX = cx - (int)(14 * sx), mY = by - (int)(2 * sy);
  spr->fillEllipse(mX, mY, (int)(7 * sx), (int)(5 * sy), 0xFCE7); // Môi hồng
  spr->fillCircle(mX, mY + 1, 3, 0xEAE1); // Lưỡi nhỏ bên trong

  // 7. 3 Khe mang sọc pastel hai bên sườn (Pastel Gill Slit Dashes)
  for (int g = 0; g < 3; g++) {
    int gx = cx - (int)((2 - g * 4) * sx);
    spr->drawFastVLine(gx, by - (int)(4 * sy), 5, 0x96BF);
  }

  // 8. Đôi sừng vây đầu nhỏ (Cephalic Flaps)
  spr->fillCircle(cx - (int)(26 * sx), by - (int)(12 * sy), 4, 0x765E);
  spr->fillCircle(cx - (int)(24 * sx), by - (int)(14 * sy), 3, 0xFFFF);

  // 9. MẮT PHA LÊ 3 ĐIỂM SÁNG (Fairy Crystal Eye)
  int eyeX = cx - (int)(4 * sx), eyeY = by - (int)(8 * sy);
  bool blink = (millis() % 3700 < 130);
  if (blink) {
    spr->drawLine(eyeX - 3, eyeY, eyeX + 3, eyeY, 0x10A6);
  } else {
    spr->fillCircle(eyeX, eyeY, 4, 0x10A6);
    spr->fillCircle(eyeX - 1, eyeY - 2, 2, 0xFFFF);
    spr->fillCircle(eyeX + 1, eyeY + 1, 1, 0xFFFF);
    spr->drawPixel(eyeX + 2, eyeY - 1, 0x765E);
  }

  // Má hồng phớt cạnh miệng
  spr->fillEllipse(cx - (int)(18 * sx), by + (int)(4 * sy), 4, 3, 0xFD79);
}

// =============================================================
// ID 5: SÒ NGỌC BIỂN CƯỜI THIÊN HÀ (SMILING PEARL CLAM)
// 100% Khớp ảnh mẫu Artist_ @Mahoukarp (X) (Bottom Center) & download (10).jpg
// =============================================================
static void drawMahoukarpPearlClam(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale) {
  // 1. Squash & Stretch 5% theo nhịp đóng mở vỏ sò ngọc
  float sy = 1.0f + 0.05f * sinf(angle);
  float sx = 1.0f - 0.025f * sinf(angle);
  int by = cy + (int)(sinf(angle) * 3.0f);

  // 2. Góc bản lề vỏ sò mở hé (Shell Hinge Opening Angle)
  float hingeAngle = sinf(angle - 0.30f);
  int upperShellLift = (int)(hingeAngle * 5.0f);

  // 3. VỎ SÒ DƯỚI (LOWER BASE SHELL) & ĐỆM NHUNG HỒNG
  // Vỏ dưới cong hình lòng chảo
  spr->fillEllipse(cx, by + (int)(18 * sy), (int)(36 * sx), (int)(16 * sy), 0x63D9); // Bóng vỏ
  spr->fillEllipse(cx, by + (int)(17 * sy), (int)(34 * sx), (int)(14 * sy), 0x7DDE); // Lam ngọc
  // Đệm nhung xà cừ hồng êm ái nâng ngọc trai
  spr->fillEllipse(cx, by + (int)(14 * sy), (int)(28 * sx), (int)(9 * sy), 0xFDDA);
  spr->fillEllipse(cx, by + (int)(13 * sy), (int)(24 * sx), (int)(7 * sy), 0xFF3E);

  // 4. VỎ SÒ TRÊN XÒE QUẠT 7 MÚI (UPPER FAN SHELL WITH 7 FLUTED RIBS)
  int upY = by - (int)(10 * sy) - upperShellLift;
  // 7 Múi quạt vỏ sò xòe rộng
  const int ribAngles[7] = {-30, -20, -10, 0, 10, 20, 30};
  const int ribHeights[7] = {20, 26, 30, 32, 30, 26, 20};

  for (int r = 0; r < 7; r++) {
    int rx = cx + (int)(ribAngles[r] * 1.1f * sx);
    int ry = upY - (int)(ribHeights[r] * 0.4f * sy);
    uint16_t ribCol = (r % 2 == 0) ? 0xACC3 : 0x7DDE;
    spr->fillEllipse(rx, ry, (int)(8 * sx), (int)(18 * sy), ribCol);
  }
  // Viền gợn sóng đỉnh vỏ trên
  spr->drawEllipse(cx, upY - 8, (int)(32 * sx), (int)(16 * sy), 0xFFFF);

  // 5. BÉ NGỌC TRAI TRÒN XOE PHÁT SÁNG (SENTIENT CHIBI LIVING PEARL)
  // Ngọc trai bồng bềnh giữa lòng sò
  int pX = cx, pY = by + (int)(8 * sy) - (int)(sinf(angle - 0.60f) * 2.0f);
  int pRadius = (int)(17 * sx);
  // Khối cầu 3D ngọc trai phát sáng
  spr->fillCircle(pX, pY, pRadius, 0xE77F);      // Lớp bóng xà cừ
  spr->fillCircle(pX - 2, pY - 2, pRadius - 2, 0xFFFF); // Lớp trắng ngọc tinh khôi

  // 6. NGÔI SAO 4 CÁNH LẤP LÁNH TRÊN TRÁN NGỌC (Forehead Star Gem)
  int sX = pX - 6, sY = pY - 9;
  spr->fillTriangle(sX, sY - 3, sX - 2, sY, sX + 2, sY, 0xFFFF);
  spr->fillTriangle(sX, sY + 3, sX - 2, sY, sX + 2, sY, 0xFFFF);
  spr->drawPixel(sX, sY, 0xFF3E);

  // 7. MẮT PHA LÊ 3 ĐIỂM SÁNG BÉ NGỌC (Crystal Kawaii Pearl Eyes)
  int eyeL = pX - 6, eyeR = pX + 6;
  int eyeY = pY - 1;
  bool blink = (millis() % 3400 < 130);

  if (blink) {
    spr->drawLine(eyeL - 3, eyeY, eyeL + 3, eyeY, 0x1086);
    spr->drawLine(eyeR - 3, eyeY, eyeR + 3, eyeY, 0x1086);
  } else {
    // Mắt trái
    spr->fillCircle(eyeL, eyeY, 3, 0x1086);
    spr->fillCircle(eyeL - 1, eyeY - 1, 1, 0xFFFF);
    spr->drawPixel(eyeL + 1, eyeY + 1, 0xFFFF);
    spr->drawPixel(eyeL + 1, eyeY - 1, 0xFF3E);
    // Mắt phải
    spr->fillCircle(eyeR, eyeY, 3, 0x1086);
    spr->fillCircle(eyeR - 1, eyeY - 1, 1, 0xFFFF);
    spr->drawPixel(eyeR + 1, eyeY + 1, 0xFFFF);
    spr->drawPixel(eyeR + 1, eyeY - 1, 0xFF3E);
  }

  // Nụ cười tí hon mỉm cười ngọt ngào ( ^ ‿ ^ )
  spr->drawPixel(pX - 2, eyeY + 4, 0x1086);
  spr->drawPixel(pX - 1, eyeY + 5, 0x1086);
  spr->drawPixel(pX,     eyeY + 5, 0x1086);
  spr->drawPixel(pX + 1, eyeY + 5, 0x1086);
  spr->drawPixel(pX + 2, eyeY + 4, 0x1086);

  // Má hồng tròn xoe thẹn thùng
  spr->fillCircle(pX - 10, eyeY + 2, 3, 0xFBD4);
  spr->fillCircle(pX + 10, eyeY + 2, 3, 0xFBD4);

  // 8. BONG BÓNG XÀ CỪ BAY LÊN (Shimmering Pearl Bubbles)
  float bubLag = sinf(angle - 1.40f);
  spr->drawCircle(cx - (int)(22 * sx), by - (int)(20 * sy) + (int)(bubLag * 4.0f), 3, 0xFFFF);
  spr->drawPixel(cx - (int)(23 * sx), by - (int)(21 * sy) + (int)(bubLag * 4.0f), 0xFFFF);
  spr->drawCircle(cx + (int)(24 * sx), by - (int)(26 * sy) - (int)(bubLag * 3.0f), 2, 0xFFFF);
}

// Unified Dispatcher Function
static void drawMahoukarpOceanCreature(SpriteRenderer::ScaledCanvas* spr, int creatureId, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  switch (creatureId % 6) {
    case 0: drawMahoukarpBlueWhale(spr, cx, cy, breath, angle, scale); break;
    case 1: drawMahoukarpWhaleShark(spr, cx, cy, breath, angle, scale); break;
    case 2: drawMahoukarpMoonJelly(spr, cx, cy, breath, angle, scale); break;
    case 3: drawMahoukarpAbyssalAngler(spr, cx, cy, breath, angle, scale); break;
    case 4: drawMahoukarpStingray(spr, cx, cy, breath, angle, scale); break;
    case 5: drawMahoukarpPearlClam(spr, cx, cy, breath, angle, scale); break;
    default: drawMahoukarpBlueWhale(spr, cx, cy, breath, angle, scale); break;
  }
}

} // namespace MahoukarpOcean
