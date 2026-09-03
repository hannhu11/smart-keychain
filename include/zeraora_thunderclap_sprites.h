#pragma once
// ============================================================================
// 08_MYTHIC_ZERAORA_THUNDERCLAP_CAT - PRODUCTION C++ HEADER
// Hardware Target: ESP32 / ESP32-S3 + ST7789 IPS Display (172x320 / 240x280 60FPS DMA)
// Stylistic Origin: 3D Pop Mart Vinyl & Mythic Thunderclap Pokémon
// Conformance: 3-Point Specular Cyan Eyes, 5% Squash & Stretch, 0.45 rad Tail Lag
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace ZeraoraThunderclap {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// =========================================================================
// 08_MYTHIC_ZERAORA_THUNDERCLAP_CAT - C++ ScaledCanvas Implementation
// 100% Hardware Compatible with ESP32/ESP32-S3 + ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl 3D Sculpt: Golden Fur, Plasma Ears, Cyan Eyes, Lightning Tail
// Organic Micro-Physics: 5% Squash & Stretch, Tail Lag 0.45 rad, Plasma Sparks
// =========================================================================
void drawZeraoraThunderclapCat(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (Organic Micro-Physics)
  float breathPhase = angle * 2.4f;
  float breathSin   = sinf(breathPhase);

  // Nhịp nhún nhảy Squash & Stretch 5% bảo toàn thể tích
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 4.0f);
  int by = cy + bounceY; // Tọa độ Y động của thân và đầu

  // Đuôi tia chớp uốn lượn sau lưng trễ pha Delta Phi = 0.45 rad
  float tailLag = breathPhase - 0.45f;
  int tailSwayX = (int)(sinf(tailLag) * 8.0f);
  int tailSwayY = (int)(cosf(tailLag) * 4.0f);

  // Hạt tia lửa điện plasma xanh lam lách tách quanh tai và đuôi
  int spark1 = (int)(sinf(angle * 14.0f) * 3.5f);
  int spark2 = (int)(cosf(angle * 18.0f) * 3.5f);
  int spark3 = (int)(sinf(angle * 22.0f) * 3.5f);

  // 2. BẢNG MÀU 16-BIT RGB565 CHUẨN XÁC POP MART VINYL
  const uint16_t C_GOLD_LIGHT      = 0xFF8F; // #FFF37A Vàng hoàng kim bắt sáng đỉnh
  const uint16_t C_GOLD_MAIN       = 0xFE63; // #FFCE1A Vàng hoàng kim chính
  const uint16_t C_GOLD_SHADOW     = 0xE540; // #E6A800 Vàng hổ phách đổ bóng
  const uint16_t C_GOLD_DARK       = 0xABA0; // #A87400 Vàng nâu che khuất rãnh sâu
  const uint16_t C_CHARCOAL        = 0x2125; // #23272F Xám than thân và mặt nạ
  const uint16_t C_CHARCOAL_DARK   = 0x10A3; // #13161C Đen tuyền vệt sấm & hốc mắt
  const uint16_t C_CHARCOAL_LIGHT  = 0x3A2A; // #3E4452 Xám đón sáng mép cơ
  const uint16_t C_CYAN_LIGHT      = 0x87BF; // #80F5FF Xanh cyan điện quang bắt sáng
  const uint16_t C_CYAN_MAIN       = 0x069F; // #00D2FF Xanh cyan plasma chính
  const uint16_t C_CYAN_DEEP       = 0x03B9; // #0077C8 Xanh lam viền bóng
  const uint16_t C_WHITE           = 0xFFFF; // #FFFFFF Catchlight, nanh & lõi chớp
  const uint16_t C_EYE_LINER       = 0x0882; // #0F1115 Viền mí mắt đen vểnh dũng cảm
  const uint16_t C_EYE_DEEP        = 0x022F; // #00457A Tròng mắt sapphire đêm
  const uint16_t C_EYE_BRIGHT      = 0x05BB; // #00B4D8 Vòm mắt xanh ngọc lam
  const uint16_t C_EYE_CYAN        = 0x66FB; // #64DFDF Đáy mắt caustic
  const uint16_t C_MOUTH_DARK      = 0x60E5; // #611C28 Khoang miệng rượu vang
  const uint16_t C_MOUTH_TONGUE    = 0xFB51; // #FF6B8B Lưỡi hồng đào
  const uint16_t C_PAW_PAD         = 0x073F; // #00E5FF Đệm móng vuốt xanh điện
  const uint16_t C_CLAW            = 0xEF7E; // #EAEFF5 Móng vuốt bạc sáng
  const uint16_t C_CONTACT_SHADOW  = 0x10A4; // #111622 Bóng tiếp xúc sàn

  // 3. LAYER 0: BÓNG TIẾP XÚC CO GIÃN MẶNH MẼ DƯỚI SÀN (Ground Contact Shadow)
  int shadowW = (int)(54.0f * sX);
  int shadowH = (int)(11.5f * sX);
  spr->fillEllipse(cx, cy + 56, shadowW, shadowH, C_CONTACT_SHADOW);
  spr->fillEllipse(cx, cy + 56, (int)(shadowW * 0.65f), (int)(shadowH * 0.6f), 0x0841);

  // 4. LAYER 1: ĐUÔI TIA CHỚP DÀI UỐN LƯỢN SAU LƯNG (Sweeping Lightning Bolt Tail with Phase Lag)
  // Gốc đuôi lông vàng nối từ sườn lưng phải vút sang phải
  spr->fillTriangle(cx + 8, by + 22, cx + 38, by + 12 + tailSwayY, cx + 22, by + 32, C_GOLD_MAIN);
  spr->fillTriangle(cx + 10, by + 24, cx + 40, by + 14 + tailSwayY, cx + 26, by + 34, C_GOLD_SHADOW);
  // Khúc vòm uốn lượn sau lưng
  spr->fillTriangle(cx + 32, by + 12 + tailSwayY, cx + 64 + tailSwayX * 0.5f, by + 8 + tailSwayY, cx + 44, by + 26 + tailSwayY, C_GOLD_MAIN);
  spr->fillTriangle(cx + 42, by + 14 + tailSwayY, cx + 64 + tailSwayX * 0.5f, by + 8 + tailSwayY, cx + 50, by + 20 + tailSwayY, C_CHARCOAL_DARK); // Vệt sấm đen
  // Khúc uốn lượn rẽ xuống phía dưới phải
  spr->fillTriangle(cx + 56 + tailSwayX * 0.5f, by + 10 + tailSwayY, cx + 82 + tailSwayX, by + 22 + tailSwayY, cx + 68 + tailSwayX * 0.7f, by + 28 + tailSwayY, C_GOLD_MAIN);
  // 3 Múi tia chớp nhọn hoắt ở ngọn đuôi
  spr->fillTriangle(cx + 74 + tailSwayX * 0.8f, by + 18 + tailSwayY, cx + 92 + tailSwayX, by + 24 + tailSwayY, cx + 78 + tailSwayX * 0.8f, by + 28 + tailSwayY, C_CYAN_LIGHT);
  spr->fillTriangle(cx + 72 + tailSwayX * 0.7f, by + 26 + tailSwayY, cx + 90 + tailSwayX, by + 36 + tailSwayY, cx + 74 + tailSwayX * 0.8f, by + 38 + tailSwayY, C_CYAN_MAIN);
  spr->fillTriangle(cx + 68 + tailSwayX * 0.6f, by + 34 + tailSwayY, cx + 82 + tailSwayX * 0.9f, by + 50 + tailSwayY, cx + 64 + tailSwayX * 0.6f, by + 42 + tailSwayY, C_CYAN_DEEP);
  spr->drawLine(cx + 70 + tailSwayX * 0.7f, by + 24 + tailSwayY, cx + 88 + tailSwayX, by + 34 + tailSwayY, C_WHITE); // Lõi sáng

  // 5. LAYER 2: BỜM LƯNG & XÙ LÔNG SẤM SÉT SAU VAI (Back Mane Tufts)
  spr->fillTriangle(cx - 20, by + 4, cx - 38, by - 4, cx - 22, by + 16, C_GOLD_SHADOW);
  spr->fillTriangle(cx - 18, by + 2, cx - 36, by - 6, cx - 20, by + 12, C_GOLD_MAIN);
  spr->fillTriangle(cx + 18, by + 2, cx + 38, by - 6, cx + 24, by + 14, C_GOLD_SHADOW);
  spr->fillTriangle(cx + 16, by + 4, cx + 36, by - 4, cx + 22, by + 12, C_GOLD_MAIN);

  // 6. LAYER 3: HAI CHÂN SẤM SÉT & ĐỆM MÓNG VUỐT XANH ĐIỆN (Legs, Paws & Claws)
  // Chân trái (viewer's left)
  spr->fillRoundRect(cx - 27, by + 32, 15, 18, 5, C_CHARCOAL); // Đùi than
  spr->fillEllipse(cx - 20, by + 40, (int)(13 * sX), (int)(10 * sY), C_GOLD_MAIN); // Cổ chân xù lông vàng
  spr->fillTriangle(cx - 24, by + 37, cx - 18, by + 43, cx - 22, by + 45, C_CHARCOAL_DARK); // Vệt sấm đen
  spr->fillRoundRect(cx - 27, by + 48, 14, 8, 3, C_CHARCOAL); // Bàn chân than
  // 3 Móng vuốt bạc
  spr->fillTriangle(cx - 28, by + 53, cx - 31, by + 57, cx - 25, by + 54, C_CLAW);
  spr->fillTriangle(cx - 24, by + 53, cx - 23, by + 58, cx - 20, by + 54, C_CLAW);
  spr->fillTriangle(cx - 19, by + 53, cx - 16, by + 57, cx - 15, by + 54, C_CLAW);
  // Đệm móng vuốt xanh điện
  spr->fillCircle(cx - 21, by + 51, 3, C_PAW_PAD);

  // Chân phải (viewer's right)
  spr->fillRoundRect(cx + 12, by + 32, 15, 18, 5, C_CHARCOAL); // Đùi than
  spr->fillEllipse(cx + 18, by + 40, (int)(13 * sX), (int)(10 * sY), C_GOLD_MAIN); // Cổ chân xù lông vàng
  spr->fillTriangle(cx + 15, by + 37, cx + 21, by + 43, cx + 18, by + 45, C_CHARCOAL_DARK); // Vệt sấm đen
  spr->fillRoundRect(cx + 13, by + 48, 14, 8, 3, C_CHARCOAL); // Bàn chân than
  // 3 Móng vuốt bạc
  spr->fillTriangle(cx + 14, by + 53, cx + 13, by + 57, cx + 17, by + 54, C_CLAW);
  spr->fillTriangle(cx + 19, by + 53, cx + 21, by + 58, cx + 23, by + 54, C_CLAW);
  spr->fillTriangle(cx + 25, by + 53, cx + 28, by + 57, cx + 29, by + 54, C_CLAW);
  // Đệm móng vuốt xanh điện
  spr->fillCircle(cx + 21, by + 51, 3, C_PAW_PAD);

  // 7. LAYER 4: THÂN ĐEN THAN & BỜM NGỰC VỆT SẤM XANH LAM (Torso & Lightning Chest)
  // Thân than tròn trĩnh Pop Mart
  spr->fillEllipse(cx, by + 25, (int)(20 * sX), (int)(17 * sY), C_CHARCOAL);
  spr->fillEllipse(cx - 4, by + 22, (int)(10 * sX), (int)(8 * sY), C_CHARCOAL_LIGHT); // Đón sáng

  // Bờm ngực lông vàng hoàng kim (Chest Mane)
  spr->fillEllipse(cx, by + 10, (int)(26 * sX), (int)(14 * sY), C_GOLD_MAIN);
  spr->fillTriangle(cx - 19, by + 10, cx - 25, by + 22, cx - 8, by + 16, C_GOLD_MAIN);
  spr->fillTriangle(cx + 19, by + 10, cx + 25, by + 22, cx + 8, by + 16, C_GOLD_MAIN);
  spr->fillTriangle(cx - 5, by + 12, cx, by + 24, cx + 5, by + 12, C_GOLD_SHADOW);

  // Vệt sấm xanh lam trước ngực (Electric Cyan Lightning Chest Crest)
  spr->fillTriangle(cx - 9, by + 4, cx, by + 18, cx + 9, by + 4, C_CYAN_DEEP);
  spr->fillTriangle(cx - 7, by + 5, cx, by + 16, cx + 6, by + 5, C_CYAN_MAIN);
  spr->fillTriangle(cx - 4, by + 6, cx, by + 14, cx + 3, by + 6, C_CYAN_LIGHT);
  spr->drawLine(cx - 1, by + 6, cx, by + 14, C_WHITE);

  // 8. LAYER 5: HAI TAY XÙ LÔNG SẤM SÉT & ĐỆM MÓNG VUỐT XANH (Forearms & Claws)
  // Tay trái (viewer's left - duỗi chéo dũng mãnh)
  spr->fillRoundRect(cx - 32, by + 8, 14, 10, 4, C_CHARCOAL); // Khớp vai than
  spr->fillEllipse(cx - 38, by + 20, 13, 16, C_GOLD_MAIN); // Ống lông vàng xù cẳng tay
  spr->fillTriangle(cx - 42, by + 15, cx - 35, by + 21, cx - 41, by + 26, C_CHARCOAL_DARK); // Vệt sấm đen cẳng tay
  spr->fillCircle(cx - 42, by + 31, 9, C_CHARCOAL); // Bàn tay than
  // 3 Móng vuốt bạc
  spr->fillTriangle(cx - 48, by + 35, cx - 52, by + 40, cx - 46, by + 37, C_CLAW);
  spr->fillTriangle(cx - 44, by + 36, cx - 45, by + 42, cx - 41, by + 37, C_CLAW);
  spr->fillTriangle(cx - 39, by + 36, cx - 38, by + 41, cx - 36, by + 37, C_CLAW);
  // Đệm móng vuốt xanh điện phát sáng
  spr->fillCircle(cx - 42, by + 31, 4, C_PAW_PAD);
  spr->drawPixel(cx - 42, by + 31, C_WHITE);

  // Tay phải (viewer's right - duỗi ngang tung đòn sấm sét)
  spr->fillRoundRect(cx + 18, by + 8, 14, 10, 4, C_CHARCOAL); // Vai than
  spr->fillEllipse(cx + 38, by + 4, 18, 12, C_GOLD_MAIN); // Ống lông vàng cẳng tay nằm ngang
  spr->fillTriangle(cx + 31, by, cx + 40, by + 5, cx + 34, by + 10, C_CHARCOAL_DARK); // Vệt sấm đen cẳng tay
  spr->fillCircle(cx + 52, by + 4, 9, C_CHARCOAL); // Bàn tay than
  // 3 Móng vuốt bạc
  spr->fillTriangle(cx + 57, by, cx + 63, by, cx + 58, by + 4, C_CLAW);
  spr->fillTriangle(cx + 57, by + 5, cx + 64, by + 6, cx + 57, by + 9, C_CLAW);
  spr->fillTriangle(cx + 54, by + 10, cx + 60, by + 13, cx + 53, by + 11, C_CLAW);
  // Đệm móng vuốt xanh điện phát sáng
  spr->fillCircle(cx + 52, by + 4, 4, C_PAW_PAD);
  spr->drawPixel(cx + 52, by + 4, C_WHITE);

  // 9. LAYER 6: TAI MÈO NHỌN DỰNG CAO VỚI ĐỆM TAI XANH LAM PLASMA (Cat Ears Background)
  // Tai trái (viewer's left - vểnh cao phía sau)
  spr->fillTriangle(cx - 10, by - 26, cx - 18, by - 66, cx - 2, by - 28, C_GOLD_MAIN);
  spr->drawLine(cx - 10, by - 26, cx - 18, by - 66, C_GOLD_SHADOW);
  spr->fillTriangle(cx - 9, by - 27, cx - 17, by - 58, cx - 4, by - 28, C_CHARCOAL_DARK);
  // Đệm tai xanh lam plasma phát sáng
  spr->fillTriangle(cx - 8, by - 30, cx - 15, by - 52, cx - 5, by - 30, C_CYAN_MAIN);
  spr->drawLine(cx - 7, by - 30, cx - 14, by - 48, C_CYAN_LIGHT);
  // Hạt tia lửa điện plasma lách tách quanh chóp tai trái
  spr->drawPixel(cx - 20 + spark1, by - 68, C_CYAN_LIGHT);
  spr->drawPixel(cx - 22 + spark2, by - 62, C_CYAN_MAIN);

  // Tai phải (viewer's right - vểnh cao phía sau)
  spr->fillTriangle(cx + 4, by - 28, cx + 22, by - 66, cx + 16, by - 26, C_GOLD_MAIN);
  spr->drawLine(cx + 16, by - 26, cx + 22, by - 66, C_GOLD_SHADOW);
  spr->fillTriangle(cx + 6, by - 28, cx + 20, by - 58, cx + 14, by - 27, C_CHARCOAL_DARK);
  // Đệm tai xanh lam plasma phát sáng
  spr->fillTriangle(cx + 8, by - 30, cx + 18, by - 52, cx + 13, by - 30, C_CYAN_MAIN);
  spr->drawLine(cx + 10, by - 30, cx + 17, by - 48, C_CYAN_LIGHT);
  // Hạt tia lửa điện plasma lách tách quanh chóp tai phải
  spr->drawPixel(cx + 24 + spark2, by - 68, C_CYAN_LIGHT);
  spr->drawPixel(cx + 26 + spark1, by - 62, C_CYAN_MAIN);

  // 10. LAYER 7: ĐẦU MÈO, BỘ LÔNG VÀNG BỒNG BỀNH & VỆT SẤM ĐEN MÁ (Head & Fur Mane)
  // Khối đầu tròn trĩnh Pop Mart
  spr->fillEllipse(cx, by - 15, (int)(30 * sX), (int)(24 * sY), C_GOLD_MAIN);
  spr->fillEllipse(cx - 4, by - 24, (int)(14 * sX), (int)(7 * sY), C_GOLD_LIGHT); // Highlight đỉnh đầu

  // Chỏm lông vàng hoàng kim trên đỉnh trán (Golden Forehead Tuft)
  spr->fillTriangle(cx - 4, by - 26, cx, by - 36, cx + 4, by - 26, C_GOLD_MAIN);

  // 3 Múi lông vàng điện chớp flaring hai bên má (Lông vàng hoàng kim bồng bềnh)
  // Má trái - vểnh xuống dưới và sang bên
  spr->fillTriangle(cx - 20, by - 16, cx - 38, by - 14, cx - 22, by - 8, C_GOLD_MAIN);
  spr->fillTriangle(cx - 22, by - 8, cx - 44, by - 2, cx - 20, by + 4, C_GOLD_MAIN);
  spr->fillTriangle(cx - 20, by + 4, cx - 36, by + 14, cx - 14, by + 8, C_GOLD_MAIN);
  spr->drawLine(cx - 22, by - 8, cx - 40, by - 3, C_GOLD_SHADOW);
  // Má phải
  spr->fillTriangle(cx + 20, by - 16, cx + 38, by - 14, cx + 22, by - 8, C_GOLD_MAIN);
  spr->fillTriangle(cx + 22, by - 8, cx + 44, by - 2, cx + 20, by + 4, C_GOLD_MAIN);
  spr->fillTriangle(cx + 20, by + 4, cx + 36, by + 14, cx + 14, by + 8, C_GOLD_MAIN);
  spr->drawLine(cx + 22, by - 8, cx + 40, by - 3, C_GOLD_SHADOW);

  // Mặt nạ than đen bao quanh mắt và mõm
  spr->fillEllipse(cx, by - 12, (int)(21 * sX), (int)(17 * sY), C_CHARCOAL);
  spr->fillTriangle(cx - 10, by - 5, cx, by + 5, cx + 10, by - 5, C_CHARCOAL); // Cằm nhọn nhẹ

  // Vệt sấm đen sắc nét hai bên má và trán (Sharp black thunder streaks)
  // Vệt má trái
  spr->fillTriangle(cx - 16, by - 16, cx - 30, by - 10, cx - 17, by - 6, C_CHARCOAL_DARK);
  // Vệt má phải
  spr->fillTriangle(cx + 16, by - 16, cx + 30, by - 10, cx + 17, by - 6, C_CHARCOAL_DARK);
  // Vệt trán trung tâm
  spr->fillTriangle(cx - 3, by - 28, cx, by - 18, cx + 3, by - 28, C_CHARCOAL_DARK);

  // 11. LAYER 8: MÀO SỪNG TIA CHỚP XANH LAM TRÊN TRÁN & RIA MÉP SẤM (Cyan Lightning Crest - VẼ TRƯỚC TRÁN)
  // Sừng tia chớp xanh lam khổng lồ vút cong ấn tượng trên trán trái
  spr->fillTriangle(cx - 6, by - 18, cx - 28, by - 50, cx - 14, by - 28, C_CYAN_DEEP);
  spr->fillTriangle(cx - 7, by - 19, cx - 26, by - 48, cx - 13, by - 29, C_CYAN_MAIN);
  spr->fillTriangle(cx - 8, by - 21, cx - 24, by - 46, cx - 13, by - 31, C_CYAN_LIGHT);
  spr->drawLine(cx - 8, by - 22, cx - 24, by - 47, C_WHITE); // Lõi sấm trắng

  // Ria mép tia chớp xanh lam bên má trái
  spr->fillTriangle(cx - 17, by - 6, cx - 32, by - 4, cx - 18, by - 1, C_CYAN_MAIN);
  spr->drawLine(cx - 17, by - 6, cx - 31, by - 4, C_CYAN_LIGHT);

  // 12. LAYER 9: ĐÔI MẮT XANH NGỌC LAM CYAN ĐIỆN QUANG TO TRÒN (Giant 3-Point Specular Eyes)
  for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
    int ex = (eyeIdx == 0) ? (cx - 10) : (cx + 10);
    int ey = by - 13;

    if (blink) {
      spr->drawEllipse(ex, ey + 2, 9, 3, C_EYE_LINER);
      spr->drawLine(ex + (eyeIdx == 0 ? -7 : 7), ey + 2, ex + (eyeIdx == 0 ? -12 : 12), ey - 3, C_EYE_LINER); // Khóe vểnh
    } else {
      // Hốc mắt & Viền mí mắt sắc nét với khóe vểnh dũng cảm
      spr->fillEllipse(ex, ey, 9, 13, C_EYE_LINER);
      if (eyeIdx == 0) {
        spr->fillTriangle(ex - 6, ey - 4, ex - 13, ey - 9, ex - 5, ey - 8, C_EYE_LINER); // Khóe vểnh trái
      } else {
        spr->fillTriangle(ex + 6, ey - 4, ex + 13, ey - 9, ex + 5, ey - 8, C_EYE_LINER); // Khóe vểnh phải
      }

      // Tròng mắt sapphire đa tầng điện quang
      spr->fillEllipse(ex, ey, 8, 12, C_EYE_DEEP);
      spr->fillEllipse(ex, ey + 3, 7, 8, C_EYE_BRIGHT);
      spr->fillEllipse(ex, ey + 5, 5, 4, C_EYE_CYAN);

      // 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Specular Highlights)
      // Điểm 1: Primary Specular (To sáng, góc 10h)
      spr->fillEllipse(ex + (eyeIdx == 0 ? 2 : 2), ey - 5, 3, 2, C_WHITE);
      // Điểm 2: Secondary Caustic Bounce (Vừa, góc 4h)
      spr->fillCircle(ex - (eyeIdx == 0 ? 3 : 2), ey + 4, 2, C_WHITE);
      // Điểm 3: Tertiary Micro Glint (Tia sáng vi điểm mép ngoài)
      spr->drawPixel(ex + (eyeIdx == 0 ? 4 : -4), ey + 1, C_WHITE);
    }
  }

  // 13. LAYER 10: MŨI, MIỆNG CƯỜI & RĂNG NANH MÈO SẮC NHỌN (Muzzle, Mouth & Cat Fangs)
  // Mũi nhỏ xíu hình tam giác
  spr->fillTriangle(cx - 3, by - 6, cx + 3, by - 6, cx, by - 4, C_CHARCOAL_DARK);
  // Miệng cười dũng cảm
  spr->fillTriangle(cx - 7, by - 1, cx, by + 6, cx + 7, by - 1, C_MOUTH_DARK);
  spr->fillCircle(cx, by + 4, 3, C_MOUTH_TONGUE);
  // 2 Chiếc răng nanh mèo trắng tinh khôi
  spr->fillTriangle(cx - 6, by - 1, cx - 3, by - 1, cx - 5, by + 2, C_WHITE);
  spr->fillTriangle(cx + 3, by - 1, cx + 6, by - 1, cx + 5, by + 2, C_WHITE);

  // 14. LAYER 11: BỤI TIA LỬA ĐIỆN PLASMA XANH LAM LÁCH TÁCH (Floating Plasma Sparks)
  // Tia lửa đuôi
  spr->fillCircle(cx + 88 + tailSwayX + spark1, by + 30 + tailSwayY, 2, C_CYAN_LIGHT);
  spr->drawPixel(cx + 88 + tailSwayX + spark1, by + 30 + tailSwayY, C_WHITE);
  // Tia lửa sườn trái
  spr->fillCircle(cx - 48 + spark2, by - 16 + spark1, 2, C_CYAN_MAIN);
  spr->drawPixel(cx - 48 + spark2, by - 16 + spark1, C_WHITE);
  // Tia lửa trên đỉnh sừng
  spr->fillCircle(cx - 28 + spark1, by - 52 + spark3, 2, C_CYAN_LIGHT);
  spr->drawPixel(cx - 28 + spark1, by - 52 + spark3, C_WHITE);
}


} // namespace ZeraoraThunderclap
