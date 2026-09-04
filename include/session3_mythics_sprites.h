#pragma once
// ============================================================================
// SESSION 3 ELECTRIC SQUAD - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 ST7789 IPS LCD (172x320 60FPS DMA)
// Pop Mart & Kawaii Visual DNA: Volumetric 4-Tone Shading & Crystal Catchlights
// Characters: Pachirisu, Emolga, Dedenne, Morpeko, Pawmi (IDs 60 to 64)
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace Session3Mythics {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// -------------------------------------------------------------
// Pachirisu - Sóc Điện Trắng Lam
// -------------------------------------------------------------
static void drawPachirisuSquirrel(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.5f);
  int by = cy + bounceY;

  // Đuôi sóc khổng lồ đung đưa trễ pha Delta Phi = 0.45 rad
  float tailLag = breathPhase - 0.45f;
  int tailSwayX = (int)(sinf(tailLag) * 6.0f);
  int tailSwayY = (int)(cosf(tailLag) * 3.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Sứ trắng
  const uint16_t C_WHITE_SHAD = 0xCE79; // #CBD5E1 Bóng sứ
  const uint16_t C_CYAN       = 0x3EDB; // #38BDF8 Xanh lam sọc trán & đuôi
  const uint16_t C_CYAN_DARK  = 0x0396; // #0284C7 Bóng sọc xanh
  const uint16_t C_CYAN_LGT   = 0xBA3F; // #BAE6FD Sáng viền xanh
  const uint16_t C_CHEEK      = 0xFE62; // #FACC15 Má túi điện vàng
  const uint16_t C_CHEEK_SHAD = 0xE540; // #EAB308 Bóng má vàng
  const uint16_t C_EYE_BLACK  = 0x08E5; // #0F172A Mắt đen tuyền
  const uint16_t C_MOUTH_DARK = 0x8887; // #881337 Khoang miệng
  const uint16_t C_TONGUE     = 0xF3B6; // #F472B6 Lưỡi hồng
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng tiếp xúc sàn
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Chiếc đuôi sóc khổng lồ sau lưng (vươn cao sang phải)
  int tx = cx + 18 + tailSwayX;
  int ty = by - 10 + tailSwayY;
  // Khối đuôi chính (xanh lam sống lưng)
  spr->fillEllipse(tx + 4, ty, 18, 30, C_CYAN_DARK);
  spr->fillEllipse(tx + 2, ty - 2, 16, 28, C_CYAN);
  // 3 Chỏm gai nhọn trên sống đuôi
  spr->fillTriangle(tx + 14, ty - 20, tx + 24, ty - 38, tx + 6, ty - 24, C_CYAN);
  spr->fillTriangle(tx + 16, ty - 6,  tx + 28, ty - 18, tx + 10, ty - 10, C_CYAN);
  spr->fillTriangle(tx + 14, ty + 10, tx + 24, ty + 4,  tx + 8, ty + 6, C_CYAN);
  // Bụng đuôi màu trắng cuộn tròn
  spr->fillEllipse(tx - 4, ty + 2, 14, 26, C_WHITE_SHAD);
  spr->fillEllipse(tx - 6, ty, 12, 24, C_WHITE);

  // 3. Thân trắng phúng phính & chân
  spr->fillEllipse(cx - 6, by + 18, (int)(18 * sX), (int)(20 * sY), C_WHITE_SHAD);
  spr->fillEllipse(cx - 6, by + 16, (int)(16 * sX), (int)(18 * sY), C_WHITE);
  // Hai chân ngắn
  spr->fillRoundRect(cx - 16, by + 30, 8, 12, 4, C_WHITE_SHAD);
  spr->fillRoundRect(cx - 15, by + 29, 7, 11, 4, C_WHITE);
  spr->fillRoundRect(cx + 2, by + 30, 8, 12, 4, C_WHITE_SHAD);
  spr->fillRoundRect(cx + 3, by + 29, 7, 11, 4, C_WHITE);

  // 4. Đầu tròn mũm mĩm Pop Mart
  spr->fillEllipse(cx - 6, by - 4, (int)(22 * sX), (int)(20 * sY), C_WHITE_SHAD);
  spr->fillEllipse(cx - 6, by - 6, (int)(20 * sX), (int)(18 * sY), C_WHITE);

  // 5. Đôi tai nhỏ trắng chóp xanh lam
  // Tai trái
  spr->fillTriangle(cx - 20, by - 12, cx - 26, by - 36, cx - 12, by - 18, C_WHITE_SHAD);
  spr->fillTriangle(cx - 19, by - 14, cx - 24, by - 34, cx - 13, by - 18, C_WHITE);
  spr->fillTriangle(cx - 21, by - 24, cx - 24, by - 34, cx - 16, by - 26, C_CYAN);
  // Tai phải
  spr->fillTriangle(cx + 2, by - 14, cx + 8, by - 36, cx + 12, by - 18, C_WHITE_SHAD);
  spr->fillTriangle(cx + 3, by - 15, cx + 8, by - 34, cx + 11, by - 18, C_WHITE);
  spr->fillTriangle(cx + 5, by - 25, cx + 8, by - 34, cx + 10, by - 26, C_CYAN);

  // 6. Vệt sọc xanh lam trên trán chạy dọc xuống đỉnh đầu
  spr->fillTriangle(cx - 6, by - 22, cx - 10, by - 10, cx - 2, by - 10, C_CYAN);
  spr->fillRoundRect(cx - 8, by - 14, 4, 10, 2, C_CYAN_LGT);

  // 7. Hai má túi điện vàng căng mọng
  spr->fillCircle(cx - 18, by + 2, 7, C_CHEEK_SHAD);
  spr->fillCircle(cx - 18, by + 1, 6, C_CHEEK);
  spr->fillCircle(cx + 6, by + 2, 7, C_CHEEK_SHAD);
  spr->fillCircle(cx + 6, by + 1, 6, C_CHEEK);

  // 8. Đôi mắt pha lê to tròn đen sâu
  if (!blink) {
    spr->fillEllipse(cx - 12, by - 6, 4, 7, C_EYE_BLACK);
    spr->fillCircle(cx - 13, by - 9, 2, C_WHITE);
    spr->drawPixel(cx - 11, by - 3, C_WHITE);

    spr->fillEllipse(cx, by - 6, 4, 7, C_EYE_BLACK);
    spr->fillCircle(cx - 1, by - 9, 2, C_WHITE);
    spr->drawPixel(cx + 1, by - 3, C_WHITE);
  } else {
    spr->drawEllipse(cx - 12, by - 5, 4, 2, C_EYE_BLACK);
    spr->drawEllipse(cx, by - 5, 4, 2, C_EYE_BLACK);
  }

  // 9. Mũi & Miệng cười với răng cửa tí hon
  spr->drawPixel(cx - 6, by - 2, C_EYE_BLACK);
  spr->fillTriangle(cx - 6, by + 7, cx - 10, by + 2, cx - 2, by + 2, C_MOUTH_DARK);
  spr->fillCircle(cx - 6, by + 5, 2, C_TONGUE);
  spr->fillRect(cx - 7, by + 2, 3, 3, C_WHITE); // Răng cửa nhỏ xíu

  // 10. Hai tay búp măng nhỏ ôm ngực
  spr->fillCircle(cx - 10, by + 12, 3, C_WHITE);
  spr->fillCircle(cx - 2, by + 12, 3, C_WHITE);
}

// -------------------------------------------------------------
// Emolga
// -------------------------------------------------------------
// =========================================================================
// 12_MYTHIC_EMOLGA_FLYING_SQUIRREL - C++ ScaledCanvas Implementation
// 100% Hardware Compatible with ESP32 / ESP32-S3 + ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl 3D Sculpt: Lemon Patagium Wings, Rounded Black Ears,
// Plump Electric Cheeks, 3-Point Specular Eyes, Sweeping Lightning Crescent Tail
// Organic Micro-Physics: 5% Squash & Stretch, 80ms Wing Flap Lag, Tail Sway
// =========================================================================
static void drawEmolgaFlyingSquirrel(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (Organic Micro-Physics)
  float breathFreq  = 2.4f;
  float breathPhase = angle * breathFreq;
  float breathSin   = sinf(breathPhase);

  // Nhịp lượn bay Squash & Stretch 5% bảo toàn thể tích thực tế
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(sinf(breathPhase) * 4.5f);
  int by = cy + bounceY; // Tọa độ Y động của thân, cánh và đầu

  // Đôi cánh sóc bay vỗ nhịp trễ pha 80ms (Delta Phi = 0.20 rad) dập dờn như cánh diều
  float wingLag = breathPhase - 0.20f;
  float wingFlap = sinf(wingLag) * 5.0f;
  float wingFlutter = sinf(breathPhase * 2.0f - 0.20f) * 1.6f;

  // Đuôi sóc xòe hình lưỡi liềm uốn lượn sau lưng trễ pha quán tính
  float tailLag = breathPhase - 0.40f;
  int tailSwayX = (int)(sinf(tailLag) * 6.5f);
  int tailSwayY = (int)(cosf(tailLag) * 3.8f);

  // Hạt bụi tĩnh điện lách tách tần số cao
  int spark1 = (int)(sinf(angle * 12.0f) * 3.0f);
  int spark2 = (int)(cosf(angle * 16.0f) * 3.0f);

  // 2. BẢNG MÀU 16-BIT RGB565 CHUẨN XÁC POP MART VINYL
  const uint16_t C_WING_YEL_LIGHT   = 0xFFEB; // #FFF875 Vàng chanh bắt sáng đỉnh
  const uint16_t C_WING_YEL_MAIN    = 0xFEA0; // #FFD000 Vàng chanh rực rỡ mặt trong
  const uint16_t C_WING_YEL_WARM    = 0xFCE0; // #F59E0B Vàng hổ phách chuyển khối
  const uint16_t C_WING_YEL_SHADOW  = 0xDBA0; // #D97706 Vàng cam đổ bóng nếp gấp
  const uint16_t C_WING_BLK_OUTER   = 0x1925; // #1E232B Mặt ngoài & viền đen bóng bẩy
  const uint16_t C_FUR_WHITE_GLOSS  = 0xFFFF; // #FFFFFF Lông trắng ngọc trai bụng, mặt
  const uint16_t C_FUR_WHITE_SHADOW = 0xE71C; // #E2E8F0 Đổ bóng lụa mềm thân trắng
  const uint16_t C_FUR_WHITE_DEEP   = 0xCE58; // #CBD5E1 Bóng che khuất nách và chân
  const uint16_t C_HOOD_BLK_MAIN    = 0x2126; // #222630 Mũ trùm đầu đen nhung tuyền
  const uint16_t C_HOOD_BLK_DARK    = 0x10A3; // #14171F Rãnh tối phân chia mũ trán
  const uint16_t C_HOOD_BLK_RIM     = 0x428C; // #475166 Viền đón sáng lụa Fresnel
  const uint16_t C_EAR_INNER_YEL    = 0xFE60; // #FFCE00 Lòng tai vàng rực rỡ
  const uint16_t C_EAR_INNER_LIGHT  = 0xFFE0; // #FFF380 Bắt sáng tâm lòng tai
  const uint16_t C_EAR_BASE_WHITE   = 0xF7BE; // #F1F5F9 Vành trắng viền đệm chân tai
  const uint16_t C_CHEEK_YEL        = 0xFDAC; // #FFB703 Túi điện tròn vo má phúng phính
  const uint16_t C_CHEEK_GLOW       = 0xFE8C; // #FFD166 Quầng điện quang má
  const uint16_t C_EYE_ONYX_DEEP    = 0x0882; // #0E1015 Hốc mắt đen láy pha lê
  const uint16_t C_EYE_PUPIL_BLK    = 0x1905; // #1C202A Tròng mắt obsidian
  const uint16_t C_WHITE            = 0xFFFF; // #FFFFFF Catchlight pha lê & móng vuốt
  const uint16_t C_SPEC_BOUNCE      = 0xE71C; // #E2E8F0 Điểm phản xạ đáy mắt
  const uint16_t C_MOUTH_CAVITY     = 0x58C4; // #581C28 Khoang miệng rượu vang Bordeaux
  const uint16_t C_MOUTH_TONGUE     = 0xFBB0; // #FB7185 Lưỡi hồng đào nhỏ nhắn
  const uint16_t C_NOSE_BLK         = 0x10A3; // #14171F Chấm mũi đen nhỏ xíu
  const uint16_t C_TAIL_BLK         = 0x18E4; // #181C24 Đuôi sóc lưỡi liềm đen tuyền
  const uint16_t C_TAIL_RIM         = 0x3A2A; // #3D4657 Sống gờ tia chớp đón sáng
  const uint16_t C_FOOT_GREY        = 0x9537; // #94A3B8 Chân sau tí hon buông lỏng
  const uint16_t C_CONTACT_SHADOW   = 0x10A4; // #121620 Bóng tiếp xúc mờ ảo sàn
  const uint16_t C_SPARK_ELEC       = 0xFF8F; // #FFF37A Hạt tĩnh điện lách tách

  // 3. LAYER 0: BÓNG TIẾP XÚC MỜ ẢO CO GIÃN NHỊP NHÀNG DƯỚI SÀN (Ground Contact Shadow)
  float shadowFactor = 1.0f - (float)bounceY * 0.04f;
  int shadowW = (int)(56.0f * sX * shadowFactor);
  int shadowH = (int)(11.5f * sX * shadowFactor);
  spr->fillEllipse(cx - 2, cy + 64, shadowW, shadowH, C_CONTACT_SHADOW);
  spr->fillEllipse(cx - 2, cy + 64, (int)(shadowW * 0.65f), (int)(shadowH * 0.6f), 0x0862);

  // 4. LAYER 1: BẢN ĐUÔI SÓC TIA CHỚP LƯỠI LIỀM KHỔNG LỒ ĐEN TUYỀN (Giant Sweeping Lightning Plume)
  // Gốc đuôi nối từ sườn lưng vút sang phải, nở rộng thành 3 mũi tia chớp nhọn sắc
  int tx0 = cx + 8;
  int ty0 = by + 22;
  int txMid = cx + 46 + (int)(tailSwayX * 0.5f);
  int tyMid = by + 8 + tailSwayY;
  int txTop = cx + 88 + tailSwayX;
  int tyTop = by - 24 + tailSwayY;
  int txNotch1 = cx + 70 + (int)(tailSwayX * 0.8f);
  int tyNotch1 = by - 8 + tailSwayY;
  int txMidSpike = cx + 104 + (int)(tailSwayX * 1.15f);
  int tyMidSpike = by - 2 + tailSwayY;
  int txNotch2 = cx + 76 + (int)(tailSwayX * 0.85f);
  int tyNotch2 = by + 12 + tailSwayY;
  int txBotSpike = cx + 92 + (int)(tailSwayX * 0.9f);
  int tyBotSpike = by + 26 + tailSwayY;

  // Lớp đệm thân đuôi dầy dặn Pop Mart
  spr->fillTriangle(tx0, ty0 - 8, txMid, tyMid - 10, tx0 + 14, ty0 + 12, C_TAIL_BLK);
  spr->fillTriangle(txMid, tyMid - 10, txTop, tyTop, txNotch1, tyNotch1, C_TAIL_BLK);
  spr->fillTriangle(txMid, tyMid - 6, txNotch1, tyNotch1, txMidSpike, tyMidSpike, C_TAIL_BLK);
  spr->fillTriangle(txMid, tyMid + 4, txMidSpike, tyMidSpike, txNotch2, tyNotch2, C_TAIL_BLK);
  spr->fillTriangle(txMid, tyMid + 8, txNotch2, tyNotch2, txBotSpike, tyBotSpike, C_TAIL_BLK);
  spr->fillTriangle(txMid, tyMid + 12, txBotSpike, tyBotSpike, tx0 + 16, ty0 + 12, C_TAIL_BLK);

  // Khối chuyển bóng 3D mặt trong đuôi
  spr->fillTriangle(txMid, tyMid, txNotch1 + 4, tyNotch1 + 2, txMidSpike - 8, tyMidSpike, C_HOOD_BLK_MAIN);
  spr->fillTriangle(txMid, tyMid + 6, txNotch2 + 4, tyNotch2 + 2, txBotSpike - 8, tyBotSpike, C_HOOD_BLK_MAIN);

  // Sống gờ tia chớp đón sáng (Specular Rim Highlight)
  spr->drawLine(tx0 + 2, ty0 - 6, txMid, tyMid - 10, C_TAIL_RIM);
  spr->drawLine(txMid, tyMid - 10, txTop, tyTop, C_TAIL_RIM);
  spr->drawLine(txTop, tyTop, txNotch1, tyNotch1, C_HOOD_BLK_RIM);
  spr->drawLine(txNotch1, tyNotch1, txMidSpike, tyMidSpike, C_TAIL_RIM);
  spr->drawLine(txMidSpike, tyMidSpike, txNotch2, tyNotch2, C_HOOD_BLK_RIM);
  spr->drawLine(txNotch2, tyNotch2, txBotSpike, tyBotSpike, C_TAIL_RIM);

  // 5. LAYER 2: ĐÔI TAI ĐEN TRÒN XÒE RỘNG VỚI LÒNG TAI VÀNG RỰC (Large Rounded Ears with Sun-Gold Inset)
  // Tai trái (viewer's left - vểnh sang trái)
  int elx = cx - 30;
  int ely = by - 36;
  spr->fillEllipse(elx, ely, 17, 20, C_HOOD_BLK_MAIN);
  spr->drawEllipse(elx, ely, 17, 20, C_HOOD_BLK_RIM);
  spr->fillEllipse(elx + 2, ely + 2, 12, 14, C_EAR_INNER_YEL);
  spr->fillEllipse(elx + 1, ely - 1, 7, 8, C_EAR_INNER_LIGHT);
  spr->fillEllipse(elx + 3, ely + 8, 8, 5, C_EAR_BASE_WHITE);

  // Tai phải (viewer's right - xòe rộng sang phải)
  int erx = cx + 22;
  int ery = by - 42;
  spr->fillEllipse(erx, ery, 19, 22, C_HOOD_BLK_MAIN);
  spr->drawEllipse(erx, ery, 19, 22, C_HOOD_BLK_RIM);
  spr->fillEllipse(erx - 1, ery + 2, 13, 16, C_EAR_INNER_YEL);
  spr->fillEllipse(erx - 2, ery - 1, 8, 9, C_EAR_INNER_LIGHT);
  spr->fillEllipse(erx - 1, ery + 10, 9, 6, C_EAR_BASE_WHITE);

  // 6. LAYER 3: HAI CÁNH SÓC BAY MÀNG VÀNG CHANH RỰC RỠ (Huge Flying Patagium Wings with 80ms Lag)
  // Cánh trái (viewer's left - màng căng từ cổ tay trái cx - 52 xuống sườn cx - 16)
  int wlx = cx - 54;
  int wly = by - 6 + (int)wingFlap;
  int whlx = cx - 16;
  int whly = by + 26;
  int wMidLx = cx - 42;
  int wMidLy = by + 22 + (int)wingFlutter;

  // Lớp viền đen mặt ngoài màng cánh trái
  spr->fillTriangle(wlx - 4, wly + 2, whlx, whly + 2, wMidLx - 5, wMidLy + 5, C_WING_BLK_OUTER);
  // Màng cánh vàng chanh rực rỡ mặt trong
  spr->fillTriangle(wlx, wly, whlx, whly, wMidLx, wMidLy, C_WING_YEL_MAIN);
  spr->fillTriangle(wlx + 8, wly + 2, whlx - 2, whly - 4, wMidLx + 2, wMidLy - 3, C_WING_YEL_LIGHT);
  spr->fillTriangle(wMidLx, wMidLy, whlx, whly, wMidLx - 3, wMidLy + 3, C_WING_YEL_SHADOW);

  // Cánh phải (viewer's right - buồm vàng khổng lồ xòe sang phải)
  int wrx = cx + 46;
  int wry = by - 4 + (int)(wingFlap * 0.85f);
  int whrx = cx + 18;
  int whry = by + 24;
  int wMidRx = cx + 42;
  int wMidRy = by + 20 + (int)wingFlutter;

  // Lớp viền đen mặt ngoài màng cánh phải
  spr->fillTriangle(wrx + 4, wry + 2, whrx, whry + 2, wMidRx + 5, wMidRy + 5, C_WING_BLK_OUTER);
  // Màng cánh vàng chanh rực rỡ mặt trong cánh phải
  spr->fillTriangle(wrx, wry, whrx, whry, wMidRx, wMidRy, C_WING_YEL_MAIN);
  spr->fillTriangle(wrx - 6, wry + 2, whrx + 2, whry - 4, wMidRx - 3, wMidRy - 3, C_WING_YEL_LIGHT);
  spr->fillTriangle(wMidRx, wMidRy, whrx, whry, wMidRx + 3, wMidRy + 4, C_WING_YEL_SHADOW);

  // 7. LAYER 4: THÂN TRÒN MẬP & HAI CHÂN SAU TÍ HON (Plump Pear Body & Dangling Feet)
  // Lưng và sườn đen bao phủ
  spr->fillEllipse(cx, by + 16, (int)(26 * sX), (int)(24 * sY), C_HOOD_BLK_MAIN);

  // Bụng trắng ngọc trai phúng phính Pop Mart
  spr->fillEllipse(cx - 2, by + 16, (int)(22 * sX), (int)(21 * sY), C_FUR_WHITE_GLOSS);
  spr->fillEllipse(cx - 2, by + 23, (int)(17 * sX), (int)(13 * sY), C_FUR_WHITE_SHADOW);

  // Hai chân sau tí hon buông lỏng tự nhiên trong gió
  // Chân trái
  spr->fillRoundRect(cx - 16, by + 36, 7, 10, 3, C_FOOT_GREY);
  spr->fillCircle(cx - 13, by + 44, 3, C_FUR_WHITE_GLOSS);
  // Chân phải
  spr->fillRoundRect(cx + 4, by + 35, 7, 10, 3, C_FOOT_GREY);
  spr->fillCircle(cx + 7, by + 43, 3, C_FUR_WHITE_GLOSS);

  // 8. LAYER 5: HAI CÁNH TAY TRẮNG MUỐT DANG RỘNG (Outstretched White Arms & Claws)
  // Tay trái (viewer's left - vẫy gió sang trái)
  spr->fillTriangle(cx - 18, by + 6, wlx, wly, cx - 20, by + 14, C_FUR_WHITE_GLOSS);
  spr->fillRoundRect(wlx - 3, wly - 5, 14, 9, 4, C_FUR_WHITE_GLOSS);
  // 3 Móng vuốt nhỏ xíu ngộ nghĩnh
  spr->fillCircle(wlx - 4, wly - 3, 2, C_WHITE);
  spr->fillCircle(wlx - 5, wly, 2, C_WHITE);
  spr->fillCircle(wlx - 3, wly + 3, 2, C_WHITE);

  // Tay phải (viewer's right - dang rộng hướng lên trước)
  spr->fillTriangle(cx + 16, by + 4, wrx, wry, cx + 18, by + 13, C_FUR_WHITE_GLOSS);
  spr->fillRoundRect(wrx - 10, wry - 5, 14, 9, 4, C_FUR_WHITE_GLOSS);
  // 3 Móng vuốt nhỏ xíu ngộ nghĩnh
  spr->fillCircle(wrx + 4, wry - 3, 2, C_WHITE);
  spr->fillCircle(wrx + 5, wry, 2, C_WHITE);
  spr->fillCircle(wrx + 3, wry + 3, 2, C_WHITE);

  // 9. LAYER 6: KHỐI ĐẦU POP MART, MŨ TRÙM ĐEN 3 MÚI & KHUÔN MẶT TRẮNG (Head, Hood & Face)
  int hx = cx - 4;
  int hy = by - 12;

  // Khối nền đầu đen bao phủ
  spr->fillEllipse(hx, hy, (int)(30 * sX), (int)(27 * sY), C_HOOD_BLK_MAIN);
  spr->fillEllipse(hx, hy - 16, (int)(18 * sX), (int)(8 * sY), C_HOOD_BLK_RIM); // Đón sáng Fresnel đỉnh đầu

  // Khuôn mặt trắng phúng phính (White Face Cheeks)
  spr->fillEllipse(hx - 2, hy + 3, (int)(25 * sX), (int)(21 * sY), C_FUR_WHITE_GLOSS);
  spr->fillEllipse(hx - 14, hy + 5, 12, 12, C_FUR_WHITE_GLOSS); // Má trái bầu bĩnh
  spr->fillEllipse(hx + 10, hy + 4, 11, 11, C_FUR_WHITE_GLOSS); // Má phải bầu bĩnh

  // Mũ trùm đầu đen 3 múi nhọn chúc xuống trán và má theo đúng nguyên tác 100%
  // Múi giữa (chúc xuống giữa 2 mắt)
  spr->fillTriangle(hx - 12, hy - 18, hx, hy - 1, hx + 10, hy - 18, C_HOOD_BLK_MAIN);
  spr->fillTriangle(hx - 10, hy - 16, hx, hy - 2, hx + 8, hy - 16, C_HOOD_BLK_DARK);
  // Múi bên trái (chúc xuống mép ngoài má trái)
  spr->fillTriangle(hx - 24, hy - 14, hx - 19, hy - 6, hx - 13, hy - 17, C_HOOD_BLK_MAIN);
  // Múi bên phải (chúc xuống mép ngoài má phải)
  spr->fillTriangle(hx + 11, hy - 17, hx + 17, hy - 7, hx + 23, hy - 14, C_HOOD_BLK_MAIN);

  // 10. LAYER 7: HAI MÁ TÚI ĐIỆN VÀNG TRÒN VO PHÚNG PHÍNH (Plump Electric Yellow Cheeks)
  // Túi điện má trái (viewer's left)
  int clx = cx - 25;
  int cly = hy + 6;
  spr->fillCircle(clx, cly, 8, C_CHEEK_YEL);
  spr->fillCircle(clx + 1, cly - 1, 5, C_CHEEK_GLOW);

  // Túi điện má phải (viewer's right)
  int crx = cx + 17;
  int cry = hy + 4;
  spr->fillCircle(crx, cry, 7, C_CHEEK_YEL);
  spr->fillCircle(crx - 1, cry - 1, 4, C_CHEEK_GLOW);

  // 11. LAYER 8: ĐÔI MẮT PHA LÊ ĐEN LÁY TO TRÒN 3 ĐIỂM BẮT SÁNG (Crystal Specular Eyes)
  // Mắt trái (viewer's left) - to tròn lấp lánh
  int elX = cx - 15;
  int elY = hy - 4;
  if (blink) {
    // Mí mắt cười nhắm cong hình trăng khuyết đáng yêu
    spr->drawEllipse(elX, elY + 2, 8, 3, C_EYE_ONYX_DEEP);
    spr->drawLine(elX - 7, elY + 3, elX - 10, elY - 1, C_EYE_ONYX_DEEP); // Đuôi mi vểnh
  } else {
    spr->fillEllipse(elX, elY, 8, 12, C_EYE_ONYX_DEEP);
    spr->fillEllipse(elX, elY, 7, 11, C_EYE_PUPIL_BLK);
    // 3 Điểm bắt sáng pha lê:
    spr->fillEllipse(elX - 2, elY - 4, 3, 3, C_WHITE);       // Điểm 1: Keylight lớn góc 10h
    spr->fillCircle(elX + 2, elY + 4, 2, C_SPEC_BOUNCE);     // Điểm 2: Phản xạ đáy mắt góc 4h
    spr->drawPixel(elX + 3, elY - 1, C_WHITE);               // Điểm 3: Vi điểm bắt sáng
  }

  // Mắt phải (viewer's right)
  int erX = cx + 6;
  int erY = hy - 7;
  if (blink) {
    spr->drawEllipse(erX, erY + 2, 7, 3, C_EYE_ONYX_DEEP);
    spr->drawLine(erX + 6, erY + 3, erX + 9, erY - 1, C_EYE_ONYX_DEEP);
  } else {
    spr->fillEllipse(erX, erY, 7, 11, C_EYE_ONYX_DEEP);
    spr->fillEllipse(erX, erY, 6, 10, C_EYE_PUPIL_BLK);
    // 3 Điểm bắt sáng pha lê:
    spr->fillEllipse(erX - 1, erY - 4, 3, 2, C_WHITE);       // Điểm 1: Keylight góc 10h
    spr->fillCircle(erX + 2, erY + 4, 2, C_SPEC_BOUNCE);     // Điểm 2: Phản xạ đáy mắt góc 4h
    spr->drawPixel(erX + 3, erY - 1, C_WHITE);               // Điểm 3: Vi điểm bắt sáng
  }

  // 12. LAYER 9: MŨI ĐEN & MIỆNG CƯỜI HẠNH PHÚC LƯỠI HỒNG (Snout & Happy Smile)
  // Mũi chấm đen tí hon
  spr->fillCircle(cx - 6, hy - 1, 1, C_NOSE_BLK);

  // Miệng cười mở rộng hình nêm hạnh phúc
  int mx0 = cx - 13;
  int my0 = hy + 4;
  int mx1 = cx + 2;
  int my1 = hy + 3;
  int mxMid = cx - 6;
  int myMid = hy + 14;

  spr->fillTriangle(mx0, my0, mx1, my1, mxMid, myMid, C_MOUTH_CAVITY);
  // Lưỡi hồng đào nhỏ nhắn hé mở
  spr->fillCircle(mxMid, myMid - 4, 4, C_MOUTH_TONGUE);

  // 13. LAYER 10: HẠT BỤI TĨNH ĐIỆN LÁCH TÁCH QUANH MÁ VÀ ĐUÔI (Floating Electric Sparks)
  spr->drawPixel(clx - 9 + spark1, cly - 4 + spark2, C_SPARK_ELEC);
  spr->drawPixel(txMidSpike + 2 + spark2, tyMidSpike - 4 + spark1, C_SPARK_ELEC);
  spr->drawPixel(wlx - 4 + spark2, wly + 6 + spark1, C_SPARK_ELEC);
  spr->drawPixel(erx + 16 + spark1, ery - 6 + spark2, C_SPARK_ELEC);
}

// -------------------------------------------------------------
// Dedenne - Chuột Ăng-ten Râu Điện
// -------------------------------------------------------------
static void drawDedenneAntennaMouse(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.3f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.5f);
  int by = cy + bounceY;

  // Râu ăng-ten rung rinh trễ pha Delta Phi = 0.45 rad
  float antLag = breathPhase - 0.45f;
  int antWiggle = (int)(sinf(antLag) * 2.5f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_ORANGE      = 0xF442; // #F97316 Cam tươi sáng
  const uint16_t C_ORANGE_DARK = 0xC2E0; // #C2410C Bóng cam
  const uint16_t C_ORANGE_LGT  = 0xFD08; // #FB923C Sáng cam
  const uint16_t C_BELLY       = 0xFF97; // #FEF08A Bụng vàng kem
  const uint16_t C_BELLY_SHAD  = 0xEE73; // #FDE047 Bóng bụng
  const uint16_t C_BLACK       = 0x18C3; // #1E293B Tai & râu đen
  const uint16_t C_CHEEK       = 0xEA80; // #EA580C Má túi điện cam đậm
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Bắt sáng & răng
  const uint16_t C_MOUTH_DARK  = 0x8887; // #881337 Khoang miệng
  const uint16_t C_TONGUE      = 0xF3B6; // #F472B6 Lưỡi hồng
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(28 * (1.0f - 0.15f * breathSin)), 7, C_SHADOW);

  // 2. Chiếc đuôi đen dài uốn lượn vòng ra trước & chóp hoa sao
  spr->drawCircle(cx + 20, by + 28, 12, C_BLACK);
  spr->drawCircle(cx + 20, by + 28, 11, C_BLACK);
  spr->drawLine(cx + 8, by + 24, cx - 18, by + 32, C_BLACK);
  // Chóp đuôi hoa sao đen
  spr->fillTriangle(cx - 24, by + 30, cx - 34, by + 24, cx - 28, by + 36, C_BLACK);
  spr->fillTriangle(cx - 26, by + 32, cx - 34, by + 38, cx - 22, by + 38, C_BLACK);

  // 3. Đôi tai đen tròn to với lòng tai vàng kem
  // Tai trái
  spr->fillCircle(cx - 20, by - 24, 11, C_BLACK);
  spr->fillCircle(cx - 20, by - 24, 8, C_BELLY);
  // Tai phải
  spr->fillCircle(cx + 20, by - 24, 11, C_BLACK);
  spr->fillCircle(cx + 20, by - 24, 8, C_BELLY);

  // 4. Thân quả lê tròn quay núng nính màu cam
  spr->fillEllipse(cx, by + 14, (int)(26 * sX), (int)(24 * sY), C_ORANGE_DARK);
  spr->fillEllipse(cx, by + 12, (int)(24 * sX), (int)(22 * sY), C_ORANGE);
  // Bụng màu vàng kem phồng to
  spr->fillEllipse(cx, by + 18, (int)(18 * sX), (int)(14 * sY), C_BELLY_SHAD);
  spr->fillEllipse(cx, by + 17, (int)(16 * sX), (int)(12 * sY), C_BELLY);

  // 5. Đầu tròn nối liền thân
  spr->fillEllipse(cx, by - 6, (int)(22 * sX), (int)(18 * sY), C_ORANGE_DARK);
  spr->fillEllipse(cx, by - 8, (int)(20 * sX), (int)(16 * sY), C_ORANGE);
  spr->fillEllipse(cx, by - 12, (int)(14 * sX), (int)(8 * sY), C_ORANGE_LGT);

  // 6. Hai chân ngắn xòe ra dưới bụng
  spr->fillRoundRect(cx - 16, by + 32, 10, 6, 2, C_ORANGE_DARK);
  spr->fillRoundRect(cx + 6, by + 32, 10, 6, 2, C_ORANGE_DARK);

  // 7. Râu ăng-ten tivi hai bên má rung rinh
  // Má trái
  spr->drawLine(cx - 16, by + 2, cx - 36, by - 6 + antWiggle, C_BLACK);
  spr->drawLine(cx - 30, by - 8 + antWiggle, cx - 26, by - 2 + antWiggle, C_BLACK); // Râu con
  spr->drawLine(cx - 16, by + 6, cx - 34, by + 14 - antWiggle, C_BLACK);
  // Má phải
  spr->drawLine(cx + 16, by + 2, cx + 36, by - 6 - antWiggle, C_BLACK);
  spr->drawLine(cx + 30, by - 8 - antWiggle, cx + 26, by - 2 - antWiggle, C_BLACK); // Râu con
  spr->drawLine(cx + 16, by + 6, cx + 34, by + 14 + antWiggle, C_BLACK);

  // 8. Má túi điện cam đậm tròn phúng phính
  spr->fillCircle(cx - 16, by + 4, 6, C_CHEEK);
  spr->fillCircle(cx + 16, by + 4, 6, C_CHEEK);

  // 9. Đôi mắt to tròn đen sâu
  if (!blink) {
    spr->fillEllipse(cx - 9, by - 8, 4, 6, C_BLACK);
    spr->fillCircle(cx - 10, by - 11, 2, C_WHITE);
    spr->fillEllipse(cx + 9, by - 8, 4, 6, C_BLACK);
    spr->fillCircle(cx + 8, by - 11, 2, C_WHITE);
  } else {
    spr->drawEllipse(cx - 9, by - 7, 4, 2, C_BLACK);
    spr->drawEllipse(cx + 9, by - 7, 4, 2, C_BLACK);
  }

  // 10. Mũi & Miệng cười với chiếc răng thỏ tí hon
  spr->drawPixel(cx, by - 4, C_BLACK);
  spr->fillTriangle(cx, by + 5, cx - 6, by, cx + 6, by, C_MOUTH_DARK);
  spr->fillCircle(cx, by + 3, 2, C_TONGUE);
  spr->fillRect(cx - 2, by, 4, 2, C_WHITE); // Răng thỏ

  // 11. Hai bàn tay nhỏ ôm đuôi trước bụng
  spr->fillCircle(cx - 6, by + 16, 3, C_ORANGE);
  spr->fillCircle(cx + 6, by + 16, 3, C_ORANGE);
}

// -------------------------------------------------------------
// Morpeko - Chuột Túi No Bụng
// -------------------------------------------------------------
static void drawMorpekoHamster(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.4f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Tai nhỏ lắc lư trễ pha 80ms
  int earWiggle = (int)(sinf(breathPhase - 0.45f) * 2.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_CREAM       = 0xFF97; // #FEF08A Vàng kem giữa
  const uint16_t C_CREAM_SHAD  = 0xEE73; // #FDE047 Bóng vàng kem
  const uint16_t C_BROWN       = 0x9B84; // #A16207 Nâu cà phê phải
  const uint16_t C_BROWN_DARK  = 0x7202; // #713F12 Bóng nâu
  const uint16_t C_CHARCOAL    = 0x31A6; // #334155 Xám than trái
  const uint16_t C_CHARC_DARK  = 0x18C3; // #1E293B Bóng xám than
  const uint16_t C_CHEEK_PINK  = 0xF3B6; // #F472B6 Má hồng đào
  const uint16_t C_BERRY       = 0x8643; // #84CC16 Quả mọng xanh
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Bắt sáng & răng
  const uint16_t C_MOUTH_DARK  = 0x8887; // #881337 Khoang miệng
  const uint16_t C_TONGUE      = 0xF3B6; // #F472B6 Lưỡi hồng
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng tiếp xúc sàn
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Hai tai lá nhỏ (trái xám than, phải nâu)
  spr->fillEllipse(cx - 16, by - 22 + earWiggle, 6, 12, C_BROWN);
  spr->fillEllipse(cx + 16, by - 22 - earWiggle, 6, 12, C_CHARCOAL);

  // 3. Thân hamster tròn vo phân mảng 3 màu
  // Mảng sườn phải nâu
  spr->fillEllipse(cx - 8, by + 12, (int)(18 * sX), (int)(22 * sY), C_BROWN);
  // Mảng sườn trái xám than
  spr->fillEllipse(cx + 8, by + 12, (int)(18 * sX), (int)(22 * sY), C_CHARCOAL);
  // Mảng trung tâm vàng kem với mép zigzag
  spr->fillEllipse(cx, by + 12, (int)(14 * sX), (int)(21 * sY), C_CREAM);
  // Đáy bụng dưới vàng kem
  spr->fillEllipse(cx, by + 24, (int)(18 * sX), (int)(12 * sY), C_CREAM);

  // 4. Khối đầu nối liền thân (Phân 3 mảng)
  spr->fillEllipse(cx - 7, by - 6, (int)(15 * sX), (int)(17 * sY), C_BROWN);
  spr->fillEllipse(cx + 7, by - 6, (int)(15 * sX), (int)(17 * sY), C_CHARCOAL);
  spr->fillEllipse(cx, by - 6, (int)(11 * sX), (int)(16 * sY), C_CREAM);

  // 5. Hai chân hạt đậu vàng kem
  spr->fillRoundRect(cx - 14, by + 32, 9, 6, 3, C_CREAM_SHAD);
  spr->fillRoundRect(cx + 5, by + 32, 9, 6, 3, C_CREAM_SHAD);

  // 6. Má hồng đào tròn xoe
  spr->fillCircle(cx - 15, by + 2, 6, C_CHEEK_PINK);
  spr->fillCircle(cx + 15, by + 2, 6, C_CHEEK_PINK);

  // 7. Đôi mắt pha lê to tròn đen sâu
  if (!blink) {
    spr->fillEllipse(cx - 9, by - 6, 4, 6, C_CHARC_DARK);
    spr->fillCircle(cx - 10, by - 8, 2, C_WHITE);
    spr->fillEllipse(cx + 9, by - 6, 4, 6, C_CHARC_DARK);
    spr->fillCircle(cx + 8, by - 8, 2, C_WHITE);
  } else {
    spr->drawEllipse(cx - 9, by - 5, 4, 2, C_CHARC_DARK);
    spr->drawEllipse(cx + 9, by - 5, 4, 2, C_CHARC_DARK);
  }

  // 8. Mũi & Miệng cười với chiếc răng chuột
  spr->drawPixel(cx, by - 2, C_CHARC_DARK);
  spr->fillTriangle(cx, by + 6, cx - 6, by + 1, cx + 6, by + 1, C_MOUTH_DARK);
  spr->fillCircle(cx, by + 4, 2, C_TONGUE);
  spr->fillRect(cx - 2, by + 1, 4, 3, C_WHITE); // Răng

  // 9. Cánh tay trái giơ lên cầm quả mọng xanh
  spr->fillRoundRect(cx + 12, by + 4, 10, 8, 3, C_CHARCOAL);
  spr->fillCircle(cx + 22, by + 6, 4, C_BERRY);
  spr->drawPixel(cx + 21, by + 5, C_WHITE); // Bắt sáng quả mọng
  // Tay phải ôm sườn
  spr->fillRoundRect(cx - 16, by + 10, 8, 8, 3, C_BROWN);
}

// -------------------------------------------------------------
// Pawmi
// -------------------------------------------------------------
// =========================================================================
// 15_MYTHIC_PAWMI_ELECTRIC_BEAR - C++ ScaledCanvas Implementation
// 100% Hardware Compatible with ESP32 / ESP32-S3 + ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl 3D Sculpt: Warm Orange Fur, Forehead Swirl Tuft,
// Jade Green Inner Ears, Golden Electric Cheeks, Yellow Discharge Paw Pads,
// 3-Point Specular Crystal Eyes, Warm Smiling Mouth.
// Organic Micro-Physics: 5% Volume-Preserving Squash & Stretch,
// Bear Ears Jiggle with Phase Lag Delta Phi = 0.45 rad, Twitching Electric Sparks
// =========================================================================

static void drawPawmiElectricBear(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (Organic Micro-Physics)
  float breathPhase = angle * 2.2f; // Tần số nhịp thở êm ái
  float breathSin   = sinf(breathPhase);

  // Nhịp thở phập phồng Squash & Stretch 5% bảo toàn thể tích (Sy * Sx ≈ 1.0)
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.5f);
  int by = cy + bounceY; // Tọa độ Y động của thân và đầu

  // Hai tai gấu rung rinh trễ pha Delta Phi = 0.45 rad
  float earLag  = breathPhase - 0.45f;
  int earLagL_X = (int)(sinf(earLag) * 3.0f);
  int earLagL_Y = (int)(cosf(earLag) * 2.0f);
  int earLagR_X = (int)(-sinf(earLag) * 2.8f);
  int earLagR_Y = (int)(cosf(earLag) * 1.8f);

  // Chỏm bờm lông trán uốn lượn trễ pha Delta Phi = 0.30 rad
  float tuftLag = breathPhase - 0.30f;
  int tuftSwayX = (int)(sinf(tuftLag) * 2.5f);

  // Xung điện lách tách quanh má và đệm bàn tay (Electric Micro-Sparks)
  int spark1 = (int)(sinf(angle * 16.0f) * 3.5f);
  int spark2 = (int)(cosf(angle * 14.0f) * 3.5f);
  int spark3 = (int)(sinf(angle * 20.0f) * 3.0f);

  // 2. BẢNG MÀU 16-BIT RGB565 CHUẨN XÁC POP MART VINYL
  const uint16_t C_FUR_LIGHT       = 0xFD48; // #FFA947 Đón sáng đỉnh lông cam
  const uint16_t C_FUR_MAIN        = 0xEB63; // #EA6C18 Lông cam ấm áp chủ đạo
  const uint16_t C_FUR_SHADOW      = 0xBA20; // #B84606 Đổ bóng hổ phách lông cam
  const uint16_t C_FUR_DARK        = 0x7940; // #7A2B00 Bóng che khuất sâu rãnh nếp gấp
  const uint16_t C_TUFT_LIGHT      = 0xFDAC; // #FFB660 Highlight sống bờm lông trán
  const uint16_t C_TUFT_MAIN       = 0xF383; // #F0731E Chỏm bờm lông trán mềm mại
  const uint16_t C_TUFT_SHADOW     = 0xA1C0; // #A33800 Bóng chân bờm lông
  const uint16_t C_EAR_TEAL_LIGHT  = 0x1593; // #17B29F Viền sáng ngọc bích lòng tai
  const uint16_t C_EAR_TEAL_MAIN   = 0x0C2E; // #0D8374 Xanh lá ngọc bích lòng tai độc bản
  const uint16_t C_EAR_TEAL_DARK   = 0x02AA; // #07554B Hốc sâu xanh ngọc bích
  const uint16_t C_CHEEK_LIGHT     = 0xFFB0; // #FFF385 Highlight má túi điện
  const uint16_t C_CHEEK_MAIN      = 0xFEC8; // #F8D847 Má túi điện vàng hoàng kim
  const uint16_t C_CHEEK_SHADOW    = 0xE5A4; // #E2B522 Đổ bóng hổ phách má túi điện
  const uint16_t C_CREAM_LIGHT     = 0xFFFA; // #FFF5E4 Đón sáng vòm mõm kem
  const uint16_t C_CREAM_MAIN      = 0xFEF8; // #FCE5C0 Mõm kem & cẳng tay gấu Chibi
  const uint16_t C_CREAM_SHADOW    = 0xDDC1; // #DDBA8F Bóng kem dưới cằm & cổ tay
  const uint16_t C_PAW_PAD_YELLOW  = 0xFF20; // #FFE600 Đệm phóng điện vàng phát sáng
  const uint16_t C_PAW_PAD_GLOW    = 0xFFD4; // #FFF9A6 Lõi chói lòa đệm phóng điện
  const uint16_t C_EYE_RIM         = 0x1882; // #1A1115 Viền mí mắt đen tuyền Chibi
  const uint16_t C_EYE_PUPIL       = 0x20C3; // #25181E Tròng mắt đen nhánh hạt pha lê
  const uint16_t C_EYE_AMBER       = 0xDBC6; // #D97736 Phản xạ caustic đáy mắt hổ phách
  const uint16_t C_WHITE           = 0xFFFF; // #FFFFFF 3 Điểm bắt sáng pha lê tinh khiết
  const uint16_t C_NOSE_BLACK      = 0x18A3; // #1E1418 Sống mũi đen nhỏ xinh
  const uint16_t C_MOUTH_LINE      = 0x6183; // #663319 Nét cười ấm áp ngây thơ
  const uint16_t C_MOUTH_TONGUE    = 0xFBC2; // #FF7A90 Lưỡi hồng đào nhỏ nhắn
  const uint16_t C_HIND_PAW        = 0xBA82; // #BD5213 Bàn chân sau sườn phải
  const uint16_t C_TAIL_CREAM      = 0xF6F8; // #F6DEC0 Đuôi kem phúng phính vểnh sau
  const uint16_t C_TAIL_SHADOW     = 0xD570; // #D4AC82 Đổ bóng gốc đuôi kem
  const uint16_t C_SPARK_EMERALD   = 0x07BA; // #00F5D4 Tia chớp ngọc bích lách tách
  const uint16_t C_CONTACT_SHADOW  = 0x2881; // #28140A Bóng tiếp xúc sàn co giãn

  // 3. LAYER 0: BÓNG TIẾP XÚC MẶT SÀN CO GIÃN ÊM ÁI (Ground Contact Shadow)
  int shadowW = (int)(80.0f * sX);
  int shadowH = (int)(15.0f * sX);
  spr->fillEllipse(cx - 2, cy + 86, shadowW, shadowH, C_CONTACT_SHADOW);
  spr->fillEllipse(cx - 2, cy + 86, (int)(shadowW * 0.65f), (int)(shadowH * 0.6f), 0x1840);

  // 4. LAYER 1: ĐUÔI KEM & BÀN CHÂN SAU (Tail & Hind Foot)
  // Đuôi kem vểnh sau lưng bên phải
  spr->fillEllipse(cx + 74 + tuftSwayX, by - 48, 14, 28, C_TAIL_CREAM);
  spr->fillCircle(cx + 78 + tuftSwayX, by - 62, 11, C_TAIL_CREAM);
  spr->fillCircle(cx + 70 + tuftSwayX, by - 36, 9, C_TAIL_SHADOW);

  // Bàn chân sau phải peeking out dưới sườn phải
  spr->fillRoundRect(cx + 80, by + 64, 18, 12, 4, C_HIND_PAW);
  spr->fillCircle(cx + 95, by + 70, 4, C_HIND_PAW);
  spr->drawPixel(cx + 86, by + 74, C_FUR_DARK);
  spr->drawPixel(cx + 91, by + 74, C_FUR_DARK);

  // 5. LAYER 2: THÂN HÌNH QUẢ CẦU BÉO MẬP CHIBI POP MART (Rotund Torso Sphere)
  int bodyW = (int)(72.0f * sX);
  int bodyH = (int)(62.0f * sY);
  spr->fillEllipse(cx + 34, by + 22, bodyW, bodyH, C_FUR_MAIN);
  spr->fillEllipse(cx + 44, by + 8, (int)(46 * sX), (int)(36 * sY), C_FUR_LIGHT);
  spr->fillEllipse(cx + 30, by + 42, (int)(56 * sX), (int)(26 * sY), C_FUR_SHADOW);

  // 6. LAYER 3: ĐÔI TAI GẤU TRÒN TO VỚI LÒNG TAI XANH NGỌC BÍCH (Bear Ears & Jade Inners)
  // Tai trái (viewer's left - vươn cao góc 75 độ)
  int eLx = cx - 64 + earLagL_X;
  int eLy = by - 56 + earLagL_Y;
  // Vành ngoài tai cam
  spr->fillEllipse(eLx, eLy, 22, 44, C_FUR_MAIN);
  spr->fillEllipse(eLx - 3, eLy - 8, 16, 34, C_FUR_LIGHT);
  // Lòng tai xanh lá ngọc bích độc bản (Emerald Jade Inners)
  spr->fillEllipse(eLx + 1, eLy + 1, 14, 30, C_EAR_TEAL_DARK);
  spr->fillEllipse(eLx + 1, eLy + 1, 11, 26, C_EAR_TEAL_MAIN);
  spr->fillEllipse(eLx, eLy - 4, 7, 18, C_EAR_TEAL_LIGHT);
  // Nếp gấp chân tai màu kem
  spr->fillCircle(eLx + 8, eLy + 26, 7, C_CREAM_MAIN);

  // Tai phải (viewer's right - nghiêng nhẹ góc 62 độ)
  int eRx = cx + 34 + earLagR_X;
  int eRy = by - 54 + earLagR_Y;
  // Vành ngoài tai cam
  spr->fillEllipse(eRx, eRy, 22, 44, C_FUR_MAIN);
  spr->fillEllipse(eRx + 3, eRy - 8, 16, 34, C_FUR_LIGHT);
  // Lòng tai xanh ngọc bích độc bản
  spr->fillEllipse(eRx - 1, eRy + 1, 14, 30, C_EAR_TEAL_DARK);
  spr->fillEllipse(eRx - 1, eRy + 1, 11, 26, C_EAR_TEAL_MAIN);
  spr->fillEllipse(eRx, eRy - 4, 7, 18, C_EAR_TEAL_LIGHT);
  // Nếp gấp chân tai màu kem
  spr->fillCircle(eRx - 7, eRy + 26, 7, C_CREAM_MAIN);

  // 7. LAYER 4: KHỐI ĐẦU TRÒN & CHỎM BỜM LÔNG TRÊN TRÁN NHÔ CAO (Head & Forehead Tuft)
  // Khối đầu tròn phúng phính
  int headW = (int)(68.0f * sX);
  int headH = (int)(54.0f * sY);
  spr->fillEllipse(cx - 15, by + 18, headW, headH, C_FUR_MAIN);
  spr->fillEllipse(cx - 22, by + 2, (int)(38 * sX), (int)(24 * sY), C_FUR_LIGHT);

  // Chỏm bờm lông trên trán nhô cao mềm mại uốn lượn sang phải (Forehead Swirl Tuft)
  int tBaseX = cx - 12 + tuftSwayX;
  int tBaseY = by - 36;
  spr->fillEllipse(tBaseX - 6, tBaseY - 10, 24, 30, C_TUFT_SHADOW);
  spr->fillEllipse(tBaseX - 3, tBaseY - 12, 23, 28, C_TUFT_MAIN);
  // Múi uốn lượn nhô cao vươn đỉnh
  spr->fillCircle(tBaseX + 6, tBaseY - 26, 16, C_TUFT_MAIN);
  spr->fillCircle(tBaseX + 12, tBaseY - 32, 12, C_TUFT_LIGHT);
  spr->fillTriangle(tBaseX + 8, tBaseY - 42, tBaseX + 24, tBaseY - 24, tBaseX + 2, tBaseY - 24, C_TUFT_MAIN);
  spr->fillEllipse(tBaseX + 6, tBaseY - 24, 11, 8, C_TUFT_LIGHT); // Highlight đỉnh bờm

  // 8. LAYER 5: HAI MÁ TÚI ĐIỆN VÀNG HOÀNG KIM PHÚNG PHÍNH (Golden Electric Cheeks)
  // Má trái
  int chLx = cx - 68;
  int chLy = by + 38;
  spr->fillEllipse(chLx, chLy, 25, 23, C_CHEEK_SHADOW);
  spr->fillEllipse(chLx, chLy - 1, 24, 22, C_CHEEK_MAIN);
  spr->fillCircle(chLx - 5, chLy - 6, 10, C_CHEEK_LIGHT);

  // Má phải
  int chRx = cx + 38;
  int chRy = by + 38;
  spr->fillEllipse(chRx, chRy, 25, 23, C_CHEEK_SHADOW);
  spr->fillEllipse(chRx, chRy - 1, 24, 22, C_CHEEK_MAIN);
  spr->fillCircle(chRx - 3, chLy - 6, 10, C_CHEEK_LIGHT);

  // 9. LAYER 6: MÕM KEM, MŨI ĐEN NHỎ & NỤ CƯỜI ẤM ÁP (Snout, Nose & Smile)
  int snX = cx - 15;
  int snY = by + 44;
  spr->fillEllipse(snX, snY + 2, 28, 19, C_CREAM_SHADOW);
  spr->fillEllipse(snX, snY, 27, 18, C_CREAM_MAIN);
  spr->fillEllipse(snX, snY - 5, 16, 9, C_CREAM_LIGHT);

  // Mũi đen nhỏ xinh
  spr->fillCircle(snX, snY - 8, 3, C_NOSE_BLACK);
  spr->drawPixel(snX - 1, snY - 9, C_WHITE);

  // Miệng cười ấm áp ngây thơ
  spr->drawLine(snX - 7, snY - 1, snX, snY + 4, C_MOUTH_LINE);
  spr->drawLine(snX, snY + 4, snX + 7, snY - 1, C_MOUTH_LINE);
  spr->fillCircle(snX, snY + 2, 2, C_MOUTH_TONGUE);

  // 10. LAYER 7: ĐÔI MẮT PHA LÊ TO TRÒN ĐEN NHÁNH 3 ĐIỂM BẮT SÁNG (Crystal Black Eyes)
  for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
    int ex = (eyeIdx == 0) ? (cx - 44) : (cx + 14);
    int ey = by + 22;

    if (blink) {
      // Mí mắt nhắm cong hình lưỡi liềm ngọt ngào
      spr->drawEllipse(ex, ey + 3, 13, 4, C_EYE_RIM);
      spr->drawLine(ex - 10, ey + 3, ex - 14, ey, C_EYE_RIM);
      spr->drawLine(ex + 10, ey + 3, ex + 14, ey, C_EYE_RIM);
    } else {
      // Viền mí & hốc mắt đen tuyền
      spr->fillEllipse(ex, ey, 14, 16, C_EYE_RIM);
      // Tròng mắt đen nhánh hạt pha lê
      spr->fillEllipse(ex, ey, 13, 15, C_EYE_PUPIL);
      // Cung phản xạ caustic đáy mắt hổ phách lấp lánh
      spr->fillEllipse(ex, ey + 6, 10, 7, C_EYE_AMBER);
      spr->fillCircle(ex, ey + 2, 8, C_EYE_PUPIL); // Đồng tử

      // 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Specular Highlights)
      // Điểm 1: Primary Keylight Specular (Bầu dục sáng to, góc 11h)
      spr->fillEllipse(ex - 3, ey - 5, 5, 3, C_WHITE);
      // Điểm 2: Secondary Caustic Specular (Tròn vừa, góc 5h)
      spr->fillCircle(ex + 3, ey + 4, 3, C_WHITE);
      // Điểm 3: Tertiary Micro Glint (Tia sáng vi điểm mép ngoài)
      spr->drawPixel(ex + 6, ey - 2, C_WHITE);
    }
  }

  // 11. LAYER 8: HAI BÀN TAY GẤU TO TRÒN & ĐỆM PHÓNG ĐIỆN VÀNG (Paws & Discharge Pads)
  // Tay trái (viewer's left - chống bên sườn trái)
  int pLx = cx - 78;
  int pLy = by + 76;
  // Cẳng tay lông cam
  spr->fillRoundRect(pLx - 14, pLy - 26, 28, 22, 8, C_FUR_MAIN);
  // Bàn tay lông kem với 3 múi ngón chạm đất
  spr->fillRoundRect(pLx - 16, pLy - 6, 32, 17, 7, C_CREAM_MAIN);
  spr->fillCircle(pLx - 11, pLy + 10, 4, C_CREAM_MAIN);
  spr->fillCircle(pLx,      pLy + 11, 4, C_CREAM_MAIN);
  spr->fillCircle(pLx + 11, pLy + 10, 4, C_CREAM_MAIN);
  spr->drawLine(pLx - 5, pLy + 7, pLx - 5, pLy + 13, C_CREAM_SHADOW);
  spr->drawLine(pLx + 5, pLy + 7, pLx + 5, pLy + 13, C_CREAM_SHADOW);
  // Đệm lòng bàn tay phóng điện màu vàng phát sáng (Yellow Discharge Pad)
  spr->fillEllipse(pLx, pLy + 2, 10, 6, C_PAW_PAD_YELLOW);
  spr->fillEllipse(pLx, pLy + 2, 6, 3, C_PAW_PAD_GLOW);
  spr->drawPixel(pLx, pLy + 2, C_WHITE);

  // Tay phải (viewer's right - chống bên sườn phải)
  int pRx = cx + 48;
  int pRy = by + 78;
  // Cẳng tay lông cam
  spr->fillRoundRect(pRx - 14, pRy - 26, 28, 22, 8, C_FUR_MAIN);
  // Bàn tay lông kem với 3 múi ngón
  spr->fillRoundRect(pRx - 16, pRy - 6, 32, 17, 7, C_CREAM_MAIN);
  spr->fillCircle(pRx - 11, pRy + 10, 4, C_CREAM_MAIN);
  spr->fillCircle(pRx,      pRy + 11, 4, C_CREAM_MAIN);
  spr->fillCircle(pRx + 11, pRy + 10, 4, C_CREAM_MAIN);
  spr->drawLine(pRx - 5, pRy + 7, pRx - 5, pRy + 13, C_CREAM_SHADOW);
  spr->drawLine(pRx + 5, pRy + 7, pRx + 5, pRy + 13, C_CREAM_SHADOW);
  // Đệm lòng bàn tay phóng điện màu vàng phát sáng
  spr->fillEllipse(pRx, pRy + 2, 10, 6, C_PAW_PAD_YELLOW);
  spr->fillEllipse(pRx, pRy + 2, 6, 3, C_PAW_PAD_GLOW);
  spr->drawPixel(pRx, pRy + 2, C_WHITE);

  // 12. LAYER 9: XUNG ĐIỆN LÁCH TÁCH & TIA LỬA PLASMA (Electric Sparks)
  // Tia lửa má trái
  spr->fillCircle(chLx - 18 + spark1, chLy + spark2, 3, C_CHEEK_LIGHT);
  spr->drawPixel(chLx - 18 + spark1, chLy + spark2, C_WHITE);
  // Tia lửa má phải
  spr->fillCircle(chRx + 18 + spark2, chRy + spark1, 3, C_CHEEK_LIGHT);
  spr->drawPixel(chRx + 18 + spark2, chRy + spark1, C_WHITE);
  // Tia chớp ngọc bích trên đỉnh tai
  spr->fillCircle(eLx - 8 + spark3, eLy - 24, 3, C_SPARK_EMERALD);
  spr->drawPixel(eLx - 8 + spark3, eLy - 24, C_WHITE);
  // Tia chớp đệm tay phải
  spr->fillCircle(pRx + 16 + spark1, pRy + spark3, 3, C_PAW_PAD_YELLOW);
  spr->drawPixel(pRx + 16 + spark1, pRy + spark3, C_WHITE);
}

} // namespace Session3Mythics
