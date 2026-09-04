#pragma once
// ============================================================================
// SESSION 6 BELOVED COMPANIONS - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 ST7789 IPS LCD (172x320 60FPS DMA)
// Pop Mart & Kawaii Visual DNA: Volumetric 4-Tone Shading & Crystal Catchlights
// Characters: Psyduck, Piplup, Alolan Vulpix, Rowlet, Mimikyu (IDs 75 to 79)
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace Session6Mythics {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// -------------------------------------------------------------
// Psyduck - Vịt Vàng Đau Đầu
// -------------------------------------------------------------
static void drawPsyduckHeadacheDuck(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.1f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Cơn đau đầu rung rinh
  int headacheWiggle = (int)(sinf(angle * 8.0f) * 1.5f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_YELLOW     = 0xFFE0; // #FACC15 Vàng vịt chủ đạo
  const uint16_t C_YEL_DARK   = 0xCA00; // #CA8A04 Bóng vàng
  const uint16_t C_BEAK_CREAM = 0xFF97; // #FEF08A Mỏ vịt kem
  const uint16_t C_BEAK_SHAD  = 0xEE73; // #FDE047 Bóng mỏ
  const uint16_t C_BLACK      = 0x08E5; // #0F172A Tóc 3 cọng & con ngươi
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Lòng trắng mắt
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Hai chân màng bơi xòe ra dưới đáy
  spr->fillRoundRect(cx - 18, by + 28, 10, 8, 3, C_BEAK_SHAD);
  spr->fillRoundRect(cx + 8,  by + 28, 10, 8, 3, C_BEAK_SHAD);

  // 3. Thân quả lê béo tròn màu vàng
  spr->fillEllipse(cx, by + 14, (int)(22 * sX), (int)(20 * sY), C_YEL_DARK);
  spr->fillEllipse(cx, by + 12, (int)(20 * sX), (int)(18 * sY), C_YELLOW);

  // 4. Khối đầu to tròn ngơ ngác
  spr->fillEllipse(cx, by - 8, (int)(22 * sX), (int)(18 * sY), C_YEL_DARK);
  spr->fillEllipse(cx, by - 10, (int)(20 * sX), (int)(16 * sY), C_YELLOW);

  // 5. 3 cọng tóc đen đặc trưng trên đỉnh đầu
  spr->drawLine(cx,     by - 26, cx,     by - 38, C_BLACK);
  spr->drawLine(cx - 4, by - 25, cx - 8, by - 36, C_BLACK);
  spr->drawLine(cx + 4, by - 25, cx + 8, by - 36, C_BLACK);

  // 6. Chiếc mỏ vịt dẹp màu kem siêu to
  spr->fillEllipse(cx, by - 4, 16, 10, C_BEAK_SHAD);
  spr->fillEllipse(cx, by - 5, 14, 9,  C_BEAK_CREAM);
  // Hai lỗ mũi nhỏ
  spr->drawPixel(cx - 2, by - 6, C_YEL_DARK);
  spr->drawPixel(cx + 2, by - 6, C_YEL_DARK);

  // 7. Đôi mắt tròn xoe ngơ ngác mất tập trung
  if (!blink) {
    spr->fillCircle(cx - 10, by - 14, 5, C_WHITE);
    spr->drawCircle(cx - 10, by - 14, 5, C_YEL_DARK);
    spr->fillCircle(cx - 10, by - 14, 1, C_BLACK); // Đồng tử tí hon ngơ ngác

    spr->fillCircle(cx + 10, by - 14, 5, C_WHITE);
    spr->drawCircle(cx + 10, by - 14, 5, C_YEL_DARK);
    spr->fillCircle(cx + 10, by - 14, 1, C_BLACK);
  } else {
    spr->drawLine(cx - 14, by - 14, cx - 6, by - 14, C_BLACK);
    spr->drawLine(cx + 6,  by - 14, cx + 14, by - 14, C_BLACK);
  }

  // 8. Hai cánh tay ôm đầu đau đầu kinh điển (Headache Pose)
  spr->fillRoundRect(cx - 24 + headacheWiggle, by - 14, 8, 16, 4, C_YELLOW);
  spr->fillRoundRect(cx + 16 - headacheWiggle, by - 14, 8, 16, 4, C_YELLOW);
}

// -------------------------------------------------------------
// Piplup - Chim Cánh Cụt Băng Tuyết
// -------------------------------------------------------------
static void drawPiplupIcePenguin(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_BLUE_HEAD   = 0x2357; // #1D4ED8 Xanh hoàng gia đầu
  const uint16_t C_BLUE_CAPE   = 0x247A; // #2563EB Áo choàng xanh
  const uint16_t C_CYAN_BODY   = 0x7EBF; // #7DD3FC Xanh lam nhạt thân
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Mặt nạ & khuy ngực
  const uint16_t C_YELLOW_BEAK = 0xFE62; // #FACC15 Mỏ & chân vàng
  const uint16_t C_EYE_NAVY    = 0x01D3; // #0C4A6E Mắt xanh sẫm
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Hai chân chim cánh cụt vàng
  spr->fillRoundRect(cx - 16, by + 28, 9, 8, 3, C_YELLOW_BEAK);
  spr->fillRoundRect(cx + 7,  by + 28, 9, 8, 3, C_YELLOW_BEAK);

  // 3. Thân chim cánh cụt màu cyan nhạt
  spr->fillEllipse(cx, by + 14, (int)(18 * sX), (int)(18 * sY), C_CYAN_BODY);
  // Hai chiếc cúc áo trắng tròn trước ngực
  spr->fillCircle(cx - 5, by + 16, 3, C_WHITE);
  spr->fillCircle(cx + 5, by + 16, 3, C_WHITE);

  // 4. Áo choàng xanh sẫm quanh cổ (Capelet)
  spr->fillEllipse(cx, by + 2, (int)(22 * sX), 8, C_BLUE_CAPE);

  // 5. Khối đầu tròn màu xanh hoàng gia
  spr->fillCircle(cx, by - 10, (int)(18 * sX), C_BLUE_HEAD);

  // 6. Vùng mặt nạ trắng bao quanh mắt
  spr->fillEllipse(cx, by - 6, (int)(15 * sX), 9, C_WHITE);
  // Vương miện lam trên trán
  spr->fillTriangle(cx - 6, by - 15, cx, by - 8, cx + 6, by - 15, C_CYAN_BODY);

  // 7. Mỏ vàng tròn trịa
  spr->fillCircle(cx, by - 4, 4, C_YELLOW_BEAK);

  // 8. Đôi mắt to tròn xanh thẳm
  if (!blink) {
    spr->fillEllipse(cx - 7, by - 9, 3, 6, C_EYE_NAVY);
    spr->fillCircle(cx - 8, by - 11, 1, C_WHITE);
    spr->fillEllipse(cx + 7, by - 9, 3, 6, C_EYE_NAVY);
    spr->fillCircle(cx + 6, by - 11, 1, C_WHITE);
  } else {
    spr->drawLine(cx - 9, by - 8, cx - 5, by - 8, C_EYE_NAVY);
    spr->drawLine(cx + 5, by - 8, cx + 9, by - 8, C_EYE_NAVY);
  }

  // 9. Hai cánh bơi nhỏ xuôi theo thân
  spr->fillRoundRect(cx - 20, by + 6, 6, 16, 3, C_BLUE_CAPE);
  spr->fillRoundRect(cx + 14, by + 6, 6, 16, 3, C_BLUE_CAPE);
}

// -------------------------------------------------------------
// Vulpix Alola - Cáo Tuyết Băng Giá
// -------------------------------------------------------------
static void drawVulpixAlolanIceFox(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Đuôi mây tuyết đung đưa trễ pha
  float tailLag = breathPhase - 0.45f;
  int tailSwayX = (int)(sinf(tailLag) * 6.0f);
  int tailSwayY = (int)(cosf(tailLag) * 3.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_SNOW_WHITE = 0xFFFF; // #FFFFFF Trắng tuyết
  const uint16_t C_ICE_BLUE   = 0xBA3F; // #BAE6FD Lam băng nhạt
  const uint16_t C_ICE_SHAD   = 0x939B; // #7DD3FC Bóng tuyết
  const uint16_t C_DEEP_BLUE  = 0x0396; // #0284C7 Tai & mắt xanh biển
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Chiếc đuôi mây tuyết khổng lồ uốn lượn sau lưng
  int tx = cx + 18 + tailSwayX;
  int ty = by - 2 + tailSwayY;
  spr->fillCircle(tx + 4, ty - 8,  9, C_ICE_BLUE);
  spr->fillCircle(tx + 8, ty,      10, C_SNOW_WHITE);
  spr->fillCircle(tx + 2, ty + 10, 8, C_SNOW_WHITE);

  // 3. Thân tuyết trắng 4 chân thanh thoát
  spr->fillEllipse(cx, by + 16, (int)(16 * sX), (int)(14 * sY), C_ICE_BLUE);
  spr->fillEllipse(cx, by + 14, (int)(14 * sX), (int)(12 * sY), C_SNOW_WHITE);
  // 4 Chân với tất lam băng
  spr->fillRoundRect(cx - 14, by + 24, 6, 12, 3, C_ICE_BLUE);
  spr->fillRoundRect(cx - 6,  by + 24, 6, 12, 3, C_ICE_BLUE);
  spr->fillRoundRect(cx + 2,  by + 24, 6, 12, 3, C_ICE_BLUE);
  spr->fillRoundRect(cx + 10, by + 24, 6, 12, 3, C_ICE_BLUE);

  // 4. Khối đầu cáo tuyết
  spr->fillEllipse(cx, by - 8, (int)(20 * sX), (int)(16 * sY), C_ICE_BLUE);
  spr->fillEllipse(cx, by - 10, (int)(18 * sX), (int)(14 * sY), C_SNOW_WHITE);

  // 5. Đôi tai cáo vươn cao với lòng tai xanh thẳm
  spr->fillTriangle(cx - 14, by - 18, cx - 24, by - 38, cx - 4, by - 22, C_SNOW_WHITE);
  spr->fillTriangle(cx - 15, by - 20, cx - 22, by - 34, cx - 7, by - 24, C_DEEP_BLUE);
  spr->fillTriangle(cx + 4,  by - 22, cx + 24, by - 38, cx + 14, by - 18, C_SNOW_WHITE);
  spr->fillTriangle(cx + 7,  by - 24, cx + 22, by - 34, cx + 15, by - 20, C_DEEP_BLUE);

  // 6. Chỏm xoáy tóc băng tuyết trước trán (Cloud Curl)
  spr->fillCircle(cx, by - 20, 8, C_ICE_BLUE);
  spr->fillCircle(cx, by - 21, 7, C_SNOW_WHITE);

  // 7. Đôi mắt ngọc bích lam băng to tròn
  if (!blink) {
    spr->fillEllipse(cx - 8, by - 10, 4, 7, C_DEEP_BLUE);
    spr->fillCircle(cx - 9, by - 13, 2, C_SNOW_WHITE);
    spr->fillEllipse(cx + 8, by - 10, 4, 7, C_DEEP_BLUE);
    spr->fillCircle(cx + 7, by - 13, 2, C_SNOW_WHITE);
  } else {
    spr->drawEllipse(cx - 8, by - 9, 4, 2, C_DEEP_BLUE);
    spr->drawEllipse(cx + 8, by - 9, 4, 2, C_DEEP_BLUE);
  }

  // 8. Mũi xanh nhỏ & Miệng cười
  spr->drawPixel(cx, by - 5, C_DEEP_BLUE);
  spr->drawLine(cx - 2, by - 2, cx + 2, by - 2, C_DEEP_BLUE);
}

// -------------------------------------------------------------
// Rowlet - Cú Mèo Tròn Vo Nơ Lá
// -------------------------------------------------------------
static void drawRowletRoundOwl(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 2.8f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_BEIGE_BODY  = 0xE5F3; // #E5D0BA Lông nâu be tròn xoe
  const uint16_t C_BEIGE_DARK  = 0xC48D; // #C2A588 Bóng lông
  const uint16_t C_WHITE_FACE  = 0xFFFF; // #FFFFFF Kính mắt đôi trắng
  const uint16_t C_GREEN_BOW   = 0x1DB2; // #10B981 Nơ lá xanh ngọc
  const uint16_t C_ORANGE_BEAK = 0xF9A6; // #F97316 Mỏ dưới & chân cam
  const uint16_t C_BLACK       = 0x10A2; // #0F172A Mắt đen
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Hai chân nhỏ màu cam
  spr->fillRoundRect(cx - 14, by + 28, 8, 8, 3, C_ORANGE_BEAK);
  spr->fillRoundRect(cx + 6,  by + 28, 8, 8, 3, C_ORANGE_BEAK);

  // 3. Khối thân hình cầu cú mèo tròn vo hoàn hảo
  spr->fillCircle(cx, by + 4, (int)(24 * sX), C_BEIGE_DARK);
  spr->fillCircle(cx, by + 2, (int)(22 * sX), C_BEIGE_BODY);

  // 4. Kính mắt đôi trắng khổng lồ (Interconnected Eye Disks)
  spr->fillCircle(cx - 10, by - 6, 11, C_WHITE_FACE);
  spr->fillCircle(cx + 10, by - 6, 11, C_WHITE_FACE);

  // 5. Chiếc mỏ hai màu: trên trắng, dưới cam
  spr->fillCircle(cx, by - 8, 4, C_WHITE_FACE);
  spr->fillTriangle(cx - 3, by - 6, cx, by - 1, cx + 3, by - 6, C_ORANGE_BEAK);

  // 6. Đôi mắt to tròn đen sâu
  if (!blink) {
    spr->fillEllipse(cx - 10, by - 6, 4, 7, C_BLACK);
    spr->fillCircle(cx - 11, by - 9, 2, C_WHITE_FACE);
    spr->fillEllipse(cx + 10, by - 6, 4, 7, C_BLACK);
    spr->fillCircle(cx + 9,  by - 9, 2, C_WHITE_FACE);
  } else {
    spr->drawEllipse(cx - 10, by - 6, 4, 2, C_BLACK);
    spr->drawEllipse(cx + 10, by - 6, 4, 2, C_BLACK);
  }

  // 7. Nơ lá kép xanh ngọc trước ngực (Leaf Bowtie)
  spr->fillEllipse(cx - 6, by + 12, 6, 4, C_GREEN_BOW);
  spr->fillEllipse(cx + 6, by + 12, 6, 4, C_GREEN_BOW);
  spr->fillCircle(cx,      by + 12, 2, C_GREEN_BOW);
}

// -------------------------------------------------------------
// Mimikyu - Búp Bê Vải Rách Đôi Mắt Sâu
// -------------------------------------------------------------
static void drawMimikyuRagdollFairy(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.3f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Đuôi gỗ mục lắc lư
  float tailLag = breathPhase - 0.45f;
  int tailSwayX = (int)(sinf(tailLag) * 4.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_CLOTH      = 0xCE55; // #D4D4D8 Vải bao bố xám be
  const uint16_t C_CLOTH_DARK = 0x9CB2; // #A1A1AA Bóng vải
  const uint16_t C_BLACK_INK  = 0x08E5; // #0F172A Mực vẽ nguệch ngoạc
  const uint16_t C_ORANGE_CH  = 0xD380; // #D97706 Má cam vẽ sáp
  const uint16_t C_WOOD_BRN   = 0x6244; // #57534E Đuôi gỗ mục
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn & chân đen

  // 1. Bóng sàn tiếp xúc & tua vải rách
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Đuôi gỗ mục sét đánh sau lưng
  int tx = cx + 18 + tailSwayX;
  spr->fillRoundRect(tx, by + 12, 8, 18, 2, C_WOOD_BRN);
  spr->fillTriangle(tx - 2, by + 20, tx + 6, by + 10, tx + 4, by + 28, C_WOOD_BRN);

  // 3. Váy vải rách trùm kín thân
  spr->fillEllipse(cx, by + 18, (int)(22 * sX), (int)(18 * sY), C_CLOTH_DARK);
  spr->fillEllipse(cx, by + 16, (int)(20 * sX), (int)(16 * sY), C_CLOTH);
  // Gấu váy rách răng cưa
  spr->fillTriangle(cx - 20, by + 28, cx - 14, by + 34, cx - 8, by + 28, C_CLOTH);
  spr->fillTriangle(cx - 6,  by + 28, cx,      by + 34, cx + 6, by + 28, C_CLOTH);
  spr->fillTriangle(cx + 8,  by + 28, cx + 14, by + 34, cx + 20, by + 28, C_CLOTH);

  // 4. Hai mắt thật màu đen hé nhìn từ khe bụng
  spr->fillCircle(cx - 5, by + 18, 2, C_BLACK_INK);
  spr->fillCircle(cx + 5, by + 18, 2, C_BLACK_INK);

  // 5. Khối đầu nghiêng nghẹo ngây thơ
  spr->fillEllipse(cx - 2, by - 6, (int)(20 * sX), (int)(18 * sY), C_CLOTH_DARK);
  spr->fillEllipse(cx - 2, by - 8, (int)(18 * sX), (int)(16 * sY), C_CLOTH);

  // 6. Đôi tai Pikachu giả nghiêng một bên (Tai phải gãy gập)
  // Tai trái dựng
  spr->fillTriangle(cx - 14, by - 16, cx - 20, by - 40, cx - 6, by - 20, C_CLOTH);
  spr->fillTriangle(cx - 17, by - 30, cx - 20, by - 40, cx - 10, by - 32, C_BLACK_INK);
  // Tai phải gãy gập rủ xuống
  spr->fillRoundRect(cx + 10, by - 18, 18, 7, 3, C_CLOTH);
  spr->fillRoundRect(cx + 20, by - 16, 8,  7, 2, C_BLACK_INK);

  // 7. Khuôn mặt vẽ bằng nét sáp nguệch ngoạc
  // Mắt vẽ tròn xoắn ốc
  spr->drawCircle(cx - 10, by - 10, 4, C_BLACK_INK);
  spr->drawCircle(cx + 6,  by - 10, 4, C_BLACK_INK);
  // Má vẽ sáp màu cam
  spr->fillCircle(cx - 15, by - 4, 4, C_ORANGE_CH);
  spr->fillCircle(cx + 11, by - 4, 4, C_ORANGE_CH);
  // Miệng răng cưa zigzag vẽ mực đen
  spr->drawLine(cx - 10, by - 1, cx - 6, by - 4, C_BLACK_INK);
  spr->drawLine(cx - 6,  by - 4, cx - 2, by - 1, C_BLACK_INK);
  spr->drawLine(cx - 2,  by - 1, cx + 2, by - 4, C_BLACK_INK);
  spr->drawLine(cx + 2,  by - 4, cx + 6, by - 1, C_BLACK_INK);
}

} // namespace Session6Mythics
