#pragma once
// ============================================================================
// SESSION 4 KANTO CLASSIC LEGENDS - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 ST7789 IPS LCD (172x320 60FPS DMA)
// Pop Mart & Kawaii Visual DNA: Volumetric 4-Tone Shading & Crystal Catchlights
// Characters: Pikachu, Eevee, Bulbasaur, Charmander, Squirtle (IDs 65 to 69)
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace Session4Mythics {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// -------------------------------------------------------------
// Pikachu - Chuột Điện Hoàng Kim
// -------------------------------------------------------------
static void drawPikachuPopMart(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.3f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.5f);
  int by = cy + bounceY;

  // Đuôi tia chớp đung đưa trễ pha 0.45 rad
  float tailLag = breathPhase - 0.45f;
  int tailSwayX = (int)(sinf(tailLag) * 5.0f);
  int tailSwayY = (int)(cosf(tailLag) * 3.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_YELLOW     = 0xFFE0; // #FACC15 Vàng hoàng kim chủ đạo
  const uint16_t C_YEL_DARK   = 0xCA00; // #CA8A04 Bóng vàng
  const uint16_t C_YEL_LGT    = 0xFFF0; // #FEF08A Sáng vàng
  const uint16_t C_RED_CHEEK  = 0xF9A6; // #EF4444 Má đỏ tròn xoe
  const uint16_t C_RED_SHAD   = 0xB8A0; // #B91C1C Bóng má đỏ
  const uint16_t C_BLACK      = 0x08E5; // #0F172A Chóp tai & mắt đen
  const uint16_t C_BROWN_TAIL = 0x8A62; // #78350F Nâu đáy đuôi
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Điểm bắt sáng
  const uint16_t C_MOUTH_DARK = 0x8887; // #881337 Khoang miệng
  const uint16_t C_TONGUE     = 0xF3B6; // #F472B6 Lưỡi hồng
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Đuôi sấm sét sau lưng
  int tx = cx + 16 + tailSwayX;
  int ty = by - 8 + tailSwayY;
  // Đáy đuôi nâu
  spr->fillRoundRect(cx + 8, by + 16, 8, 4, 2, C_BROWN_TAIL);
  // Đoạn gấp khúc 1
  spr->fillTriangle(tx - 4, ty + 16, tx + 6, ty + 12, tx + 2, ty + 22, C_YELLOW);
  // Đoạn gấp khúc 2
  spr->fillTriangle(tx + 4, ty + 12, tx + 14, ty + 2, tx + 8, ty + 16, C_YELLOW);
  // Đỉnh đuôi sấm sét to rộng
  spr->fillTriangle(tx + 10, ty + 4, tx + 28, ty - 24, tx + 14, ty - 8, C_YEL_LGT);
  spr->fillTriangle(tx + 12, ty + 2, tx + 26, ty - 22, tx + 20, ty - 4, C_YELLOW);

  // 3. Thân vàng mũm mĩm & 2 vệt nâu sau lưng
  spr->fillEllipse(cx, by + 16, (int)(22 * sX), (int)(20 * sY), C_YEL_DARK);
  spr->fillEllipse(cx, by + 14, (int)(20 * sX), (int)(18 * sY), C_YELLOW);
  // Hai chân ngắn
  spr->fillRoundRect(cx - 15, by + 28, 9, 10, 4, C_YEL_DARK);
  spr->fillRoundRect(cx - 14, by + 27, 8, 9, 4, C_YELLOW);
  spr->fillRoundRect(cx + 6, by + 28, 9, 10, 4, C_YEL_DARK);
  spr->fillRoundRect(cx + 6, by + 27, 8, 9, 4, C_YELLOW);

  // 4. Khối đầu tròn phúng phính
  spr->fillEllipse(cx, by - 6, (int)(24 * sX), (int)(20 * sY), C_YEL_DARK);
  spr->fillEllipse(cx, by - 8, (int)(22 * sX), (int)(18 * sY), C_YELLOW);
  spr->fillEllipse(cx, by - 12, (int)(16 * sX), (int)(10 * sY), C_YEL_LGT);

  // 5. Đôi tai dài nhọn với chóp đen
  // Tai trái
  spr->fillTriangle(cx - 14, by - 18, cx - 26, by - 44, cx - 6, by - 22, C_YEL_DARK);
  spr->fillTriangle(cx - 13, by - 19, cx - 25, by - 42, cx - 7, by - 22, C_YELLOW);
  spr->fillTriangle(cx - 20, by - 32, cx - 25, by - 42, cx - 15, by - 35, C_BLACK);
  // Tai phải vểnh ngang kiêu hãnh
  spr->fillTriangle(cx + 6, by - 22, cx + 32, by - 38, cx + 14, by - 18, C_YEL_DARK);
  spr->fillTriangle(cx + 7, by - 22, cx + 30, by - 36, cx + 13, by - 18, C_YELLOW);
  spr->fillTriangle(cx + 20, by - 30, cx + 30, by - 36, cx + 22, by - 24, C_BLACK);

  // 6. Hai má đỏ rực tròn xoe (Túi điện 100,000 Volt)
  spr->fillCircle(cx - 16, by + 2, 7, C_RED_SHAD);
  spr->fillCircle(cx - 16, by + 1, 6, C_RED_CHEEK);
  spr->fillCircle(cx + 16, by + 2, 7, C_RED_SHAD);
  spr->fillCircle(cx + 16, by + 1, 6, C_RED_CHEEK);

  // 7. Đôi mắt pha lê to tròn đen sâu
  if (!blink) {
    spr->fillEllipse(cx - 10, by - 8, 4, 6, C_BLACK);
    spr->fillCircle(cx - 11, by - 11, 2, C_WHITE);
    spr->fillEllipse(cx + 10, by - 8, 4, 6, C_BLACK);
    spr->fillCircle(cx + 9, by - 11, 2, C_WHITE);
  } else {
    spr->drawEllipse(cx - 10, by - 7, 4, 2, C_BLACK);
    spr->drawEllipse(cx + 10, by - 7, 4, 2, C_BLACK);
  }

  // 8. Mũi & Miệng cười há rộng vui tươi
  spr->drawPixel(cx, by - 4, C_BLACK);
  spr->fillTriangle(cx, by + 8, cx - 6, by + 1, cx + 6, by + 1, C_MOUTH_DARK);
  spr->fillCircle(cx, by + 6, 3, C_TONGUE);

  // 9. Hai tay nhỏ xòe đón nhận năng lượng
  spr->fillCircle(cx - 12, by + 12, 4, C_YELLOW);
  spr->fillCircle(cx + 12, by + 12, 4, C_YELLOW);
}

// -------------------------------------------------------------
// Eevee - Cáo Bông Bờm Trắng
// -------------------------------------------------------------
static void drawEeveeFluffyClay(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Đuôi chổi lông cáo đung đưa trễ pha
  float tailLag = breathPhase - 0.45f;
  int tailSwayX = (int)(sinf(tailLag) * 6.0f);
  int tailSwayY = (int)(cosf(tailLag) * 3.5f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_BROWN      = 0xB420; // #B45309 Lông nâu hạt dẻ
  const uint16_t C_BROWN_DARK = 0x7202; // #713F12 Bóng lông nâu
  const uint16_t C_BROWN_LGT  = 0xD566; // #D97706 Sáng lông nâu
  const uint16_t C_CREAM      = 0xFF97; // #FEF08A Bờm cổ kem xốp
  const uint16_t C_CREAM_SHAD = 0xEE73; // #FDE047 Bóng bờm kem
  const uint16_t C_BLACK      = 0x18C3; // #1E293B Tai đen & mắt
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Bắt sáng & chóp đuôi
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Chiếc đuôi chổi lông khổng lồ vểnh sau lưng
  int tx = cx + 18 + tailSwayX;
  int ty = by - 2 + tailSwayY;
  spr->fillEllipse(tx, ty, 16, 26, C_BROWN_DARK);
  spr->fillEllipse(tx - 2, ty - 2, 14, 24, C_BROWN);
  // Chóp đuôi kem xốp
  spr->fillTriangle(tx + 4, ty - 18, tx + 14, ty - 32, tx - 4, ty - 22, C_CREAM);
  spr->fillEllipse(tx + 4, ty - 22, 8, 10, C_CREAM);

  // 3. Thân nâu 4 chân vững chãi
  spr->fillEllipse(cx, by + 18, (int)(18 * sX), (int)(16 * sY), C_BROWN_DARK);
  spr->fillEllipse(cx, by + 16, (int)(16 * sX), (int)(14 * sY), C_BROWN);
  // 4 chân nhỏ
  spr->fillRoundRect(cx - 16, by + 26, 7, 12, 3, C_BROWN);
  spr->fillRoundRect(cx - 7,  by + 26, 7, 12, 3, C_BROWN);
  spr->fillRoundRect(cx + 2,  by + 26, 7, 12, 3, C_BROWN);
  spr->fillRoundRect(cx + 11, by + 26, 7, 12, 3, C_BROWN);

  // 4. Bờm cổ kem xốp bồng bềnh như đám mây (Fluffy Ruff Collar)
  spr->fillCircle(cx - 14, by + 8, 10, C_CREAM_SHAD);
  spr->fillCircle(cx - 14, by + 7, 9,  C_CREAM);
  spr->fillCircle(cx + 14, by + 8, 10, C_CREAM_SHAD);
  spr->fillCircle(cx + 14, by + 7, 9,  C_CREAM);
  spr->fillCircle(cx,      by + 12, 11, C_CREAM_SHAD);
  spr->fillCircle(cx,      by + 11, 10, C_CREAM);

  // 5. Khối đầu cáo tròn xoe
  spr->fillEllipse(cx, by - 8, (int)(22 * sX), (int)(18 * sY), C_BROWN_DARK);
  spr->fillEllipse(cx, by - 10, (int)(20 * sX), (int)(16 * sY), C_BROWN);
  spr->fillEllipse(cx, by - 14, (int)(14 * sX), (int)(8 * sY), C_BROWN_LGT);

  // 6. Đôi tai cáo dài vươn cao với lòng tai đen
  // Tai trái
  spr->fillTriangle(cx - 14, by - 20, cx - 32, by - 48, cx - 4, by - 24, C_BROWN);
  spr->fillTriangle(cx - 15, by - 22, cx - 28, by - 44, cx - 8, by - 26, C_BLACK);
  // Tai phải
  spr->fillTriangle(cx + 4,  by - 24, cx + 32, by - 48, cx + 14, by - 20, C_BROWN);
  spr->fillTriangle(cx + 8,  by - 26, cx + 28, by - 44, cx + 15, by - 22, C_BLACK);

  // 7. Chỏm lông bờm trán nhọn
  spr->fillTriangle(cx - 4, by - 24, cx, by - 32, cx + 4, by - 24, C_BROWN);

  // 8. Đôi mắt hổ phách to tròn đen sâu
  if (!blink) {
    spr->fillEllipse(cx - 9, by - 10, 4, 7, C_BLACK);
    spr->fillCircle(cx - 10, by - 13, 2, C_WHITE);
    spr->fillEllipse(cx + 9, by - 10, 4, 7, C_BLACK);
    spr->fillCircle(cx + 8, by - 13, 2, C_WHITE);
  } else {
    spr->drawEllipse(cx - 9, by - 9, 4, 2, C_BLACK);
    spr->drawEllipse(cx + 9, by - 9, 4, 2, C_BLACK);
  }

  // 9. Mũi & Miệng cười bẽn lẽn
  spr->drawPixel(cx, by - 5, C_BLACK);
  spr->drawLine(cx - 3, by - 2, cx, by - 1, C_BLACK);
  spr->drawLine(cx, by - 1, cx + 3, by - 2, C_BLACK);
}

// -------------------------------------------------------------
// Bulbasaur - Ếch Mầm Xanh Hạt Nụ
// -------------------------------------------------------------
static void drawBulbasaurFlowerBud(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.1f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 2.5f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_TEAL       = 0x2D77; // #2DD4BF Xanh lam ngọc thân
  const uint16_t C_TEAL_DARK  = 0x0C71; // #0D9488 Bóng thân
  const uint16_t C_GREEN_BUD  = 0x25E7; // #22C55E Hạt nụ xanh lá
  const uint16_t C_BUD_DARK   = 0x1407; // #15803D Bóng nụ
  const uint16_t C_BUD_LGT    = 0x4EF0; // #4ADE80 Sáng đỉnh nụ
  const uint16_t C_SPOT_GREEN = 0x0BCB; // #0F766E Đốm xanh đậm
  const uint16_t C_RED_EYE    = 0xF9A6; // #EF4444 Mắt đỏ ruby
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Bắt sáng & móng
  const uint16_t C_MOUTH_DARK = 0x8887; // #881337 Khoang miệng
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(28 * (1.0f - 0.15f * breathSin)), 7, C_SHADOW);

  // 2. Hạt nụ hoa khổng lồ trên lưng (Bulb)
  spr->fillEllipse(cx + 8, by - 8, 16, 22, C_BUD_DARK);
  spr->fillEllipse(cx + 6, by - 10, 14, 20, C_GREEN_BUD);
  spr->fillTriangle(cx, by - 24, cx + 16, by - 36, cx + 18, by - 18, C_BUD_LGT);

  // 3. Thân ếch ngọc 4 chân vững vàng
  spr->fillEllipse(cx - 4, by + 16, (int)(22 * sX), (int)(18 * sY), C_TEAL_DARK);
  spr->fillEllipse(cx - 4, by + 14, (int)(20 * sX), (int)(16 * sY), C_TEAL);
  // 4 Chân ngắn với móng trắng
  spr->fillRoundRect(cx - 20, by + 24, 9, 12, 4, C_TEAL);
  spr->fillRoundRect(cx - 9,  by + 24, 9, 12, 4, C_TEAL);
  spr->fillRoundRect(cx + 4,  by + 24, 9, 12, 4, C_TEAL);
  spr->fillRoundRect(cx + 14, by + 24, 9, 12, 4, C_TEAL);

  // 4. Khối đầu rộng ngộ nghĩnh
  spr->fillEllipse(cx - 6, by - 6, (int)(22 * sX), (int)(18 * sY), C_TEAL_DARK);
  spr->fillEllipse(cx - 6, by - 8, (int)(20 * sX), (int)(16 * sY), C_TEAL);

  // 5. Hai tai nhọn nhỏ trên đỉnh đầu
  spr->fillTriangle(cx - 20, by - 18, cx - 26, by - 32, cx - 12, by - 20, C_TEAL);
  spr->fillTriangle(cx,      by - 20, cx + 6,  by - 32, cx + 12, by - 18, C_TEAL);

  // 6. Đốm xanh lục bảo trên trán và thân
  spr->fillTriangle(cx - 10, by - 18, cx - 6, by - 24, cx - 2, by - 18, C_SPOT_GREEN);
  spr->fillTriangle(cx - 16, by + 8,  cx - 12, by + 2,  cx - 8, by + 8,  C_SPOT_GREEN);

  // 7. Đôi mắt đỏ tam giác ngây thơ
  if (!blink) {
    spr->fillTriangle(cx - 16, by - 14, cx - 6, by - 14, cx - 14, by - 2, C_RED_EYE);
    spr->fillCircle(cx - 11, by - 11, 2, C_WHITE);
    spr->fillTriangle(cx + 2,  by - 14, cx + 12, by - 14, cx + 4,  by - 2, C_RED_EYE);
    spr->fillCircle(cx + 7,  by - 11, 2, C_WHITE);
  } else {
    spr->drawLine(cx - 16, by - 6, cx - 6, by - 6, C_TEAL_DARK);
    spr->drawLine(cx + 2,  by - 6, cx + 12, by - 6, C_TEAL_DARK);
  }

  // 8. Miệng cười rộng với răng nanh nhỏ
  spr->fillTriangle(cx - 6, by + 6, cx - 14, by + 1, cx + 2, by + 1, C_MOUTH_DARK);
  spr->fillRect(cx - 12, by + 1, 2, 2, C_WHITE);
  spr->fillRect(cx,      by + 1, 2, 2, C_WHITE);
}

// -------------------------------------------------------------
// Charmander - Khủng Long Lửa Đuôi Cháy
// -------------------------------------------------------------
static void drawCharmanderEmberTail(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.4f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Ngọn lửa đuôi bập bùng trễ pha
  float flamePhase = angle * 5.0f;
  int flameWiggle = (int)(sinf(flamePhase) * 3.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_ORANGE      = 0xF442; // #F97316 Cam rực lửa thân
  const uint16_t C_ORANGE_DARK = 0xC2E0; // #C2410C Bóng thân cam
  const uint16_t C_BELLY       = 0xFF97; // #FEF08A Bụng vàng kem
  const uint16_t C_FLAME_RED   = 0xF9A6; // #EF4444 Ngọn lửa đỏ
  const uint16_t C_FLAME_YEL   = 0xFFE0; // #FACC15 Lõi lửa vàng
  const uint16_t C_EYE_BLUE    = 0x0419; // #0284C7 Mắt xanh sapphire
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Bắt sáng & móng
  const uint16_t C_MOUTH_DARK  = 0x8887; // #881337 Khoang miệng
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Đuôi uốn lượn với ngọn lửa cháy bập bùng
  spr->fillRoundRect(cx + 12, by + 20, 16, 6, 3, C_ORANGE);
  spr->fillRoundRect(cx + 22, by + 10, 8, 14, 3, C_ORANGE);
  // Ngọn lửa chóp đuôi
  int fx = cx + 26 + flameWiggle;
  int fy = by + 2;
  spr->fillTriangle(fx - 6, fy + 8, fx, fy - 18, fx + 8, fy + 8, C_FLAME_RED);
  spr->fillTriangle(fx - 4, fy + 6, fx + 2, fy - 12, fx + 6, fy + 6, C_FLAME_YEL);

  // 3. Thân cam mũm mĩm & bụng vàng kem
  spr->fillEllipse(cx - 2, by + 16, (int)(20 * sX), (int)(18 * sY), C_ORANGE_DARK);
  spr->fillEllipse(cx - 2, by + 14, (int)(18 * sX), (int)(16 * sY), C_ORANGE);
  // Bụng vàng kem
  spr->fillEllipse(cx - 6, by + 16, (int)(10 * sX), (int)(14 * sY), C_BELLY);
  // 2 chân vững chãi
  spr->fillRoundRect(cx - 16, by + 28, 10, 10, 4, C_ORANGE);
  spr->fillRoundRect(cx + 2,  by + 28, 10, 10, 4, C_ORANGE);

  // 4. Khối đầu thằn lằn tròn xoe
  spr->fillEllipse(cx - 4, by - 8, (int)(20 * sX), (int)(18 * sY), C_ORANGE_DARK);
  spr->fillEllipse(cx - 4, by - 10, (int)(18 * sX), (int)(16 * sY), C_ORANGE);

  // 5. Đôi mắt xanh thẳm sapphire to tròn
  if (!blink) {
    spr->fillEllipse(cx - 10, by - 10, 4, 7, C_EYE_BLUE);
    spr->fillCircle(cx - 11, by - 13, 2, C_WHITE);
    spr->fillEllipse(cx + 4,  by - 10, 4, 7, C_EYE_BLUE);
    spr->fillCircle(cx + 3,  by - 13, 2, C_WHITE);
  } else {
    spr->drawEllipse(cx - 10, by - 9, 4, 2, C_ORANGE_DARK);
    spr->drawEllipse(cx + 4,  by - 9, 4, 2, C_ORANGE_DARK);
  }

  // 6. Miệng cười rộng nhe răng nanh
  spr->fillTriangle(cx - 4, by + 6, cx - 12, by + 1, cx + 4, by + 1, C_MOUTH_DARK);
  spr->fillRect(cx - 10, by + 1, 2, 2, C_WHITE);
  spr->fillRect(cx + 2,  by + 1, 2, 2, C_WHITE);

  // 7. Hai tay nhỏ dang rộng
  spr->fillCircle(cx - 14, by + 10, 4, C_ORANGE);
  spr->fillCircle(cx + 8,  by + 10, 4, C_ORANGE);
}

// -------------------------------------------------------------
// Squirtle - Rùa Nước Mai Nâu
// -------------------------------------------------------------
static void drawSquirtleWaterTurtle(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 2.8f);
  int by = cy + bounceY;

  // Đuôi cuộn sóng nước lắc lư trễ pha
  float tailLag = breathPhase - 0.45f;
  int tailSwayX = (int)(sinf(tailLag) * 5.0f);
  int tailSwayY = (int)(cosf(tailLag) * 3.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_CYAN_BODY  = 0x3EDB; // #38BDF8 Lam ngọc nước
  const uint16_t C_CYAN_DARK  = 0x0396; // #0284C7 Bóng lam
  const uint16_t C_SHELL_BRN  = 0x9200; // #92400E Mai rùa nâu
  const uint16_t C_SHELL_RIM  = 0xFFFF; // #FFFFFF Viền mai trắng
  const uint16_t C_BELLY_YEL  = 0xFF97; // #FEF08A Yếm bụng vàng kem
  const uint16_t C_EYE_RED    = 0xB8A0; // #B91C1C Mắt đỏ nâu
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Bắt sáng
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Chiếc mai rùa nâu viền trắng sau lưng
  spr->fillEllipse(cx + 8, by + 10, 16, 20, C_SHELL_RIM);
  spr->fillEllipse(cx + 10, by + 10, 14, 18, C_SHELL_BRN);

  // 3. Đuôi cuộn tròn xoáy nước uốn lượn sau lưng
  int tx = cx + 22 + tailSwayX;
  int ty = by + 14 + tailSwayY;
  spr->fillCircle(tx, ty, 10, C_CYAN_BODY);
  spr->drawCircle(tx, ty, 6, C_CYAN_DARK);

  // 4. Thân rùa xanh nước biển & yếm bụng vàng kem
  spr->fillEllipse(cx - 4, by + 16, (int)(18 * sX), (int)(16 * sY), C_CYAN_DARK);
  spr->fillEllipse(cx - 4, by + 14, (int)(16 * sX), (int)(14 * sY), C_CYAN_BODY);
  // Yếm bụng vàng kem phân múi
  spr->fillEllipse(cx - 8, by + 14, (int)(10 * sX), (int)(12 * sY), C_BELLY_YEL);
  // Hai chân ngắn
  spr->fillRoundRect(cx - 18, by + 26, 9, 10, 4, C_CYAN_BODY);
  spr->fillRoundRect(cx - 2,  by + 26, 9, 10, 4, C_CYAN_BODY);

  // 5. Khối đầu tròn bóng bẩy
  spr->fillEllipse(cx - 6, by - 8, (int)(22 * sX), (int)(18 * sY), C_CYAN_DARK);
  spr->fillEllipse(cx - 6, by - 10, (int)(20 * sX), (int)(16 * sY), C_CYAN_BODY);

  // 6. Đôi mắt đỏ nâu to tròn
  if (!blink) {
    spr->fillEllipse(cx - 12, by - 10, 4, 7, C_EYE_RED);
    spr->fillCircle(cx - 13, by - 13, 2, C_WHITE);
    spr->fillEllipse(cx + 2,  by - 10, 4, 7, C_EYE_RED);
    spr->fillCircle(cx + 1,  by - 13, 2, C_WHITE);
  } else {
    spr->drawEllipse(cx - 12, by - 9, 4, 2, C_CYAN_DARK);
    spr->drawEllipse(cx + 2,  by - 9, 4, 2, C_CYAN_DARK);
  }

  // 7. Mỏ rùa cười thân thiện
  spr->drawLine(cx - 14, by - 2, cx - 4, by, C_CYAN_DARK);
  spr->drawLine(cx - 4,  by, cx + 4,  by - 2, C_CYAN_DARK);

  // 8. Hai tay bơi dang rộng
  spr->fillCircle(cx - 18, by + 8, 4, C_CYAN_BODY);
  spr->fillCircle(cx + 4,  by + 8, 4, C_CYAN_BODY);
}

} // namespace Session4Mythics
