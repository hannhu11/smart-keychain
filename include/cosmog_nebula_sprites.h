#pragma once
// ============================================================================
// 09_MYTHIC_COSMOG_NEBULA_BABY - PRODUCTION C++ HEADER
// Hardware Target: ESP32 / ESP32-S3 + ST7789 IPS Display (172x320 / 240x280 60FPS DMA)
// Stylistic Origin: 3D Pop Mart Vinyl & Mythic Space Deity Pokémon
// Conformance: 3-Point Specular Amber Crystal Eyes, 5% Squash & Stretch, 80ms Lag Twin Tufts
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace CosmogNebula {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// =========================================================================
// 09_MYTHIC_COSMOG_NEBULA_BABY - ScaledCanvas C++ Implementation
// 100% Hardware Compatible with ESP32/ESP32-S3 + ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl High-End 3D Sculpt: Nebula Cloud, Golden Ring, Crystal Amber Eyes
// Organic Micro-Physics: 5% Squash & Stretch, 80ms Lag Puffs, Orbiting Stars
// =========================================================================
void drawCosmogNebulaBaby(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // -----------------------------------------------------------------------
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ KHÔNG TRỌNG LỰC (ORGANIC ZERO-G PHYSICS)
  // -----------------------------------------------------------------------
  float breathFreq  = 2.0f;
  float breathPhase = angle * breathFreq;
  float breathSin   = sinf(breathPhase);

  // Nhịp bồng bềnh lơ lửng không trọng lực (Hovering Float Offset)
  int hoverOffsetY = (int)(breathSin * 3.8f);
  int by = cy + hoverOffsetY;

  // Squash & Stretch đàn hồi 5% (Bảo toàn thể tích thực tế: Sx^2 * Sy ≈ 1.0)
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;

  // Trễ pha động học 80ms của hai búi mây tinh vân trên đỉnh (Delta Phi = 0.25 rad)
  float lagTuftL = breathPhase - 0.25f;
  float lagTuftR = breathPhase - 0.25f + 0.12f;
  int tuftSwayLX = (int)(sinf(lagTuftL) * 3.0f);
  int tuftSwayLY = (int)(cosf(lagTuftL) * 2.0f);
  int tuftSwayRX = (int)(sinf(lagTuftR) * 3.0f);
  int tuftSwayRY = (int)(cosf(lagTuftR) * 2.0f);

  // -----------------------------------------------------------------------
  // 2. BẢNG MÀU 16-BIT RGB565 CHUẨN XÁC POP MART VINYL VŨ TRỤ
  // -----------------------------------------------------------------------
  const uint16_t C_NEB_CORE_INDIGO  = 0x1887; // #1A103C Lõi chàm tím sâu thẳm
  const uint16_t C_NEB_DARK_PURPLE  = 0x2889; // #2E124D Tím đậm chuyển tiếp
  const uint16_t C_NEB_VIOLET       = 0x48B1; // #4A148C Tím tử la tinh vân
  const uint16_t C_NEB_MAGENTA      = 0x78F4; // #7B1FA2 Tím hồng phát quang
  const uint16_t C_NEB_PINK_GLOW    = 0xD8CC; // #D81B60 Hồng sen rực rỡ đáy
  const uint16_t C_NEB_BRIGHT_PINK  = 0xE8EC; // #E91E63 Hồng magenta đón sáng
  const uint16_t C_NEB_DEEP_BLUE    = 0x0A54; // #0D47A1 Lam thẫm cuống mây
  const uint16_t C_NEB_SKY_BLUE     = 0x045A; // #0288D1 Sắc lam thanh khiết
  const uint16_t C_NEB_ELEC_CYAN    = 0x073F; // #00E5FF Xanh lơ cyan điện tử
  const uint16_t C_NEB_CYAN_GLOW    = 0x86DF; // #80D8FF Quầng sáng lam dịu
  const uint16_t C_NEB_PALE_CYAN    = 0xE7BF; // #E0F7FA Đỉnh đón sáng trắng lam

  const uint16_t C_GOLD_FRESNEL     = 0xFFFC; // #FFFDE7 Viền Fresnel đĩa vàng
  const uint16_t C_GOLD_HIGHLIGHT   = 0xFFB3; // #FFF59D Mặt đón sáng vàng
  const uint16_t C_GOLD_LIGHT       = 0xFF8E; // #FFF176 Vàng chanh thanh tao
  const uint16_t C_GOLD_MAIN        = 0xFF6B; // #FFEE58 Vàng hoàng kim vương giả
  const uint16_t C_GOLD_WARM        = 0xFEC6; // #FDD835 Vàng hổ phách tạo khối
  const uint16_t C_GOLD_SHADOW      = 0xF3E2; // #F57F17 Bóng đổ nâu vàng
  const uint16_t C_GOLD_RIM_DARK    = 0x9CE4; // #9E9D24 Viền sắc sảo đĩa khuyết

  const uint16_t C_FACE_BLACK       = 0x10A3; // #14171A Mặt nạ đen nhung
  const uint16_t C_FACE_CHARCOAL    = 0x1905; // #1E2328 Khối than chì
  const uint16_t C_FACE_RIM         = 0x320A; // #334155 Viền lụa mỏng

  const uint16_t C_EYE_GLOW         = 0xFFD8; // #FFF9C4 Vệt tụ quang đáy mắt
  const uint16_t C_EYE_BRIGHT       = 0xFF8E; // #FFF176 Lõi tròng mắt sáng
  const uint16_t C_EYE_MAIN         = 0xFE45; // #FFCA28 Vàng mật ong hổ phách
  const uint16_t C_EYE_SHADOW       = 0xF3E2; // #F57F17 Viền đổ bóng hổ phách

  const uint16_t C_CHEEK_CYAN       = 0x073F; // #00E5FF Má ngọc lam phát quang
  const uint16_t C_CHEEK_CORE       = 0x059F; // #00B0FF Tâm má xanh da trời
  const uint16_t C_BLUSH_PINK       = 0xF396; // #F472B6 Má hồng phấn bẽn lẽn

  const uint16_t C_MOUTH_PINK       = 0xFA10; // #FF4081 Khoang miệng hồng
  const uint16_t C_MOUTH_TONGUE     = 0xFC15; // #FF80AB Lưỡi nhỏ xíu
  const uint16_t C_MOUTH_RIM        = 0x0882; // #0F1114 Viền miệng đen

  const uint16_t C_WHITE_SPARKLE    = 0xFFFF; // #FFFFFF Bắt sáng pha lê 3 điểm
  const uint16_t C_STARDUST_GOLD    = 0xFF10; // #FFE082 Bụi sao vàng hoàng kim
  const uint16_t C_STARDUST_CYAN    = 0x463F; // #40C4FF Bụi sao xanh ngọc
  const uint16_t C_ASTRAL_HALO      = 0x38CA; // #3B1A54 Vầng hào quang đáy

  // -----------------------------------------------------------------------
  // 3. LAYER 0: VẦNG HÀO QUANG MỜ ẢO ĐÁY THAY CHO BÓNG SÀN (ASTRAL NEBULA HALO)
  // -----------------------------------------------------------------------
  int haloY = cy + 42;
  int haloRx = (int)((32.0f - hoverOffsetY * 1.2f) * sX);
  int haloRy = (int)(9.0f - hoverOffsetY * 0.35f);
  if (haloRx < 18) haloRx = 18;
  if (haloRy < 4)  haloRy = 4;
  spr->fillEllipse(cx, haloY, haloRx + 4, haloRy + 2, C_NEB_CORE_INDIGO);
  spr->fillEllipse(cx, haloY, haloRx, haloRy, C_ASTRAL_HALO);
  spr->fillEllipse(cx, haloY - 1, (int)(haloRx * 0.65f), (int)(haloRy * 0.6f), C_NEB_MAGENTA);

  // -----------------------------------------------------------------------
  // 4. LAYER 1: ĐĨA VÀNG KHUYẾT PHÍA SAU (REAR GOLDEN CRESCENT DISC & BAND)
  // -----------------------------------------------------------------------
  // Sừng trên đĩa vàng khuyết vươn cao góc 1h (Top Horn)
  int hornTopX = cx + 16;
  int hornTopY = by - 38;
  spr->fillTriangle(cx + 4, by - 12, hornTopX, hornTopY, cx + 18, by - 22, C_GOLD_SHADOW);
  spr->fillTriangle(cx + 6, by - 14, hornTopX, hornTopY, cx + 16, by - 24, C_GOLD_MAIN);
  spr->fillTriangle(cx + 8, by - 16, hornTopX, hornTopY, cx + 14, by - 26, C_GOLD_HIGHLIGHT);
  spr->drawLine(cx + 5, by - 13, hornTopX, hornTopY, C_GOLD_FRESNEL);
  spr->drawLine(cx + 18, by - 22, hornTopX, hornTopY, C_GOLD_RIM_DARK);

  // Sừng dưới đĩa vàng khuyết chúc xuống góc 7h (Bottom Horn)
  int hornBotX = cx - 14;
  int hornBotY = by + 46;
  spr->fillTriangle(cx - 4, by + 18, hornBotX, hornBotY, cx - 16, by + 30, C_GOLD_SHADOW);
  spr->fillTriangle(cx - 3, by + 20, hornBotX, hornBotY, cx - 14, by + 32, C_GOLD_MAIN);
  spr->fillTriangle(cx - 2, by + 22, hornBotX, hornBotY, cx - 12, by + 34, C_GOLD_HIGHLIGHT);
  spr->drawLine(cx - 16, by + 30, hornBotX, hornBotY, C_GOLD_FRESNEL);
  spr->drawLine(cx - 4, by + 18, hornBotX, hornBotY, C_GOLD_RIM_DARK);

  // -----------------------------------------------------------------------
  // 5. LAYER 2: KHỐI ĐÁM MÂY TINH VÂN VŨ TRỤ (MAIN NEBULA CLOUD BODY LOBES)
  // -----------------------------------------------------------------------
  // Chuyển sắc từ chàm tím vi lượng ở đỉnh sang hồng cánh sen rực rỡ ở đáy
  // 5.1 Các thùy mây đáy dưới (Hồng cánh sen & Magenta dạ quang)
  spr->fillEllipse(cx, by + 24, (int)(18 * sX), (int)(14 * sY), C_NEB_PINK_GLOW);
  spr->fillEllipse(cx - 15, by + 20, (int)(14 * sX), (int)(12 * sY), C_NEB_BRIGHT_PINK);
  spr->fillEllipse(cx + 15, by + 18, (int)(14 * sX), (int)(12 * sY), C_NEB_MAGENTA);
  spr->fillCircle(cx - 8, by + 26, (int)(9 * sX), C_NEB_PINK_GLOW);
  spr->fillCircle(cx + 8, by + 25, (int)(9 * sX), C_NEB_BRIGHT_PINK);

  // 5.2 Các thùy mây sườn giữa (Tím tử la & Chàm tím vũ trụ)
  spr->fillEllipse(cx - 24, by + 4, (int)(15 * sX), (int)(13 * sY), C_NEB_VIOLET);
  spr->fillEllipse(cx + 25, by + 4, (int)(15 * sX), (int)(13 * sY), C_NEB_VIOLET);
  spr->fillEllipse(cx - 22, by + 2, (int)(12 * sX), (int)(10 * sY), C_NEB_DARK_PURPLE);
  spr->fillEllipse(cx + 22, by + 2, (int)(12 * sX), (int)(10 * sY), C_NEB_DARK_PURPLE);

  // 5.3 Thùy mây đỉnh & lõi trung tâm (Chàm tím đậm & Lam vũ trụ)
  spr->fillEllipse(cx, by - 14, (int)(18 * sX), (int)(13 * sY), C_NEB_CORE_INDIGO);
  spr->fillEllipse(cx - 16, by - 12, (int)(13 * sX), (int)(11 * sY), C_NEB_DARK_PURPLE);
  spr->fillEllipse(cx + 16, by - 12, (int)(13 * sX), (int)(11 * sY), C_NEB_DARK_PURPLE);
  spr->fillCircle(cx, by + 2, (int)(19 * sX), C_NEB_CORE_INDIGO);

  // -----------------------------------------------------------------------
  // 6. LAYER 3: HAI BÚI MÂY TINH VÂN XANH LAM TRÊN ĐỈNH (TWIN NEBULA TUFTS)
  // -----------------------------------------------------------------------
  // 6.1 Cuống mây trái uốn lượn vươn lên
  int stemLX1 = cx - 12, stemLY1 = by - 14;
  int stemLX2 = cx - 24 + (int)(tuftSwayLX * 0.5f), stemLY2 = by - 28;
  int stemLX3 = cx - 36 + tuftSwayLX, stemLY3 = by - 42 + tuftSwayLY;
  spr->fillTriangle(stemLX1 - 4, stemLY1, stemLX2, stemLY2, stemLX1 + 4, stemLY1, C_NEB_DEEP_BLUE);
  spr->fillTriangle(stemLX2 - 4, stemLY2, stemLX3, stemLY3, stemLX2 + 4, stemLY2, C_NEB_SKY_BLUE);

  // Búi mây tinh vân trái (Cyan & Electric Blue Cloud Puff)
  int puffLX = stemLX3 - 6;
  int puffLY = stemLY3 - 10;
  spr->fillCircle(puffLX, puffLY, (int)(13 * sX), C_NEB_SKY_BLUE);
  spr->fillCircle(puffLX + 3, puffLY - 8, (int)(10 * sX), C_NEB_ELEC_CYAN);
  spr->fillCircle(puffLX - 9, puffLY + 1, (int)(9 * sX), C_NEB_CYAN_GLOW);
  spr->fillCircle(puffLX + 9, puffLY - 2, (int)(9 * sX), C_NEB_ELEC_CYAN);
  spr->fillCircle(puffLX - 5, puffLY + 8, (int)(8 * sX), C_NEB_SKY_BLUE);
  spr->fillCircle(puffLX + 1, puffLY - 3, (int)(8 * sX), C_NEB_PALE_CYAN);

  // 6.2 Cuống mây phải uốn lượn vươn lên
  int stemRX1 = cx + 12, stemRY1 = by - 14;
  int stemRX2 = cx + 24 + (int)(tuftSwayRX * 0.5f), stemRY2 = by - 28;
  int stemRX3 = cx + 38 + tuftSwayRX, stemRY3 = by - 38 + tuftSwayRY;
  spr->fillTriangle(stemRX1 - 4, stemRY1, stemRX2, stemRY2, stemRX1 + 4, stemRY1, C_NEB_DEEP_BLUE);
  spr->fillTriangle(stemRX2 - 4, stemRY2, stemRX3, stemRY3, stemRX2 + 4, stemRY2, C_NEB_SKY_BLUE);

  // Búi mây tinh vân phải (Cyan & Electric Blue Cloud Puff)
  int puffRX = stemRX3 + 4;
  int puffRY = stemRY3 - 10;
  spr->fillCircle(puffRX, puffRY, (int)(13 * sX), C_NEB_SKY_BLUE);
  spr->fillCircle(puffRX + 2, puffRY - 8, (int)(10 * sX), C_NEB_ELEC_CYAN);
  spr->fillCircle(puffRX + 8, puffRY + 2, (int)(9 * sX), C_NEB_CYAN_GLOW);
  spr->fillCircle(puffRX - 8, puffRY - 2, (int)(9 * sX), C_NEB_ELEC_CYAN);
  spr->fillCircle(puffRX + 4, puffRY + 8, (int)(8 * sX), C_NEB_SKY_BLUE);
  spr->fillCircle(puffRX - 1, puffRY - 3, (int)(8 * sX), C_NEB_PALE_CYAN);

  // 6.3 Hạt sương tinh vân tách rời trôi nổi (Drifting Astral Droplets)
  spr->fillCircle(puffLX - 18, puffLY - 8, 3, C_NEB_SKY_BLUE);
  spr->drawPixel(puffLX - 18, puffLY - 9, C_NEB_PALE_CYAN);
  spr->fillCircle(puffLX - 8, puffLY + 18, 2, C_NEB_ELEC_CYAN);

  spr->fillCircle(puffRX + 18, puffRY - 4, 3, C_NEB_SKY_BLUE);
  spr->drawPixel(puffRX + 18, puffRY - 5, C_NEB_PALE_CYAN);
  spr->fillCircle(puffRX + 12, puffRY + 16, 2, C_NEB_ELEC_CYAN);

  // -----------------------------------------------------------------------
  // 7. LAYER 4: BỤI SAO KIM CƯƠNG PHÁT QUANG CHÌM DƯỚI ĐÁM MÂY (DIAMOND DUST)
  // -----------------------------------------------------------------------
  // Búi mây trái: Sao kim cương lớn 4 cánh
  spr->drawFastHLine(puffLX - 3, puffLY - 4, 7, C_WHITE_SPARKLE);
  spr->drawFastVLine(puffLX, puffLY - 7, 7, C_WHITE_SPARKLE);
  spr->drawPixel(puffLX, puffLY - 4, C_WHITE_SPARKLE);
  spr->drawPixel(puffLX + 5, puffLY - 10, C_NEB_PALE_CYAN);
  spr->drawPixel(puffLX - 6, puffLY - 2, C_WHITE_SPARKLE);
  spr->drawPixel(puffLX + 6, puffLY + 4, C_NEB_CYAN_GLOW);

  // Búi mây phải: Sao kim cương lớn 4 cánh
  spr->drawFastHLine(puffRX - 1, puffRY - 5, 7, C_WHITE_SPARKLE);
  spr->drawFastVLine(puffRX + 2, puffRY - 8, 7, C_WHITE_SPARKLE);
  spr->drawPixel(puffRX + 2, puffRY - 5, C_WHITE_SPARKLE);
  spr->drawPixel(puffRX - 5, puffRY - 10, C_NEB_PALE_CYAN);
  spr->drawPixel(puffRX + 7, puffRY - 1, C_WHITE_SPARKLE);
  spr->drawPixel(puffRX - 5, puffRY + 3, C_NEB_CYAN_GLOW);

  // Bụi sao chìm trong thân tinh vân
  spr->drawPixel(cx - 12, by + 16, C_STARDUST_GOLD);
  spr->drawPixel(cx + 14, by + 14, C_STARDUST_CYAN);
  spr->drawPixel(cx, by + 26, C_WHITE_SPARKLE);
  spr->drawPixel(cx - 20, by + 8, C_STARDUST_CYAN);
  spr->drawPixel(cx + 18, by + 6, C_STARDUST_GOLD);

  // -----------------------------------------------------------------------
  // 8. LAYER 5: VÒNG ĐAI HOÀNG KIM ÔM PHÍA TRƯỚC (FRONT GOLDEN CRESCENT ARC)
  // -----------------------------------------------------------------------
  // Cung khuyết vàng bao quanh eo và nâng đỡ đám mây
  spr->drawEllipse(cx, by + 6, (int)(26 * sX), (int)(15 * sY), C_GOLD_SHADOW);
  spr->drawEllipse(cx, by + 5, (int)(25 * sX), (int)(14 * sY), C_GOLD_MAIN);
  spr->drawEllipse(cx - 1, by + 4, (int)(24 * sX), (int)(13 * sY), C_GOLD_LIGHT);
  spr->drawPixel(cx - 24, by + 6, C_GOLD_FRESNEL);
  spr->drawPixel(cx + 24, by + 6, C_GOLD_FRESNEL);

  // -----------------------------------------------------------------------
  // 9. LAYER 6: MẶT NẠ ĐÁM MÂY ĐEN TUYỀN (SCALLOPED CHARCOAL FACE MASK)
  // -----------------------------------------------------------------------
  // Tạo hình đám mây 5 thùy sắc nét màu đen nhung Pop Mart
  spr->fillCircle(cx, by - 6, (int)(10 * sX), C_FACE_BLACK);       // Thùy trên
  spr->fillCircle(cx - 10, by - 2, (int)(9 * sX), C_FACE_BLACK);    // Thùy trên trái
  spr->fillCircle(cx + 10, by - 2, (int)(9 * sX), C_FACE_BLACK);    // Thùy trên phải
  spr->fillCircle(cx - 7, by + 8, (int)(10 * sX), C_FACE_BLACK);    // Thùy dưới trái
  spr->fillCircle(cx + 7, by + 8, (int)(10 * sX), C_FACE_BLACK);    // Thùy dưới phải
  spr->fillCircle(cx, by + 1, (int)(12 * sX), C_FACE_BLACK);        // Lõi trung tâm

  // Đổ bóng than chì và vệt sáng 3D nhẹ
  spr->fillCircle(cx - 2, by - 4, (int)(7 * sX), C_FACE_CHARCOAL);
  spr->drawPixel(cx - 6, by - 8, C_FACE_RIM);
  spr->drawPixel(cx + 6, by - 8, C_FACE_RIM);

  // -----------------------------------------------------------------------
  // 10. LAYER 7: ĐÔI MÁ NGỌC LAM & MÁ HỒNG PHẤN BẼN LẼN (CHEEK BLUSHES)
  // -----------------------------------------------------------------------
  int cheekYL = by + 4;
  int cheekYR = by + 4;
  int cheekXL = cx - 13;
  int cheekXR = cx + 13;

  // Má hồng phấn bẽn lẽn phớt nhẹ quanh viền
  spr->fillCircle(cheekXL, cheekYL, 5, C_BLUSH_PINK);
  spr->fillCircle(cheekXR, cheekYR, 5, C_BLUSH_PINK);

  // Đốm má xanh lơ ngọc bích phát quang đặc trưng Cosmog
  spr->fillCircle(cheekXL, cheekYL, 4, C_CHEEK_CYAN);
  spr->fillCircle(cheekXL, cheekYL, 2, C_CHEEK_CORE);
  spr->drawPixel(cheekXL - 1, cheekYL - 1, C_WHITE_SPARKLE);

  spr->fillCircle(cheekXR, cheekYR, 4, C_CHEEK_CYAN);
  spr->fillCircle(cheekXR, cheekYR, 2, C_CHEEK_CORE);
  spr->drawPixel(cheekXR - 1, cheekYR - 1, C_WHITE_SPARKLE);

  // -----------------------------------------------------------------------
  // 11. LAYER 8: MIỆNG NHỎ XINH HÉ MỞ (CUTE OPEN MOUTH)
  // -----------------------------------------------------------------------
  int mouthY = by + 7;
  spr->fillCircle(cx, mouthY, 3, C_MOUTH_RIM);
  spr->fillCircle(cx, mouthY, 2, C_MOUTH_PINK);
  spr->drawPixel(cx, mouthY + 1, C_MOUTH_TONGUE);
  spr->drawPixel(cx, mouthY - 1, C_WHITE_SPARKLE);

  // -----------------------------------------------------------------------
  // 12. LAYER 9: ĐÔI MẮT HỔ PHÁCH VÀNG TO TRÒN TRONG VEO (CRYSTAL AMBER EYES)
  // -----------------------------------------------------------------------
  int eyeY  = by;
  int eyeXL = cx - 6;
  int eyeXR = cx + 6;

  if (blink) {
    // Nhịp chớp mắt 3.5s thành hình cung cười hạnh phúc hổ phách
    for (int eIdx = 0; eIdx < 2; eIdx++) {
      int ex = (eIdx == 0) ? eyeXL : eyeXR;
      spr->drawEllipse(ex, eyeY + 2, 4, 2, C_EYE_SHADOW);
      spr->drawEllipse(ex, eyeY + 1, 4, 1, C_EYE_MAIN);
      spr->drawPixel(ex - 3, eyeY, C_EYE_MAIN);
      spr->drawPixel(ex + 3, eyeY, C_EYE_MAIN);
    }
  } else {
    for (int eIdx = 0; eIdx < 2; eIdx++) {
      int ex = (eIdx == 0) ? eyeXL : eyeXR;
      // Tròng mắt bầu dục đứng vàng hổ phách
      spr->fillEllipse(ex, eyeY, 4, 6, C_EYE_SHADOW);
      spr->fillEllipse(ex, eyeY, 3, 5, C_EYE_MAIN);
      spr->fillEllipse(ex, eyeY - 1, 2, 3, C_EYE_BRIGHT);
      spr->fillCircle(ex, eyeY + 2, 2, C_EYE_GLOW);

      // 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Specular System)
      // Điểm 1: Direct keylight lớn góc 10h (2x2 pixel)
      spr->fillRect(ex - 2, eyeY - 3, 2, 2, C_WHITE_SPARKLE);
      // Điểm 2: Caustic ground bounce góc 4h (1x1 pixel)
      spr->drawPixel(ex + 1, eyeY + 2, C_GOLD_HIGHLIGHT);
      // Điểm 3: Surface wetness glint góc 1h (1x1 pixel)
      spr->drawPixel(ex + 1, eyeY - 2, C_WHITE_SPARKLE);
    }
  }

  // -----------------------------------------------------------------------
  // 13. LAYER 10: TINH TÚ NGÂN HÀ LẤP LÁNH XOAY TRÒN (ORBITING STARDUST)
  // -----------------------------------------------------------------------
  // Các hạt bụi sao xoay quanh vòng đai vàng theo quỹ đạo elip nghiêng
  float orbitT = angle * 3.2f;
  for (int p = 0; p < 4; p++) {
    float pPhase = orbitT + p * (6.283185f / 4.0f);
    float ox = cosf(pPhase) * (28.0f * sX);
    float oy = sinf(pPhase) * (14.0f * sY);
    // Xoay nghiêng theo góc vòng đai ~ -35 độ
    int px = cx + (int)(ox * 0.82f - oy * 0.57f);
    int py = (by + 4) + (int)(ox * 0.57f + oy * 0.82f);

    uint16_t pCol = (p % 2 == 0) ? C_STARDUST_GOLD : C_STARDUST_CYAN;
    if (p == 0) pCol = C_WHITE_SPARKLE;

    spr->drawPixel(px, py, pCol);
    if (p % 2 == 0) {
      spr->drawPixel(px - 1, py, C_GOLD_HIGHLIGHT);
      spr->drawPixel(px + 1, py, C_GOLD_HIGHLIGHT);
    }
  }
}

} // namespace CosmogNebula
