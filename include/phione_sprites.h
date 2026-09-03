#pragma once
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace SpriteRenderer {

// =========================================================================
// PHIONE - GIỌT NƯỚC BIỂN TRÔI DẠT (MYTHIC PHIONE SEA DRIFTER)
// Pop Mart / High-End Vinyl Collectible Art - 100% Hardware Compatible ST7789
// Target: ST7789 IPS 172x320 / 240x280 (16-bit RGB565)
// =========================================================================

static void drawPhioneSeaDrifter(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // 1. Nhịp bơi lơ lửng đại dương Squash & Stretch 5% bảo toàn thể tích
  float breathPhase = angle * 2.0f;
  float sY = 1.0f + 0.05f * sinf(breathPhase);
  float sX = 1.0f - 0.025f * sinf(breathPhase); // Area conservation: sY * (sX^2) ≈ 1.0
  int by = cy + (int)(sinf(breathPhase) * 3.5f); // Dao động lơ lửng Y-bobbing

  // 2. Bảng màu 16-bit RGB565 chuẩn xác
  const uint16_t C_FRESNEL_RIM   = 0xCFDE; // #CCFBF1 Viền men sứ xanh ngọc băng lóa sáng
  const uint16_t C_BODY_CYAN     = 0x269D; // #22D3EE Thân ngọc lam đại dương bán trong suốt
  const uint16_t C_BODY_LIGHT    = 0x675F; // #67E8F9 Vùng phản quang sáng khoang thể dịch
  const uint16_t C_BODY_CORE_SSS = 0x0438; // #0284C7 Lõi tán xạ ánh sáng dưới bề mặt SSS
  const uint16_t C_DEEP_CYAN     = 0x0BB2; // #0E7490 Vùng đổ bóng khuất và nếp gấp
  const uint16_t C_BUOY_LIGHT    = 0xBF3F; // #BAE6FD Men bóng đón sáng phao đỉnh đầu
  const uint16_t C_RUBY_DEEP     = 0x98C3; // #991B1B Đáy bóng tối hồng ngọc Ruby
  const uint16_t C_RUBY_CORE     = 0xD924; // #DC2626 Lõi đỏ rực hồng ngọc trái tim đại dương
  const uint16_t C_RUBY_BRIGHT   = 0xEA28; // #EF4444 Cạnh vát lóa sáng giác cắt ruby
  const uint16_t C_GOLD_BEZEL    = 0xF4E1; // #F59E0B Viền vàng hoàng kim đính ngọc
  const uint16_t C_GOLD_BRIGHT   = 0xFF91; // #FEF08A Điểm tâm sáng hoàng kim lấp lánh
  const uint16_t C_GOLD_EYELID   = 0xFE62; // #FACC15 Vệt vàng mí mắt trên
  const uint16_t C_EYE_DARK      = 0x0129; // #03254C Hốc mắt vực thẳm đại dương sâu thẳm
  const uint16_t C_EYE_IRIS_BLUE = 0x1A7B; // #1D4ED8 Thể thủy tinh Sapphire mắt xanh
  const uint16_t C_EYE_IRIS_AQUA = 0x3DFF; // #38BDF8 Khúc xạ đáy mắt màu lam ngọc
  const uint16_t C_BLUSH_PINK    = 0xFB90; // #FB7185 Đôi má hồng san hô nước biển
  const uint16_t C_MOUTH_DEEP    = 0x09F7; // #0A5B80 Nụ cười ngọt ngào đại dương
  const uint16_t C_MARKING_BLUE  = 0x0438; // #0284C7 Đốm tròn anten trán
  const uint16_t C_BUBBLE_GLOW   = 0x7E9F; // #7DD3FC Bọt nước ngân hà li ti phát sáng
  const uint16_t C_SEABED_SHADOW = 0x00E6; // #041E34 Bóng tiếp xúc mờ ảo đáy biển
  const uint16_t C_WHITE         = 0xFFFF; // #FFFFFF Điểm bắt sáng kim cương men sứ

  // 3. BÓNG TIẾP XÚC MỜ ẢO ĐÁY BIỂN (Soft Contact Shadow)
  int shadowRx = (int)((24.0f + 2.0f * sinf(breathPhase)) * sX);
  int shadowRy = 5;
  int shadowY  = cy + 38;
  spr->fillEllipse(cx - 2, shadowY, shadowRx + 4, shadowRy + 1, C_SEABED_SHADOW);
  spr->fillEllipse(cx - 2, shadowY, shadowRx, shadowRy, C_SEABED_SHADOW);

  // 4. BỌT NƯỚC NGÂN HÀ LI TI PHÁT SÁNG BỒNG BỀNH XUNG QUANH (Bioluminescent Galaxy Bubbles)
  const int bubbleOffsets[6][2] = {
    {-42, -26}, {38, -20}, {-46, 12}, {44, 18}, {-20, -46}, {26, -50}
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

  // Tọa độ đầu & phao
  int hy = by - 7;
  int buoyX = cx - (int)(4 * sX);
  int buoyY = hy - (int)(18 * sY);

  // 5. DẢI RUY BĂNG ĐUÔI DÀI RỦ XUỐNG TỪ PHAO ĐẦU (Trễ pha Delta Phi = 0.45 rad)
  // Uốn lượn hình sóng biển S-Curve mềm mại
  float ribLag = breathPhase - 0.45f;
  float sway1 = sinf(ribLag) * 4.0f;
  float sway2 = cosf(ribLag) * 5.0f;
  float sway3 = sinf(ribLag + 0.5f) * 6.0f;
  float sway4 = cosf(ribLag + 0.8f) * 7.0f;

  // 6 mốc spline trên thân ruy băng
  int rx0 = buoyX, ry0 = buoyY - 2;
  int rx1 = buoyX + 8 + (int)(sway1 * 0.4f), ry1 = buoyY - 14;
  int rx2 = buoyX + 22 + (int)(sway2 * 0.6f), ry2 = buoyY - 12;
  int rx3 = buoyX + 42 + (int)(sway3 * 0.8f), ry3 = buoyY + 6;
  int rx4 = buoyX + 62 + (int)(sway4), ry4 = buoyY + 30;
  int rx5 = buoyX + 78 + (int)(sway4 * 1.2f), ry5 = buoyY + 50;

  // Vẽ các đoạn thân ruy băng với độ dày nở dần
  spr->drawLine(rx0, ry0, rx1, ry1, C_BODY_CYAN);
  spr->drawLine(rx0 + 1, ry0, rx1 + 1, ry1, C_FRESNEL_RIM);
  spr->drawLine(rx1, ry1, rx2, ry2, C_BODY_CYAN);
  spr->drawLine(rx1, ry1 - 1, rx2, ry2 - 1, C_FRESNEL_RIM);

  spr->fillTriangle(rx1, ry1, rx2, ry2, rx2, ry2 + 5, C_BODY_CORE_SSS);
  spr->fillTriangle(rx2, ry2, rx3, ry3, rx2, ry2 + 6, C_BODY_CYAN);
  spr->fillTriangle(rx2, ry2 + 6, rx3, ry3, rx3, ry3 + 7, C_BODY_CORE_SSS);
  spr->fillTriangle(rx3, ry3, rx4, ry4, rx3, ry3 + 7, C_BODY_CYAN);
  spr->fillTriangle(rx3, ry3 + 7, rx4, ry4, rx4, ry4 + 8, C_BODY_CORE_SSS);
  spr->fillTriangle(rx4, ry4, rx5, ry5, rx4, ry4 + 8, C_BODY_CYAN);
  spr->fillTriangle(rx4, ry4 + 8, rx5, ry5, rx5, ry5 + 9, C_BODY_LIGHT);

  // Viền men sứ lóa sáng dọc lưng ruy băng
  spr->drawLine(rx0, ry0 - 1, rx1, ry1 - 1, C_FRESNEL_RIM);
  spr->drawLine(rx1, ry1 - 1, rx2, ry2 - 1, C_FRESNEL_RIM);
  spr->drawLine(rx2, ry2 - 1, rx3, ry3 - 1, C_FRESNEL_RIM);
  spr->drawLine(rx3, ry3 - 1, rx4, ry4 - 1, C_FRESNEL_RIM);
  spr->drawLine(rx4, ry4 - 1, rx5, ry5 - 1, C_FRESNEL_RIM);

  // Chóp đuôi chẻ 2 thùy đuôi cá V-notch
  int tipX = rx5, tipY = ry5;
  spr->fillTriangle(tipX - 2, tipY - 3, tipX + 8, tipY - 2, tipX + 3, tipY + 2, C_BODY_LIGHT);
  spr->fillTriangle(tipX - 2, tipY + 7, tipX + 8, tipY + 8, tipX + 3, tipY + 2, C_BODY_LIGHT);
  spr->drawLine(tipX - 2, tipY - 3, tipX + 8, tipY - 2, C_FRESNEL_RIM);
  spr->drawLine(tipX + 8, tipY - 2, tipX + 3, tipY + 2, C_FRESNEL_RIM);
  spr->drawLine(tipX + 3, tipY + 2, tipX + 8, tipY + 8, C_FRESNEL_RIM);
  spr->drawLine(tipX + 8, tipY + 8, tipX - 2, tipY + 7, C_DEEP_CYAN);

  // 6. HAI TAY BƠI NGẮN TRÒN XÒE NGANG (Swimming Paddle Flippers)
  float finLag = breathPhase - 0.35f;
  int finFlutterL = (int)(sinf(finLag) * 3.5f);
  int finFlutterR = (int)(sinf(finLag + 0.2f) * 3.5f);

  // Tay bơi phải (vươn ngang sang phải)
  int rFx1 = cx + (int)(4 * sX), rFy1 = by + 6;
  int rFx2 = cx + (int)(24 * sX), rFy2 = by + 8 + finFlutterR;
  int rFx3 = cx + (int)(40 * sX), rFy3 = by + 11 + finFlutterR;
  spr->fillTriangle(rFx1, rFy1 - 3, rFx2, rFy2 - 5, rFx1, rFy1 + 4, C_DEEP_CYAN);
  spr->fillTriangle(rFx2, rFy2 - 5, rFx3, rFy3, rFx2, rFy2 + 4, C_BODY_CYAN);
  spr->fillCircle(rFx3, rFy3, 4, C_BODY_CYAN);
  spr->fillCircle(rFx3 - 1, rFy3 - 1, 2, C_BODY_LIGHT);
  spr->drawLine(rFx1, rFy1 - 3, rFx3, rFy3, C_FRESNEL_RIM);

  // Tay bơi trái (vươn chéo xuống phía trước bên trái)
  int lFx1 = cx - (int)(8 * sX), lFy1 = by + 7;
  int lFx2 = cx - (int)(22 * sX), lFy2 = by + 16 + finFlutterL;
  int lFx3 = cx - (int)(34 * sX), lFy3 = by + 24 + finFlutterL;
  spr->fillTriangle(lFx1, lFy1 - 2, lFx2, lFy2 - 4, lFx1, lFy1 + 4, C_DEEP_CYAN);
  spr->fillTriangle(lFx2, lFy2 - 4, lFx3, lFy3, lFx2, lFy2 + 4, C_BODY_CYAN);
  spr->fillCircle(lFx3, lFy3, 4, C_BODY_CYAN);
  spr->fillCircle(lFx3 - 1, lFy3 - 1, 2, C_BODY_LIGHT);
  spr->drawLine(lFx1, lFy1 - 2, lFx3, lFy3, C_FRESNEL_RIM);

  // 7. THÂN GIỌT NƯỚC BÁN TRONG SUỐT & ĐUÔI NHỌN NÚNG NÍNH (Teardrop Torso & Tail Nub)
  int bRx = (int)(12 * sX);
  int bRy = (int)(13 * sY);
  // Khối thân trên
  spr->fillEllipse(cx - 1, by + 10, bRx + 1, bRy + 1, C_FRESNEL_RIM);
  spr->fillEllipse(cx - 1, by + 10, bRx, bRy, C_BODY_CYAN);
  spr->fillEllipse(cx - 1, by + 11, (int)(9 * sX), (int)(10 * sY), C_BODY_CORE_SSS);
  spr->fillEllipse(cx - 2, by + 8, (int)(7 * sX), (int)(7 * sY), C_BODY_LIGHT);

  // Thùy đuôi nhọn ở đáy thân
  int tailX = cx - (int)(1 * sX);
  int tailY = by + (int)(22 * sY);
  spr->fillTriangle(tailX - (int)(6 * sX), by + 14, tailX + (int)(4 * sX), by + 14, tailX, tailY, C_BODY_CYAN);
  spr->fillCircle(tailX, tailY, 2, C_BODY_CYAN);
  spr->drawFastHLine(tailX - 2, tailY, 4, C_FRESNEL_RIM);

  // Highlight men sứ hông
  spr->fillEllipse(cx - (int)(4 * sX), by + 14, 2, 1, C_WHITE);

  // 8. VIÊN HỒNG NGỌC RUBY ĐỎ RỰC TRƯỚC NGỰC & VÒNG VÀNG HOÀNG KIM
  int gemX = cx - (int)(1 * sX);
  int gemY = by + 9;
  spr->fillEllipse(gemX, gemY, 6, 8, C_GOLD_BEZEL);
  spr->drawCircle(gemX, gemY - 7, 1, C_GOLD_BRIGHT);
  spr->drawCircle(gemX, gemY + 7, 1, C_GOLD_BRIGHT);
  spr->drawCircle(gemX - 5, gemY, 1, C_GOLD_BRIGHT);
  spr->drawCircle(gemX + 5, gemY, 1, C_GOLD_BRIGHT);

  spr->fillEllipse(gemX, gemY, 5, 7, C_RUBY_DEEP);
  spr->fillEllipse(gemX, gemY, 4, 6, C_RUBY_CORE);
  spr->fillEllipse(gemX - 1, gemY - 1, 2, 3, C_RUBY_BRIGHT);
  spr->fillCircle(gemX - 1, gemY - 2, 1, C_WHITE);

  // 9. ĐẦU NƯỚC GIỌT NƯỚC KHỔNG LỒ & ĐỘ BÓNG MEN SỨ
  int hRx = (int)(24 * sX);
  int hRy = (int)(20 * sY);
  spr->fillEllipse(cx - 1, hy, hRx + 2, hRy + 2, C_FRESNEL_RIM);
  spr->fillEllipse(cx - 1, hy, hRx, hRy, C_BODY_CYAN);
  spr->fillEllipse(cx - 1, hy + 2, (int)(19 * sX), (int)(16 * sY), C_BODY_CORE_SSS);
  spr->fillEllipse(cx - 3, hy - 1, (int)(17 * sX), (int)(13 * sY), C_BODY_LIGHT);

  // Phản quang men sứ trán
  spr->fillEllipse(cx - (int)(10 * sX), hy - (int)(10 * sY), 6, 3, C_WHITE);
  spr->fillCircle(cx + (int)(9 * sX), hy - (int)(8 * sY), 2, C_WHITE);

  // 10. PHAO NỔI TRÒN TRÊN ĐỈNH ĐẦU TỰA VIÊN KẸO BIỂN
  spr->fillRoundRect(buoyX - 5, buoyY + 3, 10, 4, 2, C_BODY_CORE_SSS);
  spr->fillEllipse(buoyX, buoyY, (int)(14 * sX) + 1, (int)(7 * sY) + 1, C_FRESNEL_RIM);
  spr->fillEllipse(buoyX, buoyY, (int)(14 * sX), (int)(7 * sY), C_BODY_CYAN);
  spr->fillEllipse(buoyX, buoyY + 1, (int)(11 * sX), (int)(5 * sY), C_BODY_CORE_SSS);
  spr->fillEllipse(buoyX - 1, buoyY - 1, (int)(9 * sX), (int)(4 * sY), C_BUOY_LIGHT);
  spr->fillEllipse(buoyX, buoyY - 1, 4, 2, C_DEEP_CYAN);
  spr->fillEllipse(buoyX - 3, buoyY - 2, 3, 1, C_WHITE);

  // 11. ĐỐM ANTEN TRÁN & CUỐNG NỐI MẮT (100% Khớp ảnh mẫu Phione)
  int ey = hy + 2;
  int exL = cx - (int)(13 * sX);
  int exR = cx + (int)(7 * sX);

  // Đốm trái
  int dLx = cx - (int)(14 * sX), dLy = hy - (int)(6 * sY);
  spr->drawLine(dLx, dLy, exL - 1, ey - 6, C_MARKING_BLUE);
  spr->fillCircle(dLx, dLy, 3, C_MARKING_BLUE);
  spr->fillCircle(dLx - 1, dLy - 1, 1, C_BODY_LIGHT);

  // Đốm phải (hướng vào trung tâm trán)
  int dRx = cx - (int)(2 * sX), dRy = hy - (int)(7 * sY);
  spr->drawLine(dRx, dRy, exR - 2, ey - 6, C_MARKING_BLUE);
  spr->fillCircle(dRx, dRy, 3, C_MARKING_BLUE);
  spr->fillCircle(dRx - 1, dRy - 1, 1, C_BODY_LIGHT);

  // 12. VỆT VÀNG MÍ MẮT TRÊN (Golden Eyelid Accent)
  spr->drawEllipse(exL, ey - 1, 6, 7, C_GOLD_EYELID);
  spr->drawEllipse(exR, ey - 1, 7, 8, C_GOLD_EYELID);
  spr->drawPixel(exL + 4, ey - 6, C_GOLD_BRIGHT);
  spr->drawPixel(exR + 5, ey - 6, C_GOLD_BRIGHT);

  // 13. ĐÔI MẮT PHA LÊ XANH THẲM TO TRÒN (3-Point Specular Catchlights)
  if (blink) {
    spr->drawEllipse(exL, ey + 2, 5, 2, C_EYE_DARK);
    spr->drawEllipse(exR, ey + 2, 6, 2, C_EYE_DARK);
  } else {
    // Mắt trái:
    spr->fillEllipse(exL, ey, 5, 8, C_EYE_DARK);
    spr->fillEllipse(exL, ey + 1, 4, 7, C_EYE_IRIS_BLUE);
    spr->fillEllipse(exL, ey + 3, 3, 2, C_EYE_IRIS_AQUA);
    spr->fillCircle(exL - 1, ey - 1, 2, C_EYE_DARK);
    // 3 Catchlights mắt trái:
    spr->fillCircle(exL - 2, ey - 3, 2, C_WHITE); // Point 1: Keylight lớn
    spr->drawPixel(exL + 2, ey + 3, C_WHITE);     // Point 2: Caustic bounce
    spr->drawPixel(exL + 1, ey - 2, C_WHITE);     // Point 3: Micro twinkle

    // Mắt phải:
    spr->fillEllipse(exR, ey, 6, 9, C_EYE_DARK);
    spr->fillEllipse(exR, ey + 1, 5, 8, C_EYE_IRIS_BLUE);
    spr->fillEllipse(exR, ey + 4, 4, 3, C_EYE_IRIS_AQUA);
    spr->fillCircle(exR - 1, ey - 1, 3, C_EYE_DARK);
    // 3 Catchlights mắt phải:
    spr->fillCircle(exR - 2, ey - 3, 2, C_WHITE); // Point 1: Keylight lớn
    spr->drawPixel(exR + 2, ey + 3, C_WHITE);     // Point 2: Caustic bounce
    spr->drawPixel(exR + 2, ey - 2, C_WHITE);     // Point 3: Micro twinkle
  }

  // 14. ĐÔI MÁ ỬNG HỒNG NƯỚC BIỂN & NỤ CƯỜI NGỌT NGÀO
  spr->fillEllipse(exL - 4, hy + 8, 4, 3, C_BLUSH_PINK);
  spr->fillEllipse(exR + 5, hy + 8, 4, 3, C_BLUSH_PINK);

  // Nụ cười mỉm nhỏ xinh
  int mX = cx - (int)(3 * sX);
  int mY = hy + 8;
  spr->drawPixel(mX - 3, mY, C_MOUTH_DEEP);
  spr->drawFastHLine(mX - 2, mY + 1, 4, C_MOUTH_DEEP);
  spr->drawPixel(mX + 2, mY, C_MOUTH_DEEP);
}

static void drawPhioneSeaDrifter(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  (void)breath;
  (void)scale;
  bool blink = (fmodf(angle, 3.5f) < 0.14f);
  drawPhioneSeaDrifter(spr, cx, cy, angle, blink);
}

} // namespace SpriteRenderer
