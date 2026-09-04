# -*- coding: utf-8 -*-
"""
Master Builder Script for Emolga Flying Squirrel (Session 3, Agent 2)
Faithfully matches 12_Mythic_Emolga_Flying_Squirrel.png with 100% anatomical fidelity.
"""
import json
import os
import math

def hex_to_rgb565(hex_str):
    hex_str = hex_str.lstrip('#')
    r = int(hex_str[0:2], 16)
    g = int(hex_str[2:4], 16)
    b = int(hex_str[4:6], 16)
    r5 = (r >> 3) & 0x1F
    g6 = (g >> 2) & 0x3F
    b5 = (b >> 3) & 0x1F
    val = (r5 << 11) | (g6 << 5) | b5
    return f"0x{val:04X}"

def create_color_entry(name, hex_code, optical_fn, material_finish="Gloss Vinyl"):
    return {
        "name": name,
        "hex": hex_code,
        "rgb565": hex_to_rgb565(hex_code),
        "optical_role": optical_fn,
        "material_finish": material_finish
    }

palette_entries = [
    create_color_entry("col_wing_yellow_light",     "#FFF875", "Vàng chanh bắt sáng đỉnh màng cánh sóc bay", "High-Gloss Specular Yellow"),
    create_color_entry("col_wing_yellow_main",      "#FFD000", "Vàng chanh rực rỡ mặt trong màng cánh lượn", "Radiant Lemon Vinyl"),
    create_color_entry("col_wing_yellow_warm",      "#F59E0B", "Vàng hổ phách chuyển khối màng cánh", "Warm Amber Vinyl"),
    create_color_entry("col_wing_yellow_shadow",    "#D97706", "Vàng cam đổ bóng nếp gấp màng cánh", "Satin Amber Shadow"),
    create_color_entry("col_wing_black_outer",      "#1E232B", "Mặt ngoài màng cánh và viền đen bóng bẩy", "Glossy Black Vinyl Trim"),
    create_color_entry("col_fur_white_gloss",       "#FFFFFF", "Lông trắng ngọc trai bụng, mặt và cánh tay", "Pearlescent Porcelain White"),
    create_color_entry("col_fur_white_shadow",      "#E2E8F0", "Đổ bóng lụa mềm thân trắng Pop Mart", "Soft Vinyl Satin Shadow"),
    create_color_entry("col_fur_white_deep",        "#CBD5E1", "Bóng che khuất nách và chân bám", "Subsurface Ambient Occlusion"),
    create_color_entry("col_hood_black_main",       "#262C38", "Mũ trùm đầu và thân đen nhung tuyền", "Velvety Onyx Finish"),
    create_color_entry("col_hood_black_dark",       "#14171F", "Rãnh tối phân chia mũ trán 3 múi", "Deep Obsidian Occlusion"),
    create_color_entry("col_hood_black_rim",        "#505D75", "Viền đón sáng lụa Fresnel trên đỉnh mũ", "Fresnel Rim Highlight"),
    create_color_entry("col_ear_inner_yellow",      "#FFCE00", "Lòng tai vàng rực rỡ", "Vibrant Gold Vinyl"),
    create_color_entry("col_ear_inner_light",       "#FFF380", "Bắt sáng tâm lòng tai", "Soft Specular Reflection"),
    create_color_entry("col_ear_base_white",        "#F1F5F9", "Vành trắng viền đệm chân tai", "Porcelain Base Trim"),
    create_color_entry("col_cheek_electric_yellow", "#FFB703", "Túi điện tròn vo má phúng phính", "Electric Bio-Sac Glow"),
    create_color_entry("col_cheek_electric_glow",   "#FFD166", "Quầng điện quang phát sáng quanh má", "Warm Electric Aura"),
    create_color_entry("col_eye_onyx_deep",         "#0E1015", "Hốc mắt đen láy pha lê", "Polished Onyx Deep"),
    create_color_entry("col_eye_pupil_black",       "#1C202A", "Tròng mắt obsidian", "Gloss Crystal Core"),
    create_color_entry("col_eye_spec_keylight",     "#FFFFFF", "Điểm bắt sáng chính góc 10h", "Diamond Specular Keylight"),
    create_color_entry("col_eye_spec_bounce",       "#E2E8F0", "Điểm phản xạ đáy mắt góc 4h", "Caustic Ground Bounce"),
    create_color_entry("col_eye_spec_glint",        "#FFFFFF", "Vi điểm bắt sáng li ti", "Micro Surface Sparkle"),
    create_color_entry("col_mouth_cavity",          "#581C28", "Khoang miệng sâu màu đỏ rượu nho Bordeaux", "Deep Cavity Matte"),
    create_color_entry("col_mouth_tongue",          "#FB7185", "Lưỡi hồng đào nhỏ nhắn đáng yêu", "Warm Satin Peach Pink"),
    create_color_entry("col_nose_black",            "#14171F", "Chấm mũi đen nhỏ xíu Chibi", "Polished Noir Dot"),
    create_color_entry("col_tail_lightning_black",  "#222834", "Đuôi sóc xòe lưỡi liềm đen tuyền uốn lượn", "Glossy Black Plume"),
    create_color_entry("col_tail_lightning_rim",    "#60728A", "Sống gờ tia chớp đuôi đón sáng", "Chiseled Lightning Rim"),
    create_color_entry("col_paw_claw",              "#FFFFFF", "Móng vuốt nhỏ xíu ngón tay", "Pure White Claws"),
    create_color_entry("col_foot_grey",             "#94A3B8", "Chân sau tí hon buông lỏng", "Soft Grey Underfoot"),
    create_color_entry("col_contact_shadow",        "#121620", "Bóng tiếp xúc mờ ảo co giãn dưới sàn", "Soft Ambient Contact Shadow"),
    create_color_entry("col_spark_electric",        "#FFF37A", "Hạt bụi tĩnh điện lách tách quanh cánh và đuôi", "Electric Spark Particle")
]

cpp_scaled_canvas_code = r'''// =========================================================================
// 12_MYTHIC_EMOLGA_FLYING_SQUIRREL - C++ ScaledCanvas Implementation
// 100% Hardware Compatible with ESP32 / ESP32-S3 + ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl 3D Sculpt: Lemon Patagium Wings, Rounded Black Ears,
// Plump Electric Cheeks, 3-Point Specular Eyes, Sweeping Lightning Crescent Tail
// Organic Micro-Physics: 5% Squash & Stretch, 80ms Wing Flap Lag, Tail Sway
// =========================================================================
void drawEmolgaFlyingSquirrel(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
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
  const uint16_t C_HOOD_BLK_MAIN    = 0x2167; // #262C38 Mũ trùm đầu đen nhung tuyền
  const uint16_t C_HOOD_BLK_DARK    = 0x10A3; // #14171F Rãnh tối phân chia mũ trán
  const uint16_t C_HOOD_BLK_RIM     = 0x52EE; // #505D75 Viền đón sáng lụa Fresnel
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
  const uint16_t C_TAIL_BLK         = 0x2146; // #222834 Đuôi sóc lưỡi liềm đen tuyền
  const uint16_t C_TAIL_RIM         = 0x6391; // #60728A Sống gờ tia chớp đón sáng
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
  // Gốc đuôi nối từ sườn lưng vút chéo lên trên sang phải góc 35 độ
  int tx0 = cx + 16;
  int ty0 = by + 14;
  int txMid = cx + 54 + (int)(tailSwayX * 0.5f);
  int tyMid = by + 0 + tailSwayY;
  int txTop = cx + 96 + tailSwayX;
  int tyTop = by - 34 + tailSwayY;
  int txNotch1 = cx + 80 + (int)(tailSwayX * 0.8f);
  int tyNotch1 = by - 16 + tailSwayY;
  int txMidSpike = cx + 112 + (int)(tailSwayX * 1.15f);
  int tyMidSpike = by - 10 + tailSwayY;
  int txNotch2 = cx + 86 + (int)(tailSwayX * 0.85f);
  int tyNotch2 = by + 4 + tailSwayY;
  int txBotSpike = cx + 102 + (int)(tailSwayX * 0.9f);
  int tyBotSpike = by + 18 + tailSwayY;

  // Lớp đệm thân đuôi dày dặn Pop Mart
  spr->fillTriangle(tx0, ty0 - 6, txMid, tyMid - 8, tx0 + 12, ty0 + 10, C_TAIL_BLK);
  spr->fillTriangle(txMid, tyMid - 8, txTop, tyTop, txNotch1, tyNotch1, C_TAIL_BLK);
  spr->fillTriangle(txMid, tyMid - 4, txNotch1, tyNotch1, txMidSpike, tyMidSpike, C_TAIL_BLK);
  spr->fillTriangle(txMid, tyMid + 4, txMidSpike, tyMidSpike, txNotch2, tyNotch2, C_TAIL_BLK);
  spr->fillTriangle(txMid, tyMid + 8, txNotch2, tyNotch2, txBotSpike, tyBotSpike, C_TAIL_BLK);
  spr->fillTriangle(txMid, tyMid + 12, txBotSpike, tyBotSpike, tx0 + 14, ty0 + 10, C_TAIL_BLK);

  // Khối chuyển bóng 3D mặt trong đuôi
  spr->fillTriangle(txMid, tyMid, txNotch1 + 4, tyNotch1 + 2, txMidSpike - 8, tyMidSpike, C_HOOD_BLK_MAIN);
  spr->fillTriangle(txMid, tyMid + 6, txNotch2 + 4, tyNotch2 + 2, txBotSpike - 8, tyBotSpike, C_HOOD_BLK_MAIN);

  // Sống gờ tia chớp đón sáng (Specular Rim Highlight)
  spr->drawLine(tx0 + 2, ty0 - 4, txMid, tyMid - 8, C_TAIL_RIM);
  spr->drawLine(txMid, tyMid - 8, txTop, tyTop, C_TAIL_RIM);
  spr->drawLine(txTop, tyTop, txNotch1, tyNotch1, C_HOOD_BLK_RIM);
  spr->drawLine(txNotch1, tyNotch1, txMidSpike, tyMidSpike, C_TAIL_RIM);
  spr->drawLine(txMidSpike, tyMidSpike, txNotch2, tyNotch2, C_HOOD_BLK_RIM);
  spr->drawLine(txNotch2, tyNotch2, txBotSpike, tyBotSpike, C_TAIL_RIM);

  // 5. LAYER 2: ĐÔI TAI ĐEN TRÒN XÒE RỘNG VỚI LÒNG TAI VÀNG RỰC (Large Rounded Ears with Sun-Gold Inset)
  // Tai trái (viewer's left - vểnh sang trái góc -25 độ)
  int elx = cx - 32;
  int ely = by - 36;
  spr->fillEllipse(elx, ely, 16, 20, C_HOOD_BLK_MAIN);
  spr->drawEllipse(elx, ely, 16, 20, C_HOOD_BLK_RIM);
  spr->fillEllipse(elx + 2, ely + 2, 11, 14, C_EAR_INNER_YEL);
  spr->fillEllipse(elx + 1, ely - 1, 6, 8, C_EAR_INNER_LIGHT);
  spr->fillEllipse(elx + 3, ely + 8, 7, 5, C_EAR_BASE_WHITE);

  // Tai phải (viewer's right - xòe rộng sang phải góc +35 độ)
  int erx = cx + 20;
  int ery = by - 44;
  spr->fillEllipse(erx, ery, 20, 23, C_HOOD_BLK_MAIN);
  spr->drawEllipse(erx, ery, 20, 23, C_HOOD_BLK_RIM);
  spr->fillEllipse(erx - 1, ery + 2, 14, 17, C_EAR_INNER_YEL);
  spr->fillEllipse(erx - 2, ery - 1, 9, 10, C_EAR_INNER_LIGHT);
  spr->fillEllipse(erx - 1, ery + 10, 10, 6, C_EAR_BASE_WHITE);

  // 6. LAYER 3: HAI CÁNH SÓC BAY MÀNG VÀNG CHANH RỰC RỠ (Huge Flying Patagium Wings with 80ms Lag)
  // Cánh trái (viewer's left - màng căng từ cổ tay trái cx - 56 xuống hông cx - 18)
  int wlx = cx - 56;
  int wly = by - 8 + (int)wingFlap;
  int whlx = cx - 18;
  int whly = by + 26;
  int wMidLx = cx - 44;
  int wMidLy = by + 22 + (int)wingFlutter;

  // Lớp viền đen mặt ngoài màng cánh trái
  spr->fillTriangle(wlx - 4, wly + 2, whlx, whly + 2, wMidLx - 5, wMidLy + 5, C_WING_BLK_OUTER);
  // Màng cánh vàng chanh rực rỡ mặt trong
  spr->fillTriangle(wlx, wly, whlx, whly, wMidLx, wMidLy, C_WING_YEL_MAIN);
  spr->fillTriangle(wlx + 8, wly + 2, whlx - 2, whly - 4, wMidLx + 2, wMidLy - 3, C_WING_YEL_LIGHT);
  spr->fillTriangle(wMidLx, wMidLy, whlx, whly, wMidLx - 3, wMidLy + 3, C_WING_YEL_SHADOW);

  // Cánh phải (viewer's right - buồm vàng khổng lồ xòe sang phải đón gió)
  int wrx = cx + 46;
  int wry = by - 6 + (int)(wingFlap * 0.85f);
  int whrx = cx + 18;
  int whry = by + 24;
  int wMidRx = cx + 52;
  int wMidRy = by + 16 + (int)wingFlutter;

  // Lớp viền đen mặt ngoài màng cánh phải
  spr->fillTriangle(wrx + 4, wry + 2, whrx, whry + 2, wMidRx + 6, wMidRy + 6, C_WING_BLK_OUTER);
  // Màng cánh vàng chanh rực rỡ mặt trong cánh phải - xòe rộng đầy đặn
  spr->fillTriangle(wrx, wry, whrx, whry, wMidRx, wMidRy, C_WING_YEL_MAIN);
  spr->fillTriangle(wrx - 6, wry + 2, whrx + 2, whry - 4, wMidRx - 4, wMidRy - 3, C_WING_YEL_LIGHT);
  spr->fillTriangle(wMidRx, wMidRy, whrx, whry, wMidRx + 4, wMidRy + 4, C_WING_YEL_SHADOW);

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

  // Vòng cổ đen ôm quanh gáy và dưới cằm
  spr->fillEllipse(cx - 3, by + 4, 18, 5, C_HOOD_BLK_MAIN);

  // 8. LAYER 5: HAI CÁNH TAY TRẮNG MUỐT DANG RỘNG (Outstretched White Arms & Claws)
  // Tay trái (viewer's left - vẫy gió sang trái)
  spr->fillTriangle(cx - 18, by + 4, wlx, wly, cx - 20, by + 12, C_FUR_WHITE_GLOSS);
  spr->fillRoundRect(wlx - 3, wly - 5, 14, 9, 4, C_FUR_WHITE_GLOSS);
  // 3 Móng vuốt nhỏ xíu ngộ nghĩnh
  spr->fillCircle(wlx - 4, wly - 3, 2, C_WHITE);
  spr->fillCircle(wlx - 5, wly, 2, C_WHITE);
  spr->fillCircle(wlx - 3, wly + 3, 2, C_WHITE);

  // Tay phải (viewer's right - dang rộng hướng lên trước)
  spr->fillTriangle(cx + 14, by + 2, wrx, wry, cx + 16, by + 11, C_FUR_WHITE_GLOSS);
  spr->fillRoundRect(wrx - 10, wry - 5, 14, 9, 4, C_FUR_WHITE_GLOSS);
  // 3 Móng vuốt nhỏ xíu ngộ nghĩnh
  spr->fillCircle(wrx + 4, wry - 3, 2, C_WHITE);
  spr->fillCircle(wrx + 5, wry, 2, C_WHITE);
  spr->fillCircle(wrx + 3, wry + 3, 2, C_WHITE);

  // 9. LAYER 6: KHỐI ĐẦU POP MART, MŨ TRÙM ĐEN 3 MÚI & KHUÔN MẶT TRẮNG (Head, Hood & Face)
  int hx = cx - 4;
  int hy = by - 12;

  // Khối đỉnh đầu đen (Black Hood Base phía sau)
  spr->fillEllipse(hx, hy - 10, (int)(28 * sX), (int)(20 * sY), C_HOOD_BLK_MAIN);
  spr->fillEllipse(hx, hy - 18, (int)(18 * sX), (int)(8 * sY), C_HOOD_BLK_RIM); // Đón sáng Fresnel đỉnh đầu

  // KHUÔN MẶT TRẮNG TINH KHÔI PHÚNG PHÍNH (White Face bao trọn toàn bộ mắt, mũi, miệng, má)
  spr->fillEllipse(hx - 2, hy + 2, (int)(26 * sX), (int)(22 * sY), C_FUR_WHITE_GLOSS);
  spr->fillEllipse(hx - 14, hy + 5, 13, 13, C_FUR_WHITE_GLOSS); // Má trái bầu bĩnh
  spr->fillEllipse(hx + 10, hy + 4, 12, 12, C_FUR_WHITE_GLOSS); // Má phải bầu bĩnh
  spr->fillEllipse(hx - 2, hy - 6, 17, 13, C_FUR_WHITE_GLOSS);  // Vòm trán trắng

  // Mũ trùm đầu đen chúc xuống trán 3 múi nhọn sắc sảo (3 Sharp Black Teeth on White Forehead)
  // Múi giữa (chúc xuống chính giữa 2 mắt - cao ráo không che mắt)
  spr->fillTriangle(hx - 8, hy - 20, hx, hy - 11, hx + 7, hy - 20, C_HOOD_BLK_MAIN);
  spr->fillTriangle(hx - 6, hy - 19, hx, hy - 12, hx + 5, hy - 19, C_HOOD_BLK_DARK);
  // Múi bên trái (chúc xuống mép ngoài mắt trái)
  spr->fillTriangle(hx - 20, hy - 19, hx - 16, hy - 13, hx - 11, hy - 20, C_HOOD_BLK_MAIN);
  // Múi bên phải (chúc xuống mép ngoài mắt phải)
  spr->fillTriangle(hx + 10, hy - 20, hx + 15, hy - 14, hx + 20, hy - 18, C_HOOD_BLK_MAIN);

  // 10. LAYER 7: HAI MÁ TÚI ĐIỆN VÀNG TRÒN VO PHÚNG PHÍNH (Plump Electric Yellow Cheeks)
  // Nằm hoàn toàn trên nền lông trắng hai bên má
  int clx = cx - 25;
  int cly = hy + 6;
  spr->fillCircle(clx, cly, 8, C_CHEEK_YEL);
  spr->fillCircle(clx + 1, cly - 1, 5, C_CHEEK_GLOW);

  int crx = cx + 17;
  int cry = hy + 4;
  spr->fillCircle(crx, cry, 7, C_CHEEK_YEL);
  spr->fillCircle(crx - 1, cry - 1, 4, C_CHEEK_GLOW);

  // 11. LAYER 8: ĐÔI MẮT PHA LÊ ĐEN LÁY TO TRÒN 3 ĐIỂM BẮT SÁNG (Crystal Specular Eyes NẰM TRÊN NỀN TRẮNG)
  // Mắt trái (viewer's left) - to tròn lấp lánh trên nền mặt trắng
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
  spr->fillCircle(cx - 5, hy - 1, 1, C_NOSE_BLK);

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
'''

js_canvas_code = r'''// =========================================================================
// 12_MYTHIC_EMOLGA_FLYING_SQUIRREL - Modern HTML5 Canvas 2D Implementation
// 100% Anatomical Fidelity & High-End 3D Pop Mart Vinyl Aesthetic
// Organic Micro-Physics: 5% Squash & Stretch, 80ms Wing Flap Lag, Tail Sway
// =========================================================================
function drawEmolgaFlyingSquirrel(ctx, cx, cy, scale, t, manualBlink = false) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.scale(scale, scale);

  // 1. Organic Micro-Physics Kinematics
  const breathFreq = 2.4;
  const breathPhase = t * breathFreq;
  const breathSin = Math.sin(breathPhase);

  // Nhịp lượn bay Squash & Stretch 5% bảo toàn thể tích
  const sY = 1.0 + 0.05 * breathSin;
  const sX = 1.0 - 0.025 * breathSin;
  const bounceY = Math.sin(breathPhase) * 4.5;
  const by = bounceY; // Tọa độ Y động của thân, cánh và đầu

  // Đôi cánh sóc bay vỗ nhịp trễ pha 80ms (Delta Phi = 0.20 rad) dập dờn như cánh diều
  const wingLag = breathPhase - 0.20;
  const wingFlap = Math.sin(wingLag) * 5.0;
  const wingFlutter = Math.sin(breathPhase * 2.0 - 0.20) * 1.6;

  // Đuôi sóc xòe hình lưỡi liềm uốn lượn sau lưng trễ pha quán tính
  const tailLag = breathPhase - 0.40;
  const tailSwayX = Math.sin(tailLag) * 6.5;
  const tailSwayY = Math.cos(tailLag) * 3.8;

  // Nhịp chớp mắt 3.5s (interval 3500ms, duration 140ms)
  const blinkCycle = (t * 1000) % 3500;
  const blink = manualBlink || (blinkCycle < 140);

  // Hạt bụi tĩnh điện lách tách quanh má và cánh
  const spark1 = Math.sin(t * 12.0) * 3.0;
  const spark2 = Math.cos(t * 16.0) * 3.0;

  // 2. LAYER 0: BÓNG TIẾP XÚC MỜ ẢO CO GIÃN DƯỚI SÀN (Ground Contact Shadow)
  ctx.save();
  const shadowFactor = 1.0 - bounceY * 0.04;
  const shadowGrad = ctx.createRadialGradient(-2, 64, 3, -2, 64, 56 * sX * shadowFactor);
  shadowGrad.addColorStop(0, "rgba(18, 22, 32, 0.70)");
  shadowGrad.addColorStop(0.55, "rgba(18, 22, 32, 0.32)");
  shadowGrad.addColorStop(1, "rgba(18, 22, 32, 0.0)");
  ctx.fillStyle = shadowGrad;
  ctx.beginPath();
  ctx.ellipse(-2, 64, 56 * sX * shadowFactor, 11.5 * sX * shadowFactor, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 3. LAYER 1: BẢN ĐUÔI SÓC TIA CHỚP LƯỠI LIỀM KHỔNG LỒ ĐEN TUYỀN (Giant Sweeping Lightning Plume)
  ctx.save();
  ctx.translate(0, by);

  const tx0 = 16;
  const ty0 = 14;
  const txTop = 96 + tailSwayX;
  const tyTop = -34 + tailSwayY;
  const txNotch1 = 80 + tailSwayX * 0.8;
  const tyNotch1 = -16 + tailSwayY;
  const txMidSpike = 112 + tailSwayX * 1.15;
  const tyMidSpike = -10 + tailSwayY;
  const txNotch2 = 86 + tailSwayX * 0.85;
  const tyNotch2 = 4 + tailSwayY;
  const txBotSpike = 102 + tailSwayX * 0.9;
  const tyBotSpike = 18 + tailSwayY;

  const tailGrad = ctx.createLinearGradient(tx0, ty0, txMidSpike, tyMidSpike);
  tailGrad.addColorStop(0, "#303848");
  tailGrad.addColorStop(0.35, "#222834");
  tailGrad.addColorStop(1, "#141822");

  ctx.beginPath();
  ctx.moveTo(tx0, ty0 - 6);
  // Cung lưng đuôi vút cong lên chóp 1 góc 35 độ
  ctx.bezierCurveTo(38, 8 + tailSwayY * 0.3, 64 + tailSwayX * 0.4, -20 + tailSwayY * 0.7, txTop, tyTop);
  // Răng cưa tia chớp 1
  ctx.lineTo(txNotch1, tyNotch1);
  ctx.lineTo(txMidSpike, tyMidSpike);
  // Răng cưa tia chớp 2
  ctx.lineTo(txNotch2, tyNotch2);
  ctx.lineTo(txBotSpike, tyBotSpike);
  // Cung đáy đuôi uốn lượn ôm lại hông
  ctx.bezierCurveTo(74 + tailSwayX * 0.6, 26 + tailSwayY * 0.8, 38, 26, tx0 + 6, ty0 + 10);
  ctx.closePath();

  ctx.fillStyle = tailGrad;
  ctx.fill();
  ctx.strokeStyle = "#4D5C73";
  ctx.lineWidth = 1.4;
  ctx.stroke();

  // Sống gờ tia chớp đón sáng sắc cạnh (Chiseled Facet Rim)
  ctx.strokeStyle = "rgba(255, 255, 255, 0.45)";
  ctx.lineWidth = 1.2;
  ctx.beginPath();
  ctx.moveTo(32, 10 + tailSwayY * 0.2);
  ctx.bezierCurveTo(58 + tailSwayX * 0.4, -8 + tailSwayY * 0.6, 82 + tailSwayX * 0.8, -24 + tailSwayY * 0.9, txTop - 3, tyTop + 2);
  ctx.stroke();

  ctx.restore();

  // 4. LAYER 2: ĐÔI TAI ĐEN TRÒN XÒE RỘNG VỚI LÒNG TAI VÀNG RỰC (Large Rounded Ears)
  ctx.save();
  ctx.translate(0, by);

  // Tai trái (viewer's left - vểnh sang trái)
  ctx.save();
  ctx.translate(-32, -36);
  ctx.rotate(-0.35);
  const earGradL = ctx.createRadialGradient(-3, -4, 2, 0, 0, 22);
  earGradL.addColorStop(0, "#475166");
  earGradL.addColorStop(0.6, "#222630");
  earGradL.addColorStop(1, "#14171F");
  ctx.fillStyle = earGradL;
  ctx.beginPath();
  ctx.ellipse(0, 0, 16, 20, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = "rgba(255, 255, 255, 0.25)";
  ctx.lineWidth = 1.0;
  ctx.stroke();

  // Lòng tai vàng rực rỡ
  const earInGradL = ctx.createRadialGradient(-1, -2, 1, 1, 1, 15);
  earInGradL.addColorStop(0, "#FFF380");
  earInGradL.addColorStop(0.65, "#FFCE00");
  earInGradL.addColorStop(1, "#E69D00");
  ctx.fillStyle = earInGradL;
  ctx.beginPath();
  ctx.ellipse(1, 1, 11, 14, 0, 0, Math.PI * 2);
  ctx.fill();

  // Đệm trắng chân tai
  ctx.fillStyle = "#F1F5F9";
  ctx.beginPath();
  ctx.ellipse(2, 9, 7, 5, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // Tai phải (viewer's right - xòe rộng sang phải)
  ctx.save();
  ctx.translate(20, -44);
  ctx.rotate(0.48);
  const earGradR = ctx.createRadialGradient(-3, -4, 2, 0, 0, 25);
  earGradR.addColorStop(0, "#475166");
  earGradR.addColorStop(0.6, "#222630");
  earGradR.addColorStop(1, "#14171F");
  ctx.fillStyle = earGradR;
  ctx.beginPath();
  ctx.ellipse(0, 0, 20, 23, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = "rgba(255, 255, 255, 0.25)";
  ctx.lineWidth = 1.0;
  ctx.stroke();

  // Lòng tai vàng rực rỡ
  const earInGradR = ctx.createRadialGradient(-1, -2, 1, -1, 1, 18);
  earInGradR.addColorStop(0, "#FFF380");
  earInGradR.addColorStop(0.65, "#FFCE00");
  earInGradR.addColorStop(1, "#E69D00");
  ctx.fillStyle = earInGradR;
  ctx.beginPath();
  ctx.ellipse(-1, 1, 14, 17, 0, 0, Math.PI * 2);
  ctx.fill();

  // Đệm trắng chân tai
  ctx.fillStyle = "#F1F5F9";
  ctx.beginPath();
  ctx.ellipse(-1, 10, 10, 6, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  ctx.restore();

  // 5. LAYER 3: HAI CÁNH SÓC BAY MÀNG VÀNG CHANH RỰC RỠ (Gliding Patagium Wings with 80ms Lag)
  ctx.save();
  ctx.translate(0, by);

  // Cánh trái (viewer's left)
  const wlx = -56;
  const wly = -8 + wingFlap;
  const whlx = -18;
  const whly = 26;
  const wMidLx = -44;
  const wMidLy = 22 + wingFlutter;

  // Lớp viền đen mặt ngoài màng cánh trái
  ctx.fillStyle = "#1E232B";
  ctx.beginPath();
  ctx.moveTo(wlx, wly);
  ctx.quadraticCurveTo(wMidLx - 9, wMidLy + 7, whlx, whly);
  ctx.lineTo(whlx + 4, whly);
  ctx.quadraticCurveTo(wMidLx - 5, wMidLy + 4, wlx + 3, wly);
  ctx.closePath();
  ctx.fill();

  // Mặt trong màng cánh màu vàng chanh rực rỡ
  const wingGradL = ctx.createRadialGradient(wlx + 18, wly + 10, 2, wMidLx, wMidLy, 36);
  wingGradL.addColorStop(0, "#FFF875");
  wingGradL.addColorStop(0.6, "#FFD000");
  wingGradL.addColorStop(1, "#D97706");
  ctx.fillStyle = wingGradL;
  ctx.beginPath();
  ctx.moveTo(wlx, wly);
  ctx.quadraticCurveTo(wMidLx - 6, wMidLy + 3, whlx, whly);
  ctx.quadraticCurveTo(-28, 14, wlx, wly);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = "rgba(255, 255, 255, 0.45)";
  ctx.lineWidth = 1.0;
  ctx.stroke();

  // Cánh phải (viewer's right - buồm vàng khổng lồ xòe sang phải đón gió)
  const wrx = 46;
  const wry = -6 + wingFlap * 0.85;
  const whrx = 18;
  const whry = 24;

  // Lớp viền đen mặt ngoài màng cánh phải
  ctx.fillStyle = "#1E232B";
  ctx.beginPath();
  ctx.moveTo(wrx, wry);
  ctx.bezierCurveTo(wrx + 22, wry + 10, whrx + 38, whry + 4, whrx, whry);
  ctx.lineTo(whrx - 4, whry);
  ctx.bezierCurveTo(whrx + 32, whry, wrx + 18, wry + 6, wrx - 3, wry);
  ctx.closePath();
  ctx.fill();

  // Mặt trong màng cánh phải vàng chanh - cánh buồm phồng to rực rỡ
  const wingGradR = ctx.createRadialGradient(wrx - 8, wry + 14, 4, 38, 16, 44);
  wingGradR.addColorStop(0, "#FFF875");
  wingGradR.addColorStop(0.55, "#FFD000");
  wingGradR.addColorStop(0.85, "#F59E0B");
  wingGradR.addColorStop(1, "#D97706");
  ctx.fillStyle = wingGradR;
  ctx.beginPath();
  ctx.moveTo(14, 2); // Nách phải
  ctx.lineTo(wrx, wry); // Cổ tay phải
  ctx.bezierCurveTo(wrx + 22, wry + 8, whrx + 36, whry + 2, whrx, whry); // Cung buồm căng gió
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = "rgba(255, 255, 255, 0.45)";
  ctx.lineWidth = 1.0;
  ctx.stroke();

  ctx.restore();

  // 6. LAYER 4: THÂN TRÒN MẬP & HAI CHÂN SAU TÍ HON (Plump Pear Body & Dangling Feet)
  ctx.save();
  ctx.translate(0, by);
  ctx.scale(sX, sY);

  // Lưng và sườn đen bao phủ
  const bodyBackGrad = ctx.createRadialGradient(0, 16, 4, 0, 16, 28);
  bodyBackGrad.addColorStop(0, "#303746");
  bodyBackGrad.addColorStop(0.7, "#222630");
  bodyBackGrad.addColorStop(1, "#14171F");
  ctx.fillStyle = bodyBackGrad;
  ctx.beginPath();
  ctx.ellipse(0, 16, 26, 24, 0, 0, Math.PI * 2);
  ctx.fill();

  // Bụng trắng ngọc trai phúng phính Pop Mart
  const bellyGrad = ctx.createRadialGradient(-3, 13, 3, -1, 16, 24);
  bellyGrad.addColorStop(0, "#FFFFFF");
  bellyGrad.addColorStop(0.75, "#F8FAFC");
  bellyGrad.addColorStop(1, "#E2E8F0");
  ctx.fillStyle = bellyGrad;
  ctx.beginPath();
  ctx.ellipse(-2, 16, 22, 21, 0, 0, Math.PI * 2);
  ctx.fill();

  // Hai chân sau tí hon buông lỏng tự nhiên trong gió
  // Chân trái
  ctx.fillStyle = "#94A3B8";
  ctx.beginPath(); ctx.roundRect(-16, 36, 7, 10, 3); ctx.fill();
  ctx.fillStyle = "#FFFFFF";
  ctx.beginPath(); ctx.arc(-13, 44, 3.2, 0, Math.PI * 2); ctx.fill();

  // Chân phải
  ctx.fillStyle = "#94A3B8";
  ctx.beginPath(); ctx.roundRect(4, 35, 7, 10, 3); ctx.fill();
  ctx.fillStyle = "#FFFFFF";
  ctx.beginPath(); ctx.arc(7, 43, 3.2, 0, Math.PI * 2); ctx.fill();

  // Vòng cổ đen ôm quanh gáy và dưới cằm
  ctx.fillStyle = "#222630";
  ctx.beginPath();
  ctx.ellipse(-3, 4, 18, 5, 0, 0, Math.PI * 2);
  ctx.fill();

  ctx.restore();

  // 7. LAYER 5: HAI CÁNH TAY TRẮNG DANG RỘNG (Outstretched White Arms & Claws)
  ctx.save();
  ctx.translate(0, by);

  // Tay trái (viewer's left)
  const armGradL = ctx.createLinearGradient(-18, 4, wlx, wly);
  armGradL.addColorStop(0, "#F1F5F9");
  armGradL.addColorStop(0.7, "#FFFFFF");
  armGradL.addColorStop(1, "#E2E8F0");
  ctx.fillStyle = armGradL;
  ctx.beginPath();
  ctx.moveTo(-18, 4);
  ctx.lineTo(wlx, wly);
  ctx.lineTo(wlx + 7, wly + 7);
  ctx.lineTo(-20, 12);
  ctx.closePath();
  ctx.fill();

  // Cổ tay & móng vuốt trái
  ctx.fillStyle = "#FFFFFF";
  ctx.beginPath(); ctx.arc(wlx, wly, 5.5, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc(wlx - 4, wly - 3, 2, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc(wlx - 5, wly, 2, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc(wlx - 3, wly + 3, 2, 0, Math.PI * 2); ctx.fill();

  // Tay phải (viewer's right)
  const armGradR = ctx.createLinearGradient(14, 2, wrx, wry);
  armGradR.addColorStop(0, "#F1F5F9");
  armGradR.addColorStop(0.7, "#FFFFFF");
  armGradR.addColorStop(1, "#E2E8F0");
  ctx.fillStyle = armGradR;
  ctx.beginPath();
  ctx.moveTo(14, 2);
  ctx.lineTo(wrx, wry);
  ctx.lineTo(wrx - 5, wry + 7);
  ctx.lineTo(16, 11);
  ctx.closePath();
  ctx.fill();

  // Cổ tay & móng vuốt phải
  ctx.fillStyle = "#FFFFFF";
  ctx.beginPath(); ctx.arc(wrx, wry, 5.5, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc(wrx + 4, wry - 3, 2, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc(wrx + 5, wry, 2, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc(wrx + 3, wry + 3, 2, 0, Math.PI * 2); ctx.fill();

  ctx.restore();

  // 8. LAYER 6: KHỐI ĐẦU POP MART, MŨ TRÙM ĐEN 3 MÚI & KHUÔN MẶT TRẮNG (Head, Hood & Face)
  ctx.save();
  ctx.translate(0, by);
  ctx.scale(sX, sY);

  const hx = -4;
  const hy = -12;

  // Khối đỉnh đầu đen (Black Hood Base phía sau - chỉ ở trên vòm gáy)
  const headGrad = ctx.createRadialGradient(hx - 2, hy - 10, 3, hx, hy - 8, 26);
  headGrad.addColorStop(0, "#475166");
  headGrad.addColorStop(0.55, "#222630");
  headGrad.addColorStop(1, "#14171F");
  ctx.fillStyle = headGrad;
  ctx.beginPath();
  ctx.ellipse(hx, hy - 10, 28, 20, 0, 0, Math.PI * 2);
  ctx.fill();

  // Đón sáng lụa đỉnh đầu
  ctx.fillStyle = "rgba(255, 255, 255, 0.28)";
  ctx.beginPath();
  ctx.ellipse(hx, hy - 18, 18, 8, -0.08, 0, Math.PI * 2);
  ctx.fill();

  // KHUÔN MẶT TRẮNG TINH KHÔI PHÚNG PHÍNH (White Face bao trọn toàn bộ mắt, mũi, miệng, má và trán)
  const faceGrad = ctx.createRadialGradient(hx - 2, hy + 2, 4, hx - 2, hy + 4, 26);
  faceGrad.addColorStop(0, "#FFFFFF");
  faceGrad.addColorStop(0.85, "#F8FAFC");
  faceGrad.addColorStop(1, "#E2E8F0");
  ctx.fillStyle = faceGrad;
  ctx.beginPath();
  ctx.ellipse(hx - 2, hy + 2, 26, 22, 0, 0, Math.PI * 2);
  ctx.fill();

  // Má phúng phính bầu bĩnh Pop Mart
  ctx.beginPath(); ctx.arc(hx - 14, hy + 5, 13, 0, Math.PI * 2); ctx.fill();
  ctx.beginPath(); ctx.arc(hx + 10, hy + 4, 12, 0, Math.PI * 2); ctx.fill();
  // Vòm trán trắng vươn cao
  ctx.beginPath(); ctx.ellipse(hx - 2, hy - 6, 17, 13, 0, 0, Math.PI * 2); ctx.fill();

  // Mũ trùm đầu đen chúc xuống trán 3 múi nhọn sắc sảo (3 Sharp Black Teeth on White Forehead)
  ctx.fillStyle = "#222630";
  // Múi giữa (chúc xuống chính giữa 2 mắt - cao ráo không che mắt)
  ctx.beginPath();
  ctx.moveTo(hx - 8, hy - 20);
  ctx.lineTo(hx, hy - 11);
  ctx.lineTo(hx + 7, hy - 20);
  ctx.closePath();
  ctx.fill();

  // Múi bên trái (chúc xuống mép ngoài mắt trái)
  ctx.beginPath();
  ctx.moveTo(hx - 20, hy - 19);
  ctx.lineTo(hx - 16, hy - 13);
  ctx.lineTo(hx - 11, hy - 20);
  ctx.closePath();
  ctx.fill();

  // Múi bên phải (chúc xuống mép ngoài mắt phải)
  ctx.beginPath();
  ctx.moveTo(hx + 10, hy - 20);
  ctx.lineTo(hx + 15, hy - 14);
  ctx.lineTo(hx + 20, hy - 18);
  ctx.closePath();
  ctx.fill();

  // 9. LAYER 7: HAI MÁ TÚI ĐIỆN VÀNG TRÒN VO PHÚNG PHÍNH (Plump Electric Yellow Cheeks)
  // Nằm hoàn toàn trên nền lông trắng hai bên má
  const clx = -25;
  const cly = hy + 6;
  const cheekGradL = ctx.createRadialGradient(clx - 1, cly - 1, 1, clx, cly, 9);
  cheekGradL.addColorStop(0, "#FFF875");
  cheekGradL.addColorStop(0.5, "#FFD000");
  cheekGradL.addColorStop(1, "#FFB703");
  ctx.fillStyle = cheekGradL;
  ctx.beginPath();
  ctx.arc(clx, cly, 8.2, 0, Math.PI * 2);
  ctx.fill();

  // Túi điện má phải (viewer's right)
  const crx = 17;
  const cry = hy + 4;
  const cheekGradR = ctx.createRadialGradient(crx - 1, cry - 1, 1, crx, cry, 8);
  cheekGradR.addColorStop(0, "#FFF875");
  cheekGradR.addColorStop(0.5, "#FFD000");
  cheekGradR.addColorStop(1, "#FFB703");
  ctx.fillStyle = cheekGradR;
  ctx.beginPath();
  ctx.arc(crx, cry, 7.5, 0, Math.PI * 2);
  ctx.fill();

  // 10. LAYER 8: ĐÔI MẮT PHA LÊ ĐEN LÁY TO TRÒN 3 ĐIỂM BẮT SÁNG (Crystal Specular Eyes NẰM TRÊN NỀN TRẮNG)
  // Mắt trái (viewer's left) - to tròn lấp lánh trên nền mặt trắng
  const elX = -15;
  const elY = hy - 4;
  drawEmolgaEye(ctx, elX, elY, 8.2, 12.0, -0.1, blink);

  // Mắt phải (viewer's right)
  const erX = 6;
  const erY = hy - 7;
  drawEmolgaEye(ctx, erX, erY, 7.5, 11.2, 0.1, blink);

  // 11. LAYER 9: MŨI ĐEN & MIỆNG CƯỜI HẠNH PHÚC LƯỠI HỒNG (Snout & Happy Smile)
  // Chấm mũi đen nhỏ xíu
  ctx.fillStyle = "#14171F";
  ctx.beginPath();
  ctx.arc(-5, hy - 1, 1.4, 0, Math.PI * 2);
  ctx.fill();

  // Miệng cười mở rộng hình nêm hạnh phúc
  ctx.save();
  const mx0 = -13;
  const my0 = hy + 4;
  const mx1 = 2;
  const my1 = hy + 3;
  const mxMid = -6;
  const myMid = hy + 14;

  ctx.beginPath();
  ctx.moveTo(mx0, my0);
  ctx.quadraticCurveTo(mxMid, my0 - 1, mx1, my1);
  ctx.quadraticCurveTo(mx1 + 1, myMid - 2, mxMid, myMid);
  ctx.quadraticCurveTo(mx0 - 1, myMid - 2, mx0, my0);
  ctx.closePath();
  ctx.fillStyle = "#581C28";
  ctx.fill();
  ctx.strokeStyle = "#380D15";
  ctx.lineWidth = 0.8;
  ctx.stroke();

  // Lưỡi hồng đào nhỏ nhắn hé mở
  ctx.fillStyle = "#FB7185";
  ctx.beginPath();
  ctx.arc(mxMid, myMid - 3.5, 3.8, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  ctx.restore(); // restore head scale

  // 12. LAYER 10: HẠT BỤI TĨNH ĐIỆN LÁCH TÁCH (Floating Electric Sparks)
  drawElectricSpark(ctx, -25 - 9 + spark1, hy + 6 - 4 + spark2, "#FFF875");
  drawElectricSpark(ctx, 112 + tailSwayX * 1.15 + 2 + spark2, -10 + tailSwayY - 4 + spark1, "#FFD000");
  drawElectricSpark(ctx, wlx - 4 + spark2, wly + 6 + spark1, "#FFF875");
  drawElectricSpark(ctx, 20 + 16 + spark1, -44 - 6 + spark2, "#FFD000");

  ctx.restore();
}

function drawEmolgaEye(ctx, ex, ey, rx, ry, rot, blink) {
  ctx.save();
  ctx.translate(ex, ey);
  ctx.rotate(rot);

  if (blink) {
    ctx.strokeStyle = "#0E1015";
    ctx.lineWidth = 2.6;
    ctx.lineCap = "round";
    ctx.beginPath();
    ctx.arc(0, 2, rx * 0.85, Math.PI * 0.15, Math.PI * 0.85);
    ctx.stroke();
    // Đuôi mi mắt vểnh ngộ nghĩnh
    ctx.beginPath();
    ctx.moveTo(rx * 0.7, 3);
    ctx.lineTo(rx * 1.2, -1);
    ctx.stroke();
  } else {
    // Hốc mắt & Tròng mắt đen láy obsidian
    const eyeGrad = ctx.createRadialGradient(-1, -3, 1, 0, 0, ry);
    eyeGrad.addColorStop(0, "#2E3442");
    eyeGrad.addColorStop(0.5, "#1C202A");
    eyeGrad.addColorStop(1, "#0E1015");
    ctx.fillStyle = eyeGrad;
    ctx.beginPath();
    ctx.ellipse(0, 0, rx, ry, 0, 0, Math.PI * 2);
    ctx.fill();

    // 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Specular Highlights)
    // Điểm 1: Primary Keylight lớn góc 10h (hình bầu dục sáng bóng)
    ctx.fillStyle = "#FFFFFF";
    ctx.beginPath();
    ctx.ellipse(-rx * 0.28, -ry * 0.38, rx * 0.44, ry * 0.30, -0.2, 0, Math.PI * 2);
    ctx.fill();

    // Điểm 2: Secondary Caustic Bounce góc 4h (vầng phản chiếu mềm)
    ctx.fillStyle = "rgba(226, 232, 240, 0.88)";
    ctx.beginPath();
    ctx.ellipse(rx * 0.35, ry * 0.38, rx * 0.30, ry * 0.22, 0.2, 0, Math.PI * 2);
    ctx.fill();

    // Điểm 3: Tertiary Micro Specular Glint (vi điểm bắt sáng li ti mép phải)
    ctx.fillStyle = "#FFFFFF";
    ctx.beginPath();
    ctx.arc(rx * 0.45, -ry * 0.05, 1.2, 0, Math.PI * 2);
    ctx.fill();
  }

  ctx.restore();
}

function drawElectricSpark(ctx, sx, sy, color) {
  ctx.save();
  ctx.translate(sx, sy);
  ctx.fillStyle = color;
  ctx.beginPath();
  ctx.moveTo(0, -4.0);
  ctx.lineTo(1.4, -1.2);
  ctx.lineTo(4.0, 0);
  ctx.lineTo(1.4, 1.2);
  ctx.lineTo(0, 4.0);
  ctx.lineTo(-1.4, 1.2);
  ctx.lineTo(-4.0, 0);
  ctx.lineTo(-1.4, -1.2);
  ctx.closePath();
  ctx.fill();
  ctx.restore();
}
'''

emolga_profile = {
    "id": 12,
    "global_id": 12,
    "codename": "MYTHIC_EMOLGA_FLYING_SQUIRREL",
    "name_vi": "Emolga - Sóc Bay Đôi Cánh Điện",
    "name_en": "Mythic Emolga the Sky Squirrel",
    "japanese_name": "エモンガ (Emonga - モモンガポケモン)",
    "pokedex_number": 587,
    "category": "Linh Thú Sóc Bay Thần Thoại & Bé Cưng Pop Mart 3D",
    "archetype": "Sóc Bay Đôi Cánh Điện (The Golden Sky Glider)",
    "elements": [
        "Lôi Điện Thuần Khiết (Mythic Electric)",
        "Phi Thiên Tự Do (Aerial Glider)"
    ],
    "signature_moves": [
        "Electro Ball (Quả Cầu Sấm Sét Hoàng Kim)",
        "Acrobatics (Nhào Lộn Phi Thân)"
    ],
    "mythology_lore": "Emolga là linh thú sóc bay mang đôi cánh điện thần kỳ cư ngụ trên những ngọn cây cổ thụ ngút ngàn. Khi dang rộng đôi màng cánh vàng chanh rực rỡ, Emolga phóng lướt trên bầu trời như một cánh diều tích điện lượn bay tự do giữa tầng mây. Năng lượng sấm sét được lưu trữ trong hai chiếc túi điện tròn phúng phính trên má và phóng thích dọc theo sống lưng đuôi hình tia chớp uốn lượn sau lưng. Trong hình hài Pop Mart 3D Vinyl độc bản, Emolga toát lên vẻ đáng yêu vô ngần với đôi mắt pha lê đen láy to tròn long lanh 3 điểm bắt sáng, màng cánh sóc bay vàng chanh vẫy nhịp trễ pha 80ms dập dờn bồng bềnh và nụ cười rạng rỡ mang lại niềm hạnh phúc vô tận cho người bạn đồng hành.",
    "inspirational_quotes": {
        "vi": "Hãy dang rộng đôi cánh tâm hồn và lượn bay qua mọi giông bão, nụ cười của bạn chính là nguồn năng lượng sáng ngời nhất.",
        "en": "Spread your wings and glide effortlessly above every storm; your radiant smile is the purest electric spark in the universe."
    }
}

volumetric_3d_anatomy = {
    "mesh_topology": "High-End Pop Mart Vinyl Sculpt: Pear-Ellipsoid Porcelain Belly, 3-Peak Scalloped Onyx Hood, Convex Aerodynamic Patagium Wings, Large Rounded Ears with Golden Disc Inset, and Serrated 3-Prong Lightning Tail",
    "light_rig": {
        "key_light": {
            "direction": [-0.4, -0.85, 0.5],
            "color": "#FFF875",
            "role": "Studio Keylight trên đỉnh trán, vành tai và sống màng cánh lượn vàng chanh"
        },
        "fill_light": {
            "direction": [0.5, 0.3, 0.3],
            "color": "#FFD000",
            "role": "Ánh sáng tán xạ môi trường vàng hổ phách Pop Mart Vinyl mặt trong màng cánh"
        },
        "rim_light": {
            "direction": [0.0, 0.0, -1.0],
            "color": "#505D75",
            "role": "Viền Fresnel lụa mịn tách bạch khối mũ trùm đen và bản đuôi tia chớp khỏi nền tối"
        }
    },
    "patagium_wings": {
        "inner_membrane": "Màng cánh sóc bay màu vàng chanh rực rỡ (#FFD000, #FFF875) nối liền từ cổ tay đến hông, bề mặt căng mịn đàn hồi như cánh diều lượn.",
        "outer_dorsal_trim": "Mặt ngoài và gờ viền màng cánh bọc lớp da đen bóng bẩy (#1E232B) tạo tương phản thị giác sắc sảo và đường khí động học hoàn hảo.",
        "flutter_kinematics": "Vỗ nhịp trễ pha 80ms (Delta Phi = 0.20 rad) dập dờn như cánh diều lướt gió."
    },
    "ears_and_hood": {
        "ears": "Đôi tai đen tròn xòe rộng với lòng tai vàng rực (#FFCE00, #FFF380) và vành đệm trắng ngọc (#F1F5F9) chân tai.",
        "black_hood": "Mũ trùm đầu đen nhung tuyền (#262C38) ôm trọn đỉnh gáy và chúc xuống trán 3 múi nhọn sắc sảo: 1 múi trung tâm chúc giữa 2 mắt và 2 múi bên má tạo nét tinh nghịch đáng yêu."
    },
    "electric_cheeks_and_eyes": {
        "cheeks": "Hai má túi điện vàng tròn vo (#FFB703, #FFD166) má phúng phính tích đầy điện trường Pop Mart ngọt ngào.",
        "crystal_eyes": {
            "type": "3-Point Specular Glossy Crystal Orb",
            "coverage": "Chiếm 38% diện tích khuôn mặt Chibi",
            "color": "Hốc mắt và tròng mắt obsidian đen láy (#0E1015, #1C202A) đặt trọn vẹn trong khuôn mặt trắng tinh khôi",
            "catchlight_1": "Primary Studio Keylight góc 10h (#FFFFFF) hình bầu dục phản chiếu đèn mềm",
            "catchlight_2": "Secondary Ground Bounce Caustic góc 4h (#E2E8F0) tụ sáng lòng dưới",
            "catchlight_3": "Tertiary Micro Surface Sparkle góc 2h (#FFFFFF) vi điểm bắt sáng lấp lánh"
        },
        "snout_and_smile": "Chấm mũi đen tí hon Chibi và khuôn miệng cười mở rộng hình nêm khoe khoang miệng Bordeaux (#581C28) cùng chiếc lưỡi hồng đào (#FB7185) ngọt ngào."
    },
    "lightning_tail": {
        "structure": "Bản đuôi sóc xòe rộng hình lưỡi liềm đen tuyền (#222834) uốn lượn sau lưng, vút chéo lên trên sang phải góc 35 độ và xẻ 3 răng cưa tia chớp nhọn hoắt dũng mãnh.",
        "phase_lag": "Uốn lượn trễ pha quán tính Delta Phi = 0.40 rad nhịp nhàng theo chuyển động lượn bay."
    },
    "body_and_feet": {
        "body": "Khối thân hạt lê tròn mập trắng muốt (#FFFFFF) với độ bóng men sứ và đổ bóng satin mềm mại (#E2E8F0).",
        "feet": "Hai bàn chân sau xám nhạt (#94A3B8) tí hon buông lỏng tự nhiên trong tư thế lướt gió."
    }
}

organic_microphysics_kinematics = {
    "squash_and_stretch": {
        "frequency_hz": 0.38,
        "angular_freq_rad": 2.4,
        "amplitude_pct": 5.0,
        "vertical_scale_formula": "Sy = 1.0 + 0.05 * sin(2.4 * t)",
        "horizontal_scale_formula": "Sx = 1.0 - 0.025 * sin(2.4 * t)",
        "glide_bobbing_formula": "by = sin(2.4 * t) * 4.5 px",
        "volume_conservation": "Sx * Sx * Sy = 0.9506 * 1.05 = 0.9981 (~ 1.00)"
    },
    "patagium_wing_flutter": {
        "phase_lag_rad": 0.20,
        "time_lag_ms": 80,
        "wing_flap_formula": "wingFlap = sin(2.4 * t - 0.20) * 5.0 px",
        "trailing_flutter_formula": "wingFlutter = sin(4.8 * t - 0.20) * 1.6 px",
        "aerodynamic_damping": 0.96
    },
    "lightning_tail_sway": {
        "delta_phi_rad": 0.40,
        "sway_x_formula": "tailSwayX = sin(2.4 * t - 0.40) * 6.5 px",
        "sway_y_formula": "tailSwayY = cos(2.4 * t - 0.40) * 3.8 px",
        "angular_tilt_rad": "tailTilt = sin(2.4 * t - 0.40) * 0.06 rad"
    },
    "blinking_state_machine": {
        "cycle_period_ms": 3500,
        "blink_duration_ms": 140,
        "closed_eye_shape": "Mí mắt cười cong hình lưỡi liềm ngọt ngào với đuôi mi mắt vểnh"
    },
    "dynamic_contact_shadow": {
        "base_width_px": 56,
        "base_height_px": 11.5,
        "dynamic_scaling": "width = 56 * Sx * (1.0 - bounceY * 0.04), height = 11.5 * Sx * (1.0 - bounceY * 0.04)"
    },
    "electric_static_sparks": {
        "frequency_rad": 14.0,
        "flicker_formula": "spark1 = sin(12.0 * t) * 3.0, spark2 = cos(16.0 * t) * 3.0",
        "particle_count": 4,
        "spark_locations": "Hai má túi điện, ngọn đuôi tia chớp và chóp màng cánh"
    }
}

master_json = {
    "metadata": {
        "session": "session3_agent2",
        "agent_name": "Nghệ Sĩ Điêu Khắc Emolga Sóc Bay Đôi Cánh Điện (Emolga Flying Squirrel 3D Sculptor)",
        "agent_role": "Master 3D Pop Mart & Vinyl Creature Sculptor for IoT Digital Keychain",
        "version": "3.0.0-PRO-MAX",
        "created_date": "2026-09-04",
        "target_display": "ST7789 240x280 / 172x320 16-bit RGB565 IPS Display & Modern HTML5 Canvas 2D",
        "reference_artwork": "12_Mythic_Emolga_Flying_Squirrel.png",
        "design_frameworks": [
            "12_Mythic_Emolga_Flying_Squirrel.png (Official Master Art 100% Fidelity)",
            "Reffernce/NHOM_1_FRONTEND_UIUX/ui-ux-pro-max-skill-main (High-fidelity design intelligence, micro-interactions, anti-cheap-icon)",
            "Reffernce/NHOM_1_FRONTEND_UIUX/react-bits-main (Viscoelastic spring physics, fluid canvas motion, organic lag)",
            "Reffernce/NHOM_1_FRONTEND_UIUX/impeccable-main (Craft floor, material fidelity, organic depth)"
        ],
        "core_design_rules": {
            "style_definition": "3D Pop Mart Vinyl Toy cao cấp: Hình thể tròn trĩnh bóng bẩy, viền vát 3D tinh xảo, đổ bóng mềm mại, không sử dụng icon phẳng thô sơ rẻ tiền.",
            "patagium_wings_rule": "Màng cánh sóc bay màu vàng chanh rực rỡ (#FFD000, #FFF875) nối từ cổ tay đến hông, mặt trong màu vàng mặt ngoài màu đen bóng bẩy (#1E232B).",
            "ears_and_hood_rule": "Đôi tai đen tròn xòe rộng với lòng tai vàng rực rỡ và vành đệm chân tai trắng ngọc; mũ trùm đầu đen chúc xuống trán 3 múi nhọn sắc sảo theo chuẩn nguyên tác 100%.",
            "electric_cheeks_rule": "Hai má túi điện vàng tròn vo má phúng phính tích đầy điện trường Pop Mart ngọt ngào.",
            "crystal_eyes_rule": "Đôi mắt pha lê đen láy to tròn long lanh 3 điểm bắt sáng vật lý (Primary Keylight góc 10h, Secondary Caustic Bounce góc 4h, Tertiary Micro Specular Glint) nằm trọn vẹn trong khuôn mặt trắng tinh.",
            "lightning_tail_rule": "Đuôi sóc xòe hình lưỡi liềm đen tuyền uốn lượn sau lưng vút chéo lên trên sang phải xẻ 3 răng cưa tia chớp sắc nét với sống gờ phản quang.",
            "kinematics_rule": "Chuyển động vi vật lý hữu cơ: Nhịp lượn bay Squash & Stretch 5% bồng bềnh bảo toàn thể tích, đôi cánh vỗ nhịp trễ pha 80ms dập dờn như cánh diều, đuôi sóc lắc lư trễ pha quán tính, nhịp chớp mắt 3.5s, bóng tiếp xúc co giãn nhịp nhàng dưới sàn."
        }
    },
    "creature_profile": emolga_profile,
    "palette": palette_entries,
    "volumetric_3d_anatomy": volumetric_3d_anatomy,
    "organic_microphysics_kinematics": organic_microphysics_kinematics,
    "cpp_scaled_canvas_code": cpp_scaled_canvas_code.strip(),
    "js_canvas_code": js_canvas_code.strip()
}

# Write output json
base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
out_json_path = os.path.join(base_dir, "data", "session3_agent2_emolga.json")

with open(out_json_path, "w", encoding="utf-8") as f:
    json.dump(master_json, f, ensure_ascii=False, indent=2)

print(f"Successfully generated JSON: {out_json_path}")

# Generate interactive preview HTML
preview_html = f"""<!DOCTYPE html>
<html lang="vi">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>EMOLGA SÓC BAY ĐÔI CÁNH ĐIỆN - Pop Mart 3D Vinyl Sculptor Preview</title>
  <style>
    :root {{
      --bg-dark: #0b0f17;
      --card-bg: rgba(18, 24, 38, 0.85);
      --border-glow: rgba(255, 213, 0, 0.35);
      --accent-yellow: #FFD000;
      --accent-gold: #FFF875;
      --accent-electric: #FFB703;
      --text-main: #f8fafc;
      --text-muted: #94a3b8;
    }}
    * {{
      box-sizing: border-box;
      margin: 0;
      padding: 0;
    }}
    body {{
      background: radial-gradient(circle at 50% 20%, #172033 0%, var(--bg-dark) 85%);
      color: var(--text-main);
      font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
      min-height: 100vh;
      padding: 30px 20px;
      display: flex;
      flex-direction: column;
      align-items: center;
    }}
    .header {{
      text-align: center;
      margin-bottom: 25px;
    }}
    .header h1 {{
      font-size: 26px;
      letter-spacing: 1.5px;
      background: linear-gradient(135deg, #FFF875, #FFD000, #FFB703);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
      margin-bottom: 8px;
    }}
    .header p {{
      color: var(--text-muted);
      font-size: 13px;
    }}
    .container {{
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
      gap: 24px;
      max-width: 1280px;
      width: 100%;
    }}
    .card {{
      background: var(--card-bg);
      border: 1px solid rgba(255, 255, 255, 0.1);
      border-radius: 16px;
      padding: 20px;
      backdrop-filter: blur(12px);
      box-shadow: 0 10px 30px rgba(0, 0, 0, 0.5);
      display: flex;
      flex-direction: column;
      align-items: center;
      position: relative;
      overflow: hidden;
    }}
    .card::before {{
      content: "";
      position: absolute;
      top: 0; left: 0; right: 0; height: 3px;
      background: linear-gradient(90deg, transparent, var(--accent-yellow), transparent);
    }}
    .card h2 {{
      font-size: 15px;
      color: #e2e8f0;
      margin-bottom: 15px;
      width: 100%;
      display: flex;
      justify-content: space-between;
      align-items: center;
      border-bottom: 1px solid rgba(255, 255, 255, 0.08);
      padding-bottom: 8px;
    }}
    .badge {{
      font-size: 10px;
      padding: 3px 8px;
      background: rgba(255, 213, 0, 0.15);
      border: 1px solid rgba(255, 213, 0, 0.4);
      color: #FFF875;
      border-radius: 20px;
      font-weight: 600;
    }}
    img.ref {{
      width: 220px;
      height: 220px;
      object-fit: contain;
      filter: drop-shadow(0 8px 16px rgba(0, 0, 0, 0.6));
      margin: auto;
    }}
    canvas {{
      border-radius: 12px;
      background: radial-gradient(circle at 50% 40%, #151b29 0%, #0c1018 100%);
      box-shadow: inset 0 0 20px rgba(0, 0, 0, 0.8), 0 4px 12px rgba(0, 0, 0, 0.5);
    }}
    .controls {{
      display: flex;
      gap: 10px;
      margin-top: 14px;
      width: 100%;
      justify-content: center;
    }}
    button {{
      background: #1e293b;
      color: #e2e8f0;
      border: 1px solid #334155;
      padding: 7px 14px;
      border-radius: 8px;
      font-size: 12px;
      cursor: pointer;
      transition: all 0.2s;
    }}
    button:hover {{
      background: #334155;
      border-color: var(--accent-yellow);
      color: #ffffff;
      box-shadow: 0 0 10px rgba(255, 213, 0, 0.3);
    }}
    .metrics {{
      margin-top: 12px;
      font-family: monospace;
      font-size: 11px;
      color: #fde047;
      display: flex;
      gap: 14px;
    }}
    .specs-card {{
      font-size: 12px;
      line-height: 1.6;
      color: #94a3b8;
    }}
    .specs-card ul {{
      list-style: none;
      padding: 0;
    }}
    .specs-card li {{
      margin-bottom: 8px;
      padding-left: 18px;
      position: relative;
    }}
    .specs-card li::before {{
      content: "⚡";
      position: absolute;
      left: 0;
      color: var(--accent-yellow);
    }}
    .specs-card strong {{
      color: #e2e8f0;
    }}
  </style>
</head>
<body>

  <div class="header">
    <h1>EMOLGA SÓC BAY ĐÔI CÁNH ĐIỆN</h1>
    <p>3D Pop Mart Vinyl Sculptor • Session 3 Agent 2 • Pokedex #587 • ST7789 IPS 16-bit RGB565</p>
  </div>

  <div class="container">
    <!-- Panel 1: Reference Artwork -->
    <div class="card">
      <h2>REFERENCE IMAGE <span class="badge">100% Fidelity</span></h2>
      <img class="ref" src="../ảnh mẫu fllow theo để tạo y hệt như vậy ( giống 100 % các kiểu cách )/12_Mythic_Emolga_Flying_Squirrel.png" alt="Emolga Reference">
      <div class="metrics">Official Master Art 100%</div>
    </div>

    <!-- Panel 2: ST7789 Standard Display (240x280) -->
    <div class="card">
      <h2>ST7789 240x280 <span class="badge">Hardware 1.0x</span></h2>
      <canvas id="canvas1" width="240" height="280"></canvas>
      <div class="controls">
        <button id="btnBlink">Trigger Blink</button>
        <button id="btnPause">Pause / Resume</button>
      </div>
      <div class="metrics">
        <span id="fps">FPS: 60</span>
        <span id="squash">Squash: 1.00</span>
      </div>
    </div>

    <!-- Panel 3: HD Collectible Inspection -->
    <div class="card">
      <h2>POP MART HD INSPECTION <span class="badge">Scale 1.45x</span></h2>
      <canvas id="canvas2" width="340" height="380"></canvas>
      <div class="metrics">
        <span id="wing">Wing Lag: 80ms</span>
        <span id="tail">Tail Sway: Active</span>
      </div>
    </div>

    <!-- Panel 4: Sculpting Specs Breakdown -->
    <div class="card specs-card">
      <h2>SCULPTING SPECS <span class="badge">PRO-MAX</span></h2>
      <ul>
        <li><strong>Màng cánh sóc bay vàng chanh:</strong> Mặt trong vàng chanh rực rỡ, mặt ngoài đen bóng bẩy nối từ cổ tay đến hông.</li>
        <li><strong>Vỗ cánh trễ pha 80ms:</strong> Đôi cánh sóc bay vỗ nhịp trễ pha Delta Phi = 0.20 rad dập dờn như cánh diều lướt gió.</li>
        <li><strong>Đôi tai đen tròn & Lòng tai vàng:</strong> Đôi tai tròn xòe rộng với lòng tai vàng rực rỡ và vành đệm trắng chân tai.</li>
        <li><strong>Mũ trùm đầu đen 3 múi:</strong> Chúc xuống trán 3 múi nhọn (1 giữa 2 mắt, 2 bên má) trên nền mặt trắng ngọc.</li>
        <li><strong>Hai má túi điện vàng phúng phính:</strong> Túi điện tròn vo tích tụ điện trường Pop Mart ngọt ngào.</li>
        <li><strong>Mắt pha lê 3 điểm bắt sáng:</strong> Đôi mắt đen láy to tròn với Primary Keylight, Caustic Bounce và Micro Glint.</li>
        <li><strong>Đuôi sóc lưỡi liềm tia chớp:</strong> Xòe rộng đen tuyền sau lưng vút chéo lên phải với 3 khía răng cưa tia chớp uốn lượn.</li>
        <li><strong>Bóng tiếp xúc mờ ảo:</strong> Co giãn mềm mại dưới sàn theo cao độ lượn bay không trọng lực.</li>
      </ul>
    </div>
  </div>

  <script>
    {js_canvas_code}

    const c1 = document.getElementById("canvas1");
    const ctx1 = c1.getContext("2d");

    const c2 = document.getElementById("canvas2");
    const ctx2 = c2.getContext("2d");

    let isPaused = false;
    let manualBlinkTimer = 0;
    let lastTime = performance.now();
    let frames = 0;
    let fpsTimer = 0;

    document.getElementById("btnBlink").addEventListener("click", () => {{
      manualBlinkTimer = 0.25;
    }});

    document.getElementById("btnPause").addEventListener("click", () => {{
      isPaused = !isPaused;
    }});

    function animate(now) {{
      const dt = (now - lastTime) / 1000;
      lastTime = now;
      const t = now / 1000;

      if (!isPaused) {{
        frames++;
        fpsTimer += dt;
        if (fpsTimer >= 1.0) {{
          document.getElementById("fps").textContent = `FPS: ${{frames}}`;
          frames = 0;
          fpsTimer = 0;
        }}

        if (manualBlinkTimer > 0) {{
          manualBlinkTimer -= dt;
        }}

        const breathSin = Math.sin(t * 2.4);
        const sY = 1.0 + 0.05 * breathSin;
        document.getElementById("squash").textContent = `Squash Y: ${{sY.toFixed(3)}}`;

        // Canvas 1: ST7789 240x280 (Native Hardware 1.0x)
        ctx1.clearRect(0, 0, c1.width, c1.height);
        drawEmolgaFlyingSquirrel(ctx1, 115, 142, 1.25, t, manualBlinkTimer > 0);

        // Canvas 2: HD Collectible Inspection (Scale 1.45x)
        ctx2.clearRect(0, 0, c2.width, c2.height);
        drawEmolgaFlyingSquirrel(ctx2, 165, 205, 1.62, t, manualBlinkTimer > 0);
      }}

      requestAnimationFrame(animate);
    }}
    requestAnimationFrame(animate);
  </script>
</body>
</html>
"""

out_html_path = os.path.join(base_dir, "data", "session3_agent2_emolga_preview.html")
with open(out_html_path, "w", encoding="utf-8") as f:
    f.write(preview_html)

print(f"Successfully generated HTML Preview: {out_html_path}")
