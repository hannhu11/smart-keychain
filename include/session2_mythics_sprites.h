#pragma once
// ============================================================================
// SESSION 2 MYTHIC BEASTS SUITE - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 ST7789 IPS LCD (172x320 60FPS DMA)
// Pop Mart & Kawaii Visual DNA: Volumetric 4-Tone Shading & Crystal Catchlights
// Characters: Phione, Marshadow, Zeraora, Cosmog, Poipole (IDs 55 to 59)
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace Session2Mythics {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// -------------------------------------------------------------
// Phione - Giọt Nước Biển Trôi Dạt
// -------------------------------------------------------------
// =========================================================================
// PHIONE - GIỌT NƯỚC BIỂN TRÔI DẠT (MYTHIC PHIONE SEA DRIFTER)
// Pop Mart / High-End Vinyl Collectible Art - 100% Hardware Compatible ST7789
// Target: ST7789 IPS 172x320 / 240x280 (16-bit RGB565)
// =========================================================================

static void drawPhioneSeaDrifter(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // 1. Nhịp bơi lơ lửng đại dương Squash & Stretch 5% bảo toàn thể tích
  float breathPhase = angle * 2.0f;
  float sY = 1.0f + 0.05f * sinf(breathPhase);
  float sX = 1.0f - 0.025f * sinf(breathPhase); // Volume conservation: sY * (sX^2) ≈ 1.0
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

// -------------------------------------------------------------
// Marshadow - Tinh Linh Bóng Đêm Khói Xám (Thần Thú Ẩn Mình Trong Bóng Tối)
// -------------------------------------------------------------
// =========================================================================
// MARSHADOW TINH LINH BÓNG ĐÊM KHÓI XÁM (MYTHIC MARSHADOW GLOOMY GHOST)
// ScaledCanvas C++ Implementation - 100% Hardware Compatible ST7789
// Pop Mart / Vinyl High-End 3D Sculpting & Micro-Physics Engine
// Target Display: ST7789 IPS 240x280 / 172x320 (16-bit RGB565)
// =========================================================================
static void drawMythicMarshadow(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // -----------------------------------------------------------------------
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (ORGANIC MICRO-PHYSICS)
  // -----------------------------------------------------------------------
  float breathPhase = angle * 2.0f;
  
  // Chu kỳ lơ lửng & phập phồng nhẹ theo phương đứng (Hovering float)
  int hoverOffsetY = (int)(sinf(breathPhase) * 2.5f);
  int by = cy + hoverOffsetY;

  // Nhịp thở đàn hồi Squash & Stretch 5% (Bảo toàn thể tích thực tế sY * sX ≈ 1.0)
  float sY = 1.0f + 0.05f * sinf(breathPhase);
  float sX = 1.0f - 0.025f * sinf(breathPhase);

  // Trễ pha động học 80ms (Delta Phi ≈ 0.48 rad)
  float lagSmoke  = breathPhase - 0.48f; // Khói cổ & mũ
  float lagCrest  = breathPhase - 0.40f; // Ngọn lửa chỏm mũ
  float lagShadow = breathPhase - 0.20f; // Vùng bóng trải sàn
  float lagArm    = breathPhase - 0.25f; // Đung đưa nắm đấm

  // -----------------------------------------------------------------------
  // 2. BẢNG MÀU 16-BIT RGB565 CHUẨN XÁC POP MART VINYL MARSHADOW
  // -----------------------------------------------------------------------
  const uint16_t C_SMOKE_CREST    = 0x8CD5; // #8C9BAF Lóa sáng bạc ngọn lửa và chóp sừng
  const uint16_t C_SMOKE_LIGHT    = 0x6370; // #636E80 Diện đón sáng men sứ góc 10h
  const uint16_t C_SMOKE_MAIN     = 0x3A2A; // #3D4450 Sắc xám than chì chủ đạo
  const uint16_t C_SMOKE_DARK     = 0x2987; // #2B313A Bóng đổ thể tích vinyl
  const uint16_t C_SMOKE_DEEP     = 0x1905; // #1C2128 Khối tối sâu và rãnh cổ áo
  const uint16_t C_FACE_MASK      = 0x10A3; // #14171C Hốc mặt bóng đêm sâu thẳm
  const uint16_t C_WAIST_BAND     = 0x18C5; // #1A1D24 Đai bóng tối ngang ngực/eo
  const uint16_t C_WRIST_PAD      = 0x52ED; // #555F6E Vòng phù hiệu cổ tay
  const uint16_t C_EYE_RUBY_DARK  = 0x98C3; // #991B1B Đáy viền đỏ thẫm hốc mắt
  const uint16_t C_EYE_RUBY_CORE  = 0xD924; // #DC2626 Tròng đỏ ruby quyền năng
  const uint16_t C_EYE_AMBER      = 0xFB82; // #F97316 Cam hổ phách rực rỡ
  const uint16_t C_EYE_GOLD_CORE  = 0xFE62; // #FACC15 Lõi vàng hoàng kim phát quang
  const uint16_t C_EYE_FLAME_TIP  = 0xFF91; // #FEF08A Chóp lửa ngọn nến trên đỉnh mắt
  const uint16_t C_EYE_SPEC_WHITE = 0xFFFF; // #FFFFFF Điểm bắt sáng pha lê 1 & 3
  const uint16_t C_EYE_SPEC_AMBER = 0xFEB5; // #FED7AA Điểm bắt sáng phụ phản xạ ấm góc 4h
  const uint16_t C_ASH_SILVER     = 0xE75E; // #E2E8F0 Đốm tàn tro dạ quang xám bạc
  const uint16_t C_ASH_GLOW       = 0x9517; // #94A3B8 Quầng sáng tàn tro lơ lửng
  const uint16_t C_SHADOW_VOID    = 0x0862; // #0A0C10 Vùng bóng đêm loang rộng dưới sàn
  const uint16_t C_SHADOW_EDGE    = 0x1905; // #1E232B Dải khói bóng đêm bò dài trên sàn
  const uint16_t C_MOUTH_LINE     = 0x10A3; // #121419 Khóe miệng kiên định

  // -----------------------------------------------------------------------
  // 3. LỚP 1: VÙNG BÓNG ĐÊM LOANG RỘNG DƯỚI CHÂN & DẢI KHÓI TRẢI SÀN
  // -----------------------------------------------------------------------
  int floorY = cy + 46;
  int shRx = (int)((27.0f - hoverOffsetY * 1.2f) * sX);
  int shRy = (int)(6.8f - hoverOffsetY * 0.3f);
  if (shRx < 12) shRx = 12;
  if (shRy < 3)  shRy = 3;

  spr->fillEllipse(cx, floorY, shRx + 8, shRy + 2, C_SHADOW_EDGE);
  spr->fillEllipse(cx, floorY, shRx, shRy, C_SHADOW_VOID);

  // Dải khói bóng đêm bò dài trên sàn từ gót chân phải (Trailing Shadow Ribbon)
  int shadowWave1 = (int)(sinf(lagShadow) * 2.4f);
  int shadowWave2 = (int)(cosf(lagShadow * 1.2f) * 2.8f);
  int shadowWave3 = (int)(sinf(lagShadow * 1.5f) * 2.0f);

  int rX0 = cx + 4,  rY0 = floorY - 1;
  int rX1 = cx + 18, rY1 = floorY + 1 + shadowWave1;
  int rX2 = cx + 32, rY2 = floorY - 1 + shadowWave2;
  int rX3 = cx + 46, rY3 = floorY + 2 + shadowWave3;
  int rX4 = cx + 62, rY4 = floorY + shadowWave3;

  spr->fillTriangle(rX0, rY0, rX1, rY1, rX0, rY0 + 3, C_SHADOW_VOID);
  spr->fillTriangle(rX1, rY1, rX2, rY2, rX1, rY1 + 3, C_SHADOW_EDGE);
  spr->fillTriangle(rX2, rY2, rX3, rY3, rX2, rY2 + 2, C_SHADOW_EDGE);
  spr->fillTriangle(rX3, rY3, rX4, rY4, rX3, rY3 + 2, C_SHADOW_VOID);
  spr->drawLine(rX0, rY0, rX2, rY2, C_SMOKE_DEEP);
  spr->drawLine(rX2, rY2, rX4, rY4, C_SHADOW_EDGE);

  // -----------------------------------------------------------------------
  // 4. LỚP 2: ĐỐM TÀN TRO DẠ QUANG XÁM BẠC BAY LƠ LỬNG
  // -----------------------------------------------------------------------
  const int ashOffsets[6][2] = {
    {-38, -30}, {38, -22}, {-44, 14}, {42, 20}, {-16, -54}, {22, -58}
  };
  const float ashPhases[6] = {0.0f, 1.5f, 2.8f, 4.0f, 5.1f, 3.4f};
  for (int a = 0; a < 6; a++) {
    float aLag = breathPhase * 0.7f + ashPhases[a];
    int ax = cx + ashOffsets[a][0] + (int)(sinf(aLag) * 4.5f);
    int ay = cy + ashOffsets[a][1] + (int)(cosf(aLag * 0.9f) * 4.0f);
    uint16_t colAsh = (a % 2 == 0) ? C_ASH_SILVER : C_EYE_GOLD_CORE;
    spr->drawCircle(ax, ay, 2, C_ASH_GLOW);
    spr->drawPixel(ax, ay, colAsh);
    spr->drawPixel(ax - 1, ay, C_EYE_SPEC_WHITE);
  }

  // -----------------------------------------------------------------------
  // 5. LỚP 3: HAI CHÂN NGẮN MŨM MĨM (LÚN VÀO BÓNG TỐI)
  // -----------------------------------------------------------------------
  int legY = by + 28;
  int legW = (int)(8.5f * sX);
  int legH = (int)(17.0f * sY);

  for (int legIdx = 0; legIdx < 2; legIdx++) {
    int sign = (legIdx == 0) ? -1 : 1;
    int lx = cx + sign * (int)(8.5f * sX);
    spr->fillRoundRect(lx - legW / 2, legY, legW, legH, 3, C_SMOKE_DARK);
    spr->fillRoundRect(lx - legW / 2 + 1, legY + 1, legW - 2, legH - 3, 2, C_SMOKE_MAIN);
    // Bàn chân lún vào bóng
    spr->fillEllipse(lx + (sign < 0 ? -1 : 1), legY + legH - 2, (int)(legW * 0.65f), (int)(3.0f * sY), C_SMOKE_DEEP);
    spr->drawFastVLine(sign < 0 ? lx - legW / 2 : lx + legW / 2 - 1, legY + 2, legH - 4, C_SMOKE_LIGHT);
  }

  // -----------------------------------------------------------------------
  // 6. LỚP 4: THÂN KHÓI THAN CHÌ BÓNG BẨY & ĐAI BÓNG TỐI NGANG EO
  // -----------------------------------------------------------------------
  int bodyY = by + 16;
  int bRx   = (int)(17.5f * sX);
  int bRy   = (int)(15.5f * sY);

  // Đổ bóng đáy thân
  spr->fillEllipse(cx, bodyY + 4, bRx + 1, bRy - 2, C_SMOKE_DEEP);
  // Thân chính
  spr->fillEllipse(cx, bodyY, bRx, bRy, C_SMOKE_MAIN);
  spr->fillEllipse(cx - (int)(3 * sX), bodyY - (int)(3 * sY), bRx - 3, bRy - 3, C_SMOKE_LIGHT);
  spr->fillEllipse(cx, bodyY, bRx - 4, bRy - 4, C_SMOKE_MAIN);

  // Đai bóng tối ngang eo/ngực (100% Khớp ảnh mẫu)
  spr->fillEllipse(cx, bodyY - 5, (int)(bRx * 0.94f), (int)(4.5f * sY), C_WAIST_BAND);

  // Highlight men sứ vinyl sườn trái
  spr->fillEllipse(cx - (int)(7 * sX), bodyY + 2, 3, 2, C_SMOKE_CREST);

  // -----------------------------------------------------------------------
  // 7. LỚP 5: HAI TAY MŨM MĨM & HAI NẮM ĐẤM BỌC KHÓI CỔ TAY
  // -----------------------------------------------------------------------
  int armSwayL = (int)(sinf(lagArm) * 1.5f);
  int armSwayR = -(int)(sinf(lagArm) * 1.5f);

  for (int armIdx = 0; armIdx < 2; armIdx++) {
    int sign = (armIdx == 0) ? -1 : 1;
    int sway = (armIdx == 0) ? armSwayL : armSwayR;
    int shX = cx + sign * (int)(13.0f * sX);
    int shY = by + 12;
    int fistX = cx + sign * (int)(20.5f * sX) + sway / 2;
    int fistY = by + 24 + sway;

    // Cánh tay nối
    spr->fillTriangle(shX, shY - 2, fistX - sign * 2, fistY - 6, fistX + sign * 5, fistY - 2, C_SMOKE_DARK);
    spr->fillTriangle(shX, shY - 2, fistX + sign * 5, fistY - 2, shX + sign * 3, shY + 3, C_SMOKE_MAIN);

    // Nắm đấm tròn vo mũm mĩm
    spr->fillCircle(fistX, fistY, 7, C_SMOKE_DARK);
    spr->fillCircle(fistX - sign, fistY - 1, 6, C_SMOKE_MAIN);
    spr->fillCircle(fistX - sign * 2, fistY - 2, 3, C_SMOKE_LIGHT);

    // Vòng xoáy khói cổ tay đặc trưng
    int padX = fistX + sign * 3;
    int padY = fistY - 4;
    spr->drawEllipse(padX, padY, 3, 4, C_SMOKE_LIGHT);
    spr->fillCircle(padX, padY, 2, C_WRIST_PAD);
  }

  // -----------------------------------------------------------------------
  // 8. LỚP 6: CỔ ÁO KHÓI XOẮN ỐC BỒNG BỀNH (BILLOWING SMOKE COWL)
  // -----------------------------------------------------------------------
  int cowlY = by + 4;
  int smokeWave  = (int)(sinf(lagSmoke) * 2.2f);
  int smokeWave2 = (int)(cosf(lagSmoke * 1.1f) * 2.0f);

  // Bóng đổ dưới cổ áo
  spr->fillEllipse(cx, cowlY + 6, (int)(24 * sX), 6, C_SMOKE_DEEP);

  // 3 Múi khói phía trước
  spr->fillEllipse(cx - (int)(16 * sX), cowlY + 1 + smokeWave / 2, (int)(10 * sX), (int)(7 * sY), C_SMOKE_DARK);
  spr->fillEllipse(cx - (int)(16 * sX), cowlY + smokeWave / 2, (int)(9 * sX), (int)(6 * sY), C_SMOKE_LIGHT);

  spr->fillEllipse(cx - (int)(5 * sX), cowlY + 3 + smokeWave2 / 2, (int)(11 * sX), (int)(8 * sY), C_SMOKE_DARK);
  spr->fillEllipse(cx - (int)(5 * sX), cowlY + 2 + smokeWave2 / 2, (int)(10 * sX), (int)(7 * sY), C_SMOKE_MAIN);

  spr->fillEllipse(cx + (int)(8 * sX), cowlY + 2 - smokeWave / 2, (int)(12 * sX), (int)(8 * sY), C_SMOKE_DARK);
  spr->fillEllipse(cx + (int)(8 * sX), cowlY + 1 - smokeWave / 2, (int)(11 * sX), (int)(7 * sY), C_SMOKE_LIGHT);

  // Đuôi khói cổ áo vút sang phải (Trailing Collar Smoke Wisp)
  int tailX1 = cx + (int)(18 * sX);
  int tailY1 = cowlY + 1;
  int tailX2 = cx + (int)(31 * sX) + smokeWave2 / 2;
  int tailY2 = cowlY + 2 + smokeWave;
  int tailX3 = cx + (int)(44 * sX) + smokeWave;
  int tailY3 = cowlY - 3 + smokeWave2;

  spr->fillTriangle(tailX1, tailY1 + 4, tailX2, tailY2 + 2, tailX1 + 2, tailY1 - 2, C_SMOKE_MAIN);
  spr->fillTriangle(tailX2, tailY2 + 2, tailX3, tailY3, tailX2 - 2, tailY2 - 3, C_SMOKE_LIGHT);
  spr->drawLine(tailX1, tailY1 - 2, tailX3, tailY3, C_SMOKE_CREST);

  // -----------------------------------------------------------------------
  // 9. LỚP 7: MŨ TRÙM ĐẦU KHÓI THAN CHÌ (SMOKY HOOD)
  // -----------------------------------------------------------------------
  int headY = by - 12;
  int hRx   = (int)(25.0f * sX);
  int hRy   = (int)(22.5f * sY);

  spr->fillEllipse(cx, headY, hRx + 1, hRy + 1, C_SMOKE_DEEP);
  spr->fillEllipse(cx, headY, hRx, hRy, C_SMOKE_MAIN);
  spr->fillEllipse(cx - (int)(4 * sX), headY - (int)(4 * sY), hRx - 4, hRy - 4, C_SMOKE_LIGHT);
  spr->fillEllipse(cx, headY, hRx - 5, hRy - 5, C_SMOKE_MAIN);

  // Tai mũ trùm hai bên má (Cheek lobes)
  spr->fillEllipse(cx - (int)(18 * sX), headY + (int)(8 * sY), (int)(7 * sX), (int)(9 * sY), C_SMOKE_MAIN);
  spr->fillEllipse(cx + (int)(18 * sX), headY + (int)(8 * sY), (int)(7 * sX), (int)(9 * sY), C_SMOKE_MAIN);
  spr->drawEllipse(cx - (int)(18 * sX), headY + (int)(8 * sY), (int)(7 * sX), (int)(9 * sY), C_SMOKE_DARK);
  spr->drawEllipse(cx + (int)(18 * sX), headY + (int)(8 * sY), (int)(7 * sX), (int)(9 * sY), C_SMOKE_DARK);

  // -----------------------------------------------------------------------
  // 10. LỚP 8: CHỎM LỬA BÓNG TỐI TRUNG TÂM VƯƠN CAO (UPRIGHT FLAME CREST)
  // -----------------------------------------------------------------------
  int crestWave = (int)(sinf(lagCrest) * 2.8f);
  int crestBaseY = by - (int)(28 * sY);

  int crRootL = cx - (int)(8 * sX);
  int crRootR = cx + (int)(8 * sX);
  int crMidX  = cx + crestWave / 2;
  int crMidY  = crestBaseY - 16;
  int crTipX  = cx + 7 + crestWave;
  int crTipY  = crestBaseY - 32;

  spr->fillTriangle(crRootL, crestBaseY, crMidX - 4, crMidY, crRootR, crestBaseY, C_SMOKE_MAIN);
  spr->fillTriangle(crMidX - 4, crMidY, crTipX, crTipY, crMidX + 5, crMidY, C_SMOKE_LIGHT);
  spr->fillTriangle(crTipX, crTipY, crTipX + 4, crTipY + 4, crMidX + 4, crMidY, C_SMOKE_CREST);
  spr->drawLine(crRootL, crestBaseY, crTipX, crTipY, C_SMOKE_CREST);
  spr->drawPixel(crTipX, crTipY, C_EYE_SPEC_WHITE);

  // -----------------------------------------------------------------------
  // 11. LỚP 9: ĐÔI SỪNG KHÓI XOẮN ỐC HAI BÊN (TWIN SPIRAL SMOKE HORNS)
  // -----------------------------------------------------------------------
  int hornLag = breathPhase - 0.52f;
  int hornSway = (int)(sinf(hornLag) * 2.0f);

  for (int hornIdx = 0; hornIdx < 2; hornIdx++) {
    int sign = (hornIdx == 0) ? -1 : 1;
    int hornBaseX = cx + sign * (int)(14 * sX);
    int hornBaseY = by - (int)(24 * sY);
    int spCenterX = cx + sign * (int)(18.0f * sX) + hornSway * sign / 2;
    int spCenterY = by - (int)(33.5f * sY) + hornSway / 2;

    spr->fillCircle(spCenterX, spCenterY, 8, C_SMOKE_DARK);
    spr->fillCircle(spCenterX - sign, spCenterY - 1, 7, C_SMOKE_MAIN);
    spr->fillCircle(spCenterX - sign * 2, spCenterY - 2, 5, C_SMOKE_LIGHT);
    spr->fillCircle(spCenterX, spCenterY, 3, C_SMOKE_CREST);

    // Vòng xoáy ốc (Spiral Inward Curl)
    spr->drawCircle(spCenterX, spCenterY, 6, C_SMOKE_CREST);
    spr->drawCircle(spCenterX - sign, spCenterY, 4, C_SMOKE_DARK);
    spr->drawLine(hornBaseX, hornBaseY, spCenterX - sign * 4, spCenterY + 4, C_SMOKE_MAIN);
    spr->drawLine(hornBaseX + sign * 2, hornBaseY, spCenterX + sign * 5, spCenterY + 2, C_SMOKE_CREST);
  }

  // -----------------------------------------------------------------------
  // 12. LỚP 10: HỐC MẶT BÓNG ĐÊM SÂU THẲM (DARK FACE WELL)
  // -----------------------------------------------------------------------
  int faceY = by - 12;
  spr->fillCircle(cx - (int)(10.5f * sX), faceY, (int)(11 * sX), C_FACE_MASK);
  spr->fillCircle(cx + (int)(10.5f * sX), faceY, (int)(11 * sX), C_FACE_MASK);
  spr->fillEllipse(cx, faceY + 5, (int)(12 * sX), (int)(8 * sY), C_FACE_MASK);

  // Chiếc miệng nhỏ xinh kiên định
  int mouthY = faceY + (int)(7.2f * sY);
  spr->drawFastHLine(cx - 2, mouthY, 5, C_MOUTH_LINE);
  spr->drawPixel(cx - 2, mouthY - 1, C_MOUTH_LINE);
  spr->drawPixel(cx + 2, mouthY - 1, C_MOUTH_LINE);

  // -----------------------------------------------------------------------
  // 13. LỚP 11: ĐÔI MẮT HỔ PHÁCH VÀNG CAM RỰC SÁNG VỚI TRÒNG ĐỎ RUBY
  // -----------------------------------------------------------------------
  int eyeY  = by - 12;
  int eyeXL = cx - (int)(10.5f * sX);
  int eyeXR = cx + (int)(10.5f * sX);
  int eyeR  = (int)(5.2f * sX);
  int eyeH  = (int)(7.8f * sY);

  if (blink) {
    for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
      int ex = (eyeIdx == 0) ? eyeXL : eyeXR;
      spr->drawFastHLine(ex - eyeR, eyeY + 1, eyeR * 2 + 1, C_EYE_AMBER);
      spr->drawFastHLine(ex - eyeR + 1, eyeY + 2, eyeR * 2 - 1, C_FACE_MASK);
      spr->drawPixel(ex - eyeR, eyeY, C_FACE_MASK);
      spr->drawPixel(ex + eyeR, eyeY, C_FACE_MASK);
    }
  } else {
    for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
      int ex = (eyeIdx == 0) ? eyeXL : eyeXR;

      // 1. Quầng hào quang mắt
      spr->drawCircle(ex, eyeY, eyeH + 2, C_EYE_RUBY_DARK);

      // 2. Chóp lửa ngọn nến vàng rực trên đỉnh mắt (100% Khớp ảnh mẫu)
      int fTipY = eyeY - eyeH - 4;
      spr->fillTriangle(ex - 2, eyeY - eyeH + 2, ex + 2, eyeY - eyeH + 2, ex, fTipY, C_EYE_GOLD_CORE);
      spr->drawPixel(ex, fTipY, C_EYE_SPEC_WHITE);
      spr->drawPixel(ex, fTipY + 1, C_EYE_FLAME_TIP);

      // 3. Tròng mắt oval chính: Đỏ ruby ngoài, Cam hổ phách giữa, Vàng hoàng kim trong
      spr->fillEllipse(ex, eyeY, eyeR + 1, eyeH + 1, C_EYE_RUBY_DARK);
      spr->fillEllipse(ex, eyeY, eyeR, eyeH, C_EYE_RUBY_CORE);
      spr->fillEllipse(ex, eyeY, eyeR - 1, eyeH - 2, C_EYE_AMBER);
      spr->fillEllipse(ex, eyeY, eyeR - 2, eyeH - 4, C_EYE_GOLD_CORE);

      // 4. Vệt tụ quang khúc xạ đáy mắt
      spr->drawFastHLine(ex - 2, eyeY + eyeH - 2, 5, C_EYE_FLAME_TIP);

      // 5. 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Specular Crystal Eyes)
      // Điểm 1: Direct Keylight 10h (2x2 px sắc nét)
      spr->fillRect(ex - 2, eyeY - 3, 2, 2, C_EYE_SPEC_WHITE);
      // Điểm 2: Ground Amber Bounce 4h (1x1 px phản xạ ấm)
      spr->drawPixel(ex + 2, eyeY + 2, C_EYE_SPEC_AMBER);
      // Điểm 3: Crystal Slit Micro Glint 2h (tia lóa pha lê)
      spr->drawPixel(ex + 1, eyeY - 2, C_EYE_SPEC_WHITE);
    }
  }

  // -----------------------------------------------------------------------
  // 14. LỚP 12: ĐỐM SÁNG HOÀNG KIM TIA LỬA LƠ LỬNG
  // -----------------------------------------------------------------------
  int sp1X = cx - (int)(17 * sX) + (int)(sinf(breathPhase * 1.5f) * 2.5f);
  int sp1Y = by - 8 + (int)(cosf(breathPhase * 1.2f) * 2.0f);
  spr->drawPixel(sp1X, sp1Y, C_EYE_FLAME_TIP);

  int sp2X = cx + (int)(17 * sX) - (int)(cosf(breathPhase * 1.4f) * 2.5f);
  int sp2Y = by - 8 + (int)(sinf(breathPhase * 1.4f) * 2.0f);
  spr->drawPixel(sp2X, sp2Y, C_EYE_AMBER);
}

static void drawMythicMarshadow(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  (void)breath;
  (void)scale;
  bool blink = (fmodf(angle, 3.5f) < 0.14f);
  drawMythicMarshadow(spr, cx, cy, angle, blink);
}

// -------------------------------------------------------------
// Zeraora
// -------------------------------------------------------------
// =========================================================================
// 08_MYTHIC_ZERAORA_THUNDERCLAP_CAT - C++ ScaledCanvas Implementation
// 100% Hardware Compatible with ESP32/ESP32-S3 + ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl 3D Sculpt: Golden Fur, Plasma Ears, Cyan Eyes, Lightning Tail
// Organic Micro-Physics: 5% Squash & Stretch, Tail Lag 0.45 rad, Plasma Sparks
// =========================================================================
static void drawZeraoraThunderclapCat(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
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
  int tailSwayX = (int)(sinf(tailLag) * 9.0f);
  int tailSwayY = (int)(cosf(tailLag) * 4.5f);

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

  // 4. LAYER 1: ĐUÔI TIA CHỚP XANH LAM UỐN LƯỢN SAU LƯNG (Lightning Bolt Tail with Phase Lag)
  // Gốc đuôi lông vàng dày dặn nối từ sườn lưng phải
  spr->fillTriangle(cx + 8, by + 22, cx + 34, by + 14 + tailSwayY, cx + 20, by + 32, C_GOLD_MAIN);
  spr->fillTriangle(cx + 10, by + 24, cx + 36, by + 16 + tailSwayY, cx + 24, by + 34, C_GOLD_SHADOW);
  // Khúc uốn zigzag 1
  spr->fillTriangle(cx + 28, by + 14 + tailSwayY, cx + 54 + tailSwayX * 0.5f, by + 2 + tailSwayY, cx + 38, by + 22 + tailSwayY, C_GOLD_MAIN);
  spr->fillTriangle(cx + 34, by + 16 + tailSwayY, cx + 54 + tailSwayX * 0.5f, by + 2 + tailSwayY, cx + 42, by + 18 + tailSwayY, C_CHARCOAL_DARK); // Vệt sấm đen đuôi
  // Khúc ngọn tia chớp chuyển sang xanh lam plasma điện quang
  spr->fillTriangle(cx + 46 + tailSwayX * 0.5f, by + 4 + tailSwayY, cx + 70 + tailSwayX * 0.8f, by - 20 + tailSwayY, cx + 56 + tailSwayX * 0.6f, by + 10 + tailSwayY, C_CYAN_DEEP);
  spr->fillTriangle(cx + 52 + tailSwayX * 0.6f, by + 2 + tailSwayY, cx + 72 + tailSwayX * 0.8f, by - 22 + tailSwayY, cx + 60 + tailSwayX * 0.7f, by + 6 + tailSwayY, C_CYAN_MAIN);
  // Mũi nhọn chóp đuôi tia chớp phát quang vút cao
  spr->fillTriangle(cx + 62 + tailSwayX * 0.7f, by - 16 + tailSwayY, cx + 86 + tailSwayX, by - 44 + tailSwayY, cx + 68 + tailSwayX * 0.8f, by - 10 + tailSwayY, C_CYAN_LIGHT);
  spr->drawLine(cx + 64 + tailSwayX * 0.7f, by - 18 + tailSwayY, cx + 84 + tailSwayX, by - 42 + tailSwayY, C_WHITE); // Lõi sáng

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

  // Tay phải (viewer's right - giơ cao nắm đấm sấm sét chào chiến hữu)
  spr->fillRoundRect(cx + 18, by + 8, 14, 10, 4, C_CHARCOAL); // Vai than
  spr->fillEllipse(cx + 36, by + 2, 16, 13, C_GOLD_MAIN); // Ống lông vàng cẳng tay
  spr->fillTriangle(cx + 30, by - 2, cx + 38, by + 3, cx + 33, by + 8, C_CHARCOAL_DARK); // Vệt sấm đen cẳng tay
  spr->fillCircle(cx + 47, by + 2, 9, C_CHARCOAL); // Bàn tay than
  // 3 Móng vuốt bạc
  spr->fillTriangle(cx + 52, by - 2, cx + 58, by - 2, cx + 53, by + 2, C_CLAW);
  spr->fillTriangle(cx + 52, by + 3, cx + 59, by + 4, cx + 52, by + 7, C_CLAW);
  spr->fillTriangle(cx + 49, by + 8, cx + 55, by + 11, cx + 48, by + 9, C_CLAW);
  // Đệm móng vuốt xanh điện phát sáng
  spr->fillCircle(cx + 47, by + 2, 4, C_PAW_PAD);
  spr->drawPixel(cx + 47, by + 2, C_WHITE);

  // 9. LAYER 6: ĐẦU MÈO, BỘ LÔNG VÀNG BỒNG BỀNH & VỆT SẤM ĐEN MÁ (Head & Fur Mane)
  // Khối đầu tròn trĩnh Pop Mart
  spr->fillEllipse(cx, by - 15, (int)(31 * sX), (int)(25 * sY), C_GOLD_MAIN);
  spr->fillEllipse(cx - 4, by - 24, (int)(15 * sX), (int)(7 * sY), C_GOLD_LIGHT); // Highlight đỉnh đầu

  // 3 Múi lông vàng điện chớp flaring hai bên má (Lông vàng hoàng kim bồng bềnh)
  // Má trái
  spr->fillTriangle(cx - 23, by - 20, cx - 46, by - 25, cx - 23, by - 11, C_GOLD_MAIN);
  spr->fillTriangle(cx - 24, by - 12, cx - 50, by - 10, cx - 21, by - 2, C_GOLD_MAIN);
  spr->fillTriangle(cx - 21, by - 3, cx - 43, by + 8, cx - 16, by + 3, C_GOLD_MAIN);
  spr->drawLine(cx - 23, by - 11, cx - 45, by - 10, C_GOLD_SHADOW);
  // Má phải
  spr->fillTriangle(cx + 23, by - 20, cx + 46, by - 25, cx + 23, by - 11, C_GOLD_MAIN);
  spr->fillTriangle(cx + 24, by - 12, cx + 50, by - 10, cx + 21, by - 2, C_GOLD_MAIN);
  spr->fillTriangle(cx + 21, by - 3, cx + 43, by + 8, cx + 16, by + 3, C_GOLD_MAIN);
  spr->drawLine(cx + 23, by - 11, cx + 45, by - 10, C_GOLD_SHADOW);

  // Mặt nạ than đen bao quanh mắt và mõm
  spr->fillEllipse(cx, by - 12, (int)(21 * sX), (int)(17 * sY), C_CHARCOAL);
  spr->fillTriangle(cx - 10, by - 5, cx, by + 5, cx + 10, by - 5, C_CHARCOAL); // Cằm nhọn nhẹ

  // Vệt sấm đen sắc nét hai bên má và trán (Sharp black thunder streaks)
  // Vệt má trái
  spr->fillTriangle(cx - 17, by - 17, cx - 33, by - 12, cx - 18, by - 8, C_CHARCOAL_DARK);
  // Vệt má phải
  spr->fillTriangle(cx + 17, by - 17, cx + 33, by - 12, cx + 18, by - 8, C_CHARCOAL_DARK);
  // Vệt trán trung tâm
  spr->fillTriangle(cx - 4, by - 29, cx, by - 19, cx + 4, by - 29, C_CHARCOAL_DARK);

  // 10. LAYER 7: MÀO SỪNG TIA CHỚP XANH LAM TRÊN TRÁN & RIA MÉP SẤM (Cyan Lightning Crest)
  // Sừng tia chớp xanh lam vút lên trán bên trái (Cyan lightning horn on forehead)
  spr->fillTriangle(cx - 6, by - 22, cx - 19, by - 54, cx - 12, by - 31, C_CYAN_DEEP);
  spr->fillTriangle(cx - 7, by - 23, cx - 18, by - 52, cx - 12, by - 32, C_CYAN_MAIN);
  spr->fillTriangle(cx - 9, by - 26, cx - 17, by - 50, cx - 13, by - 34, C_CYAN_LIGHT);
  spr->drawLine(cx - 9, by - 27, cx - 17, by - 51, C_WHITE);

  // Ria mép tia chớp xanh lam bên má trái
  spr->fillTriangle(cx - 18, by - 6, cx - 32, by - 4, cx - 19, by - 1, C_CYAN_MAIN);
  spr->drawLine(cx - 18, by - 6, cx - 31, by - 4, C_CYAN_LIGHT);

  // 11. LAYER 8: TAI MÈO NHỌN DỰNG CAO VỚI ĐỆM TAI XANH LAM PLASMA (Cat Ears with Plasma Pads)
  // Tai trái (viewer's left)
  spr->fillTriangle(cx - 12, by - 27, cx - 24, by - 64, cx - 2, by - 28, C_GOLD_MAIN);
  spr->drawLine(cx - 12, by - 27, cx - 24, by - 64, C_GOLD_SHADOW);
  spr->fillTriangle(cx - 11, by - 28, cx - 21, by - 57, cx - 5, by - 29, C_CHARCOAL_DARK);
  // Đệm tai xanh lam plasma phát sáng
  spr->fillTriangle(cx - 10, by - 31, cx - 18, by - 52, cx - 6, by - 32, C_CYAN_MAIN);
  spr->drawLine(cx - 9, by - 32, cx - 16, by - 48, C_CYAN_LIGHT);
  // Hạt tia lửa điện plasma lách tách quanh chóp tai trái
  spr->drawPixel(cx - 26 + spark1, by - 67, C_CYAN_LIGHT);
  spr->drawPixel(cx - 28 + spark2, by - 62, C_CYAN_MAIN);

  // Tai phải (viewer's right)
  spr->fillTriangle(cx + 2, by - 28, cx + 24, by - 64, cx + 12, by - 27, C_GOLD_MAIN);
  spr->drawLine(cx + 12, by - 27, cx + 24, by - 64, C_GOLD_SHADOW);
  spr->fillTriangle(cx + 5, by - 29, cx + 21, by - 57, cx + 11, by - 28, C_CHARCOAL_DARK);
  // Đệm tai xanh lam plasma phát sáng
  spr->fillTriangle(cx + 6, by - 32, cx + 18, by - 52, cx + 10, by - 31, C_CYAN_MAIN);
  spr->drawLine(cx + 9, by - 32, cx + 16, by - 48, C_CYAN_LIGHT);
  // Hạt tia lửa điện plasma lách tách quanh chóp tai phải
  spr->drawPixel(cx + 26 + spark2, by - 67, C_CYAN_LIGHT);
  spr->drawPixel(cx + 28 + spark1, by - 62, C_CYAN_MAIN);

  // 12. LAYER 9: ĐÔI MẮT XANH NGỌC LAM CYAN ĐIỆN QUANG TO TRÒN (Giant 3-Point Specular Eyes)
  for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
    int ex = (eyeIdx == 0) ? (cx - 11) : (cx + 11);
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
  spr->fillCircle(cx + 88 + tailSwayX + spark1, by - 46 + tailSwayY, 2, C_CYAN_LIGHT);
  spr->drawPixel(cx + 88 + tailSwayX + spark1, by - 46 + tailSwayY, C_WHITE);
  // Tia lửa sườn trái
  spr->fillCircle(cx - 48 + spark2, by - 16 + spark1, 2, C_CYAN_MAIN);
  spr->drawPixel(cx - 48 + spark2, by - 16 + spark1, C_WHITE);
  // Tia lửa trên đỉnh sừng
  spr->fillCircle(cx - 20 + spark1, by - 56 + spark3, 2, C_CYAN_LIGHT);
  spr->drawPixel(cx - 20 + spark1, by - 56 + spark3, C_WHITE);
}

// -------------------------------------------------------------
// Cosmog - Đám Mây Tinh Vân Vũ Trụ (Bé Cưng Tinh Cầu Nguyên Sơ)
// -------------------------------------------------------------
// =========================================================================
// 09_MYTHIC_COSMOG_NEBULA_BABY - ScaledCanvas C++ Implementation
// 100% Hardware Compatible with ESP32/ESP32-S3 + ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl High-End 3D Sculpt: Nebula Cloud, Golden Ring, Crystal Amber Eyes
// Organic Micro-Physics: 5% Squash & Stretch, 80ms Lag Puffs, Orbiting Stars
// =========================================================================
static void drawCosmogNebulaBaby(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
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

// -------------------------------------------------------------
// Poipole
// -------------------------------------------------------------
// =========================================================================
// 10_MYTHIC_POIPOLE_ADHESIVE_ALIEN - C++ ScaledCanvas Implementation
// 100% Hardware Compatible with ESP32 / ESP32-S3 + ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl 3D Sculpt: Giant Chubby Pastel Lavender Head, 3 Cyan Needle Horns,
// Cyan Rhombus Glowing Eyes, Mischievous V-Smile, Glowing Cyan Neck/Chest Stripes,
// Micro-Physics: 5% Volume-Preserving Squash & Stretch, Horn Lag 0.45 rad, Wagging Tail
// =========================================================================

static void drawPoipoleAdhesiveAlien(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (Organic Micro-Physics)
  float breathPhase = angle * 2.0f; // Chu kỳ bay lơ lửng bồng bềnh
  float breathSin   = sinf(breathPhase);

  // Nhịp bay lơ lửng Squash & Stretch 5% bảo toàn thể tích (Sy * Sx ≈ 1.0)
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int by = cy + (int)(breathSin * 3.5f); // Dao động độ cao Y-bobbing

  // 3 Chiếc kim tiêm / sừng ngọc uốn lượn nhẹ trễ pha Delta Phi = 0.45 rad
  float hornLag    = breathPhase - 0.45f;
  int hornSwayX    = (int)(sinf(hornLag) * 3.0f);
  int hornSwayY    = (int)(cosf(hornLag) * 2.0f);

  // Đuôi nhỏ ngoe nguẩy vui vẻ trễ pha Delta Phi = 0.65 rad
  float tailLag    = breathPhase - 0.65f;
  int tailSway     = (int)(sinf(tailLag) * 5.0f);

  // 2. BẢNG MÀU 16-BIT RGB565 CHUẨN XÁC POP MART VINYL
  const uint16_t C_FRESNEL_LAVENDER  = 0xF75F; // #F3E8FF Viền men sứ tím pastel lóa sáng
  const uint16_t C_HEAD_PASTEL_LIGHT = 0xDEBF; // #DDD6FE Đỉnh đầu đón sáng studio
  const uint16_t C_HEAD_PASTEL_MID   = 0xC5BF; // #C4B5FD Chuyển sắc tím pastel mềm mại
  const uint16_t C_HEAD_PURPLE       = 0xA45F; // #A78BFA Sắc tím oải hương pastel chủ đạo
  const uint16_t C_HEAD_PURPLE_DARK  = 0x79DD; // #7C3AED Đổ bóng đầu tím đậm
  const uint16_t C_HELMET_DEEP       = 0x5916; // #5B21B6 Khe rãnh múi giáp tím sâu thẳm
  const uint16_t C_BODY_DARK         = 0x48F2; // #4C1D95 Thân tím thẫm ngoài hành tinh
  const uint16_t C_BODY_SHADOW       = 0x288C; // #2E1065 Hốc tối thân và chân sâu thẳm
  const uint16_t C_MAGENTA_LIGHT     = 0xF396; // #F472B6 Đón sáng giác cắt hồng fuchsia
  const uint16_t C_MAGENTA_CORE      = 0xE0E9; // #E11D48 Mặt nạ mắt & vành mũ hồng magenta
  const uint16_t C_MAGENTA_DEEP      = 0x9887; // #9F1239 Đáy bóng tối hồng magenta
  const uint16_t C_CYAN_GLOW         = 0xA79F; // #A5F3FC Hào quang lam ngọc rực sáng
  const uint16_t C_CYAN_BRIGHT       = 0x269D; // #22D3EE Sọc dạ quang cyan cổ & ngực
  const uint16_t C_CYAN_CORE         = 0x05BA; // #06B6D4 Mắt hình thoi lam ngọc phát sáng
  const uint16_t C_CYAN_DARK         = 0x0BB2; // #0E7490 Viền hốc mắt lam ngọc đậm
  const uint16_t C_HORN_TIP_WHITE    = 0xFFFF; // #FFFFFF Đỉnh chóp kim tiêm men sứ bắt sáng
  const uint16_t C_HORN_STEM         = 0xEEBF; // #E9D5FF Thân kim tiêm ngọc lam tím nhạt
  const uint16_t C_BLUSH_PINK        = 0xF1EB; // #F43F5E Đôi má ửng hồng tím ngộ nghĩnh
  const uint16_t C_MOUTH_DEEP        = 0x4823; // #4C0519 Nụ cười chữ V tinh nghịch
  const uint16_t C_CONTACT_SHADOW    = 0x18C9; // #1E1B4B Bóng tiếp xúc không gian mờ ảo
  const uint16_t C_WHITE             = 0xFFFF; // #FFFFFF Điểm bắt sáng pha lê

  // 3. LAYER 0: BÓNG TIẾP XÚC MỜ ẢO CO GIÃN NHỊP NHÀNG (Dynamic Ambient Occlusion Ground Shadow)
  int groundY  = cy + 42;
  int shadowRx = (int)((26.0f - breathSin * 3.0f) * sX);
  int shadowRy = (int)(5.5f - breathSin * 0.8f);
  spr->fillEllipse(cx, groundY, shadowRx + 4, shadowRy + 1, C_CONTACT_SHADOW);
  spr->fillEllipse(cx, groundY, shadowRx, shadowRy, 0x10A4);

  // 4. LAYER 1: BỌT ĐỘC DẠ QUANG LI TI PHÁT SÁNG BỒNG BỀNH (Bioluminescent Poison Plasma Droplets)
  const int dropletOffsets[6][2] = {
    {-32, -22}, {34, -18}, {-38, 14}, {36, 20}, {-20, -42}, {24, -46}
  };
  const float dropletPhases[6] = {0.0f, 1.2f, 2.4f, 3.6f, 4.8f, 5.5f};
  for (int b = 0; b < 6; b++) {
    float bLag = breathPhase * 0.8f + dropletPhases[b];
    int bx = cx + dropletOffsets[b][0] + (int)(cosf(bLag) * 3.0f);
    int bby = cy + dropletOffsets[b][1] + (int)(sinf(bLag) * 3.5f);
    int br = (b % 2 == 0) ? 3 : 2;
    spr->drawCircle(bx, bby, br, C_CYAN_GLOW);
    spr->fillCircle(bx, bby, br - 1, C_CYAN_BRIGHT);
    spr->drawPixel(bx, bby, C_WHITE);
  }

  // 5. LAYER 2: CHIẾC ĐUÔI NHỎ NGOE NGUẨY VUI VẺ (Playful Wagging Alien Tail)
  int tRootX = cx + (int)(4 * sX);
  int tRootY = by + (int)(16 * sY);
  int tMidX  = cx + (int)(22 * sX) + tailSway;
  int tMidY  = by + (int)(22 * sY);
  int tPeakX = cx + (int)(32 * sX) + (int)(tailSway * 1.2f);
  int tPeakY = by + (int)(32 * sY);
  int tTipX  = cx + (int)(34 * sX) + (int)(tailSway * 1.5f);
  int tTipY  = by + (int)(44 * sY);

  // Thân đuôi uốn lượn dày dặn
  spr->fillTriangle(tRootX, tRootY - 2, tMidX, tMidY - 3, tRootX, tRootY + 4, C_BODY_DARK);
  spr->fillTriangle(tMidX, tMidY - 3, tPeakX, tPeakY - 2, tMidX, tMidY + 3, C_BODY_DARK);
  spr->fillTriangle(tPeakX, tPeakY - 2, tTipX, tTipY, tPeakX, tPeakY + 2, C_BODY_SHADOW);

  // Vây gai nhỏ nhô trên sống đuôi (Dorsal Tail Fin)
  spr->fillTriangle(tMidX - 2, tMidY - 2, tMidX + 4, tMidY - 8, tMidX + 6, tMidY - 1, C_BODY_DARK);
  spr->drawLine(tMidX - 2, tMidY - 2, tMidX + 4, tMidY - 8, C_FRESNEL_LAVENDER);

  // Viền sống đuôi đón sáng Fresnel
  spr->drawLine(tRootX, tRootY - 2, tMidX, tMidY - 3, C_HEAD_PURPLE);
  spr->drawLine(tMidX, tMidY - 3, tPeakX, tPeakY - 2, C_HEAD_PURPLE);
  spr->drawLine(tPeakX, tPeakY - 2, tTipX, tTipY, C_MAGENTA_CORE);

  // Chóp đuôi màu hồng fuchsia vuốt nhọn xinh xắn với đốm cyan phát quang
  spr->fillTriangle(tPeakX, tPeakY + 1, tTipX, tTipY, tTipX - 2, tTipY + 4, C_MAGENTA_CORE);
  spr->drawPixel(tTipX, tTipY, C_CYAN_BRIGHT);

  // 6. LAYER 3: ĐÔI CHÂN NHỎ MŨM MĨM & KHỐI THÂN TÍM ĐẬM (Chubby Legs & Tiny Purple Body)
  // Chân trái (viewer's left)
  spr->fillRoundRect(cx - (int)(11 * sX), by + 19, (int)(8 * sX), (int)(12 * sY), 4, C_BODY_DARK);
  spr->fillCircle(cx - (int)(7 * sX), by + 28, (int)(3 * sX), C_HEAD_PURPLE_DARK);
  spr->drawPixel(cx - (int)(7 * sX), by + 29, C_FRESNEL_LAVENDER);

  // Chân phải (viewer's right)
  spr->fillRoundRect(cx + (int)(3 * sX), by + 19, (int)(8 * sX), (int)(12 * sY), 4, C_BODY_DARK);
  spr->fillCircle(cx + (int)(7 * sX), by + 28, (int)(3 * sX), C_HEAD_PURPLE_DARK);
  spr->drawPixel(cx + (int)(7 * sX), by + 29, C_FRESNEL_LAVENDER);

  // Khối thân tím đậm nhỏ bé mũm mĩm (Tiny Chubby Torso)
  int bRy = (int)(14 * sY);
  int bRx = (int)(14 * sX);
  spr->fillEllipse(cx, by + 11, bRx + 1, bRy + 1, C_HEAD_PURPLE_DARK);
  spr->fillEllipse(cx, by + 11, bRx, bRy, C_BODY_DARK);
  spr->fillEllipse(cx, by + 13, (int)(10 * sX), (int)(8 * sY), C_BODY_SHADOW);
  spr->fillEllipse(cx - (int)(4 * sX), by + 8, (int)(6 * sX), (int)(5 * sY), C_HEAD_PURPLE);

  // 7. LAYER 4: VỆT SỌC DẠ QUANG CYAN NỔI BẬT QUANH CỔ VÀ NGỰC & YẾM MAGENTA
  int chestY = by + 5;
  spr->fillTriangle(cx - (int)(7 * sX), chestY, cx + (int)(7 * sX), chestY, cx, chestY + (int)(8 * sY), C_MAGENTA_CORE);
  spr->fillTriangle(cx - (int)(5 * sX), chestY, cx + (int)(5 * sX), chestY, cx, chestY + (int)(6 * sY), C_MAGENTA_LIGHT);

  // Sọc dạ quang cyan nổi bật
  spr->drawLine(cx - (int)(8 * sX), chestY - 1, cx, chestY + (int)(9 * sY), C_CYAN_BRIGHT);
  spr->drawLine(cx + (int)(8 * sX), chestY - 1, cx, chestY + (int)(9 * sY), C_CYAN_BRIGHT);
  spr->drawLine(cx - (int)(9 * sX), chestY - 1, cx, chestY + (int)(10 * sY), C_CYAN_GLOW);
  spr->drawLine(cx + (int)(9 * sX), chestY - 1, cx, chestY + (int)(10 * sY), C_CYAN_GLOW);
  spr->drawFastHLine(cx - (int)(7 * sX), chestY - 2, (int)(14 * sX), C_CYAN_BRIGHT);
  spr->drawPixel(cx, chestY + (int)(9 * sY), C_WHITE);

  // 8. LAYER 5: TỨ CHI TÍ HON ĐÁNG YÊU (Tiny Playful Arms)
  // Tay phải (viewer's right)
  int armRx1 = cx + (int)(9 * sX),  armRy1 = by + 7;
  int armRx2 = cx + (int)(22 * sX), armRy2 = by + 9 + (int)(sinf(breathPhase) * 2.0f);
  spr->fillTriangle(armRx1, armRy1 - 3, armRx1, armRy1 + 3, armRx2, armRy2, C_BODY_DARK);
  spr->fillCircle(armRx2, armRy2, 2, C_HEAD_PURPLE);
  spr->drawLine(armRx1, armRy1 - 3, armRx2, armRy2, C_FRESNEL_LAVENDER);

  // Tay trái (viewer's left - giơ lên má)
  int armLx1 = cx - (int)(8 * sX),  armLy1 = by + 7;
  int armLx2 = cx - (int)(15 * sX), armLy2 = by + 2;
  int armLx3 = cx - (int)(12 * sX), armLy3 = by - 3;
  spr->fillTriangle(armLx1, armLy1 - 2, armLx2, armLy2, armLx1, armLy1 + 3, C_BODY_DARK);
  spr->fillTriangle(armLx2, armLy2 - 2, armLx3, armLy3, armLx2, armLy2 + 2, C_BODY_DARK);
  spr->fillCircle(armLx3, armLy3, 2, C_HEAD_PURPLE);
  spr->drawPixel(armLx3, armLy3 - 1, C_FRESNEL_LAVENDER);

  // 9. LAYER 6: ĐẦU TO TRÒN PHÚNG PHÍNH MÀU TÍM OẢI HƯƠNG PASTEL (Chubby Lavender Head)
  int hy = by - 16;
  int hRy = (int)(25 * sY);
  int hRx = (int)(27 * sX);

  spr->fillEllipse(cx, hy, hRx + 2, hRy + 2, C_FRESNEL_LAVENDER);
  spr->fillEllipse(cx, hy, hRx, hRy, C_HEAD_PURPLE);
  spr->fillEllipse(cx, hy - (int)(3 * sY), (int)(24 * sX), (int)(19 * sY), C_HEAD_PASTEL_MID);
  spr->fillEllipse(cx - (int)(7 * sX), hy - (int)(9 * sY), (int)(15 * sX), (int)(9 * sY), C_HEAD_PASTEL_LIGHT);

  // Múi giáp đầu bên hông
  spr->fillTriangle(cx - (int)(25 * sX), hy + (int)(5 * sY), cx - (int)(32 * sX), hy - (int)(6 * sY), cx - (int)(20 * sX), hy - (int)(14 * sY), C_HEAD_PURPLE_DARK);
  spr->fillTriangle(cx + (int)(25 * sX), hy + (int)(5 * sY), cx + (int)(32 * sX), hy - (int)(6 * sY), cx + (int)(20 * sX), hy - (int)(14 * sY), C_HEAD_PURPLE_DARK);
  spr->drawLine(cx - (int)(25 * sX), hy + (int)(5 * sY), cx - (int)(32 * sX), hy - (int)(6 * sY), C_FRESNEL_LAVENDER);
  spr->drawLine(cx + (int)(25 * sX), hy + (int)(5 * sY), cx + (int)(32 * sX), hy - (int)(6 * sY), C_FRESNEL_LAVENDER);

  // Vành mũ chóp đầu màu hồng magenta
  spr->fillEllipse(cx, hy - (int)(18 * sY), (int)(15 * sX), (int)(7 * sY), C_MAGENTA_DEEP);
  spr->fillEllipse(cx, hy - (int)(19 * sY), (int)(14 * sX), (int)(6 * sY), C_MAGENTA_CORE);
  spr->fillEllipse(cx - (int)(4 * sX), hy - (int)(20 * sY), (int)(7 * sX), (int)(3 * sY), C_MAGENTA_LIGHT);

  // Kim cương magenta trán
  int fX = cx, fY = hy - (int)(8 * sY);
  spr->fillTriangle(fX, fY - (int)(9 * sY), fX - (int)(5 * sX), fY, fX + (int)(5 * sX), fY, C_MAGENTA_CORE);
  spr->fillTriangle(fX, fY + (int)(8 * sY), fX - (int)(5 * sX), fY, fX + (int)(5 * sX), fY, C_MAGENTA_CORE);
  spr->drawLine(fX, fY - (int)(9 * sY), fX - (int)(5 * sX), fY, C_MAGENTA_LIGHT);
  spr->drawLine(fX, fY - (int)(9 * sY), fX + (int)(5 * sX), fY, C_MAGENTA_LIGHT);
  spr->drawPixel(fX, fY, C_WHITE);

  // Rãnh phân múi giáp
  spr->drawLine(cx - (int)(7 * sX), hy - (int)(16 * sY), cx - (int)(16 * sX), hy - (int)(4 * sY), C_HELMET_DEEP);
  spr->drawLine(cx + (int)(7 * sX), hy - (int)(16 * sY), cx + (int)(16 * sX), hy - (int)(4 * sY), C_HELMET_DEEP);

  // 10. LAYER 7: 3 CHIẾC KIM TIÊM / SỪNG NGỌC LAM CYAN PHÁT QUANG (Lag 0.45 rad)
  // Sừng giữa đỉnh đầu
  int s0BaseX = cx, s0BaseY = hy - (int)(23 * sY);
  int s0TipX  = cx + (int)(hornSwayX * 0.7f);
  int s0TipY  = hy - (int)(46 * sY) + hornSwayY;

  spr->fillTriangle(s0BaseX - 3, s0BaseY, s0BaseX + 3, s0BaseY, s0TipX, s0TipY, C_HORN_STEM);
  spr->drawLine(s0BaseX, s0BaseY, s0TipX, s0TipY, C_FRESNEL_LAVENDER);
  spr->fillCircle(s0TipX, s0TipY, 4, C_CYAN_GLOW);
  spr->fillCircle(s0TipX, s0TipY, 2, C_CYAN_BRIGHT);
  spr->drawPixel(s0TipX, s0TipY - 1, C_HORN_TIP_WHITE);

  // Sừng trái
  int sLBaseX = cx - (int)(23 * sX), sLBaseY = hy - (int)(10 * sY);
  int sLTipX  = cx - (int)(38 * sX) + hornSwayX;
  int sLTipY  = hy - (int)(26 * sY) + hornSwayY;

  spr->fillCircle(sLBaseX, sLBaseY, 4, C_MAGENTA_CORE);
  spr->fillCircle(sLBaseX - 1, sLBaseY - 1, 2, C_MAGENTA_LIGHT);
  spr->fillTriangle(sLBaseX, sLBaseY - 2, sLBaseX, sLBaseY + 2, sLTipX, sLTipY, C_HORN_STEM);
  spr->drawLine(sLBaseX, sLBaseY - 2, sLTipX, sLTipY, C_FRESNEL_LAVENDER);
  spr->fillCircle(sLTipX, sLTipY, 3, C_CYAN_GLOW);
  spr->fillCircle(sLTipX, sLTipY, 2, C_CYAN_BRIGHT);
  spr->drawPixel(sLTipX, sLTipY, C_HORN_TIP_WHITE);

  // Sừng phải
  int sRBaseX = cx + (int)(23 * sX), sRBaseY = hy - (int)(10 * sY);
  int sRTipX  = cx + (int)(38 * sX) + hornSwayX;
  int sRTipY  = hy - (int)(26 * sY) + hornSwayY;

  spr->fillCircle(sRBaseX, sRBaseY, 4, C_MAGENTA_CORE);
  spr->fillCircle(sRBaseX + 1, sRBaseY - 1, 2, C_MAGENTA_LIGHT);
  spr->fillTriangle(sRBaseX, sRBaseY - 2, sRBaseX, sRBaseY + 2, sRTipX, sRTipY, C_HORN_STEM);
  spr->drawLine(sRBaseX, sRBaseY - 2, sRTipX, sRTipY, C_FRESNEL_LAVENDER);
  spr->fillCircle(sRTipX, sRTipY, 3, C_CYAN_GLOW);
  spr->fillCircle(sRTipX, sRTipY, 2, C_CYAN_BRIGHT);
  spr->drawPixel(sRTipX, sRTipY, C_HORN_TIP_WHITE);

  // 11. LAYER 8: MẶT NẠ MẮT HỒNG MAGENTA & ĐÔI MÁ HỒNG TÍM
  int maskY = hy + 2;
  spr->fillEllipse(cx, maskY, (int)(18 * sX), (int)(8 * sY), C_MAGENTA_CORE);
  spr->fillEllipse(cx, maskY - 1, (int)(16 * sX), (int)(6 * sY), C_MAGENTA_LIGHT);

  spr->fillEllipse(cx - (int)(19 * sX), hy + 7, 4, 3, C_BLUSH_PINK);
  spr->fillEllipse(cx + (int)(19 * sX), hy + 7, 4, 3, C_BLUSH_PINK);

  // 12. LAYER 9: ĐÔI MẮT HÌNH THOI MÀU LAM NGỌC PHÁT SÁNG NGỘ NGHĨNH
  int eyeY  = hy + 1;
  int eyeXL = cx - (int)(11 * sX);
  int eyeXR = cx + (int)(11 * sX);

  if (blink) {
    spr->drawLine(eyeXL - 6, eyeY, eyeXL, eyeY + 2, C_CYAN_BRIGHT);
    spr->drawLine(eyeXL, eyeY + 2, eyeXL + 6, eyeY - 1, C_CYAN_BRIGHT);
    spr->drawLine(eyeXL - 6, eyeY - 1, eyeXL, eyeY + 1, C_CYAN_GLOW);

    spr->drawLine(eyeXR - 6, eyeY - 1, eyeXR, eyeY + 2, C_CYAN_BRIGHT);
    spr->drawLine(eyeXR, eyeY + 2, eyeXR + 6, eyeY, C_CYAN_BRIGHT);
    spr->drawLine(eyeXR + 1, eyeY + 1, eyeXR + 6, eyeY - 1, C_CYAN_GLOW);
  } else {
    // Mắt trái
    int xl1 = eyeXL,            yl1 = eyeY - 6;
    int xl2 = eyeXL + 6,        yl2 = eyeY - 1;
    int xl3 = eyeXL,            yl3 = eyeY + 5;
    int xl4 = eyeXL - 7,        yl4 = eyeY - 1;

    spr->fillTriangle(xl1, yl1, xl2, yl2, xl4, yl4, C_CYAN_DARK);
    spr->fillTriangle(xl3, yl3, xl2, yl2, xl4, yl4, C_CYAN_DARK);
    spr->fillTriangle(xl1 + 1, yl1 + 1, xl2 - 1, yl2, xl4 + 1, yl4, C_CYAN_CORE);
    spr->fillTriangle(xl3, yl3 - 1, xl2 - 1, yl2, xl4 + 1, yl4, C_CYAN_BRIGHT);

    spr->fillCircle(eyeXL - 1, eyeY - 2, 2, C_WHITE);
    spr->drawPixel(eyeXL + 2, eyeY + 2, C_CYAN_GLOW);

    // Mắt phải
    int xr1 = eyeXR,            yr1 = eyeY - 6;
    int xr2 = eyeXR + 7,        yr2 = eyeY - 1;
    int xr3 = eyeXR,            yr3 = eyeY + 5;
    int xr4 = eyeXR - 6,        yr4 = eyeY - 1;

    spr->fillTriangle(xr1, yr1, xr2, yr2, xr4, yr4, C_CYAN_DARK);
    spr->fillTriangle(xr3, yr3, xr2, yr2, xr4, yr4, C_CYAN_DARK);
    spr->fillTriangle(xr1 - 1, yr1 + 1, xr2 - 1, yr2, xr4 + 1, yr4, C_CYAN_CORE);
    spr->fillTriangle(xr3, yr3 - 1, xr2 - 1, yr2, xr4 + 1, yr4, C_CYAN_BRIGHT);

    spr->fillCircle(eyeXR - 1, eyeY - 2, 2, C_WHITE);
    spr->drawPixel(eyeXR + 2, eyeY + 2, C_CYAN_GLOW);
  }

  // 13. LAYER 10: MIỆNG CƯỜI CHỮ V TINH NGHỊCH (Mischievous V-Smile)
  int mY = hy + 8;
  spr->fillTriangle(cx - 4, mY, cx + 4, mY, cx, mY + 4, C_MOUTH_DEEP);
  spr->drawLine(cx - 4, mY, cx, mY + 4, C_CYAN_BRIGHT);
  spr->drawLine(cx, mY + 4, cx + 4, mY, C_CYAN_BRIGHT);
}

static void drawPoipoleAdhesiveAlien(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  (void)breath;
  (void)scale;
  bool blink = (fmodf(angle, 3.5f) < 0.14f);
  drawPoipoleAdhesiveAlien(spr, cx, cy, angle, blink);
}

} // namespace Session2Mythics
