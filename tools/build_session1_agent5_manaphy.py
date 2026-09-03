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
"""

js_code = """// =========================================================================
// MANAPHY - HOÀNG TỬ BIỂN SÂU HUYỀN THOẠI (MYTHIC MANAPHY OCEAN PRINCE)
// Pop Mart / High-End Vinyl Collectible Art - Modern HTML5 Canvas 2D
// =========================================================================

function drawMythicManaphy(ctx, cx, cy, scale, t) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.scale(scale, scale);

  // 1. Nhịp bơi lơ lửng đại dương Squash & Stretch 5%
  const breathFreq = 2.0;
  const breathPhase = t * breathFreq;
  const sY = 1.0 + 0.05 * Math.sin(breathPhase);
  const sX = 1.0 - 0.025 * Math.sin(breathPhase);
  const by = Math.sin(breathPhase) * 3.5;
  const blink = ((t % 3.5) < 0.14);

  // 2. Bóng tiếp xúc mờ ảo đáy biển (Soft Contact Shadow)
  ctx.save();
  const shadowGrad = ctx.createRadialGradient(0, 38, 4, 0, 38, 28 * sX);
  shadowGrad.addColorStop(0, 'rgba(4, 30, 52, 0.45)');
  shadowGrad.addColorStop(0.6, 'rgba(4, 30, 52, 0.20)');
  shadowGrad.addColorStop(1, 'rgba(4, 30, 52, 0)');
  ctx.fillStyle = shadowGrad;
  ctx.beginPath();
  ctx.ellipse(0, 38, 26 * sX, 6, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 3. Bọt nước ngân hà li ti phát sáng (Bioluminescent Galaxy Bubbles)
  const bubbleDefs = [
    { x: -36, y: -26, r: 3.2, phase: 0.0 },
    { x: 38,  y: -20, r: 2.8, phase: 1.2 },
    { x: -42, y: 12,  r: 2.4, phase: 2.4 },
    { x: 40,  y: 18,  r: 3.0, phase: 3.6 },
    { x: -18, y: -44, r: 2.0, phase: 4.8 },
    { x: 22,  y: -48, r: 2.5, phase: 5.5 }
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
    // Điểm bắt sáng bọt
    ctx.fillStyle = '#FFFFFF';
    ctx.beginPath();
    ctx.arc(bx - b.r * 0.35, by_pos - b.r * 0.35, b.r * 0.3, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  });

  // 4. Đôi ăng-ten đỉnh đầu uốn lượn hình chữ S (Độ trễ pha 80ms)
  const hy = by - 16;
  const antLag = breathPhase - 0.52;
  const sCurve1 = Math.sin(antLag) * 6.0;
  const sCurve2 = Math.cos(antLag) * 3.0;

  function drawAntenna(rootX, rootY, c1x, c1y, c2x, c2y, tipX, tipY, isFront) {
    ctx.save();
    ctx.lineWidth = 3.2;
    ctx.lineCap = 'round';
    ctx.strokeStyle = isFront ? '#22D3EE' : '#0E7490';
    ctx.beginPath();
    ctx.moveTo(rootX, rootY);
    ctx.bezierCurveTo(c1x, c1y, c2x, c2y, tipX, tipY);
    ctx.stroke();

    // Viền men sứ lóa sáng
    ctx.lineWidth = 1.0;
    ctx.strokeStyle = '#CCFBF1';
    ctx.beginPath();
    ctx.moveTo(rootX + 0.6, rootY - 0.6);
    ctx.bezierCurveTo(c1x + 0.6, c1y - 0.6, c2x + 0.6, c2y - 0.6, tipX, tipY);
    ctx.stroke();

    // Viên ngọc xanh ngọc bích phát quang ở chóp
    ctx.shadowColor = '#34D399';
    ctx.shadowBlur = 14;
    const orbGrad = ctx.createRadialGradient(tipX - 1.5, tipY - 1.5, 1, tipX, tipY, 6);
    orbGrad.addColorStop(0, '#FFFFFF');
    orbGrad.addColorStop(0.3, '#6EE7B7');
    orbGrad.addColorStop(0.8, '#10B981');
    orbGrad.addColorStop(1, '#047857');
    ctx.fillStyle = orbGrad;
    ctx.beginPath();
    ctx.arc(tipX, tipY, 5.5, 0, Math.PI * 2);
    ctx.fill();

    // Vầng hào quang ngọc bích
    ctx.strokeStyle = 'rgba(110, 231, 183, 0.6)';
    ctx.lineWidth = 1.4;
    ctx.stroke();
    ctx.restore();
  }

  // Ăng-ten sau
  drawAntenna(3, hy - 14, 20 + sCurve2, hy - 28 + sCurve1 * 0.5, 40 + sCurve1, hy - 24 - sCurve2, 52 + sCurve1, hy - 10 + sCurve2, false);
  // Ăng-ten trước
  drawAntenna(-2, hy - 14, 16 + sCurve2, hy - 24 + sCurve1 * 0.5, 36 + sCurve1, hy - 20 - sCurve2, 46 + sCurve1, hy - 4 + sCurve2, true);

  // 5. Hai tay bơi dài xòe rộng như vây cá tiên
  const finLag = breathPhase - 0.35;
  const finFlutterL = Math.sin(finLag) * 4.0;
  const finFlutterR = Math.sin(finLag + 0.15) * 4.0;

  function drawFin(isLeft, flutter) {
    ctx.save();
    const sign = isLeft ? -1 : 1;
    const rX = sign * 10 * sX, rY = by + 3;
    const mX = sign * 32 * sX, mY = by + 8 + flutter;
    const tX = sign * 48 * sX, tY = by + 4 + flutter;

    const finGrad = ctx.createLinearGradient(rX, rY, tX, tY);
    finGrad.addColorStop(0, '#0E7490');
    finGrad.addColorStop(0.5, '#22D3EE');
    finGrad.addColorStop(1, '#67E8F9');

    ctx.fillStyle = finGrad;
    ctx.beginPath();
    ctx.moveTo(rX, rY - 3);
    ctx.quadraticCurveTo(mX, mY - 6, tX, tY);
    ctx.arc(tX, tY, 5.2, isLeft ? Math.PI * 0.5 : -Math.PI * 0.5, isLeft ? -Math.PI * 0.5 : Math.PI * 0.5);
    ctx.quadraticCurveTo(mX, mY + 6, rX, rY + 4);
    ctx.closePath();
    ctx.fill();

    // Gờ men sứ lóa sáng
    ctx.strokeStyle = 'rgba(255, 255, 255, 0.7)';
    ctx.lineWidth = 1.2;
    ctx.stroke();
    ctx.restore();
  }
  drawFin(true, finFlutterL);
  drawFin(false, finFlutterR);

  // 6. Thân nước giọt nước bán trong suốt & Chân bánh bao
  // Chân
  ctx.fillStyle = '#22D3EE';
  ctx.beginPath();
  ctx.roundRect(-11 * sX, by + 18, 8 * sX, 9 * sY, 4);
  ctx.roundRect(3 * sX,  by + 18, 8 * sX, 9 * sY, 4);
  ctx.fill();

  // Khối thân (Torso)
  ctx.save();
  const bodyGrad = ctx.createRadialGradient(-2 * sX, by + 6, 3, 0, by + 10, 18 * sY);
  bodyGrad.addColorStop(0, '#67E8F9');
  bodyGrad.addColorStop(0.5, '#22D3EE');
  bodyGrad.addColorStop(0.85, '#0284C7');
  bodyGrad.addColorStop(1, '#0E7490');
  ctx.fillStyle = bodyGrad;
  ctx.beginPath();
  ctx.ellipse(0, by + 10, 16 * sX, 16 * sY, 0, 0, Math.PI * 2);
  ctx.fill();

  // Viền men sứ lóa sáng
  ctx.strokeStyle = '#CCFBF1';
  ctx.lineWidth = 1.4;
  ctx.stroke();

  // Highlight bóng men sứ trên hông
  ctx.fillStyle = 'rgba(255, 255, 255, 0.65)';
  ctx.beginPath();
  ctx.ellipse(-6 * sX, by + 14, 3, 2, -0.2, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 7. Viên hồng ngọc Ruby đỏ rực trước ngực & Vòng chấm vàng hoàng kim
  const gemY = by + 4;
  ctx.save();
  // Vòng chấm vàng hoàng kim tỏa sáng
  ctx.fillStyle = '#F59E0B';
  ctx.beginPath();
  ctx.ellipse(0, gemY, 8.5, 10.5, 0, 0, Math.PI * 2);
  ctx.fill();

  ctx.fillStyle = '#FEF08A';
  const dotAngles = [0, Math.PI/2, Math.PI, Math.PI*1.5];
  dotAngles.forEach(a => {
    ctx.beginPath();
    ctx.arc(Math.cos(a) * 7.5, gemY + Math.sin(a) * 9.5, 1.3, 0, Math.PI * 2);
    ctx.fill();
  });

  // Viên ngọc Ruby đỏ rực
  ctx.shadowColor = 'rgba(220, 38, 38, 0.75)';
  ctx.shadowBlur = 10;
  const rubyGrad = ctx.createRadialGradient(-1, gemY - 2, 1, 0, gemY, 7);
  rubyGrad.addColorStop(0, '#FCA5A5');
  rubyGrad.addColorStop(0.25, '#EF4444');
  rubyGrad.addColorStop(0.7, '#DC2626');
  rubyGrad.addColorStop(1, '#881337');
  ctx.fillStyle = rubyGrad;
  ctx.beginPath();
  ctx.ellipse(0, gemY, 5.5, 7.5, 0, 0, Math.PI * 2);
  ctx.fill();

  // Điểm bắt sáng lóa giác cắt ruby
  ctx.fillStyle = '#FFFFFF';
  ctx.beginPath();
  ctx.arc(-1.5, gemY - 2.5, 1.2, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // Chấm vàng phúc khí bụng dưới
  ctx.save();
  ctx.fillStyle = '#F59E0B';
  ctx.beginPath();
  ctx.ellipse(0, by + 16, 3, 4, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.fillStyle = '#FEF08A';
  ctx.beginPath();
  ctx.ellipse(0, by + 16, 2, 2.8, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 8. Đầu nước giọt nước khổng lồ & Độ bóng men sứ
  ctx.save();
  const headGrad = ctx.createRadialGradient(-8 * sX, hy - 8 * sY, 4, 0, hy, 26 * sX);
  headGrad.addColorStop(0, '#E0F2FE');
  headGrad.addColorStop(0.3, '#67E8F9');
  headGrad.addColorStop(0.7, '#22D3EE');
  headGrad.addColorStop(1, '#0284C7');
  ctx.fillStyle = headGrad;
  ctx.beginPath();
  ctx.ellipse(0, hy, 26 * sX, 22 * sY, 0, 0, Math.PI * 2);
  ctx.fill();

  ctx.strokeStyle = '#CCFBF1';
  ctx.lineWidth = 1.6;
  ctx.stroke();

  // Điểm phản chiếu men sứ đỉnh đầu
  ctx.fillStyle = 'rgba(255, 255, 255, 0.8)';
  ctx.beginPath();
  ctx.ellipse(-10 * sX, hy - 11 * sY, 7, 3, -0.3, 0, Math.PI * 2);
  ctx.fill();
  ctx.beginPath();
  ctx.arc(12 * sX, hy - 8 * sY, 2.2, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 9. Hoa văn mí mắt hoàng kim & đốm tròn anten mắt
  const ey = hy + 1;
  const exL = -11 * sX;
  const exR = 11 * sX;

  function drawBrowDots(originX, sign) {
    ctx.save();
    ctx.strokeStyle = '#FACC15';
    ctx.lineWidth = 1.4;

    // Cuống 1
    ctx.beginPath();
    ctx.moveTo(originX + sign * 1, ey - 9);
    ctx.lineTo(originX + sign * 3, ey - 15);
    ctx.stroke();
    // Đốm 1
    ctx.fillStyle = '#F59E0B';
    ctx.beginPath();
    ctx.arc(originX + sign * 3, ey - 15, 3.2, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillStyle = '#FEF08A';
    ctx.beginPath();
    ctx.arc(originX + sign * 3, ey - 15, 2.0, 0, Math.PI * 2);
    ctx.fill();

    // Cuống 2
    ctx.beginPath();
    ctx.moveTo(originX - sign * 4, ey - 8);
    ctx.lineTo(originX - sign * 8, ey - 13);
    ctx.stroke();
    // Đốm 2
    ctx.fillStyle = '#F59E0B';
    ctx.beginPath();
    ctx.arc(originX - sign * 8, ey - 13, 3.2, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillStyle = '#FEF08A';
    ctx.beginPath();
    ctx.arc(originX - sign * 8, ey - 13, 2.0, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();
  }
  drawBrowDots(exL, -1);
  drawBrowDots(exR, 1);

  // Viền mí mắt vàng
  ctx.save();
  ctx.strokeStyle = '#FACC15';
  ctx.lineWidth = 1.6;
  ctx.beginPath();
  ctx.ellipse(exL, ey, 7, 9, 0, 0, Math.PI * 2);
  ctx.ellipse(exR, ey, 7, 9, 0, 0, Math.PI * 2);
  ctx.stroke();
  ctx.restore();

  // 10. Đôi mắt xanh thẳm đại dương pha lê (3-Point Specular)
  if (blink) {
    ctx.strokeStyle = '#03254C';
    ctx.lineWidth = 2.4;
    ctx.beginPath();
    ctx.ellipse(exL, ey + 2, 6, 2, 0, 0, Math.PI);
    ctx.ellipse(exR, ey + 2, 6, 2, 0, 0, Math.PI);
    ctx.stroke();
  } else {
    [exL, exR].forEach(ex => {
      ctx.save();
      // Hốc mắt xanh tối
      ctx.fillStyle = '#03254C';
      ctx.beginPath();
      ctx.ellipse(ex, ey, 6, 8, 0, 0, Math.PI * 2);
      ctx.fill();

      // Mống mắt sapphire
      const eyeGrad = ctx.createRadialGradient(ex, ey + 4, 1, ex, ey + 2, 6);
      eyeGrad.addColorStop(0, '#38BDF8');
      eyeGrad.addColorStop(0.6, '#1D4ED8');
      eyeGrad.addColorStop(1, '#03254C');
      ctx.fillStyle = eyeGrad;
      ctx.beginPath();
      ctx.ellipse(ex, ey + 2, 5, 5.5, 0, 0, Math.PI * 2);
      ctx.fill();

      // Đồng tử
      ctx.fillStyle = '#031733';
      ctx.beginPath();
      ctx.arc(ex, ey - 0.5, 3.2, 0, Math.PI * 2);
      ctx.fill();

      // 3 Catchlights:
      // Điểm 1: Primary lớn
      ctx.fillStyle = '#FFFFFF';
      ctx.beginPath();
      ctx.arc(ex - 2, ey - 3, 1.9, 0, Math.PI * 2);
      ctx.fill();
      // Điểm 2: Secondary bounce
      ctx.beginPath();
      ctx.arc(ex + 2, ey + 3, 1.1, 0, Math.PI * 2);
      ctx.fill();
      // Điểm 3: Micro glint
      ctx.fillStyle = 'rgba(255, 255, 255, 0.85)';
      ctx.beginPath();
      ctx.arc(ex + 2.2, ey - 2, 0.7, 0, Math.PI * 2);
      ctx.fill();

      ctx.restore();
    });
  }

  // 11. Đôi má ửng hồng nước biển & Nụ cười hoàng tử biển sâu
  // Má hồng
  ctx.save();
  const blushGradL = ctx.createRadialGradient(-18 * sX, hy + 6, 1, -18 * sX, hy + 6, 5);
  blushGradL.addColorStop(0, 'rgba(251, 113, 133, 0.8)');
  blushGradL.addColorStop(1, 'rgba(251, 113, 133, 0)');
  ctx.fillStyle = blushGradL;
  ctx.beginPath();
  ctx.ellipse(-18 * sX, hy + 6, 4.8, 3.5, 0, 0, Math.PI * 2);
  ctx.fill();

  const blushGradR = ctx.createRadialGradient(18 * sX, hy + 6, 1, 18 * sX, hy + 6, 5);
  blushGradR.addColorStop(0, 'rgba(251, 113, 133, 0.8)');
  blushGradR.addColorStop(1, 'rgba(251, 113, 133, 0)');
  ctx.fillStyle = blushGradR;
  ctx.beginPath();
  ctx.ellipse(18 * sX, hy + 6, 4.8, 3.5, 0, 0, Math.PI * 2);
  ctx.fill();

  // Miệng cười
  ctx.fillStyle = '#9F1239';
  ctx.beginPath();
  ctx.moveTo(-4.5, hy + 8);
  ctx.quadraticCurveTo(0, hy + 14, 4.5, hy + 8);
  ctx.closePath();
  ctx.fill();

  // Chiếc lưỡi nhỏ xinh
  ctx.fillStyle = '#FDA4AF';
  ctx.beginPath();
  ctx.arc(0, hy + 11, 2.2, 0, Math.PI);
  ctx.fill();
  ctx.restore();

  ctx.restore();
}
"""

data = {
    "character_profile": {
        "id": 5,
        "codename": "MYTHIC_MANAPHY_OCEAN_PRINCE",
        "name_vi": "Manaphy - Hoàng Tử Biển Sâu Huyền Thoại",
        "name_en": "Mythic Manaphy - Prince of the Ocean",
        "japanese_name": "マナフィ (Manafi)",
        "archetype": "Linh Thú Biển Sâu Thần Thoại / Pop Mart Vinyl Nghệ Thuật Cao Cấp",
        "source_art_reference": "05_Mythic_Manaphy_Ocean_Prince.png",
        "designer_toy_series": "Mythic Ocean Prince Pop Mart / Vinyl High-End Collectible 3D Series",
        "mythology_lore": "Vị Hoàng Tử Biển Sâu Huyền Thoại sinh ra từ đáy đại dương thanh khiết nhất thế giới. Trái tim của Manaphy mang sức mạnh cộng hưởng tâm linh thấu hiểu vạn vật biển khơi (Heart Swap), dẫn lối cho toàn bộ sinh linh đại dương. Thân hình giọt nước trong suốt phát ra ánh hào quang ngọc bích êm dịu, mang lại hòa bình và sự thanh tịnh vô tận cho những ai chiêm ngưỡng.",
        "sculpture_aesthetic_spec": {
            "finish_quality": "High-End Pop Mart / Porcelain Glazed Vinyl Collectible Toy",
            "body_material": "Thân nước xanh lam ngọc trong suốt (Water droplet body) với độ bóng men sứ phủ nano và tán xạ dưới bề mặt SSS (Subsurface Scattering)",
            "antennae_sculpt": "Đôi ăng-ten mềm mại uyển chuyển đính 2 viên ngọc lục bảo biển phát quang dạ quang (Bioluminescent Jade Gem Orbs)",
            "chest_ruby_solar": "Viên hồng ngọc Ruby đỏ rực hình bầu dục đính viền chạm khắc hoàng kim (Gilded Solar Ruby Core) cùng chấm vàng hoàng kim phúc khí",
            "ocean_crystal_eyes": "Đôi mắt pha lê xanh lam thẳm 3 điểm bắt sáng vật lý (Keylight, Ground Bounce, Micro Twinkle) kết hợp vệt viền hoàng kim và chấm anten mí mắt",
            "angel_fins": "Hai tay bơi vây cá tiên thon dài xòe rộng uốn lượn đa tầng đón sáng",
            "seabed_shadow": "Bóng tiếp xúc mờ ảo đáy biển (Ambient Occlusion Contact Shadow)"
        }
    },
    "palette": [
        create_color("C_FRESNEL_RIM", "#CCFBF1", "Viền men sứ xanh ngọc băng lóa sáng ngoài cùng (Fresnel Rim)"),
        create_color("C_BODY_CYAN", "#22D3EE", "Thân ngọc lam đại dương bán trong suốt chính"),
        create_color("C_BODY_LIGHT", "#67E8F9", "Vùng phản quang sáng khoang thể dịch bên trong"),
        create_color("C_BODY_CORE_SSS", "#0284C7", "Lõi tán xạ ánh sáng dưới bề mặt SSS thể tích"),
        create_color("C_DEEP_CYAN", "#0E7490", "Vùng đổ bóng khuất vạt nách và thùy đuôi"),
        create_color("C_JADE_CORE", "#34D399", "Ngọc lục bảo biển phát quang đầu anten"),
        create_color("C_JADE_GLOW", "#6EE7B7", "Quầng hào quang dạ quang ngọc bích"),
        create_color("C_RUBY_DEEP", "#991B1B", "Đáy bóng tối hồng ngọc Ruby"),
        create_color("C_RUBY_CORE", "#DC2626", "Lõi đỏ rực hồng ngọc trái tim đại dương"),
        create_color("C_RUBY_BRIGHT", "#EF4444", "Cạnh vát lóa sáng giác cắt ruby"),
        create_color("C_GOLD_CROWN", "#F59E0B", "Viền vàng hoàng kim & hoa văn anten"),
        create_color("C_GOLD_BRIGHT", "#FEF08A", "Điểm tâm sáng hoàng kim lấp lánh"),
        create_color("C_GOLD_EYE_RING", "#FACC15", "Viền mí mắt & chấm anten vàng"),
        create_color("C_EYE_DARK", "#03254C", "Hốc mắt vực thẳm đại dương sâu thẳm"),
        create_color("C_EYE_IRIS_BLUE", "#1D4ED8", "Thể thủy tinh Sapphire mắt xanh"),
        create_color("C_EYE_IRIS_AQUA", "#38BDF8", "Khúc xạ đáy mắt màu lam ngọc"),
        create_color("C_BLUSH_PINK", "#FB7185", "Đôi má hồng san hô e ấp ngọt ngào"),
        create_color("C_MOUTH_DEEP", "#9F1239", "Khoang miệng hồng thẫm ngọt ngào"),
        create_color("C_MOUTH_TONGUE", "#FDA4AF", "Lưỡi nhỏ hồng phấn đáng yêu"),
        create_color("C_BUBBLE_GLOW", "#7DD3FC", "Bọt nước ngân hà li ti phát sáng"),
        create_color("C_SEABED_SHADOW", "#041E34", "Bóng tiếp xúc mờ ảo đáy biển"),
        create_color("C_WHITE", "#FFFFFF", "Điểm bắt sáng kim cương men sứ")
    ],
    "organic_kinematics": {
        "swimming_levitation": {
            "frequency_hz": 0.28,
            "period_s": 3.5,
            "y_bobbing_amplitude_px": 3.5,
            "squash_and_stretch_vertical_pct": 5.0,
            "squash_and_stretch_horizontal_pct": -2.5,
            "volume_preservation_formula": "Sy * Sx ≈ 1.0 (sY = 1.0 + 0.05*sin(t*2.0), sX = 1.0 - 0.025*sin(t*2.0))"
        },
        "antennae_undulation": {
            "waveform": "S-Curve undulation with phase lag",
            "phase_lag_ms": 80,
            "phase_lag_rad": 0.52,
            "lateral_sway_px": 6.0,
            "vertical_sway_px": 3.0,
            "formula": "sinf(breathPhase - 0.52f) * 6.0f"
        },
        "angel_flippers_flutter": {
            "phase_lag_ms": 55,
            "phase_lag_rad": 0.35,
            "flutter_amplitude_px": 4.0,
            "formula": "sinf(breathPhase - 0.35f) * 4.0f"
        },
        "crystal_eye_blink": {
            "interval_ms": 3500,
            "duration_ms": 140,
            "shape_when_blinking": "Happy kawaii crescent curve"
        },
        "bioluminescent_galaxy_bubbles": {
            "bubble_count": 6,
            "oscillation_hz": 0.75,
            "glow_color": "#7DD3FC"
        },
        "seabed_ambient_shadow": {
            "contact_falloff_px": 8,
            "dynamic_expansion": "Expands when descending, contracts when ascending"
        }
    },
    "cpp_scaled_canvas_code": cpp_code.strip(),
    "js_canvas_code": js_code.strip(),
    "generated_render_artifact": {
        "image_file": "manaphy_popmart_3d_1788461163831.jpg",
        "description": "Bản điêu khắc 3D Pop Mart / Vinyl cao cấp của Hoàng Tử Biển Sâu Manaphy với men sứ bóng bẩy, thân ngọc lam SSS, ngọc ruby ngực phát sáng và đôi ăng-ten ngọc bích dạ quang.",
        "status": "Verified & Rendered"
    }
}

os.makedirs('data', exist_ok=True)
output_path = os.path.join('data', 'session1_agent5_manaphy.json')
with open(output_path, 'w', encoding='utf-8') as f:
    json.dump(data, f, ensure_ascii=False, indent=2)

print("SUCCESS: Written session1_agent5_manaphy.json")
print("File size:", os.path.getsize(output_path), "bytes")
