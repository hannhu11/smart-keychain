# -*- coding: utf-8 -*-
"""
Builder Script for Cosmog Nebula Baby (Session 2, Agent 4)
Produces:
  1. data/session2_agent4_cosmog.json
  2. data/session2_agent4_cosmog_preview.html
  3. test/preview_cosmog.html
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
        "optical_function": optical_fn,
        "material_finish": material_finish
    }

cosmog_palette = [
    create_color_entry("col_nebula_core_indigo",  "#1A103C", "Lõi tinh vân chàm tím đậm sâu thẳm vũ trụ", "Translucent Cosmic SSS"),
    create_color_entry("col_nebula_dark_purple",  "#2E124D", "Khối mây tím đậm chuyển tiếp trung tâm", "Velvety Frosted Vinyl"),
    create_color_entry("col_nebula_violet",       "#4A148C", "Sắc tím tử la tinh vân vòm trên", "Gloss Nebula Resin"),
    create_color_entry("col_nebula_magenta",      "#7B1FA2", "Sắc tím hồng phát quang thùy mây dưới", "Luminescent Vinyl"),
    create_color_entry("col_nebula_pink_glow",    "#D81B60", "Hồng cánh sen rực rỡ đáy tinh vân", "Neon Gas Luminescence"),
    create_color_entry("col_nebula_bright_pink",  "#E91E63", "Chóp viền hồng magenta đón sáng cực đại", "Bioluminescent Edge"),
    create_color_entry("col_nebula_deep_blue",    "#0D47A1", "Lam thẫm cuống mây vươn lên đỉnh", "Deep Space SSS"),
    create_color_entry("col_nebula_sky_blue",     "#0288D1", "Sắc lam thanh khiết đệm hai búi mây", "Soft Cyan Sheen"),
    create_color_entry("col_nebula_electric_cyan","#00E5FF", "Xanh lơ cyan điện tử hai búi mây đỉnh", "Electric Gas Glow"),
    create_color_entry("col_nebula_cyan_glow",    "#80D8FF", "Vầng hào quang phát quang búi mây và má", "Astral Fog Diffusion"),
    create_color_entry("col_nebula_pale_cyan",    "#E0F7FA", "Đỉnh đón sáng trắng lam búi mây", "Specular Starlight"),
    create_color_entry("col_gold_fresnel",        "#FFFDE7", "Viền lóa sáng Fresnel đĩa vàng khuyết", "Mirror Gold Specular"),
    create_color_entry("col_gold_highlight",      "#FFF59D", "Mặt diện đón sáng vàng hoàng kim", "Polished Gilded Brass"),
    create_color_entry("col_gold_light",          "#FFF176", "Vàng chanh thanh tao thân vòng đai", "High-Gloss Gold Resin"),
    create_color_entry("col_gold_main",           "#FFEE58", "Sắc vàng hoàng kim nguyên bản vương giả", "Satin Gold Lacquer"),
    create_color_entry("col_gold_warm",           "#FDD835", "Vàng hổ phách tạo khối 3D đĩa khuyết", "Warm Gold Volume"),
    create_color_entry("col_gold_shadow",         "#F57F17", "Bóng đổ nâu vàng sườn đĩa khuyết", "Deep Gold Occlusion"),
    create_color_entry("col_gold_rim_dark",       "#9E9D24", "Đường viền sắc sảo của đĩa khuyết hoàng kim", "Carved Gold Edge"),
    create_color_entry("col_face_black",          "#14171A", "Mặt nạ đám mây đen tuyền trung tâm", "Matte Obsidian Velvet"),
    create_color_entry("col_face_charcoal",       "#1E2328", "Khối chuyển sắc than chì mặt nạ", "Soft Charcoal Shading"),
    create_color_entry("col_face_rim_sheen",      "#334155", "Viền phản xạ lụa mỏng quanh mặt nạ", "Subtle Rim Sheen"),
    create_color_entry("col_eye_amber_glow",      "#FFF9C4", "Vệt tụ quang đáy mắt hổ phách phản chiếu", "Caustic Amber Light"),
    create_color_entry("col_eye_amber_bright",    "#FFF176", "Lõi đón sáng rực rỡ tròng mắt vàng", "Luminous Pupil Glow"),
    create_color_entry("col_eye_amber_main",      "#FFCA28", "Sắc vàng mật ong hổ phách nguyên bản", "Pure Honey Amber Crystal"),
    create_color_entry("col_eye_amber_shadow",    "#F57F17", "Viền đổ bóng sâu hốc mắt hổ phách", "Deep Amber Refraction"),
    create_color_entry("col_cheek_cyan_bright",   "#00E5FF", "Hai đốm má ngọc lam phát quang đặc trưng", "Bioluminescent Cyan"),
    create_color_entry("col_cheek_cyan_core",     "#00B0FF", "Tâm má xanh da trời đậm nét", "Cyan Core Hue"),
    create_color_entry("col_cheek_cyan_soft",     "#80D8FF", "Quầng sáng lam dịu quanh má", "Cyan Soft Bloom"),
    create_color_entry("col_blush_pink_soft",     "#F472B6", "Má hồng phấn bẽn lẽn phớt nhẹ ngọt ngào", "Blush Powder Velvet"),
    create_color_entry("col_mouth_inner_pink",    "#FF4081", "Khoang miệng hoa hồng hé mở", "Moist Mucosa Sheen"),
    create_color_entry("col_mouth_tongue",        "#FF80AB", "Lưỡi hồng đào nhỏ xíu ngây thơ", "Soft Tongue Highlight"),
    create_color_entry("col_mouth_rim",           "#0F1114", "Viền môi đen tuyền sắc sảo", "Sharp Ink Outline"),
    create_color_entry("col_white_sparkle",       "#FFFFFF", "Bắt sáng pha lê 3 điểm và tâm kim cương", "Pure Crystal Glint"),
    create_color_entry("col_stardust_gold",       "#FFE082", "Bụi sao vàng hoàng kim xoay quanh đai", "Orbiting Stardust Spark"),
    create_color_entry("col_stardust_cyan",       "#40C4FF", "Bụi sao xanh ngọc thiên hà", "Orbiting Cyan Stardust"),
    create_color_entry("col_astral_halo",         "#3B1A54", "Vầng hào quang tinh vân mờ ảo dưới đáy", "Zero-Gravity Base Halo")
]

cpp_scaled_canvas_code = """// =========================================================================
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
"""

js_canvas_code = """// =========================================================================
// 09_MYTHIC_COSMOG_NEBULA_BABY - Modern HTML5 Canvas 2D Implementation
// 100% Anatomical Likeness & High-End 3D Pop Mart Vinyl Aesthetic
// Organic Micro-Physics: 5% Squash & Stretch, 80ms Lag Puffs, Orbiting Stars
// =========================================================================
function drawCosmogNebulaBaby(ctx, cx, cy, scale, t) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.scale(scale, scale);

  // -----------------------------------------------------------------------
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (ORGANIC ZERO-G PHYSICS)
  // -----------------------------------------------------------------------
  const breathFreq  = 2.0;
  const breathPhase = t * breathFreq;
  const breathSin   = Math.sin(breathPhase);

  // Nhịp bồng bềnh lơ lửng không trọng lực (Hovering Float Offset)
  const hoverOffsetY = breathSin * 4.0;
  const by = hoverOffsetY;

  // Squash & Stretch đàn hồi 5% (Bảo toàn thể tích thực tế)
  const sY = 1.0 + 0.05 * breathSin;
  const sX = 1.0 - 0.025 * breathSin;

  // Trễ pha động học 80ms của hai búi mây tinh vân trên đỉnh (Delta Phi = 0.25 rad)
  const lagTuftL = breathPhase - 0.25;
  const lagTuftR = breathPhase - 0.25 + 0.12;
  const tuftSwayLX = Math.sin(lagTuftL) * 3.5;
  const tuftSwayLY = Math.cos(lagTuftL) * 2.2;
  const tuftRotL   = Math.sin(lagTuftL) * 0.06;

  const tuftSwayRX = Math.sin(lagTuftR) * 3.5;
  const tuftSwayRY = Math.cos(lagTuftR) * 2.2;
  const tuftRotR   = Math.sin(lagTuftR) * 0.06;

  // Chu kỳ chớp mắt tự nhiên 3.5s (140ms duration)
  const blinkCycle = (t * 1000) % 3500;
  const blink = blinkCycle < 140;

  // -----------------------------------------------------------------------
  // 2. LAYER 0: VẦNG HÀO QUANG MỜ ẢO ĐÁY THAY CHO BÓNG SÀN (ASTRAL NEBULA HALO)
  // -----------------------------------------------------------------------
  ctx.save();
  const haloY = 46;
  const haloRx = Math.max(16, (34.0 - hoverOffsetY * 1.2) * sX);
  const haloRy = Math.max(5, 10.0 - hoverOffsetY * 0.35);
  const haloAlpha = 0.45 + (hoverOffsetY / 4.0) * 0.15;

  const haloGrad = ctx.createRadialGradient(0, haloY, 2, 0, haloY, haloRx);
  haloGrad.addColorStop(0, `rgba(123, 31, 162, ${haloAlpha * 0.8})`);
  haloGrad.addColorStop(0.4, `rgba(74, 20, 140, ${haloAlpha * 0.5})`);
  haloGrad.addColorStop(0.75, `rgba(26, 16, 60, ${haloAlpha * 0.25})`);
  haloGrad.addColorStop(1, "rgba(26, 16, 60, 0)");
  ctx.fillStyle = haloGrad;
  ctx.beginPath();
  ctx.ellipse(0, haloY, haloRx, haloRy, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // -----------------------------------------------------------------------
  // 3. LAYER 1: ĐĨA VÀNG KHUYẾT PHÍA SAU (REAR GOLDEN CRESCENT DISC & BAND)
  // -----------------------------------------------------------------------
  ctx.save();
  ctx.translate(0, by);

  // Sừng trên đĩa vàng khuyết vươn cao góc 1h (Top Horn)
  const topHornGrad = ctx.createLinearGradient(6, -16, 18, -42);
  topHornGrad.addColorStop(0, "#CA8A04");
  topHornGrad.addColorStop(0.4, "#FFEE58");
  topHornGrad.addColorStop(0.8, "#FFF59D");
  topHornGrad.addColorStop(1, "#FFFDE7");
  ctx.fillStyle = topHornGrad;
  ctx.strokeStyle = "#9E9D24";
  ctx.lineWidth = 1.0;

  ctx.beginPath();
  ctx.moveTo(4, -14);
  ctx.quadraticCurveTo(8, -28, 17, -42);
  ctx.quadraticCurveTo(22, -26, 18, -20);
  ctx.closePath();
  ctx.fill();
  ctx.stroke();

  // Highlight sống đĩa vàng
  ctx.strokeStyle = "rgba(255, 253, 231, 0.9)";
  ctx.lineWidth = 1.2;
  ctx.beginPath();
  ctx.moveTo(5, -14);
  ctx.quadraticCurveTo(9, -27, 16.5, -41);
  ctx.stroke();

  // Sừng dưới đĩa vàng khuyết chúc xuống góc 7h (Bottom Horn)
  const botHornGrad = ctx.createLinearGradient(-4, 20, -16, 50);
  botHornGrad.addColorStop(0, "#CA8A04");
  botHornGrad.addColorStop(0.4, "#FFEE58");
  botHornGrad.addColorStop(0.8, "#FFF59D");
  botHornGrad.addColorStop(1, "#FFFDE7");
  ctx.fillStyle = botHornGrad;
  ctx.strokeStyle = "#9E9D24";
  ctx.lineWidth = 1.0;

  ctx.beginPath();
  ctx.moveTo(-4, 20);
  ctx.quadraticCurveTo(-8, 36, -15, 50);
  ctx.quadraticCurveTo(-22, 34, -16, 26);
  ctx.closePath();
  ctx.fill();
  ctx.stroke();

  ctx.strokeStyle = "rgba(255, 253, 231, 0.9)";
  ctx.lineWidth = 1.2;
  ctx.beginPath();
  ctx.moveTo(-16, 26);
  ctx.quadraticCurveTo(-18, 38, -14.5, 49);
  ctx.stroke();
  ctx.restore();

  // -----------------------------------------------------------------------
  // 4. LAYER 2: KHỐI ĐÁM MÂY TINH VÂN VŨ TRỤ (MAIN NEBULA CLOUD BODY)
  // -----------------------------------------------------------------------
  ctx.save();
  ctx.translate(0, by);
  ctx.scale(sX, sY);

  // 4.1 Thùy mây đáy dưới (Hồng cánh sen rực rỡ & Magenta dạ quang)
  function drawNebulaLobe(x, y, rx, ry, colorInner, colorOuter, alpha = 0.95) {
    ctx.save();
    const grad = ctx.createRadialGradient(x - rx * 0.25, y - ry * 0.25, rx * 0.15, x, y, Math.max(rx, ry));
    grad.addColorStop(0, colorInner);
    grad.addColorStop(0.7, colorOuter);
    grad.addColorStop(1, "rgba(26, 16, 60, 0.9)");
    ctx.fillStyle = grad;
    ctx.beginPath();
    ctx.ellipse(x, y, rx, ry, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }

  // Cụm thùy dưới
  drawNebulaLobe(0, 24, 20, 15, "#E91E63", "#7B1FA2");
  drawNebulaLobe(-16, 20, 16, 13, "#FF4081", "#8E24AA");
  drawNebulaLobe(16, 18, 16, 13, "#D81B60", "#6A1B9A");
  drawNebulaLobe(-8, 28, 12, 10, "#FF80AB", "#AD1457");
  drawNebulaLobe(8, 27, 12, 10, "#FF4081", "#880E4F");

  // Cụm thùy sườn giữa
  drawNebulaLobe(-26, 4, 16, 14, "#8E24AA", "#2E124D");
  drawNebulaLobe(27, 4, 16, 14, "#7B1FA2", "#2E124D");

  // Cụm thùy đỉnh & trung tâm (Lõi chàm tím huyền bí)
  drawNebulaLobe(0, -14, 20, 14, "#4A148C", "#1A103C");
  drawNebulaLobe(-17, -12, 14, 12, "#3F1968", "#1A103C");
  drawNebulaLobe(17, -12, 14, 12, "#3F1968", "#1A103C");
  drawNebulaLobe(0, 2, 22, 18, "#2E124D", "#1A103C");

  // Ánh sáng phát quang bên dưới lớp mây
  const innerGlow = ctx.createRadialGradient(0, 8, 4, 0, 8, 26);
  innerGlow.addColorStop(0, "rgba(233, 30, 99, 0.35)");
  innerGlow.addColorStop(0.6, "rgba(123, 31, 162, 0.2)");
  innerGlow.addColorStop(1, "rgba(26, 16, 60, 0)");
  ctx.fillStyle = innerGlow;
  ctx.beginPath();
  ctx.ellipse(0, 8, 26, 22, 0, 0, Math.PI * 2);
  ctx.fill();

  ctx.restore();

  // -----------------------------------------------------------------------
  // 5. LAYER 3: HAI BÚI MÂY TINH VÂN XANH LAM TRÊN ĐỈNH (TWIN NEBULA TUFTS)
  // -----------------------------------------------------------------------
  ctx.save();
  ctx.translate(0, by);

  // Cuống mây trái
  ctx.save();
  const stemLGrad = ctx.createLinearGradient(-12, -14, -36 + tuftSwayLX, -42 + tuftSwayLY);
  stemLGrad.addColorStop(0, "#1A103C");
  stemLGrad.addColorStop(0.4, "#0D47A1");
  stemLGrad.addColorStop(1, "#0288D1");
  ctx.fillStyle = stemLGrad;
  ctx.beginPath();
  ctx.moveTo(-16, -12);
  ctx.quadraticCurveTo(-24 + tuftSwayLX * 0.4, -28, -38 + tuftSwayLX, -44 + tuftSwayLY);
  ctx.lineTo(-32 + tuftSwayLX, -46 + tuftSwayLY);
  ctx.quadraticCurveTo(-18 + tuftSwayLX * 0.4, -24, -8, -14);
  ctx.closePath();
  ctx.fill();

  // Búi mây tinh vân trái (Left Cloud Puff)
  ctx.translate(-42 + tuftSwayLX, -54 + tuftSwayLY);
  ctx.rotate(tuftRotL);

  function drawCloudBubble(x, y, r, innerCol, outerCol) {
    ctx.save();
    const g = ctx.createRadialGradient(x - r * 0.3, y - r * 0.3, r * 0.15, x, y, r);
    g.addColorStop(0, innerCol);
    g.addColorStop(0.6, outerCol);
    g.addColorStop(1, "rgba(2, 136, 209, 0.85)");
    ctx.fillStyle = g;
    ctx.beginPath();
    ctx.arc(x, y, r, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }

  drawCloudBubble(0, 0, 15, "#E0F7FA", "#00E5FF");
  drawCloudBubble(4, -9, 12, "#FFFFFF", "#80D8FF");
  drawCloudBubble(-10, 2, 11, "#E0F7FA", "#0288D1");
  drawCloudBubble(10, -2, 11, "#80D8FF", "#00E5FF");
  drawCloudBubble(-5, 9, 10, "#80D8FF", "#0288D1");
  drawCloudBubble(1, -3, 9, "#FFFFFF", "#E0F7FA");

  // Bụi sao kim cương phát quang trên búi mây trái
  drawDiamondStar(ctx, 0, -4, 6, "#FFFFFF");
  drawDiamondStar(ctx, 7, -10, 3.5, "#E0F7FA");
  drawStardustDot(ctx, -7, -3, 1.5, "#FFFFFF");
  drawStardustDot(ctx, -3, 7, 1.2, "#80D8FF");
  drawStardustDot(ctx, 8, 5, 1.2, "#E0F7FA");
  ctx.restore();

  // Cuống mây phải
  ctx.save();
  const stemRGrad = ctx.createLinearGradient(12, -14, 38 + tuftSwayRX, -38 + tuftSwayRY);
  stemRGrad.addColorStop(0, "#1A103C");
  stemRGrad.addColorStop(0.4, "#0D47A1");
  stemRGrad.addColorStop(1, "#0288D1");
  ctx.fillStyle = stemRGrad;
  ctx.beginPath();
  ctx.moveTo(8, -14);
  ctx.quadraticCurveTo(20 + tuftSwayRX * 0.4, -26, 34 + tuftSwayRX, -42 + tuftSwayRY);
  ctx.lineTo(40 + tuftSwayRX, -40 + tuftSwayRY);
  ctx.quadraticCurveTo(26 + tuftSwayRX * 0.4, -24, 16, -12);
  ctx.closePath();
  ctx.fill();

  // Búi mây tinh vân phải (Right Cloud Puff)
  ctx.translate(44 + tuftSwayRX, -50 + tuftSwayRY);
  ctx.rotate(tuftRotR);

  drawCloudBubble(0, 0, 15, "#E0F7FA", "#00E5FF");
  drawCloudBubble(3, -9, 12, "#FFFFFF", "#80D8FF");
  drawCloudBubble(10, 2, 11, "#E0F7FA", "#0288D1");
  drawCloudBubble(-10, -2, 11, "#80D8FF", "#00E5FF");
  drawCloudBubble(5, 9, 10, "#80D8FF", "#0288D1");
  drawCloudBubble(-1, -3, 9, "#FFFFFF", "#E0F7FA");

  // Bụi sao kim cương phát quang trên búi mây phải
  drawDiamondStar(ctx, 2, -4, 6, "#FFFFFF");
  drawDiamondStar(ctx, -6, -9, 3.5, "#E0F7FA");
  drawStardustDot(ctx, 7, -3, 1.5, "#FFFFFF");
  drawStardustDot(ctx, 3, 7, 1.2, "#80D8FF");
  drawStardustDot(ctx, -8, 5, 1.2, "#E0F7FA");
  ctx.restore();

  // Các giọt tinh vân trôi dạt (Drifting Astral Droplets)
  drawAstralDroplet(ctx, -64 + tuftSwayLX * 0.7, -66 + tuftSwayLY * 0.6, 4.5, -0.4);
  drawAstralDroplet(ctx, -48 + tuftSwayLX * 0.5, -28 + tuftSwayLY * 0.4, 3.5, -0.2);
  drawAstralDroplet(ctx, 64 + tuftSwayRX * 0.7, -58 + tuftSwayRY * 0.6, 4.5, 0.4);
  drawAstralDroplet(ctx, 58 + tuftSwayRX * 0.5, -38 + tuftSwayRY * 0.4, 3.5, 0.3);

  ctx.restore();

  // -----------------------------------------------------------------------
  // 6. LAYER 4: VÒNG ĐAI HOÀNG KIM ÔM TRƯỚC THÂN (FRONT GOLDEN RING & CRESCENTS)
  // -----------------------------------------------------------------------
  ctx.save();
  ctx.translate(0, by);

  // Vành đai vàng ôm quanh eo
  ctx.save();
  ctx.rotate((-38 * Math.PI) / 180);
  const ringGrad = ctx.createLinearGradient(-34, 0, 34, 0);
  ringGrad.addColorStop(0, "#CA8A04");
  ringGrad.addColorStop(0.25, "#FFEE58");
  ringGrad.addColorStop(0.5, "#FFFDE7");
  ringGrad.addColorStop(0.75, "#FFEE58");
  ringGrad.addColorStop(1, "#CA8A04");
  ctx.strokeStyle = ringGrad;
  ctx.lineWidth = 2.4;
  ctx.beginPath();
  ctx.ellipse(0, 0, 31 * sX, 12 * sY, 0, 0, Math.PI * 2);
  ctx.stroke();
  ctx.restore();

  ctx.restore();

  // -----------------------------------------------------------------------
  // 7. LAYER 5: MẶT NẠ ĐÁM MÂY ĐEN TUYỀN (SCALLOPED CHARCOAL FACE MASK)
  // -----------------------------------------------------------------------
  ctx.save();
  ctx.translate(0, by);
  ctx.scale(sX, sY);

  ctx.shadowColor = "rgba(15, 23, 42, 0.65)";
  ctx.shadowBlur = 8;

  const maskGrad = ctx.createRadialGradient(-3, -4, 3, 0, 0, 20);
  maskGrad.addColorStop(0, "#2A3038");
  maskGrad.addColorStop(0.5, "#1E2328");
  maskGrad.addColorStop(0.9, "#14171A");
  maskGrad.addColorStop(1, "#0D0F12");
  ctx.fillStyle = maskGrad;

  // Điêu khắc đám mây 5 thùy sắc nét Pop Mart
  ctx.beginPath();
  ctx.arc(0, -7, 11, 0, Math.PI * 2);       // Thùy đỉnh
  ctx.arc(-11, -3, 10, 0, Math.PI * 2);     // Thùy trên trái
  ctx.arc(11, -3, 10, 0, Math.PI * 2);      // Thùy trên phải
  ctx.arc(-8, 9, 11, 0, Math.PI * 2);       // Thùy dưới trái
  ctx.arc(8, 9, 11, 0, Math.PI * 2);        // Thùy dưới phải
  ctx.arc(0, 1, 13, 0, Math.PI * 2);        // Lõi trung tâm
  ctx.fill();

  ctx.shadowBlur = 0;
  ctx.strokeStyle = "rgba(51, 65, 85, 0.6)";
  ctx.lineWidth = 1.0;
  ctx.stroke();

  // -----------------------------------------------------------------------
  // 8. LAYER 6: ĐÔI MÁ NGỌC LAM & MÁ HỒNG PHẤN BẼN LẼN (CHEEK BLUSHES)
  // -----------------------------------------------------------------------
  const cheekYL = 4;
  const cheekYR = 4;
  const cheekXL = -14;
  const cheekXR = 14;

  // Vầng má hồng phấn bẽn lẽn phớt nhẹ Chibi
  const blushGradL = ctx.createRadialGradient(cheekXL, cheekYL, 1, cheekXL, cheekYL, 8);
  blushGradL.addColorStop(0, "rgba(244, 114, 182, 0.65)");
  blushGradL.addColorStop(0.6, "rgba(251, 207, 232, 0.35)");
  blushGradL.addColorStop(1, "rgba(251, 207, 232, 0)");
  ctx.fillStyle = blushGradL;
  ctx.beginPath();
  ctx.arc(cheekXL, cheekYL, 8, 0, Math.PI * 2);
  ctx.fill();

  const blushGradR = ctx.createRadialGradient(cheekXR, cheekYR, 1, cheekXR, cheekYR, 8);
  blushGradR.addColorStop(0, "rgba(244, 114, 182, 0.65)");
  blushGradR.addColorStop(0.6, "rgba(251, 207, 232, 0.35)");
  blushGradR.addColorStop(1, "rgba(251, 207, 232, 0)");
  ctx.fillStyle = blushGradR;
  ctx.beginPath();
  ctx.arc(cheekXR, cheekYR, 8, 0, Math.PI * 2);
  ctx.fill();

  // Đốm má tròn xanh lơ ngọc bích phát quang đặc trưng
  function drawCyanCheek(cxPos, cyPos) {
    ctx.save();
    ctx.shadowColor = "rgba(0, 229, 255, 0.75)";
    ctx.shadowBlur = 6;

    const cGrad = ctx.createRadialGradient(cxPos - 1, cyPos - 1, 1, cxPos, cyPos, 5);
    cGrad.addColorStop(0, "#E0F7FA");
    cGrad.addColorStop(0.35, "#80D8FF");
    cGrad.addColorStop(0.7, "#00E5FF");
    cGrad.addColorStop(1, "#0091EA");
    ctx.fillStyle = cGrad;
    ctx.beginPath();
    ctx.arc(cxPos, cyPos, 4.8, 0, Math.PI * 2);
    ctx.fill();

    // Điểm bắt sáng men sứ má
    ctx.fillStyle = "#FFFFFF";
    ctx.beginPath();
    ctx.arc(cxPos - 1.2, cyPos - 1.2, 1.2, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }

  drawCyanCheek(cheekXL, cheekYL);
  drawCyanCheek(cheekXR, cheekYR);

  // -----------------------------------------------------------------------
  // 9. LAYER 7: MIỆNG NHỎ XINH HÉ MỞ (CUTE OPEN MOUTH)
  // -----------------------------------------------------------------------
  ctx.save();
  const mouthY = 7.5;
  ctx.beginPath();
  ctx.ellipse(0, mouthY, 3.8, 4.2, 0, 0, Math.PI * 2);
  const mGrad = ctx.createLinearGradient(0, mouthY - 3, 0, mouthY + 4);
  mGrad.addColorStop(0, "#4A0E2E");
  mGrad.addColorStop(0.5, "#D81B60");
  mGrad.addColorStop(1, "#FF4081");
  ctx.fillStyle = mGrad;
  ctx.fill();
  ctx.strokeStyle = "#0F1114";
  ctx.lineWidth = 0.8;
  ctx.stroke();

  // Lưỡi hồng đào nhỏ xíu ngây thơ
  ctx.beginPath();
  ctx.ellipse(0, mouthY + 2.2, 2.5, 1.8, 0, 0, Math.PI * 2);
  ctx.fillStyle = "#FF80AB";
  ctx.fill();

  // Điểm nước bóng môi
  ctx.fillStyle = "rgba(255, 255, 255, 0.85)";
  ctx.beginPath();
  ctx.arc(0, mouthY - 1.8, 0.8, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // -----------------------------------------------------------------------
  // 10. LAYER 8: ĐÔI MẮT HỔ PHÁCH VÀNG TO TRÒN TRONG VEO (CRYSTAL AMBER EYES)
  // -----------------------------------------------------------------------
  const eyeY = 0;
  const eyeXL = -6.8;
  const eyeXR = 6.8;

  function drawAmberEye(ex, ey, isLeft, isBlink) {
    ctx.save();
    if (isBlink) {
      // Mí mắt cong cười hạnh phúc
      ctx.strokeStyle = "#F57F17";
      ctx.lineWidth = 2.4;
      ctx.lineCap = "round";
      ctx.beginPath();
      ctx.arc(ex, ey + 1, 4.5, 0.2 * Math.PI, 0.8 * Math.PI, false);
      ctx.stroke();

      ctx.strokeStyle = "#FFEE58";
      ctx.lineWidth = 1.0;
      ctx.beginPath();
      ctx.arc(ex, ey + 1, 4.0, 0.25 * Math.PI, 0.75 * Math.PI, false);
      ctx.stroke();
    } else {
      // Hốc mắt vàng hổ phách 3 tầng
      ctx.shadowColor = "rgba(255, 202, 40, 0.6)";
      ctx.shadowBlur = 8;

      const eyeGrad = ctx.createLinearGradient(ex, ey - 7, ex, ey + 7);
      eyeGrad.addColorStop(0, "#FFF9C4");
      eyeGrad.addColorStop(0.2, "#FFF176");
      eyeGrad.addColorStop(0.6, "#FFCA28");
      eyeGrad.addColorStop(0.9, "#FFB300");
      eyeGrad.addColorStop(1, "#F57F17");
      ctx.fillStyle = eyeGrad;

      ctx.beginPath();
      ctx.ellipse(ex, ey, 4.8, 7.5, 0, 0, Math.PI * 2);
      ctx.fill();

      ctx.shadowBlur = 0;
      ctx.strokeStyle = "#E65100";
      ctx.lineWidth = 0.8;
      ctx.stroke();

      // Vùng khúc xạ tụ quang đáy mắt
      ctx.beginPath();
      ctx.ellipse(ex, ey + 3.2, 3.2, 2.2, 0, 0, Math.PI);
      ctx.fillStyle = "rgba(255, 249, 196, 0.65)";
      ctx.fill();

      // 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Specular System)
      // Điểm 1: Direct keylight lớn góc 10h
      ctx.fillStyle = "#FFFFFF";
      ctx.beginPath();
      ctx.arc(ex - 1.5, ey - 3.2, 1.8, 0, Math.PI * 2);
      ctx.fill();

      // Điểm 2: Caustic ground bounce góc 4h
      ctx.fillStyle = "#FFFDE7";
      ctx.beginPath();
      ctx.arc(ex + 1.6, ey + 3.0, 1.1, 0, Math.PI * 2);
      ctx.fill();

      // Điểm 3: Surface wetness micro-sparkle góc 1h
      ctx.fillStyle = "#FFFFFF";
      ctx.beginPath();
      ctx.arc(ex + 1.5, ey - 1.6, 0.8, 0, Math.PI * 2);
      ctx.fill();
    }
    ctx.restore();
  }

  drawAmberEye(eyeXL, eyeY, true, blink);
  drawAmberEye(eyeXR, eyeY, false, blink);

  ctx.restore(); // Restore head & body scale

  // -----------------------------------------------------------------------
  // 11. LAYER 9: TINH TÚ NGÂN HÀ XOAY TRÒN QUANH VÒNG ĐAI VÀNG (ORBITING STARDUST)
  // -----------------------------------------------------------------------
  ctx.save();
  ctx.translate(0, by);
  const orbitT = t * 3.0;
  const numParticles = 6;

  for (let i = 0; i < numParticles; i++) {
    const pAngle = orbitT + i * ((Math.PI * 2) / numParticles);
    const ox = Math.cos(pAngle) * (34.0 * sX);
    const oy = Math.sin(pAngle) * (14.0 * sY);

    // Xoay nghiêng theo góc vòng đai ~ -38 độ
    const rot = (-38 * Math.PI) / 180;
    const px = ox * Math.cos(rot) - oy * Math.sin(rot);
    const py = ox * Math.sin(rot) + oy * Math.cos(rot);

    // Độ lớn và màu sắc vi hạt
    const pScale = 0.7 + 0.3 * Math.sin(pAngle + t);
    const pCol = (i % 3 === 0) ? "#FFFFFF" : (i % 3 === 1 ? "#FFEE58" : "#00E5FF");

    ctx.save();
    ctx.translate(px, py);
    ctx.fillStyle = pCol;
    ctx.shadowColor = pCol;
    ctx.shadowBlur = 5;
    ctx.beginPath();
    ctx.arc(0, 0, 1.6 * pScale, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }
  ctx.restore();

  ctx.restore(); // Restore root translation & scale
}

// -------------------------------------------------------------------------
// HELPER DRAWING FUNCTIONS
// -------------------------------------------------------------------------
function drawDiamondStar(ctx, x, y, r, color) {
  ctx.save();
  ctx.translate(x, y);
  ctx.fillStyle = color;
  ctx.shadowColor = color;
  ctx.shadowBlur = 6;
  ctx.beginPath();
  ctx.moveTo(0, -r);
  ctx.quadraticCurveTo(0, 0, r, 0);
  ctx.quadraticCurveTo(0, 0, 0, r);
  ctx.quadraticCurveTo(0, 0, -r, 0);
  ctx.quadraticCurveTo(0, 0, 0, -r);
  ctx.closePath();
  ctx.fill();

  ctx.fillStyle = "#FFFFFF";
  ctx.beginPath();
  ctx.arc(0, 0, r * 0.3, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();
}

function drawStardustDot(ctx, x, y, r, color) {
  ctx.save();
  ctx.fillStyle = color;
  ctx.beginPath();
  ctx.arc(x, y, r, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();
}

function drawAstralDroplet(ctx, x, y, r, rot) {
  ctx.save();
  ctx.translate(x, y);
  ctx.rotate(rot);

  const dropGrad = ctx.createRadialGradient(-r * 0.2, -r * 0.3, r * 0.2, 0, 0, r);
  dropGrad.addColorStop(0, "#E0F7FA");
  dropGrad.addColorStop(0.5, "#00E5FF");
  dropGrad.addColorStop(1, "#0288D1");
  ctx.fillStyle = dropGrad;

  ctx.beginPath();
  ctx.moveTo(0, -r * 1.5);
  ctx.bezierCurveTo(r * 0.8, -r * 0.5, r, r * 0.5, 0, r);
  ctx.bezierCurveTo(-r, r * 0.5, -r * 0.8, -r * 0.5, 0, -r * 1.5);
  ctx.closePath();
  ctx.fill();

  ctx.fillStyle = "rgba(255, 255, 255, 0.8)";
  ctx.beginPath();
  ctx.arc(-r * 0.2, -r * 0.4, r * 0.28, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();
}
"""

cosmog_master_entry = {
    "id": 9,
    "global_id": 9,
    "pokedex_number": 789,
    "code": "MYTHIC_COSMOG_NEBULA_BABY",
    "name_vi": "Cosmog - Đám Mây Tinh Vân Vũ Trụ (Bé Cưng Tinh Cầu Nguyên Sơ)",
    "name_en": "Mythic Cosmog the Nebula Baby (Celestial Cloud Child)",
    "japanese_name": "コスモッグ (Cosmog - 星の子)",
    "species": "Nebula Pokémon (Linh Thú Tinh Vân)",
    "category": "Linh Thú Thần Thoại Không Gian Tối Cao (Mythical Celestial / Legendary Space Deity)",
    "element": "Psychic / Cosmic Nebula (Tâm Linh Không Gian & Tinh Vân Thiên Thể)",
    "signature_sound": "Pew! ✨ (Tiếng kêu ngân vang thanh thót như chuông gió pha lê dải ngân hà)",
    "quotes": {
        "vi": "Em là hạt mầm của cả dải ngân hà, bồng bềnh lơ lửng giữa những đám mây tinh vân để sưởi ấm những giấc mơ thuần khiết nhất.",
        "en": "Born from the cradle of ancient stardust, floating through the endless cosmos to light up your darkest night."
    },
    "mythology_lore": [
        "太古の昔に『星の子』と呼ばれ、異空間から現れたとされる謎多き伝説のポケモン (Thời viễn cổ, Cosmog được xưng tụng là 'Hài Nhi Tinh Tú' giáng trần từ không gian đa chiều huyền bí).",
        "ガス状の体は風に吹かれるほど軽く、夜空の星屑を吸い込んでゆっくりと成長する (Thân thể khí thể tinh vân nhẹ tựa lông hồng bay theo làn gió đêm, hấp thụ bụi sao để dần ngưng kết và lớn lên).",
        "心優しき者に出会うと、金色の軌道環を煌めかせながら愛らしい声『ピュー！』と鳴いて懐く (Khi gặp người có trái tim nhân từ, Cosmog xoay tròn vòng đai vàng hoàng kim và cất tiếng reo 'Pew!' vô cùng đáng yêu).",
        "その小さな体には銀河系を丸ごと包み込むほどの莫大な宇宙エネルギーが秘められている (Bên trong thân hình bé bỏng núng nính là nguồn năng lượng vũ trụ vô tận đủ sức khai sinh cả một thái dương hệ mới)."
    ],
    "palette": cosmog_palette,
    "volumetric_anatomy": {
        "style_archetype": "High-End Pop Mart / Vinyl Blind Box 3D Figurine with Cosmic Subsurface Scattering & Ceramic Sheen",
        "nebula_cloud_core": {
            "description": "Thân là khối đám mây tinh vân đa thùy bồng bềnh chuyển sắc mờ ảo huyền bí. Đáy dưới mang sắc hồng cánh sen (#D81B60, #E91E63) và magenta dạ quang (#7B1FA2), chuyển tiếp mượt mà lên tím tử la (#4A148C) và lõi chàm tím sâu thẳm (#1A103C). Bề mặt mềm mịn phúng phính Pop Mart Vinyl với độ sâu tán xạ dưới bề mặt (SSS).",
            "proportions": "Thùy chính tâm y = +2px, bán kính 22px; thùy đáy dưới y = +24px rực hồng cánh sen."
        },
        "twin_nebula_tufts": {
            "description": "Hai cuống mây tinh vân xanh lam vươn cong lên hai bên đỉnh đầu. Chóp cuống nở bung thành hai búi mây tròn phồng màu xanh lơ cyan điện tử (#00E5FF, #80D8FF) và lam thanh khiết (#0288D1). Bên trong đính các cụm bụi sao kim cương phát quang 4 cánh tinh khiết.",
            "lag_physics": "Chuyển động trễ pha 80ms (Delta Phi = 0.25 rad) nhịp nhàng như hai chùm bong bóng xà phòng vũ trụ đang bồng bềnh."
        },
        "drifting_astral_droplets": {
            "description": "4 Hạt sương tinh vân tách rời lơ lửng tự do xung quanh hai búi mây (2 bên trái, 2 bên phải), dao động vi mô bồng bềnh theo dòng hạt gió sao."
        },
        "golden_crescent_rings": {
            "description": "Vòng đai hoàng kim vương giả ôm quanh thân nghiêng một góc 38 độ theo mặt phẳng quỹ đạo hành tinh. Gồm đĩa vàng khuyết trên vươn cao chóp sừng đón sáng tại góc 1h và đĩa vàng khuyết dưới cong cong ôm trọn đáy mây tại góc 7h, bề mặt mạ vàng vát 3D bóng bẩy (#FFEE58, #FFFDE7, #F57F17).",
            "protective_role": "Đĩa vàng khuyết đóng vai trò là chiếc nôi không gian bảo hộ nguồn năng lượng sơ sinh của Cosmog."
        },
        "scalloped_charcoal_face_mask": {
            "description": "Mặt nạ đám mây đen tuyền 5 thùy uốn lượn sắc sảo chiếm vị trí trung tâm cơ thể. Bề mặt chất liệu đá obsidian đen mờ (Matte Charcoal Vinyl) tương phản tuyệt đối với vầng tinh vân dạ quang xung quanh.",
            "contour": "5 Thùy mây tròn trịa ôm lấy đôi mắt hổ phách, hai má ngọc lam và khóe miệng bé xíu."
        },
        "crystal_amber_eyes": {
            "archetype": "Đôi Mắt Hổ Phách Vàng To Tròn Trong Veo (3-Point Specular Amber Crystal Eyes)",
            "description": "Đôi mắt hình hạt đậu / bầu dục đứng màu vàng mật ong hổ phách (#FFCA28, #FFF176) với chiều sâu khúc xạ đáy mắt (#FFF9C4).",
            "point_1_primary": {"role": "Direct Keylight Specular", "coords": "Góc 10h (2x2 pixel)", "color": "0xFFFF (#FFFFFF)"},
            "point_2_secondary": {"role": "Caustic Ground Bounce", "coords": "Góc 4h (1x1 pixel)", "color": "0xFFB3 (#FFF9C4)"},
            "point_3_tertiary": {"role": "Surface Wetness Slit Glint", "coords": "Góc 1h (1x1 pixel)", "color": "0xFFFF (#FFFFFF)"},
            "blinking": "Khi chớp mắt 3.5s (140ms), mắt khép thành đường cong lưỡi liềm cười ngây ngô bẽn lẽn."
        },
        "cyan_cheeks_and_powder_blush": {
            "description": "Hai đốm má ngọc lam tròn xoe phát quang (#00E5FF, #00B0FF) đặc trưng của Cosmog, được phớt nhẹ lớp má hồng phấn bẽn lẽn (#F472B6) mang phong cách Chibi siêu ngọt ngào.",
            "coords": "Tọa độ (-14px, +4px) và (+14px, +4px) trên mặt nạ đen."
        },
        "cute_open_mouth": {
            "description": "Chiếc miệng nhỏ xíu hình giọt nước ngược hé mở tinh nghịch, khoe khoang miệng màu hồng mâm xôi (#D81B60) và chiếc lưỡi đào tí hon (#FF80AB)."
        },
        "orbiting_galactic_stardust": {
            "description": "6 Hạt tinh tú ngân hà (kim cương trắng, bụi vàng, ngọc lam) xoay tròn liên tục quanh vòng đai vàng theo quỹ đạo elip nghiêng 38 độ, tạo hiệu ứng thiên hà sống động 60 FPS."
        },
        "zero_gravity_base_halo": {
            "description": "Vầng hào quang tinh vân mờ ảo dưới đáy (Astral Nebula Base Halo) thay thế cho bóng sàn tiếp xúc cơ học, phản ánh đúng bản chất sinh vật không trọng lực của Cosmog."
        }
    },
    "kinematics": {
        "breath_frequency_hz": 0.32,
        "hover_vertical_amplitude_px": 4.0,
        "squash_and_stretch_vertical_pct": 5.0,
        "squash_and_stretch_horizontal_pct": -2.5,
        "twin_tufts_phase_lag_rad": 0.25,
        "twin_tufts_time_lag_ms": 80,
        "twin_tufts_sway_amplitude_px": 3.5,
        "blink_interval_ms": 3500,
        "blink_duration_ms": 140,
        "orbiting_stardust_speed_rad_s": 3.0,
        "diamond_sparkle_pulse_hz": 1.5
    },
    "cpp_scaled_canvas_code": cpp_scaled_canvas_code.strip(),
    "js_canvas_code": js_canvas_code.strip(),
    "visual_breakdown_checklist": [
        "1. Thân là khối đám mây tinh vân vũ trụ (Nebula cloud) chuyển sắc mờ ảo từ chàm tím vi lượng (#1A103C) sang hồng cánh sen rực rỡ (#D81B60, #E91E63).",
        "2. Hai búi mây tinh vân xanh lam trên đỉnh (Cyan & Electric Blue Cloud Puffs) nở bung tròn phồng với chùm bụi sao kim cương phát quang 4 cánh.",
        "3. Vòng đai hoàng kim vương giả ôm quanh thân với 2 đĩa vàng khuyết bảo vệ nghiêng góc 38 độ (sừng trên vươn cao góc 1h, sừng dưới ôm đáy góc 7h).",
        "4. Mặt nạ đám mây đen tuyền 5 thùy uốn lượn sắc sảo (Scalloped Charcoal Black Face Mask) chất liệu obsidian matte tương phản tuyệt đối.",
        "5. Đôi mắt hổ phách vàng to tròn trong veo dạng hạt đậu đứng với hệ thống 3 điểm bắt sáng pha lê (Keylight, Ground Bounce, Micro Glint).",
        "6. Hai đốm má ngọc lam tròn xoe phát quang (#00E5FF) kết hợp lớp má hồng phấn bẽn lẽn (#F472B6) ngọt ngào Chibi.",
        "7. Miệng nhỏ xíu hé mở khoe khoang miệng màu hồng hoa sen và lưỡi đào tí hon.",
        "8. Chuyển động vi vật lý hữu cơ: Nhịp bồng bềnh không trọng lực Squash & Stretch 5% bảo toàn thể tích thực tế.",
        "9. Hai búi mây tinh vân uốn lượn xoay nhẹ trễ pha 80ms (Delta Phi = 0.25 rad).",
        "10. Các hạt tinh tú ngân hà lấp lánh xoay tròn 360 độ quanh vòng đai vàng theo quỹ đạo elip nghiêng.",
        "11. Nhịp chớp mắt 3.5s tự nhiên (140ms) khép thành vầng trăng khuyết cười bẽn lẽn đáng yêu.",
        "12. Vầng hào quang tinh vân mờ ảo dịu dàng dưới đáy thay cho bóng sàn cứng thông thường.",
        "13. Xuất đầy đủ mã C++ ScaledCanvas (100% phần cứng ESP32 ST7789) và mã JavaScript Canvas 2D 60 FPS."
    ]
}

master_doc = {
    "metadata": {
        "session": "session2_agent4",
        "agent_name": "Nghệ Sĩ Điêu Khắc Cosmog Đám Mây Tinh Vân Vũ Trụ (Cosmog Nebula Baby 3D Sculptor)",
        "agent_role": "Master 3D Pop Mart & Vinyl Creature Sculptor for IoT Digital Keychain",
        "version": "2.0.0-PRO-MAX",
        "created_date": "2026-09-04",
        "target_display": "ST7789 240x280 / 172x320 16-bit RGB565 IPS Display & Modern HTML5 Canvas 2D",
        "reference_artwork": "09_Mythic_Cosmog_Nebula_Baby.png",
        "design_frameworks": [
            "09_Mythic_Cosmog_Nebula_Baby.png (Official Master Artwork 100% Fidelity)",
            "Reffernce/NHOM_1_FRONTEND_UIUX/ui-ux-pro-max-skill-main (High-fidelity design intelligence, micro-interactions, anti-cheap-icon)",
            "Reffernce/NHOM_1_FRONTEND_UIUX/react-bits-main (Viscoelastic spring physics, fluid canvas motion, particle sparkles)",
            "Reffernce/NHOM_1_FRONTEND_UIUX/impeccable-main (Craft floor, material fidelity, organic depth)"
        ],
        "core_design_rules": {
            "nebula_body_rule": "Thân là khối đám mây tinh vân vũ trụ đa thùy bồng bềnh chuyển sắc mờ ảo huyền bí từ chàm tím vi lượng (#1A103C, #2E124D, #4A148C) ở trung tâm sang hồng magenta và cánh sen dạ quang (#7B1FA2, #D81B60, #E91E63) ở đáy dưới, tạo chiều sâu thể tích 3D Pop Mart mềm mại.",
            "golden_rings_rule": "Vòng đai hoàng kim vương giả ôm quanh thân với 2 đĩa vàng khuyết bảo vệ nghiêng góc 38 độ theo quỹ đạo thiên thể: đĩa vàng khuyết trên vươn cao chóp sừng đón sáng, đĩa vàng khuyết dưới uốn cong nâng đỡ khối mây tinh vân, viền vát 3D vàng hoàng kim (#FFFDE7, #FFF59D, #FFEE58, #F57F17).",
            "crystal_amber_eyes_rule": "Đôi mắt hổ phách vàng to tròn trong veo dạng hạt đậu đứng với 3 điểm bắt sáng pha lê vật lý (Điểm 1 keylight 2x2 góc 10h #FFFFFF, Điểm 2 caustic ground bounce #FFF9C4 góc 4h, Điểm 3 wetness micro-sparkle #FFFFFF góc 1h), đồng tử phát quang dịu êm.",
            "cheeks_blush_rule": "Hai đốm má tròn xanh lơ ngọc bích phát quang đặc trưng (#00E5FF, #00B0FF) đính hai bên mặt nạ đen, phủ lớp má hồng phấn bẽn lẽn (#F472B6) ngọt ngào Chibi.",
            "stardust_diamond_rule": "Bụi sao kim cương 4 cánh phát quang (#FFFFFF core, #80D8FF aura) lấp lánh chìm sâu trong hai búi mây tinh vân xanh lam và trôi nổi khắp cơ thể.",
            "zero_gravity_halo_rule": "Vầng hào quang tinh vân mờ ảo dịu dàng (Astral Nebula Aura) dưới đáy thay cho bóng sàn cứng thông thường, co giãn và mờ dần theo nhịp lơ lửng không trọng lực.",
            "kinematics_lag_rule": "Chuyển động vi vật lý hữu cơ: Nhịp bồng bềnh không trọng lực Squash & Stretch 5% (bảo toàn thể tích thực tế), hai búi mây tinh vân uốn lượn xoay nhẹ trễ pha 80ms (Delta Phi = 0.25 rad), các hạt tinh tú ngân hà lấp lánh xoay tròn quanh vòng đai vàng, nhịp chớp mắt 3.5s."
        }
    },
    "characters": [cosmog_master_entry]
}

# Write JSON file
base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
out_json_path = os.path.join(base_dir, "data", "session2_agent4_cosmog.json")

with open(out_json_path, "w", encoding="utf-8") as f:
    json.dump(master_doc, f, ensure_ascii=False, indent=2)

print(f"Generated Cosmog master JSON: {out_json_path}")
print(f"File size: {os.path.getsize(out_json_path)} bytes")

# Also generate interactive HTML preview
html_content = f"""<!DOCTYPE html>
<html lang="vi">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Cosmog Nebula Baby - 3D Pop Mart Sculpt & 60 FPS Micro-Physics</title>
  <style>
    :root {{
      --bg-space: #070913;
      --card-bg: rgba(22, 27, 46, 0.75);
      --border-glow: #00E5FF;
      --gold: #FFEE58;
      --nebula-pink: #E91E63;
      --text: #F1F5F9;
      --text-muted: #94A3B8;
    }}
    * {{ box-sizing: border-box; margin: 0; padding: 0; font-family: 'Segoe UI', system-ui, -apple-system, sans-serif; }}
    body {{
      background: radial-gradient(circle at 50% 25%, #1D1435 0%, var(--bg-space) 75%);
      color: var(--text);
      min-height: 100vh;
      padding: 24px;
      display: flex;
      flex-direction: column;
      align-items: center;
      overflow-x: hidden;
    }}
    header {{
      text-align: center;
      margin-bottom: 24px;
    }}
    h1 {{
      font-size: 2.2rem;
      background: linear-gradient(135deg, #00E5FF, #FFEE58, #E91E63);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
      margin-bottom: 8px;
      font-weight: 800;
    }}
    .subtitle {{
      color: var(--text-muted);
      font-size: 0.95rem;
    }}
    .tags {{
      display: flex;
      gap: 10px;
      justify-content: center;
      margin-top: 12px;
      flex-wrap: wrap;
    }}
    .tag {{
      background: rgba(0, 229, 255, 0.12);
      border: 1px solid rgba(0, 229, 255, 0.35);
      color: #80D8FF;
      padding: 4px 14px;
      border-radius: 9999px;
      font-size: 0.82rem;
      font-weight: 600;
    }}
    .tag.gold {{
      background: rgba(255, 238, 88, 0.12);
      border-color: rgba(255, 238, 88, 0.35);
      color: #FFF59D;
    }}
    .tag.pink {{
      background: rgba(233, 30, 99, 0.12);
      border-color: rgba(233, 30, 99, 0.35);
      color: #FF80AB;
    }}
    .workspace {{
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 24px;
      max-width: 1200px;
      width: 100%;
    }}
    @media (max-width: 900px) {{
      .workspace {{ grid-template-columns: 1fr; }}
    }}
    .card {{
      background: var(--card-bg);
      backdrop-filter: blur(16px);
      border: 1px solid rgba(255, 255, 255, 0.08);
      border-radius: 20px;
      padding: 24px;
      box-shadow: 0 16px 40px rgba(0, 0, 0, 0.5);
      display: flex;
      flex-direction: column;
      align-items: center;
      position: relative;
    }}
    .card h2 {{
      font-size: 1.15rem;
      color: #FFF59D;
      margin-bottom: 16px;
      display: flex;
      align-items: center;
      gap: 8px;
      align-self: flex-start;
    }}
    .canvas-container {{
      position: relative;
      width: 320px;
      height: 360px;
      background: radial-gradient(circle at 50% 50%, #15102A 0%, #080A14 80%);
      border: 2px solid rgba(0, 229, 255, 0.25);
      border-radius: 18px;
      display: flex;
      align-items: center;
      justify-content: center;
      box-shadow: inset 0 0 40px rgba(0, 0, 0, 0.8), 0 8px 24px rgba(0, 229, 255, 0.15);
      overflow: hidden;
    }}
    canvas {{
      image-rendering: auto;
    }}
    .controls {{
      margin-top: 18px;
      width: 100%;
      display: flex;
      flex-direction: column;
      gap: 12px;
    }}
    .control-row {{
      display: flex;
      justify-content: space-between;
      align-items: center;
      font-size: 0.88rem;
    }}
    input[type=range] {{
      accent-color: #00E5FF;
      width: 160px;
    }}
    .btn-row {{
      display: flex;
      gap: 10px;
      margin-top: 8px;
    }}
    button {{
      background: linear-gradient(135deg, #00E5FF, #0288D1);
      color: #051329;
      font-weight: 700;
      border: none;
      padding: 8px 16px;
      border-radius: 8px;
      cursor: pointer;
      transition: all 0.2s ease;
      font-size: 0.85rem;
    }}
    button:hover {{
      transform: translateY(-2px);
      box-shadow: 0 4px 12px rgba(0, 229, 255, 0.4);
    }}
    .info-panel {{
      width: 100%;
      display: flex;
      flex-direction: column;
      gap: 14px;
      font-size: 0.9rem;
      line-height: 1.5;
    }}
    .info-box {{
      background: rgba(0, 0, 0, 0.3);
      border: 1px solid rgba(255, 255, 255, 0.06);
      border-radius: 12px;
      padding: 14px;
    }}
    .info-box h3 {{
      font-size: 0.95rem;
      color: #80D8FF;
      margin-bottom: 6px;
    }}
    .palette-grid {{
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(130px, 1fr));
      gap: 8px;
      margin-top: 8px;
    }}
    .color-chip {{
      display: flex;
      align-items: center;
      gap: 8px;
      background: rgba(255, 255, 255, 0.03);
      padding: 4px 8px;
      border-radius: 6px;
      font-size: 0.75rem;
    }}
    .swatch {{
      width: 18px;
      height: 18px;
      border-radius: 4px;
      border: 1px solid rgba(255, 255, 255, 0.3);
      flex-shrink: 0;
    }}
    .spec-item {{
      margin-bottom: 6px;
    }}
    .spec-item strong {{
      color: #FFF59D;
    }}
  </style>
</head>
<body>
  <header>
    <h1>COSMOG ĐÁM MÂY TINH VÂN VŨ TRỤ</h1>
    <p class="subtitle">Session 2 - Agent 4 | 3D Pop Mart Vinyl & Micro-Physics Engine | 100% Fidelity to 09_Mythic_Cosmog_Nebula_Baby.png</p>
    <div class="tags">
      <span class="tag">Psychic / Cosmic Nebula</span>
      <span class="tag gold">Imperial Golden Rings</span>
      <span class="tag pink">Squash & Stretch 5%</span>
      <span class="tag">Lag 80ms Twin Puffs</span>
      <span class="tag gold">ST7789 16-bit RGB565 Ready</span>
    </div>
  </header>

  <div class="workspace">
    <!-- LEFT: 60 FPS INTERACTIVE VIEWPORT -->
    <div class="card">
      <h2>✨ 60 FPS Canvas Viewport</h2>
      <div class="canvas-container">
        <canvas id="cosmogCanvas" width="320" height="360"></canvas>
      </div>

      <div class="controls">
        <div class="control-row">
          <span>Tốc độ chuyển động:</span>
          <input type="range" id="speedSlider" min="0.2" max="2.5" step="0.1" value="1.0">
          <span id="speedVal">1.0x</span>
        </div>
        <div class="control-row">
          <span>Kích thước (Scale):</span>
          <input type="range" id="scaleSlider" min="0.8" max="2.2" step="0.05" value="1.55">
          <span id="scaleVal">1.55x</span>
        </div>
        <div class="btn-row">
          <button id="btnBlink">Chớp mắt (Blink)</button>
          <button id="btnFreeze">Tạm dừng (Pause)</button>
          <button id="btnReset">Mặc định (Reset)</button>
        </div>
      </div>
    </div>

    <!-- RIGHT: 3D ANATOMY & PHYSICAL DETAILS -->
    <div class="card">
      <h2>🔭 Thông Số Tạo Hình 3D & Vi Vật Lý</h2>
      <div class="info-panel">
        <div class="info-box">
          <h3>🌌 Tạo Hình Đám Mây Tinh Vân (Nebula Cloud)</h3>
          <p class="spec-item"><strong>Thân:</strong> Đa thùy bồng bềnh chuyển sắc từ chàm tím vi lượng (#1A103C, #4A148C) ở đỉnh sang hồng cánh sen (#D81B60, #E91E63) và magenta dạ quang ở đáy.</p>
          <p class="spec-item"><strong>Búi mây đỉnh:</strong> Hai cuống lam thẫm vươn cao với hai búi mây xanh lơ cyan điện tử (#00E5FF) đính bụi sao kim cương phát quang 4 cánh.</p>
          <p class="spec-item"><strong>Đĩa vàng khuyết:</strong> Vòng đai hoàng kim vương giả ôm quanh thân nghiêng 38 độ (sừng trên góc 1h, sừng dưới góc 7h).</p>
        </div>

        <div class="info-box">
          <h3>✨ Chi Tiết Khuôn Mặt & Ánh Sáng</h3>
          <p class="spec-item"><strong>Mặt nạ:</strong> Đám mây đen tuyền 5 thùy sắc nét chất liệu đá obsidian matte vinyl.</p>
          <p class="spec-item"><strong>Mắt hổ phách:</strong> 3 Điểm bắt sáng pha lê vật lý (Keylight 2x2 #FFFFFF góc 10h, Caustic bounce #FFF9C4 góc 4h, Micro-sparkle góc 1h).</p>
          <p class="spec-item"><strong>Đôi má:</strong> Đốm tròn ngọc lam phát quang (#00E5FF) kèm má hồng phấn bẽn lẽn (#F472B6) ngọt ngào.</p>
          <p class="spec-item"><strong>Hào quang đáy:</strong> Vầng tinh vân mờ ảo dịu dàng nâng đỡ thay cho bóng sàn cứng.</p>
        </div>

        <div class="info-box">
          <h3>🎨 Bảng Màu 16-bit RGB565 Trích Lọc</h3>
          <div class="palette-grid">
            <div class="color-chip"><div class="swatch" style="background:#00E5FF"></div><div><strong>0x073F</strong><br>#00E5FF</div></div>
            <div class="color-chip"><div class="swatch" style="background:#FFEE58"></div><div><strong>0xFF6B</strong><br>#FFEE58</div></div>
            <div class="color-chip"><div class="swatch" style="background:#E91E63"></div><div><strong>0xE8EC</strong><br>#E91E63</div></div>
            <div class="color-chip"><div class="swatch" style="background:#1A103C"></div><div><strong>0x1887</strong><br>#1A103C</div></div>
            <div class="color-chip"><div class="swatch" style="background:#FFCA28"></div><div><strong>0xFE45</strong><br>#FFCA28</div></div>
            <div class="color-chip"><div class="swatch" style="background:#F472B6"></div><div><strong>0xF396</strong><br>#F472B6</div></div>
          </div>
        </div>
      </div>
    </div>
  </div>

  <script>
    // JS IMPLEMENTATION
    {js_canvas_code}

    // Interactive Loop
    const canvas = document.getElementById('cosmogCanvas');
    const ctx = canvas.getContext('2d');
    let speed = 1.0;
    let scale = 1.55;
    let isPaused = false;
    let forceBlinkTime = 0;

    const speedSlider = document.getElementById('speedSlider');
    const scaleSlider = document.getElementById('scaleSlider');
    const speedVal = document.getElementById('speedVal');
    const scaleVal = document.getElementById('scaleVal');
    const btnBlink = document.getElementById('btnBlink');
    const btnFreeze = document.getElementById('btnFreeze');
    const btnReset = document.getElementById('btnReset');

    speedSlider.addEventListener('input', (e) => {{
      speed = parseFloat(e.target.value);
      speedVal.textContent = speed.toFixed(1) + 'x';
    }});

    scaleSlider.addEventListener('input', (e) => {{
      scale = parseFloat(e.target.value);
      scaleVal.textContent = scale.toFixed(2) + 'x';
    }});

    btnBlink.addEventListener('click', () => {{
      forceBlinkTime = performance.now() / 1000;
    }});

    btnFreeze.addEventListener('click', () => {{
      isPaused = !isPaused;
      btnFreeze.textContent = isPaused ? 'Tiếp tục (Play)' : 'Tạm dừng (Pause)';
    }});

    btnReset.addEventListener('click', () => {{
      speed = 1.0; scale = 1.55; isPaused = false;
      speedSlider.value = 1.0; speedVal.textContent = '1.0x';
      scaleSlider.value = 1.55; scaleVal.textContent = '1.55x';
      btnFreeze.textContent = 'Tạm dừng (Pause)';
    }});

    let simulatedTime = 0;
    let lastStamp = performance.now();

    function renderLoop(stamp) {{
      const delta = (stamp - lastStamp) / 1000;
      lastStamp = stamp;

      if (!isPaused) {{
        simulatedTime += delta * speed;
      }}

      // Clear canvas
      ctx.clearRect(0, 0, canvas.width, canvas.height);

      // Draw Cosmog
      let renderTime = simulatedTime;
      if (forceBlinkTime > 0 && (stamp / 1000 - forceBlinkTime) < 0.25) {{
        // force blink
        renderTime = 0.05; // blink condition
      }}

      drawCosmogNebulaBaby(ctx, canvas.width / 2, canvas.height / 2, scale, renderTime);

      requestAnimationFrame(renderLoop);
    }}

    requestAnimationFrame(renderLoop);
  </script>
</body>
</html>
"""

out_preview_path1 = os.path.join(base_dir, "data", "session2_agent4_cosmog_preview.html")
out_preview_path2 = os.path.join(base_dir, "test", "preview_cosmog.html")

os.makedirs(os.path.dirname(out_preview_path2), exist_ok=True)

with open(out_preview_path1, "w", encoding="utf-8") as f:
    f.write(html_content)

with open(out_preview_path2, "w", encoding="utf-8") as f:
    f.write(html_content)

print(f"Generated Cosmog preview HTML (data): {out_preview_path1}")
print(f"Generated Cosmog preview HTML (test): {out_preview_path2}")
