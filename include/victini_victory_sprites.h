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
  int bounceY = (int)(-fabsf(breathSin) * 3.5f);
  int by = cy + bounceY; // Tọa độ Y động của thân và đầu

  // Đôi cánh nhỏ sau lưng vỗ nhịp trễ pha Delta Phi = 0.45 rad
  float wLag   = breathPhase - 0.45f;
  int wFlapL   = (int)(sinf(wLag) * 4.5f);
  int wFlapR   = (int)(sinf(wLag + 0.15f) * 4.5f);

  // Hào quang lửa chiến thắng bập bùng tần số cao trên chóp tai
  int flameL = (int)(sinf(angle * 14.0f) * 3.0f);
  int flameR = (int)(cosf(angle * 16.0f) * 2.8f);

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

  // 3. LAYER 0: BÓNG TIẾP XÚC MẶT ĐẤT CO GIÃN MẶNH MẼ (Ground Contact Shadow)
  int shadowW = (int)(40.0f * sX);
  int shadowH = (int)(9.5f * sX);
  spr->fillEllipse(cx - 8, cy + 86, shadowW, shadowH, C_CONTACT_SHADOW);
  spr->fillEllipse(cx - 8, cy + 86, (int)(shadowW * 0.65f), (int)(shadowH * 0.6f), 0x0841);

  // 4. LAYER 1: ĐÔI CÁNH LÔNG VŨ SAU LƯNG (Feathered Wings with Phase Lag)
  // 4.1 Cánh trái (viewer's left)
  spr->fillTriangle(cx - 26, by + 48, cx - 46, by + 40 + wFlapL, cx - 34, by + 50 + (int)(wFlapL * 0.8f), C_WING_SHADOW);
  spr->fillTriangle(cx - 30, by + 50, cx - 50, by + 48 + (int)(wFlapL * 0.8f), cx - 32, by + 56, C_WING_CREAM);
  spr->fillTriangle(cx - 28, by + 54, cx - 44, by + 56 + (int)(wFlapL * 0.6f), cx - 24, by + 58, C_WING_SHADOW);
  spr->drawLine(cx - 26, by + 48, cx - 46, by + 40 + wFlapL, C_WING_CREAM);

  // 4.2 Cánh phải (viewer's right)
  spr->fillTriangle(cx + 28, by + 56, cx + 48, by + 48 + wFlapR, cx + 36, by + 58 + (int)(wFlapR * 0.8f), C_WING_CREAM);
  spr->fillTriangle(cx + 32, by + 58, cx + 52, by + 56 + (int)(wFlapR * 0.8f), cx + 34, by + 64, C_WING_SHADOW);
  spr->fillTriangle(cx + 30, by + 62, cx + 46, by + 64 + (int)(wFlapR * 0.6f), cx + 26, by + 66, C_WING_CREAM);
  spr->drawLine(cx + 28, by + 56, cx + 48, by + 48 + wFlapR, C_BODY_HIGHLIGHT);

  // 5. LAYER 2: ĐÔI TAI NHỌN CHỮ V KHỔNG LỒ (Iconic Giant V-Ears 3D)
  // 5.1 TAI PHẢI (Viewer's Right Ear - Huge Diagonal V-Wing)
  spr->fillTriangle(cx - 4, by - 18, cx + 112, by - 52, cx + 34, by - 2, C_BODY_CREAM);
  spr->drawLine(cx - 4, by - 18, cx + 112, by - 52, C_BODY_SHADOW);
  // Lòng tai đen nhung
  spr->fillTriangle(cx + 10, by - 14, cx + 88, by - 43, cx + 30, by + 4, C_EAR_BLACK);
  spr->drawLine(cx + 10, by - 14, cx + 88, by - 43, C_EAR_CHARCOAL);
  // Mặt trên tai cam rực lửa
  spr->fillTriangle(cx - 4, by - 18, cx + 112, by - 52, cx + 82, by - 40, C_EAR_ORANGE);
  spr->fillTriangle(cx - 4, by - 18, cx + 82, by - 40, cx + 6, by - 11, C_EAR_DARK);
  spr->drawLine(cx - 4, by - 18, cx + 110, by - 51, C_EAR_LIGHT); // Sống tai bắt sáng

  // 5.2 TAI TRÁI (Viewer's Left Ear - Massive Upward Triangular Spire)
  spr->fillTriangle(cx - 32, by - 4, cx - 6, by - 92, cx - 4, by - 18, C_EAR_ORANGE);
  spr->fillTriangle(cx - 6, by - 92, cx - 4, by - 18, cx - 12, by - 14, C_EAR_DARK); // Vát 3D
  spr->drawLine(cx - 31, by - 4, cx - 7, by - 90, C_EAR_LIGHT); // Sống tai sáng ngoài

  // 5.3 HÀO QUANG LỬA CHIẾN THẮNG TRÊN CHÓP TAI (Victory Flame Aura)
  // Chóp tai trái
  spr->fillCircle(cx - 6, by - 96 + flameL, 5, C_FIRE_ORANGE);
  spr->fillCircle(cx - 6, by - 98 + flameL, 3, C_FIRE_GOLD);
  spr->fillCircle(cx - 6, by - 100 + flameL, 2, C_WHITE);
  // Chóp tai phải
  spr->fillCircle(cx + 112, by - 55 + flameR, 5, C_FIRE_ORANGE);
  spr->fillCircle(cx + 114, by - 57 + flameR, 3, C_FIRE_GOLD);
  spr->fillCircle(cx + 116, by - 59 + flameR, 2, C_WHITE);

  // 6. LAYER 3: THÂN MÀU KEM VANI TRÒN VO MŨM MĨM & CHÂN (Chubby Vinyl Body)
  // Chân trái & móng cam
  spr->fillCircle(cx - 20, by + 76, 6, C_BODY_CREAM);
  spr->fillTriangle(cx - 24, by + 78, cx - 27, by + 84, cx - 22, by + 82, C_EAR_ORANGE);
  spr->fillTriangle(cx - 21, by + 79, cx - 20, by + 85, cx - 17, by + 82, C_EAR_ORANGE);
  // Chân phải & móng cam
  spr->fillCircle(cx + 3, by + 77, 6, C_BODY_CREAM);
  spr->fillTriangle(cx, by + 79, cx, by + 85, cx + 3, by + 82, C_EAR_ORANGE);
  spr->fillTriangle(cx + 4, by + 79, cx + 7, by + 84, cx + 8, by + 80, C_EAR_ORANGE);

  // Mông tròn trĩu Pop Mart
  spr->fillEllipse(cx - 17, by + 65, (int)(13 * sX), (int)(11 * sY), C_BODY_CREAM);
  spr->fillEllipse(cx + 5, by + 65, (int)(13 * sX), (int)(11 * sY), C_BODY_CREAM);
  spr->fillEllipse(cx - 6, by + 70, (int)(16 * sX), (int)(7 * sY), C_BODY_SHADOW);
  // Thân bụng chính
  spr->fillEllipse(cx - 6, by + 55, (int)(18 * sX), (int)(16 * sY), C_BODY_CREAM);
  spr->fillEllipse(cx - 9, by + 50, (int)(9 * sX), (int)(7 * sY), C_BODY_HIGHLIGHT);

  // Yếm ngực chữ V màu cam (Chest V-Collar)
  spr->fillTriangle(cx - 14, by + 38, cx - 6, by + 56, cx + 4, by + 38, C_EAR_ORANGE);
  spr->drawLine(cx - 14, by + 38, cx - 6, by + 56, C_EAR_LIGHT);
  spr->drawLine(cx + 4, by + 38, cx - 6, by + 56, C_EAR_DARK);

  // 7. LAYER 4: TỨ CHI & TƯ THẾ GIƠ TAY CHỮ V CHÀO NGƯỜI DÙNG (Victory Sign Hand)
  // Tay phải (viewer's left - xòe tự nhiên)
  spr->fillRoundRect(cx - 30, by + 44, 14, 9, 4, C_BODY_CREAM);
  spr->fillCircle(cx - 37, by + 49, 3, C_EAR_ORANGE);
  spr->fillCircle(cx - 38, by + 53, 3, C_EAR_ORANGE);
  spr->fillCircle(cx - 35, by + 57, 3, C_EAR_ORANGE);

  // Tay trái (viewer's right - GIƠ TAY CHỮ V CHIẾN THẮNG)
  spr->fillRoundRect(cx + 18, by + 36, 16, 10, 4, C_BODY_CREAM);
  spr->fillCircle(cx + 36, by + 30, 5, C_BODY_CREAM);
  // 2 ngón tay cam chữ V kiêu hãnh
  spr->fillRoundRect(cx + 31, by + 16, 4, 12, 2, C_EAR_ORANGE);
  spr->fillRoundRect(cx + 38, by + 18, 4, 12, 2, C_EAR_ORANGE);
  spr->fillCircle(cx + 34, by + 30, 3, C_BODY_CREAM); // Ngón cái gập

  // 8. LAYER 5: ĐẦU TRÒN & KHUÔN MẶT POP MART VINYL (Head Dome & Chubby Cheeks)
  spr->fillEllipse(cx - 6, by + 12, (int)(26 * sX), (int)(22 * sY), C_BODY_CREAM);
  spr->fillTriangle(cx - 30, by + 22, cx - 18, by + 45, cx + 10, by + 28, C_BODY_CREAM); // Cằm nhọn
  spr->drawFastHLine(cx - 22, by + 42, 8, C_BODY_SHADOW);
  spr->fillEllipse(cx - 10, by - 5, (int)(12 * sX), (int)(6 * sY), C_BODY_HIGHLIGHT); // Vòm trán bóng

  // Má hồng đào phúng phính (Squishy Peach Blushes)
  spr->fillCircle(cx - 26, by + 20, 5, C_BLUSH_PINK);
  spr->fillCircle(cx + 16, by + 18, 5, C_BLUSH_PINK);

  // Mũi nhỏ xíu
  spr->drawPixel(cx - 18, by + 11, 0x3923);

  // 9. LAYER 6: ĐÔI MẮT SAPPHIRE KHỔNG LỒ (Giant 3-Point Specular Crystal Eyes)
  for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
    int ex = (eyeIdx == 0) ? (cx - 25) : (cx + 12);
    int ey = (eyeIdx == 0) ? (by - 6) : (by - 1);
    int erx = (eyeIdx == 0) ? 6 : 11;
    int ery = (eyeIdx == 0) ? 13 : 15;

    if (blink) {
      spr->drawEllipse(ex, ey + 2, erx, 3, C_EYE_NAVY);
      spr->drawLine(ex + (eyeIdx == 0 ? -4 : 6), ey + 4, ex + (eyeIdx == 0 ? -7 : 9), ey + 1, C_EYE_NAVY);
    } else {
      // Hốc mắt sâu
      spr->fillEllipse(ex, ey, erx, ery, C_EYE_NAVY);
      // Tròng mắt sapphire đa tầng
      spr->fillEllipse(ex, ey, erx - 1, ery - 1, C_EYE_DEEP);
      spr->fillEllipse(ex, ey + 3, erx - 2, ery - 4, C_EYE_BRIGHT);
      spr->fillEllipse(ex, ey + 6, erx - 4, 4, C_EYE_CYAN);

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
  spr->fillTriangle(cx - 22, by + 19, cx - 16, by + 34, cx - 6, by + 20, C_MOUTH_DARK);
  spr->fillCircle(cx - 14, by + 30, 3, C_MOUTH_TONGUE);
  spr->drawLine(cx - 22, by + 19, cx - 6, by + 20, C_BODY_SHADOW);
  // Chiếc răng nanh trắng nhỏ xinh
  spr->fillTriangle(cx - 20, by + 19, cx - 19, by + 24, cx - 17, by + 19, C_WHITE);

  // 11. LAYER 8: BỤI SAO CHIẾN THẮNG (Floating Victory Embers)
  spr->fillCircle(cx - 38, by - 24, 2, C_FIRE_GOLD);
  spr->drawPixel(cx - 38, by - 24, C_WHITE);
  spr->fillCircle(cx + 48, by - 12, 2, C_FIRE_GOLD);
  spr->drawPixel(cx + 48, by - 12, C_WHITE);
  spr->fillCircle(cx + 42, by + 46, 2, C_FIRE_ORANGE);
}


} // namespace VictiniVictory
