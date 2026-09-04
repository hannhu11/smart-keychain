#pragma once
// ============================================================================
// SESSION 5 JOHTO & BELOVED ICONS - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 ST7789 IPS LCD (172x320 60FPS DMA)
// Pop Mart & Kawaii Visual DNA: Volumetric 4-Tone Shading & Crystal Catchlights
// Characters: Togepi, Mew, Snorlax, Gengar, Jigglypuff (IDs 70 to 74)
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace Session5Mythics {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// -------------------------------------------------------------
// Togepi - Trứng Hạnh Phúc Vỏ Hoa
// -------------------------------------------------------------
static void drawTogepiSpottedEgg(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.3f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_WHITE_SHELL = 0xFFFF; // #FFFFFF Vỏ trứng men sứ
  const uint16_t C_SHELL_SHAD  = 0xCE79; // #CBD5E1 Bóng vỏ trứng
  const uint16_t C_BODY_YEL    = 0xFF97; // #FEF08A Thân vàng kem
  const uint16_t C_BODY_SHAD   = 0xEE73; // #FDE047 Bóng thân
  const uint16_t C_RED_SPOT    = 0xF9A6; // #EF4444 Đốm đỏ vỏ trứng
  const uint16_t C_BLUE_SPOT   = 0x3EDB; // #38BDF8 Đốm lam vỏ trứng
  const uint16_t C_BLACK       = 0x10A2; // #0F172A Mắt đen
  const uint16_t C_MOUTH_DARK  = 0x8887; // #881337 Miệng
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Hai bàn chân nhỏ vàng kem
  spr->fillRoundRect(cx - 16, by + 30, 10, 8, 3, C_BODY_SHAD);
  spr->fillRoundRect(cx + 6,  by + 30, 10, 8, 3, C_BODY_SHAD);

  // 3. Khối đầu vàng kem với 5 chóp nhọn hình sao
  spr->fillEllipse(cx, by - 12, (int)(18 * sX), (int)(16 * sY), C_BODY_YEL);
  // 5 Chóp gai đầu sao
  spr->fillTriangle(cx - 20, by - 14, cx - 26, by - 32, cx - 12, by - 18, C_BODY_YEL);
  spr->fillTriangle(cx - 14, by - 18, cx - 10, by - 38, cx - 2,  by - 20, C_BODY_YEL);
  spr->fillTriangle(cx - 4,  by - 20, cx,      by - 40, cx + 4,  by - 20, C_BODY_YEL);
  spr->fillTriangle(cx + 2,  by - 20, cx + 10, by - 38, cx + 14, by - 18, C_BODY_YEL);
  spr->fillTriangle(cx + 12, by - 18, cx + 26, by - 32, cx + 20, by - 14, C_BODY_YEL);

  // 4. Vỏ trứng tròn xoe men sứ trắng bao quanh thân dưới
  spr->fillEllipse(cx, by + 12, (int)(24 * sX), (int)(22 * sY), C_SHELL_SHAD);
  spr->fillEllipse(cx, by + 10, (int)(22 * sX), (int)(20 * sY), C_WHITE_SHELL);
  // Mép vỏ trứng nứt zigzag
  spr->fillTriangle(cx - 18, by - 2, cx - 12, by - 8, cx - 6,  by - 2, C_WHITE_SHELL);
  spr->fillTriangle(cx - 6,  by - 2, cx,      by - 8, cx + 6,  by - 2, C_WHITE_SHELL);
  spr->fillTriangle(cx + 6,  by - 2, cx + 12, by - 8, cx + 18, by - 2, C_WHITE_SHELL);

  // 5. Hoa văn đốm tam giác & hình vuông đỏ, lam trên vỏ trứng
  // Tam giác lam giữa
  spr->fillTriangle(cx - 8, by + 8, cx + 2, by + 2, cx - 2, by + 18, C_BLUE_SPOT);
  // Khối đỏ bên phải
  spr->fillRect(cx + 8, by + 4, 8, 8, C_RED_SPOT);
  // Tam giác đỏ bên trái
  spr->fillTriangle(cx - 16, by + 6, cx - 12, by + 2, cx - 10, by + 12, C_RED_SPOT);
  // Tam giác lam dưới phải
  spr->fillTriangle(cx + 4, by + 18, cx + 14, by + 14, cx + 10, by + 24, C_BLUE_SPOT);

  // 6. Đôi mắt to tròn đen sâu
  if (!blink) {
    spr->fillEllipse(cx - 8, by - 16, 3, 6, C_BLACK);
    spr->fillCircle(cx - 9, by - 18, 1, C_WHITE_SHELL);
    spr->fillEllipse(cx + 8, by - 16, 3, 6, C_BLACK);
    spr->fillCircle(cx + 7, by - 18, 1, C_WHITE_SHELL);
  } else {
    spr->drawLine(cx - 10, by - 15, cx - 6, by - 15, C_BLACK);
    spr->drawLine(cx + 6,  by - 15, cx + 10, by - 15, C_BLACK);
  }

  // 7. Miệng cười chữ V xinh xắn
  spr->fillTriangle(cx, by - 8, cx - 4, by - 12, cx + 4, by - 12, C_MOUTH_DARK);

  // 8. Hai tay nhỏ dang rộng vui vẻ
  spr->fillCircle(cx - 20, by - 2, 4, C_BODY_YEL);
  spr->fillCircle(cx + 20, by - 2, 4, C_BODY_YEL);
}

// -------------------------------------------------------------
// Mew - Mèo Tiên Hồng Không Trọng Lực
// -------------------------------------------------------------
static void drawMewCelestialPink(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.0f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 4.0f);
  int by = cy + bounceY;

  // Đuôi dài uốn lượn bay không trọng lực trễ pha
  float tailLag = breathPhase - 0.45f;
  int tailSwayX = (int)(sinf(tailLag) * 8.0f);
  int tailSwayY = (int)(cosf(tailLag) * 5.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_PINK       = 0xFBB6; // #F472B6 Hồng pastel chủ đạo
  const uint16_t C_PINK_DARK  = 0xD212; // #E11D48 Bóng hồng
  const uint16_t C_PINK_LGT   = 0xFDF7; // #FBCFE8 Sáng hồng men sứ
  const uint16_t C_EYE_BLUE   = 0x0419; // #0284C7 Mắt sapphire xanh ngọc
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Bắt sáng
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc mờ ảo
  spr->fillEllipse(cx, cy + 42, (int)(22 * (1.0f - 0.15f * breathSin)), 5, C_SHADOW);

  // 2. Chiếc đuôi dài uốn cong vòng lên trên đầu
  int tx = cx + tailSwayX;
  int ty = by - 16 + tailSwayY;
  spr->drawCircle(tx + 4, ty, 20, C_PINK);
  spr->drawCircle(tx + 4, ty, 19, C_PINK);
  // Chóp đuôi hình oval dẹp
  spr->fillEllipse(tx - 12, ty - 18, 6, 10, C_PINK);
  spr->fillEllipse(tx - 13, ty - 19, 4, 8,  C_PINK_LGT);

  // 3. Thân mèo tiên thon gọn không trọng lực
  spr->fillEllipse(cx, by + 12, (int)(14 * sX), (int)(16 * sY), C_PINK_DARK);
  spr->fillEllipse(cx, by + 10, (int)(12 * sX), (int)(14 * sY), C_PINK);
  // Hai chân sau thon dài kiểu kangaroo
  spr->fillRoundRect(cx - 10, by + 20, 6, 16, 3, C_PINK);
  spr->fillRoundRect(cx + 4,  by + 20, 6, 16, 3, C_PINK);

  // 4. Khối đầu mèo tròn phúng phính
  spr->fillEllipse(cx - 2, by - 10, (int)(20 * sX), (int)(16 * sY), C_PINK_DARK);
  spr->fillEllipse(cx - 2, by - 12, (int)(18 * sX), (int)(14 * sY), C_PINK);
  spr->fillEllipse(cx - 4, by - 15, (int)(12 * sX), (int)(8 * sY),  C_PINK_LGT);

  // 5. Đôi tai mèo tam giác nhỏ xinh
  spr->fillTriangle(cx - 16, by - 18, cx - 22, by - 30, cx - 10, by - 22, C_PINK);
  spr->fillTriangle(cx + 6,  by - 22, cx + 16, by - 30, cx + 14, by - 18, C_PINK);

  // 6. Đôi mắt sapphire xanh ngọc to tròn
  if (!blink) {
    spr->fillEllipse(cx - 8, by - 12, 4, 7, C_EYE_BLUE);
    spr->fillCircle(cx - 9, by - 15, 2, C_WHITE);
    spr->fillEllipse(cx + 4,  by - 12, 4, 7, C_EYE_BLUE);
    spr->fillCircle(cx + 3,  by - 15, 2, C_WHITE);
  } else {
    spr->drawEllipse(cx - 8, by - 11, 4, 2, C_PINK_DARK);
    spr->drawEllipse(cx + 4,  by - 11, 4, 2, C_PINK_DARK);
  }

  // 7. Mõm & Nụ cười bẽn lẽn
  spr->drawLine(cx - 4, by - 5, cx - 1, by - 4, C_PINK_DARK);
  spr->drawLine(cx - 1, by - 4, cx + 2, by - 5, C_PINK_DARK);

  // 8. Hai bàn tay nhỏ buông lỏng không trọng lực
  spr->fillCircle(cx - 8, by + 4, 3, C_PINK);
  spr->fillCircle(cx + 4, by + 4, 3, C_PINK);
}

// -------------------------------------------------------------
// Snorlax - Gấu Lười Ngủ Khổng Lồ
// -------------------------------------------------------------
static void drawSnorlaxSoftGiant(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 1.6f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.06f * breathSin;
  float sX = 1.0f - 0.03f * breathSin;
  int by = cy;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_TEAL_BODY  = 0x0BEB; // #0E7490 Xanh lam thẫm
  const uint16_t C_TEAL_DARK  = 0x028A; // #155E75 Bóng thân
  const uint16_t C_BELLY_CREAM = 0xFF97; // #FEF08A Bụng & mặt kem
  const uint16_t C_BELLY_SHAD  = 0xEE73; // #FDE047 Bóng bụng
  const uint16_t C_BROWN_PAD   = 0x9B84; // #A16207 Đệm chân nâu
  const uint16_t C_BLACK       = 0x08E5; // #0F172A Mắt nhắm
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Răng nanh & móng
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc khổng lồ
  spr->fillEllipse(cx, cy + 42, (int)(32 * (1.0f - 0.15f * breathSin)), 8, C_SHADOW);

  // 2. Thân béo tròn khổng lồ núng nính
  spr->fillEllipse(cx, by + 16, (int)(30 * sX), (int)(24 * sY), C_TEAL_DARK);
  spr->fillEllipse(cx, by + 14, (int)(28 * sX), (int)(22 * sY), C_TEAL_BODY);
  // Bụng kem siêu to
  spr->fillEllipse(cx, by + 16, (int)(22 * sX), (int)(18 * sY), C_BELLY_SHAD);
  spr->fillEllipse(cx, by + 15, (int)(20 * sX), (int)(16 * sY), C_BELLY_CREAM);

  // 3. Hai bàn chân khổng lồ hướng về trước với đệm nâu
  spr->fillCircle(cx - 22, by + 30, 10, C_BELLY_CREAM);
  spr->fillCircle(cx - 22, by + 30, 6,  C_BROWN_PAD);
  spr->fillCircle(cx + 22, by + 30, 10, C_BELLY_CREAM);
  spr->fillCircle(cx + 22, by + 30, 6,  C_BROWN_PAD);

  // 4. Khối đầu tròn ngủ say
  spr->fillEllipse(cx, by - 10, (int)(22 * sX), (int)(16 * sY), C_TEAL_DARK);
  spr->fillEllipse(cx, by - 12, (int)(20 * sX), (int)(14 * sY), C_TEAL_BODY);
  // Mặt nạ kem
  spr->fillEllipse(cx, by - 11, (int)(14 * sX), (int)(10 * sY), C_BELLY_CREAM);

  // 5. Hai tai gấu nhọn
  spr->fillTriangle(cx - 16, by - 20, cx - 22, by - 34, cx - 8, by - 22, C_TEAL_BODY);
  spr->fillTriangle(cx + 8,  by - 22, cx + 22, by - 34, cx + 16, by - 20, C_TEAL_BODY);

  // 6. Đôi mắt nhắm tít ngủ say & Nụ cười mãn nguyện
  spr->drawLine(cx - 10, by - 13, cx - 4, by - 13, C_BLACK);
  spr->drawLine(cx + 4,  by - 13, cx + 10, by - 13, C_BLACK);
  spr->drawLine(cx - 6,  by - 7,  cx + 6,  by - 7,  C_BLACK);
  // 2 chiếc răng nanh nhỏ nhô lên
  spr->fillTriangle(cx - 5, by - 7, cx - 4, by - 10, cx - 3, by - 7, C_WHITE);
  spr->fillTriangle(cx + 3, by - 7, cx + 4, by - 10, cx + 5, by - 7, C_WHITE);

  // 7. Hai tay buông thõng hai bên sườn
  spr->fillRoundRect(cx - 30, by + 8, 10, 16, 5, C_TEAL_BODY);
  spr->fillRoundRect(cx + 20, by + 8, 10, 16, 5, C_TEAL_BODY);
}

// -------------------------------------------------------------
// Gengar - Bóng Ma Tím Nụ Cười Gian
// -------------------------------------------------------------
static void drawGengarNeonShadow(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.3f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.5f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_PURPLE     = 0x7919; // #7E22CE Tím bóng ma chủ đạo
  const uint16_t C_PURP_DARK  = 0x50CD; // #581C87 Bóng tím thẫm
  const uint16_t C_PURP_LGT   = 0x91B7; // #9333EA Sáng tím viền
  const uint16_t C_RED_EYE    = 0xF9A6; // #EF4444 Mắt đỏ ruby
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Hàm răng trắng
  const uint16_t C_BLACK      = 0x08E5; // #0F172A Khoang miệng & đồng tử
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc mờ ảo
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Gai lưng nhọn hoắt sau lưng
  spr->fillTriangle(cx - 10, by - 20, cx,      by - 38, cx + 10, by - 20, C_PURPLE);
  spr->fillTriangle(cx + 8,  by - 10, cx + 28, by - 16, cx + 12, by + 4,  C_PURPLE);
  spr->fillTriangle(cx - 8,  by - 10, cx - 28, by - 16, cx - 12, by + 4,  C_PURPLE);

  // 3. Khối thân bóng ma tròn phúng phính Pop Mart
  spr->fillEllipse(cx, by + 12, (int)(24 * sX), (int)(22 * sY), C_PURP_DARK);
  spr->fillEllipse(cx, by + 10, (int)(22 * sX), (int)(20 * sY), C_PURPLE);
  // Hai chân ngắn
  spr->fillRoundRect(cx - 16, by + 28, 9, 10, 4, C_PURPLE);
  spr->fillRoundRect(cx + 7,  by + 28, 9, 10, 4, C_PURPLE);

  // 4. Khối đầu tròn nối liền thân & Đôi tai nhọn
  spr->fillEllipse(cx, by - 6, (int)(22 * sX), (int)(18 * sY), C_PURP_DARK);
  spr->fillEllipse(cx, by - 8, (int)(20 * sX), (int)(16 * sY), C_PURPLE);
  // Đôi tai nhọn vươn cao
  spr->fillTriangle(cx - 16, by - 18, cx - 26, by - 40, cx - 8, by - 22, C_PURPLE);
  spr->fillTriangle(cx + 8,  by - 22, cx + 26, by - 40, cx + 16, by - 18, C_PURPLE);

  // 5. Đôi mắt đỏ trăng khuyết tinh nghịch
  if (!blink) {
    spr->fillTriangle(cx - 16, by - 12, cx - 6, by - 16, cx - 6, by - 4, C_RED_EYE);
    spr->fillCircle(cx - 9, by - 10, 2, C_BLACK);
    spr->fillTriangle(cx + 16, by - 12, cx + 6, by - 16, cx + 6, by - 4, C_RED_EYE);
    spr->fillCircle(cx + 9, by - 10, 2, C_BLACK);
  } else {
    spr->drawLine(cx - 16, by - 10, cx - 6, by - 10, C_PURP_DARK);
    spr->drawLine(cx + 6,  by - 10, cx + 16, by - 10, C_PURP_DARK);
  }

  // 6. Nụ cười gian khổng lồ với hàm răng trắng muốt
  spr->fillRoundRect(cx - 18, by + 2, 36, 12, 6, C_WHITE);
  // Các đường kẽ răng
  spr->drawFastVLine(cx - 9, by + 2, 12, C_BLACK);
  spr->drawFastVLine(cx,     by + 2, 12, C_BLACK);
  spr->drawFastVLine(cx + 9, by + 2, 12, C_BLACK);
  spr->drawFastHLine(cx - 18, by + 8, 36, C_BLACK);

  // 7. Hai cánh tay nhỏ giơ lên hù dọa đáng yêu
  spr->fillCircle(cx - 18, by + 4, 5, C_PURPLE);
  spr->fillCircle(cx + 18, by + 4, 5, C_PURPLE);
}

// -------------------------------------------------------------
// Jigglypuff - Bóng Hồng Khúc Hát Ru
// -------------------------------------------------------------
static void drawJigglypuffBalloonSinger(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_PINK_BALL  = 0xFDB8; // #F472B6 Hồng bóng bay
  const uint16_t C_PINK_DARK  = 0xD212; // #E11D48 Bóng hồng
  const uint16_t C_PINK_LGT   = 0xFDF7; // #FBCFE8 Sáng hồng men sứ
  const uint16_t C_EAR_BLACK  = 0x10A2; // #0F172A Lòng tai đen
  const uint16_t C_AQUA_EYE   = 0x0599; // #06B6D4 Xanh ngọc biển mắt
  const uint16_t C_AQUA_DARK  = 0x0473; // #0891B2 Bóng mắt xanh
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Bắt sáng
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Hai chân nhỏ tròn vo
  spr->fillRoundRect(cx - 16, by + 28, 10, 8, 4, C_PINK_DARK);
  spr->fillRoundRect(cx + 6,  by + 28, 10, 8, 4, C_PINK_DARK);

  // 3. Đôi tai mèo tam giác với lòng tai đen
  spr->fillTriangle(cx - 20, by - 16, cx - 28, by - 36, cx - 12, by - 22, C_PINK_BALL);
  spr->fillTriangle(cx - 21, by - 18, cx - 26, by - 32, cx - 14, by - 22, C_EAR_BLACK);
  spr->fillTriangle(cx + 12, by - 22, cx + 28, by - 36, cx + 20, by - 16, C_PINK_BALL);
  spr->fillTriangle(cx + 14, by - 22, cx + 26, by - 32, cx + 21, by - 18, C_EAR_BLACK);

  // 4. Khối thân hình cầu bóng bay hoàn hảo
  spr->fillCircle(cx, by + 4, (int)(24 * sX), C_PINK_DARK);
  spr->fillCircle(cx, by + 2, (int)(22 * sX), C_PINK_BALL);
  spr->fillCircle(cx - 4, by - 2, (int)(14 * sX), C_PINK_LGT);

  // 5. Chỏm xoáy tóc bồng bềnh trước trán (Signature Curl)
  spr->fillCircle(cx, by - 16, 8, C_PINK_DARK);
  spr->fillCircle(cx, by - 17, 7, C_PINK_BALL);
  spr->fillCircle(cx - 2, by - 18, 4, C_PINK_LGT);

  // 6. Đôi mắt ngọc bích aqua khổng lồ siêu long lanh
  if (!blink) {
    // Vòng trắng quanh mắt
    spr->fillCircle(cx - 12, by - 2, 8, C_WHITE);
    spr->fillCircle(cx - 12, by - 2, 7, C_AQUA_DARK);
    spr->fillCircle(cx - 12, by - 2, 6, C_AQUA_EYE);
    spr->fillCircle(cx - 14, by - 4, 3, C_WHITE); // Bắt sáng lớn
    spr->fillCircle(cx - 10, by,      1, C_WHITE); // Bắt sáng nhỏ

    spr->fillCircle(cx + 12, by - 2, 8, C_WHITE);
    spr->fillCircle(cx + 12, by - 2, 7, C_AQUA_DARK);
    spr->fillCircle(cx + 12, by - 2, 6, C_AQUA_EYE);
    spr->fillCircle(cx + 10, by - 4, 3, C_WHITE);
    spr->fillCircle(cx + 14, by,      1, C_WHITE);
  } else {
    spr->drawEllipse(cx - 12, by - 2, 7, 2, C_PINK_DARK);
    spr->drawEllipse(cx + 12, by - 2, 7, 2, C_PINK_DARK);
  }

  // 7. Miệng cười nhỏ chúm chím
  spr->drawLine(cx - 3, by + 10, cx, by + 12, C_PINK_DARK);
  spr->drawLine(cx, by + 12, cx + 3, by + 10, C_PINK_DARK);

  // 8. Hai tay nhỏ xíu hạt đậu
  spr->fillCircle(cx - 20, by + 10, 4, C_PINK_BALL);
  spr->fillCircle(cx + 20, by + 10, 4, C_PINK_BALL);
}

} // namespace Session5Mythics
