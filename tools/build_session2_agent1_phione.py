# -*- coding: utf-8 -*-
import json
import os

def hex_to_rgb565(hex_str):
    hex_str = hex_str.lstrip('#')
    r = int(hex_str[0:2], 16)
    g = int(hex_str[2:4], 16)
    b = int(hex_str[4:6], 16)
    rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
    return f"0x{rgb565:04X}"

def create_color(name, hex_code, optical_function):
    return {
        "name": name,
        "hex": hex_code,
        "rgb565": hex_to_rgb565(hex_code),
        "optical_function": optical_function
    }

cpp_code = """// =========================================================================
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
}"""

js_code = """// =========================================================================
// PHIONE - GIỌT NƯỚC BIỂN TRÔI DẠT (MYTHIC PHIONE SEA DRIFTER)
// Pop Mart / High-End Vinyl Collectible Art - Modern HTML5 Canvas 2D
// =========================================================================

function drawMythicPhione(ctx, cx, cy, scale, t, forceBlink = false) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.scale(scale, scale);

  // 1. Nhịp bơi lơ lửng đại dương Squash & Stretch 5%
  const breathFreq = 2.0;
  const breathPhase = t * breathFreq;
  const sY = 1.0 + 0.05 * Math.sin(breathPhase);
  const sX = 1.0 - 0.025 * Math.sin(breathPhase);
  const by = Math.sin(breathPhase) * 3.5;
  const blink = forceBlink || ((t % 3.5) < 0.14);

  // 2. Bóng tiếp xúc mờ ảo đáy biển (Soft Contact Shadow)
  ctx.save();
  const shadowY = 56;
  const shadowRx = (26.0 + 2.0 * Math.sin(breathPhase)) * sX;
  const shadowGrad = ctx.createRadialGradient(-2, shadowY, 3, -2, shadowY, shadowRx);
  shadowGrad.addColorStop(0, 'rgba(4, 30, 52, 0.50)');
  shadowGrad.addColorStop(0.6, 'rgba(4, 30, 52, 0.22)');
  shadowGrad.addColorStop(1, 'rgba(4, 30, 52, 0)');
  ctx.fillStyle = shadowGrad;
  ctx.beginPath();
  ctx.ellipse(-2, shadowY, shadowRx, 6.5, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 3. Bọt nước ngân hà li ti phát sáng (Bioluminescent Galaxy Bubbles)
  const bubbleDefs = [
    { x: -48, y: -30, r: 3.0, phase: 0.0 },
    { x: 42,  y: -24, r: 2.6, phase: 1.1 },
    { x: -52, y: 14,  r: 2.2, phase: 2.3 },
    { x: 48,  y: 22,  r: 2.8, phase: 3.5 },
    { x: -24, y: -52, r: 1.8, phase: 4.7 },
    { x: 30,  y: -56, r: 2.4, phase: 5.4 }
  ];
  bubbleDefs.forEach(b => {
    const bLag = breathPhase * 0.8 + b.phase;
    const bx = b.x + Math.cos(bLag) * 3.0;
    const by_pos = b.y + Math.sin(bLag) * 4.0;
    ctx.save();
    ctx.shadowColor = '#7DD3FC';
    ctx.shadowBlur = 8;
    ctx.fillStyle = 'rgba(125, 211, 252, 0.35)';
    ctx.strokeStyle = 'rgba(255, 255, 255, 0.85)';
    ctx.lineWidth = 0.9;
    ctx.beginPath();
    ctx.arc(bx, by_pos, b.r, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();

    ctx.fillStyle = '#FFFFFF';
    ctx.beginPath();
    ctx.arc(bx - b.r * 0.35, by_pos - b.r * 0.35, b.r * 0.3, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  });

  // Tọa độ đầu & phao
  const hy = by - 8;
  const buoyX = -4 * sX;
  const buoyY = hy - 20 * sY;

  // 4. DẢI RUY BĂNG ĐUÔI DÀI MỀM MẠI (Ribbon Tail - Trễ pha Delta Phi = 0.45 rad)
  const ribLag = breathPhase - 0.45;
  const sway1 = Math.sin(ribLag) * 4.0;
  const sway2 = Math.cos(ribLag) * 5.0;
  const sway3 = Math.sin(ribLag + 0.5) * 6.0;
  const sway4 = Math.cos(ribLag + 0.8) * 7.0;

  // Trục xương sống ruy băng:
  const p0 = { x: buoyX, y: buoyY - 3 };
  const p1 = { x: buoyX + 8 + sway1 * 0.4, y: buoyY - 16 };
  const p2 = { x: buoyX + 24 + sway2 * 0.6, y: buoyY - 14 };
  const p3 = { x: buoyX + 46 + sway3 * 0.8, y: buoyY + 6 };
  const p4 = { x: buoyX + 70 + sway4, y: buoyY + 34 };
  const p5 = { x: buoyX + 90 + sway4 * 1.2, y: buoyY + 58 };

  ctx.save();
  ctx.lineCap = 'round';
  ctx.lineJoin = 'round';

  // Lớp bóng dưới ruy băng
  ctx.lineWidth = 11;
  ctx.strokeStyle = 'rgba(2, 132, 199, 0.45)';
  ctx.beginPath();
  ctx.moveTo(p0.x, p0.y);
  ctx.bezierCurveTo(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
  ctx.bezierCurveTo(p3.x + 12, p3.y + 14, p4.x - 6, p4.y - 10, p5.x, p5.y);
  ctx.stroke();

  // Thân ruy băng chuyển sắc
  const ribGrad = ctx.createLinearGradient(p0.x, p0.y, p5.x, p5.y);
  ribGrad.addColorStop(0, '#22D3EE');
  ribGrad.addColorStop(0.4, '#38BDF8');
  ribGrad.addColorStop(0.8, '#67E8F9');
  ribGrad.addColorStop(1, '#A5F3FC');

  ctx.lineWidth = 9;
  ctx.strokeStyle = ribGrad;
  ctx.beginPath();
  ctx.moveTo(p0.x, p0.y);
  ctx.bezierCurveTo(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
  ctx.bezierCurveTo(p3.x + 12, p3.y + 14, p4.x - 6, p4.y - 10, p5.x, p5.y);
  ctx.stroke();

  // Viền men sứ lóa sáng ruy băng
  ctx.lineWidth = 1.4;
  ctx.strokeStyle = 'rgba(208, 248, 255, 0.85)';
  ctx.beginPath();
  ctx.moveTo(p0.x, p0.y - 3);
  ctx.bezierCurveTo(p1.x, p1.y - 3, p2.x, p2.y - 3, p3.x, p3.y - 3);
  ctx.bezierCurveTo(p3.x + 12, p3.y + 11, p4.x - 6, p4.y - 13, p5.x, p5.y - 3);
  ctx.stroke();

  // Chóp đuôi chẻ 2 thùy V-notch cá tính (Notched Swallowtail)
  const tipX = p5.x;
  const tipY = p5.y;
  ctx.fillStyle = '#67E8F9';
  ctx.strokeStyle = '#D0F8FF';
  ctx.lineWidth = 1.2;
  ctx.beginPath();
  ctx.moveTo(tipX - 4, tipY - 5);
  ctx.lineTo(tipX + 8, tipY - 4);
  ctx.lineTo(tipX + 3, tipY + 1);
  ctx.lineTo(tipX + 9, tipY + 7);
  ctx.lineTo(tipX - 3, tipY + 5);
  ctx.closePath();
  ctx.fill();
  ctx.stroke();
  ctx.restore();

  // 5. HAI TAY BƠI NGẮN TRÒN XÒE NGANG (Swimming Paddle Flippers)
  const finLag = breathPhase - 0.35;
  const finFlutterL = Math.sin(finLag) * 3.5;
  const finFlutterR = Math.sin(finLag + 0.2) * 3.5;

  // Tay bơi phải
  ctx.save();
  const rFinX1 = 4 * sX, rFinY1 = by + 6;
  const rFinX2 = 28 * sX, rFinY2 = by + 8 + finFlutterR;
  const rFinX3 = 46 * sX, rFinY3 = by + 12 + finFlutterR;

  const finRGrad = ctx.createLinearGradient(rFinX1, rFinY1, rFinX3, rFinY3);
  finRGrad.addColorStop(0, '#0284C7');
  finRGrad.addColorStop(0.5, '#38BDF8');
  finRGrad.addColorStop(1, '#7DD3FC');
  ctx.fillStyle = finRGrad;
  ctx.beginPath();
  ctx.moveTo(rFinX1, rFinY1 - 4);
  ctx.quadraticCurveTo(rFinX2, rFinY2 - 6, rFinX3, rFinY3);
  ctx.arc(rFinX3, rFinY3 + 3, 5.0, -Math.PI * 0.4, Math.PI * 0.4);
  ctx.quadraticCurveTo(rFinX2, rFinY2 + 8, rFinX1, rFinY1 + 5);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = 'rgba(208, 248, 255, 0.7)';
  ctx.lineWidth = 1.1;
  ctx.stroke();
  ctx.restore();

  // Tay bơi trái
  ctx.save();
  const lFinX1 = -8 * sX, lFinY1 = by + 7;
  const lFinX2 = -26 * sX, lFinY2 = by + 17 + finFlutterL;
  const lFinX3 = -38 * sX, lFinY3 = by + 26 + finFlutterL;

  const finLGrad = ctx.createLinearGradient(lFinX1, lFinY1, lFinX3, lFinY3);
  finLGrad.addColorStop(0, '#0369A1');
  finLGrad.addColorStop(0.4, '#38BDF8');
  finLGrad.addColorStop(1, '#67E8F9');
  ctx.fillStyle = finLGrad;
  ctx.beginPath();
  ctx.moveTo(lFinX1, lFinY1 - 3);
  ctx.quadraticCurveTo(lFinX2, lFinY2 - 5, lFinX3, lFinY3);
  ctx.arc(lFinX3 + 2, lFinY3 + 3, 5.2, -Math.PI * 0.6, Math.PI * 0.5);
  ctx.quadraticCurveTo(lFinX2 + 4, lFinY2 + 7, lFinX1, lFinY1 + 6);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = 'rgba(208, 248, 255, 0.75)';
  ctx.lineWidth = 1.2;
  ctx.stroke();
  ctx.restore();

  // 6. THÂN GIỌT NƯỚC BÁN TRONG SUỐT & ĐUÔI NHỌN NÚNG NÍNH
  ctx.save();
  const torsoGrad = ctx.createRadialGradient(-3 * sX, by + 8, 2, -1 * sX, by + 13, 16 * sY);
  torsoGrad.addColorStop(0, '#7DD3FC');
  torsoGrad.addColorStop(0.5, '#38BDF8');
  torsoGrad.addColorStop(0.85, '#0284C7');
  torsoGrad.addColorStop(1, '#0369A1');
  ctx.fillStyle = torsoGrad;

  ctx.beginPath();
  ctx.moveTo(-10 * sX, by + 7);
  ctx.quadraticCurveTo(-14 * sX, by + 17, -2 * sX, by + 28 * sY);
  ctx.quadraticCurveTo(10 * sX, by + 17, 8 * sX, by + 7);
  ctx.closePath();
  ctx.fill();

  ctx.strokeStyle = '#D0F8FF';
  ctx.lineWidth = 1.3;
  ctx.stroke();

  ctx.fillStyle = 'rgba(255, 255, 255, 0.65)';
  ctx.beginPath();
  ctx.ellipse(-5 * sX, by + 16, 2.5, 1.8, -0.25, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 7. VIÊN HỒNG NGỌC RUBY ĐỎ RỰC TRƯỚC NGỰC
  const gemX = -1 * sX;
  const gemY = by + 10;
  ctx.save();
  ctx.fillStyle = '#F59E0B';
  ctx.beginPath();
  ctx.ellipse(gemX, gemY, 6.5, 8.5, 0, 0, Math.PI * 2);
  ctx.fill();

  ctx.fillStyle = '#FEF08A';
  const bezelPoints = [
    { x: gemX, y: gemY - 7.5 },
    { x: gemX, y: gemY + 7.5 },
    { x: gemX - 5.5, y: gemY },
    { x: gemX + 5.5, y: gemY }
  ];
  bezelPoints.forEach(pt => {
    ctx.beginPath();
    ctx.arc(pt.x, pt.y, 1.0, 0, Math.PI * 2);
    ctx.fill();
  });

  ctx.shadowColor = 'rgba(220, 38, 38, 0.8)';
  ctx.shadowBlur = 10;
  const rubyGrad = ctx.createRadialGradient(gemX - 1, gemY - 2, 1, gemX, gemY, 6);
  rubyGrad.addColorStop(0, '#FCA5A5');
  rubyGrad.addColorStop(0.25, '#EF4444');
  rubyGrad.addColorStop(0.7, '#DC2626');
  rubyGrad.addColorStop(1, '#991B1B');
  ctx.fillStyle = rubyGrad;
  ctx.beginPath();
  ctx.ellipse(gemX, gemY, 4.8, 6.8, 0, 0, Math.PI * 2);
  ctx.fill();

  ctx.fillStyle = '#FFFFFF';
  ctx.beginPath();
  ctx.arc(gemX - 1.2, gemY - 2.2, 1.2, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 8. ĐẦU NƯỚC GIỌT NƯỚC KHỔNG LỒ & ĐỘ BÓNG MEN SỨ
  ctx.save();
  const headGrad = ctx.createRadialGradient(-7 * sX, hy - 6 * sY, 3, -1 * sX, hy, 25 * sX);
  headGrad.addColorStop(0, '#BAE6FD');
  headGrad.addColorStop(0.35, '#7DD3FC');
  headGrad.addColorStop(0.7, '#38BDF8');
  headGrad.addColorStop(1, '#0284C7');
  ctx.fillStyle = headGrad;
  ctx.beginPath();
  ctx.ellipse(-1 * sX, hy, 24 * sX, 21 * sY, 0, 0, Math.PI * 2);
  ctx.fill();

  ctx.strokeStyle = '#D0F8FF';
  ctx.lineWidth = 1.6;
  ctx.stroke();

  ctx.fillStyle = 'rgba(255, 255, 255, 0.85)';
  ctx.beginPath();
  ctx.ellipse(-11 * sX, hy - 11 * sY, 6.5, 3.2, -0.3, 0, Math.PI * 2);
  ctx.fill();
  ctx.beginPath();
  ctx.arc(10 * sX, hy - 9 * sY, 2.0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 9. PHAO NỔI TRÒN TRÊN ĐỈNH ĐẦU
  ctx.save();
  ctx.fillStyle = '#0284C7';
  ctx.beginPath();
  ctx.ellipse(buoyX, buoyY + 4, 7, 3, 0, 0, Math.PI * 2);
  ctx.fill();

  const buoyGrad = ctx.createRadialGradient(buoyX - 2, buoyY - 2, 2, buoyX, buoyY, 15);
  buoyGrad.addColorStop(0, '#BAE6FD');
  buoyGrad.addColorStop(0.4, '#38BDF8');
  buoyGrad.addColorStop(0.85, '#0284C7');
  buoyGrad.addColorStop(1, '#0369A1');
  ctx.fillStyle = buoyGrad;
  ctx.beginPath();
  ctx.ellipse(buoyX, buoyY, 14 * sX, 7.5 * sY, 0, 0, Math.PI * 2);
  ctx.fill();

  ctx.strokeStyle = '#D0F8FF';
  ctx.lineWidth = 1.3;
  ctx.stroke();

  ctx.fillStyle = '#0284C7';
  ctx.beginPath();
  ctx.ellipse(buoyX, buoyY - 1, 4.5 * sX, 2.2 * sY, 0, 0, Math.PI * 2);
  ctx.fill();

  ctx.fillStyle = 'rgba(255, 255, 255, 0.8)';
  ctx.beginPath();
  ctx.ellipse(buoyX - 4 * sX, buoyY - 3 * sY, 4.0, 1.4, -0.15, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 10. ĐỐM ANTEN TRÁN & CUỐNG NỐI MẮT
  const ey = hy + 2;
  const exL = -13 * sX;
  const exR = 7 * sX;

  ctx.save();
  const dotLX = -14 * sX, dotLY = hy - 6 * sY;
  ctx.strokeStyle = '#0284C7';
  ctx.lineWidth = 1.3;
  ctx.beginPath();
  ctx.moveTo(dotLX, dotLY);
  ctx.lineTo(exL - 1, ey - 7);
  ctx.stroke();

  ctx.fillStyle = '#0284C7';
  ctx.beginPath();
  ctx.arc(dotLX, dotLY, 3.4, 0, Math.PI * 2);
  ctx.fill();
  ctx.fillStyle = '#7DD3FC';
  ctx.beginPath();
  ctx.arc(dotLX - 0.8, dotLY - 0.8, 1.6, 0, Math.PI * 2);
  ctx.fill();

  const dotRX = -2 * sX, dotRY = hy - 7 * sY;
  ctx.beginPath();
  ctx.moveTo(dotRX, dotRY);
  ctx.lineTo(exR - 2, ey - 7);
  ctx.stroke();

  ctx.fillStyle = '#0284C7';
  ctx.beginPath();
  ctx.arc(dotRX, dotRY, 3.4, 0, Math.PI * 2);
  ctx.fill();
  ctx.fillStyle = '#7DD3FC';
  ctx.beginPath();
  ctx.arc(dotRX - 0.8, dotRY - 0.8, 1.6, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 11. VỆT VÀNG MÍ MẮT TRÊN
  ctx.save();
  ctx.strokeStyle = '#FACC15';
  ctx.lineWidth = 1.4;
  ctx.lineCap = 'round';

  ctx.beginPath();
  ctx.arc(exL, ey - 1, 6.0, Math.PI * 1.05, Math.PI * 1.85);
  ctx.stroke();

  ctx.beginPath();
  ctx.arc(exR, ey - 1, 7.0, Math.PI * 1.05, Math.PI * 1.85);
  ctx.stroke();

  ctx.fillStyle = '#FEF08A';
  ctx.beginPath();
  ctx.arc(exL + 4, ey - 6, 1.0, 0, Math.PI * 2);
  ctx.arc(exR + 5, ey - 6.5, 1.0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 12. ĐÔI MẮT PHA LÊ XANH THẲM TO TRÒN
  if (blink) {
    ctx.save();
    ctx.strokeStyle = '#031E3D';
    ctx.lineWidth = 2.4;
    ctx.lineCap = 'round';
    ctx.beginPath();
    ctx.ellipse(exL, ey + 2, 5.5, 2.2, 0, 0, Math.PI);
    ctx.ellipse(exR, ey + 2, 6.5, 2.5, 0, 0, Math.PI);
    ctx.stroke();
    ctx.restore();
  } else {
    const eyeConfigs = [
      { ex: exL, rx: 5.5, ry: 8.5 },
      { ex: exR, rx: 6.8, ry: 9.8 }
    ];
    eyeConfigs.forEach(({ ex, rx, ry }) => {
      ctx.save();
      ctx.fillStyle = '#031E3D';
      ctx.beginPath();
      ctx.ellipse(ex, ey, rx, ry, 0, 0, Math.PI * 2);
      ctx.fill();

      const irisGrad = ctx.createRadialGradient(ex, ey + 3, 1, ex, ey + 1, ry - 1);
      irisGrad.addColorStop(0, '#38BDF8');
      irisGrad.addColorStop(0.5, '#1D4ED8');
      irisGrad.addColorStop(1, '#031E3D');
      ctx.fillStyle = irisGrad;
      ctx.beginPath();
      ctx.ellipse(ex, ey + 1, rx - 1, ry - 1.2, 0, 0, Math.PI * 2);
      ctx.fill();

      ctx.fillStyle = 'rgba(56, 189, 248, 0.75)';
      ctx.beginPath();
      ctx.ellipse(ex, ey + ry * 0.45, rx * 0.65, ry * 0.28, 0, 0, Math.PI * 2);
      ctx.fill();

      ctx.fillStyle = '#021226';
      ctx.beginPath();
      ctx.ellipse(ex - 0.5, ey - 0.5, rx * 0.5, ry * 0.55, 0, 0, Math.PI * 2);
      ctx.fill();

      ctx.fillStyle = '#FFFFFF';
      ctx.beginPath();
      ctx.arc(ex - rx * 0.35, ey - ry * 0.35, 1.8, 0, Math.PI * 2);
      ctx.fill();

      ctx.fillStyle = 'rgba(255, 255, 255, 0.9)';
      ctx.beginPath();
      ctx.arc(ex + rx * 0.35, ey + ry * 0.35, 1.0, 0, Math.PI * 2);
      ctx.fill();

      ctx.fillStyle = 'rgba(255, 255, 255, 0.8)';
      ctx.beginPath();
      ctx.arc(ex + rx * 0.35, ey - ry * 0.25, 0.7, 0, Math.PI * 2);
      ctx.fill();
      ctx.restore();
    });
  }

  // 13. ĐÔI MÁ HỒNG NƯỚC BIỂN & NỤ CƯỜI NGỌT NGÀO
  ctx.save();
  const blushL = ctx.createRadialGradient(exL - 4, hy + 8, 1, exL - 4, hy + 8, 4.5);
  blushL.addColorStop(0, 'rgba(251, 113, 133, 0.75)');
  blushL.addColorStop(1, 'rgba(251, 113, 133, 0)');
  ctx.fillStyle = blushL;
  ctx.beginPath();
  ctx.ellipse(exL - 4, hy + 8, 4.5, 3.0, 0, 0, Math.PI * 2);
  ctx.fill();

  const blushR = ctx.createRadialGradient(exR + 5, hy + 8, 1, exR + 5, hy + 8, 4.5);
  blushR.addColorStop(0, 'rgba(251, 113, 133, 0.75)');
  blushR.addColorStop(1, 'rgba(251, 113, 133, 0)');
  ctx.fillStyle = blushR;
  ctx.beginPath();
  ctx.ellipse(exR + 5, hy + 8, 4.5, 3.0, 0, 0, Math.PI * 2);
  ctx.fill();

  ctx.strokeStyle = '#0C4A6E';
  ctx.lineWidth = 1.3;
  ctx.lineCap = 'round';
  ctx.beginPath();
  ctx.arc(-3 * sX, hy + 8, 4.0, 0.15, Math.PI * 0.85);
  ctx.stroke();
  ctx.restore();

  ctx.restore();
}"""

data = {
  "character_profile": {
    "id": 6,
    "global_smart_keychain_id": 55,
    "codename": "MYTHIC_PHIONE_SEA_DRIFTER",
    "name_vi": "Phione - Giọt Nước Biển Trôi Dạt",
    "name_en": "Mythic Phione - Sea Drifter",
    "japanese_name": "フィオネ (Phione)",
    "pokedex_number": 489,
    "species": "Kaiyū Pokémon (Linh Thú Hải Du / Bé Cưng Phiêu Bạt Biển Ấm)",
    "archetype": "Linh Thú Biển Sâu Thần Thoại / Pop Mart Vinyl Nghệ Thuật Cao Cấp",
    "source_art_reference": "06_Mythic_Phione_Sea_Drifter.png",
    "designer_toy_series": "Mythic Ocean Pop Mart / Vinyl High-End Collectible 3D Series",
    "mythology_lore": "Sinh linh bé nhỏ huyền bí trôi dạt theo những dòng hải lưu ấm áp khắp năm châu bốn biển. Trên đỉnh đầu Phione ngự trị một chiếc phao cứu sinh tròn phồng tựa viên kẹo biển, giúp em tự do bềnh bồng ngắm nhìn bầu trời xanh thẳm. Dải ruy băng đuôi dài mềm mại uốn lượn như vũ điệu của sóng nước, cùng viên hồng ngọc Ruby đỏ rực đính trước ngực kết tinh từ tình yêu thuần khiết của lòng đại dương bao la.",
    "inspirational_quotes": {
      "vi": "Hãy thả lỏng tâm hồn và trôi dạt nhẹ nhàng cùng những con sóng hiền hòa, bình yên sẽ tự tìm đến bên bạn.",
      "en": "Drift gently with the ocean currents; peace and wonder will naturally find their way to your heart."
    },
    "sculpture_aesthetic_spec": {
      "finish_quality": "High-End Pop Mart / Porcelain Glazed Vinyl Collectible Toy (Men sứ bóng nano & Vinyl cao cấp)",
      "body_material": "Thân giọt nước xanh lam ngọc trong suốt (Water droplet body) với độ bóng men sứ phủ nano và hiệu ứng tán xạ ánh sáng dưới bề mặt SSS (Subsurface Scattering)",
      "buoy_crown": "Phao nổi tròn phồng to trên đỉnh đầu tựa viên kẹo biển / phao cứu sinh (Flotation Buoy Cushion) với tâm lõm sâu và gờ cổ chân phao đón sáng",
      "ribbon_tail": "Dải ruy băng đuôi dài mềm mại rủ xuống từ phao đầu, uốn lượn hình sóng biển S-Curve trễ pha Delta Phi = 0.45 rad và chóp đuôi chẻ 2 thùy đuôi cá V-notch",
      "chest_ruby": "Viên hồng ngọc Ruby đỏ rực hình bầu dục đính viền chạm khắc hoàng kim (Gilded Solar Ruby Core) kiêu sa đón sáng",
      "ocean_crystal_eyes": "Đôi mắt pha lê xanh lam thẳm 3 điểm bắt sáng vật lý (Keylight 10h, Caustic bounce 4h, Micro twinkle), vệt vàng mí mắt trên và 2 đốm anten trán nối cuống xuống viền mắt theo đúng 100% nguyên tác",
      "paddle_flippers": "Hai tay bơi ngắn tròn xòe ngang như đôi vây cá nhỏ màng mỏng vẫy nhịp nhàng đón luồng nước",
      "seabed_shadow": "Bóng tiếp xúc mờ ảo đáy biển (Ambient Occlusion Contact Shadow) co giãn tương tác theo cao độ lơ lửng"
    }
  },
  "palette": [
    create_color("C_FRESNEL_RIM", "#CCFBF1", "Viền men sứ xanh ngọc băng lóa sáng ngoài cùng (Fresnel Rim)"),
    create_color("C_BODY_CYAN", "#22D3EE", "Thân ngọc lam đại dương bán trong suốt chính"),
    create_color("C_BODY_LIGHT", "#67E8F9", "Vùng phản quang sáng khoang thể dịch bên trong"),
    create_color("C_BODY_CORE_SSS", "#0284C7", "Lõi tán xạ ánh sáng dưới bề mặt SSS thể tích"),
    create_color("C_DEEP_CYAN", "#0E7490", "Vùng đổ bóng khuất và nếp gấp sau thân"),
    create_color("C_BUOY_LIGHT", "#BAE6FD", "Men bóng đón sáng phao nổi kẹo biển đỉnh đầu"),
    create_color("C_RUBY_DEEP", "#991B1B", "Đáy bóng tối hồng ngọc Ruby"),
    create_color("C_RUBY_CORE", "#DC2626", "Lõi đỏ rực hồng ngọc trái tim đại dương"),
    create_color("C_RUBY_BRIGHT", "#EF4444", "Cạnh vát lóa sáng giác cắt facet ruby"),
    create_color("C_GOLD_BEZEL", "#F59E0B", "Viền vàng hoàng kim chạm khắc đính ngọc"),
    create_color("C_GOLD_BRIGHT", "#FEF08A", "Điểm tâm sáng hoàng kim lấp lánh"),
    create_color("C_GOLD_EYELID", "#FACC15", "Vệt viền vàng mí mắt trên"),
    create_color("C_EYE_DARK", "#03254C", "Hốc mắt vực thẳm đại dương sâu thẳm"),
    create_color("C_EYE_IRIS_BLUE", "#1D4ED8", "Thể thủy tinh Sapphire mắt xanh"),
    create_color("C_EYE_IRIS_AQUA", "#38BDF8", "Khúc xạ đáy mắt màu lam ngọc"),
    create_color("C_BLUSH_PINK", "#FB7185", "Đôi má hồng san hô nước biển ngọt ngào"),
    create_color("C_MOUTH_DEEP", "#0A5B80", "Nụ cười mỉm ngọt ngào đại dương"),
    create_color("C_MARKING_BLUE", "#0284C7", "Đốm tròn anten trán & cuống nối mắt"),
    create_color("C_BUBBLE_GLOW", "#7DD3FC", "Bọt nước ngân hà li ti phát sáng"),
    create_color("C_SEABED_SHADOW", "#041E34", "Bóng tiếp xúc mờ ảo đáy biển"),
    create_color("C_WHITE", "#FFFFFF", "Điểm bắt sáng kim cương men sứ")
  ],
  "volumetric_anatomy": {
    "silhouette": "Hình thể giọt nước tròn trĩnh múp míp (Water droplet chibi), tỷ lệ đầu to thân nhỏ 1.2:1 đặc trưng dòng Pop Mart Vinyl cao cấp.",
    "head_droplet": "Đầu dạng giọt nước khổng lồ tròn trịa, bề mặt phủ men sứ bóng bẩy với lõi tán xạ SSS lam ngọc và vệt bắt sáng specular trán.",
    "flotation_buoy_crown": "Phao nổi tròn phồng to tựa viên kẹo biển / phao cứu sinh mini ngự trên đỉnh đầu, có cổ chân phao và tâm lõm sâu đón sáng.",
    "long_ribbon_tail": "Dải ruy băng đuôi dài mềm mại xuất phát từ đỉnh phao đầu, uốn lượn hình sóng biển rủ sang phải và kết thúc bằng chóp đuôi cá chẻ 2 thùy V-notch.",
    "forehead_orbs_and_stems": "2 đốm tròn ngọc lam trên trán đối xứng nối cuống xuống viền mắt trên theo đúng 100% nguyên tác của Phione.",
    "golden_eyelid_accents": "Vệt viền vàng hoàng kim ôm trọn bờ mi trên đôi mắt, tạo điểm nhấn quý phái tinh khôi.",
    "crystal_eyes": {
      "proportion": "Chiếm 35% diện tích khuôn mặt, tạo nét biểu cảm ngây thơ, thánh thiện.",
      "specular_highlights": {
        "point_1_primary": "Đốm chính 2x2 góc 10h (#FFFFFF) - nguồn sáng chính trực tiếp.",
        "point_2_secondary": "Đốm phụ 1x1 góc 4h (#FFFFFF / Ice cyan) - phản xạ ánh sáng môi trường nảy từ mặt nước.",
        "point_3_micro_twinkle": "Đốm li ti góc 2h (#FFFFFF) và vệt trăng khuyết caustic phản quang đáy mắt."
      }
    },
    "chest_ruby_solar": "Viên hồng ngọc Ruby đỏ rực hình bầu dục đính giữa ngực trong vành vàng hoàng kim, tượng trưng cho trái tim đại dương.",
    "paddle_flippers": "Đôi tay bơi ngắn tròn xòe ngang như hai chiếc vây cá nhỏ màng mỏng, nhịp nhàng vẫy theo luồng hải lưu.",
    "tail_nub": "Đáy thân thuôn nhọn thành thùy đuôi tí hon mềm mại núng nính."
  },
  "organic_kinematics": {
    "ocean_hovering": {
      "frequency_hz": 0.28,
      "period_s": 3.5,
      "y_bobbing_amplitude_px": 3.5,
      "squash_and_stretch_vertical_pct": 5.0,
      "squash_and_stretch_horizontal_pct": -2.5,
      "volume_preservation_formula": "Sy * (Sx^2) ≈ 1.0 (sY = 1.0 + 0.05*sin(breathPhase), sX = 1.0 - 0.025*sin(breathPhase))"
    },
    "ribbon_tail_undulation": {
      "waveform": "S-Curve hydrodynamic wave with progressive phase lag",
      "phase_lag_rad": 0.45,
      "lateral_sway_px": 7.0,
      "vertical_sway_px": 4.0,
      "formula": "sinf(breathPhase - 0.45f) * 6.0f"
    },
    "flipper_paddle_flutter": {
      "phase_lag_rad": 0.35,
      "flutter_amplitude_px": 3.5,
      "formula": "sinf(breathPhase - 0.35f) * 3.5f"
    },
    "crystal_eye_blink": {
      "interval_ms": 3500,
      "duration_ms": 140,
      "shape_when_blinking": "Happy kawaii crescent curve"
    },
    "bioluminescent_galaxy_bubbles": {
      "bubble_count": 6,
      "oscillation_hz": 0.8,
      "glow_color": "#7DD3FC"
    },
    "seabed_ambient_shadow": {
      "contact_falloff_px": 7,
      "dynamic_expansion": "Expands when descending, contracts when ascending"
    }
  },
  "cpp_scaled_canvas_code": cpp_code,
  "js_canvas_code": js_code,
  "generated_render_artifact": {
    "image_file": "phione_popmart_3d_1788461851471.jpg",
    "description": "Bản điêu khắc 3D Pop Mart / Vinyl cao cấp của Phione Giọt Nước Biển Trôi Dạt với thân giọt nước trong suốt SSS núng nính, phao nổi tròn tựa viên kẹo biển, dải ruy băng đuôi dài mềm mại uốn lượn hình sóng, ngọc ruby ngực đỏ rực và đôi mắt pha lê 3 điểm bắt sáng.",
    "status": "Verified & Rendered"
  }
}

target_path = os.path.join("data", "session2_agent1_phione.json")
with open(target_path, "w", encoding="utf-8") as f:
    json.dump(data, f, ensure_ascii=False, indent=2)

print(f"Successfully wrote {target_path} ({os.path.getsize(target_path)} bytes)")
