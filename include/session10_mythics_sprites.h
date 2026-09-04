#pragma once
// ============================================================================
// SESSION 10 GRAND FINALE - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 ST7789 IPS LCD (172x320 60FPS DMA)
// Pop Mart & Kawaii Visual DNA: Volumetric 4-Tone Shading & Crystal Catchlights
// Characters: Mantine, Regice, Noctowl, Kecleon, Solgaleo (IDs 95 to 99 -> 100 Total Themes!)
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace Session10Mythics {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// -------------------------------------------------------------
// Mantine - Cá Đuối Cánh Tiên Đại Dương
// -------------------------------------------------------------
static void drawMantineCelestialRay(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.4f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.04f * breathSin;
  float sX = 1.0f - 0.02f * breathSin;
  int bounceY = (int)(sinf(breathPhase) * 3.5f);
  int by = cy + bounceY;

  // Cánh đuối vỗ nhịp đại dương
  int wingFlap = (int)(sinf(angle * 2.8f) * 4.5f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_NAVY_BACK   = 0x2357; // #1D4ED8 Lưng cá đuối xanh biển sâu
  const uint16_t C_LILAC_BELLY = 0xDEFB; // #E0E7FF Bụng trắng tím nhạt
  const uint16_t C_REMORAID    = 0x6436; // #64748B Cá nhỏ Remoraid bơi cùng
  const uint16_t C_BLACK_EYE   = 0x18C3; // #1E293B Mắt đen tròn
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Răng & Catchlight
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(32 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Đuôi cá đuối dài thướt tha uốn lượn sau lưng
  spr->fillTriangle(cx + 8, by + 12, cx + 34, by + 24, cx + 18, by + 18, C_NAVY_BACK);
  spr->fillCircle(cx + 34, by + 24, 4, C_LILAC_BELLY);

  // 3. Đôi cánh cá đuối khổng lồ sải rộng (Manta Wings)
  // Cánh trái
  int wly = by + wingFlap;
  spr->fillTriangle(cx - 6, by + 4, cx - 44, wly - 8, cx - 18, by + 16, C_NAVY_BACK);
  spr->fillTriangle(cx - 8, by + 6, cx - 42, wly - 6, cx - 18, by + 14, C_LILAC_BELLY);
  // Cánh phải
  int wry = by - wingFlap;
  spr->fillTriangle(cx + 6, by + 4, cx + 44, wry - 8, cx + 18, by + 16, C_NAVY_BACK);
  spr->fillTriangle(cx + 8, by + 6, cx + 42, wry - 6, cx + 18, by + 14, C_LILAC_BELLY);

  // 4. Cá nhỏ Remoraid bám dưới cánh phải
  spr->fillRoundRect(cx + 24, wry + 2, 10, 5, 2, C_REMORAID);
  spr->fillTriangle(cx + 34, wry + 4, cx + 38, wry + 1, cx + 38, wry + 7, C_REMORAID);

  // 5. Thân cá đuối tròn trĩnh bụ bẫm
  spr->fillEllipse(cx, by + 10, (int)(22 * sX), (int)(16 * sY), C_NAVY_BACK);
  spr->fillEllipse(cx, by + 12, (int)(19 * sX), (int)(14 * sY), C_LILAC_BELLY);

  // 6. Đôi ăng-ten sừng cong trên đầu
  spr->fillRoundRect(cx - 14, by - 16, 5, 14, 2, C_NAVY_BACK);
  spr->fillRoundRect(cx - 2,  by - 18, 5, 16, 2, C_NAVY_BACK);

  // 7. Khuôn mặt cười chúm chím với 2 chiếc răng nanh nhỏ dưới mép
  spr->drawCircle(cx - 8, by + 4, 3, C_NAVY_BACK);
  spr->fillRect(cx - 10, by + 1, 6, 3, C_LILAC_BELLY); // Mép cười
  spr->drawPixel(cx - 9, by + 3, C_WHITE); // Răng nhỏ

  // 8. Đôi mắt to tròn ngây thơ
  if (!blink) {
    spr->fillCircle(cx - 14, by + 2, 3, C_BLACK_EYE);
    spr->drawPixel(cx - 15, by + 1, C_WHITE);
    spr->fillCircle(cx + 4,  by + 2, 3, C_BLACK_EYE);
    spr->drawPixel(cx + 3,  by + 1, C_WHITE);
  } else {
    spr->drawLine(cx - 16, by + 2, cx - 12, by + 2, C_BLACK_EYE);
    spr->drawLine(cx + 2,  by + 2, cx + 6,  by + 2, C_BLACK_EYE);
  }
}

// -------------------------------------------------------------
// Regice - Băng Cực Cổ Thần Cương Băng
// -------------------------------------------------------------
static void drawRegiceGlacierGolem(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 1.6f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.03f * breathSin;
  float sX = 1.0f - 0.015f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 2.8f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_ICE_BLUE   = 0xBA3F; // #BAE6FD Khối băng xanh nhạt
  const uint16_t C_ICE_DARK   = 0x7EBF; // #7DD3FC Bóng khối băng
  const uint16_t C_ICE_SHAD   = 0x3CF3; // #38BDF8 Rãnh nứt băng sâu
  const uint16_t C_ICE_WHITE  = 0xFFFF; // #FFFFFF Cạnh phản quang kim cương
  const uint16_t C_EYE_YELLOW = 0xFE60; // #FACC15 7 Điểm sáng mắt vàng chữ thập
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 44, (int)(28 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. 4 Trụ băng sau lưng nhô ra như cánh (Back Ice Spikes)
  spr->fillTriangle(cx - 14, by - 6, cx - 28, by - 26, cx - 8,  by - 14, C_ICE_DARK);
  spr->fillTriangle(cx - 16, by + 4, cx - 30, by - 12, cx - 10, by - 2,  C_ICE_BLUE);

  spr->fillTriangle(cx + 14, by - 6, cx + 28, by - 26, cx + 8,  by - 14, C_ICE_DARK);
  spr->fillTriangle(cx + 16, by + 4, cx + 30, by - 12, cx + 10, by - 2,  C_ICE_BLUE);

  // 3. Hai chân trụ băng hình nón nhọn lơ lửng
  spr->fillTriangle(cx - 16, by + 20, cx - 10, by + 36, cx - 4,  by + 20, C_ICE_DARK);
  spr->fillTriangle(cx - 14, by + 20, cx - 10, by + 34, cx - 6,  by + 20, C_ICE_BLUE);

  spr->fillTriangle(cx + 4,  by + 20, cx + 10, by + 36, cx + 16, by + 20, C_ICE_DARK);
  spr->fillTriangle(cx + 6,  by + 20, cx + 10, by + 34, cx + 14, by + 20, C_ICE_BLUE);

  // 4. Khối thân tảng băng đa giác khổng lồ (Faceted Hexagonal Ice Body)
  // Đỉnh nón nhọn trên cùng
  spr->fillTriangle(cx - 14, by - 14, cx, by - 36, cx + 14, by - 14, C_ICE_DARK);
  spr->fillTriangle(cx - 12, by - 14, cx, by - 34, cx + 12, by - 14, C_ICE_BLUE);

  // Thân giữa đa giác
  spr->fillRoundRect(cx - 16, by - 14, 32, 34, 4, C_ICE_DARK);
  spr->fillRoundRect(cx - 14, by - 12, 28, 30, 3, C_ICE_BLUE);

  // Mặt vát băng sáng bên trái
  spr->fillTriangle(cx - 14, by - 12, cx - 6, by - 12, cx - 12, by + 16, C_ICE_WHITE);

  // 5. Hai cánh tay trụ băng đa giác vươn hai bên
  // Tay trái
  spr->fillRoundRect(cx - 32, by - 6, 14, 26, 4, C_ICE_DARK);
  spr->fillRoundRect(cx - 30, by - 4, 12, 22, 3, C_ICE_BLUE);
  spr->fillTriangle(cx - 34, by + 18, cx - 28, by + 28, cx - 24, by + 18, C_ICE_BLUE);

  // Tay phải
  spr->fillRoundRect(cx + 18, by - 6, 14, 26, 4, C_ICE_DARK);
  spr->fillRoundRect(cx + 18, by - 4, 12, 22, 3, C_ICE_BLUE);
  spr->fillTriangle(cx + 24, by + 18, cx + 28, by + 28, cx + 34, by + 18, C_ICE_BLUE);

  // 6. Chòm 7 điểm sáng mắt vàng hình chữ thập biểu tượng (Braille Eye Pattern)
  if (!blink) {
    // Điểm trung tâm
    spr->fillCircle(cx, by - 2, 2, C_EYE_YELLOW);
    // Điểm trên & dưới
    spr->fillCircle(cx, by - 8, 2, C_EYE_YELLOW);
    spr->fillCircle(cx, by + 4, 2, C_EYE_YELLOW);
    // Điểm trái & phải
    spr->fillCircle(cx - 6, by - 2, 2, C_EYE_YELLOW);
    spr->fillCircle(cx + 6, by - 2, 2, C_EYE_YELLOW);
    // 2 Điểm chéo
    spr->fillCircle(cx - 10, by - 6, 2, C_EYE_YELLOW);
    spr->fillCircle(cx + 10, by - 6, 2, C_EYE_YELLOW);
  }
}

// -------------------------------------------------------------
// Noctowl - Cú Mèo Tri Thức Sừng Hoàng Kim
// -------------------------------------------------------------
static void drawNoctowlMysticOwl(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.1f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.04f * breathSin;
  float sX = 1.0f - 0.02f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 2.8f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_BROWN_BODY  = 0x8A84; // #9A3412 Thân cú lông nâu gỗ
  const uint16_t C_BEIGE_CHEST = 0xCE55; // #D4D4D8 Ngực màu be sáng
  const uint16_t C_GOLD_HORN   = 0xFE60; // #FACC15 Gạc sừng lông mày hoàng kim
  const uint16_t C_DARK_TRI    = 0x3961; // #451A03 Họa tiết tam giác ngực
  const uint16_t C_RED_EYE     = 0xF800; // #EF4444 Mắt đỏ thông thái
  const uint16_t C_BEAK_CREAM  = 0xDEFB; // #E2E8F0 Mỏ & móng vuốt
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Hai chân móng vuốt chim bám chắc
  spr->fillRoundRect(cx - 12, by + 28, 6, 12, 2, C_BEAK_CREAM);
  spr->fillRoundRect(cx + 6,  by + 28, 6, 12, 2, C_BEAK_CREAM);

  // 3. Khối thân cú tròn trịa màu nâu
  spr->fillEllipse(cx, by + 12, (int)(18 * sX), (int)(18 * sY), C_BROWN_BODY);
  spr->fillEllipse(cx, by + 14, (int)(14 * sX), (int)(14 * sY), C_BEIGE_CHEST);

  // 4. Họa tiết tam giác đen trước ngực đặc trưng
  spr->fillTriangle(cx - 8, by + 8,  cx - 4, by + 14, cx,     by + 8,  C_DARK_TRI);
  spr->fillTriangle(cx,     by + 8,  cx + 4, by + 14, cx + 8, by + 8,  C_DARK_TRI);
  spr->fillTriangle(cx - 4, by + 16, cx,     by + 22, cx + 4, by + 16, C_DARK_TRI);

  // 5. Cánh xếp gọn hai bên sườn
  spr->fillRoundRect(cx - 20, by + 4, 6, 20, 3, C_BROWN_BODY);
  spr->fillRoundRect(cx + 14, by + 4, 6, 20, 3, C_BROWN_BODY);

  // 6. Khối đầu cú to tròn thông thái
  spr->fillCircle(cx, by - 8, (int)(16 * sX), C_BROWN_BODY);

  // 7. Gạc lông mày hoàng kim khổng lồ hình vương miện ba chĩa (Golden Horn Brow)
  spr->fillTriangle(cx - 18, by - 16, cx - 22, by - 38, cx - 12, by - 14, C_GOLD_HORN);
  spr->fillTriangle(cx - 14, by - 16, cx,     by - 26, cx - 6,  by - 14, C_GOLD_HORN);
  spr->fillTriangle(cx + 18, by - 16, cx + 22, by - 38, cx + 12, by - 14, C_GOLD_HORN);
  spr->fillTriangle(cx + 14, by - 16, cx,     by - 26, cx + 6,  by - 14, C_GOLD_HORN);

  // 8. Đôi mắt to tròn đỏ rực với hai vòng tròn đen thôi miên
  spr->fillCircle(cx - 8, by - 8, 6, 0x18C3);
  spr->fillCircle(cx + 8, by - 8, 6, 0x18C3);
  if (!blink) {
    spr->fillCircle(cx - 8, by - 8, 4, C_RED_EYE);
    spr->fillCircle(cx - 9, by - 10, 1, 0xFFFF);
    spr->fillCircle(cx + 8, by - 8, 4, C_RED_EYE);
    spr->fillCircle(cx + 7, by - 10, 1, 0xFFFF);
  } else {
    spr->drawLine(cx - 11, by - 8, cx - 5, by - 8, 0xFFFF);
    spr->drawLine(cx + 5,  by - 8, cx + 11, by - 8, 0xFFFF);
  }

  // 9. Mỏ chim nhỏ quặp xuống
  spr->fillTriangle(cx - 3, by - 6, cx, by - 1, cx + 3, by - 6, C_BEAK_CREAM);
}

// -------------------------------------------------------------
// Kecleon - Kỳ Dông Biến Sắc Đuôi Xoắn
// -------------------------------------------------------------
static void drawKecleonChameleon(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.3f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 2.8f);
  int by = cy + bounceY;

  // Đuôi xoắn ốc co giãn
  int tailWiggle = (int)(sinf(angle * 2.5f) * 2.0f);

  // Mắt chuyển động độc lập
  int eyeMoveX = (int)(sinf(angle * 3.5f) * 2.0f);
  int eyeMoveY = (int)(cosf(angle * 3.5f) * 2.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_GREEN_BODY = 0x4EC8; // #22C55E Thân tắc kè xanh lục tươi
  const uint16_t C_GREEN_DARK = 0x2488; // #15803D Bóng thân
  const uint16_t C_RED_ZIGZAG = 0xF800; // #EF4444 Sọc zigzag đỏ trước bụng
  const uint16_t C_YELLOW_LIP = 0xFE60; // #FACC15 Mào đầu & Mép môi vàng
  const uint16_t C_BLACK_EYE  = 0x18C3; // #1E293B Con ngươi đen
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Catchlight
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx - 2, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Đuôi cuộn xoắn ốc tròn xoe sau lưng (Spiral Tail)
  int tx = cx + 18 + tailWiggle;
  spr->fillCircle(tx,      by + 16, 10, C_GREEN_BODY);
  spr->fillCircle(tx + 2,  by + 16, 6,  C_GREEN_DARK);
  spr->fillCircle(tx + 2,  by + 16, 3,  C_GREEN_BODY);

  // 3. Thân tắc kè hoa tròn vo ngộ nghĩnh
  spr->fillEllipse(cx - 2, by + 14, (int)(16 * sX), (int)(16 * sY), C_GREEN_DARK);
  spr->fillEllipse(cx - 2, by + 12, (int)(14 * sX), (int)(14 * sY), C_GREEN_BODY);

  // 4. Sọc zigzag đỏ rực rỡ quanh bụng (Signature Red Zig-Zag)
  spr->drawLine(cx - 12, by + 12, cx - 8,  by + 16, C_RED_ZIGZAG);
  spr->drawLine(cx - 8,  by + 16, cx - 4,  by + 12, C_RED_ZIGZAG);
  spr->drawLine(cx - 4,  by + 12, cx,      by + 16, C_RED_ZIGZAG);
  spr->drawLine(cx,      by + 16, cx + 4,  by + 12, C_RED_ZIGZAG);
  spr->drawLine(cx + 4,  by + 12, cx + 8,  by + 16, C_RED_ZIGZAG);

  // 5. 4 Chân ngắn với bàn chân móng chẽ hai ngón
  spr->fillRoundRect(cx - 14, by + 24, 6, 12, 2, C_GREEN_BODY);
  spr->fillRoundRect(cx + 4,  by + 24, 6, 12, 2, C_GREEN_BODY);

  // 6. Khối đầu tắc kè hoa hình nón nghiêng
  spr->fillCircle(cx - 6, by - 8, (int)(16 * sX), C_GREEN_BODY);

  // 7. Mào răng cưa màu vàng trên đỉnh đầu
  spr->fillTriangle(cx - 14, by - 16, cx - 18, by - 32, cx - 6, by - 20, C_YELLOW_LIP);
  spr->fillTriangle(cx - 8,  by - 18, cx,     by - 34, cx + 4, by - 18, C_YELLOW_LIP);

  // 8. Chiếc mỏ dẹp vàng dài
  spr->fillRoundRect(cx - 22, by - 6, 16, 5, 2, C_YELLOW_LIP);

  // 9. Mắt hình tháp xoay chuyển động độc lập
  spr->fillCircle(cx - 4, by - 10, 7, C_YELLOW_LIP);
  spr->fillCircle(cx - 4, by - 10, 5, C_GREEN_BODY);
  if (!blink) {
    spr->fillCircle(cx - 4 + eyeMoveX, by - 10 + eyeMoveY, 2, C_BLACK_EYE);
    spr->drawPixel(cx - 5 + eyeMoveX,  by - 11 + eyeMoveY, C_WHITE);
  } else {
    spr->drawLine(cx - 8, by - 10, cx, by - 10, C_BLACK_EYE);
  }
}

// -------------------------------------------------------------
// Solgaleo - Thái Dương Thần Sư Mặt Trời
// -------------------------------------------------------------
static void drawSolgaleoSunLion(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.0f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.04f * breathSin;
  float sX = 1.0f - 0.02f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_WHITE_LION  = 0xFFFF; // #FFFFFF Thân sư tử trắng sứ
  const uint16_t C_GOLD_RAY    = 0xFE60; // #FACC15 Tia sáng thái dương vàng
  const uint16_t C_ORANGE_FIRE = 0xFD20; // #F97316 Hỏa diễm cam chóp bờm
  const uint16_t C_COSMOS_BLUE = 0x0155; // #0F172A Mặt nạ tinh vân vũ trụ
  const uint16_t C_CYAN_EYE    = 0x07FF; // #06B6D4 Mắt xanh tinh tú
  const uint16_t C_GREY_JOINT  = 0x4208; // #475569 Khớp xám đen
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 44, (int)(34 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Đuôi sư tử dài uốn lượn chóp bầu dục đen viền vàng
  spr->fillTriangle(cx + 14, by + 12, cx + 32, by - 6, cx + 22, by + 18, C_WHITE_LION);
  spr->fillCircle(cx + 32, by - 6, 4, C_GOLD_RAY);
  spr->fillCircle(cx + 32, by - 6, 2, C_GREY_JOINT);

  // 3. Thân sư tử trắng muốt cơ bắp
  spr->fillEllipse(cx - 2, by + 14, (int)(18 * sX), (int)(14 * sY), C_GREY_JOINT);
  spr->fillEllipse(cx - 2, by + 12, (int)(16 * sX), (int)(12 * sY), C_WHITE_LION);

  // 4. 4 Chân vững chắc với vòng cam quanh cổ chân
  spr->fillRoundRect(cx - 16, by + 18, 6, 18, 2, C_WHITE_LION);
  spr->fillRect(cx - 16, by + 30, 6, 3, C_ORANGE_FIRE);

  spr->fillRoundRect(cx - 8,  by + 20, 6, 16, 2, C_WHITE_LION);
  spr->fillRect(cx - 8,  by + 30, 6, 3, C_ORANGE_FIRE);

  spr->fillRoundRect(cx + 4,  by + 20, 6, 16, 2, C_WHITE_LION);
  spr->fillRect(cx + 4,  by + 30, 6, 3, C_ORANGE_FIRE);

  spr->fillRoundRect(cx + 12, by + 18, 6, 18, 2, C_WHITE_LION);
  spr->fillRect(cx + 12, by + 30, 6, 3, C_ORANGE_FIRE);

  // 5. Bờm Thái Dương Mặt Trời rực rỡ tỏa tia sáng 8 hướng (Solar Corona Mane)
  // Các tia sáng trắng viền vàng cam bao quanh đầu
  spr->fillTriangle(cx - 10, by - 12, cx - 34, by - 32, cx - 18, by - 24, C_WHITE_LION);
  spr->fillTriangle(cx - 10, by - 12, cx - 8,  by - 42, cx,      by - 26, C_WHITE_LION);
  spr->fillTriangle(cx,     by - 12, cx + 8,  by - 42, cx + 10, by - 26, C_WHITE_LION);
  spr->fillTriangle(cx + 10, by - 12, cx + 34, by - 32, cx + 18, by - 24, C_WHITE_LION);

  spr->fillTriangle(cx - 10, by - 6,  cx - 36, by - 4,  cx - 20, by + 4,  C_WHITE_LION);
  spr->fillTriangle(cx + 10, by - 6,  cx + 36, by - 4,  cx + 20, by + 4,  C_WHITE_LION);

  // Chóp cam lửa trên các cánh bờm
  spr->fillCircle(cx - 30, by - 28, 3, C_ORANGE_FIRE);
  spr->fillCircle(cx - 6,  by - 38, 3, C_ORANGE_FIRE);
  spr->fillCircle(cx + 6,  by - 38, 3, C_ORANGE_FIRE);
  spr->fillCircle(cx + 30, by - 28, 3, C_ORANGE_FIRE);

  // 6. Ngôi sao 4 cánh vàng hoàng kim trên trán
  spr->drawLine(cx - 14, by - 10, cx + 14, by - 10, C_GOLD_RAY);
  spr->drawLine(cx,     by - 24, cx,     by + 4,  C_GOLD_RAY);

  // 7. Mặt nạ tinh vân ngân hà xanh đen sâu thẳm
  spr->fillCircle(cx, by - 10, 8, C_COSMOS_BLUE);

  // 8. Đôi mắt xanh tinh tú rực sáng
  if (!blink) {
    spr->fillCircle(cx - 3, by - 10, 2, C_CYAN_EYE);
    spr->drawPixel(cx - 3,  by - 11, 0xFFFF);
    spr->fillCircle(cx + 3, by - 10, 2, C_CYAN_EYE);
    spr->drawPixel(cx + 3,  by - 11, 0xFFFF);
  } else {
    spr->drawLine(cx - 5, by - 10, cx - 1, by - 10, 0xFFFF);
    spr->drawLine(cx + 1, by - 10, cx + 5, by - 10, 0xFFFF);
  }
}

} // namespace Session10Mythics
