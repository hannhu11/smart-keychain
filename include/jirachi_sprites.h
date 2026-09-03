#pragma once
// ============================================================================
// JIRACHI WISH MAKER - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 / ESP32-C3 / ESP32-S3 + ST7789 LCD (172x320 / 240x280)
// High-End 3D Pop Mart Vinyl Sculpting & Micro-Physics Engine
// Reference: 02_Mythic_Jirachi_Wish_Maker.png (100% Fidelity)
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace JirachiCelestial {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// =========================================================================
// JIRACHI NGÔI SAO BAN ĐIỀU ƯỚC THIÊN HÀ (MYTHIC JIRACHI WISH MAKER)
// ScaledCanvas C++ Implementation - 100% Hardware Compatible ST7789
// =========================================================================
inline void drawJirachiWishMaker(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink) {
  // -----------------------------------------------------------------------
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (ORGANIC MICRO-PHYSICS)
  // -----------------------------------------------------------------------
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
      spr->fillRect(ex - 2, eyeY - 3, 2, 2, C_WHITE_VINYL);
      spr->drawPixel(ex + 2, eyeY + 2, C_WHITE_VINYL);
      spr->drawPixel(ex + 1, eyeY - 2, C_WHITE_VINYL);
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

} // namespace JirachiCelestial
