#pragma once
// ============================================================================
// 04_MYTHIC_VICTINI_VICTORY_STAR - PRODUCTION C++ HEADER
// Hardware Target: ESP32 / ESP32-S3 + ST7789 IPS Display (172x320 60FPS DMA)
// Stylistic Origin: 3D Pop Mart Vinyl & Victory Star Mythic Pokémon
// Conformance: 3-Point Sapphire Eyes, 5% Squash & Stretch, 0.45 rad Wing Lag
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace VictiniVictory {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// =========================================================================
// 04_MYTHIC_VICTINI_VICTORY_STAR - C++ ScaledCanvas Implementation
// 100% Hardware Compatible with ESP32/ESP32-S3 + ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl 3D Sculpt: Giant V-Ears, Sapphire Eyes, V-Sign Hand
// Organic Micro-Physics: 5% Squash & Stretch, Flap Lag 0.45 rad, Ear Flames
// =========================================================================
void drawVictiniVictoryStar(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (Organic Micro-Physics)
  float breathPhase = angle * 2.4f;
  float breathSin   = sinf(breathPhase);
  
  // Nhịp nhún nhảy Squash & Stretch 5% bảo toàn thể tích
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 4.0f);
  int by = cy + bounceY; // Tọa độ Y động của thân và đầu

  // Đôi cánh nhỏ sau lưng vỗ nhịp trễ pha Delta Phi = 0.45 rad
  float wLag   = breathPhase - 0.45f;
  int wFlapL   = (int)(sinf(wLag) * 5.0f);
  int wFlapR   = (int)(sinf(wLag + 0.15f) * 5.0f);

  // Hào quang lửa chiến thắng bập bùng tần số cao trên chóp tai
  int flameL = (int)(sinf(angle * 14.0f) * 3.0f);
  int flameR = (int)(cosf(angle * 16.0f) * 3.0f);

  // 2. BẢNG MÀU 16-BIT RGB565 CHUẨN XÁC POP MART VINYL
  const uint16_t C_BODY_CREAM     = 0xFF13; // #FCE39E Kem vani chính
  const uint16_t C_BODY_SHADOW    = 0xE5CC; // #E2BA63 Bóng kem ấm
  const uint16_t C_BODY_HIGHLIGHT = 0xFFBB; // #FFF7DE Sáng vòm đỉnh
  const uint16_t C_EAR_ORANGE     = 0xF2C4; // #F35824 Cam rực lửa chữ V
  const uint16_t C_EAR_DARK       = 0xD1E2; // #D63F10 Cam đổ bóng mép tai
  const uint16_t C_EAR_LIGHT      = 0xFC29; // #FF844B Cam bắt sáng đỉnh
  const uint16_t C_EAR_BLACK      = 0x18C3; // #1A1819 Lòng tai nhung đen
  const uint16_t C_EAR_CHARCOAL   = 0x2945; // #2C282A Đổ bóng lòng tai
  const uint16_t C_EAR_RIM        = 0xFF76; // #FFF4D1 Viền kem mép tai
  const uint16_t C_EYE_NAVY       = 0x08C5; // #091B2C Viền mắt sapphire đêm
  const uint16_t C_EYE_DEEP       = 0x02B4; // #0556A5 Tròng sapphire đậm
  const uint16_t C_EYE_BRIGHT     = 0x2DBF; // #2FB4F8 Xanh da trời ngọc bích
  const uint16_t C_EYE_CYAN       = 0x7F1F; // #7EE3FB Đáy mắt bắt sáng cyan
  const uint16_t C_WHITE          = 0xFFFF; // #FFFFFF Catchlight pha lê & răng khểnh
  const uint16_t C_MOUTH_DARK     = 0x8149; // #872B4C Khoang miệng rượu vang
  const uint16_t C_MOUTH_TONGUE   = 0xF391; // #F4718C Lưỡi hồng đào
  const uint16_t C_BLUSH_PINK     = 0xFD31; // #FFA68B Má hồng phúng phính
  const uint16_t C_FIRE_GOLD      = 0xFEE7; // #FFDF38 Lửa vàng chói lọi
  const uint16_t C_FIRE_ORANGE    = 0xFCA0; // #FF9500 Hào quang lửa cam
  const uint16_t C_CONTACT_SHADOW = 0x10A2; // #12161E Bóng tiếp xúc sàn
  const uint16_t C_WING_CREAM     = 0xF6F2; // #F6DC92 Cánh lông vũ kem
  const uint16_t C_WING_SHADOW    = 0xDD8A; // #DAB052 Cánh đổ bóng

  // 3. LAYER 0: BÓNG TIẾP XÚC CO GIÃN MẶNH MẼ DƯỚI CHÂN (Ground Contact Shadow)
  int shadowW = (int)(38.0f * sX);
  int shadowH = (int)(8.5f * sX);
  spr->fillEllipse(cx, cy + 44, shadowW, shadowH, C_CONTACT_SHADOW);
  spr->fillEllipse(cx, cy + 44, (int)(shadowW * 0.65f), (int)(shadowH * 0.6f), 0x0841);

  // 4. LAYER 1: ĐÔI CÁNH LÔNG VŨ SAU LƯNG (Feathered Wings with Phase Lag)
  // 4.1 Cánh trái (viewer's left)
  spr->fillTriangle(cx - 16, by + 18, cx - 36, by + 10 + wFlapL, cx - 24, by + 20 + (int)(wFlapL * 0.8f), C_WING_SHADOW);
  spr->fillTriangle(cx - 20, by + 20, cx - 40, by + 18 + (int)(wFlapL * 0.8f), cx - 22, by + 26, C_WING_CREAM);
  spr->fillTriangle(cx - 18, by + 24, cx - 34, by + 26 + (int)(wFlapL * 0.6f), cx - 14, by + 28, C_WING_SHADOW);
  spr->drawLine(cx - 16, by + 18, cx - 36, by + 10 + wFlapL, C_WING_CREAM);

  // 4.2 Cánh phải (viewer's right)
  spr->fillTriangle(cx + 14, by + 16, cx + 34, by + 8 + wFlapR, cx + 22, by + 18 + (int)(wFlapR * 0.8f), C_WING_CREAM);
  spr->fillTriangle(cx + 18, by + 18, cx + 38, by + 16 + (int)(wFlapR * 0.8f), cx + 20, by + 24, C_WING_SHADOW);
  spr->fillTriangle(cx + 16, by + 22, cx + 32, by + 24 + (int)(wFlapR * 0.6f), cx + 12, by + 26, C_WING_CREAM);
  spr->drawLine(cx + 14, by + 16, cx + 34, by + 8 + wFlapR, C_BODY_HIGHLIGHT);

  // 5. LAYER 2: ĐÔI TAI NHỌN CHỮ V MÀU CAM RỰC RỠ (Giant Iconic V-Ears 3D)
  // 5.1 Tai trái (Viewer's Left - Upward Vertical Ear)
  spr->fillTriangle(cx - 18, by - 16, cx - 23, by - 96, cx + 2, by - 26, C_EAR_ORANGE);
  spr->fillTriangle(cx - 20, by - 16, cx - 23, by - 96, cx - 10, by - 40, C_EAR_DARK);
  spr->drawLine(cx - 18, by - 16, cx - 23, by - 96, C_EAR_LIGHT); // Sống tai vát sáng 3D
  // Lòng tai nhung đen
  spr->fillTriangle(cx - 15, by - 24, cx - 20, by - 76, cx - 4, by - 28, C_EAR_BLACK);
  spr->drawLine(cx - 15, by - 24, cx - 20, by - 76, C_EAR_CHARCOAL);
  spr->drawLine(cx - 23, by - 96, cx - 16, by - 16, C_EAR_RIM); // Mép viền kem 3D

  // 5.2 Tai phải (Viewer's Right - Diagonal Outward Ear)
  spr->fillTriangle(cx + 2, by - 26, cx + 88, by - 62, cx + 16, by - 14, C_EAR_ORANGE);
  spr->fillTriangle(cx + 8, by - 24, cx + 88, by - 62, cx + 45, by - 24, C_EAR_DARK);
  spr->drawLine(cx + 2, by - 26, cx + 88, by - 62, C_EAR_LIGHT); // Sống tai trên
  // Lòng tai nhung đen
  spr->fillTriangle(cx + 6, by - 24, cx + 70, by - 53, cx + 20, by - 18, C_EAR_BLACK);
  spr->drawLine(cx + 6, by - 24, cx + 70, by - 53, C_EAR_CHARCOAL);
  spr->drawLine(cx + 88, by - 62, cx + 18, by - 14, C_EAR_RIM); // Mép viền kem dưới

  // 5.3 Hào quang lửa chiến thắng trên chóp tai (Victory Flame Aura)
  // Chóp tai trái
  spr->fillCircle(cx - 23, by - 102 + flameL, 6, C_FIRE_ORANGE);
  spr->fillCircle(cx - 23, by - 100 + flameL, 4, C_FIRE_GOLD);
  spr->fillCircle(cx - 23, by - 98 + flameL, 2, C_WHITE);
  spr->drawPixel(cx - 25, by - 106 + flameL, C_FIRE_GOLD);
  // Chóp tai phải
  spr->fillCircle(cx + 91, by - 66 + flameR, 6, C_FIRE_ORANGE);
  spr->fillCircle(cx + 89, by - 64 + flameR, 4, C_FIRE_GOLD);
  spr->fillCircle(cx + 88, by - 62 + flameR, 2, C_WHITE);
  spr->drawPixel(cx + 94, by - 70 + flameR, C_FIRE_GOLD);

  // 6. LAYER 3: THÂN MÀU KEM VANI TRÒN VO MŨM MĨM & CHÂN (Chubby Vinyl Body)
  // Chân trái & móng cam
  spr->fillCircle(cx - 14, by + 39, 7, C_BODY_CREAM);
  spr->fillTriangle(cx - 18, by + 40, cx - 21, by + 46, cx - 16, by + 44, C_EAR_ORANGE);
  spr->fillTriangle(cx - 15, by + 41, cx - 14, by + 47, cx - 11, by + 44, C_EAR_ORANGE);
  // Chân phải & móng cam
  spr->fillCircle(cx + 10, by + 40, 7, C_BODY_CREAM);
  spr->fillTriangle(cx + 6, by + 41, cx + 6, by + 47, cx + 9, by + 44, C_EAR_ORANGE);
  spr->fillTriangle(cx + 10, by + 41, cx + 13, by + 46, cx + 14, by + 42, C_EAR_ORANGE);

  // Khối mông tròn trĩu Pop Mart
  spr->fillEllipse(cx - 11, by + 30, (int)(14 * sX), (int)(12 * sY), C_BODY_CREAM);
  spr->fillEllipse(cx + 9, by + 30, (int)(14 * sX), (int)(12 * sY), C_BODY_CREAM);
  spr->fillEllipse(cx - 1, by + 34, (int)(16 * sX), (int)(7 * sY), C_BODY_SHADOW);
  // Thân bụng chính
  spr->fillEllipse(cx - 1, by + 22, (int)(18 * sX), (int)(16 * sY), C_BODY_CREAM);
  spr->fillEllipse(cx - 4, by + 18, (int)(9 * sX), (int)(7 * sY), C_BODY_HIGHLIGHT);

  // Yếm ngực chữ V màu cam (Chest V-Collar)
  spr->fillTriangle(cx - 10, by + 11, cx - 2, by + 25, cx + 7, by + 11, C_EAR_ORANGE);
  spr->drawLine(cx - 10, by + 11, cx - 2, by + 25, C_EAR_LIGHT);
  spr->drawLine(cx + 7, by + 11, cx - 2, by + 25, C_EAR_DARK);

  // 7. LAYER 4: TỨ CHI & TƯ THẾ GIƠ TAY CHỮ V CHÀO NGƯỜI DÙNG (Victory Sign Hand)
  // Tay phải (viewer's left - xòe tự nhiên)
  spr->fillRoundRect(cx - 26, by + 15, 14, 9, 4, C_BODY_CREAM);
  spr->fillCircle(cx - 28, by + 19, 3, C_EAR_ORANGE);
  spr->fillCircle(cx - 30, by + 23, 3, C_EAR_ORANGE);
  spr->fillCircle(cx - 27, by + 27, 3, C_EAR_ORANGE);

  // Tay trái (viewer's right - GIƠ TAY CHỮ V CHIẾN THẮNG)
  spr->fillRoundRect(cx + 14, by + 8, 14, 10, 4, C_BODY_CREAM);
  spr->fillCircle(cx + 28, by + 4, 5, C_BODY_CREAM);
  // 2 ngón tay cam chữ V kiêu hãnh
  spr->fillRoundRect(cx + 23, by - 8, 4, 11, 2, C_EAR_ORANGE);
  spr->fillRoundRect(cx + 29, by - 7, 4, 11, 2, C_EAR_ORANGE);
  spr->fillCircle(cx + 26, by + 5, 2, C_BODY_CREAM); // Ngón cái gập

  // 8. LAYER 5: ĐẦU TRÒN & KHUÔN MẶT POP MART VINYL (Head Dome & Chubby Cheeks)
  spr->fillEllipse(cx - 2, by - 8, (int)(26 * sX), (int)(22 * sY), C_BODY_CREAM);
  spr->fillTriangle(cx - 14, by, cx - 5, by + 14, cx + 5, by, C_BODY_CREAM); // Cằm nhọn nhẹ
  spr->drawFastHLine(cx - 8, by + 12, 7, C_BODY_SHADOW);
  spr->fillEllipse(cx - 6, by - 18, (int)(12 * sX), (int)(6 * sY), C_BODY_HIGHLIGHT); // Vòm trán bóng

  // Má hồng đào phúng phính (Squishy Peach Blushes)
  spr->fillCircle(cx - 20, by - 2, 5, C_BLUSH_PINK);
  spr->fillCircle(cx + 16, by - 2, 5, C_BLUSH_PINK);

  // Mũi nhỏ xíu
  spr->drawPixel(cx - 5, by - 6, 0x3923);
  spr->drawPixel(cx - 4, by - 6, 0x3923);

  // 9. LAYER 6: ĐÔI MẮT SAPPHIRE KHỔNG LỒ (Giant 3-Point Specular Crystal Eyes)
  for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
    int ex = (eyeIdx == 0) ? (cx - 14) : (cx + 8);
    int ey = by - 8;

    if (blink) {
      spr->drawEllipse(ex, ey + 2, 8, 3, C_EYE_NAVY);
      spr->drawLine(ex + (eyeIdx == 0 ? -6 : 6), ey + 4, ex + (eyeIdx == 0 ? -9 : 9), ey + 1, C_EYE_NAVY);
    } else {
      // Hốc mắt sâu
      spr->fillEllipse(ex, ey, 9, 14, C_EYE_NAVY);
      // Tròng mắt sapphire đa tầng
      spr->fillEllipse(ex, ey, 8, 13, C_EYE_DEEP);
      spr->fillEllipse(ex, ey + 3, 7, 8, C_EYE_BRIGHT);
      spr->fillEllipse(ex, ey + 6, 5, 4, C_EYE_CYAN);

      // 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Specular Highlights)
      // Điểm 1: Primary Specular (Lớn, góc trên phải)
      spr->fillEllipse(ex + 2, ey - 5, 3, 2, C_WHITE);
      // Điểm 2: Secondary Caustic (Vừa, góc dưới trái)
      spr->fillCircle(ex - 2, ey + 5, 2, C_WHITE);
      // Điểm 3: Tertiary Micro Sparkle (Nhỏ, góc giữa phải)
      spr->drawPixel(ex + 3, ey + 2, C_WHITE);
    }
  }

  // 10. LAYER 7: NỤ CƯỜI TƯƠI & RĂNG NANH CHIBI (Joyful Mouth & Chibi Fang)
  spr->fillTriangle(cx - 11, by + 2, cx - 5, by + 14, cx + 2, by + 2, C_MOUTH_DARK);
  spr->fillCircle(cx - 5, by + 11, 3, C_MOUTH_TONGUE);
  spr->drawLine(cx - 11, by + 2, cx + 2, by + 2, C_BODY_SHADOW);
  // Chiếc răng nanh trắng nhỏ xinh
  spr->fillTriangle(cx - 9, by + 2, cx - 7, by + 2, cx - 8, by + 5, C_WHITE);

  // 11. LAYER 8: BỤI SAO CHIẾN THẮNG (Floating Victory Embers)
  spr->fillCircle(cx - 38, by - 22, 2, C_FIRE_GOLD);
  spr->drawPixel(cx - 38, by - 22, C_WHITE);
  spr->fillCircle(cx + 46, by - 12, 2, C_FIRE_GOLD);
  spr->drawPixel(cx + 46, by - 12, C_WHITE);
  spr->fillCircle(cx + 40, by + 32, 2, C_FIRE_ORANGE);
}


} // namespace VictiniVictory
