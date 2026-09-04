#pragma once
// ============================================================================
// SESSION 7 MYTHIC CELESTIAL BEASTS - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 ST7789 IPS LCD (172x320 60FPS DMA)
// Pop Mart & Kawaii Visual DNA: Volumetric 4-Tone Shading & Crystal Catchlights
// Characters: Arceus, Ninetales, Dratini, Moltres, Torterra (IDs 80 to 84)
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace Session7Mythics {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// -------------------------------------------------------------
// Arceus - Đấng Sáng Thế Vũ Trụ
// -------------------------------------------------------------
static void drawArceusCreatorGod(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.0f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.04f * breathSin;
  float sX = 1.0f - 0.02f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.5f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_GOLD_RIM   = 0xFE60; // #FACC15 Vàng hoàng kim Thánh Luân
  const uint16_t C_GOLD_DARK  = 0xCA00; // #CA8A04 Bóng vàng
  const uint16_t C_WHITE_BODY = 0xFFFF; // #FFFFFF Trắng sứ thiên thần
  const uint16_t C_WHITE_SHAD = 0xDEFB; // #E2E8F0 Bóng trắng sứ
  const uint16_t C_CHARCOAL   = 0x2965; // #334155 Xám than chì cổ & bụng
  const uint16_t C_EMERALD    = 0x05E5; // #10B981 Ngọc lục bảo Thánh Luân
  const uint16_t C_EYE_GREEN  = 0x07E0; // #22C55E Mắt ngọc lục bảo
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc co giãn
  spr->fillEllipse(cx, cy + 44, (int)(28 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Thánh Luân Hoàng Kim (Golden Wheel of Creation) - Vòng tròn vàng bao quanh hông
  spr->drawCircle(cx, by + 10, 19, C_GOLD_DARK);
  spr->drawCircle(cx, by + 10, 18, C_GOLD_RIM);
  spr->drawCircle(cx, by + 10, 17, C_GOLD_RIM);
  // 4 Nan hoa vàng chữ X vươn ra 4 hướng
  spr->drawLine(cx - 14, by - 4,  cx - 24, by - 14, C_GOLD_RIM);
  spr->drawLine(cx + 14, by - 4,  cx + 24, by - 14, C_GOLD_RIM);
  spr->drawLine(cx - 14, by + 24, cx - 22, by + 32, C_GOLD_RIM);
  spr->drawLine(cx + 14, by + 24, cx + 22, by + 32, C_GOLD_RIM);
  // 4 Viên ngọc lục bảo phát quang trên nan hoa
  spr->fillCircle(cx - 16, by - 6,  3, C_EMERALD);
  spr->fillCircle(cx + 16, by - 6,  3, C_EMERALD);
  spr->fillCircle(cx - 16, by + 24, 3, C_EMERALD);
  spr->fillCircle(cx + 16, by + 24, 3, C_EMERALD);

  // 3. Đuôi dài trắng uốn lượn sau lưng
  spr->fillTriangle(cx + 12, by + 14, cx + 32, by + 4, cx + 18, by + 20, C_WHITE_SHAD);
  spr->fillTriangle(cx + 14, by + 13, cx + 30, by + 5, cx + 18, by + 18, C_WHITE_BODY);

  // 4. Thân ngựa thần trắng muốt
  spr->fillEllipse(cx, by + 12, (int)(18 * sX), (int)(14 * sY), C_WHITE_SHAD);
  spr->fillEllipse(cx, by + 10, (int)(16 * sX), (int)(12 * sY), C_WHITE_BODY);
  // Mảng giáp ngực xám than chì
  spr->fillRoundRect(cx - 7, by + 4, 14, 12, 3, C_CHARCOAL);

  // 5. 4 Chân thon dài quý phái với móng vàng nhọn
  spr->fillRoundRect(cx - 14, by + 18, 5, 20, 2, C_WHITE_SHAD);
  spr->fillRoundRect(cx - 15, by + 34, 7, 5, 2,  C_GOLD_RIM);
  spr->fillRoundRect(cx - 5,  by + 20, 5, 18, 2, C_WHITE_SHAD);
  spr->fillRoundRect(cx - 6,  by + 34, 7, 5, 2,  C_GOLD_RIM);
  spr->fillRoundRect(cx + 3,  by + 20, 5, 18, 2, C_WHITE_SHAD);
  spr->fillRoundRect(cx + 2,  by + 34, 7, 5, 2,  C_GOLD_RIM);
  spr->fillRoundRect(cx + 11, by + 18, 5, 20, 2, C_WHITE_SHAD);
  spr->fillRoundRect(cx + 10, by + 34, 7, 5, 2,  C_GOLD_RIM);

  // 6. Cổ cao vươn kiêu hãnh
  spr->fillTriangle(cx - 8, by + 8, cx + 6, by + 8, cx, by - 14, C_WHITE_SHAD);
  spr->fillTriangle(cx - 6, by + 7, cx + 4, by + 7, cx, by - 13, C_WHITE_BODY);
  // Sọc xám mặt trước cổ
  spr->drawLine(cx - 1, by + 6, cx - 1, by - 10, C_CHARCOAL);

  // 7. Khối đầu thần thoại với bờm nhọn vuốt ngược ra sau
  // Bờm xám vuốt cong lên cao
  spr->fillTriangle(cx - 2, by - 14, cx + 16, by - 38, cx + 4, by - 14, C_CHARCOAL);
  // Bờm trắng chính bao bọc ngoài
  spr->fillTriangle(cx - 6, by - 16, cx + 18, by - 36, cx, by - 24, C_WHITE_BODY);
  // Khuôn mặt trắng
  spr->fillEllipse(cx - 6, by - 18, 9, 8, C_WHITE_BODY);
  // Chỏm vàng trước trán
  spr->fillTriangle(cx - 12, by - 18, cx - 8, by - 24, cx - 7, by - 16, C_GOLD_RIM);

  // 8. Đôi mắt ngọc lục bảo uy nghiêm
  if (!blink) {
    spr->fillEllipse(cx - 6, by - 18, 2, 4, C_CHARCOAL);
    spr->fillCircle(cx - 6, by - 18, 1, C_EYE_GREEN);
    spr->drawPixel(cx - 7, by - 19, C_WHITE_BODY); // Điểm bắt sáng
  } else {
    spr->drawLine(cx - 8, by - 18, cx - 4, by - 18, C_CHARCOAL);
  }
}

// -------------------------------------------------------------
// Ninetales - Cửu Vĩ Kim Hồ Hoàng Gia
// -------------------------------------------------------------
static void drawNinetalesMoonFox(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 2.8f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_CREAM      = 0xFFF5; // #FEF9C3 Lông vàng kem thượng lưu
  const uint16_t C_GOLD_AMBER = 0xFEA0; // #FDE047 Vàng mật ong
  const uint16_t C_ORANGE_TIP = 0xFD20; // #F97316 Cam rực lửa đuôi
  const uint16_t C_RUBY_EYE   = 0xF800; // #EF4444 Mắt ngọc ruby kiêu hãnh
  const uint16_t C_DARK_INK   = 0x18C3; // #1E293B Viền mắt & mũi
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Lông ngực & catchlight
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(32 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Chùm 9 chiếc đuôi uốn lượn hình quạt bồng bềnh (Cascade 9 Tails)
  const int tailAngles[9] = {-48, -36, -24, -12, 0, 12, 24, 36, 48};
  for (int i = 0; i < 9; ++i) {
    float tailWave = sinf(breathPhase - 0.35f * i) * 3.5f;
    int tx = cx - 4 + (int)(tailAngles[i] * 0.7f + tailWave);
    int ty = by + 2 - (int)(cosf(tailAngles[i] * 0.035f) * 16.0f);
    // Thân đuôi vàng kem
    spr->fillCircle(tx, ty, 8, C_GOLD_AMBER);
    spr->fillCircle(tx, ty - 2, 7, C_CREAM);
    // Chóp đuôi vuốt nhọn màu cam lửa
    spr->fillTriangle(tx - 4, ty - 6, tx, ty - 16, tx + 4, ty - 6, C_ORANGE_TIP);
  }

  // 3. Thân cáo thanh tú ngồi kiêu sa
  spr->fillEllipse(cx - 2, by + 16, (int)(16 * sX), (int)(16 * sY), C_GOLD_AMBER);
  spr->fillEllipse(cx - 2, by + 14, (int)(14 * sX), (int)(14 * sY), C_CREAM);
  // Bờm lông ngực trắng muốt mềm mại
  spr->fillCircle(cx - 6, by + 12, 6, C_WHITE);
  spr->fillCircle(cx,     by + 14, 5, C_WHITE);

  // 4. Bốn chân thon gọn thanh lịch
  spr->fillRoundRect(cx - 12, by + 22, 5, 18, 2, C_CREAM);
  spr->fillRoundRect(cx - 4,  by + 22, 5, 18, 2, C_CREAM);
  spr->fillRoundRect(cx + 4,  by + 24, 6, 16, 2, C_CREAM);

  // 5. Khối đầu cáo thanh tú
  spr->fillEllipse(cx - 6, by - 8, (int)(14 * sX), (int)(12 * sY), C_CREAM);
  // Mõm cáo thon nhọn
  spr->fillTriangle(cx - 18, by - 6, cx - 8, by - 12, cx - 8, by - 2, C_CREAM);
  spr->drawPixel(cx - 18, by - 6, C_DARK_INK); // Mũi đen

  // 6. Đôi tai cáo vươn cao quý tộc
  spr->fillTriangle(cx - 8, by - 14, cx - 14, by - 36, cx - 2, by - 18, C_CREAM);
  spr->fillTriangle(cx - 7, by - 16, cx - 12, by - 32, cx - 3, by - 20, C_GOLD_AMBER);
  spr->fillTriangle(cx,     by - 14, cx + 4,  by - 34, cx + 8, by - 16, C_CREAM);
  spr->fillTriangle(cx + 1, by - 16, cx + 4,  by - 30, cx + 7, by - 18, C_GOLD_AMBER);

  // 7. Bờm tóc quý tộc uốn lượn sau gáy
  spr->fillTriangle(cx + 2, by - 12, cx + 22, by - 28, cx + 10, by - 6, C_CREAM);
  spr->fillTriangle(cx + 4, by - 10, cx + 24, by - 24, cx + 12, by - 4, C_GOLD_AMBER);

  // 8. Đôi mắt phượng ruby kiêu sa
  if (!blink) {
    spr->fillEllipse(cx - 10, by - 8, 2, 4, C_RUBY_EYE);
    spr->drawPixel(cx - 11, by - 9, C_WHITE);
  } else {
    spr->drawLine(cx - 12, by - 8, cx - 8, by - 8, C_DARK_INK);
  }
}

// -------------------------------------------------------------
// Dratini - Tiểu Thanh Long Biển Sâu
// -------------------------------------------------------------
static void drawDratiniAzureDragon(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.3f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Cánh tai vỗ nhịp đón gió
  int finFlutter = (int)(sinf(angle * 4.0f) * 3.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_BLUE_BODY  = 0x7EBF; // #7DD3FC Xanh lam ngọc pastel
  const uint16_t C_BLUE_DARK  = 0x3CF3; // #38BDF8 Bóng xanh ngọc
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Bụng, mỏ, ngọc trán & cánh tai
  const uint16_t C_PURPLE_EYE = 0x61B6; // #7C3AED Mắt tím thạch anh sâu thẳm
  const uint16_t C_BLUSH      = 0xFC18; // #F472B6 Má hồng đào
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx - 4, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Thân rồng uốn lượn chữ S mềm mại (Serpentine S-body)
  // Vòng đuôi đáy
  spr->fillEllipse(cx - 16, by + 28, 14, 8, C_BLUE_DARK);
  spr->fillEllipse(cx - 16, by + 26, 12, 7, C_BLUE_BODY);
  // Đuôi vuốt nhọn vểnh lên
  spr->fillTriangle(cx - 28, by + 24, cx - 38, by + 18, cx - 22, by + 28, C_BLUE_BODY);

  // Khúc thân giữa dựng đứng
  spr->fillRoundRect(cx + 2, by + 8, 14, 22, 6, C_BLUE_DARK);
  spr->fillRoundRect(cx + 4, by + 6, 12, 22, 5, C_BLUE_BODY);
  // Bụng trắng chạy dọc thân
  spr->fillRoundRect(cx + 6, by + 8, 8, 20, 4, C_WHITE);

  // 3. Khối đầu rồng tròn vo Chibi đáng yêu
  spr->fillCircle(cx + 10, by - 8, (int)(18 * sX), C_BLUE_DARK);
  spr->fillCircle(cx + 10, by - 10, (int)(16 * sX), C_BLUE_BODY);

  // 4. Mũi trắng tròn trịa phúng phính (White Snout)
  spr->fillCircle(cx + 2, by - 6, 8, C_WHITE);

  // 5. Viên ngọc trai trắng phát quang trước trán
  spr->fillCircle(cx + 10, by - 22, 4, C_WHITE);

  // 6. Đôi cánh tai thiên thần trắng hai bên đầu (Wing Fins)
  // Cánh tai trái
  spr->fillTriangle(cx - 2, by - 16, cx - 18 + finFlutter, by - 28, cx + 2, by - 22, C_WHITE);
  // Cánh tai phải
  spr->fillTriangle(cx + 20, by - 20, cx + 32 - finFlutter, by - 34, cx + 24, by - 14, C_WHITE);

  // 7. Má hồng đào dịu dàng
  spr->fillCircle(cx + 4, by - 2, 3, C_BLUSH);

  // 8. Đôi mắt to tròn tím thạch anh long lanh
  if (!blink) {
    spr->fillEllipse(cx + 10, by - 10, 4, 7, C_PURPLE_EYE);
    spr->fillCircle(cx + 9,  by - 13, 2, C_WHITE); // Catchlight chính
    spr->drawPixel(cx + 11, by - 7,  C_WHITE); // Catchlight phụ
  } else {
    spr->drawEllipse(cx + 10, by - 10, 4, 2, C_PURPLE_EYE);
  }
}

// -------------------------------------------------------------
// Moltres - Chu Tước Hỏa Diễm Điểu
// -------------------------------------------------------------
static void drawMoltresFlamePhoenix(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.5f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.5f);
  int by = cy + bounceY;

  // Cánh lửa vỗ nhịp bùng cháy
  float wingFlap = sinf(angle * 3.2f) * 6.0f;
  int flameWiggle = (int)(sinf(angle * 7.0f) * 2.5f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_GOLD_BODY   = 0xFEA0; // #FDE047 Thân vàng hoàng kim
  const uint16_t C_ORANGE_FIRE = 0xFD20; // #F97316 Lửa cam rực rỡ
  const uint16_t C_RED_FIRE    = 0xF800; // #EF4444 Lửa đỏ hồng ngọc
  const uint16_t C_YELLOW_FIRE = 0xFFE0; // #FEF08A Lửa vàng chói sáng
  const uint16_t C_BEAK_CREAM  = 0xE5F3; // #E2E8F0 Mỏ nhọn
  const uint16_t C_DARK_EYE    = 0x18C3; // #1E293B Mắt sắc sảo
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 44, (int)(28 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Đuôi lửa bập bùng uốn lượn sau lưng
  spr->fillTriangle(cx - 8, by + 18, cx - 28 + flameWiggle, by + 32, cx, by + 24, C_RED_FIRE);
  spr->fillTriangle(cx - 6, by + 18, cx - 24 + flameWiggle, by + 30, cx, by + 22, C_ORANGE_FIRE);

  // 3. Thân chim hoàng kim thanh thoát
  spr->fillEllipse(cx, by + 12, (int)(14 * sX), (int)(18 * sY), C_GOLD_BODY);

  // 4. Đôi cánh lửa khổng lồ rực cháy (Blazing Fire Wings)
  // Cánh trái
  int wly = by + (int)wingFlap;
  spr->fillTriangle(cx - 10, by + 6, cx - 40, wly - 16, cx - 18, by + 18, C_RED_FIRE);
  spr->fillTriangle(cx - 12, by + 8, cx - 36, wly - 14, cx - 20, by + 16, C_ORANGE_FIRE);
  spr->fillTriangle(cx - 14, by + 10, cx - 30, wly - 10, cx - 20, by + 14, C_YELLOW_FIRE);
  // Cánh phải
  int wry = by - (int)wingFlap;
  spr->fillTriangle(cx + 10, by + 6, cx + 40, wry - 16, cx + 18, by + 18, C_RED_FIRE);
  spr->fillTriangle(cx + 12, by + 8, cx + 36, wry - 14, cx + 20, by + 16, C_ORANGE_FIRE);
  spr->fillTriangle(cx + 14, by + 10, cx + 30, wry - 10, cx + 20, by + 14, C_YELLOW_FIRE);

  // 5. Cổ và Đầu chim hoàng kim
  spr->fillRoundRect(cx - 4, by - 6, 8, 14, 3, C_GOLD_BODY);
  spr->fillCircle(cx, by - 12, 10, C_GOLD_BODY);

  // 6. Mào lửa bốc cháy trên đỉnh đầu (Flaming Crest)
  spr->fillTriangle(cx - 4, by - 18, cx + flameWiggle, by - 36, cx + 8, by - 16, C_RED_FIRE);
  spr->fillTriangle(cx - 2, by - 18, cx + flameWiggle, by - 32, cx + 6, by - 16, C_ORANGE_FIRE);
  spr->fillTriangle(cx,     by - 18, cx + flameWiggle, by - 26, cx + 4, by - 16, C_YELLOW_FIRE);

  // 7. Mỏ nhọn dài kiêu hãnh
  spr->fillTriangle(cx - 4, by - 12, cx - 18, by - 8, cx - 4, by - 6, C_BEAK_CREAM);

  // 8. Đôi mắt phượng hoàng lửa
  if (!blink) {
    spr->fillCircle(cx + 2, by - 12, 3, C_DARK_EYE);
    spr->drawPixel(cx + 1, by - 13, C_YELLOW_FIRE);
  } else {
    spr->drawLine(cx, by - 12, cx + 4, by - 12, C_DARK_EYE);
  }

  // 9. Hai chân móng vuốt chim gọn gàng
  spr->fillRoundRect(cx - 6, by + 28, 4, 10, 2, C_BEAK_CREAM);
  spr->fillRoundRect(cx + 2, by + 28, 4, 10, 2, C_BEAK_CREAM);
}

// -------------------------------------------------------------
// Torterra - Huyền Quy Đại Lục Bonsai
// -------------------------------------------------------------
static void drawTorterraContinentTortoise(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 1.8f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.03f * breathSin;
  float sX = 1.0f - 0.015f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 2.0f);
  int by = cy + bounceY;

  // Cây bonsai đung đưa nhẹ theo gió
  int treeSway = (int)(sinf(angle * 2.0f) * 2.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_SHELL_GREEN = 0x34C8; // #15803D Mai rùa xanh rêu đại ngàn
  const uint16_t C_SHELL_LIGHT = 0x5D8B; // #22C55E Vùng cỏ xanh trên mai
  const uint16_t C_SILVER_RIM  = 0xBDD7; // #CBD5E1 Viền mai kim loại bạc
  const uint16_t C_BROWN_WOOD  = 0x7263; // #78350F Thân cây bonsai cổ thụ
  const uint16_t C_LEAF_GREEN  = 0x1C84; // #166534 Tán lá cây bonsai
  const uint16_t C_MOUNTAIN    = 0x94B2; // #94A3B8 Đỉnh núi đá xám
  const uint16_t C_EARTH_BROWN = 0x8A84; // #9A3412 4 Chân vững chắc
  const uint16_t C_HEAD_GREEN  = 0x4D09; // #16A34A Đầu rùa bọc giáp
  const uint16_t C_RED_EYE     = 0xF800; // #EF4444 Mắt đỏ kiên định
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Móng vuốt & gai sừng má
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc đại lục khổng lồ
  spr->fillEllipse(cx, cy + 42, (int)(36 * (1.0f - 0.15f * breathSin)), 8, C_SHADOW);

  // 2. 3 Đỉnh núi đá nhọn mọc trên mai rùa bên trái
  spr->fillTriangle(cx - 24, by - 6, cx - 18, by - 24, cx - 10, by - 6, C_MOUNTAIN);
  spr->fillTriangle(cx - 16, by - 4, cx - 10, by - 18, cx - 4,  by - 4, C_SILVER_RIM);

  // 3. Cây Bonsai cổ thụ sừng sững bên phải mai rùa
  int bx = cx + 16 + treeSway;
  // Thân gỗ nâu
  spr->fillRoundRect(bx - 3, by - 14, 6, 16, 2, C_BROWN_WOOD);
  spr->fillTriangle(bx - 6, by - 8, bx + 8, by - 16, bx + 2, by - 6, C_BROWN_WOOD);
  // 3 Khối tán lá tròn xanh mướt
  spr->fillCircle(bx + 4,  by - 22, 10, C_LEAF_GREEN);
  spr->fillCircle(bx - 6,  by - 18, 8,  C_LEAF_GREEN);
  spr->fillCircle(bx + 12, by - 16, 7,  C_SHELL_LIGHT);

  // 4. Mai rùa đại lục đồ sộ vòm xanh
  spr->fillEllipse(cx, by + 4, (int)(28 * sX), (int)(18 * sY), C_SHELL_GREEN);
  spr->fillEllipse(cx, by + 2, (int)(25 * sX), (int)(15 * sY), C_SHELL_LIGHT);

  // 5. Viền mai kim loại bạc dày kiên cố
  spr->fillRoundRect(cx - 30, by + 12, 60, 8, 3, C_SILVER_RIM);

  // 6. 4 Chân cột đình màu nâu đất vững chãi với móng vuốt trắng
  spr->fillRoundRect(cx - 26, by + 16, 10, 20, 3, C_EARTH_BROWN);
  spr->fillCircle(cx - 24, by + 34, 2, C_WHITE);
  spr->fillCircle(cx - 20, by + 34, 2, C_WHITE);

  spr->fillRoundRect(cx - 10, by + 18, 10, 18, 3, C_EARTH_BROWN);
  spr->fillCircle(cx - 8,  by + 34, 2, C_WHITE);
  spr->fillCircle(cx - 4,  by + 34, 2, C_WHITE);

  spr->fillRoundRect(cx + 6,  by + 18, 10, 18, 3, C_EARTH_BROWN);
  spr->fillCircle(cx + 8,  by + 34, 2, C_WHITE);
  spr->fillCircle(cx + 12, by + 34, 2, C_WHITE);

  spr->fillRoundRect(cx + 18, by + 16, 10, 20, 3, C_EARTH_BROWN);
  spr->fillCircle(cx + 20, by + 34, 2, C_WHITE);
  spr->fillCircle(cx + 24, by + 34, 2, C_WHITE);

  // 7. Đầu rùa bọc giáp xanh kiên cố
  spr->fillEllipse(cx - 24, by + 8, 12, 10, C_HEAD_GREEN);
  // Mỏ sừng đen
  spr->fillTriangle(cx - 34, by + 10, cx - 28, by + 6, cx - 28, by + 14, 0x18C3);
  // Gai sừng bạc hai bên má
  spr->fillTriangle(cx - 24, by + 14, cx - 30, by + 18, cx - 20, by + 18, C_WHITE);

  // 8. Đôi mắt đỏ kiên định
  if (!blink) {
    spr->fillCircle(cx - 24, by + 6, 2, C_RED_EYE);
    spr->drawPixel(cx - 25, by + 5, C_WHITE);
  } else {
    spr->drawLine(cx - 26, by + 6, cx - 22, by + 6, 0x18C3);
  }
}

} // namespace Session7Mythics
