#pragma once
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace SpriteRenderer {

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
      spr->fillCircle(ex - 2, ey - 3, 2, C_WHITE);
      spr->fillCircle(ex + 2, ey + 3, 1, C_WHITE);
      spr->drawPixel(ex + 2, ey - 2, C_WHITE);
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

} // namespace SpriteRenderer
