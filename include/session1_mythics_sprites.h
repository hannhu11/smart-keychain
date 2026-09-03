#pragma once
// ============================================================================
// SESSION 1 MYTHIC CELESTIALS SUITE - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 ST7789 IPS LCD (172x320 60FPS DMA)
// Pop Mart & Kawaii Visual DNA: Volumetric 4-Tone Shading & Crystal Catchlights
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace Session1Mythics {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// -------------------------------------------------------------
// Celebi Tinh Linh Rừng Xanh Thời Gian
// -------------------------------------------------------------
// =========================================================================
// CELEBI TINH LINH RỪNG XANH THỜI GIAN (MYTHIC CELEBI FOREST FAIRY)
// ScaledCanvas C++ Implementation - 100% Hardware Compatible ST7789
// Primitives used: fillCircle, fillRoundRect, fillEllipse, drawLine,
//                  drawFastHLine, drawFastVLine, drawCircle, drawEllipse, fillTriangle
// =========================================================================
static void drawCelebiForestFairy(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink) {
  // 1. Nhịp thở Squash & Stretch 5% bảo toàn thể tích quanh tâm (cx, cy)
  float breathFreq  = 2.0f;
  float breathPhase = angle * breathFreq;
  float breathSin   = sinf(breathPhase);

  int by   = cy + (int)(breathSin * 3.5f);
  float sY = 1.0f + 0.05f * breathSin;       // Co giãn trục dọc +5%
  float sX = 1.0f - 0.025f * breathSin;      // Co bù trục ngang -2.5%

  // 2. Cánh tiên đập trễ pha Delta Phi = 0.45 rad (dao động 15 độ tần số cao)
  float wingPhase = angle * 7.5f - 0.45f;
  float wingFlap  = sinf(wingPhase) * 5.0f;

  // 3. Ăng-ten quán tính khi bay lên xuống (Delta Phi = 0.25 rad)
  float antPhase = breathPhase - 0.25f;
  int antSwayX   = (int)(cosf(antPhase) * 2.5f);
  int antSwayY   = (int)(sinf(antPhase) * 2.0f);

  // 4. Bảng màu 16-bit RGB565 chuẩn xác
  const uint16_t C_FRESNEL        = 0xF7FE; // #F4FDF0 Viền Fresnel trắng ngọc
  const uint16_t C_BODY_BASE      = 0xCF94; // #C8F0A6 Thân búp hành tây mint pastel
  const uint16_t C_BODY_MID       = 0xB731; // #B2E58B Sắc xanh cỏ non trung gian
  const uint16_t C_BODY_SHADOW    = 0x8E8C; // #8FD065 Bóng đổ cằm và thân dưới
  const uint16_t C_BODY_DEEP      = 0x6D48; // #68A843 Bóng hốc tối
  const uint16_t C_CREST_TIP      = 0x3C65; // #3E8E2D Chóp nhọn củ hành tây xanh đậm
  const uint16_t C_CREST_DARK     = 0x22E3; // #245C1A Gân lá chóp vương miện rừng già
  const uint16_t C_CREST_GLOW     = 0x972D; // #95E46A Đón sáng chóp đầu
  const uint16_t C_PANTS_DARK     = 0x4C45; // #488A2E Quần đùi lá xanh đậm quanh hông
  const uint16_t C_PANTS_LIGHT    = 0x6DE9; // #6EBD4D Đón sáng quần lá
  const uint16_t C_LEGS_DARK      = 0x3BA4; // #3D7527 Chân búp măng rừng già
  const uint16_t C_LEGS_LIGHT     = 0x6529; // #64A648 Bàn chân đón sáng
  const uint16_t C_ANT_STEM       = 0xB751; // #B2E88F Thân ăng-ten xanh ngọc dẻo
  const uint16_t C_ANT_MID        = 0x66D9; // #64D8CB Chuyển sắc lam ngọc
  const uint16_t C_ANT_TIP        = 0x05BB; // #00B4D8 Chóp ăng-ten xanh lam dạ quang
  const uint16_t C_ANT_GLOW       = 0x777B; // #72EFDD Vầng quang cyan tỏa sáng
  const uint16_t C_EYE_RING       = 0x10C2; // #121812 Viền mắt đen nhung sắc nét 35%
  const uint16_t C_IRIS_DEEP      = 0x01F1; // #023E8A Đáy mắt xanh sapphire thẫm
  const uint16_t C_IRIS_SAPPHIRE  = 0x03B6; // #0077B6 Đồng tử xanh sapphire trong vắt
  const uint16_t C_IRIS_BRIGHT    = 0x05BB; // #00B4D8 Mống mắt lam ngọc tươi sáng
  const uint16_t C_IRIS_CAUSTIC   = 0x971D; // #90E0EF Vệt trăng khuyết đáy mắt
  const uint16_t C_WHITE          = 0xFFFF; // #FFFFFF Đốm bắt sáng chính 2x2 góc 10h
  const uint16_t C_SPEC_SEC       = 0xCF9F; // #CAF0F8 Đốm bắt sáng phụ 1x1 góc 4h
  const uint16_t C_BLUSH          = 0xFD54; // #FFAAA6 Má hồng đào tán mịn squishy
  const uint16_t C_MOUTH          = 0x19C3; // #1A3818 Nụ cười khóe miệng tí hon
  const uint16_t C_WING_GLASS     = 0xE7BF; // #E0F7FA Cánh tiên lụa trong suốt SSS
  const uint16_t C_WING_GLOW      = 0xA79A; // #A7F3D0 Phản quang viền cánh tiên
  const uint16_t C_WING_RIM       = 0x86FD; // #80DEEA Khung viền cánh tiên
  const uint16_t C_WING_VEIN      = 0x4E9C; // #4DD0E1 Gân cánh tiên trong suốt
  const uint16_t C_SHADOW_GND     = 0x08E1; // #0A1C0A Lõi bóng sàn đậm đặc
  const uint16_t C_SHADOW_DIFF    = 0x1162; // #142E14 Vầng bóng sàn khuếch tán
  const uint16_t C_MAGIC_SPORE    = 0xE7E9; // #E0FF4F Bụi bào tử rừng phát sáng
  const uint16_t C_STAR_GOLD      = 0xFF91; // #FEF08A Bụi sao hoàng kim ✨

  // =========================================================================
  // LỚP 1: BÓNG TIẾP XÚC MẶT SÀN CO GIÃN THEO ĐỘ CAO
  // =========================================================================
  int groundY = cy + 46;
  int diffRx  = (int)((22.0f - breathSin * 3.5f) * sX);
  int diffRy  = max(2, (int)(6.5f - breathSin * 1.2f));
  int coreRx  = (int)((16.0f - breathSin * 2.8f) * sX);
  int coreRy  = max(2, (int)(4.5f - breathSin * 1.0f));
  spr->drawEllipse(cx + 4, groundY, diffRx, diffRy, C_SHADOW_DIFF);
  spr->fillEllipse(cx + 4, groundY, coreRx, coreRy, C_SHADOW_GND);

  // =========================================================================
  // LỚP 2: CÁNH TIÊN PHÍA SAU (Far Wing) - Trễ pha 0.45 rad
  // =========================================================================
  int w1TipX = cx + 32;
  int w1TipY = by - 18 + (int)wingFlap;
  int w1MidX = cx + 24;
  int w1MidY = by - 8 + (int)(wingFlap * 0.7f);
  spr->fillTriangle(cx + 6, by - 4, w1TipX, w1TipY, w1MidX, w1MidY, C_WING_GLASS);
  spr->fillTriangle(cx + 6, by - 2, w1MidX, w1MidY, cx + 18, by + 4, C_WING_GLOW);
  spr->drawLine(cx + 6, by - 4, w1TipX, w1TipY, C_WING_RIM);
  spr->drawLine(cx + 6, by - 4, w1MidX, w1MidY, C_WING_VEIN);

  // =========================================================================
  // LỚP 3: CÁNH TAY SAU (Left / Far Arm)
  // =========================================================================
  spr->fillTriangle(cx - 10, by + 7, cx - 8, by + 3, cx - 26, by - 2, C_BODY_BASE);
  spr->drawLine(cx - 10, by + 3, cx - 26, by - 2, C_FRESNEL);
  // 3 ngón tay nhỏ nhắn búp măng
  spr->fillCircle(cx - 28, by - 5, 1, C_BODY_BASE);
  spr->fillCircle(cx - 30, by - 2, 1, C_BODY_BASE);
  spr->fillCircle(cx - 27, by + 1, 1, C_BODY_BASE);

  // =========================================================================
  // LỚP 4: ĐÔI CHÂN & BÀN CHÂN BO TRÒN DỄ THƯƠNG
  // =========================================================================
  // Chân sau (Far leg)
  spr->fillRoundRect(cx + 6, by + 18, (int)(7 * sX), (int)(12 * sY), 3, C_LEGS_DARK);
  spr->fillCircle(cx + 9, by + 28, (int)(3 * sX), C_LEGS_LIGHT);
  // Chân trước (Near leg)
  spr->fillRoundRect(cx + 12, by + 21, (int)(8 * sX), (int)(14 * sY), 4, C_LEGS_DARK);
  spr->fillRoundRect(cx + 13, by + 22, (int)(6 * sX), (int)(9 * sY), 3, C_LEGS_LIGHT);
  spr->fillCircle(cx + 16, by + 33, (int)(4 * sX), C_LEGS_LIGHT);
  spr->drawPixel(cx + 16, by + 34, C_FRESNEL);

  // =========================================================================
  // LỚP 5: QUẦN LÁ XANH ĐẬM (Leaf Bloomers)
  // =========================================================================
  spr->fillEllipse(cx + 3, by + 14, (int)(13 * sX), (int)(10 * sY), C_PANTS_DARK);
  spr->fillEllipse(cx + 2, by + 13, (int)(11 * sX), (int)(8 * sY), C_PANTS_LIGHT);
  spr->drawRoundRect(cx - 5, by + 8, (int)(14 * sX), (int)(8 * sY), 3, C_CREST_TIP);

  // =========================================================================
  // LỚP 6: THÂN BÚP HÀNH TÂY (Onion Fairy Body)
  // =========================================================================
  spr->fillEllipse(cx + 1, by + 7, (int)(12 * sX), (int)(11 * sY), C_BODY_SHADOW);
  spr->fillEllipse(cx, by + 6, (int)(11 * sX), (int)(10 * sY), C_BODY_BASE);
  spr->fillEllipse(cx - 2, by + 5, (int)(8 * sX), (int)(7 * sY), C_FRESNEL);

  // =========================================================================
  // LỚP 7: CÁNH TIÊN PHÍA TRƯỚC (Near Wing)
  // =========================================================================
  float frontFlap = sinf(wingPhase + 0.2f) * 5.0f;
  int w2TipX = cx + 38;
  int w2TipY = by - 12 + (int)frontFlap;
  int w2MidX = cx + 28;
  int w2MidY = by + (int)(frontFlap * 0.7f);
  spr->fillTriangle(cx + 8, by - 2, w2TipX, w2TipY, w2MidX, w2MidY, C_WING_GLASS);
  spr->fillTriangle(cx + 8, by, w2MidX, w2MidY, cx + 20, by + 8, C_WING_GLOW);
  spr->drawLine(cx + 8, by - 2, w2TipX, w2TipY, C_FRESNEL);
  spr->drawLine(cx + 8, by - 2, w2MidX, w2MidY, C_WING_VEIN);
  spr->fillCircle(w2TipX, w2TipY, 1, C_FRESNEL);

  // =========================================================================
  // LỚP 8: CÁNH TAY TRƯỚC (Right / Near Arm)
  // =========================================================================
  spr->fillTriangle(cx + 6, by + 6, cx + 8, by + 10, cx + 32, by + 10, C_BODY_BASE);
  spr->drawLine(cx + 6, by + 6, cx + 32, by + 9, C_FRESNEL);
  // 3 ngón tay búp măng dang rộng đón gió
  spr->fillCircle(cx + 34, by + 8, 1, C_BODY_BASE);
  spr->fillCircle(cx + 36, by + 10, 1, C_BODY_BASE);
  spr->fillCircle(cx + 33, by + 13, 1, C_BODY_BASE);

  // =========================================================================
  // LỚP 9: ĐẦU BÚP HÀNH TÂY & CHÓP XANH RỪNG VƯƠN CAO (Onion Sprout Crest)
  // =========================================================================
  int hy  = by - 8;
  int hrx = (int)(22 * sX);
  int hry = (int)(22 * sY);
  // Khối đầu tròn mịn màng
  spr->drawEllipse(cx - 3, hy, hrx + 1, hry + 1, C_FRESNEL);
  spr->fillEllipse(cx - 3, hy, hrx, hry, C_BODY_BASE);
  spr->fillEllipse(cx + 5, hy + 4, (int)(14 * sX), (int)(12 * sY), C_BODY_SHADOW);
  spr->fillCircle(cx - 16, hy + 8, (int)(9 * sX), C_BODY_BASE);
  spr->fillCircle(cx - 7, hy + 14, (int)(8 * sX), C_BODY_BASE);

  // Chóp đầu nhọn uốn cong thanh thoát về phía sau-trên (Flame/Onion Sprout Crest)
  spr->fillTriangle(cx - 4, hy - 14, cx + 12, hy - 10, cx + 18, hy - 40, C_BODY_BASE);
  spr->fillTriangle(cx + 2, hy - 22, cx + 14, hy - 16, cx + 18, hy - 40, C_CREST_GLOW);
  spr->fillTriangle(cx + 6, hy - 26, cx + 16, hy - 22, cx + 18, hy - 40, C_CREST_TIP);
  // Đỉnh vuốt cong nhẹ
  spr->fillTriangle(cx + 12, hy - 36, cx + 18, hy - 40, cx + 16, hy - 44, C_CREST_DARK);
  // Các đường khía gân lá xanh rừng thẫm uốn lượn
  spr->drawLine(cx + 16, hy - 44, cx + 8, hy - 18, C_CREST_DARK);
  spr->drawLine(cx + 16, hy - 44, cx + 12, hy - 14, C_CREST_DARK);
  spr->drawLine(cx + 16, hy - 44, cx + 16, hy - 22, C_CREST_DARK);
  spr->drawFastVLine(cx + 15, hy - 38, 12, C_CREST_DARK);
  spr->drawLine(cx + 6, hy - 18, cx + 15, hy - 41, C_FRESNEL);

  // =========================================================================
  // LỚP 10: CẶP ĂNG-TEN KÉP XANH NGỌC VƯƠN CAO, CHÓP XANH LAM DẠ QUANG
  // (Cong uốn lượn hình cánh cung duyên dáng + Quán tính dao động)
  // =========================================================================
  // 10.1 Ăng-ten trái (Far Antenna)
  int a1_x0 = cx - 11, a1_y0 = hy - 12;
  int a1_x1 = cx - 21 + antSwayX, a1_y1 = hy - 24 + antSwayY;
  int a1_x2 = cx - 23 + (int)(antSwayX * 1.2f), a1_y2 = hy - 34 + antSwayY;
  int a1_x3 = cx - 18 + (int)(antSwayX * 1.4f), a1_y3 = hy - 42 + antSwayY;

  // Thân ăng-ten uốn cong
  spr->drawLine(a1_x0, a1_y0, a1_x1, a1_y1, C_ANT_STEM);
  spr->drawLine(a1_x0 + 1, a1_y0, a1_x1 + 1, a1_y1, C_BODY_BASE);
  spr->drawLine(a1_x1, a1_y1, a1_x2, a1_y2, C_ANT_MID);
  spr->drawLine(a1_x2, a1_y2, a1_x3, a1_y3, C_ANT_TIP);
  // Chóp dạ quang xanh lam
  spr->drawCircle(a1_x3, a1_y3, 3, C_ANT_GLOW);
  spr->fillCircle(a1_x3, a1_y3, 2, C_ANT_TIP);
  spr->drawPixel(a1_x3, a1_y3, C_FRESNEL);

  // 10.2 Ăng-ten phải (Near Antenna)
  int a2_x0 = cx - 1, a2_y0 = hy - 14;
  int a2_x1 = cx + 3 + antSwayX, a2_y1 = hy - 26 + antSwayY;
  int a2_x2 = cx + 5 + (int)(antSwayX * 1.2f), a2_y2 = hy - 38 + antSwayY;
  int a2_x3 = cx + 1 + (int)(antSwayX * 1.4f), a2_y3 = hy - 46 + antSwayY;

  spr->drawLine(a2_x0, a2_y0, a2_x1, a2_y1, C_ANT_STEM);
  spr->drawLine(a2_x0 + 1, a2_y0, a2_x1 + 1, a2_y1, C_FRESNEL);
  spr->drawLine(a2_x1, a2_y1, a2_x2, a2_y2, C_ANT_MID);
  spr->drawLine(a2_x2, a2_y2, a2_x3, a2_y3, C_ANT_TIP);
  // Chóp dạ quang xanh lam to hơn, bắt mắt
  spr->drawCircle(a2_x3, a2_y3, 4, C_ANT_GLOW);
  spr->fillCircle(a2_x3, a2_y3, 3, C_ANT_TIP);
  spr->fillCircle(a2_x3, a2_y3, 1, C_FRESNEL);

  // =========================================================================
  // LỚP 11: MÁ HỒNG ĐÀO TÁN MỊN & NỤ CƯỜI TÍ HON
  // =========================================================================
  spr->fillEllipse(cx - 19, hy + 9, 4, 3, C_BLUSH);
  spr->fillEllipse(cx + 6, hy + 12, 5, 3, C_BLUSH);
  // Khóe miệng nụ cười nhỏ nhắn ở góc dưới má trái
  spr->drawPixel(cx - 13, hy + 16, C_MOUTH);
  spr->drawPixel(cx - 12, hy + 17, C_MOUTH);
  spr->drawPixel(cx - 11, hy + 17, C_MOUTH);
  spr->drawPixel(cx - 10, hy + 16, C_MOUTH);

  // =========================================================================
  // LỚP 12: ĐÔI MẮT PHA LÊ TO TRÒN CHIẾM 35% KHUÔN MẶT VIỀN ĐEN SẮC NÉT
  // =========================================================================
  // 12.1 Mắt trái (Far eye trong góc 3/4)
  int exL = cx - 17;
  int eyL = hy + 3;
  if (blink) {
    spr->drawEllipse(exL, eyL + 2, 5, 2, C_EYE_RING);
  } else {
    // Viền đen sắc nét
    spr->fillEllipse(exL, eyL, 6, 12, C_EYE_RING);
    // Mống mắt sapphire
    spr->fillEllipse(exL, eyL, 4, 10, C_IRIS_SAPPHIRE);
    // Mống mắt lam ngọc sáng
    spr->fillEllipse(exL, eyL + 1, 3, 7, C_IRIS_BRIGHT);
    // Vệt trăng khuyết đáy mắt
    spr->fillEllipse(exL, eyL + 5, 3, 4, C_IRIS_CAUSTIC);
    // Đáy mắt đồng tử đen thẳm
    spr->fillEllipse(exL, eyL, 3, 5, C_IRIS_DEEP);
    // 3 điểm bắt sáng mắt trái
    spr->fillRect(exL - 1, eyL - 3, 2, 2, C_WHITE);
    spr->drawPixel(exL + 1, eyL + 4, C_SPEC_SEC);
    spr->drawFastHLine(exL - 1, eyL + 6, 2, C_WHITE);
  }

  // 12.2 Mắt phải (Near eye - Trực diện 35% khuôn mặt)
  int exR = cx - 4;
  int eyR = hy + 6;
  if (blink) {
    spr->drawEllipse(exR, eyR + 2, 9, 3, C_EYE_RING);
    spr->drawEllipse(exR, eyR + 3, 9, 3, C_EYE_RING);
  } else {
    // Viền đen sắc nét nhung tuyền (Iconic thick black eye ring)
    spr->fillEllipse(exR, eyR, 11, 16, C_EYE_RING);
    // Mống mắt xanh sapphire
    spr->fillEllipse(exR, eyR, 9, 14, C_IRIS_SAPPHIRE);
    // Vùng xanh lam ngọc tươi sáng
    spr->fillEllipse(exR, eyR + 1, 8, 10, C_IRIS_BRIGHT);
    // Vệt trăng khuyết caustic phản quang đáy mắt
    spr->fillEllipse(exR, eyR + 6, 6, 4, C_IRIS_CAUSTIC);
    // Đồng tử xanh sapphire đen thẳm
    spr->fillEllipse(exR - 1, eyR - 1, 5, 8, C_IRIS_DEEP);
    // 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Specular Highlights)
    // 1. Đốm chính 2x2 góc 10h
    spr->fillRect(exR - 4, eyR - 5, 2, 2, C_WHITE);
    spr->drawPixel(exR - 3, eyR - 6, C_WHITE);
    // 2. Đốm phụ 1x1 góc 4h
    spr->drawPixel(exR + 2, eyR + 5, C_SPEC_SEC);
    // 3. Vệt trăng khuyết đáy mắt (Caustic crescent highlights)
    spr->drawFastHLine(exR - 3, eyR + 7, 4, C_WHITE);
    spr->drawFastHLine(exR - 2, eyR + 8, 2, C_SPEC_SEC);
  }

  // =========================================================================
  // LỚP 13: BỤI BÀO TỬ RỪNG XANH PHÁT QUANG (Forest Magic Spores ✨)
  // =========================================================================
  // Bụi hoàng kim
  spr->drawFastHLine(cx - 24, by + 16, 3, C_STAR_GOLD);
  spr->drawFastVLine(cx - 23, by + 15, 3, C_STAR_GOLD);
  spr->drawPixel(cx - 23, by + 16, C_WHITE);
  // Bụi lam ngọc
  spr->drawFastHLine(cx + 28, by - 28, 3, C_ANT_GLOW);
  spr->drawFastVLine(cx + 29, by - 29, 3, C_ANT_GLOW);
  spr->drawPixel(cx + 29, by - 28, C_WHITE);
  // Đốm sáng xanh lộc biếc
  spr->drawPixel(cx - 18, by - 22, C_MAGIC_SPORE);
  spr->drawPixel(cx + 22, by + 26, C_MAGIC_SPORE);
}

// -------------------------------------------------------------
// Jirachi Ngôi Sao Ban Điều Ước Thiên Hà (Thần Thú Nguyện Ước Nghìn Năm)
// -------------------------------------------------------------
// =========================================================================
// JIRACHI NGÔI SAO BAN ĐIỀU ƯỚC THIÊN HÀ (MYTHIC JIRACHI WISH MAKER)
// ScaledCanvas C++ Implementation - 100% Hardware Compatible ST7789
// Pop Mart / Vinyl High-End 3D Sculpting & Micro-Physics Engine
// =========================================================================
static void drawJirachiWishMaker(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink) {
  // -----------------------------------------------------------------------
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (ORGANIC MICRO-PHYSICS)
  // -----------------------------------------------------------------------
  // Chu kỳ nhịp thở & dao động lơ lửng
  float breathPhase = angle * 2.0f;
  
  // Chu kỳ lơ lửng theo phương đứng (Hovering float)
  int hoverOffsetY = (int)(sinf(breathPhase) * 3.5f);
  int by = cy + hoverOffsetY;

  // Nhịp thở đàn hồi Squash & Stretch 5% (Bảo toàn thể tích thực tế)
  float sY = 1.0f + 0.05f * sinf(breathPhase);
  float sX = 1.0f - 0.03f * sinf(breathPhase);

  // Trễ pha động học 3 dải bùa xanh ngọc (Delta Phi = 0.45 rad)
  float lagTagTop   = breathPhase - 0.45f;
  float lagTagLeft  = breathPhase - 0.45f - 0.15f;
  float lagTagRight = breathPhase - 0.45f + 0.15f;

  // Trễ pha tà áo lụa phía sau lưng (Delta Phi = 0.60 rad)
  float lagSashL = breathPhase - 0.60f;
  float lagSashR = breathPhase - 0.55f;

  // Trễ pha tai mũ rủ hai bên má (Delta Phi = 0.20 rad)
  float lagLappet = breathPhase - 0.20f;
  int lappetSway = (int)(sinf(lagLappet) * 1.5f);

  // -----------------------------------------------------------------------
  // 2. BẢNG MÀU 16-BIT RGB565 CHUẨN XÁC POP MART VINYL & PHÉP THUẬT
  // -----------------------------------------------------------------------
  const uint16_t C_GOLD_BRIGHT = 0xFFB4; // #FFF7A0 Viền Fresnel đỉnh sao
  const uint16_t C_GOLD_LIGHT  = 0xFF91; // #FEF08A Vàng sáng diện đón sáng
  const uint16_t C_GOLD_MAIN   = 0xFE62; // #FACC15 Sắc vàng hoàng kim chuẩn
  const uint16_t C_GOLD_WARM   = 0xED81; // #EAB308 Vàng hổ phách tạo khối 3D
  const uint16_t C_GOLD_SHADOW = 0xCC40; // #CA8A04 Vàng sẫm đổ bóng nếp gấp
  const uint16_t C_GOLD_DEEP   = 0x8261; // #854D0E Nâu hổ phách gầm mũ sao

  const uint16_t C_CYAN_BRIGHT = 0xA79F; // #A5F3FC Xanh ngọc đón sáng
  const uint16_t C_CYAN_MAIN   = 0x05BA; // #06B6D4 Xanh ngọc lam Tanzaku chính
  const uint16_t C_CYAN_DEEP   = 0x0BB2; // #0E7490 Xanh ngọc sẫm nếp bùa
  const uint16_t C_CYAN_GLYPH  = 0xC7DF; // #CFFAFE Ký tự ước nguyện cổ

  const uint16_t C_TEAR_CYAN   = 0x0438; // #0284C7 Vết bùa lệ ước dưới mắt

  const uint16_t C_WHITE_VINYL = 0xFFFF; // #FFFFFF Trắng sứ tinh khiết
  const uint16_t C_CREAM_WHITE = 0xFFDF; // #F8FAFC Trắng kem vinyl SSS
  const uint16_t C_BODY_SHADOW = 0xE75E; // #E2E8F0 Bóng đổ thể tích cơ thể
  const uint16_t C_CREASE_GREY = 0xCEBC; // #CBD5E1 Rãnh nách, cằm, chân

  const uint16_t C_THIRD_EYE   = 0x08A5; // #0F172A Mắt thứ ba nhắm tĩnh lặng
  const uint16_t C_EYE_DARK    = 0x0022; // #020617 Hốc mắt đen pha lê
  const uint16_t C_EYE_NAVY    = 0x18C9; // #1E1B4B Mống mắt chàm vũ trụ
  const uint16_t C_EYE_CAUSTIC = 0x3DFF; // #38BDF8 Khúc xạ đáy mắt ngọc lam

  const uint16_t C_BLUSH_PINK  = 0xF396; // #F472B6 Má hồng phấn ngọt ngào
  const uint16_t C_BLUSH_SOFT  = 0xFE7D; // #FBCFE8 Viền má hồng tán mịn
  const uint16_t C_MOUTH_CURVE = 0x320A; // #334155 Khóe miệng cười tí hon

  const uint16_t C_SILK_LIGHT  = 0xFFD8; // #FEF9C3 Lụa vàng mỏng đón sáng
  const uint16_t C_SILK_MAIN   = 0xFF08; // #FDE047 Tà áo lụa bay sau lưng
  const uint16_t C_SILK_SHADOW = 0xED81; // #EAB308 Bóng nếp lượn sóng áo lụa

  const uint16_t C_FLOOR_SHADOW= 0x9517; // #94A3B8 Bóng tiếp xúc sàn

  // -----------------------------------------------------------------------
  // 3. LỚP 1: BÓNG TIẾP XÚC MẶT SÀN (CONTACT AMBIENT SHADOW)
  // -----------------------------------------------------------------------
  int floorY = cy + 42;
  int shRadiusX = (int)((26.0f - hoverOffsetY * 1.5f) * sX);
  int shRadiusY = (int)((6.5f - hoverOffsetY * 0.4f));
  if (shRadiusX < 14) shRadiusX = 14;
  if (shRadiusY < 3)  shRadiusY = 3;
  spr->fillEllipse(cx, floorY, shRadiusX + 2, shRadiusY + 1, C_BODY_SHADOW);
  spr->fillEllipse(cx, floorY, shRadiusX, shRadiusY, C_FLOOR_SHADOW);

  // -----------------------------------------------------------------------
  // 4. LỚP 2: TÀ ÁO LỤA THIÊN HÀ BAY BỔNG SAU LƯNG (FLOWING SILK SASHES)
  // -----------------------------------------------------------------------
  // Cánh lụa trái (Left Silk Sash)
  int sashWaveL = (int)(sinf(lagSashL) * 4.0f);
  int sashBaseLX = cx - 8;
  int sashBaseLY = by + 12;
  int sashMidLX  = cx - 30;
  int sashMidLY  = by + 18 + sashWaveL;
  int sashEndLX  = cx - 50;
  int sashEndLY  = by + 23 + (int)(sinf(lagSashL + 0.4f) * 5.0f);
  spr->fillTriangle(sashBaseLX, sashBaseLY, sashMidLX, sashMidLY, sashBaseLX, sashBaseLY + 6, C_SILK_SHADOW);
  spr->fillTriangle(sashMidLX, sashMidLY, sashEndLX, sashEndLY, sashMidLX + 2, sashMidLY + 7, C_SILK_MAIN);
  spr->fillTriangle(sashEndLX, sashEndLY, sashEndLX + 8, sashEndLY + 5, sashMidLX + 4, sashMidLY + 8, C_SILK_LIGHT);
  spr->drawLine(sashBaseLX, sashBaseLY, sashMidLX, sashMidLY, C_GOLD_BRIGHT);
  spr->drawLine(sashMidLX, sashMidLY, sashEndLX, sashEndLY, C_GOLD_BRIGHT);

  // Cánh lụa phải (Right Silk Sash)
  int sashWaveR = (int)(sinf(lagSashR) * 4.0f);
  int sashBaseRX = cx + 8;
  int sashBaseRY = by + 12;
  int sashMidRX  = cx + 30;
  int sashMidRY  = by + 18 + sashWaveR;
  int sashEndRX  = cx + 50;
  int sashEndRY  = by + 23 + (int)(sinf(lagSashR + 0.4f) * 5.0f);
  spr->fillTriangle(sashBaseRX, sashBaseRY, sashMidRX, sashMidRY, sashBaseRX, sashBaseRY + 6, C_SILK_SHADOW);
  spr->fillTriangle(sashMidRX, sashMidRY, sashEndRX, sashEndRY, sashMidRX - 2, sashMidRY + 7, C_SILK_MAIN);
  spr->fillTriangle(sashEndRX, sashEndRY, sashEndRX - 8, sashEndRY + 5, sashMidRX - 4, sashMidRY + 8, C_SILK_LIGHT);
  spr->drawLine(sashBaseRX, sashBaseRY, sashMidRX, sashMidRY, C_GOLD_BRIGHT);
  spr->drawLine(sashMidRX, sashMidRY, sashEndRX, sashEndRY, C_GOLD_BRIGHT);

  // -----------------------------------------------------------------------
  // 5. LỚP 3: MŨ NGÔI SAO HOÀNG KIM 3 CÁNH (3-POINTED GOLDEN STAR HELM)
  // -----------------------------------------------------------------------
  int starTopX = cx;
  int starTopY = by - 46;
  int starLeftX = cx - 46;
  int starLeftY = by - 9;
  int starRightX = cx + 46;
  int starRightY = by - 9;

  spr->fillTriangle(starTopX, starTopY, starLeftX, starLeftY, cx, by - 12, C_GOLD_WARM);
  spr->fillTriangle(starTopX, starTopY, starRightX, starRightY, cx, by - 12, C_GOLD_SHADOW);
  spr->fillTriangle(starLeftX, starLeftY, starRightX, starRightY, cx, by - 6, C_GOLD_MAIN);

  spr->fillTriangle(starTopX, starTopY, starLeftX, starLeftY, cx - 12, by - 22, C_GOLD_LIGHT);
  spr->fillTriangle(starLeftX, starLeftY, cx - 18, by - 12, cx - 12, by - 22, C_GOLD_MAIN);
  spr->drawLine(starTopX, starTopY, starLeftX, starLeftY, C_GOLD_BRIGHT);

  spr->fillTriangle(starTopX, starTopY, starRightX, starRightY, cx + 12, by - 22, C_GOLD_MAIN);
  spr->fillTriangle(starRightX, starRightY, cx + 18, by - 12, cx + 12, by - 22, C_GOLD_SHADOW);
  spr->drawLine(starTopX, starTopY, starRightX, starRightY, C_GOLD_LIGHT);

  spr->fillTriangle(starLeftX, starLeftY, cx - 22, by + 1, cx - 14, by - 10, C_GOLD_WARM);
  spr->fillTriangle(starRightX, starRightY, cx + 22, by + 1, cx + 14, by - 10, C_GOLD_SHADOW);

  spr->fillEllipse(cx, by - 16, (int)(22 * sX), (int)(13 * sY), C_GOLD_SHADOW);
  spr->fillEllipse(cx, by - 17, (int)(20 * sX), (int)(12 * sY), C_GOLD_MAIN);
  spr->fillEllipse(cx - 2, by - 20, (int)(15 * sX), (int)(7 * sY), C_GOLD_LIGHT);

  // -----------------------------------------------------------------------
  // 6. LỚP 4: 3 DẢI BÙA NGUYỆN ƯỚC XANH NGỌC LAM (TANZAKU WISH TAGS)
  // -----------------------------------------------------------------------
  // DẢI BÙA 1: ĐỈNH SAO
  int t1BaseX = starTopX;
  int t1BaseY = starTopY + 2;
  int t1Wave = (int)(sinf(lagTagTop) * 2.0f);
  spr->fillRoundRect(t1BaseX - 3 + t1Wave, t1BaseY, 7, 24, 2, C_CYAN_DEEP);
  spr->fillRoundRect(t1BaseX - 3 + t1Wave, t1BaseY, 6, 23, 2, C_CYAN_MAIN);
  spr->fillRect(t1BaseX - 2 + t1Wave, t1BaseY + 2, 2, 20, C_CYAN_BRIGHT);
  spr->drawFastVLine(t1BaseX + t1Wave, t1BaseY + 5, 12, C_CYAN_GLYPH);
  spr->drawFastHLine(t1BaseX - 1 + t1Wave, t1BaseY + 8, 3, C_CYAN_GLYPH);
  spr->drawFastHLine(t1BaseX - 1 + t1Wave, t1BaseY + 13, 3, C_CYAN_GLYPH);

  // DẢI BÙA 2: CÁNH SAO TRÁI
  int t2BaseX = starLeftX + 2;
  int t2BaseY = starLeftY + 1;
  int t2Wave1 = (int)(sinf(lagTagLeft) * 3.0f);
  int t2Wave2 = (int)(sinf(lagTagLeft + 0.35f) * 4.0f);
  spr->fillRoundRect(t2BaseX - 3 + t2Wave1, t2BaseY, 7, 14, 2, C_CYAN_DEEP);
  spr->fillRoundRect(t2BaseX - 3 + t2Wave1, t2BaseY, 6, 13, 2, C_CYAN_MAIN);
  spr->fillRect(t2BaseX - 2 + t2Wave1, t2BaseY + 2, 2, 10, C_CYAN_BRIGHT);
  spr->fillRoundRect(t2BaseX - 3 + t2Wave2, t2BaseY + 12, 7, 14, 2, C_CYAN_DEEP);
  spr->fillRoundRect(t2BaseX - 3 + t2Wave2, t2BaseY + 12, 6, 13, 2, C_CYAN_MAIN);
  spr->fillRect(t2BaseX - 2 + t2Wave2, t2BaseY + 14, 2, 9, C_CYAN_BRIGHT);
  spr->drawFastVLine(t2BaseX + t2Wave1, t2BaseY + 4, 8, C_CYAN_GLYPH);
  spr->drawFastVLine(t2BaseX + t2Wave2, t2BaseY + 15, 8, C_CYAN_GLYPH);

  // DẢI BÙA 3: CÁNH SAO PHẢI
  int t3BaseX = starRightX - 2;
  int t3BaseY = starRightY + 1;
  int t3Wave1 = (int)(sinf(lagTagRight) * 3.0f);
  int t3Wave2 = (int)(sinf(lagTagRight + 0.35f) * 4.0f);
  spr->fillRoundRect(t3BaseX - 3 + t3Wave1, t3BaseY, 7, 14, 2, C_CYAN_DEEP);
  spr->fillRoundRect(t3BaseX - 3 + t3Wave1, t3BaseY, 6, 13, 2, C_CYAN_MAIN);
  spr->fillRect(t3BaseX - 1 + t3Wave1, t3BaseY + 2, 2, 10, C_CYAN_BRIGHT);
  spr->fillRoundRect(t3BaseX - 3 + t3Wave2, t3BaseY + 12, 7, 14, 2, C_CYAN_DEEP);
  spr->fillRoundRect(t3BaseX - 3 + t3Wave2, t3BaseY + 12, 6, 13, 2, C_CYAN_MAIN);
  spr->fillRect(t3BaseX - 1 + t3Wave2, t3BaseY + 14, 2, 9, C_CYAN_BRIGHT);
  spr->drawFastVLine(t3BaseX + t3Wave1, t3BaseY + 4, 8, C_CYAN_GLYPH);
  spr->drawFastVLine(t3BaseX + t3Wave2, t3BaseY + 15, 8, C_CYAN_GLYPH);

  // -----------------------------------------------------------------------
  // 7. LỚP 5: THÂN TRẮNG SỮA PHÚNG PHÍNH & HAI CHÂN BÁNH BAO
  // -----------------------------------------------------------------------
  int bodyY = by + 14;
  int bRx   = (int)(16 * sX);
  int bRy   = (int)(15 * sY);

  int footYL = by + 26 + (int)(sinf(breathPhase) * 1.0f);
  int footYR = by + 26 - (int)(sinf(breathPhase) * 1.0f);
  spr->fillCircle(cx - 7, footYL, (int)(4.5f * sX), C_BODY_SHADOW);
  spr->fillCircle(cx - 7, footYL - 1, (int)(4.2f * sX), C_WHITE_VINYL);
  spr->fillCircle(cx + 7, footYR, (int)(4.5f * sX), C_BODY_SHADOW);
  spr->fillCircle(cx + 7, footYR - 1, (int)(4.2f * sX), C_WHITE_VINYL);

  spr->fillEllipse(cx, bodyY + 1, bRx + 2, bRy + 2, C_BODY_SHADOW);
  spr->fillEllipse(cx, bodyY, bRx, bRy, C_CREAM_WHITE);
  spr->fillEllipse(cx - 1, bodyY - 2, bRx - 2, bRy - 3, C_WHITE_VINYL);
  spr->fillCircle(cx - 3, bodyY - 4, 5, C_WHITE_VINYL);

  // -----------------------------------------------------------------------
  // 8. LỚP 6: MẮT THỨ BA TRÊN BỤNG (TRUE EYE OF TRUTH)
  // -----------------------------------------------------------------------
  int thirdEyeY = by + 16;
  int eyeArcW   = (int)(13 * sX);
  spr->drawEllipse(cx, thirdEyeY, eyeArcW, (int)(5 * sY), C_CREASE_GREY);
  spr->drawEllipse(cx, thirdEyeY + 1, eyeArcW - 1, (int)(4 * sY), C_THIRD_EYE);
  spr->drawPixel(cx, thirdEyeY + 4, C_THIRD_EYE);
  spr->drawPixel(cx - 1, thirdEyeY + 3, C_THIRD_EYE);
  spr->drawPixel(cx + 1, thirdEyeY + 3, C_THIRD_EYE);

  // -----------------------------------------------------------------------
  // 9. LỚP 7: HAI TAY MŨM MĨM DANG RỘNG
  // -----------------------------------------------------------------------
  spr->fillTriangle(cx - 10, by + 10, cx - 23, by + 16, cx - 11, by + 17, C_BODY_SHADOW);
  spr->fillTriangle(cx - 10, by + 9, cx - 23, by + 15, cx - 11, by + 16, C_WHITE_VINYL);
  spr->drawPixel(cx - 24, by + 14, C_WHITE_VINYL);
  spr->drawPixel(cx - 25, by + 15, C_WHITE_VINYL);
  spr->drawPixel(cx - 24, by + 16, C_WHITE_VINYL);

  spr->fillTriangle(cx + 10, by + 10, cx + 23, by + 16, cx + 11, by + 17, C_BODY_SHADOW);
  spr->fillTriangle(cx + 10, by + 9, cx + 23, by + 15, cx + 11, by + 16, C_WHITE_VINYL);
  spr->drawPixel(cx + 24, by + 14, C_WHITE_VINYL);
  spr->drawPixel(cx + 25, by + 15, C_WHITE_VINYL);
  spr->drawPixel(cx + 24, by + 16, C_WHITE_VINYL);

  // -----------------------------------------------------------------------
  // 10. LỚP 8: ĐẦU & KHUÔN MẶT BÁNH BAO
  // -----------------------------------------------------------------------
  int headY = by - 6;
  int hRx   = (int)(21 * sX);
  int hRy   = (int)(15 * sY);

  spr->fillEllipse(cx, headY + 1, hRx + 1, hRy + 1, C_BODY_SHADOW);
  spr->fillEllipse(cx, headY, hRx, hRy, C_CREAM_WHITE);
  spr->fillCircle(cx - 13, headY + 2, (int)(6 * sX), C_WHITE_VINYL);
  spr->fillCircle(cx + 13, headY + 2, (int)(6 * sX), C_WHITE_VINYL);
  spr->fillEllipse(cx, headY - 2, hRx - 3, hRy - 3, C_WHITE_VINYL);

  // -----------------------------------------------------------------------
  // 11. LỚP 9: HAI TAI MŨ SAO VÀNG RỦ XUỐNG HAI BÊN MÁ (STAR LAPPETS)
  // -----------------------------------------------------------------------
  int lapLX = cx - 18 + lappetSway;
  int lapLY = by - 8;
  spr->fillRoundRect(lapLX - 4, lapLY, 8, 20, 3, C_GOLD_SHADOW);
  spr->fillRoundRect(lapLX - 4, lapLY, 7, 19, 3, C_GOLD_MAIN);
  spr->fillCircle(lapLX, lapLY + 18, 3, C_GOLD_LIGHT);
  spr->drawFastVLine(lapLX - 2, lapLY + 2, 14, C_GOLD_BRIGHT);

  int lapRX = cx + 18 + lappetSway;
  int lapRY = by - 8;
  spr->fillRoundRect(lapRX - 4, lapRY, 8, 20, 3, C_GOLD_DEEP);
  spr->fillRoundRect(lapRX - 3, lapRY, 7, 19, 3, C_GOLD_MAIN);
  spr->fillCircle(lapRX, lapRY + 18, 3, C_GOLD_LIGHT);
  spr->drawFastVLine(lapRX + 1, lapRY + 2, 14, C_GOLD_BRIGHT);

  spr->drawCircle(cx, by - 12, 12, C_GOLD_SHADOW);
  spr->drawCircle(cx, by - 13, 12, C_GOLD_WARM);

  // -----------------------------------------------------------------------
  // 12. LỚP 10: CHI TIẾT BIỂU CẢM KHUÔN MẶT
  // -----------------------------------------------------------------------
  spr->fillCircle(cx - 13, headY + 3, 4, C_BLUSH_SOFT);
  spr->fillCircle(cx - 13, headY + 3, 2, C_BLUSH_PINK);
  spr->fillCircle(cx + 13, headY + 3, 4, C_BLUSH_SOFT);
  spr->fillCircle(cx + 13, headY + 3, 2, C_BLUSH_PINK);

  spr->fillTriangle(cx - 10, headY + 1, cx - 12, headY + 6, cx - 8, headY + 6, C_TEAR_CYAN);
  spr->fillTriangle(cx + 10, headY + 1, cx + 8, headY + 6, cx + 12, headY + 6, C_TEAR_CYAN);

  int mouthY = headY + 5;
  spr->drawPixel(cx - 2, mouthY,     C_MOUTH_CURVE);
  spr->drawPixel(cx - 1, mouthY + 1, C_MOUTH_CURVE);
  spr->drawPixel(cx,     mouthY + 1, C_MOUTH_CURVE);
  spr->drawPixel(cx + 1, mouthY + 1, C_MOUTH_CURVE);
  spr->drawPixel(cx + 2, mouthY,     C_MOUTH_CURVE);

  // -----------------------------------------------------------------------
  // 13. LỚP 11: ĐÔI MẮT PHA LÊ 3 ĐIỂM BẮT SÁNG (3-POINT SPECULAR CRYSTAL EYES)
  // -----------------------------------------------------------------------
  int eyeY  = headY - 1;
  int eyeXL = cx - 10;
  int eyeXR = cx + 10;

  if (blink) {
    for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
      int ex = (eyeIdx == 0) ? eyeXL : eyeXR;
      spr->drawEllipse(ex, eyeY + 2, 5, 2, C_EYE_DARK);
      spr->drawEllipse(ex, eyeY + 3, 4, 1, C_EYE_DARK);
      spr->drawPixel(ex - 4, eyeY + 1, C_EYE_DARK);
      spr->drawPixel(ex + 4, eyeY + 1, C_EYE_DARK);
    }
  } else {
    for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
      int ex = (eyeIdx == 0) ? eyeXL : eyeXR;
      spr->fillEllipse(ex, eyeY, 5, 7, C_EYE_DARK);
      spr->fillEllipse(ex, eyeY - 1, 4, 5, C_EYE_NAVY);
      spr->fillEllipse(ex, eyeY + 3, 3, 2, C_EYE_CAUSTIC);
      spr->drawPixel(ex - 1, eyeY + 4, C_CYAN_BRIGHT);
      spr->drawPixel(ex,     eyeY + 4, C_WHITE_VINYL);
      spr->drawPixel(ex + 1, eyeY + 4, C_CYAN_BRIGHT);
      spr->fillCircle(ex, eyeY, 3, C_EYE_DARK);
      spr->fillRect(ex - 2, eyeY - 3, 2, 2, C_WHITE_VINYL); // Điểm 1 (10h, 2x2)
      spr->drawPixel(ex + 2, eyeY + 2, C_WHITE_VINYL);      // Điểm 2 (4h, 1x1)
      spr->drawPixel(ex + 1, eyeY - 2, C_WHITE_VINYL);      // Điểm 3 (2h, vệt màng nước)
    }
  }

  // -----------------------------------------------------------------------
  // 14. LỚP 12: HÀO QUANG BỤI SAO & KIM CƯƠNG PHÁT QUANG (STARDUST SPARKS ✨)
  // -----------------------------------------------------------------------
  int sparkT = (int)(angle * 8.0f) % 4;
  uint16_t colSpark = (sparkT % 2 == 0) ? C_GOLD_BRIGHT : C_CYAN_BRIGHT;

  int spTopX = starTopX + (int)(sinf(breathPhase * 1.5f) * 6.0f);
  int spTopY = starTopY - 6;
  spr->drawFastHLine(spTopX - 2, spTopY, 5, colSpark);
  spr->drawFastVLine(spTopX, spTopY - 2, 5, colSpark);
  spr->drawPixel(spTopX, spTopY, C_WHITE_VINYL);

  int spLeftX = starLeftX - 4;
  int spLeftY = starLeftY - 3 + (int)(cosf(breathPhase) * 3.0f);
  spr->drawPixel(spLeftX, spLeftY, colSpark);
  spr->drawPixel(spLeftX - 1, spLeftY, C_GOLD_LIGHT);
  spr->drawPixel(spLeftX + 1, spLeftY, C_GOLD_LIGHT);

  int spRightX = starRightX + 4;
  int spRightY = starRightY - 3 - (int)(cosf(breathPhase) * 3.0f);
  spr->drawPixel(spRightX, spRightY, colSpark);
  spr->drawPixel(spRightX, spRightY - 1, C_CYAN_BRIGHT);
  spr->drawPixel(spRightX, spRightY + 1, C_CYAN_BRIGHT);

  spr->drawPixel(cx - 16, by + 18 + (int)(sinf(breathPhase + 1.0f) * 2.0f), C_GOLD_BRIGHT);
  spr->drawPixel(cx + 17, by + 17 - (int)(sinf(breathPhase + 1.0f) * 2.0f), C_CYAN_BRIGHT);
}

// -------------------------------------------------------------
// Shaymin - Nhím Hoa Cỏ Gracidea (Linh Thú Hoa Cỏ Thần Thoại)
// -------------------------------------------------------------
// =========================================================================
// SHAYMIN - NHÍM HOA CỎ GRACIDEA (SHAYMIN FLORA HEDGEHOG 3D POP MART)
// ScaledCanvas C++ Implementation - 100% Hardware Compatible (LovyanGFX ST7789)
// =========================================================================
static void drawShayminFloraHedgehog(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float t, bool blink = false) {
  // 1. Nhịp thở Squash & Stretch 5%
  float breathPhase = t * 2.1f;
  int by = cy + (int)(sinf(breathPhase) * 2.5f);
  float sY = 1.0f + 0.05f * sinf(breathPhase);
  float sX = 1.0f - 0.025f * sinf(breathPhase);

  // Trễ pha vi vật lý hữu cơ
  float petalLag = breathPhase - 0.25f; // Trễ pha 80ms (~0.25 rad)
  int petalFlutter = (int)(sinf(petalLag) * 2.0f);
  float footLag = breathPhase - 0.40f;
  int footWobble = (int)(sinf(footLag) * 1.5f);

  // 2. Bảng màu 16-bit RGB565 chuẩn xác
  const uint16_t C_WHITE        = 0xFFFF; // #FFFFFF Sứ trắng muốt bồng bềnh
  const uint16_t C_BODY_SHADOW  = 0xE73C; // #E2E8F0 Bóng đổ sứ mềm mại
  const uint16_t C_BODY_OCCL    = 0xCE79; // #CBD5E1 Bóng nếp gấp sâu
  const uint16_t C_GRASS_LIGHT  = 0x9F0B; // #9BE15D Gai cỏ xanh ngọc non đón nắng
  const uint16_t C_GRASS_BASE   = 0x7E4A; // #78C850 Thảm cỏ xanh ngọc mướt mát
  const uint16_t C_GRASS_SHADOW = 0x3BE4; // #3D7D20 Khối cầu cỏ đổ bóng 3D
  const uint16_t C_GRASS_DEEP   = 0x22A2; // #235315 Nền cỏ khuất sâu
  const uint16_t C_POLLEN_GOLD  = 0xFE62; // #FACC15 Nhị & đốm phấn hoa hoàng kim
  const uint16_t C_POLLEN_LIGHT = 0xFF91; // #FEF08A Điểm sáng phấn hoa
  const uint16_t C_PETAL_PINK   = 0xF396; // #F472B6 Cánh hoa Gracidea nở rộ
  const uint16_t C_PETAL_LIGHT  = 0xFE79; // #FBCFE8 Viền cánh hoa đón sáng
  const uint16_t C_PETAL_CORE   = 0xD94E; // #DB2777 Tâm hoa hồng đậm
  const uint16_t C_STAMEN_GOLD  = 0xF4E1; // #F59E0B Nhụy hoa vàng tỏa hương
  const uint16_t C_STAMEN_SPECK = 0x4829; // #4A044E Hạt nhụy hoa tím thẫm
  const uint16_t C_LEAF_GREEN   = 0x1529; // #16A34A Lá xanh mướt dưới đài hoa
  const uint16_t C_LEAF_LIGHT   = 0x4EEF; // #4ADE80 Sống gân lá ngọc
  const uint16_t C_LEAF_SHADOW  = 0x1326; // #166534 Bóng lá phía sau
  const uint16_t C_EYE_DARK     = 0x0162; // #052E16 Hốc mắt lục bảo thẫm sâu
  const uint16_t C_EYE_EMERALD  = 0x15D0; // #10B981 Mống mắt ngọc lục bảo
  const uint16_t C_EYE_BRIGHT   = 0x3693; // #34D399 Vòm quang khúc xạ đáy mắt
  const uint16_t C_NOSE_BLACK   = 0x1967; // #1E293B Sống mũi cúc áo nhỏ xinh
  const uint16_t C_MOUTH_PINK   = 0xFE19; // #FDA4AF Lưỡi hồng ngọt ngào
  const uint16_t C_MOUTH_DEEP   = 0xE0E9; // #E11D48 Vòm họng chúm chím
  const uint16_t C_BLUSH_PEACH  = 0xFC87; // #FB923C Má ửng hồng cam tự nhiên
  const uint16_t C_FLOOR_SHADOW = 0x320A; // #334155 Bóng tiếp xúc mặt sàn

  // 3. Bóng tiếp xúc mặt sàn co giãn êm ái
  int shadowW = (int)(42 * (1.0f + 0.04f * sinf(breathPhase)));
  int shadowH = (int)(8 * (1.0f - 0.03f * sinf(breathPhase)));
  spr->fillEllipse(cx + 4, cy + 40, shadowW + 4, shadowH + 2, 0x1967);
  spr->fillEllipse(cx + 4, cy + 40, shadowW, shadowH, C_FLOOR_SHADOW);

  // 4. Chân sau bên phải (khuất trong bóng) lúc lắc nhịp nhàng
  spr->fillRoundRect(cx + 26, by + 22 + (int)(footWobble * 0.4f), (int)(11 * sX), (int)(16 * sY), 5, C_BODY_SHADOW);
  // Chân trước bên phải (khuất)
  spr->fillRoundRect(cx - 8, by + 23 + (int)(footWobble * 0.4f), (int)(10 * sX), (int)(16 * sY), 5, C_BODY_SHADOW);

  // 5. Lớp gai cỏ sâu phía sau lưng (3D Back Spikes Layer 1)
  spr->fillTriangle(cx - 2, by - 32, cx + 8, by - 48, cx + 18, by - 30, C_GRASS_DEEP);
  spr->fillTriangle(cx + 14, by - 30, cx + 24, by - 44, cx + 32, by - 24, C_GRASS_DEEP);
  spr->fillTriangle(cx + 28, by - 24, cx + 42, by - 34, cx + 44, by - 16, C_GRASS_DEEP);
  spr->fillTriangle(cx + 38, by - 16, cx + 54, by - 20, cx + 48, by - 4, C_GRASS_DEEP);
  spr->fillTriangle(cx + 44, by - 4, cx + 58, by + 2, cx + 46, by + 14, C_GRASS_DEEP);
  spr->fillTriangle(cx + 40, by + 10, cx + 52, by + 18, cx + 38, by + 24, C_GRASS_DEEP);

  // 6. Cánh hoa Gracidea tai phải (xa) e ấp sau lưng cỏ
  spr->fillCircle(cx - 16 + petalFlutter, by - 20, 6, C_PETAL_CORE);
  spr->fillCircle(cx - 16 + petalFlutter, by - 20, 5, C_PETAL_PINK);
  spr->fillCircle(cx - 10 + petalFlutter, by - 24, 6, C_PETAL_PINK);
  spr->fillCircle(cx - 10 + petalFlutter, by - 24, 4, C_PETAL_LIGHT);

  // 7. Lớp gai cỏ trung gian & khối cầu 3D chính (3D Mid Spikes Layer 2)
  spr->fillTriangle(cx - 6, by - 26, cx + 2, by - 42, cx + 14, by - 24, C_GRASS_SHADOW);
  spr->fillTriangle(cx + 10, by - 24, cx + 20, by - 38, cx + 28, by - 18, C_GRASS_SHADOW);
  spr->fillTriangle(cx + 24, by - 18, cx + 38, by - 28, cx + 40, by - 10, C_GRASS_SHADOW);
  spr->fillTriangle(cx + 34, by - 10, cx + 48, by - 14, cx + 42, by + 4, C_GRASS_SHADOW);
  spr->fillTriangle(cx + 38, by + 2, cx + 50, by + 8, cx + 38, by + 20, C_GRASS_SHADOW);

  // 8. Khối lưng cỏ xanh ngọc mướt mát (Lush Jade Grass Torso Dome)
  int gRx = (int)(38 * sX);
  int gRy = (int)(28 * sY);
  spr->fillEllipse(cx + 12, by - 4, gRx + 2, gRy + 2, C_GRASS_SHADOW); // Bóng khối cầu
  spr->fillEllipse(cx + 12, by - 4, gRx, gRy, C_GRASS_BASE);           // Thảm cỏ ngọc chính
  spr->fillEllipse(cx + 8, by - 10, (int)(30 * sX), (int)(18 * sY), C_GRASS_LIGHT); // Mặt cỏ đón nắng

  // Gai cỏ vòm trước & đỉnh đầu
  spr->fillTriangle(cx - 24, by - 16, cx - 18, by - 30, cx - 10, by - 14, C_GRASS_BASE);
  spr->fillTriangle(cx - 14, by - 18, cx - 8, by - 34, cx + 2, by - 16, C_GRASS_LIGHT);
  spr->fillTriangle(cx - 2, by - 18, cx + 6, by - 36, cx + 14, by - 16, C_GRASS_LIGHT);
  spr->fillTriangle(cx + 8, by - 16, cx + 18, by - 32, cx + 24, by - 14, C_GRASS_LIGHT);

  // 9. Đốm phấn hoa vàng hoàng kim trên lưng cỏ
  spr->fillEllipse(cx - 14, by - 18, 4, 2, C_POLLEN_GOLD);
  spr->drawPixel(cx - 14, by - 18, C_POLLEN_LIGHT);
  spr->fillEllipse(cx + 6, by - 22, 5, 3, C_POLLEN_GOLD);
  spr->drawPixel(cx + 6, by - 22, C_POLLEN_LIGHT);
  spr->fillEllipse(cx + 24, by - 8, 4, 2, C_POLLEN_GOLD);
  spr->drawPixel(cx + 24, by - 8, C_POLLEN_LIGHT);
  spr->fillEllipse(cx + 18, by + 2, 3, 2, C_POLLEN_GOLD);

  // 10. Thân trắng muốt bồng bềnh (Porcelain Belly & Body)
  int bRx = (int)(30 * sX);
  int bRy = (int)(18 * sY);
  spr->fillEllipse(cx + 4, by + 16, bRx + 2, bRy + 2, C_BODY_SHADOW);
  spr->fillEllipse(cx + 4, by + 15, bRx, bRy, C_WHITE);
  spr->fillEllipse(cx + 6, by + 20, (int)(22 * sX), (int)(10 * sY), C_BODY_SHADOW);
  spr->fillEllipse(cx + 6, by + 18, (int)(20 * sX), (int)(9 * sY), C_WHITE);

  // 11. Đôi chân nhỏ tròn vo như hạt đậu (Foreground Bean Feet)
  int f1x = cx - 22;
  int f1y = by + 20 + footWobble;
  spr->fillRoundRect(f1x, f1y, (int)(13 * sX), (int)(18 * sY), 6, C_BODY_SHADOW);
  spr->fillRoundRect(f1x + 1, f1y, (int)(11 * sX), (int)(17 * sY), 5, C_WHITE);
  spr->drawFastVLine(f1x + 4, f1y + 12, 4, C_BODY_SHADOW);
  spr->drawFastVLine(f1x + 8, f1y + 12, 4, C_BODY_SHADOW);

  int f2x = cx + 14;
  int f2y = by + 20 - footWobble;
  spr->fillRoundRect(f2x, f2y, (int)(14 * sX), (int)(18 * sY), 6, C_BODY_SHADOW);
  spr->fillRoundRect(f2x + 1, f2y, (int)(12 * sX), (int)(17 * sY), 5, C_WHITE);
  spr->drawFastVLine(f2x + 4, f2y + 12, 4, C_BODY_SHADOW);
  spr->drawFastVLine(f2x + 8, f2y + 12, 4, C_BODY_SHADOW);

  // 12. Đầu trắng muốt & Sống mũi nhỏ xinh (Head, Snout & Cheeks)
  int hy = by + 4;
  int hx = cx - 28;
  spr->fillEllipse(hx, hy, (int)(22 * sX), (int)(19 * sY), C_BODY_SHADOW);
  spr->fillEllipse(hx + 1, hy, (int)(21 * sX), (int)(18 * sY), C_WHITE);

  spr->fillTriangle(hx - 12, hy - 4, hx - 24, hy + 3, hx - 10, hy + 9, C_BODY_SHADOW);
  spr->fillTriangle(hx - 11, hy - 3, hx - 24, hy + 3, hx - 9, hy + 8, C_WHITE);

  // Má ửng hồng cam tự nhiên
  spr->fillEllipse(hx - 4, hy + 8, 7, 4, C_BLUSH_PEACH);
  spr->fillCircle(hx - 4, hy + 8, 2, C_WHITE);

  // Miệng cười chúm chím hé mở ngọt ngào
  spr->fillTriangle(hx - 18, hy + 6, hx - 12, hy + 6, hx - 14, hy + 13, C_MOUTH_DEEP);
  spr->fillCircle(hx - 14, hy + 9, 3, C_MOUTH_PINK);

  // Sống mũi cúc áo đen nhỏ xinh
  spr->fillCircle(hx - 24, hy + 3, 3, C_NOSE_BLACK);
  spr->drawPixel(hx - 25, hy + 2, C_WHITE);

  // 13. Hai chiếc lá xanh mướt dưới đài hoa Gracidea
  int flx = cx - 12;
  int fly = by + 8;
  spr->fillTriangle(flx, fly + 4, flx - 2, fly + 26, flx + 12, fly + 16, C_LEAF_SHADOW);
  spr->fillTriangle(flx + 1, fly + 4, flx - 1, fly + 24, flx + 10, fly + 15, C_LEAF_GREEN);
  spr->drawLine(flx + 2, fly + 6, flx + 4, fly + 20, C_LEAF_LIGHT);

  spr->fillTriangle(flx + 6, fly, flx + 28, fly + 12, flx + 12, fly + 20, C_LEAF_SHADOW);
  spr->fillTriangle(flx + 7, fly, flx + 26, fly + 11, flx + 12, fly + 18, C_LEAF_GREEN);
  spr->drawLine(flx + 8, fly + 2, flx + 20, fly + 12, C_LEAF_LIGHT);

  // 14. ĐÓA HOA HỒNG GRACIDEA NỞ RỘ (6 cánh, trễ pha 80ms)
  const float petalAngles[6] = { 0.0f, 1.047f, 2.094f, 3.141f, 4.188f, 5.235f };
  const int petalLens[6]     = { 18, 20, 19, 18, 17, 19 };

  for (int p = 0; p < 6; p++) {
    float ang = petalAngles[p] + 0.18f + petalFlutter * 0.03f;
    float cosA = cosf(ang);
    float sinA = sinf(ang);
    int len = petalLens[p];

    int tipX = flx + (int)(cosA * len);
    int tipY = fly + (int)(sinA * len);

    float perpCos = -sinA;
    float perpSin = cosA;
    int w = 7;
    int b1x = flx + (int)(cosA * 5 + perpCos * w);
    int b1y = fly + (int)(sinA * 5 + perpSin * w);
    int b2x = flx + (int)(cosA * 5 - perpCos * w);
    int b2y = fly + (int)(sinA * 5 - perpSin * w);

    spr->fillTriangle(flx, fly, b1x, b1y, tipX, tipY, C_PETAL_CORE);
    spr->fillTriangle(flx, fly, b2x, b2y, tipX, tipY, C_PETAL_PINK);
    spr->fillCircle(tipX, tipY, 3, C_PETAL_LIGHT);
    spr->drawLine(flx, fly, tipX, tipY, C_PETAL_LIGHT);
  }

  // Tâm đài hoa hồng đậm
  spr->fillCircle(flx, fly, 6, C_PETAL_CORE);

  // Nhị hoa vàng hoàng kim tỏa hương
  spr->fillCircle(flx, fly, 3, C_STAMEN_GOLD);
  spr->drawPixel(flx, fly, C_POLLEN_LIGHT);

  // Hạt nhụy hoa tím thẫm đặc trưng Gracidea
  for (int s = 0; s < 6; s++) {
    float ang = petalAngles[s] + 0.18f;
    int sx = flx + (int)(cosf(ang) * 5.5f);
    int sy = fly + (int)(sinf(ang) * 5.5f);
    spr->drawPixel(sx, sy, C_STAMEN_SPECK);
  }

  // 15. ĐÔI MẮT PHA LÊ XANH LỤC BẢO (3-Point Specular Emerald Crystal Eyes)
  int ex = hx - 10;
  int ey = hy - 1;

  if (blink) {
    spr->drawCircle(ex, ey + 1, 5, C_EYE_DARK);
    spr->drawCircle(ex, ey + 2, 5, C_EYE_DARK);
    spr->drawFastHLine(ex - 4, ey + 4, 8, C_EYE_DARK);
  } else {
    // 15.1 Hốc mắt lục bảo sâu
    spr->fillEllipse(ex, ey, 6, 8, C_EYE_DARK);
    // 15.2 Mống mắt ngọc lục bảo khúc xạ
    spr->fillEllipse(ex, ey + 2, 5, 5, C_EYE_EMERALD);
    // 15.3 Vòm sáng đáy mắt ngọc bích
    spr->fillEllipse(ex, ey + 4, 3, 2, C_EYE_BRIGHT);
    // 15.4 Đồng tử đen thẳm
    spr->fillCircle(ex, ey - 1, 3, C_EYE_DARK);

    // 15.5 ĐIỂM SÁNG 1: Primary Direct Keylight Specular
    spr->fillCircle(ex - 2, ey - 3, 2, C_WHITE);
    // 15.6 ĐIỂM SÁNG 2: Secondary Emerald Caustic Bounce
    spr->fillCircle(ex + 2, ey + 3, 1, C_WHITE);
    // 15.7 ĐIỂM SÁNG 3: Tertiary Surface Wetness Sparkle
    spr->drawPixel(ex + 2, ey - 2, C_WHITE);
  }
}

// -------------------------------------------------------------
// Victini - Tinh Linh Chiến Thắng Tai Chữ V
// -------------------------------------------------------------
// =========================================================================
// 04_MYTHIC_VICTINI_VICTORY_STAR - C++ ScaledCanvas Implementation
// 100% Hardware Compatible with ESP32 ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl 3D Sculpt: Giant V-Ears, Sapphire Eyes, V-Sign Hand
// Organic Micro-Physics: 5% Squash & Stretch, Flap Lag 0.45 rad, Ear Flames
// =========================================================================
static void drawVictiniVictoryStar(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // 1. Vi vật lý hữu cơ (Organic Micro-Physics)
  float breathPhase = angle * 2.4f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 4.0f);
  int by = cy + bounceY;

  // Cánh nhỏ vỗ trễ pha 0.45 rad
  float wLag = breathPhase - 0.45f;
  int wFlapL = (int)(sinf(wLag) * 4.0f);
  int wFlapR = (int)(sinf(wLag + 0.15f) * 4.0f);

  // Bảng màu RGB565 chuẩn Pop Mart Vinyl
  const uint16_t C_CREAM       = 0xFF13; // #FCE39E Thân kem vani
  const uint16_t C_CREAM_SHAD  = 0xE5CC; // #E2BA63 Bóng thân kem
  const uint16_t C_CREAM_LIGHT = 0xFFBB; // #FFF7DE Sáng vòm đỉnh
  const uint16_t C_ORANGE      = 0xF2C4; // #F35824 Cam rực lửa chữ V
  const uint16_t C_ORANGE_DARK = 0xD1E2; // #D63F10 Cam đổ bóng mép tai
  const uint16_t C_ORANGE_LGT  = 0xFC29; // #FF844B Cam bắt sáng đỉnh
  const uint16_t C_EAR_BLACK   = 0x18C3; // #1A1819 Lòng tai nhung đen
  const uint16_t C_EYE_NAVY    = 0x08E5; // #091B2C Viền hốc mắt
  const uint16_t C_EYE_BLUE    = 0x02B4; // #0556A5 Sapphire sâu thẳm
  const uint16_t C_EYE_CYAN    = 0x2DBF; // #2FB4F8 Lam ngọc phản quang
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Bắt sáng & răng nanh
  const uint16_t C_BLUSH       = 0xFD51; // #FFA68B Má đào
  const uint16_t C_MOUTH_DARK  = 0x8149; // #872B4C Khoang miệng
  const uint16_t C_SHADOW      = 0x18C3; // #12161E Bóng tiếp xúc

  // 1. Bóng tiếp xúc sàn đàn hồi
  int shadowW = (int)(28 * (1.0f - 0.18f * breathSin));
  spr->fillEllipse(cx, cy + 42, shadowW, 7, C_SHADOW);

  // 2. Đôi cánh lông vũ sau lưng (vỗ trễ pha)
  spr->fillEllipse(cx - 24, by + 10 + wFlapL, 8, 14, C_CREAM_SHAD);
  spr->fillEllipse(cx - 23, by + 10 + wFlapL, 7, 12, C_CREAM);
  spr->fillEllipse(cx + 24, by + 10 + wFlapR, 8, 14, C_CREAM_SHAD);
  spr->fillEllipse(cx + 23, by + 10 + wFlapR, 7, 12, C_CREAM);

  // 3. Đôi tai chữ V cam khổng lồ (Kiến tạo hình học 3D)
  // Tai trái
  spr->fillTriangle(cx - 8, by - 12, cx - 36, by - 48, cx - 18, by - 18, C_ORANGE_DARK);
  spr->fillTriangle(cx - 6, by - 14, cx - 34, by - 46, cx - 16, by - 20, C_ORANGE);
  spr->fillTriangle(cx - 10, by - 16, cx - 32, by - 44, cx - 20, by - 24, C_ORANGE_LGT);
  spr->fillTriangle(cx - 12, by - 20, cx - 28, by - 40, cx - 18, by - 26, C_EAR_BLACK);
  // Tai phải
  spr->fillTriangle(cx + 8, by - 12, cx + 36, by - 48, cx + 18, by - 18, C_ORANGE_DARK);
  spr->fillTriangle(cx + 6, by - 14, cx + 34, by - 46, cx + 16, by - 20, C_ORANGE);
  spr->fillTriangle(cx + 10, by - 16, cx + 32, by - 44, cx + 20, by - 24, C_ORANGE_LGT);
  spr->fillTriangle(cx + 12, by - 20, cx + 28, by - 40, cx + 18, by - 26, C_EAR_BLACK);

  // 4. Thân tròn mũm mĩm & Chân
  spr->fillEllipse(cx, by + 18, (int)(22 * sX), (int)(24 * sY), C_CREAM_SHAD);
  spr->fillEllipse(cx, by + 16, (int)(20 * sX), (int)(22 * sY), C_CREAM);
  spr->fillEllipse(cx, by + 20, (int)(14 * sX), (int)(15 * sY), C_CREAM_LIGHT);

  // Hai chân ngắn tròn
  spr->fillRoundRect(cx - 14, by + 30, 10, 14, 4, C_ORANGE);
  spr->fillRoundRect(cx + 4, by + 30, 10, 14, 4, C_ORANGE);

  // Họa tiết chữ V cam trước ngực
  spr->fillTriangle(cx, by + 18, cx - 10, by + 6, cx + 10, by + 6, C_ORANGE);
  spr->fillTriangle(cx, by + 15, cx - 7, by + 6, cx + 7, by + 6, C_ORANGE_LGT);

  // 5. Khối đầu tròn phúng phính Pop Mart
  spr->fillEllipse(cx, by - 2, (int)(26 * sX), (int)(22 * sY), C_CREAM_SHAD);
  spr->fillEllipse(cx, by - 4, (int)(24 * sX), (int)(20 * sY), C_CREAM);
  spr->fillEllipse(cx, by - 8, (int)(18 * sX), (int)(14 * sY), C_CREAM_LIGHT);

  // Má hồng đào
  spr->fillEllipse(cx - 16, by + 4, 6, 4, C_BLUSH);
  spr->fillEllipse(cx + 16, by + 4, 6, 4, C_BLUSH);

  // 6. Đôi mắt pha lê khổng lồ & 3 điểm bắt sáng
  if (!blink) {
    // Mắt trái
    spr->fillEllipse(cx - 10, by - 4, 7, 10, C_EYE_NAVY);
    spr->fillEllipse(cx - 10, by - 3, 6, 9, C_EYE_BLUE);
    spr->fillEllipse(cx - 10, by - 1, 5, 6, C_EYE_CYAN);
    spr->fillCircle(cx - 12, by - 8, 2, C_WHITE); // Điểm sáng 1 (10h)
    spr->drawPixel(cx - 8, by - 1, C_WHITE);       // Điểm sáng 2 (4h)
    spr->drawFastHLine(cx - 12, by + 4, 4, C_WHITE); // Vệt trăng khuyết đáy mắt

    // Mắt phải
    spr->fillEllipse(cx + 10, by - 4, 7, 10, C_EYE_NAVY);
    spr->fillEllipse(cx + 10, by - 3, 6, 9, C_EYE_BLUE);
    spr->fillEllipse(cx + 10, by - 1, 5, 6, C_EYE_CYAN);
    spr->fillCircle(cx + 8, by - 8, 2, C_WHITE);  // Điểm sáng 1 (10h)
    spr->drawPixel(cx + 12, by - 1, C_WHITE);      // Điểm sáng 2 (4h)
    spr->drawFastHLine(cx + 8, by + 4, 4, C_WHITE); // Vệt trăng khuyết đáy mắt
  } else {
    // Nhịp chớp mắt vui vẻ
    spr->drawEllipse(cx - 10, by - 2, 6, 3, C_EYE_NAVY);
    spr->drawEllipse(cx + 10, by - 2, 6, 3, C_EYE_NAVY);
  }

  // 7. Miệng cười nhe răng nanh tí hon
  spr->fillTriangle(cx, by + 10, cx - 4, by + 6, cx + 4, by + 6, C_MOUTH_DARK);
  spr->drawPixel(cx - 2, by + 7, C_WHITE); // Răng nanh chibi

  // 8. Cánh tay giơ chữ V biểu tượng chiến thắng
  spr->fillRoundRect(cx + 18, by + 2, 8, 16, 3, C_CREAM);
  spr->fillCircle(cx + 22, by, 4, C_ORANGE);
  spr->drawFastVLine(cx + 20, by - 6, 6, C_ORANGE);
  spr->drawFastVLine(cx + 23, by - 6, 6, C_ORANGE);
}

// -------------------------------------------------------------
// Manaphy - Hoàng Tử Biển Sâu Huyền Thoại
// -------------------------------------------------------------
// =========================================================================
// MANAPHY - HOÀNG TỬ BIỂN SÂU HUYỀN THOẠI (MYTHIC MANAPHY OCEAN PRINCE)
// Pop Mart / High-End Vinyl Collectible Art - 100% Hardware Compatible
// Target: ST7789 IPS 172x320 / 240x280 (16-bit RGB565)
// =========================================================================

static void drawMythicManaphy(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // 1. Nhịp bơi lơ lửng đại dương Squash & Stretch 5%
  float breathPhase = angle * 2.0f;
  float sY = 1.0f + 0.05f * sinf(breathPhase);
  float sX = 1.0f - 0.025f * sinf(breathPhase); // Area conservation: sY * sX ≈ 1.0
  int by = cy + (int)(sinf(breathPhase) * 3.5f); // Dao động bơi lơ lửng Y-bobbing

  // 2. Bảng màu 16-bit RGB565 chuẩn xác
  const uint16_t C_FRESNEL_RIM   = 0xCFDE; // #CCFBF1 Viền men sứ xanh ngọc băng lóa sáng
  const uint16_t C_BODY_CYAN     = 0x269D; // #22D3EE Thân ngọc lam đại dương bán trong suốt
  const uint16_t C_BODY_LIGHT    = 0x675F; // #67E8F9 Vùng phản quang sáng khoang thể dịch
  const uint16_t C_BODY_CORE_SSS = 0x0438; // #0284C7 Lõi tán xạ ánh sáng dưới bề mặt SSS
  const uint16_t C_DEEP_CYAN     = 0x0BB2; // #0E7490 Vùng đổ bóng khuất vạt nách và đuôi
  const uint16_t C_JADE_CORE     = 0x3693; // #34D399 Ngọc lục bảo biển phát quang đầu anten
  const uint16_t C_JADE_GLOW     = 0x6F36; // #6EE7B7 Quầng hào quang dạ quang ngọc bích
  const uint16_t C_RUBY_DEEP     = 0x98C3; // #991B1B Đáy bóng tối hồng ngọc Ruby
  const uint16_t C_RUBY_CORE     = 0xD924; // #DC2626 Lõi đỏ rực hồng ngọc trái tim đại dương
  const uint16_t C_RUBY_BRIGHT   = 0xEA28; // #EF4444 Cạnh vát lóa sáng giác cắt ruby
  const uint16_t C_GOLD_CROWN    = 0xF4E1; // #F59E0B Viền vàng hoàng kim & hoa văn anten
  const uint16_t C_GOLD_BRIGHT   = 0xFF91; // #FEF08A Điểm tâm sáng hoàng kim lấp lánh
  const uint16_t C_GOLD_EYE_RING = 0xFE62; // #FACC15 Viền mí mắt & chấm anten vàng
  const uint16_t C_EYE_DARK      = 0x0129; // #03254C Hốc mắt vực thẳm đại dương sâu thẳm
  const uint16_t C_EYE_IRIS_BLUE = 0x1A7B; // #1D4ED8 Thể thủy tinh Sapphire mắt xanh
  const uint16_t C_EYE_IRIS_AQUA = 0x3DFF; // #38BDF8 Khúc xạ đáy mắt màu lam ngọc
  const uint16_t C_BLUSH_PINK    = 0xFB90; // #FB7185 Đôi má hồng san hô e ấp
  const uint16_t C_MOUTH_DEEP    = 0x9887; // #9F1239 Khoang miệng hồng thẫm ngọt ngào
  const uint16_t C_MOUTH_TONGUE  = 0xFD35; // #FDA4AF Lưỡi nhỏ hồng phấn đáng yêu
  const uint16_t C_BUBBLE_GLOW   = 0x7E9F; // #7DD3FC Bọt nước ngân hà li ti phát sáng
  const uint16_t C_SEABED_SHADOW = 0x00E6; // #041E34 Bóng tiếp xúc mờ ảo đáy biển
  const uint16_t C_WHITE         = 0xFFFF; // #FFFFFF Điểm bắt sáng kim cương men sứ

  // 3. BÓNG TIẾP XÚC MỜ ẢO ĐÁY BIỂN (Soft Contact Shadow)
  int shadowRx = (int)((24.0f + 2.0f * sinf(breathPhase)) * sX);
  int shadowRy = 5;
  int shadowY  = cy + 38;
  spr->fillEllipse(cx, shadowY, shadowRx + 4, shadowRy + 1, C_SEABED_SHADOW);
  spr->fillEllipse(cx, shadowY, shadowRx, shadowRy, C_SEABED_SHADOW);

  // 4. BỌT NƯỚC NGÂN HÀ LI TI PHÁT SÁNG BỒNG BỀNH XUNG QUANH (Bioluminescent Galaxy Bubbles)
  const int bubbleOffsets[6][2] = {
    {-36, -26}, {38, -20}, {-42, 12}, {40, 18}, {-18, -44}, {22, -48}
  };
  const float bubblePhases[6] = {0.0f, 1.2f, 2.4f, 3.6f, 4.8f, 5.5f};
  for (int b = 0; b < 6; b++) {
    float bLag = breathPhase * 0.8f + bubblePhases[b];
    int bx = cx + bubbleOffsets[b][0] + (int)(cosf(bLag) * 3.0f);
    int bby = cy + bubbleOffsets[b][1] + (int)(sinf(bLag) * 4.0f);
    int br = (b % 2 == 0) ? 3 : 2;
    spr->drawCircle(bx, bby, br, C_BUBBLE_GLOW);
    spr->drawPixel(bx - 1, bby - 1, C_WHITE);
  }

  // 5. ĐÔI ĂNG-TEN ĐỈNH ĐẦU UỐN LƯỢN HÌNH CHỮ S (Độ trễ pha 80ms ~ 0.52 rad)
  int hy = by - 16;
  float antLag = breathPhase - 0.52f; // Trễ pha 80ms
  int sCurve1 = (int)(sinf(antLag) * 6.0f);
  int sCurve2 = (int)(cosf(antLag) * 3.0f);

  // Ăng-ten 1 (Phía trước):
  int a1RootX = cx - 2, a1RootY = hy - 14;
  int a1MidX  = cx + 16 + sCurve2, a1MidY = hy - 24 + sCurve1 / 2;
  int a1PeakX = cx + 36 + sCurve1, a1PeakY = hy - 20 - sCurve2;
  int a1TipX  = cx + 46 + sCurve1, a1TipY = hy - 4 + sCurve2;

  spr->drawLine(a1RootX, a1RootY, a1MidX, a1MidY, C_BODY_CYAN);
  spr->drawLine(a1RootX + 1, a1RootY, a1MidX + 1, a1MidY, C_FRESNEL_RIM);
  spr->drawLine(a1MidX, a1MidY, a1PeakX, a1PeakY, C_BODY_CYAN);
  spr->drawLine(a1MidX + 1, a1MidY, a1PeakX + 1, a1PeakY, C_FRESNEL_RIM);
  spr->drawLine(a1PeakX, a1PeakY, a1TipX, a1TipY, C_BODY_CYAN);
  spr->drawLine(a1PeakX + 1, a1PeakY, a1TipX + 1, a1TipY, C_FRESNEL_RIM);

  // Viên ngọc xanh ngọc bích phát quang 1 (Luminous Jade Gem Orb 1)
  spr->fillCircle(a1TipX, a1TipY, 6, C_JADE_GLOW);
  spr->fillCircle(a1TipX, a1TipY, 4, C_JADE_CORE);
  spr->fillCircle(a1TipX - 1, a1TipY - 1, 2, C_WHITE);

  // Ăng-ten 2 (Phía sau):
  int a2RootX = cx + 3, a2RootY = hy - 14;
  int a2MidX  = cx + 20 + sCurve2, a2MidY = hy - 28 + sCurve1 / 2;
  int a2PeakX = cx + 40 + sCurve1, a2PeakY = hy - 24 - sCurve2;
  int a2TipX  = cx + 52 + sCurve1, a2TipY = hy - 10 + sCurve2;

  spr->drawLine(a2RootX, a2RootY, a2MidX, a2MidY, C_DEEP_CYAN);
  spr->drawLine(a2RootX + 1, a2RootY, a2MidX + 1, a2MidY, C_BODY_CYAN);
  spr->drawLine(a2MidX, a2MidY, a2PeakX, a2PeakY, C_DEEP_CYAN);
  spr->drawLine(a2MidX + 1, a2MidY, a2PeakX + 1, a2PeakY, C_BODY_CYAN);
  spr->drawLine(a2PeakX, a2PeakY, a2TipX, a2TipY, C_DEEP_CYAN);
  spr->drawLine(a2PeakX + 1, a2PeakY, a2TipX + 1, a2TipY, C_BODY_CYAN);

  // Viên ngọc xanh ngọc bích phát quang 2 (Luminous Jade Gem Orb 2)
  spr->fillCircle(a2TipX, a2TipY, 6, C_JADE_GLOW);
  spr->fillCircle(a2TipX, a2TipY, 4, C_JADE_CORE);
  spr->fillCircle(a2TipX - 1, a2TipY - 1, 2, C_WHITE);

  // 6. HAI TAY BƠI DÀI XÒE RỘNG UYỂN CHUYỂN NHƯ VÂY CÁ TIÊN (Angel Fairy Swimming Flippers)
  float finLag = breathPhase - 0.35f;
  int finFlutterL = (int)(sinf(finLag) * 4.0f);
  int finFlutterR = (int)(sinf(finLag + 0.15f) * 4.0f);

  // Tay bơi trái:
  int fLx1 = cx - (int)(10 * sX), fLy1 = by + 3;
  int fLx2 = cx - (int)(32 * sX), fLy2 = by + 8 + finFlutterL;
  int fLx3 = cx - (int)(48 * sX), fLy3 = by + 4 + finFlutterL;
  spr->fillTriangle(fLx1, fLy1 - 3, fLx2, fLy2 - 5, fLx1, fLy1 + 5, C_DEEP_CYAN);
  spr->fillTriangle(fLx2, fLy2 - 5, fLx3, fLy3 - 2, fLx2, fLy2 + 4, C_BODY_CYAN);
  spr->fillCircle(fLx3, fLy3, 5, C_BODY_CYAN);
  spr->fillCircle(fLx3 - 1, fLy3 - 1, 3, C_BODY_LIGHT);
  spr->drawLine(fLx1, fLy1 - 3, fLx3, fLy3 - 2, C_FRESNEL_RIM);

  // Tay bơi phải:
  int fRx1 = cx + (int)(10 * sX), fRy1 = by + 3;
  int fRx2 = cx + (int)(32 * sX), fRy2 = by + 8 + finFlutterR;
  int fRx3 = cx + (int)(48 * sX), fRy3 = by + 4 + finFlutterR;
  spr->fillTriangle(fRx1, fRy1 - 3, fRx2, fRy2 - 5, fRx1, fRy1 + 5, C_DEEP_CYAN);
  spr->fillTriangle(fRx2, fRy2 - 5, fRx3, fRy3 - 2, fRx2, fRy2 + 4, C_BODY_CYAN);
  spr->fillCircle(fRx3, fRy3, 5, C_BODY_CYAN);
  spr->fillCircle(fRx3 - 1, fRy3 - 1, 3, C_BODY_LIGHT);
  spr->drawLine(fRx1, fRy1 - 3, fRx3, fRy3 - 2, C_FRESNEL_RIM);

  // 7. THÂN NƯỚC GIỌT NƯỚC BÁN TRONG SUỐT & CHÂN BÁNH BAO
  spr->fillRoundRect(cx - (int)(11 * sX), by + 18, (int)(8 * sX), (int)(9 * sY), 4, C_BODY_CYAN);
  spr->fillRoundRect(cx + (int)(3 * sX),  by + 18, (int)(8 * sX), (int)(9 * sY), 4, C_BODY_CYAN);
  spr->drawFastHLine(cx - (int)(9 * sX), by + 26, (int)(5 * sX), C_FRESNEL_RIM);
  spr->drawFastHLine(cx + (int)(5 * sX),  by + 26, (int)(5 * sX), C_FRESNEL_RIM);

  int bRy = (int)(16 * sY);
  int bRx = (int)(16 * sX);
  spr->fillEllipse(cx, by + 10, bRx + 2, bRy + 2, C_FRESNEL_RIM);
  spr->fillEllipse(cx, by + 10, bRx, bRy, C_BODY_CYAN);
  spr->fillEllipse(cx, by + 11, (int)(12 * sX), (int)(12 * sY), C_BODY_CORE_SSS);
  spr->fillEllipse(cx, by + 8,  (int)(10 * sX), (int)(8 * sY),  C_BODY_LIGHT);
  spr->fillEllipse(cx - (int)(6 * sX), by + 14, 3, 2, C_WHITE);

  // 8. VIÊN HỒNG NGỌC RUBY ĐỎ RỰC TRƯỚC NGỰC & VÒNG CHẤM VÀNG HOÀNG KIM
  int gemY = by + 4;
  spr->fillEllipse(cx, gemY, 8, 10, C_GOLD_CROWN);
  spr->drawCircle(cx, gemY - 9, 1, C_GOLD_BRIGHT);
  spr->drawCircle(cx, gemY + 9, 1, C_GOLD_BRIGHT);
  spr->drawCircle(cx - 7, gemY, 1, C_GOLD_BRIGHT);
  spr->drawCircle(cx + 7, gemY, 1, C_GOLD_BRIGHT);

  spr->fillEllipse(cx, gemY, 6, 8, C_RUBY_DEEP);
  spr->fillEllipse(cx, gemY, 5, 7, C_RUBY_CORE);
  spr->fillEllipse(cx, gemY - 1, 3, 4, C_RUBY_BRIGHT);
  spr->fillCircle(cx - 1, gemY - 2, 1, C_WHITE);

  int dotY = by + 16;
  spr->fillEllipse(cx, dotY, 3, 4, C_GOLD_CROWN);
  spr->fillCircle(cx, dotY, 2, C_GOLD_BRIGHT);

  // 9. ĐẦU NƯỚC GIỌT NƯỚC KHỔNG LỒ & ĐỘ BÓNG MEN SỨ
  int hRy = (int)(22 * sY);
  int hRx = (int)(26 * sX);
  spr->fillEllipse(cx, hy, hRx + 2, hRy + 2, C_FRESNEL_RIM);
  spr->fillEllipse(cx, hy, hRx, hRy, C_BODY_CYAN);
  spr->fillEllipse(cx, hy + 2, (int)(21 * sX), (int)(17 * sY), C_BODY_LIGHT);

  spr->fillEllipse(cx - (int)(10 * sX), hy - (int)(11 * sY), 7, 3, C_WHITE);
  spr->fillCircle(cx + (int)(12 * sX), hy - (int)(8 * sY), 2, C_WHITE);

  // 10. HOA VĂN MÍ MẮT HOÀNG KIM & ĐỐM TRÒN ĂNG-TEN MẮT (100% Khớp ảnh mẫu)
  int ey = hy + 1;
  int exL = cx - (int)(11 * sX);
  int exR = cx + (int)(11 * sX);

  spr->drawEllipse(exL, ey, 7, 9, C_GOLD_EYE_RING);
  spr->drawEllipse(exR, ey, 7, 9, C_GOLD_EYE_RING);

  spr->drawLine(exL - 1, ey - 9, exL - 3, ey - 15, C_GOLD_EYE_RING);
  spr->fillCircle(exL - 3, ey - 15, 3, C_GOLD_CROWN);
  spr->fillCircle(exL - 3, ey - 15, 2, C_GOLD_BRIGHT);

  spr->drawLine(exL + 4, ey - 8, exL + 8, ey - 13, C_GOLD_EYE_RING);
  spr->fillCircle(exL + 8, ey - 13, 3, C_GOLD_CROWN);
  spr->fillCircle(exL + 8, ey - 13, 2, C_GOLD_BRIGHT);

  spr->drawLine(exR + 1, ey - 9, exR + 3, ey - 15, C_GOLD_EYE_RING);
  spr->fillCircle(exR + 3, ey - 15, 3, C_GOLD_CROWN);
  spr->fillCircle(exR + 3, ey - 15, 2, C_GOLD_BRIGHT);

  spr->drawLine(exR - 4, ey - 8, exR - 8, ey - 13, C_GOLD_EYE_RING);
  spr->fillCircle(exR - 8, ey - 13, 3, C_GOLD_CROWN);
  spr->fillCircle(exR - 8, ey - 13, 2, C_GOLD_BRIGHT);

  // 11. ĐÔI MẮT XANH THẲM ĐẠI DƯƠNG PHA LÊ (3-Point Catchlights)
  if (blink) {
    spr->drawEllipse(exL, ey + 2, 6, 2, C_EYE_DARK);
    spr->drawEllipse(exR, ey + 2, 6, 2, C_EYE_DARK);
  } else {
    for (int eyeSide = 0; eyeSide < 2; eyeSide++) {
      int ex = (eyeSide == 0) ? exL : exR;
      spr->fillEllipse(ex, ey, 6, 8, C_EYE_DARK);
      spr->fillEllipse(ex, ey + 2, 5, 5, C_EYE_IRIS_BLUE);
      spr->fillEllipse(ex, ey + 4, 4, 2, C_EYE_IRIS_AQUA);
      spr->fillCircle(ex, ey - 1, 3, C_EYE_DARK);

      // 3 Catchlights:
      spr->fillCircle(ex - 2, ey - 3, 2, C_WHITE); // Point 1: Keylight lớn
      spr->fillCircle(ex + 2, ey + 3, 1, C_WHITE); // Point 2: Caustic bounce
      spr->drawPixel(ex + 2, ey - 2, C_WHITE);     // Point 3: Micro twinkle
    }
  }

  // 12. ĐÔI MÁ ỬNG HỒNG NƯỚC BIỂN & NỤ CƯỜI HOÀNG TỬ BIỂN SÂU
  spr->fillEllipse(cx - (int)(18 * sX), hy + 6, 4, 3, C_BLUSH_PINK);
  spr->fillEllipse(cx + (int)(18 * sX), hy + 6, 4, 3, C_BLUSH_PINK);

  int mY = hy + 8;
  spr->fillTriangle(cx - 4, mY, cx + 4, mY, cx, mY + 5, C_MOUTH_DEEP);
  spr->fillCircle(cx, mY + 4, 2, C_MOUTH_TONGUE);
  spr->drawLine(cx - 4, mY, cx + 4, mY, C_DEEP_CYAN);
}

static void drawMythicManaphy(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  (void)breath;
  (void)scale;
  bool blink = (fmodf(angle, 3.5f) < 0.14f);
  drawMythicManaphy(spr, cx, cy, angle, blink);
}

} // namespace Session1Mythics
