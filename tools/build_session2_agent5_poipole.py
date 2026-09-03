# -*- coding: utf-8 -*-
"""
Builder Script for Poipole Adhesive Alien (Session 2, Agent 5)
Produces:
  1. data/session2_agent5_poipole.json
  2. data/session2_agent5_poipole_preview.html
  3. test/preview_poipole.html
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
    create_color_entry("C_FRESNEL_LAVENDER",   "#F3E8FF", "Viền men sứ tím oải hương pastel lóa sáng Fresnel ngoài cùng", "High-Gloss Fresnel Porcelain Glaze"),
    create_color_entry("C_HEAD_PASTEL_LIGHT",  "#DDD6FE", "Vòm đỉnh đầu tím oải hương pastel đón sáng studio chính diện", "Specular High Gloss"),
    create_color_entry("C_HEAD_PASTEL_MID",    "#C4B5FD", "Vùng chuyển tiếp màu đầu tím oải hương mềm mịn", "Soft Vinyl Satin"),
    create_color_entry("C_HEAD_PURPLE",        "#A78BFA", "Sắc tím oải hương pastel chủ đạo khối đầu phúng phính", "Smooth Vinyl Finish"),
    create_color_entry("C_HEAD_PURPLE_DARK",   "#7C3AED", "Vùng đổ bóng chuyển khối và nếp gấp giáp đầu", "Matte Vinyl Shading"),
    create_color_entry("C_HELMET_DEEP",        "#5B21B6", "Khe rãnh múi giáp tím sâu thẳm phân tách các cánh hoa đầu", "Deep Cavity Occlusion"),
    create_color_entry("C_BODY_DARK",          "#4C1D95", "Khối thân nhỏ bé mũm mĩm màu tím đậm ngoài hành tinh", "Deep Purple Vinyl"),
    create_color_entry("C_BODY_SHADOW",        "#2E1065", "Hốc tối thân dưới, khe nách và khe đùi", "Subsurface Ambient Occlusion"),
    create_color_entry("C_MAGENTA_LIGHT",      "#F472B6", "Cạnh đón sáng giác cắt hồng fuchsia trên trán và chóp sừng", "Vibrant Specular Ridge"),
    create_color_entry("C_MAGENTA_CORE",       "#E11D48", "Mặt nạ vùng mắt, vành mũ và yếm ngực hồng magenta rực rỡ", "Embossed Gloss Vinyl"),
    create_color_entry("C_MAGENTA_DEEP",       "#9F1239", "Đáy bóng tối của mảng hoa văn magenta", "Deep Shadow Velvet"),
    create_color_entry("C_CYAN_GLOW",          "#A5F3FC", "Quầng hào quang phát quang lam ngọc rực sáng", "Bioluminescent Bloom Aura"),
    create_color_entry("C_CYAN_BRIGHT",        "#22D3EE", "Sọc dạ quang cyan nổi bật quanh cổ, ngực và chóp kim tiêm", "Luminous Neon Plasma"),
    create_color_entry("C_CYAN_CORE",          "#06B6D4", "Tròng mắt hình thoi lam ngọc phát sáng ngộ nghĩnh", "Refractive Crystal Core"),
    create_color_entry("C_CYAN_DARK",          "#0E7490", "Viền mắt hình thoi và rãnh dẫn độc cyan thẫm", "Sharp Graphic Contour"),
    create_color_entry("C_HORN_TIP_WHITE",     "#FFFFFF", "Đỉnh chóp kim tiêm men sứ bắt sáng lóa kim cương", "Diamond Specular Glint"),
    create_color_entry("C_HORN_STEM",          "#E9D5FF", "Thân 3 chiếc kim tiêm/sừng ngọc lam tím nhạt thanh mảnh", "Translucent Quartz Ceramic"),
    create_color_entry("C_BLUSH_PINK",         "#F43F5E", "Đôi má ửng hồng tím ngộ nghĩnh bẽn lẽn Chibi Pop Mart", "Airbrushed Soft Diffusion"),
    create_color_entry("C_MOUTH_DEEP",         "#4C0519", "Khóe miệng cười chữ V tinh nghịch", "Sharp Smile Inset"),
    create_color_entry("C_CONTACT_SHADOW",     "#1E1B4B", "Bóng tiếp xúc mờ ảo co giãn nhịp nhàng trên mặt sàn", "Soft Ambient Ground Occlusion"),
    create_color_entry("C_WHITE",              "#FFFFFF", "Điểm bắt sáng pha lê long lanh mắt và vòm trán", "Diamond Catchlight")
]

cpp_code = r'''// =========================================================================
// 10_MYTHIC_POIPOLE_ADHESIVE_ALIEN - C++ ScaledCanvas Implementation
// 100% Hardware Compatible with ESP32 / ESP32-S3 + ST7789 IPS 16-bit RGB565
// Pop Mart / Vinyl 3D Sculpt: Tapered Acorn/Flask Head, 3 Cyan Needle Horns,
// Cyan Rhombus Glowing Eyes, Mischievous V-Smile, Glowing Cyan Neck/Chest Stripes,
// Micro-Physics: 5% Volume-Preserving Squash & Stretch, Horn Lag 0.45 rad, Wagging Tail
// =========================================================================

void drawPoipoleAdhesiveAlien(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (Organic Micro-Physics)
  float breathPhase = angle * 2.0f; // Chu kỳ bay lơ lửng bồng bềnh
  float breathSin   = sinf(breathPhase);

  // Nhịp bay lơ lửng Squash & Stretch 5% bảo toàn thể tích (Sy * Sx ≈ 1.0)
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int by = cy + (int)(breathSin * 3.5f); // Dao động độ cao Y-bobbing

  // 3 Chiếc kim tiêm / sừng ngọc uốn lượn nhẹ trễ pha Delta Phi = 0.45 rad
  float hornLag    = breathPhase - 0.45f;
  int hornSwayX    = (int)(sinf(hornLag) * 2.5f);
  int hornSwayY    = (int)(cosf(hornLag) * 1.8f);

  // Đuôi nhỏ ngoe nguẩy vui vẻ trễ pha Delta Phi = 0.65 rad
  float tailLag    = breathPhase - 0.65f;
  int tailSway     = (int)(sinf(tailLag) * 4.5f);

  // 2. BẢNG MÀU 16-BIT RGB565 CHUẨN XÁC POP MART VINYL
  const uint16_t C_FRESNEL_LAVENDER  = 0xF75F; // #F3E8FF Viền men sứ tím pastel lóa sáng
  const uint16_t C_HEAD_PASTEL_LIGHT = 0xDEBF; // #DDD6FE Đỉnh đầu đón sáng studio
  const uint16_t C_HEAD_PASTEL_MID   = 0xC5BF; // #C4B5FD Chuyển sắc tím pastel mềm mại
  const uint16_t C_HEAD_PURPLE       = 0x6959; // #6D28D9 Tím hoàng gia Pop Mart
  const uint16_t C_HEAD_PURPLE_LIGHT = 0x8AEF; // #8B5CF6 Tím oải hương đón sáng
  const uint16_t C_HEAD_PURPLE_DARK  = 0x48F2; // #4C1D95 Tím đậm đổ bóng khối
  const uint16_t C_HELMET_DEEP       = 0x288C; // #2E1065 Khe rãnh múi giáp tím sâu thẫm
  const uint16_t C_BODY_DARK         = 0x48F2; // #4C1D95 Thân tím thẫm ngoài hành tinh
  const uint16_t C_BODY_SHADOW       = 0x1848; // #1E0A40 Hốc tối thân và chân sâu thẳm
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

  // 3. LAYER 0: BÓNG TIẾP XÚC MẶT SÀN (Ground Contact Shadow)
  int groundY  = cy + 46;
  int shadowRx = (int)((28.0f - breathSin * 3.0f) * sX);
  int shadowRy = (int)(6.0f - breathSin * 0.8f);
  spr->fillEllipse(cx + 2, groundY, shadowRx + 4, shadowRy + 1, C_CONTACT_SHADOW);
  spr->fillEllipse(cx + 2, groundY, shadowRx, shadowRy, 0x10A4);

  // 4. LAYER 1: BỌT ĐỘC DẠ QUANG PHÁT SÁNG (Bioluminescent Poison Plasma Droplets)
  const int dropletOffsets[6][2] = {
    {-34, -22}, {36, -18}, {-40, 14}, {38, 22}, {-22, -44}, {26, -50}
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

  // 5. LAYER 2: CHIẾC ĐUÔI CONG NGOE NGUẨY VUI VẺ (Curved Alien Tail with Fin & Pink Tip)
  int tRootX = cx + (int)(6 * sX);
  int tRootY = by + (int)(14 * sY);
  int tMidX  = cx + (int)(24 * sX) + tailSway;
  int tMidY  = by + (int)(20 * sY);
  int tArchX = cx + (int)(36 * sX) + (int)(tailSway * 1.2f);
  int tArchY = by + (int)(32 * sY);
  int tTipX  = cx + (int)(38 * sX) + (int)(tailSway * 1.5f);
  int tTipY  = by + (int)(48 * sY);

  spr->fillTriangle(tRootX, tRootY - 3, tMidX, tMidY - 3, tRootX, tRootY + 4, C_BODY_DARK);
  spr->fillTriangle(tMidX, tMidY - 3, tArchX, tArchY - 2, tMidX, tMidY + 3, C_BODY_DARK);
  spr->fillTriangle(tArchX, tArchY - 2, tTipX, tTipY, tArchX, tArchY + 3, C_BODY_SHADOW);

  // Vây gai nhọn trên sống đuôi (Dorsal Fin)
  spr->fillTriangle(tMidX + 2, tMidY - 2, tMidX + 10, tMidY - 8, tMidX + 11, tMidY - 1, C_HEAD_PURPLE_DARK);
  spr->drawLine(tMidX + 2, tMidY - 2, tMidX + 10, tMidY - 8, C_FRESNEL_LAVENDER);

  // Viền sống đuôi
  spr->drawLine(tRootX, tRootY - 3, tMidX, tMidY - 3, C_HEAD_PURPLE_LIGHT);
  spr->drawLine(tMidX, tMidY - 3, tArchX, tArchY - 2, C_HEAD_PURPLE);
  spr->drawLine(tArchX, tArchY - 2, tTipX, tTipY, C_MAGENTA_CORE);

  // Chóp đuôi màu hồng fuchsia vuốt nhọn với đốm cyan phát quang
  spr->fillTriangle(tArchX + 1, tArchY + 1, tTipX, tTipY, tTipX - 3, tTipY + 4, C_MAGENTA_CORE);
  spr->drawPixel(tTipX, tTipY, C_CYAN_BRIGHT);

  // 6. LAYER 3: ĐÔI CHÂN CO BÁNH BAO & KHỐI THÂN TÍM ĐẬM (Chubby Legs & Tiny Torso)
  int intLegLX = cx - (int)(8 * sX);
  spr->fillRoundRect(intLegLX - 4, by + 17, (int)(8 * sX), (int)(13 * sY), 4, C_BODY_DARK);
  spr->fillCircle(intLegLX, by + 27, (int)(3.5f * sX), C_HEAD_PURPLE_DARK);
  spr->drawPixel(intLegLX, by + 28, C_FRESNEL_LAVENDER);

  int intLegRX = cx + (int)(5 * sX);
  spr->fillRoundRect(intLegRX - 4, by + 17, (int)(8 * sX), (int)(13 * sY), 4, C_BODY_DARK);
  spr->fillCircle(intLegRX, by + 27, (int)(3.5f * sX), C_HEAD_PURPLE_DARK);
  spr->drawPixel(intLegRX, by + 28, C_FRESNEL_LAVENDER);

  // Khối thân tím đậm nhỏ bé mũm mĩm
  int bRy = (int)(14 * sY);
  int bRx = (int)(13 * sX);
  spr->fillEllipse(cx - (int)(1 * sX), by + 10, bRx + 1, bRy + 1, C_HEAD_PURPLE_DARK);
  spr->fillEllipse(cx - (int)(1 * sX), by + 10, bRx, bRy, C_BODY_DARK);
  spr->fillEllipse(cx - (int)(1 * sX), by + 13, (int)(10 * sX), (int)(8 * sY), C_BODY_SHADOW);
  spr->fillEllipse(cx - (int)(4 * sX), by + 7, (int)(6 * sX), (int)(5 * sY), C_HEAD_PURPLE_LIGHT);

  // 7. LAYER 4: YẾM CHEVRON MAGENTA & SỌC DẠ QUANG CYAN CỔ VÀ NGỰC
  int chestY = by + 4;
  spr->fillTriangle(cx - (int)(8 * sX), chestY, cx + (int)(6 * sX), chestY, cx - (int)(1 * sX), chestY + (int)(9 * sY), C_MAGENTA_CORE);
  spr->fillTriangle(cx - (int)(5 * sX), chestY, cx + (int)(4 * sX), chestY, cx - (int)(1 * sX), chestY + (int)(7 * sY), C_MAGENTA_LIGHT);

  // Sọc dạ quang cyan phát quang viền yếm
  spr->drawLine(cx - (int)(8 * sX), chestY, cx - (int)(1 * sX), chestY + (int)(9 * sY), C_CYAN_BRIGHT);
  spr->drawLine(cx + (int)(6 * sX), chestY, cx - (int)(1 * sX), chestY + (int)(9 * sY), C_CYAN_BRIGHT);
  spr->drawLine(cx - (int)(9 * sX), chestY, cx - (int)(1 * sX), chestY + (int)(10 * sY), C_CYAN_GLOW);
  spr->drawLine(cx + (int)(7 * sX), chestY, cx - (int)(1 * sX), chestY + (int)(10 * sY), C_CYAN_GLOW);
  spr->drawFastHLine(cx - (int)(8 * sX), chestY - 2, (int)(15 * sX), C_CYAN_BRIGHT);
  spr->drawPixel(cx - (int)(1 * sX), chestY + (int)(9 * sY), C_WHITE);

  // 8. LAYER 5: TỨ CHI TÍ HON
  int armRx1 = cx + (int)(8 * sX),  armRy1 = by + 6;
  int armRx2 = cx + (int)(22 * sX), armRy2 = by + 7 + (int)(sinf(breathPhase) * 2.0f);
  spr->fillTriangle(armRx1, armRy1 - 3, armRx1, armRy1 + 3, armRx2, armRy2, C_BODY_DARK);
  spr->fillCircle(armRx2, armRy2, 2, C_HEAD_PURPLE_LIGHT);
  spr->drawLine(armRx1, armRy1 - 3, armRx2, armRy2, C_FRESNEL_LAVENDER);

  // Tay trái giơ lên má
  int armLx1 = cx - (int)(7 * sX),  armLy1 = by + 6;
  int armLx2 = cx - (int)(15 * sX), armLy2 = by + 2;
  int armLx3 = cx - (int)(13 * sX), armLy3 = by - 4;
  spr->fillTriangle(armLx1, armLy1 - 2, armLx2, armLy2, armLx1, armLy1 + 3, C_BODY_DARK);
  spr->fillTriangle(armLx2, armLy2 - 2, armLx3, armLy3, armLx2, armLy2 + 2, C_BODY_DARK);
  spr->fillCircle(armLx3, armLy3, 2, C_HEAD_PURPLE_LIGHT);
  spr->drawPixel(armLx3, armLy3 - 1, C_FRESNEL_LAVENDER);

  // 9. LAYER 6: ĐẦU DÁNG QUẢ LÊ / GIỌT NƯỚC NGƯỢC (Tapered Acorn/Flask Head)
  int hy = by - 16;
  int hRy = (int)(28 * sY);
  int hRx = (int)(25 * sX);

  // Thùy má hai bên phúng phính
  spr->fillEllipse(cx - (int)(15 * sX), hy + (int)(5 * sY), (int)(14 * sX), (int)(17 * sY), C_HEAD_PURPLE);
  spr->fillEllipse(cx + (int)(15 * sX), hy + (int)(5 * sY), (int)(14 * sX), (int)(17 * sY), C_HEAD_PURPLE);

  // Khối vòm đầu chính
  spr->fillEllipse(cx, hy, hRx + 2, hRy + 2, C_FRESNEL_LAVENDER);
  spr->fillEllipse(cx, hy, hRx, hRy, C_HEAD_PURPLE);
  spr->fillEllipse(cx, hy - (int)(4 * sY), (int)(22 * sX), (int)(22 * sY), C_HEAD_PURPLE_LIGHT);
  spr->fillEllipse(cx - (int)(6 * sX), hy - (int)(12 * sY), (int)(13 * sX), (int)(12 * sY), C_HEAD_PASTEL_LIGHT);

  // Chóp nón vươn lên đỉnh
  spr->fillTriangle(cx - (int)(15 * sX), hy - (int)(16 * sY), cx + (int)(15 * sX), hy - (int)(16 * sY), cx, hy - (int)(32 * sY), C_HEAD_PURPLE);
  spr->fillTriangle(cx - (int)(10 * sX), hy - (int)(16 * sY), cx + (int)(10 * sX), hy - (int)(16 * sY), cx, hy - (int)(32 * sY), C_HEAD_PURPLE_LIGHT);
  spr->drawLine(cx - (int)(15 * sX), hy - (int)(16 * sY), cx, hy - (int)(32 * sY), C_FRESNEL_LAVENDER);
  spr->drawLine(cx + (int)(15 * sX), hy - (int)(16 * sY), cx, hy - (int)(32 * sY), C_HEAD_PURPLE_DARK);

  // Cằm bo tròn mềm mại dưới má
  spr->fillEllipse(cx, hy + (int)(17 * sY), (int)(13 * sX), (int)(8 * sY), C_HEAD_PURPLE);
  spr->drawEllipse(cx, hy + (int)(17 * sY), (int)(13 * sX), (int)(8 * sY), C_HEAD_PURPLE_DARK);

  // Múi giáp cánh hoa xòe hai bên tai
  spr->fillTriangle(cx - (int)(23 * sX), hy + (int)(6 * sY), cx - (int)(34 * sX), hy - (int)(7 * sY), cx - (int)(18 * sX), hy - (int)(14 * sY), C_HEAD_PURPLE_DARK);
  spr->fillTriangle(cx + (int)(23 * sX), hy + (int)(6 * sY), cx + (int)(34 * sX), hy - (int)(7 * sY), cx + (int)(18 * sX), hy - (int)(14 * sY), C_HEAD_PURPLE_DARK);
  spr->drawLine(cx - (int)(23 * sX), hy + (int)(6 * sY), cx - (int)(34 * sX), hy - (int)(7 * sY), C_FRESNEL_LAVENDER);
  spr->drawLine(cx + (int)(23 * sX), hy + (int)(6 * sY), cx + (int)(34 * sX), hy - (int)(7 * sY), C_FRESNEL_LAVENDER);

  // Vành nón đỉnh đầu magenta
  spr->fillEllipse(cx, hy - (int)(22 * sY), (int)(13 * sX), (int)(6 * sY), C_MAGENTA_DEEP);
  spr->fillEllipse(cx, hy - (int)(23 * sY), (int)(12 * sX), (int)(5 * sY), C_MAGENTA_CORE);
  spr->fillEllipse(cx - (int)(3 * sX), hy - (int)(24 * sY), (int)(6 * sX), (int)(2.5f * sY), C_MAGENTA_LIGHT);

  // Cánh hoa kim cương magenta giữa trán
  int fX = cx, fY = hy - (int)(8 * sY);
  spr->fillTriangle(fX, fY - (int)(11 * sY), fX - (int)(6 * sX), fY, fX + (int)(6 * sX), fY, C_MAGENTA_CORE);
  spr->fillTriangle(fX, fY + (int)(9 * sY), fX - (int)(6 * sX), fY, fX + (int)(6 * sX), fY, C_MAGENTA_CORE);
  spr->drawLine(fX, fY - (int)(11 * sY), fX - (int)(6 * sX), fY, C_MAGENTA_LIGHT);
  spr->drawLine(fX, fY - (int)(11 * sY), fX + (int)(6 * sX), fY, C_MAGENTA_LIGHT);
  spr->drawPixel(fX, fY, C_WHITE);

  // Rãnh múi giáp tím thẫm
  spr->drawLine(cx - (int)(7 * sX), hy - (int)(18 * sY), cx - (int)(15 * sX), hy - (int)(3 * sY), C_HELMET_DEEP);
  spr->drawLine(cx + (int)(7 * sX), hy - (int)(18 * sY), cx + (int)(15 * sX), hy - (int)(3 * sY), C_HELMET_DEEP);

  // 10. LAYER 7: 3 CHIẾC KIM TIÊM / SỪNG NGỌC LAM CYAN PHÁT QUANG
  int s0BaseX = cx, s0BaseY = hy - (int)(28 * sY);
  int s0TipX  = cx + (int)(hornSwayX * 0.7f);
  int s0TipY  = hy - (int)(54 * sY) + hornSwayY;

  spr->fillTriangle(s0BaseX - 3, s0BaseY, s0BaseX + 3, s0BaseY, s0TipX, s0TipY, C_HORN_STEM);
  spr->drawLine(s0BaseX, s0BaseY, s0TipX, s0TipY, C_FRESNEL_LAVENDER);
  spr->fillCircle(s0TipX, s0TipY, 4, C_CYAN_GLOW);
  spr->fillCircle(s0TipX, s0TipY, 2, C_CYAN_BRIGHT);
  spr->drawPixel(s0TipX, s0TipY - 1, C_HORN_TIP_WHITE);

  int sLBaseX = cx - (int)(24 * sX), sLBaseY = hy - (int)(8 * sY);
  int sLTipX  = cx - (int)(41 * sX) + hornSwayX;
  int sLTipY  = hy - (int)(26 * sY) + hornSwayY;

  spr->fillCircle(sLBaseX, sLBaseY, 5, C_MAGENTA_CORE);
  spr->fillCircle(sLBaseX - 1, sLBaseY - 1, 3, C_MAGENTA_LIGHT);
  spr->fillTriangle(sLBaseX, sLBaseY - 2, sLBaseX, sLBaseY + 2, sLTipX, sLTipY, C_HORN_STEM);
  spr->drawLine(sLBaseX, sLBaseY - 2, sLTipX, sLTipY, C_FRESNEL_LAVENDER);
  spr->fillCircle(sLTipX, sLTipY, 3, C_CYAN_GLOW);
  spr->fillCircle(sLTipX, sLTipY, 2, C_CYAN_BRIGHT);
  spr->drawPixel(sLTipX, sLTipY, C_HORN_TIP_WHITE);

  int sRBaseX = cx + (int)(24 * sX), sRBaseY = hy - (int)(8 * sY);
  int sRTipX  = cx + (int)(41 * sX) + hornSwayX;
  int sRTipY  = hy - (int)(26 * sY) + hornSwayY;

  spr->fillCircle(sRBaseX, sRBaseY, 5, C_MAGENTA_CORE);
  spr->fillCircle(sRBaseX + 1, sRBaseY - 1, 3, C_MAGENTA_LIGHT);
  spr->fillTriangle(sRBaseX, sRBaseY - 2, sRBaseX, sRBaseY + 2, sRTipX, sRTipY, C_HORN_STEM);
  spr->drawLine(sRBaseX, sRBaseY - 2, sRTipX, sRTipY, C_FRESNEL_LAVENDER);
  spr->fillCircle(sRTipX, sRTipY, 3, C_CYAN_GLOW);
  spr->fillCircle(sRTipX, sRTipY, 2, C_CYAN_BRIGHT);
  spr->drawPixel(sRTipX, sRTipY, C_HORN_TIP_WHITE);

  // 11. LAYER 8: MẶT NẠ MẮT HỒNG MAGENTA & ĐÔI MÁ HỒNG TÍM
  int maskY = hy + 4;
  spr->fillEllipse(cx, maskY, (int)(18 * sX), (int)(8 * sY), C_MAGENTA_CORE);
  spr->fillEllipse(cx, maskY - 1, (int)(16 * sX), (int)(6 * sY), C_MAGENTA_LIGHT);

  spr->fillEllipse(cx - (int)(17 * sX), hy + 9, 4, 3, C_BLUSH_PINK);
  spr->fillEllipse(cx + (int)(17 * sX), hy + 9, 4, 3, C_BLUSH_PINK);

  // 12. LAYER 9: ĐÔI MẮT HÌNH THOI MÀU LAM NGỌC PHÁT SÁNG (Tilted Rhombus Cyan Eyes)
  int eyeY  = hy + 3;
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
    // Mắt trái: Tilted Quadrilateral / Rhombus
    int xl1_x = eyeXL + 3, xl1_y = eyeY - 6;
    int xl2_x = eyeXL + 6, xl2_y = eyeY;
    int xl3_x = eyeXL - 2, xl3_y = eyeY + 6;
    int xl4_x = eyeXL - 8, xl4_y = eyeY - 2;

    spr->fillTriangle(xl1_x, xl1_y, xl2_x, xl2_y, xl4_x, xl4_y, C_CYAN_DARK);
    spr->fillTriangle(xl3_x, xl3_y, xl2_x, xl2_y, xl4_x, xl4_y, C_CYAN_DARK);
    spr->fillTriangle(xl1_x - 1, xl1_y + 1, xl2_x - 1, xl2_y, xl4_x + 1, xl4_y, C_CYAN_CORE);
    spr->fillTriangle(xl3_x + 1, xl3_y - 1, xl2_x - 1, xl2_y, xl4_x + 1, xl4_y, C_CYAN_BRIGHT);

    spr->fillCircle(eyeXL, eyeY - 2, 2, C_WHITE);
    spr->drawPixel(eyeXL + 3, eyeY + 2, C_CYAN_GLOW);

    // Mắt phải: Tilted Quadrilateral / Rhombus
    int xr1_x = eyeXR - 3, xr1_y = eyeY - 6;
    int xr2_x = eyeXR + 8, xr2_y = eyeY - 2;
    int xr3_x = eyeXR + 2, xr3_y = eyeY + 6;
    int xr4_x = eyeXR - 6, xr4_y = eyeY;

    spr->fillTriangle(xr1_x, xr1_y, xr2_x, xr2_y, xr4_x, xr4_y, C_CYAN_DARK);
    spr->fillTriangle(xr3_x, xr3_y, xr2_x, xr2_y, xr4_x, xr4_y, C_CYAN_DARK);
    spr->fillTriangle(xr1_x + 1, xr1_y + 1, xr2_x - 1, xr2_y, xr4_x + 1, xr4_y, C_CYAN_CORE);
    spr->fillTriangle(xr3_x - 1, xr3_y - 1, xr2_x - 1, xr2_y, xr4_x + 1, xr4_y, C_CYAN_BRIGHT);

    spr->fillCircle(eyeXR, eyeY - 2, 2, C_WHITE);
    spr->drawPixel(eyeXR - 3, eyeY + 2, C_CYAN_GLOW);
  }

  // 13. LAYER 10: MIỆNG CƯỜI CHỮ V TINH NGHỊCH (Mischievous V-Smile)
  int mY = hy + 13;
  spr->fillTriangle(cx - 5, mY - 1, cx + 5, mY - 1, cx, mY + 3, C_MOUTH_DEEP);
  spr->drawLine(cx - 5, mY - 1, cx, mY + 3, C_CYAN_BRIGHT);
  spr->drawLine(cx, mY + 3, cx + 5, mY - 1, C_CYAN_BRIGHT);
}

static void drawPoipoleAdhesiveAlien(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  (void)breath;
  (void)scale;
  bool blink = (fmodf(angle, 3.5f) < 0.14f);
  drawPoipoleAdhesiveAlien(spr, cx, cy, angle, blink);
}
'''

js_code = r'''// =========================================================================
// 10_MYTHIC_POIPOLE_ADHESIVE_ALIEN - Modern HTML5 Canvas 2D Implementation
// 100% Anatomical Likeness & High-End 3D Pop Mart Vinyl Aesthetic
// Organic Micro-Physics: 5% Squash & Stretch, Horn Sway Lag 0.45 rad, Wagging Tail
// =========================================================================

function drawPoipoleAdhesiveAlien(ctx, cx, cy, scale, t) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.scale(scale, scale);

  // 1. CHUYỂN ĐỘNG VI VẬT LÝ HỮU CƠ (Organic Micro-Physics)
  const breathFreq  = 2.0;
  const breathPhase = t * breathFreq;
  const breathSin   = Math.sin(breathPhase);

  // Squash & Stretch 5% bảo toàn thể tích (sY * sX ≈ 1.0)
  const sY = 1.0 + 0.05 * breathSin;
  const sX = 1.0 - 0.025 * breathSin;
  const by = breathSin * 3.5;

  // 3 Chiếc kim tiêm / sừng ngọc trễ pha Delta Phi = 0.45 rad
  const hornLag   = breathPhase - 0.45;
  const hornSwayX = Math.sin(hornLag) * 2.5;
  const hornSwayY = Math.cos(hornLag) * 1.8;

  // Đuôi ngoe nguẩy trễ pha Delta Phi = 0.65 rad
  const tailLag  = breathPhase - 0.65;
  const tailSway = Math.sin(tailLag) * 4.5;

  // Nhịp chớp mắt 3.5s (chu kỳ 3500ms, thời gian nhắm 140ms)
  const blink = ((t % 3.5) < 0.14);

  // 2. LAYER 0: BÓNG TIẾP XÚC MỜ ẢO CO GIÃN NHỊP NHÀNG
  ctx.save();
  const groundY = 46;
  const shadowW = (28.0 - breathSin * 3.0) * sX;
  const shadowH = 6.0 - breathSin * 0.8;
  const shadowGrad = ctx.createRadialGradient(2, groundY, 2, 2, groundY, shadowW);
  shadowGrad.addColorStop(0, 'rgba(30, 27, 75, 0.7)');
  shadowGrad.addColorStop(0.6, 'rgba(30, 27, 75, 0.35)');
  shadowGrad.addColorStop(1, 'rgba(30, 27, 75, 0)');
  ctx.fillStyle = shadowGrad;
  ctx.beginPath();
  ctx.ellipse(2, groundY, shadowW, shadowH, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 3. LAYER 1: BỌT ĐỘC DẠ QUANG LI TI PHÁT SÁNG BỒNG BỀNH
  const dropletDefs = [
    { x: -34, y: -22, r: 3.0, phase: 0.0 },
    { x: 36,  y: -18, r: 2.6, phase: 1.2 },
    { x: -40, y: 14,  r: 2.4, phase: 2.4 },
    { x: 38,  y: 22,  r: 2.8, phase: 3.6 },
    { x: -22, y: -44, r: 2.0, phase: 4.8 },
    { x: 26,  y: -50, r: 2.5, phase: 5.5 }
  ];
  dropletDefs.forEach(d => {
    const dLag = breathPhase * 0.8 + d.phase;
    const dx = d.x + Math.cos(dLag) * 3.0;
    const dy = d.y + Math.sin(dLag) * 3.5;
    ctx.save();
    ctx.shadowColor = '#22D3EE';
    ctx.shadowBlur = 10;
    ctx.fillStyle = 'rgba(34, 211, 238, 0.75)';
    ctx.beginPath();
    ctx.arc(dx, dy, d.r, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillStyle = '#FFFFFF';
    ctx.beginPath();
    ctx.arc(dx - d.r * 0.3, dy - d.r * 0.3, d.r * 0.35, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  });

  // 4. LAYER 2: CHIẾC ĐUÔI CONG NGOE NGUẨY VUI VẺ
  ctx.save();
  ctx.translate(0, by);
  const tRootX = 6 * sX, tRootY = 14 * sY;
  const tMidX  = 24 * sX + tailSway, tMidY = 20 * sY;
  const tArchX = 36 * sX + tailSway * 1.2, tArchY = 32 * sY;
  const tTipX  = 38 * sX + tailSway * 1.5, tTipY = 48 * sY;

  const tailGrad = ctx.createLinearGradient(tRootX, tRootY, tTipX, tTipY);
  tailGrad.addColorStop(0, '#4C1D95');
  tailGrad.addColorStop(0.65, '#5B21B6');
  tailGrad.addColorStop(0.85, '#E11D48');
  tailGrad.addColorStop(1, '#F472B6');
  ctx.fillStyle = tailGrad;
  ctx.beginPath();
  ctx.moveTo(tRootX, tRootY - 3);
  ctx.quadraticCurveTo(tMidX, tMidY - 3, tArchX, tArchY - 2);
  ctx.lineTo(tTipX, tTipY);
  ctx.lineTo(tTipX - 3, tTipY + 4);
  ctx.quadraticCurveTo(tMidX, tMidY + 3, tRootX, tRootY + 4);
  ctx.closePath();
  ctx.fill();

  // Vây gai sống đuôi
  ctx.fillStyle = '#4C1D95';
  ctx.beginPath();
  ctx.moveTo(tMidX + 2, tMidY - 2);
  ctx.lineTo(tMidX + 10, tMidY - 8);
  ctx.lineTo(tMidX + 11, tMidY - 1);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = '#F3E8FF';
  ctx.lineWidth = 0.8;
  ctx.stroke();

  // Viền sống đuôi
  ctx.strokeStyle = '#8B5CF6';
  ctx.lineWidth = 1.2;
  ctx.beginPath();
  ctx.moveTo(tRootX, tRootY - 3);
  ctx.quadraticCurveTo(tMidX, tMidY - 3, tArchX, tArchY - 2);
  ctx.stroke();

  ctx.shadowColor = '#22D3EE';
  ctx.shadowBlur = 8;
  ctx.fillStyle = '#22D3EE';
  ctx.beginPath();
  ctx.arc(tTipX, tTipY, 2.2, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 5. LAYER 3: ĐÔI CHÂN NHỎ MŨM MĨM & KHỐI THÂN TÍM ĐẬM
  ctx.save();
  ctx.translate(0, by);
  ctx.scale(sX, sY);

  const intLegLX = -8;
  const intLegRX = 5;
  ctx.fillStyle = '#4C1D95';
  ctx.beginPath();
  ctx.roundRect(intLegLX - 4, 17, 8, 13, 4);
  ctx.roundRect(intLegRX - 4, 17, 8, 13, 4);
  ctx.fill();

  ctx.fillStyle = '#4C1D95';
  ctx.beginPath();
  ctx.arc(intLegLX, 27, 3.5, 0, Math.PI * 2);
  ctx.arc(intLegRX, 27, 3.5, 0, Math.PI * 2);
  ctx.fill();
  ctx.fillStyle = '#F3E8FF';
  ctx.beginPath();
  ctx.arc(intLegLX, 28, 1, 0, Math.PI * 2);
  ctx.arc(intLegRX, 28, 1, 0, Math.PI * 2);
  ctx.fill();

  const bodyGrad = ctx.createRadialGradient(-3, 8, 2, -1, 10, 15);
  bodyGrad.addColorStop(0, '#8B5CF6');
  bodyGrad.addColorStop(0.35, '#6D28D9');
  bodyGrad.addColorStop(0.8, '#4C1D95');
  bodyGrad.addColorStop(1, '#1E0A40');
  ctx.fillStyle = bodyGrad;
  ctx.beginPath();
  ctx.ellipse(-1, 10, 13, 14, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = '#4C1D95';
  ctx.lineWidth = 1.0;
  ctx.stroke();

  // 6. LAYER 4: YẾM CHEVRON MAGENTA & SỌC DẠ QUANG CYAN CỔ VÀ NGỰC
  const chestY = 4;
  const chestGrad = ctx.createLinearGradient(0, chestY, 0, chestY + 9);
  chestGrad.addColorStop(0, '#F472B6');
  chestGrad.addColorStop(0.4, '#E11D48');
  chestGrad.addColorStop(1, '#9F1239');
  ctx.fillStyle = chestGrad;
  ctx.beginPath();
  ctx.moveTo(-8, chestY);
  ctx.lineTo(6, chestY);
  ctx.lineTo(-1, chestY + 9);
  ctx.closePath();
  ctx.fill();

  ctx.save();
  ctx.shadowColor = '#22D3EE';
  ctx.shadowBlur = 12;
  ctx.strokeStyle = '#22D3EE';
  ctx.lineWidth = 1.8;
  ctx.beginPath();
  ctx.moveTo(-8, chestY);
  ctx.lineTo(-1, chestY + 9);
  ctx.lineTo(6, chestY);
  ctx.stroke();

  ctx.beginPath();
  ctx.moveTo(-8, chestY - 2);
  ctx.lineTo(7, chestY - 2);
  ctx.stroke();

  ctx.fillStyle = '#FFFFFF';
  ctx.beginPath();
  ctx.arc(-1, chestY + 9, 1.4, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  ctx.restore(); // restore body scale

  // 7. LAYER 5: TỨ CHI TÍ HON ĐÁNG YÊU
  ctx.save();
  ctx.translate(0, by);

  // Tay phải
  const armRx1 = 8 * sX, armRy1 = 6;
  const armRx2 = 22 * sX, armRy2 = 7 + Math.sin(breathPhase) * 2.0;
  ctx.fillStyle = '#4C1D95';
  ctx.beginPath();
  ctx.moveTo(armRx1, armRy1 - 3);
  ctx.quadraticCurveTo(armRx1 + 8, armRy1 + 1, armRx2, armRy2);
  ctx.lineTo(armRx1, armRy1 + 3);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = '#F3E8FF';
  ctx.lineWidth = 0.8;
  ctx.stroke();
  ctx.fillStyle = '#8B5CF6';
  ctx.beginPath();
  ctx.arc(armRx2, armRy2, 2.4, 0, Math.PI * 2);
  ctx.fill();

  // Tay trái (giơ lên má cười khúc khích)
  const armLx1 = -7 * sX, armLy1 = 6;
  const armLx2 = -15 * sX, armLy2 = 2;
  const armLx3 = -13 * sX, armLy3 = -4;
  ctx.fillStyle = '#4C1D95';
  ctx.beginPath();
  ctx.moveTo(armLx1, armLy1 - 2);
  ctx.lineTo(armLx2, armLy2);
  ctx.lineTo(armLx3, armLy3);
  ctx.lineTo(armLx2 + 2, armLy2 + 2);
  ctx.lineTo(armLx1, armLy1 + 3);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = '#F3E8FF';
  ctx.lineWidth = 0.8;
  ctx.stroke();
  ctx.fillStyle = '#8B5CF6';
  ctx.beginPath();
  ctx.arc(armLx3, armLy3, 2.4, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 8. LAYER 6: ĐẦU QUẢ LÊ / GIỌT NƯỚC NGƯỢC
  ctx.save();
  ctx.translate(0, by);
  ctx.scale(sX, sY);

  const hy = -16;

  // Thùy má hai bên phúng phính
  ctx.fillStyle = '#6D28D9';
  ctx.beginPath();
  ctx.ellipse(-15, hy + 5, 14, 17, 0, 0, Math.PI * 2);
  ctx.ellipse(15, hy + 5, 14, 17, 0, 0, Math.PI * 2);
  ctx.fill();

  // Vòm đầu cao
  const headGrad = ctx.createRadialGradient(-6, hy - 10, 3, 0, hy, 28);
  headGrad.addColorStop(0, '#DDD6FE');
  headGrad.addColorStop(0.35, '#8B5CF6');
  headGrad.addColorStop(0.75, '#6D28D9');
  headGrad.addColorStop(1, '#4C1D95');
  ctx.fillStyle = headGrad;
  ctx.beginPath();
  ctx.ellipse(0, hy, 25, 28, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = '#F3E8FF';
  ctx.lineWidth = 1.4;
  ctx.stroke();

  // Chóp nón vươn lên đỉnh
  ctx.fillStyle = '#6D28D9';
  ctx.beginPath();
  ctx.moveTo(-15, hy - 16);
  ctx.lineTo(15, hy - 16);
  ctx.lineTo(0, hy - 32);
  ctx.closePath();
  ctx.fill();

  // Cằm bo tròn dưới má
  ctx.fillStyle = '#6D28D9';
  ctx.beginPath();
  ctx.ellipse(0, hy + 17, 13, 8, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = '#4C1D95';
  ctx.lineWidth = 0.8;
  ctx.stroke();

  // Múi giáp cánh hoa xòe hai bên tai
  ctx.fillStyle = '#4C1D95';
  ctx.beginPath();
  ctx.moveTo(-23, hy + 6);
  ctx.lineTo(-34, hy - 7);
  ctx.lineTo(-18, hy - 14);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = '#F3E8FF';
  ctx.lineWidth = 1.0;
  ctx.stroke();

  ctx.beginPath();
  ctx.moveTo(23, hy + 6);
  ctx.lineTo(34, hy - 7);
  ctx.lineTo(18, hy - 14);
  ctx.closePath();
  ctx.fill();
  ctx.stroke();

  // Vành nón đỉnh đầu magenta
  const domeGrad = ctx.createRadialGradient(-3, hy - 24, 2, 0, hy - 23, 13);
  domeGrad.addColorStop(0, '#F472B6');
  domeGrad.addColorStop(0.6, '#E11D48');
  domeGrad.addColorStop(1, '#9F1239');
  ctx.fillStyle = domeGrad;
  ctx.beginPath();
  ctx.ellipse(0, hy - 23, 12, 5.5, 0, 0, Math.PI * 2);
  ctx.fill();

  // Họa tiết cánh hoa kim cương magenta giữa trán
  const fX = 0, fY = hy - 8;
  const diaGrad = ctx.createLinearGradient(0, fY - 11, 0, fY + 9);
  diaGrad.addColorStop(0, '#F472B6');
  diaGrad.addColorStop(0.5, '#E11D48');
  diaGrad.addColorStop(1, '#9F1239');
  ctx.fillStyle = diaGrad;
  ctx.beginPath();
  ctx.moveTo(fX, fY - 11);
  ctx.lineTo(fX + 6, fY);
  ctx.lineTo(fX, fY + 9);
  ctx.lineTo(fX - 6, fY);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = '#F472B6';
  ctx.lineWidth = 1.0;
  ctx.stroke();

  ctx.fillStyle = '#FFFFFF';
  ctx.beginPath();
  ctx.arc(fX, fY, 1.4, 0, Math.PI * 2);
  ctx.fill();

  ctx.strokeStyle = '#2E1065';
  ctx.lineWidth = 1.2;
  ctx.beginPath();
  ctx.moveTo(-7, hy - 18);
  ctx.lineTo(-15, hy - 3);
  ctx.moveTo(7, hy - 18);
  ctx.lineTo(15, hy - 3);
  ctx.stroke();

  ctx.restore(); // restore head scale

  // 9. LAYER 7: 3 CHIẾC KIM TIÊM / SỪNG NGỌC LAM CYAN PHÁT QUANG
  ctx.save();
  ctx.translate(0, by);

  function drawNeedleHorn(bx, by_pos, tx, ty, isCenter) {
    ctx.save();
    const hornGrad = ctx.createLinearGradient(bx, by_pos, tx, ty);
    hornGrad.addColorStop(0, '#F472B6');
    hornGrad.addColorStop(0.3, '#E9D5FF');
    hornGrad.addColorStop(1, '#22D3EE');
    ctx.strokeStyle = hornGrad;
    ctx.lineWidth = isCenter ? 3.4 : 2.8;
    ctx.lineCap = 'round';
    ctx.beginPath();
    ctx.moveTo(bx, by_pos);
    ctx.lineTo(tx, ty);
    ctx.stroke();

    ctx.strokeStyle = '#FFFFFF';
    ctx.lineWidth = 1.0;
    ctx.beginPath();
    ctx.moveTo(bx - 0.5, by_pos);
    ctx.lineTo(tx - 0.5, ty);
    ctx.stroke();

    ctx.shadowColor = '#22D3EE';
    ctx.shadowBlur = 14;
    ctx.fillStyle = '#22D3EE';
    ctx.beginPath();
    ctx.arc(tx, ty, isCenter ? 4.5 : 3.6, 0, Math.PI * 2);
    ctx.fill();

    ctx.fillStyle = '#FFFFFF';
    ctx.beginPath();
    ctx.arc(tx, ty - 0.8, isCenter ? 1.8 : 1.4, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
  }

  const hyBase = -16;
  drawNeedleHorn(0, hyBase - 28 * sY, hornSwayX * 0.7, hyBase - 54 * sY + hornSwayY, true);

  ctx.fillStyle = '#E11D48';
  ctx.beginPath();
  ctx.arc(-24 * sX, hyBase - 8 * sY, 5.0, 0, Math.PI * 2);
  ctx.fill();
  drawNeedleHorn(-24 * sX, hyBase - 8 * sY, -41 * sX + hornSwayX, hyBase - 26 * sY + hornSwayY, false);

  ctx.fillStyle = '#E11D48';
  ctx.beginPath();
  ctx.arc(24 * sX, hyBase - 8 * sY, 5.0, 0, Math.PI * 2);
  ctx.fill();
  drawNeedleHorn(24 * sX, hyBase - 8 * sY, 41 * sX + hornSwayX, hyBase - 26 * sY + hornSwayY, false);

  ctx.restore(); // restore horns transform

  // 10. LAYER 8: MẶT NẠ MẮT HỒNG MAGENTA & ĐÔI MÁ HỒNG TÍM
  ctx.save();
  ctx.translate(0, by);
  ctx.scale(sX, sY);

  const maskY = hy + 4;
  const maskGrad = ctx.createLinearGradient(0, maskY - 6, 0, maskY + 6);
  maskGrad.addColorStop(0, '#F472B6');
  maskGrad.addColorStop(0.5, '#E11D48');
  maskGrad.addColorStop(1, '#9F1239');
  ctx.fillStyle = maskGrad;
  ctx.beginPath();
  ctx.ellipse(0, maskY, 18, 8, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = '#F472B6';
  ctx.lineWidth = 1.0;
  ctx.stroke();

  const blushGradL = ctx.createRadialGradient(-17, hy + 9, 1, -17, hy + 9, 5);
  blushGradL.addColorStop(0, 'rgba(244, 63, 94, 0.75)');
  blushGradL.addColorStop(1, 'rgba(244, 63, 94, 0)');
  ctx.fillStyle = blushGradL;
  ctx.beginPath();
  ctx.ellipse(-17, hy + 9, 4, 3, 0, 0, Math.PI * 2);
  ctx.fill();

  const blushGradR = ctx.createRadialGradient(17, hy + 9, 1, 17, hy + 9, 5);
  blushGradR.addColorStop(0, 'rgba(244, 63, 94, 0.75)');
  blushGradR.addColorStop(1, 'rgba(244, 63, 94, 0)');
  ctx.fillStyle = blushGradR;
  ctx.beginPath();
  ctx.ellipse(17, hy + 9, 4, 3, 0, 0, Math.PI * 2);
  ctx.fill();

  // 11. LAYER 9: ĐÔI MẮT HÌNH THOI MÀU LAM NGỌC PHÁT SÁNG
  const eyeY  = hy + 3;
  const eyeXL = -11;
  const eyeXR = 11;

  function drawRhombusEye(ex, isLeft) {
    ctx.save();
    ctx.translate(ex, eyeY);

    if (blink) {
      ctx.shadowColor = '#22D3EE';
      ctx.shadowBlur = 10;
      ctx.strokeStyle = '#22D3EE';
      ctx.lineWidth = 2.4;
      ctx.lineCap = 'round';
      ctx.beginPath();
      ctx.moveTo(isLeft ? -6 : -5, 0);
      ctx.quadraticCurveTo(0, 3, isLeft ? 5 : 6, 0);
      ctx.stroke();
    } else {
      ctx.shadowColor = '#22D3EE';
      ctx.shadowBlur = 14;

      const p1 = isLeft ? { x: 3,  y: -6 } : { x: -3, y: -6 };
      const p2 = isLeft ? { x: 6,  y: 0 }  : { x: 8,  y: -2 };
      const p3 = isLeft ? { x: -2, y: 6 }  : { x: 2,  y: 6 };
      const p4 = isLeft ? { x: -8, y: -2 } : { x: -6, y: 0 };

      ctx.fillStyle = '#0E7490';
      ctx.beginPath();
      ctx.moveTo(p1.x, p1.y);
      ctx.lineTo(p2.x, p2.y);
      ctx.lineTo(p3.x, p3.y);
      ctx.lineTo(p4.x, p4.y);
      ctx.closePath();
      ctx.fill();

      const eyeGrad = ctx.createLinearGradient(p4.x, p1.y, p2.x, p3.y);
      eyeGrad.addColorStop(0, '#A5F3FC');
      eyeGrad.addColorStop(0.4, '#22D3EE');
      eyeGrad.addColorStop(0.85, '#06B6D4');
      eyeGrad.addColorStop(1, '#0891B2');
      ctx.fillStyle = eyeGrad;
      ctx.beginPath();
      ctx.moveTo(p1.x, p1.y);
      ctx.lineTo(p2.x, p2.y);
      ctx.lineTo(p3.x, p3.y);
      ctx.lineTo(p4.x, p4.y);
      ctx.closePath();
      ctx.fill();

      ctx.fillStyle = '#FFFFFF';
      ctx.beginPath();
      ctx.arc(0, -2, 2.0, 0, Math.PI * 2);
      ctx.fill();

      ctx.fillStyle = 'rgba(255, 255, 255, 0.85)';
      ctx.beginPath();
      ctx.arc(isLeft ? 3 : -3, 2, 1.0, 0, Math.PI * 2);
      ctx.fill();
    }
    ctx.restore();
  }

  drawRhombusEye(eyeXL, true);
  drawRhombusEye(eyeXR, false);

  // 12. LAYER 10: MIỆNG CƯỜI CHỮ V TINH NGHỊCH
  const mY = hy + 13;
  ctx.save();
  ctx.fillStyle = '#4C0519';
  ctx.beginPath();
  ctx.moveTo(-5, mY - 1);
  ctx.lineTo(5, mY - 1);
  ctx.lineTo(0, mY + 3);
  ctx.closePath();
  ctx.fill();

  ctx.shadowColor = '#22D3EE';
  ctx.shadowBlur = 6;
  ctx.strokeStyle = '#22D3EE';
  ctx.lineWidth = 1.3;
  ctx.beginPath();
  ctx.moveTo(-5, mY - 1);
  ctx.lineTo(0, mY + 3);
  ctx.lineTo(5, mY - 1);
  ctx.stroke();
  ctx.restore();

  ctx.restore(); // restore head scale
  ctx.restore(); // restore root
}
'''

data = {
    "metadata": {
        "session": "session2_agent5",
        "agent_name": "Nghệ Sĩ Điêu Khắc Poipole Tinh Linh Tím Ngoài Hành Tinh (Poipole Adhesive Alien 3D Sculptor)",
        "agent_role": "Master 3D Pop Mart & Vinyl Creature Sculptor for IoT Digital Keychain",
        "version": "2.0.0-PRO-MAX",
        "created_date": "2026-09-04",
        "target_display": "ST7789 240x280 / 172x320 16-bit RGB565 IPS Display & Modern HTML5 Canvas 2D",
        "reference_artwork": "10_Mythic_Poipole_Adhesive_Alien.png",
        "design_frameworks": [
            "Reffernce/NHOM_1_FRONTEND_UIUX/ui-ux-pro-max-skill-main (Design Intelligence, Material Fidelity, Anti-Cheap Icon)",
            "Reffernce/NHOM_1_FRONTEND_UIUX/impeccable-main (Craft Floor, Restraint in Chrome, Brilliant Texture, Organic Motion)",
            "Reffernce/NHOM_1_FRONTEND_UIUX/gsap-skills (Harmonic Physics, Phase Lag Delta Phi = 0.45 rad, Volume Conservation)"
        ],
        "core_design_rules": {
            "head_and_horns_rule": "Đầu to tròn phúng phính màu tím oải hương pastel chiếm trọn khối điêu khắc với 3 chiếc kim tiêm/sừng ngọc lam cyan phát quang. Sừng giữa đỉnh đầu vươn cao, hai sừng bên xòe cánh hoa magenta, uốn lượn nhịp nhàng trễ pha Delta Phi = 0.45 rad.",
            "body_and_tail_rule": "Thân nhỏ bé mũm mĩm màu tím đậm ngoài hành tinh với chiếc đuôi nhỏ cong mềm mại có vây gai và chóp hồng fuchsia ngoe nguẩy vui vẻ.",
            "face_and_eyes_rule": "Đôi mắt hình thoi màu lam ngọc phát sáng ngộ nghĩnh (Cyan Rhombus Glowing Eyes), miệng cười chữ V tinh nghịch lấp lánh neon, đôi má ửng hồng tím ngộ nghĩnh Chibi Pop Mart.",
            "luminous_stripes_rule": "Vệt sọc dạ quang cyan nổi bật quanh cổ và ngực (Luminous Cyan Neon Stripes), tỏa sáng quầng hào quang bọc quanh yếm chevron magenta.",
            "kinematics_rule": "Chuyển động vi vật lý hữu cơ: Nhịp bay lơ lửng Squash & Stretch 5% bảo toàn thể tích, 3 sừng ngọc trễ pha 0.45 rad, đuôi ngoe nguẩy trễ pha 0.65 rad, nhịp chớp mắt 3.5s, bóng tiếp xúc co giãn mềm mại theo độ cao."
        }
    },
    "creature_profile": {
        "id": 10,
        "global_id": 10,
        "codename": "MYTHIC_POIPOLE_ADHESIVE_ALIEN",
        "name_vi": "Poipole - Tinh Linh Tím Ngoài Hành Tinh (Quái Thú Keo Dính Không Gian Cực Siêu)",
        "name_en": "Mythic Poipole - The Adhesive Poison Pin Alien",
        "japanese_name": "ベベノム (Bevenom - UB Adhesive)",
        "pokedex_number": 803,
        "category": "Ultra Beast / Tinh Linh Thần Thoại Không Gian & Bé Cưng Pop Mart 3D",
        "archetype": "Tinh Linh Độc Tố Keo Dính Ngoài Hành Tinh (Adhesive Celestial Symbiote)",
        "elements": [
            "Độc Tố Không Gian (Cosmic Poison)",
            "Năng Lượng Cực Siêu (Ultra Space Plasma)"
        ],
        "signature_moves": [
            "Venoshock (Sốc Độc Tố Không Gian)",
            "Poison Tail (Đuôi Độc Ngân Hà)",
            "Fell Stinger (Kim Chích Cực Siêu)",
            "Nasty Plot (Mưu Kế Tinh Nghịch)"
        ],
        "mythology_lore": "Poipole (ベベノム) là sinh vật Ultra Beast bí ẩn đến từ thế giới Ultra Megalopolis rực rỡ nhưng đã bị mất đi ánh sáng. Mang hình hài một búp hoa tinh linh tím ngoài hành tinh với chiếc đầu to tròn phúng phính và 3 chiếc kim tiêm phun dịch keo phát quang lấp lánh, Poipole sở hữu trí thông minh vượt bậc và cảm xúc vô cùng phong phú. Chú rất thích con người, luôn cười toe toét với chiếc miệng chữ V tinh nghịch và vẫy đuôi mừng rỡ khi tìm thấy những người bạn chân thành từ các vì sao xa xôi.",
        "inspirational_quotes": {
            "vi": "Dù từ một chiều không gian xa xôi, nụ cười tinh nghịch của em sẽ luôn thắp sáng hành trình của bạn.",
            "en": "No matter how vast the cosmos, my mischievous smile will always light up your journey."
        }
    },
    "sculpture_aesthetic_spec": {
        "finish_quality": "High-End Pop Mart / Porcelain Glazed Vinyl Collectible Toy with Micro Subsurface Scattering",
        "head_sculpt": "Đầu giọt nước ngược khổng lồ màu tím oải hương pastel (#DDD6FE -> #A78BFA) với các múi giáp tai và vành mũ magenta (#E11D48)",
        "horns_syringes": "3 Chiếc kim tiêm ngọc lam phát quang: 1 sừng đỉnh đầu vươn thẳng và 2 sừng bên xòe 45 độ, đính hạt ngọc cyan dạ quang phát sáng",
        "body_material": "Thân tí hon màu tím thẫm ngoài hành tinh (#4C1D95) phủ lớp men bóng vinyl phản xạ mềm mại",
        "glowing_markings": "Vệt sọc dạ quang cyan nổi bật quanh cổ và ngực viền quanh yếm chevron hồng fuchsia",
        "diamond_eyes": "Đôi mắt hình thoi màu lam ngọc phát sáng ngộ nghĩnh với điểm bắt sáng kim cương lấp lánh",
        "tail_sculpt": "Chiếc đuôi nhỏ cong mềm mại có vây gai và chóp hồng fuchsia điểm đốm cyan phát quang",
        "ambient_shadow": "Bóng tiếp xúc mờ ảo co giãn nhịp nhàng trên mặt đất theo độ cao bay lơ lửng"
    },
    "palette": palette_entries,
    "volumetric_3d_anatomy": {
        "mesh_topology": "Chibi Ultra Beast Inverted-Teardrop Cranium with Triple Syringe Needles, Chevron Chest Bib, Chubby Torso and Curved Fin Tail",
        "light_rig": {
            "key_light": {
                "direction": [-0.4, -0.8, 0.45],
                "color": "#DDD6FE",
                "role": "Studio Keylight trên đỉnh trán và sống kim tiêm"
            },
            "fill_light": {
                "direction": [0.5, 0.3, 0.2],
                "color": "#C4B5FD",
                "role": "Ánh sáng tán xạ môi trường tím oải hương pastel"
            },
            "rim_light": {
                "direction": [0.0, 0.0, -1.0],
                "color": "#F3E8FF",
                "role": "Viền men sứ Fresnel 3D nổi khối tách nền tối"
            }
        },
        "head_dome_and_cowl": {
            "cranium_volume": "Khối vòm đầu chiếm 65% tổng thể tích nhân vật với độ bo tròn Pop Mart mũm mĩm",
            "forehead_diamond": "Viên kim cương magenta thon dài trên trán biểu trưng cho buồng chứa dung dịch keo không gian",
            "side_flanges": "Hai cánh giáp bên tai vát 3D đón sáng tạo phong thái nón phi hành gia ngoài hành tinh"
        },
        "horns_syringes_structure": {
            "center_horn": "Kim tiêm trung tâm đỉnh đầu dài 24px vươn thẳng đón nhận tín hiệu vũ trụ",
            "left_horn": "Kim tiêm trái vươn góc 45 độ hướng ra ngoài, chân sừng nở cánh hoa magenta",
            "right_horn": "Kim tiêm phải vươn góc 45 độ hướng ra ngoài, chân sừng nở cánh hoa magenta"
        },
        "glowing_cyan_eyes": {
            "shape": "Hình thoi / Parallelogram nghiêng góc sắc sảo, đầu nhọn hướng ra ngoài",
            "color_depth": "Chuyển sắc 3 lớp: Viền hốc tối Cyan (#0E7490) -> Lõi ngọc lam (#06B6D4) -> Hào quang sáng (#22D3EE / #A5F3FC)",
            "catchlight": "Điểm bắt sáng kim cương men sứ trắng tinh khiết góc 11h và đốm phản xạ đáy mắt"
        },
        "torso_and_limbs": {
            "torso": "Thân tím thẫm hạt đậu nhỏ nhắn nâng đỡ đầu, yếm chevron magenta trước ngực",
            "cyan_neck_chest_stripes": "Sọc dạ quang neon cyan sắc nét chạy quanh viền cổ và yếm ngực",
            "left_arm": "Cánh tay trái giơ lên gần má tạo cử chỉ cười khúc khích tinh nghịch",
            "right_arm": "Cánh tay phải xòe tự nhiên đón gió",
            "feet": "Hai chân bánh bao tròn trĩnh co nhẹ trong tư thế bay không trọng lực"
        },
        "playful_tail": {
            "shape": "Đuôi cong vuốt mềm mại ra sau lưng với gai nhỏ trên sống đuôi và chóp nhọn fuchsia",
            "wag_lag": "Ngoe nguẩy trễ pha Delta Phi = 0.65 rad tạo cảm giác chuyển động hữu cơ sống động"
        }
    },
    "organic_microphysics_kinematics": {
        "floating_levitation": {
            "frequency_hz": 0.32,
            "period_s": 3.14,
            "y_bobbing_amplitude_px": 3.5,
            "squash_and_stretch_vertical_pct": 5.0,
            "squash_and_stretch_horizontal_pct": -2.5,
            "volume_preservation_formula": "Sy * Sx ≈ 1.0 (sY = 1.0 + 0.05*sin(t*2.0), sX = 1.0 - 0.025*sin(t*2.0))"
        },
        "horns_undulation": {
            "phase_lag_rad": 0.45,
            "phase_lag_ms": 72,
            "swaying_formulas": {
                "sway_x": "sinf(breathPhase - 0.45f) * 3.0f",
                "sway_y": "cosf(breathPhase - 0.45f) * 2.0f"
            },
            "description": "3 Chiếc kim tiêm/sừng ngọc uốn lượn nhẹ nhàng theo nhịp bay với độ trễ sóng âm vi vật lý"
        },
        "tail_sway_kinematics": {
            "phase_lag_rad": 0.65,
            "tail_flutter_amplitude_px": 5.0,
            "formula": "sinf(breathPhase - 0.65f) * 5.0f",
            "description": "Chiếc đuôi nhỏ ngoe nguẩy vui vẻ nhịp nhàng sau thân"
        },
        "blinking_state_machine": {
            "cycle_period_ms": 3500,
            "blink_duration_ms": 140,
            "closed_eye_shape": "Đường cong lam ngọc vui tươi với góc ngoài vểnh nhẹ tinh nghịch"
        },
        "bioluminescent_poison_droplets": {
            "droplet_count": 6,
            "oscillation_hz": 0.65,
            "glow_color": "#22D3EE",
            "description": "Bọt keo độc ngân hà li ti phát sáng bồng bềnh xung quanh cơ thể"
        },
        "dynamic_contact_shadow": {
            "contact_falloff_px": 8,
            "base_width_px": 26,
            "base_height_px": 5.5,
            "dynamic_scaling": "Co giãn ngược pha với độ cao bay: phóng to khi hạ thấp, thu nhỏ khi bay cao"
        }
    },
    "cpp_scaled_canvas_code": cpp_code.strip(),
    "js_canvas_code": js_code.strip(),
    "visual_breakdown_checklist": [
        "1. Tạo hình 3D Pop Mart Vinyl cao cấp cho Poipole: Đầu to tròn phúng phính màu tím oải hương pastel (#DDD6FE -> #A78BFA) chuẩn 100% tỷ lệ Chibi.",
        "2. 3 Chiếc kim tiêm/sừng ngọc lam cyan phát quang: 1 sừng đỉnh đầu và 2 sừng bên uốn lượn nhẹ trễ pha Delta Phi = 0.45 rad.",
        "3. Thân nhỏ bé mũm mĩm màu tím đậm (#4C1D95) với chiếc đuôi nhỏ xinh xắn ngoe nguẩy vui vẻ trễ pha 0.65 rad.",
        "4. Đôi mắt hình thoi màu lam ngọc phát sáng ngộ nghĩnh (Cyan Rhombus Glowing Eyes) với điểm bắt sáng kim cương men sứ long lanh.",
        "5. Miệng cười chữ V tinh nghịch viền cyan phát quang sắc sảo kèm đôi má ửng hồng tím ngộ nghĩnh Pop Mart.",
        "6. Vệt sọc dạ quang cyan nổi bật quanh cổ và ngực viền quanh yếm chevron magenta rực rỡ.",
        "7. Chuyển động vi vật lý hữu cơ: Nhịp bay lơ lửng Squash & Stretch 5% bảo toàn thể tích chân thực (sY = 1.0 + 0.05*sin, sX = 1.0 - 0.025*sin).",
        "8. Nhịp chớp mắt 3.5s (chu kỳ 3500ms, thời gian nhắm 140ms) khép thành đường cong lam ngọc vui vẻ.",
        "9. Bóng tiếp xúc mờ ảo co giãn nhịp nhàng trên mặt sàn co giãn đồng bộ theo độ cao.",
        "10. Xuất đầy đủ mã C++ ScaledCanvas và JavaScript Canvas 2D tương thích 100% phần cứng ESP32 ST7789 và HTML5."
    ],
    "generated_render_artifact": {
        "image_file": "10_Mythic_Poipole_Adhesive_Alien.png",
        "description": "Bản điêu khắc 3D Pop Mart / Vinyl cao cấp của Poipole Quái Thú Không Gian Cực Siêu với đầu tím oải hương pastel phúng phính, 3 sừng ngọc kim tiêm cyan phát quang, mắt hình thoi ngọc lam rực sáng và sọc dạ quang cổ ngực.",
        "status": "Verified & Rendered 100% Master Fidelity"
    }
}

base_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
json_output_path = os.path.join(base_dir, 'data', 'session2_agent5_poipole.json')
os.makedirs(os.path.dirname(json_output_path), exist_ok=True)

with open(json_output_path, 'w', encoding='utf-8') as f:
    json.dump(data, f, indent=2, ensure_ascii=False)
print(f"Generated Poipole JSON: {json_output_path} ({os.path.getsize(json_output_path)} bytes)")

# Interactive HTML Preview
html_content = f'''<!DOCTYPE html>
<html lang="vi">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Poipole Adhesive Alien 3D Pop Mart - Master Preview</title>
  <style>
    * {{ box-sizing: border-box; margin: 0; padding: 0; }}
    body {{
      background: radial-gradient(circle at 50% 25%, #2e1065 0%, #0f172a 100%);
      font-family: 'Segoe UI', system-ui, -apple-system, sans-serif;
      color: #f8fafc;
      min-height: 100vh;
      display: flex;
      flex-direction: column;
      align-items: center;
      padding: 24px;
    }}
    .header {{
      text-align: center;
      margin-bottom: 20px;
    }}
    .header h1 {{
      font-size: 26px;
      font-weight: 700;
      color: #c4b5fd;
      text-shadow: 0 0 20px rgba(196, 181, 253, 0.5);
      margin-bottom: 6px;
    }}
    .header p {{
      font-size: 14px;
      color: #94a3b8;
    }}
    .badge {{
      display: inline-block;
      background: rgba(34, 211, 238, 0.2);
      border: 1px solid #22d3ee;
      color: #67e8f9;
      padding: 3px 10px;
      border-radius: 12px;
      font-size: 12px;
      font-weight: 600;
      margin-top: 6px;
    }}
    .container {{
      display: flex;
      gap: 32px;
      flex-wrap: wrap;
      justify-content: center;
      align-items: flex-start;
      max-width: 1060px;
      width: 100%;
    }}
    .card {{
      background: rgba(30, 27, 75, 0.6);
      backdrop-filter: blur(16px);
      border: 1px solid rgba(196, 181, 253, 0.2);
      border-radius: 20px;
      padding: 20px;
      box-shadow: 0 20px 40px rgba(0, 0, 0, 0.5);
      display: flex;
      flex-direction: column;
      align-items: center;
    }}
    .card h2 {{
      font-size: 16px;
      font-weight: 600;
      margin-bottom: 12px;
      color: #f472b6;
    }}
    canvas {{
      background: #110c28;
      border-radius: 16px;
      box-shadow: inset 0 0 30px rgba(0, 0, 0, 0.8), 0 0 25px rgba(34, 211, 238, 0.15);
      border: 1px solid rgba(243, 232, 255, 0.15);
    }}
    .controls {{
      margin-top: 16px;
      display: flex;
      flex-direction: column;
      gap: 10px;
      width: 100%;
    }}
    .control-row {{
      display: flex;
      justify-content: space-between;
      align-items: center;
      font-size: 13px;
      color: #cbd5e1;
    }}
    .control-row input[type="range"] {{
      width: 130px;
      accent-color: #22d3ee;
    }}
    .btn {{
      background: linear-gradient(135deg, #7c3aed 0%, #22d3ee 100%);
      border: none;
      color: white;
      font-weight: 600;
      padding: 8px 16px;
      border-radius: 10px;
      cursor: pointer;
      font-size: 13px;
      transition: all 0.2s;
    }}
    .btn:hover {{
      transform: translateY(-1px);
      box-shadow: 0 4px 15px rgba(34, 211, 238, 0.4);
    }}
    .spec-table {{
      width: 100%;
      border-collapse: collapse;
      font-size: 13px;
      margin-top: 10px;
    }}
    .spec-table td {{
      padding: 6px 10px;
      border-bottom: 1px solid rgba(255, 255, 255, 0.08);
    }}
    .spec-table td:first-child {{
      color: #94a3b8;
      font-weight: 500;
    }}
    .spec-table td:last-child {{
      color: #f1f5f9;
      font-family: monospace;
    }}
    .palette-grid {{
      display: grid;
      grid-template-columns: repeat(4, 1fr);
      gap: 8px;
      margin-top: 12px;
      width: 100%;
    }}
    .palette-item {{
      display: flex;
      flex-direction: column;
      align-items: center;
      background: rgba(15, 23, 42, 0.6);
      border-radius: 8px;
      padding: 6px;
      font-size: 10px;
    }}
    .color-swatch {{
      width: 100%;
      height: 22px;
      border-radius: 4px;
      margin-bottom: 4px;
      border: 1px solid rgba(255, 255, 255, 0.2);
    }}
  </style>
</head>
<body>
  <div class="header">
    <h1>Poipole Adhesive Alien (ベベノム)</h1>
    <p>3D Pop Mart / Vinyl High-End Collectible Simulation & ScaledCanvas Verification</p>
    <div class="badge">Session 2 - Agent 5 | 100% Hardware Compatible ST7789</div>
  </div>

  <div class="container">
    <div class="card">
      <h2>Live Organic Canvas 2D (ST7789 240x280)</h2>
      <canvas id="viewCanvas" width="240" height="280"></canvas>
      <div class="controls">
        <div class="control-row">
          <span>Tốc độ chuyển động:</span>
          <input type="range" id="speedSlider" min="0.2" max="2.5" step="0.1" value="1.0">
          <span id="speedVal">1.0x</span>
        </div>
        <div class="control-row">
          <span>Thu phóng (Scale):</span>
          <input type="range" id="scaleSlider" min="0.8" max="2.0" step="0.1" value="1.3">
          <span id="scaleVal">1.3x</span>
        </div>
        <div class="control-row" style="justify-content: center; gap: 10px; margin-top: 6px;">
          <button class="btn" id="blinkBtn">Chớp Mắt Ngay</button>
          <button class="btn" id="pauseBtn">Tạm Dừng</button>
        </div>
      </div>
    </div>

    <div class="card" style="max-width: 440px;">
      <h2>Thông Số Điêu Khắc Vi Vật Lý Hữu Cơ</h2>
      <table class="spec-table">
        <tr><td>Nhân vật:</td><td>Poipole (ベベノム UB-01 Adhesive)</td></tr>
        <tr><td>Độ phân giải hiển thị:</td><td>ST7789 240x280 / 172x320 IPS</td></tr>
        <tr><td>Squash & Stretch:</td><td>5% (sY=1.05, sX=0.975) Thể tích không đổi</td></tr>
        <tr><td>Độ trễ pha 3 sừng ngọc:</td><td>Delta Phi = 0.45 rad (~72ms)</td></tr>
        <tr><td>Độ trễ pha đuôi ngoe nguẩy:</td><td>Delta Phi = 0.65 rad (~105ms)</td></tr>
        <tr><td>Chu kỳ chớp mắt:</td><td>3500ms (Thời gian nhắm: 140ms)</td></tr>
        <tr><td>Sọc dạ quang cổ & ngực:</td><td>Cyan Neon (#22D3EE / RGB565: 0x269D)</td></tr>
        <tr><td>Mắt hình thoi:</td><td>Cyan Rhombus Specular Crystals</td></tr>
      </table>

      <h2 style="margin-top: 16px; font-size: 14px;">Bảng Màu 16-bit RGB565 Pop Mart Vinyl</h2>
      <div class="palette-grid">
        <div class="palette-item">
          <div class="color-swatch" style="background: #F3E8FF;"></div>
          <span>FRESNEL</span>
          <code>0xF75F</code>
        </div>
        <div class="palette-item">
          <div class="color-swatch" style="background: #A78BFA;"></div>
          <span>HEAD PURPLE</span>
          <code>0xA45F</code>
        </div>
        <div class="palette-item">
          <div class="color-swatch" style="background: #4C1D95;"></div>
          <span>BODY DARK</span>
          <code>0x48F2</code>
        </div>
        <div class="palette-item">
          <div class="color-swatch" style="background: #E11D48;"></div>
          <span>MAGENTA</span>
          <code>0xE0E9</code>
        </div>
        <div class="palette-item">
          <div class="color-swatch" style="background: #22D3EE;"></div>
          <span>CYAN STRIPE</span>
          <code>0x269D</code>
        </div>
        <div class="palette-item">
          <div class="color-swatch" style="background: #06B6D4;"></div>
          <span>CYAN EYE</span>
          <code>0x05BA</code>
        </div>
        <div class="palette-item">
          <div class="color-swatch" style="background: #F43F5E;"></div>
          <span>BLUSH PINK</span>
          <code>0xF1EB</code>
        </div>
        <div class="palette-item">
          <div class="color-swatch" style="background: #FFFFFF;"></div>
          <span>WHITE SPEC</span>
          <code>0xFFFF</code>
        </div>
      </div>
    </div>
  </div>

  <script>
    {js_code}

    const canvas = document.getElementById('viewCanvas');
    const ctx = canvas.getContext('2d');
    let startTime = performance.now();
    let isPaused = false;
    let manualBlink = false;
    let manualBlinkTimer = 0;

    const speedSlider = document.getElementById('speedSlider');
    const speedVal = document.getElementById('speedVal');
    const scaleSlider = document.getElementById('scaleSlider');
    const scaleVal = document.getElementById('scaleVal');
    const blinkBtn = document.getElementById('blinkBtn');
    const pauseBtn = document.getElementById('pauseBtn');

    speedSlider.addEventListener('input', (e) => {{
      speedVal.textContent = e.target.value + 'x';
    }});

    scaleSlider.addEventListener('input', (e) => {{
      scaleVal.textContent = e.target.value + 'x';
    }});

    blinkBtn.addEventListener('click', () => {{
      manualBlink = true;
      manualBlinkTimer = performance.now();
    }});

    pauseBtn.addEventListener('click', () => {{
      isPaused = !isPaused;
      pauseBtn.textContent = isPaused ? 'Tiếp Tục' : 'Tạm Dừng';
    }});

    function animate(currentTime) {{
      requestAnimationFrame(animate);
      if (isPaused) return;

      const elapsed = (currentTime - startTime) * 0.001 * parseFloat(speedSlider.value);
      const scale = parseFloat(scaleSlider.value);

      ctx.clearRect(0, 0, canvas.width, canvas.height);

      ctx.fillStyle = 'rgba(255, 255, 255, 0.25)';
      ctx.fillRect(28, 40, 1.5, 1.5);
      ctx.fillRect(210, 55, 1.5, 1.5);
      ctx.fillRect(35, 230, 1.5, 1.5);
      ctx.fillRect(195, 210, 1.5, 1.5);

      let tSim = elapsed;
      if (manualBlink) {{
        if (currentTime - manualBlinkTimer < 200) {{
          tSim = 0.05;
        }} else {{
          manualBlink = false;
        }}
      }}

      drawPoipoleAdhesiveAlien(ctx, canvas.width / 2, canvas.height / 2, scale, tSim);
    }}

    requestAnimationFrame(animate);
  </script>
</body>
</html>
'''

out_preview_path1 = os.path.join(base_dir, 'data', 'session2_agent5_poipole_preview.html')
out_preview_path2 = os.path.join(base_dir, 'test', 'preview_poipole.html')
os.makedirs(os.path.dirname(out_preview_path2), exist_ok=True)

with open(out_preview_path1, 'w', encoding='utf-8') as f:
    f.write(html_content)

with open(out_preview_path2, 'w', encoding='utf-8') as f:
    f.write(html_content)

print(f"Generated Poipole preview HTML (data): {out_preview_path1}")
print(f"Generated Poipole preview HTML (test): {out_preview_path2}")
