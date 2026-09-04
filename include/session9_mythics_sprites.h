#pragma once
// ============================================================================
// SESSION 9 SACRED LEGENDS & RAINBOW GUARDIANS - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 ST7789 IPS LCD (172x320 60FPS DMA)
// Pop Mart & Kawaii Visual DNA: Volumetric 4-Tone Shading & Crystal Catchlights
// Characters: Silvally, Rapidash Galar, Hydreigon, Morelull, Ho-Oh (IDs 90 to 94)
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace Session9Mythics {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// -------------------------------------------------------------
// Silvally - Thần Thú Cơ Giáp Huyễn Tưởng
// -------------------------------------------------------------
static void drawSilvallyChimeraGuardian(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.04f * breathSin;
  float sX = 1.0f - 0.02f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_WHITE_MANE  = 0xFFFF; // #FFFFFF Bờm sư tử trắng muốt
  const uint16_t C_SILVER_HELM = 0xBDD7; // #CBD5E1 Mũ giáp rìu bạc
  const uint16_t C_BLACK_BODY  = 0x18C3; // #1E293B Thân thú đen than chì
  const uint16_t C_GREEN_TALON = 0x2488; // #15803D Móng vuốt bò sát xanh
  const uint16_t C_PURP_SCALE  = 0x7997; // #7C3AED Vảy cá tím chân sau
  const uint16_t C_BLUE_FIN    = 0x221F; // #2563EB Vây đuôi cá lam
  const uint16_t C_RED_EYE     = 0xF800; // #EF4444 Mắt đỏ dũng mãnh
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(32 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Đuôi vây cá cơ giáp màu lam vuốt cong lên cao
  spr->fillTriangle(cx + 14, by + 12, cx + 34, by - 8, cx + 22, by + 18, C_BLUE_FIN);
  spr->fillTriangle(cx + 26, by - 2,  cx + 34, by - 8, cx + 36, by + 8,  C_SILVER_HELM);

  // 3. Thân thú đen than chì
  spr->fillEllipse(cx - 2, by + 14, (int)(18 * sX), (int)(14 * sY), C_BLACK_BODY);

  // 4. 2 Chân sau có vảy cá tím & 2 Chân trước móng vuốt bò sát xanh
  // Chân sau
  spr->fillRoundRect(cx + 4,  by + 18, 6, 18, 2, C_BLACK_BODY);
  spr->fillCircle(cx + 7,  by + 26, 3, C_PURP_SCALE);
  spr->fillRoundRect(cx + 12, by + 16, 6, 20, 2, C_BLACK_BODY);
  spr->fillCircle(cx + 15, by + 24, 3, C_PURP_SCALE);
  // Chân trước móng xanh
  spr->fillRoundRect(cx - 16, by + 18, 6, 18, 2, C_BLACK_BODY);
  spr->fillCircle(cx - 13, by + 34, 4, C_GREEN_TALON);
  spr->fillRoundRect(cx - 8,  by + 20, 6, 16, 2, C_BLACK_BODY);
  spr->fillCircle(cx - 5,  by + 34, 4, C_GREEN_TALON);

  // 5. Bờm lông vũ trắng muốt bao quanh ngực và cổ
  spr->fillCircle(cx - 8, by + 6,  12, C_WHITE_MANE);
  spr->fillCircle(cx,     by + 4,  10, C_WHITE_MANE);
  spr->fillCircle(cx - 6, by - 4,  13, C_WHITE_MANE);

  // 6. Đầu cơ giáp với mào rìu bạc khổng lồ vươn cao
  spr->fillCircle(cx - 10, by - 12, 10, C_WHITE_MANE);
  // Lưỡi rìu bạc trên đỉnh đầu
  spr->fillTriangle(cx - 14, by - 16, cx - 22, by - 40, cx - 4, by - 20, C_SILVER_HELM);
  spr->fillTriangle(cx - 6,  by - 20, cx + 4,  by - 38, cx,    by - 16, C_WHITE_MANE);
  spr->fillTriangle(cx + 2,  by - 18, cx + 12, by - 32, cx + 6, by - 14, C_WHITE_MANE);

  // 7. Bánh răng cơ học bên tai
  spr->fillCircle(cx - 2, by - 12, 4, C_SILVER_HELM);
  spr->drawCircle(cx - 2, by - 12, 4, C_BLACK_BODY);

  // 8. Mặt nạ & Mỏ thú cơ giáp
  spr->fillTriangle(cx - 16, by - 14, cx - 26, by - 8, cx - 14, by - 6, C_SILVER_HELM);

  // 9. Đôi mắt đỏ rực dũng cảm
  if (!blink) {
    spr->fillCircle(cx - 12, by - 12, 2, C_RED_EYE);
    spr->drawPixel(cx - 13, by - 13, C_WHITE_MANE);
  } else {
    spr->drawLine(cx - 14, by - 12, cx - 10, by - 12, C_BLACK_BODY);
  }
}

// -------------------------------------------------------------
// Rapidash Galar - Bạch Mã Kỳ Lân Kẹo Bông
// -------------------------------------------------------------
static void drawRapidashPastelUnicorn(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.0f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.04f * breathSin;
  float sX = 1.0f - 0.02f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Bờm mây kẹo bông uốn lượn thướt tha
  float maneLag = breathPhase - 0.4f;
  int maneSwayX = (int)(sinf(maneLag) * 3.5f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_WHITE_BODY  = 0xFFFF; // #FFFFFF Thân ngựa trắng sứ
  const uint16_t C_WHITE_SHAD  = 0xDEFB; // #E2E8F0 Bóng trắng sứ
  const uint16_t C_PURP_MANE   = 0xC49B; // #C084FC Tím kẹo bông pastel
  const uint16_t C_CYAN_MANE   = 0x7EBF; // #7DD3FC Lam ngọc kẹo bông pastel
  const uint16_t C_DARK_HORN   = 0x6196; // #7C3AED Sừng xoắn tím huyền bí
  const uint16_t C_CYAN_EYE    = 0x05F7; // #06B6D4 Mắt xanh biếc pha lê
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(30 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Chiếc đuôi mây kẹo bông pastel bồng bềnh uốn lượn sau lưng
  int tx = cx + 18 + maneSwayX;
  spr->fillCircle(tx,     by - 4,  10, C_PURP_MANE);
  spr->fillCircle(tx + 4, by + 4,  11, C_CYAN_MANE);
  spr->fillCircle(tx + 8, by + 14, 9,  C_PURP_MANE);

  // 3. Thân ngựa trắng muốt kiêu sa
  spr->fillEllipse(cx - 2, by + 14, (int)(16 * sX), (int)(13 * sY), C_WHITE_SHAD);
  spr->fillEllipse(cx - 2, by + 12, (int)(14 * sX), (int)(11 * sY), C_WHITE_BODY);

  // 4. 4 Chân thon thả với túm lông mây tím quanh cổ chân (Fetlocks)
  spr->fillRoundRect(cx - 14, by + 18, 4, 18, 2, C_WHITE_BODY);
  spr->fillCircle(cx - 12, by + 34, 4, C_PURP_MANE);

  spr->fillRoundRect(cx - 6,  by + 20, 4, 16, 2, C_WHITE_BODY);
  spr->fillCircle(cx - 4,  by + 34, 4, C_CYAN_MANE);

  spr->fillRoundRect(cx + 4,  by + 20, 4, 16, 2, C_WHITE_BODY);
  spr->fillCircle(cx + 6,  by + 34, 4, C_CYAN_MANE);

  spr->fillRoundRect(cx + 10, by + 18, 4, 18, 2, C_WHITE_BODY);
  spr->fillCircle(cx + 12, by + 34, 4, C_PURP_MANE);

  // 5. Cổ cao và Bờm mây kẹo bông hai màu tím-lam rủ dài
  spr->fillRoundRect(cx - 8, by - 4, 7, 16, 3, C_WHITE_BODY);
  // Bờm mây tím & lam
  spr->fillCircle(cx - 12, by - 12, 10, C_PURP_MANE);
  spr->fillCircle(cx - 8,  by - 6,  11, C_CYAN_MANE);
  spr->fillCircle(cx - 4,  by + 2,  10, C_PURP_MANE);

  // 6. Đầu kỳ lân trắng thanh tú
  spr->fillEllipse(cx - 10, by - 14, 8, 7, C_WHITE_BODY);
  // Mõm thon nhọn
  spr->fillTriangle(cx - 18, by - 12, cx - 12, by - 16, cx - 12, by - 10, C_WHITE_BODY);

  // 7. Sừng xoắn kỳ lân tím vươn thẳng kiêu hãnh
  spr->fillTriangle(cx - 14, by - 18, cx - 22, by - 42, cx - 8, by - 18, C_DARK_HORN);
  // Vòng xoắn trắng trên sừng
  spr->drawLine(cx - 14, by - 26, cx - 10, by - 24, C_WHITE_BODY);
  spr->drawLine(cx - 18, by - 34, cx - 14, by - 32, C_WHITE_BODY);

  // 8. Đôi mắt biếc pha lê to tròn dịu dàng
  if (!blink) {
    spr->fillCircle(cx - 10, by - 14, 2, C_CYAN_EYE);
    spr->drawPixel(cx - 11, by - 15, C_WHITE_BODY);
  } else {
    spr->drawLine(cx - 12, by - 14, cx - 8, by - 14, 0x18C3);
  }
}

// -------------------------------------------------------------
// Hydreigon - Tam Đầu Hắc Long Quyền Năng
// -------------------------------------------------------------
static void drawHydreigonThreeHeadedDragon(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.3f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.5f);
  int by = cy + bounceY;

  // Hai đầu tay lúc lắc nhịp nhàng
  int leftHeadLag  = (int)(sinf(angle * 2.5f - 0.6f) * 3.5f);
  int rightHeadLag = (int)(sinf(angle * 2.5f + 0.6f) * 3.5f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_CHARCOAL   = 0x18C3; // #1E293B Thân hắc long than chì
  const uint16_t C_BLUE_DRAG  = 0x2357; // #1D4ED8 Đầu rồng xanh hoàng gia
  const uint16_t C_MAGENTA_FR = 0xD094; // #E11D48 Vòng cổ cánh hoa đỏ tươi
  const uint16_t C_RED_EYE    = 0xF800; // #EF4444 Mắt đỏ quyền năng
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Răng nanh trắng
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 44, (int)(28 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. 6 Chiếc cánh rồng đen tuyền xòe sau lưng (6 Ribbon Wings)
  // Cánh trái
  spr->fillTriangle(cx - 10, by + 4, cx - 36, by - 16, cx - 18, by + 16, C_CHARCOAL);
  spr->fillTriangle(cx - 12, by + 6, cx - 38, by,      cx - 20, by + 18, C_CHARCOAL);
  spr->fillTriangle(cx - 14, by + 8, cx - 34, by + 14, cx - 22, by + 20, C_CHARCOAL);
  // Cánh phải
  spr->fillTriangle(cx + 10, by + 4, cx + 36, by - 16, cx + 18, by + 16, C_CHARCOAL);
  spr->fillTriangle(cx + 12, by + 6, cx + 38, by,      cx + 20, by + 18, C_CHARCOAL);
  spr->fillTriangle(cx + 14, by + 8, cx + 34, by + 14, cx + 22, by + 20, C_CHARCOAL);

  // 3. Đuôi rồng đen sọc đỏ uốn lượn dưới đáy
  spr->fillRoundRect(cx - 4, by + 22, 8, 18, 3, C_CHARCOAL);
  spr->fillRect(cx - 3, by + 26, 6, 3, C_MAGENTA_FR);
  spr->fillRect(cx - 3, by + 32, 6, 3, C_MAGENTA_FR);

  // 4. Thân rồng béo tròn màu đen than chì
  spr->fillEllipse(cx, by + 12, (int)(18 * sX), (int)(16 * sY), C_CHARCOAL);
  // Sọc đỏ trước bụng
  spr->fillRoundRect(cx - 8, by + 8, 16, 4, 2, C_MAGENTA_FR);
  spr->fillRoundRect(cx - 6, by + 14, 12, 4, 2, C_MAGENTA_FR);

  // 5. Cổ và Đầu trung tâm (Main Head)
  // Cổ
  spr->fillRoundRect(cx - 5, by - 4, 10, 14, 3, C_CHARCOAL);
  // Vòng cánh hoa đỏ tươi bao quanh đầu chính
  spr->fillCircle(cx, by - 12, 14, C_MAGENTA_FR);
  // Khối đầu rồng xanh lam
  spr->fillCircle(cx, by - 12, 9, C_BLUE_DRAG);
  // Mắt đỏ
  if (!blink) {
    spr->fillCircle(cx - 3, by - 13, 2, C_RED_EYE);
    spr->fillCircle(cx + 3, by - 13, 2, C_RED_EYE);
  } else {
    spr->drawLine(cx - 5, by - 13, cx - 1, by - 13, 0x0000);
    spr->drawLine(cx + 1, by - 13, cx + 5, by - 13, 0x0000);
  }

  // 6. Đầu tay trái (Left Puppet Head)
  int lhx = cx - 22;
  int lhy = by + 2 + leftHeadLag;
  spr->fillRoundRect(cx - 16, by + 4, 10, 8, 2, C_CHARCOAL);
  spr->fillCircle(lhx, lhy, 8, C_MAGENTA_FR);
  spr->fillCircle(lhx, lhy, 6, C_BLUE_DRAG);
  // Miệng há to
  spr->fillCircle(lhx - 2, lhy + 2, 3, 0x5000);

  // 7. Đầu tay phải (Right Puppet Head)
  int rhx = cx + 22;
  int rhy = by + 2 + rightHeadLag;
  spr->fillRoundRect(cx + 6, by + 4, 10, 8, 2, C_CHARCOAL);
  spr->fillCircle(rhx, rhy, 8, C_MAGENTA_FR);
  spr->fillCircle(rhx, rhy, 6, C_BLUE_DRAG);
  // Miệng há to
  spr->fillCircle(rhx + 2, rhy + 2, 3, 0x5000);
}

// -------------------------------------------------------------
// Morelull - Nấm Thần Phát Quang Dạ Cảnh
// -------------------------------------------------------------
static void drawMorelullMushroomFairy(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 2.5f);
  int by = cy + bounceY;

  // Nấm đung đưa nhẹ
  int mushSway1 = (int)(sinf(angle * 2.2f) * 2.0f);
  int mushSway2 = (int)(cosf(angle * 2.2f) * 2.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_CREAM_BODY  = 0xFFFF; // #FFFFFF Thân nấm trắng kem
  const uint16_t C_PINK_CAP    = 0xFC18; // #F472B6 Nón nấm hồng dạ quang
  const uint16_t C_PURP_CAP    = 0xC49B; // #C084FC Nón nấm tím dạ quang
  const uint16_t C_CAP_SHAD    = 0x9214; // #9333EA Chân nấm tím sẫm
  const uint16_t C_GREEN_BLUSH = 0xAF75; // #86EFAC Má xanh huỳnh quang
  const uint16_t C_BLACK_EYE   = 0x18C3; // #1E293B Hạt mắt đen tròn
  const uint16_t C_STEM_GREEN  = 0xDF19; // #D9F99D Cuống rễ xanh nhạt
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(24 * (1.0f - 0.15f * breathSin)), 5, C_SHADOW);

  // 2. Chân rễ cây nhỏ xíu chạm đất
  spr->drawLine(cx,     by + 24, cx,     by + 36, C_STEM_GREEN);
  spr->drawLine(cx,     by + 36, cx - 8, by + 40, C_STEM_GREEN);
  spr->drawLine(cx,     by + 36, cx + 8, by + 40, C_STEM_GREEN);

  // 3. Khối đầu nấm tròn xoe màu kem
  spr->fillCircle(cx, by + 12, (int)(16 * sX), C_CREAM_BODY);

  // 4. Hai má xanh huỳnh quang phát sáng dịu dàng
  spr->fillCircle(cx - 10, by + 14, 3, C_GREEN_BLUSH);
  spr->fillCircle(cx + 10, by + 14, 3, C_GREEN_BLUSH);

  // 5. Đôi mắt hạt đậu đen tròn ngây thơ
  if (!blink) {
    spr->fillEllipse(cx - 5, by + 12, 2, 4, C_BLACK_EYE);
    spr->fillEllipse(cx + 5, by + 12, 2, 4, C_BLACK_EYE);
  } else {
    spr->drawLine(cx - 7, by + 12, cx - 3, by + 12, C_BLACK_EYE);
    spr->drawLine(cx + 3, by + 12, cx + 7, by + 12, C_BLACK_EYE);
  }

  // 6. Cổ áo ren bèo hình bông tuyết trên đỉnh đầu
  spr->fillCircle(cx - 8, by - 2, 5, C_CREAM_BODY);
  spr->fillCircle(cx,     by - 4, 6, C_CREAM_BODY);
  spr->fillCircle(cx + 8, by - 2, 5, C_CREAM_BODY);

  // 7. 3 Cây nấm phát quang mọc trên đỉnh đầu (3 Bioluminescent Mushrooms)
  // Cây nấm chính giữa (To nhất màu hồng)
  int mx = cx + mushSway1;
  spr->fillRect(mx - 2, by - 24, 4, 22, C_STEM_GREEN);
  spr->fillEllipse(mx, by - 26, 12, 16, C_PINK_CAP);
  spr->fillRoundRect(mx - 10, by - 16, 20, 8, 3, C_CAP_SHAD);

  // Cây nấm bên trái (Màu tím nhạt)
  int lx = cx - 14 + mushSway2;
  spr->fillRect(lx, by - 16, 3, 16, C_STEM_GREEN);
  spr->fillEllipse(lx - 2, by - 18, 9, 13, C_PURP_CAP);
  spr->fillRoundRect(lx - 8, by - 10, 14, 6, 2, C_CAP_SHAD);

  // Cây nấm bên phải (Màu tím nhạt)
  int rx = cx + 14 - mushSway2;
  spr->fillRect(rx - 2, by - 14, 3, 14, C_STEM_GREEN);
  spr->fillEllipse(rx + 2, by - 16, 8, 12, C_PURP_CAP);
  spr->fillRoundRect(rx - 4, by - 8, 13, 6, 2, C_CAP_SHAD);
}

// -------------------------------------------------------------
// Ho-Oh - Phụng Hoàng Cầu Vồng Thần Thánh
// -------------------------------------------------------------
static void drawHoOhRainbowPhoenix(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.5f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.5f);
  int by = cy + bounceY;

  // Cánh sải rộng vỗ nhịp hào quang
  float wingFlap = sinf(angle * 3.0f) * 6.0f;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_RED_BODY    = 0xF9A0; // #F97316 Thân đỏ cam rực rỡ
  const uint16_t C_WHITE_BELLY = 0xFFFF; // #FFFFFF Bụng trắng muốt
  const uint16_t C_GREEN_FEAT  = 0x87E0; // #84CC16 Đầu cánh xanh cốm rực rỡ
  const uint16_t C_GOLD_CREST  = 0xFFE0; // #FEF08A Mào vương miện & đuôi vàng
  const uint16_t C_GOLD_DARK   = 0xFE60; // #FACC15 Bóng vàng
  const uint16_t C_DARK_TALON  = 0x18C3; // #1E293B Móng vuốt xám đen
  const uint16_t C_RED_EYE     = 0xF800; // #EF4444 Mắt ngọc đỏ
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 44, (int)(32 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Chùm đuôi hoàng kim xòe hình quạt rực rỡ (Golden Tail Plumes)
  spr->fillTriangle(cx - 16, by + 22, cx - 28, by + 40, cx, by + 28, C_GOLD_DARK);
  spr->fillTriangle(cx - 10, by + 24, cx,     by + 44, cx + 10, by + 24, C_GOLD_CREST);
  spr->fillTriangle(cx,     by + 28, cx + 28, by + 40, cx + 16, by + 22, C_GOLD_DARK);

  // 3. Thân phượng hoàng đỏ rực rỡ với bụng trắng
  spr->fillEllipse(cx, by + 12, (int)(15 * sX), (int)(18 * sY), C_RED_BODY);
  spr->fillEllipse(cx, by + 14, (int)(10 * sX), (int)(14 * sY), C_WHITE_BELLY);

  // 4. Đôi cánh cầu vồng khổng lồ sải rộng (Rainbow Wings)
  // Cánh trái
  int wly = by + (int)wingFlap;
  spr->fillTriangle(cx - 10, by + 6, cx - 44, wly - 18, cx - 18, by + 18, C_RED_BODY);
  spr->fillTriangle(cx - 36, wly - 14, cx - 46, wly - 20, cx - 40, wly - 6, C_GREEN_FEAT);
  spr->fillTriangle(cx - 28, wly - 8,  cx - 38, wly - 14, cx - 32, wly,     C_GREEN_FEAT);

  // Cánh phải
  int wry = by - (int)wingFlap;
  spr->fillTriangle(cx + 10, by + 6, cx + 44, wry - 18, cx + 18, by + 18, C_RED_BODY);
  spr->fillTriangle(cx + 36, wry - 14, cx + 46, wry - 20, cx + 40, wry - 6, C_GREEN_FEAT);
  spr->fillTriangle(cx + 28, wry - 8,  cx + 38, wry - 14, cx + 32, wry,     C_GREEN_FEAT);

  // 5. Cổ cao vươn thẳng với vòng cổ xanh cốm
  spr->fillRoundRect(cx - 4, by - 6, 8, 14, 3, C_RED_BODY);
  spr->fillRect(cx - 4, by + 2, 8, 3, C_GREEN_FEAT);

  // 6. Đầu phượng hoàng đỏ kiêu hãnh
  spr->fillCircle(cx, by - 12, 9, C_RED_BODY);

  // 7. Mào hoàng kim vương giả trên đỉnh đầu (Crown Crest)
  spr->fillCircle(cx, by - 22, 6, C_GOLD_CREST);
  spr->fillCircle(cx - 4, by - 24, 4, C_GOLD_CREST);
  spr->fillCircle(cx + 4, by - 24, 4, C_GOLD_CREST);

  // 8. Mỏ cong vàng & Đôi mắt đỏ uy nghiêm
  spr->fillTriangle(cx + 4, by - 12, cx + 18, by - 10, cx + 4, by - 6, C_GOLD_DARK);
  if (!blink) {
    spr->fillCircle(cx + 2, by - 12, 2, C_RED_EYE);
    spr->drawPixel(cx + 1, by - 13, C_WHITE_BELLY);
  } else {
    spr->drawLine(cx, by - 12, cx + 4, by - 12, C_DARK_TALON);
  }

  // 9. Hai chân móng vuốt xám đen
  spr->fillRoundRect(cx - 6, by + 26, 4, 8, 2, C_DARK_TALON);
  spr->fillRoundRect(cx + 2, by + 26, 4, 8, 2, C_DARK_TALON);
}

} // namespace Session9Mythics
