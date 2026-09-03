# -*- coding: utf-8 -*-
"""
Builder script for data/session1_agent1_celebi.json
Authored by: Nghệ Sĩ Điêu Khắc Celebi Tinh Linh Rừng Xanh Thời Gian (Celebi Forest Fairy 3D Sculptor)
"""
import json
import os

def hex_to_rgb565(hex_str):
    hex_str = hex_str.lstrip('#')
    r = int(hex_str[0:2], 16)
    g = int(hex_str[2:4], 16)
    b = int(hex_str[4:6], 16)
    rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
    return f"0x{rgb565:04X}"

def create_color_entry(name, hex_code, optical_function):
    return {
        "name": name,
        "hex": hex_code,
        "rgb565": hex_to_rgb565(hex_code),
        "optical_function": optical_function
    }

celebi_data = {
    "metadata": {
        "agent_name": "Nghệ Sĩ Điêu Khắc Celebi Tinh Linh Rừng Xanh Thời Gian (Celebi Forest Fairy 3D Sculptor)",
        "role": "Lead 3D Pop Mart & Vinyl Stylist / Organic Micro-Physics Animator",
        "version": "2.1.0-PRO-MAX-CELEBI",
        "created_date": "2026-09-04",
        "target_display": "ST7789 172x320 & 240x280 16-bit RGB565 IPS LCD / Modern HTML5 Canvas 2D",
        "reference_art": "01_Mythic_Celebi_Forest_Fairy.png",
        "design_frameworks": [
            "Reffernce/NHOM_1_FRONTEND_UIUX/ui-ux-pro-max-skill-main (Design Intelligence, Precision Crafting, Anti-cheap-icon)",
            "Reffernce/NHOM_1_FRONTEND_UIUX/impeccable-main (Craft floor, tactile vinyl depth, material fidelity)"
        ],
        "core_design_rules": {
            "onion_fairy_silhouette": "Thân hình búp hành tây (Onion fairy body) mềm mại núng nính, chóp đầu vuốt nhọn cong vút lên cao với các nếp khía gân lá xanh rừng thẫm rực rỡ.",
            "crystal_sapphire_eyes": "Đôi mắt pha lê to tròn chiếm 35% diện tích khuôn mặt viền đen sắc nét, đồng tử xanh sapphire 3 điểm bắt sáng vật lý (đốm chính 2x2 góc 10h, đốm phụ 1x1 góc 4h, vệt trăng khuyết đáy mắt), má hồng đào tán mịn.",
            "luminescent_antennae": "Cặp ăng-ten kép vươn cao uốn cong duyên dáng từ trán, gốc xanh ngọc chuyển tiếp sang chóp xanh lam dạ quang (cyan-electric glow) có quán tính lắc lư khi chuyển động.",
            "translucent_sss_silk_wings": "Đôi cánh tiên lụa trong suốt mô phỏng vật liệu tán xạ dưới bề mặt (SSS - Subsurface Scattering), viền phản quang Fresnel ngọc bích, rung đập trễ pha 0.45 rad với tần số cao.",
            "bamboo_shoots_limbs": "Chân tay thon gọn búp măng, ngón tay 3 khía nhỏ xíu dang rộng đón gió, bàn chân bo tròn dễ thương tựa giọt sương đọng trên lá cỏ.",
            "organic_micro_physics": "Hệ thống vi vật lý hữu cơ hoàn chỉnh: Nhịp thở Squash & Stretch 5% bảo toàn thể tích quanh tâm (cx, cy), cánh tiên trễ pha Delta Phi 0.45 rad, ăng-ten uốn lượn quán tính 0.25 rad, nhịp chớp mắt tự nhiên 3.5s, bóng sàn co giãn tương tác cao độ."
        }
    },
    "character": {
        "id": 1,
        "code": "MYTHIC_CELEBI_FOREST_FAIRY",
        "name_vi": "Celebi Tinh Linh Rừng Xanh Thời Gian",
        "name_en": "Celebi Mythic Forest Fairy (Voice of the Forest)",
        "japanese_name": "セレビィ (Celebi)",
        "species": "Celebi Sylvestris Chronos",
        "category": "Tinh Linh Thần Thoại Vượt Thời Gian",
        "element": "Cỏ / Tâm Linh / Rừng Xanh Thời Không (Grass / Psychic / Forest Starlight)",
        "quote_vi": "Người bảo hộ của những cánh rừng già nguyên sinh. Nơi nào Celebi lướt qua, vạn vật hồi sinh, hoa thơm cỏ lạ nở rộ vượt thời gian.",
        "quote_en": "The guardian spirit of the ancient forests. Wherever Celebi dances through time, lush flora and withered woods blossom into eternal spring.",
        "mythic_lore": [
            "Là linh hồn bất tử của thiên nhiên, Celebi có khả năng chu du xuyên qua các dòng thời gian để gieo mầm sự sống xanh tươi cho muôn loài.",
            "Cơ thể Celebi mang kết cấu mềm mại như búp hành tây non đọng sương mai, hai ăng-ten tiếp nhận năng lượng sinh thái của đất trời.",
            "Đôi mắt to tròn long lanh phản chiếu vẻ đẹp trong ngần của những hồ nước nguyên sinh ngàn năm sâu thẳm trong rừng thiêng.",
            "Đôi cánh tiên siêu mỏng rung động với tần số cao, tạo nên luồng gió mang theo phấn hoa phát sáng lấp lánh như bụi sao."
        ],
        "palette": [
            create_color_entry("col_fresnel_rim", "#F4FDF0", "Viền phản xạ Fresnel trắng ngọc ánh xanh thanh khiết ngoài cùng"),
            create_color_entry("col_body_base", "#C8F0A6", "Thân xanh hành tây mềm mại (Mint pastel onion skin base)"),
            create_color_entry("col_body_mid", "#B2E58B", "Sắc xanh cỏ non trung gian chuyển tiếp độ sâu thể tích"),
            create_color_entry("col_body_shadow", "#8FD065", "Vùng đổ bóng khuất mềm mại dưới cằm và nếp gấp thân"),
            create_color_entry("col_body_deep", "#68A843", "Bóng đổ Ambient Occlusion sâu lắng dưới hốc đùi"),
            create_color_entry("col_crest_tip", "#3E8E2D", "Chóp nhọn củ hành tây xanh lá cây đậm vươn cao"),
            create_color_entry("col_crest_dark", "#245C1A", "Đường khía gân lá chóp vương miện rừng già"),
            create_color_entry("col_crest_glow", "#95E46A", "Vùng đón sáng rực rỡ mặt trước chóp đầu"),
            create_color_entry("col_pants_dark", "#488A2E", "Quần đùi lá xanh rừng thẫm bao quanh hông"),
            create_color_entry("col_pants_light", "#6EBD4D", "Mặt đón sáng nổi khối của quần lá"),
            create_color_entry("col_legs_dark", "#3D7527", "Chân búp măng thon gọn bóng râm"),
            create_color_entry("col_legs_light", "#64A648", "Mặt đón sáng bàn chân tròn ngộ nghĩnh"),
            create_color_entry("col_antenna_stem", "#B2E88F", "Thân ăng-ten xanh ngọc dẻo dai uốn lượn"),
            create_color_entry("col_antenna_mid", "#64D8CB", "Vùng chuyển sắc lam ngọc giữa ăng-ten"),
            create_color_entry("col_antenna_tip", "#00B4D8", "Chóp ăng-ten xanh lam dạ quang phát sáng rực rỡ"),
            create_color_entry("col_antenna_glow", "#72EFDD", "Vầng quang cyan tỏa sáng quanh chóp ăng-ten"),
            create_color_entry("col_antenna_core", "#0077B6", "Lõi xanh sapphire thẫm của chóp dạ quang"),
            create_color_entry("col_eye_ring", "#121812", "Viền mắt đen nhung sắc nét chiếm 35% khuôn mặt"),
            create_color_entry("col_eye_socket", "#0A0F0A", "Hốc mắt đen tuyền huyền bí"),
            create_color_entry("col_iris_deep", "#023E8A", "Đáy mắt xanh sapphire thẫm sâu thẳm"),
            create_color_entry("col_iris_sapphire", "#0077B6", "Đồng tử xanh sapphire trong vắt tựa ngọc bích"),
            create_color_entry("col_iris_bright", "#00B4D8", "Mống mắt lam ngọc tươi sáng đón ánh mặt trời"),
            create_color_entry("col_iris_caustic", "#90E0EF", "Vệt trăng khuyết caustic phản quang đáy mắt"),
            create_color_entry("col_specular_key", "#FFFFFF", "Điểm bắt sáng chính 2x2 góc 10h (Keylight Glint)"),
            create_color_entry("col_specular_sec", "#CAF0F8", "Điểm bắt sáng phụ 1x1 góc 4h (Ambient Bounce)"),
            create_color_entry("col_blush_peach", "#FFAAA6", "Má hồng đào tán mịn squishy phúng phính"),
            create_color_entry("col_mouth", "#1A3818", "Khóe miệng nụ cười nhỏ nhắn tinh nghịch"),
            create_color_entry("col_wing_glass", "#E0F7FA", "Cánh tiên lụa trong suốt màng mỏng đón sáng"),
            create_color_entry("col_wing_glow", "#A7F3D0", "Ánh phản quang Fresnel ngọc bích viền cánh tiên"),
            create_color_entry("col_wing_rim", "#80DEEA", "Khung viền cánh tiên phát quang lộng lẫy"),
            create_color_entry("col_wing_vein", "#4DD0E1", "Gân cánh tiên trong suốt khúc xạ ánh sáng"),
            create_color_entry("col_shadow_ground", "#0A1C0A", "Lõi bóng tiếp xúc sàn hữu cơ đậm đặc"),
            create_color_entry("col_shadow_diffuse", "#142E14", "Vầng bóng sàn khuếch tán mềm co giãn theo độ cao"),
            create_color_entry("col_magic_spore", "#E0FF4F", "Bụi bào tử rừng xanh lơ lửng phát sáng"),
            create_color_entry("col_stardust_gold", "#FEF08A", "Bụi sao hoàng kim thời không lấp lánh ✨")
        ],
        "volumetric_anatomy": {
            "silhouette": "Hình thể giọt sương búp hành tây (Onion fairy body) mềm mại, tỷ lệ Chibi 1:1 đặc trưng của dòng Pop Mart Vinyl cao cấp.",
            "head_and_crest": "Đầu dạng búp hành tây tròn trịa mập mạp, phía sau vươn cao thành một chóp nhọn uốn lượn (Flame / Sprout Crest) với các đường khía gân lá xanh rừng thẫm uyển chuyển.",
            "dual_antennae": "Cặp ăng-ten kép xanh ngọc vươn cao từ vùng trán, uốn cong hình cánh cung duyên dáng với chóp xanh lam dạ quang phát sáng rực rỡ.",
            "crystal_eyes": {
                "proportion": "Chiếm 35% diện tích khuôn mặt, tạo nét biểu cảm ngây thơ, thần thoại thuần khiết.",
                "contour": "Viền mắt đen nhung tuyền dày dặn, sắc nét, bao trọn mống mắt sapphire đa lớp.",
                "specular_highlights": {
                    "point_1_primary": "Đốm bắt sáng chính 2x2 góc 10h (#FFFFFF) - nguồn sáng chính trực tiếp.",
                    "point_2_secondary": "Đốm bắt sáng phụ 1x1 góc 4h (#CAF0F8) - phản xạ ánh sáng môi trường nảy từ mặt đất.",
                    "point_3_caustic_crescent": "Vệt trăng khuyết phản quang đáy mắt (#90E0EF & #FFFFFF) tạo hiệu ứng đáy mắt ngậm nước long lanh."
                }
            },
            "cheeks_and_smile": "Má hồng đào tán mịn squishy (#FFAAA6) nở rộ dưới hai mắt; khóe miệng vẽ một nụ cười mỉm nhỏ nhắn ở góc dưới má trái.",
            "limbs_and_toes": "Chân tay thon gọn búp măng, ngón tay 3 khía nhỏ xíu xòe rộng đón gió khi bay lượn, ngón chân bo tròn dễ thương tựa giọt sương đọng trên lá cỏ.",
            "wings_sss": "Đôi cánh tiên lụa trong suốt màng mỏng mô phỏng tán xạ dưới bề mặt SSS, phản chiếu ánh sáng ngọc bích và đập cánh với tần số cao trễ pha 0.45 rad."
        },
        "micro_physics_kinematics": {
            "breathing_cycle": {
                "frequency_hz": 0.32,
                "angular_frequency": 2.0,
                "squash_and_stretch_vertical_pct": 5.0,
                "squash_and_stretch_horizontal_pct": -2.5,
                "formula_vertical": "sY = 1.0 + 0.05 * sin(t * 2.0)",
                "formula_horizontal": "sX = 1.0 - 0.025 * sin(t * 2.0)",
                "volume_conservation_note": "(1 + sY) * (1 + sX)^2 ≈ 1.00 bảo toàn thể tích khối mềm quanh tâm (cx, cy)."
            },
            "wing_flapping": {
                "phase_lag_rad": 0.45,
                "oscillation_deg": 15.0,
                "frequency_multiplier": 3.75,
                "formula": "wingFlap = sin(t * 7.5 - 0.45) * 5.0",
                "flutter_note": "Dao động tần số cao mô phỏng cánh côn trùng tiên cảnh bay lơ lửng ổn định."
            },
            "antenna_inertia": {
                "phase_lag_rad": 0.25,
                "horizontal_sway_px": 2.5,
                "vertical_sway_px": 2.0,
                "formula_x": "antSwayX = cos(t * 2.0 - 0.25) * 2.5",
                "formula_y": "antSwayY = sin(t * 2.0 - 0.25) * 2.0",
                "viscoelastic_note": "Ăng-ten uốn lượn theo gia tốc quán tính khi Celebi nâng hạ độ cao."
            },
            "natural_blinking": {
                "cycle_ms": 3500,
                "closed_duration_ms": 140,
                "formula_trigger": "(millis() % 3500 < 140)",
                "eyelid_shape": "Cung trăng khuyết khép mi dịu dàng, hạnh phúc."
            },
            "ground_contact_shadow": {
                "center": "cx + 4, cy + 46",
                "formula_diffuse_rx": "(22 - sin(t * 2.0) * 3.5) * sX",
                "formula_diffuse_ry": "max(2, 6.5 - sin(t * 2.0) * 1.2)",
                "formula_core_rx": "(16 - sin(t * 2.0) * 2.8) * sX",
                "formula_core_ry": "max(2, 4.5 - sin(t * 2.0) * 1.0)",
                "altitude_interaction": "Khi Celebi hạ thấp (thở ra), bóng tiếp xúc sàn thu hẹp độ nhòe và đậm nét hơn; khi Celebi bay cao, bóng loang rộng và mờ dịu."
            }
        },
        "cpp_scaled_canvas_code": """// =========================================================================
// CELEBI TINH LINH RỪNG XANH THỜI GIAN (MYTHIC CELEBI FOREST FAIRY)
// ScaledCanvas C++ Implementation - 100% Hardware Compatible ST7789
// Primitives used: fillCircle, fillRoundRect, fillEllipse, drawLine,
//                  drawFastHLine, drawFastVLine, drawCircle, drawEllipse, fillTriangle
// =========================================================================
void drawCelebiForestFairy(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink) {
  // 1. Nhịp thở Squash & Stretch 5% bảo toàn thể tích quanh tâm (cx, cy)
  float breathFreq  = 2.0f;
  float breathPhase = angle * breathFreq;
  float breathSin   = sinf(breathPhase);

  int by   = cy + (int)(breathSin * 3.5f);
  float sY = 1.0f + 0.05f * breathSin;       // Co giãn trục dọc +5%
  float sX = 1.0f - 0.025f * breathSin;      // Co bù trục ngang -2.5%

  // 2. Cánh tiên đập trễ pha Delta Phi = 0.45 rad (dao động 15 độ tần số cao)
  float wingPhase = angle * 7.5f - 0.45f;
  float wingFlap  = sinf(wingPhase) * 5.0f;

  // 3. Ăng-ten quán tính khi bay lên xuống (Delta Phi = 0.25 rad)
  float antPhase = breathPhase - 0.25f;
  int antSwayX   = (int)(cosf(antPhase) * 2.5f);
  int antSwayY   = (int)(sinf(antPhase) * 2.0f);

  // 4. Bảng màu 16-bit RGB565 chuẩn xác
  const uint16_t C_FRESNEL        = 0xF7FE; // #F4FDF0 Viền Fresnel trắng ngọc
  const uint16_t C_BODY_BASE      = 0xCF94; // #C8F0A6 Thân búp hành tây mint pastel
  const uint16_t C_BODY_MID       = 0xB731; // #B2E58B Sắc xanh cỏ non trung gian
  const uint16_t C_BODY_SHADOW    = 0x8E8C; // #8FD065 Bóng đổ cằm và thân dưới
  const uint16_t C_BODY_DEEP      = 0x6D48; // #68A843 Bóng hốc tối
  const uint16_t C_CREST_TIP      = 0x3C65; // #3E8E2D Chóp nhọn củ hành tây xanh đậm
  const uint16_t C_CREST_DARK     = 0x22E3; // #245C1A Gân lá chóp vương miện rừng già
  const uint16_t C_CREST_GLOW     = 0x972D; // #95E46A Đón sáng chóp đầu
  const uint16_t C_PANTS_DARK     = 0x4C45; // #488A2E Quần đùi lá xanh đậm quanh hông
  const uint16_t C_PANTS_LIGHT    = 0x6DE9; // #6EBD4D Đón sáng quần lá
  const uint16_t C_LEGS_DARK      = 0x3BA4; // #3D7527 Chân búp măng rừng già
  const uint16_t C_LEGS_LIGHT     = 0x6529; // #64A648 Bàn chân đón sáng
  const uint16_t C_ANT_STEM       = 0xB751; // #B2E88F Thân ăng-ten xanh ngọc dẻo
  const uint16_t C_ANT_MID        = 0x66D9; // #64D8CB Chuyển sắc lam ngọc
  const uint16_t C_ANT_TIP        = 0x05BB; // #00B4D8 Chóp ăng-ten xanh lam dạ quang
  const uint16_t C_ANT_GLOW       = 0x777B; // #72EFDD Vầng quang cyan tỏa sáng
  const uint16_t C_EYE_RING       = 0x10C2; // #121812 Viền mắt đen nhung sắc nét 35%
  const uint16_t C_IRIS_DEEP      = 0x01F1; // #023E8A Đáy mắt xanh sapphire thẫm
  const uint16_t C_IRIS_SAPPHIRE  = 0x03B6; // #0077B6 Đồng tử xanh sapphire trong vắt
  const uint16_t C_IRIS_BRIGHT    = 0x05BB; // #00B4D8 Mống mắt lam ngọc tươi sáng
  const uint16_t C_IRIS_CAUSTIC   = 0x971D; // #90E0EF Vệt trăng khuyết đáy mắt
  const uint16_t C_WHITE          = 0xFFFF; // #FFFFFF Đốm bắt sáng chính 2x2 góc 10h
  const uint16_t C_SPEC_SEC       = 0xCF9F; // #CAF0F8 Đốm bắt sáng phụ 1x1 góc 4h
  const uint16_t C_BLUSH          = 0xFD54; // #FFAAA6 Má hồng đào tán mịn squishy
  const uint16_t C_MOUTH          = 0x19C3; // #1A3818 Nụ cười khóe miệng tí hon
  const uint16_t C_WING_GLASS     = 0xE7BF; // #E0F7FA Cánh tiên lụa trong suốt SSS
  const uint16_t C_WING_GLOW      = 0xA79A; // #A7F3D0 Phản quang viền cánh tiên
  const uint16_t C_WING_RIM       = 0x86FD; // #80DEEA Khung viền cánh tiên
  const uint16_t C_WING_VEIN      = 0x4E9C; // #4DD0E1 Gân cánh tiên trong suốt
  const uint16_t C_SHADOW_GND     = 0x08E1; // #0A1C0A Lõi bóng sàn đậm đặc
  const uint16_t C_SHADOW_DIFF    = 0x1162; // #142E14 Vầng bóng sàn khuếch tán
  const uint16_t C_MAGIC_SPORE    = 0xE7E9; // #E0FF4F Bụi bào tử rừng phát sáng
  const uint16_t C_STAR_GOLD      = 0xFF91; // #FEF08A Bụi sao hoàng kim ✨

  // =========================================================================
  // LỚP 1: BÓNG TIẾP XÚC MẶT SÀN CO GIÃN THEO ĐỘ CAO
  // =========================================================================
  int groundY = cy + 46;
  int diffRx  = (int)((22.0f - breathSin * 3.5f) * sX);
  int diffRy  = max(2, (int)(6.5f - breathSin * 1.2f));
  int coreRx  = (int)((16.0f - breathSin * 2.8f) * sX);
  int coreRy  = max(2, (int)(4.5f - breathSin * 1.0f));
  spr->drawEllipse(cx + 4, groundY, diffRx, diffRy, C_SHADOW_DIFF);
  spr->fillEllipse(cx + 4, groundY, coreRx, coreRy, C_SHADOW_GND);

  // =========================================================================
  // LỚP 2: CÁNH TIÊN PHÍA SAU (Far Wing) - Trễ pha 0.45 rad
  // =========================================================================
  int w1TipX = cx + 32;
  int w1TipY = by - 18 + (int)wingFlap;
  int w1MidX = cx + 24;
  int w1MidY = by - 8 + (int)(wingFlap * 0.7f);
  spr->fillTriangle(cx + 6, by - 4, w1TipX, w1TipY, w1MidX, w1MidY, C_WING_GLASS);
  spr->fillTriangle(cx + 6, by - 2, w1MidX, w1MidY, cx + 18, by + 4, C_WING_GLOW);
  spr->drawLine(cx + 6, by - 4, w1TipX, w1TipY, C_WING_RIM);
  spr->drawLine(cx + 6, by - 4, w1MidX, w1MidY, C_WING_VEIN);

  // =========================================================================
  // LỚP 3: CÁNH TAY SAU (Left / Far Arm)
  // =========================================================================
  spr->fillTriangle(cx - 10, by + 7, cx - 8, by + 3, cx - 26, by - 2, C_BODY_BASE);
  spr->drawLine(cx - 10, by + 3, cx - 26, by - 2, C_FRESNEL);
  // 3 ngón tay nhỏ nhắn búp măng
  spr->fillCircle(cx - 28, by - 5, 1, C_BODY_BASE);
  spr->fillCircle(cx - 30, by - 2, 1, C_BODY_BASE);
  spr->fillCircle(cx - 27, by + 1, 1, C_BODY_BASE);

  // =========================================================================
  // LỚP 4: ĐÔI CHÂN & BÀN CHÂN BO TRÒN DỄ THƯƠNG
  // =========================================================================
  // Chân sau (Far leg)
  spr->fillRoundRect(cx + 6, by + 18, (int)(7 * sX), (int)(12 * sY), 3, C_LEGS_DARK);
  spr->fillCircle(cx + 9, by + 28, (int)(3 * sX), C_LEGS_LIGHT);
  // Chân trước (Near leg)
  spr->fillRoundRect(cx + 12, by + 21, (int)(8 * sX), (int)(14 * sY), 4, C_LEGS_DARK);
  spr->fillRoundRect(cx + 13, by + 22, (int)(6 * sX), (int)(9 * sY), 3, C_LEGS_LIGHT);
  spr->fillCircle(cx + 16, by + 33, (int)(4 * sX), C_LEGS_LIGHT);
  spr->drawPixel(cx + 16, by + 34, C_FRESNEL);

  // =========================================================================
  // LỚP 5: QUẦN LÁ XANH ĐẬM (Leaf Bloomers)
  // =========================================================================
  spr->fillEllipse(cx + 3, by + 14, (int)(13 * sX), (int)(10 * sY), C_PANTS_DARK);
  spr->fillEllipse(cx + 2, by + 13, (int)(11 * sX), (int)(8 * sY), C_PANTS_LIGHT);
  spr->drawRoundRect(cx - 5, by + 8, (int)(14 * sX), (int)(8 * sY), 3, C_CREST_TIP);

  // =========================================================================
  // LỚP 6: THÂN BÚP HÀNH TÂY (Onion Fairy Body)
  // =========================================================================
  spr->fillEllipse(cx + 1, by + 7, (int)(12 * sX), (int)(11 * sY), C_BODY_SHADOW);
  spr->fillEllipse(cx, by + 6, (int)(11 * sX), (int)(10 * sY), C_BODY_BASE);
  spr->fillEllipse(cx - 2, by + 5, (int)(8 * sX), (int)(7 * sY), C_FRESNEL);

  // =========================================================================
  // LỚP 7: CÁNH TIÊN PHÍA TRƯỚC (Near Wing)
  // =========================================================================
  float frontFlap = sinf(wingPhase + 0.2f) * 5.0f;
  int w2TipX = cx + 38;
  int w2TipY = by - 12 + (int)frontFlap;
  int w2MidX = cx + 28;
  int w2MidY = by + (int)(frontFlap * 0.7f);
  spr->fillTriangle(cx + 8, by - 2, w2TipX, w2TipY, w2MidX, w2MidY, C_WING_GLASS);
  spr->fillTriangle(cx + 8, by, w2MidX, w2MidY, cx + 20, by + 8, C_WING_GLOW);
  spr->drawLine(cx + 8, by - 2, w2TipX, w2TipY, C_FRESNEL);
  spr->drawLine(cx + 8, by - 2, w2MidX, w2MidY, C_WING_VEIN);
  spr->fillCircle(w2TipX, w2TipY, 1, C_FRESNEL);

  // =========================================================================
  // LỚP 8: CÁNH TAY TRƯỚC (Right / Near Arm)
  // =========================================================================
  spr->fillTriangle(cx + 6, by + 6, cx + 8, by + 10, cx + 32, by + 10, C_BODY_BASE);
  spr->drawLine(cx + 6, by + 6, cx + 32, by + 9, C_FRESNEL);
  // 3 ngón tay búp măng dang rộng đón gió
  spr->fillCircle(cx + 34, by + 8, 1, C_BODY_BASE);
  spr->fillCircle(cx + 36, by + 10, 1, C_BODY_BASE);
  spr->fillCircle(cx + 33, by + 13, 1, C_BODY_BASE);

  // =========================================================================
  // LỚP 9: ĐẦU BÚP HÀNH TÂY & CHÓP XANH RỪNG VƯƠN CAO (Onion Sprout Crest)
  // =========================================================================
  int hy  = by - 8;
  int hrx = (int)(22 * sX);
  int hry = (int)(22 * sY);
  // Khối đầu tròn mịn màng
  spr->drawEllipse(cx - 3, hy, hrx + 1, hry + 1, C_FRESNEL);
  spr->fillEllipse(cx - 3, hy, hrx, hry, C_BODY_BASE);
  spr->fillEllipse(cx + 5, hy + 4, (int)(14 * sX), (int)(12 * sY), C_BODY_SHADOW);
  spr->fillCircle(cx - 16, hy + 8, (int)(9 * sX), C_BODY_BASE);
  spr->fillCircle(cx - 7, hy + 14, (int)(8 * sX), C_BODY_BASE);

  // Chóp đầu nhọn uốn cong thanh thoát về phía sau-trên (Flame/Onion Sprout Crest)
  spr->fillTriangle(cx - 4, hy - 14, cx + 12, hy - 10, cx + 18, hy - 40, C_BODY_BASE);
  spr->fillTriangle(cx + 2, hy - 22, cx + 14, hy - 16, cx + 18, hy - 40, C_CREST_GLOW);
  spr->fillTriangle(cx + 6, hy - 26, cx + 16, hy - 22, cx + 18, hy - 40, C_CREST_TIP);
  // Đỉnh vuốt cong nhẹ
  spr->fillTriangle(cx + 12, hy - 36, cx + 18, hy - 40, cx + 16, hy - 44, C_CREST_DARK);
  // Các đường khía gân lá xanh rừng thẫm uốn lượn
  spr->drawLine(cx + 16, hy - 44, cx + 8, hy - 18, C_CREST_DARK);
  spr->drawLine(cx + 16, hy - 44, cx + 12, hy - 14, C_CREST_DARK);
  spr->drawLine(cx + 16, hy - 44, cx + 16, hy - 22, C_CREST_DARK);
  spr->drawFastVLine(cx + 15, hy - 38, 12, C_CREST_DARK);
  spr->drawLine(cx + 6, hy - 18, cx + 15, hy - 41, C_FRESNEL);

  // =========================================================================
  // LỚP 10: CẶP ĂNG-TEN KÉP XANH NGỌC VƯƠN CAO, CHÓP XANH LAM DẠ QUANG
  // (Cong uốn lượn hình cánh cung duyên dáng + Quán tính dao động)
  // =========================================================================
  // 10.1 Ăng-ten trái (Far Antenna)
  int a1_x0 = cx - 11, a1_y0 = hy - 12;
  int a1_x1 = cx - 21 + antSwayX, a1_y1 = hy - 24 + antSwayY;
  int a1_x2 = cx - 23 + (int)(antSwayX * 1.2f), a1_y2 = hy - 34 + antSwayY;
  int a1_x3 = cx - 18 + (int)(antSwayX * 1.4f), a1_y3 = hy - 42 + antSwayY;

  // Thân ăng-ten uốn cong
  spr->drawLine(a1_x0, a1_y0, a1_x1, a1_y1, C_ANT_STEM);
  spr->drawLine(a1_x0 + 1, a1_y0, a1_x1 + 1, a1_y1, C_BODY_BASE);
  spr->drawLine(a1_x1, a1_y1, a1_x2, a1_y2, C_ANT_MID);
  spr->drawLine(a1_x2, a1_y2, a1_x3, a1_y3, C_ANT_TIP);
  // Chóp dạ quang xanh lam
  spr->drawCircle(a1_x3, a1_y3, 3, C_ANT_GLOW);
  spr->fillCircle(a1_x3, a1_y3, 2, C_ANT_TIP);
  spr->drawPixel(a1_x3, a1_y3, C_FRESNEL);

  // 10.2 Ăng-ten phải (Near Antenna)
  int a2_x0 = cx - 1, a2_y0 = hy - 14;
  int a2_x1 = cx + 3 + antSwayX, a2_y1 = hy - 26 + antSwayY;
  int a2_x2 = cx + 5 + (int)(antSwayX * 1.2f), a2_y2 = hy - 38 + antSwayY;
  int a2_x3 = cx + 1 + (int)(antSwayX * 1.4f), a2_y3 = hy - 46 + antSwayY;

  spr->drawLine(a2_x0, a2_y0, a2_x1, a2_y1, C_ANT_STEM);
  spr->drawLine(a2_x0 + 1, a2_y0, a2_x1 + 1, a2_y1, C_FRESNEL);
  spr->drawLine(a2_x1, a2_y1, a2_x2, a2_y2, C_ANT_MID);
  spr->drawLine(a2_x2, a2_y2, a2_x3, a2_y3, C_ANT_TIP);
  // Chóp dạ quang xanh lam to hơn, bắt mắt
  spr->drawCircle(a2_x3, a2_y3, 4, C_ANT_GLOW);
  spr->fillCircle(a2_x3, a2_y3, 3, C_ANT_TIP);
  spr->fillCircle(a2_x3, a2_y3, 1, C_FRESNEL);

  // =========================================================================
  // LỚP 11: MÁ HỒNG ĐÀO TÁN MỊN & NỤ CƯỜI TÍ HON
  // =========================================================================
  spr->fillEllipse(cx - 19, hy + 9, 4, 3, C_BLUSH);
  spr->fillEllipse(cx + 6, hy + 12, 5, 3, C_BLUSH);
  // Khóe miệng nụ cười nhỏ nhắn ở góc dưới má trái
  spr->drawPixel(cx - 13, hy + 16, C_MOUTH);
  spr->drawPixel(cx - 12, hy + 17, C_MOUTH);
  spr->drawPixel(cx - 11, hy + 17, C_MOUTH);
  spr->drawPixel(cx - 10, hy + 16, C_MOUTH);

  // =========================================================================
  // LỚP 12: ĐÔI MẮT PHA LÊ TO TRÒN CHIẾM 35% KHUÔN MẶT VIỀN ĐEN SẮC NÉT
  // =========================================================================
  // 12.1 Mắt trái (Far eye trong góc 3/4)
  int exL = cx - 17;
  int eyL = hy + 3;
  if (blink) {
    spr->drawEllipse(exL, eyL + 2, 5, 2, C_EYE_RING);
  } else {
    // Viền đen sắc nét
    spr->fillEllipse(exL, eyL, 6, 12, C_EYE_RING);
    // Mống mắt sapphire
    spr->fillEllipse(exL, eyL, 4, 10, C_IRIS_SAPPHIRE);
    // Mống mắt lam ngọc sáng
    spr->fillEllipse(exL, eyL + 1, 3, 7, C_IRIS_BRIGHT);
    // Vệt trăng khuyết đáy mắt
    spr->fillEllipse(exL, eyL + 5, 3, 4, C_IRIS_CAUSTIC);
    // Đáy mắt đồng tử đen thẳm
    spr->fillEllipse(exL, eyL, 3, 5, C_IRIS_DEEP);
    // 3 điểm bắt sáng mắt trái
    spr->fillRect(exL - 1, eyL - 3, 2, 2, C_WHITE);
    spr->drawPixel(exL + 1, eyL + 4, C_SPEC_SEC);
    spr->drawFastHLine(exL - 1, eyL + 6, 2, C_WHITE);
  }

  // 12.2 Mắt phải (Near eye - Trực diện 35% khuôn mặt)
  int exR = cx - 4;
  int eyR = hy + 6;
  if (blink) {
    spr->drawEllipse(exR, eyR + 2, 9, 3, C_EYE_RING);
    spr->drawEllipse(exR, eyR + 3, 9, 3, C_EYE_RING);
  } else {
    // Viền đen sắc nét nhung tuyền (Iconic thick black eye ring)
    spr->fillEllipse(exR, eyR, 11, 16, C_EYE_RING);
    // Mống mắt xanh sapphire
    spr->fillEllipse(exR, eyR, 9, 14, C_IRIS_SAPPHIRE);
    // Vùng xanh lam ngọc tươi sáng
    spr->fillEllipse(exR, eyR + 1, 8, 10, C_IRIS_BRIGHT);
    // Vệt trăng khuyết caustic phản quang đáy mắt
    spr->fillEllipse(exR, eyR + 6, 6, 4, C_IRIS_CAUSTIC);
    // Đồng tử xanh sapphire đen thẳm
    spr->fillEllipse(exR - 1, eyR - 1, 5, 8, C_IRIS_DEEP);
    // 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Specular Highlights)
    // 1. Đốm chính 2x2 góc 10h
    spr->fillRect(exR - 4, eyR - 5, 2, 2, C_WHITE);
    spr->drawPixel(exR - 3, eyR - 6, C_WHITE);
    // 2. Đốm phụ 1x1 góc 4h
    spr->drawPixel(exR + 2, eyR + 5, C_SPEC_SEC);
    // 3. Vệt trăng khuyết đáy mắt (Caustic crescent highlights)
    spr->drawFastHLine(exR - 3, eyR + 7, 4, C_WHITE);
    spr->drawFastHLine(exR - 2, eyR + 8, 2, C_SPEC_SEC);
  }

  // =========================================================================
  // LỚP 13: BỤI BÀO TỬ RỪNG XANH PHÁT QUANG (Forest Magic Spores ✨)
  // =========================================================================
  // Bụi hoàng kim
  spr->drawFastHLine(cx - 24, by + 16, 3, C_STAR_GOLD);
  spr->drawFastVLine(cx - 23, by + 15, 3, C_STAR_GOLD);
  spr->drawPixel(cx - 23, by + 16, C_WHITE);
  // Bụi lam ngọc
  spr->drawFastHLine(cx + 28, by - 28, 3, C_ANT_GLOW);
  spr->drawFastVLine(cx + 29, by - 29, 3, C_ANT_GLOW);
  spr->drawPixel(cx + 29, by - 28, C_WHITE);
  // Đốm sáng xanh lộc biếc
  spr->drawPixel(cx - 18, by - 22, C_MAGIC_SPORE);
  spr->drawPixel(cx + 22, by + 26, C_MAGIC_SPORE);
}
""",
        "js_canvas_code": """// =========================================================================
// CELEBI TINH LINH RỪNG XANH THỜI GIAN - Modern HTML5 Canvas 2D Implementation
// 3D Pop Mart / Vinyl Shading, Translucent SSS Wings, Organic Physics
// =========================================================================
function drawCelebiForestFairy(ctx, cx, cy, scale, t) {
  ctx.save();

  // 1. Nhịp thở Squash & Stretch 5% bảo toàn thể tích quanh tâm
  const breathFreq  = 2.0;
  const breathPhase = t * breathFreq;
  const breathSin   = Math.sin(breathPhase);
  const by = cy + breathSin * 3.5;
  const sY = 1.0 + 0.05 * breathSin;
  const sX = 1.0 - 0.025 * breathSin;

  ctx.translate(cx, by);
  ctx.scale(scale, scale);

  // Chớp mắt tự nhiên 3.5s
  const blink = (Math.sin(t * 1.8) > 0.95);

  // Trễ pha cánh tiên 0.45 rad (15 độ)
  const wingPhase = t * 7.5 - 0.45;
  const wingFlap  = Math.sin(wingPhase) * 5.0;

  // Quán tính ăng-ten 0.25 rad
  const antPhase = breathPhase - 0.25;
  const antSwayX = Math.cos(antPhase) * 2.5;
  const antSwayY = Math.sin(antPhase) * 2.0;

  // Màu sắc chuẩn
  const C_FRESNEL     = "#F4FDF0";
  const C_BODY_BASE   = "#C8F0A6";
  const C_BODY_SHADOW = "#8FD065";
  const C_CREST_TIP   = "#3E8E2D";
  const C_CREST_DARK  = "#245C1A";
  const C_CREST_GLOW  = "#95E46A";
  const C_PANTS_DARK  = "#488A2E";
  const C_PANTS_LIGHT = "#6EBD4D";
  const C_LEGS_DARK   = "#3D7527";
  const C_LEGS_LIGHT  = "#64A648";
  const C_ANT_STEM    = "#B2E88F";
  const C_EYE_RING    = "#121812";
  const C_IRIS_DEEP   = "#023E8A";
  const C_IRIS_SAPPHIRE = "#0077B6";
  const C_IRIS_BRIGHT = "#00B4D8";
  const C_SPEC_SEC    = "#CAF0F8";
  const C_MOUTH       = "#1A3818";
  const C_STAR_GOLD   = "#FEF08A";
  const C_ANT_GLOW    = "#72EFDD";
  const C_MAGIC_SPORE = "#E0FF4F";

  // --- LỚP 1: BÓNG TIẾP XÚC MẶT SÀN CO GIÃN THEO ĐỘ CAO ---
  ctx.save();
  const shadowY = 46 - (by - cy);
  const sGrad = ctx.createRadialGradient(4, shadowY, 2, 4, shadowY, 24);
  sGrad.addColorStop(0, "rgba(5, 18, 7, 0.85)");
  sGrad.addColorStop(0.6, "rgba(10, 32, 14, 0.45)");
  sGrad.addColorStop(1, "rgba(10, 32, 14, 0)");
  ctx.fillStyle = sGrad;
  ctx.beginPath();
  ctx.ellipse(4, shadowY, (22 - breathSin * 3.5) * sX, (6.5 - breathSin * 1.2), 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // --- LỚP 2: CÁNH TIÊN PHÍA SAU (Far Wing) ---
  ctx.save();
  ctx.shadowColor = "rgba(128, 222, 234, 0.6)";
  ctx.shadowBlur = 8;
  const wingGrad1 = ctx.createLinearGradient(6, -4, 32, -18 + wingFlap);
  wingGrad1.addColorStop(0, "rgba(224, 247, 250, 0.4)");
  wingGrad1.addColorStop(0.7, "rgba(167, 243, 208, 0.65)");
  wingGrad1.addColorStop(1, "rgba(128, 222, 234, 0.85)");
  ctx.fillStyle = wingGrad1;
  ctx.beginPath();
  ctx.moveTo(6, -4);
  ctx.quadraticCurveTo(20, -18 + wingFlap, 32, -18 + wingFlap);
  ctx.quadraticCurveTo(24, -6 + wingFlap * 0.7, 18, 4);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = "rgba(244, 253, 240, 0.8)";
  ctx.lineWidth = 1.2;
  ctx.stroke();
  ctx.restore();

  // --- LỚP 3: CÁNH TAY SAU (Far Arm) ---
  ctx.save();
  ctx.fillStyle = C_BODY_BASE;
  ctx.beginPath();
  ctx.moveTo(-10, 7); ctx.lineTo(-8, 3); ctx.lineTo(-26, -2);
  ctx.closePath();
  ctx.fill();
  [-5, -2, 1].forEach((offY, i) => {
    ctx.beginPath();
    ctx.arc(-27 - (i === 1 ? 2 : 0), -2 + offY, 1.3, 0, Math.PI * 2);
    ctx.fill();
  });
  ctx.restore();

  // --- LỚP 4: ĐÔI CHÂN & BÀN CHÂN BO TRÒN DỄ THƯƠNG ---
  ctx.save();
  const legGrad = ctx.createLinearGradient(8, 18, 16, 34);
  legGrad.addColorStop(0, C_LEGS_DARK);
  legGrad.addColorStop(1, C_LEGS_LIGHT);
  ctx.fillStyle = legGrad;
  // Chân sau
  ctx.beginPath();
  ctx.roundRect(6, 18, 7 * sX, 12 * sY, 4);
  ctx.fill();
  // Chân trước
  ctx.beginPath();
  ctx.roundRect(12, 21, 8 * sX, 14 * sY, 4);
  ctx.fill();
  ctx.fillStyle = C_FRESNEL;
  ctx.beginPath();
  ctx.arc(16, 33, 1.5, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // --- LỚP 5: QUẦN LÁ XANH ĐẬM (Leaf Bloomers) ---
  ctx.save();
  const pantsGrad = ctx.createRadialGradient(2, 13, 2, 3, 14, 14);
  pantsGrad.addColorStop(0, C_PANTS_LIGHT);
  pantsGrad.addColorStop(0.8, C_PANTS_DARK);
  pantsGrad.addColorStop(1, "#2F5E1E");
  ctx.fillStyle = pantsGrad;
  ctx.beginPath();
  ctx.ellipse(3, 14, 13 * sX, 10 * sY, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // --- LỚP 6: THÂN BÚP HÀNH TÂY MỀM MẠI ---
  ctx.save();
  const bodyGrad = ctx.createRadialGradient(-1, 5, 2, 0, 6, 14);
  bodyGrad.addColorStop(0, C_FRESNEL);
  bodyGrad.addColorStop(0.5, C_BODY_BASE);
  bodyGrad.addColorStop(1, C_BODY_SHADOW);
  ctx.fillStyle = bodyGrad;
  ctx.beginPath();
  ctx.ellipse(0, 6, 11 * sX, 10 * sY, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // --- LỚP 7: CÁNH TIÊN PHÍA TRƯỚC (Near Wing) ---
  ctx.save();
  const frontFlap = Math.sin(wingPhase + 0.2) * 5.0;
  ctx.shadowColor = "rgba(114, 239, 221, 0.7)";
  ctx.shadowBlur = 10;
  const wingGrad2 = ctx.createLinearGradient(8, -2, 38, -12 + frontFlap);
  wingGrad2.addColorStop(0, "rgba(244, 253, 240, 0.5)");
  wingGrad2.addColorStop(0.6, "rgba(224, 247, 250, 0.7)");
  wingGrad2.addColorStop(1, "rgba(114, 239, 221, 0.9)");
  ctx.fillStyle = wingGrad2;
  ctx.beginPath();
  ctx.moveTo(8, -2);
  ctx.quadraticCurveTo(24, -14 + frontFlap, 38, -12 + frontFlap);
  ctx.quadraticCurveTo(28, 4 + frontFlap * 0.7, 16, 8);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = "#FFFFFF";
  ctx.lineWidth = 1.3;
  ctx.stroke();
  ctx.restore();

  // --- LỚP 8: CÁNH TAY TRƯỚC (Near Arm) ---
  ctx.save();
  ctx.fillStyle = C_BODY_BASE;
  ctx.beginPath();
  ctx.moveTo(6, 6); ctx.lineTo(8, 10); ctx.lineTo(32, 10);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = C_FRESNEL;
  ctx.lineWidth = 1;
  ctx.beginPath();
  ctx.moveTo(6, 6); ctx.lineTo(32, 9);
  ctx.stroke();
  [8, 10, 13].forEach((offY, i) => {
    ctx.beginPath();
    ctx.arc(33 + (i === 1 ? 3 : 1), offY, 1.3, 0, Math.PI * 2);
    ctx.fill();
  });
  ctx.restore();

  // --- LỚP 9: ĐẦU BÚP HÀNH TÂY & CHÓP RỪNG VƯƠN CAO ---
  const hy = -8;
  ctx.save();
  const headGrad = ctx.createRadialGradient(-5, hy - 4, 4, -3, hy, 24);
  headGrad.addColorStop(0, C_FRESNEL);
  headGrad.addColorStop(0.6, C_BODY_BASE);
  headGrad.addColorStop(1, C_BODY_SHADOW);
  ctx.fillStyle = headGrad;
  ctx.beginPath();
  ctx.ellipse(-3, hy, 22 * sX, 22 * sY, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.beginPath();
  ctx.arc(-16, hy + 8, 9 * sX, 0, Math.PI * 2);
  ctx.fill();

  // Chóp củ hành tây
  const crestGrad = ctx.createLinearGradient(0, hy - 14, 18, hy - 44);
  crestGrad.addColorStop(0, C_BODY_BASE);
  crestGrad.addColorStop(0.5, C_CREST_GLOW);
  crestGrad.addColorStop(0.85, C_CREST_TIP);
  crestGrad.addColorStop(1, C_CREST_DARK);
  ctx.fillStyle = crestGrad;
  ctx.beginPath();
  ctx.moveTo(-4, hy - 14);
  ctx.quadraticCurveTo(10, hy - 16, 16, hy - 44);
  ctx.quadraticCurveTo(18, hy - 20, 12, hy - 10);
  ctx.closePath();
  ctx.fill();

  // Gân lá chóp đầu
  ctx.strokeStyle = C_CREST_DARK;
  ctx.lineWidth = 1.1;
  ctx.beginPath();
  ctx.moveTo(16, hy - 44); ctx.quadraticCurveTo(12, hy - 28, 8, hy - 18);
  ctx.moveTo(16, hy - 44); ctx.quadraticCurveTo(14, hy - 26, 12, hy - 14);
  ctx.moveTo(16, hy - 44); ctx.quadraticCurveTo(16, hy - 30, 16, hy - 22);
  ctx.stroke();
  ctx.restore();

  // --- LỚP 10: CẶP ĂNG-TEN KÉP XANH NGỌC, CHÓP XANH LAM DẠ QUANG ---
  ctx.save();
  // Ăng-ten trái
  ctx.strokeStyle = C_ANT_STEM;
  ctx.lineWidth = 2.0;
  ctx.lineCap = "round";
  ctx.beginPath();
  ctx.moveTo(-11, hy - 12);
  ctx.quadraticCurveTo(-21 + antSwayX, hy - 24 + antSwayY, -18 + antSwayX * 1.4, hy - 42 + antSwayY);
  ctx.stroke();
  ctx.shadowColor = "#00B4D8";
  ctx.shadowBlur = 8;
  ctx.fillStyle = "#00B4D8";
  ctx.beginPath();
  ctx.arc(-18 + antSwayX * 1.4, hy - 42 + antSwayY, 3, 0, Math.PI * 2);
  ctx.fill();

  // Ăng-ten phải
  ctx.beginPath();
  ctx.moveTo(-1, hy - 14);
  ctx.quadraticCurveTo(4 + antSwayX, hy - 26 + antSwayY, 1 + antSwayX * 1.4, hy - 46 + antSwayY);
  ctx.stroke();
  ctx.beginPath();
  ctx.arc(1 + antSwayX * 1.4, hy - 46 + antSwayY, 4, 0, Math.PI * 2);
  ctx.fill();
  ctx.fillStyle = "#FFFFFF";
  ctx.beginPath();
  ctx.arc(1 + antSwayX * 1.4, hy - 46 + antSwayY, 1.2, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // --- LỚP 11: MÁ HỒNG ĐÀO TÁN MỊN & NỤ CƯỜI TÍ HON ---
  ctx.save();
  ctx.fillStyle = "rgba(255, 170, 166, 0.65)";
  ctx.beginPath();
  ctx.ellipse(-19, hy + 9, 4.5, 3, 0, 0, Math.PI * 2);
  ctx.ellipse(6, hy + 12, 5.5, 3.2, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = C_MOUTH;
  ctx.lineWidth = 1.2;
  ctx.beginPath();
  ctx.arc(-11, hy + 15, 3, 0.2, Math.PI * 0.9);
  ctx.stroke();
  ctx.restore();

  // --- LỚP 12: ĐÔI MẮT PHA LÊ CHIẾM 35% KHUÔN MẶT VIỀN ĐEN SẮC NÉT ---
  const exL = -17, eyL = hy + 3;
  const exR = -4, eyR = hy + 6;

  if (blink) {
    ctx.strokeStyle = C_EYE_RING;
    ctx.lineWidth = 2.4;
    ctx.beginPath();
    ctx.arc(exL, eyL + 2, 5, 0.2, Math.PI * 0.85);
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(exR, eyR + 3, 8, 0.2, Math.PI * 0.85);
    ctx.stroke();
  } else {
    // Mắt trái
    ctx.save();
    ctx.fillStyle = C_EYE_RING;
    ctx.beginPath(); ctx.ellipse(exL, eyL, 6, 12, 0, 0, Math.PI * 2); ctx.fill();
    const eyeLGrad = ctx.createLinearGradient(exL, eyL - 10, exL, eyL + 10);
    eyeLGrad.addColorStop(0, C_IRIS_DEEP);
    eyeLGrad.addColorStop(0.5, C_IRIS_SAPPHIRE);
    eyeLGrad.addColorStop(1, C_IRIS_BRIGHT);
    ctx.fillStyle = eyeLGrad;
    ctx.beginPath(); ctx.ellipse(exL, eyL, 4, 10, 0, 0, Math.PI * 2); ctx.fill();
    ctx.fillStyle = "#FFFFFF";
    ctx.beginPath(); ctx.arc(exL - 1, eyL - 3, 1.5, 0, Math.PI * 2); ctx.fill();
    ctx.restore();

    // Mắt phải (35% diện tích mặt)
    ctx.save();
    ctx.fillStyle = C_EYE_RING;
    ctx.beginPath(); ctx.ellipse(exR, eyR, 11, 16, 0.05, 0, Math.PI * 2); ctx.fill();
    const eyeRGrad = ctx.createRadialGradient(exR - 2, eyR - 2, 1, exR, eyR + 2, 14);
    eyeRGrad.addColorStop(0, C_IRIS_BRIGHT);
    eyeRGrad.addColorStop(0.5, C_IRIS_SAPPHIRE);
    eyeRGrad.addColorStop(0.9, C_IRIS_DEEP);
    eyeRGrad.addColorStop(1, "#051622");
    ctx.fillStyle = eyeRGrad;
    ctx.beginPath(); ctx.ellipse(exR, eyR, 9, 14, 0.05, 0, Math.PI * 2); ctx.fill();

    // Vệt trăng khuyết caustic
    ctx.fillStyle = "rgba(144, 224, 239, 0.85)";
    ctx.beginPath(); ctx.ellipse(exR, eyR + 6, 6, 4, 0, 0, Math.PI * 2); ctx.fill();

    // Đồng tử sapphire sâu
    ctx.fillStyle = "#031526";
    ctx.beginPath(); ctx.ellipse(exR - 1, eyR - 1, 5, 8, 0.05, 0, Math.PI * 2); ctx.fill();

    // 3 ĐIỂM BẮT SÁNG PHA LÊ
    // 1. Đốm chính 2x2 góc 10h
    ctx.fillStyle = "#FFFFFF";
    ctx.shadowColor = "#FFFFFF";
    ctx.shadowBlur = 4;
    ctx.beginPath(); ctx.arc(exR - 3.5, eyR - 4.5, 2.2, 0, Math.PI * 2); ctx.fill();
    // 2. Đốm phụ 1x1 góc 4h
    ctx.fillStyle = C_SPEC_SEC;
    ctx.shadowBlur = 0;
    ctx.beginPath(); ctx.arc(exR + 2.5, eyR + 5.5, 1.2, 0, Math.PI * 2); ctx.fill();
    // 3. Vệt trăng khuyết sáng vi sợi
    ctx.strokeStyle = "rgba(255, 255, 255, 0.9)";
    ctx.lineWidth = 1.2;
    ctx.beginPath();
    ctx.arc(exR - 1, eyR + 6, 5, 0.4, Math.PI * 0.85);
    ctx.stroke();
    ctx.restore();
  }

  // --- LỚP 13: BỤI BÀO TỬ THẦN THOẠI ✨ ---
  ctx.save();
  const drawSpore = (x, y, col) => {
    ctx.fillStyle = col;
    ctx.shadowColor = col;
    ctx.shadowBlur = 6;
    ctx.beginPath(); ctx.arc(x, y, 1.5, 0, Math.PI * 2); ctx.fill();
  };
  drawSpore(-23, 16, C_STAR_GOLD);
  drawSpore(29, -28, C_ANT_GLOW);
  drawSpore(-18, -22, C_MAGIC_SPORE);
  drawSpore(22, 26, C_MAGIC_SPORE);
  ctx.restore();

  ctx.restore();
}
"""
    }
}

target_file = os.path.join("data", "session1_agent1_celebi.json")
with open(target_file, "w", encoding="utf-8") as f:
    json.dump(celebi_data, f, ensure_ascii=False, indent=2)

print(f"Successfully generated: {target_file}")
