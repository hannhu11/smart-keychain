# -*- coding: utf-8 -*-
"""
Generator script for data/agent3_fantasy_beasts.json
Produced by Fantasy Bestiary Engineer (Antigravity Agent 3)
"""
import json
import os

beasts = [
    {
        "id": 0,
        "codename": "LOP_EARED_GOLDEN_GUARDIAN",
        "name_vi": "Thần Thú Tai Dài Rừng Thiêng",
        "name_en": "Lop-Eared Golden Guardian",
        "archetype": "Thần Thú Hộ Mệnh Rừng Thiêng (Ancient Forest Colossus Guardian)",
        "source_art_reference": "download (00).jpg",
        "category": "Thần Thú & Linh Thú Rừng Thiêng",
        "mythology_lore": "Vị Thần Thú hộ vệ nghìn năm của Rừng Già Nguyên Sinh (Ancient Sacred Grove). Mang thân hình tròn trĩu vững chãi như bàn thạch ngàn năm nhưng được bao phủ bởi lớp lông tơ vàng óng ấm áp như vạt nắng sớm rọi qua tán cổ thụ. Đôi tai rủ dài chạm sàn vạt rộng như dải lụa hoàng gia, dệt nên những hoa văn thổ cẩm linh thiêng của tộc người rừng cổ đại với sắc ngọc lam và thạch anh tím. Mỗi bước đi uyển chuyển của thần thú làm bừng nở những đóa ngọc lan bích sắc dưới thảm cỏ rừng già.",
        "palette": {
            "primary_hex": "#F7DC88",
            "primary_name": "Warm Golden Fur",
            "rgb565_primary": "0xF6EA",
            "secondary_hex": "#C99A3A",
            "secondary_name": "Honey Amber Fur Shadow",
            "rgb565_secondary": "0xCCE7",
            "highlight_hex": "#FFF8DB",
            "highlight_name": "Sunlit Cream Fur Highlight",
            "rgb565_highlight": "0xFFFB",
            "occlusion_hex": "#8F641B",
            "occlusion_name": "Deep Fur Occlusion",
            "rgb565_occlusion": "0x8B23",
            "tribal_cyan_hex": "#06B6D4",
            "tribal_cyan_name": "Sacred Turquoise Jade",
            "rgb565_tribal_cyan": "0x05BA",
            "tribal_purple_hex": "#7C3AED",
            "tribal_purple_name": "Royal Amethyst Violet",
            "rgb565_tribal_purple": "0x79DD",
            "tribal_gold_hex": "#FBBF24",
            "tribal_gold_name": "Solar Gold Accent",
            "rgb565_tribal_gold": "0xFDE4",
            "eye_sapphire_deep_hex": "#0F2A4A",
            "rgb565_eye_deep": "0x0949",
            "eye_sapphire_mid_hex": "#1D6BB8",
            "rgb565_eye_mid": "0x1B57",
            "eye_sapphire_bright_hex": "#60A5FA",
            "rgb565_eye_bright": "0x653F"
        },
        "breathing_squash_stretch_specs": {
            "frequency_hz": 0.32,
            "squash_stretch_percent": 5.0,
            "vertical_scale_formula": "1.0 + 0.05 * sin(t * 2.0)",
            "horizontal_volume_formula": "1.0 - 0.025 * sin(t * 2.0)",
            "ear_lag_rad": 0.55,
            "ear_lag_formula": "sin(t * 2.0 - 0.55) * 4.0",
            "tail_lag_rad": 0.85,
            "tail_lag_formula": "sin(t * 2.0 - 0.85) * 6.0",
            "secondary_inertia_damping": 0.88
        },
        "eye_specs": {
            "eye_type": "sapphire_crystal_orb",
            "blink_interval_ms": 3800,
            "blink_duration_ms": 140,
            "pupil_shape": "vertical_crystal_drop",
            "catchlight_3points": [
                {
                    "point_id": 1,
                    "name": "Primary Diamond Specular",
                    "dx": -2,
                    "dy": -3,
                    "radius_px": 2.0,
                    "color_hex": "#FFFFFF",
                    "rgb565": "0xFFFF",
                    "role": "Direct celestial sunlight reflection on upper cornea"
                },
                {
                    "point_id": 2,
                    "name": "Secondary Soft Glint",
                    "dx": 2,
                    "dy": 1,
                    "radius_px": 1.0,
                    "color_hex": "#BAE6FD",
                    "rgb565": "0xBDF7",
                    "role": "Ambient forest canopy shimmer on iris edge"
                },
                {
                    "point_id": 3,
                    "name": "Tertiary Caustic Bounce",
                    "dx": -1,
                    "dy": 2,
                    "radius_px": 0.8,
                    "color_hex": "#93C5FD",
                    "rgb565": "0x963F",
                    "role": "Subsurface crystal iris caustic bounce light"
                }
            ],
            "pupil_tracking_range_px": {"max_x": 3, "max_y": 2}
        },
        "volumetric_3d_specs": {
            "mesh_topology": "Pear-shaped monolithic ellipsoid with 4 stout columnar pillars and draping silk ear banners",
            "light_direction": [-0.5, -0.7, 0.5],
            "ambient_occlusion_passes": [
                "Belly-to-floor ground contact shadow (rx=38, ry=10, cy+46)",
                "Inner ear drapery occlusion shadow behind neck",
                "Columnar front leg inner groin cleft line"
            ],
            "specular_power": 16.0,
            "rim_light_color": "0xFFFB"
        },
        "secondary_motion_specs": {
            "ear_drapery_physics": "Double sinusoidal ripple simulating silk banner weight resting on ground",
            "tail_spiral_physics": "Harmonic spiral curl deflection with phase delay phi=0.85 rad",
            "squash_stretch_body": "True volume-preserving squash (Y expand 5% -> X contract 2.5%)"
        },
        "visual_breakdown": [
            "Thân hình tròn trĩu vững chãi như quả lê ấm áp, phủ lông tơ vàng mật ong",
            "4 chân cột trụ múp míp với ngón chân mềm mại bám đất rừng thiêng",
            "Đôi tai rủ dài chạm sàn vạt rộng như dải lụa hoàng gia, uốn lượn cong vút ở chóp tai",
            "Họa tiết thổ cẩm bộ tộc cổ: dải zíc zắc tím thạch anh (#7C3AED), ngọc lam (#06B6D4) và hình thoi hoàng kim (#FBBF24)",
            "Đuôi xoắn ốc thon dài uyển chuyển phía sau với đường cong Fibonacci",
            "Mặt cười hình chữ w (^w^) hiền từ, 2 mắt bích ngọc sapphire lấp lánh 3 điểm sáng pha lê"
        ],
        "quote_vi": "Vạn dặm rừng thiêng, bước chân anh qua đều nở hoa vì có em.",
        "shader_effect": "Sunlit Forest Dappled Shimmer & Floor Blossom Drift",
        "cpp_render_snippet": """void drawLopEaredGuardian(ScaledCanvas* spr, int cx, int cy, float t) {
  // 1. Nhịp thở Squash & Stretch 5%
  float breathY = 1.0f + 0.05f * sinf(t * 2.0f);
  float breathX = 1.0f - 0.025f * sinf(t * 2.0f);
  float earLag = sinf(t * 2.0f - 0.55f) * 4.0f;
  float tailLag = sinf(t * 2.0f - 0.85f) * 6.0f;
  bool blink = (fmodf(t, 3.8f) < 0.14f);

  // 2. Bóng tiếp xúc mặt đất (Ground contact shadow)
  spr->fillEllipse(cx, cy + 45, (int)(38 * breathX), 8, 0x18C3);

  // 3. Đuôi xoắn ốc (Spiral Golden Tail) với độ trễ pha
  int tx0 = cx - 22, ty0 = cy + 24 + (int)(tailLag * 0.4f);
  int tx1 = cx - 36, ty1 = cy + 34 + (int)(tailLag * 0.8f);
  int tx2 = cx - 44, ty2 = cy + 42 + (int)tailLag;
  int tx3 = cx - 34, ty3 = cy + 48 + (int)(tailLag * 0.7f);
  int tx4 = cx - 24, ty4 = cy + 42 + (int)(tailLag * 0.4f);
  spr->drawLine(tx0, ty0, tx1, ty1, 0xCCE7);
  spr->drawLine(tx1, ty1, tx2, ty2, 0xF6EA);
  spr->drawLine(tx2, ty2, tx3, ty3, 0xF6EA);
  spr->drawLine(tx3, ty3, tx4, ty4, 0xFFFB);
  spr->fillCircle(tx4, ty4, 3, 0xFFFB);

  // 4. Chân sau (Hind columnar legs - shadow layer)
  spr->fillRoundRect(cx - 28, cy + 18, 14, 26, 6, 0xCCE7);
  spr->fillRoundRect(cx + 14, cy + 18, 14, 26, 6, 0xCCE7);

  // 5. Thân tròn ấm áp (Volumetric Pear Body)
  spr->fillEllipse(cx, cy + 14, (int)(32 * breathX), (int)(34 * breathY), 0xF6EA);
  spr->fillEllipse(cx, cy + 24, (int)(28 * breathX), (int)(18 * breathY), 0xCCE7);
  spr->fillEllipse(cx, cy + 4, (int)(20 * breathX), (int)(22 * breathY), 0xFFFB);

  // 6. Chân trước (Front columnar legs)
  spr->fillRoundRect(cx - 16, cy + 16, 12, 28, 5, 0xF6EA);
  spr->fillRoundRect(cx + 4, cy + 16, 12, 28, 5, 0xF6EA);
  spr->drawFastVLine(cx - 12, cy + 38, 5, 0x8B23);
  spr->drawFastVLine(cx + 8, cy + 38, 5, 0x8B23);

  // 7. Đầu tròn (Head Dome)
  spr->fillEllipse(cx, cy - 18, (int)(24 * breathX), (int)(22 * breathY), 0xF6EA);
  spr->fillEllipse(cx, cy - 18, 16, 14, 0xFFFB);

  // 8. Đôi tai rủ dài chạm sàn với hoa văn thổ cẩm (Brocade Lop Ears)
  for (int side = -1; side <= 1; side += 2) {
    float lag = (side == -1) ? earLag : -earLag * 0.7f;
    int ex0 = cx + side * 14, ey0 = cy - 28;
    int ex1 = cx + side * 38 + (int)lag, ey1 = cy - 8;
    int ex2 = cx + side * 48 + (int)(lag * 1.4f), ey2 = cy + 20;
    int ex3 = cx + side * 54 + (int)(lag * 1.8f), ey3 = cy + 44; // chạm sàn
    int ex4 = cx + side * 66 + (int)(lag * 2.1f), ey4 = cy + 36; // lượn cong lên

    // Dải tai chính
    spr->drawLine(ex0, ey0, ex1, ey1, 0xF6EA);
    spr->drawLine(ex1, ey1, ex2, ey2, 0xF6EA);
    spr->drawLine(ex2, ey2, ex3, ey3, 0xF6EA);
    spr->drawLine(ex3, ey3, ex4, ey4, 0xFFFB);
    spr->fillCircle(ex1, ey1, 9, 0xF6EA);
    spr->fillCircle(ex2, ey2, 8, 0xF6EA);
    spr->fillCircle(ex3, ey3, 7, 0xF6EA);
    spr->fillCircle(ex4, ey4, 5, 0xFFFB);

    // Hoa văn thổ cẩm: Dải tím thạch anh (#7C3AED)
    spr->fillTriangle(ex1 - side*3, ey1 - 4, ex1 + side*5, ey1, ex1 - side*3, ey1 + 4, 0x79DD);
    spr->fillTriangle(ex2 - side*2, ey2 - 4, ex2 + side*4, ey2, ex2 - side*2, ey2 + 4, 0x79DD);

    // Họa tiết ngọc lam (#06B6D4) & vàng (#FBBF24)
    spr->drawCircle(ex1 + side*2, ey1, 3, 0x05BA);
    spr->drawCircle(ex2 + side*1, ey2, 2, 0x05BA);
    spr->drawPixel(ex1 + side*2, ey1, 0xFDE4);
    spr->drawPixel(ex2 + side*1, ey2, 0xFDE4);
  }

  // 9. Mắt Bích Ngọc Sapphire (3 Catchlights Pha Lê)
  for (int side = -1; side <= 1; side += 2) {
    int eyeX = cx + side * 12, eyeY = cy - 20;
    if (blink) {
      spr->drawFastHLine(eyeX - 4, eyeY, 8, 0x0949);
    } else {
      spr->fillEllipse(eyeX, eyeY, 5, 7, 0x0949); // Hốc mắt sâu
      spr->fillEllipse(eyeX, eyeY, 4, 6, 0x1B57); // Thể thủy tinh sapphire
      spr->fillEllipse(eyeX, eyeY + 1, 3, 3, 0x653F); // Vòm sáng lam ngọc
      // 3 Điểm sáng pha lê
      spr->fillCircle(eyeX - 2, eyeY - 3, 2, 0xFFFF); // Điểm 1: Tâm quang chính
      spr->drawPixel(eyeX + 2, eyeY + 1, 0xFFFF);     // Điểm 2: Ánh tán xạ góc
      spr->drawPixel(eyeX - 1, eyeY + 2, 0x963F);     // Điểm 3: Phản quang đáy
    }
  }

  // 10. Miệng cười w-smile hiền từ (^w^)
  spr->drawPixel(cx - 3, cy - 13, 0x8B23);
  spr->drawPixel(cx - 2, cy - 12, 0x8B23);
  spr->drawPixel(cx - 1, cy - 12, 0x8B23);
  spr->drawPixel(cx,     cy - 13, 0x8B23);
  spr->drawPixel(cx + 1, cy - 12, 0x8B23);
  spr->drawPixel(cx + 2, cy - 12, 0x8B23);
  spr->drawPixel(cx + 3, cy - 13, 0x8B23);
}""",
        "js_render_snippet": """function drawLopEaredGuardian(ctx, cx, cy, scale, t) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.scale(scale, scale);

  const breathY = 1.0 + 0.05 * Math.sin(t * 2.0);
  const breathX = 1.0 - 0.025 * Math.sin(t * 2.0);
  const earLag = Math.sin(t * 2.0 - 0.55) * 4.0;
  const tailLag = Math.sin(t * 2.0 - 0.85) * 6.0;
  const blink = (t % 3.8 < 0.14);

  // 1. Bóng tiếp xúc mặt đất
  ctx.fillStyle = 'rgba(24, 28, 36, 0.35)';
  ctx.beginPath();
  ctx.ellipse(0, 45, 38 * breathX, 8, 0, 0, Math.PI * 2);
  ctx.fill();

  // 2. Đuôi xoắn ốc (Fibonacci Spiral Tail)
  ctx.strokeStyle = '#F7DC88';
  ctx.lineWidth = 4.5;
  ctx.lineCap = 'round';
  ctx.beginPath();
  ctx.moveTo(-22, 24 + tailLag * 0.4);
  ctx.bezierCurveTo(-38, 32 + tailLag * 0.8, -46, 44 + tailLag, -34, 48 + tailLag * 0.7);
  ctx.bezierCurveTo(-24, 50 + tailLag * 0.5, -22, 40, -28, 36);
  ctx.stroke();

  // 3. Chân sau (Hind legs shadow)
  ctx.fillStyle = '#C99A3A';
  ctx.beginPath();
  ctx.roundRect(-28, 18, 14, 26, 6);
  ctx.roundRect(14, 18, 14, 26, 6);
  ctx.fill();

  // 4. Thân hình vòm hạt đậu ấm áp
  ctx.save();
  ctx.scale(breathX, breathY);
  let bodyGrad = ctx.createRadialGradient(0, 8, 8, 0, 14, 34);
  bodyGrad.addColorStop(0, '#FFF8DB');
  bodyGrad.addColorStop(0.6, '#F7DC88');
  bodyGrad.addColorStop(1, '#C99A3A');
  ctx.fillStyle = bodyGrad;
  ctx.beginPath();
  ctx.ellipse(0, 14, 32, 34, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 5. Chân trước (Front columnar legs)
  ctx.fillStyle = '#F7DC88';
  ctx.beginPath();
  ctx.roundRect(-16, 16, 12, 28, 5);
  ctx.roundRect(4, 16, 12, 28, 5);
  ctx.fill();
  ctx.strokeStyle = '#8F641B';
  ctx.lineWidth = 1.2;
  ctx.beginPath();
  ctx.moveTo(-12, 38); ctx.lineTo(-12, 43);
  ctx.moveTo(8, 38); ctx.lineTo(8, 43);
  ctx.stroke();

  // 6. Đầu vòm (Head Dome)
  ctx.save();
  ctx.scale(breathX, breathY);
  let headGrad = ctx.createRadialGradient(0, -20, 6, 0, -18, 24);
  headGrad.addColorStop(0, '#FFF8DB');
  headGrad.addColorStop(0.7, '#F7DC88');
  headGrad.addColorStop(1, '#DDA336');
  ctx.fillStyle = headGrad;
  ctx.beginPath();
  ctx.ellipse(0, -18, 24, 22, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 7. Đôi tai rủ dài chạm sàn với hoa văn thổ cẩm
  for (let side of [-1, 1]) {
    let lag = (side === -1) ? earLag : -earLag * 0.7;
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(side * 14, -28);
    ctx.bezierCurveTo(side * 38 + lag, -8, side * 48 + lag * 1.4, 20, side * 54 + lag * 1.8, 44);
    ctx.quadraticCurveTo(side * 66 + lag * 2.1, 46, side * 68 + lag * 2.1, 34);
    ctx.bezierCurveTo(side * 52 + lag * 1.5, 22, side * 42 + lag, 0, side * 18, -26);
    ctx.closePath();

    let earGrad = ctx.createLinearGradient(side * 14, -28, side * 68, 40);
    earGrad.addColorStop(0, '#F7DC88');
    earGrad.addColorStop(0.5, '#FFF0B3');
    earGrad.addColorStop(0.85, '#E6B044');
    earGrad.addColorStop(1, '#FFF8DB');
    ctx.fillStyle = earGrad;
    ctx.fill();
    ctx.strokeStyle = '#8F641B';
    ctx.lineWidth = 1.0;
    ctx.stroke();

    // Họa tiết thổ cẩm bộ tộc: Vải tím & Ngọc lam
    let mx1 = side * 38 + lag, my1 = -6;
    let mx2 = side * 48 + lag * 1.4, my2 = 18;

    // Tam giác zíc zắc tím Amethyst
    ctx.fillStyle = '#7C3AED';
    ctx.beginPath();
    ctx.moveTo(mx1 - side * 4, my1 - 6);
    ctx.lineTo(mx1 + side * 6, my1);
    ctx.lineTo(mx1 - side * 4, my1 + 6);
    ctx.closePath();
    ctx.fill();

    ctx.beginPath();
    ctx.moveTo(mx2 - side * 4, my2 - 6);
    ctx.lineTo(mx2 + side * 6, my2);
    ctx.lineTo(mx2 - side * 4, my2 + 6);
    ctx.closePath();
    ctx.fill();

    // Hạt cườm ngọc lam & thoi vàng
    ctx.fillStyle = '#06B6D4';
    ctx.beginPath();
    ctx.arc(mx1 + side * 2, my1, 3, 0, Math.PI * 2);
    ctx.arc(mx2 + side * 2, my2, 2.5, 0, Math.PI * 2);
    ctx.fill();

    ctx.fillStyle = '#FBBF24';
    ctx.fillRect(mx1 + side * 1, my1 - 1, 2, 2);
    ctx.fillRect(mx2 + side * 1, my2 - 1, 2, 2);
    ctx.restore();
  }

  // 8. Mắt Bích Ngọc Sapphire với 3 điểm sáng pha lê
  for (let side of [-1, 1]) {
    let eyeX = side * 12, eyeY = -20;
    if (blink) {
      ctx.strokeStyle = '#0F2A4A';
      ctx.lineWidth = 2.2;
      ctx.beginPath();
      ctx.moveTo(eyeX - 4, eyeY);
      ctx.lineTo(eyeX + 4, eyeY);
      ctx.stroke();
    } else {
      // Hốc mắt & tròng cầu Sapphire
      let eyeGrad = ctx.createRadialGradient(eyeX, eyeY - 2, 1, eyeX, eyeY, 6);
      eyeGrad.addColorStop(0, '#60A5FA');
      eyeGrad.addColorStop(0.5, '#1D6BB8');
      eyeGrad.addColorStop(1, '#0F2A4A');
      ctx.fillStyle = eyeGrad;
      ctx.beginPath();
      ctx.ellipse(eyeX, eyeY, 5, 7, 0, 0, Math.PI * 2);
      ctx.fill();

      // 3 Điểm sáng phản quang pha lê
      ctx.fillStyle = '#FFFFFF';
      ctx.beginPath();
      ctx.arc(eyeX - 2, eyeY - 3, 2.0, 0, Math.PI * 2); // Điểm 1: Lóa đỉnh
      ctx.fill();

      ctx.fillStyle = '#BAE6FD';
      ctx.beginPath();
      ctx.arc(eyeX + 2, eyeY + 1, 1.0, 0, Math.PI * 2); // Điểm 2: Ánh góc
      ctx.fill();

      ctx.fillStyle = '#93C5FD';
      ctx.beginPath();
      ctx.arc(eyeX - 1, eyeY + 2, 0.8, 0, Math.PI * 2); // Điểm 3: Phản xạ đáy
      ctx.fill();
    }
  }

  // 9. Nụ cười w-smile hiền từ (^w^)
  ctx.strokeStyle = '#8F641B';
  ctx.lineWidth = 1.5;
  ctx.beginPath();
  ctx.moveTo(-4, -13);
  ctx.quadraticCurveTo(-2, -11, 0, -13);
  ctx.quadraticCurveTo(2, -11, 4, -13);
  ctx.stroke();

  ctx.restore();
}"""
    },
    {
        "id": 1,
        "codename": "LUMININE_SNOW_LIGHT_FOX",
        "name_vi": "Cáo Tuyết Ánh Sáng Luminine",
        "name_en": "Luminine Frostlight Aurora Fox",
        "korean_name": "루미나인 (빛의 여우)",
        "archetype": "Linh Hồ Băng Tuyết & Ánh Sáng (Aurora Glacial Fox)",
        "source_art_reference": "✨ 판타지 동물 도감 (루미나인)",
        "category": "Thần Thú & Linh Thú Rừng Thiêng",
        "mythology_lore": "Linh thú tuyết sinh ra nơi đỉnh núi Băng Phong ngàn năm. Khoác lên mình bộ lông trắng muốt như tuyết đầu mùa, tỏa ra luồng cực quang xanh ngọc dịu mát. Trước trán đính viên đá Lam Ngọc phát quang (Sapphire Sigil) tích tụ tinh hoa nhật nguyệt, chiếc đuôi ánh sáng bồng bềnh tựa dải mây soi sáng khắp lối đi trong đêm cực hàn.",
        "palette": {
            "primary_hex": "#FFFFFF",
            "primary_name": "Pure Snow White",
            "rgb565_primary": "0xFFFF",
            "secondary_hex": "#E0F2FE",
            "secondary_name": "Icy Glaze Sky Tint",
            "rgb565_secondary": "0xE79F",
            "accent_hex": "#38BDF8",
            "accent_name": "Electric Aurora Blue",
            "rgb565_accent": "0x3DFE",
            "shadow_hex": "#0284C7",
            "shadow_name": "Deep Glacial Shadow",
            "rgb565_shadow": "0x0438",
            "sigil_cyan_hex": "#00F0FF",
            "sigil_cyan_name": "Radiant Forehead Cyan Sigil",
            "rgb565_sigil_cyan": "0x077F",
            "aurora_violet_hex": "#C4B5FD",
            "aurora_violet_name": "Pastel Lavender Inner Ear",
            "rgb565_aurora_violet": "0xC5BF",
            "eye_sapphire_hex": "#0369A1",
            "rgb565_eye_sapphire": "0x0354"
        },
        "breathing_squash_stretch_specs": {
            "frequency_hz": 0.35,
            "squash_stretch_percent": 5.0,
            "vertical_scale_formula": "1.0 + 0.05 * sin(t * 2.2)",
            "horizontal_volume_formula": "1.0 - 0.025 * sin(t * 2.2)",
            "ear_lag_rad": 0.40,
            "ear_lag_formula": "sin(t * 2.2 - 0.40) * 3.0",
            "tail_lag_rad": 0.65,
            "tail_lag_formula": "sin(t * 2.2 - 0.65) * 8.0",
            "secondary_inertia_damping": 0.90
        },
        "eye_specs": {
            "eye_type": "ice_crystal_almond",
            "blink_interval_ms": 3600,
            "blink_duration_ms": 130,
            "pupil_shape": "radiant_rhombus_diamond",
            "catchlight_3points": [
                {
                    "point_id": 1,
                    "name": "Diamond Aurora Flare",
                    "dx": -2,
                    "dy": -3,
                    "radius_px": 2.0,
                    "color_hex": "#FFFFFF",
                    "rgb565": "0xFFFF",
                    "role": "Direct celestial star glint on glacial cornea"
                },
                {
                    "point_id": 2,
                    "name": "Ice Shimmer Point",
                    "dx": 2,
                    "dy": 1,
                    "radius_px": 1.0,
                    "color_hex": "#FFFFFF",
                    "rgb565": "0xFFFF",
                    "role": "Secondary crisp glacial shine"
                },
                {
                    "point_id": 3,
                    "name": "Glacial Caustic Rim",
                    "dx": -1,
                    "dy": 2,
                    "radius_px": 0.8,
                    "color_hex": "#E0F2FE",
                    "rgb565": "0xE79F",
                    "role": "Bottom eyelid ice bounce light"
                }
            ],
            "pupil_tracking_range_px": {"max_x": 4, "max_y": 3}
        },
        "volumetric_3d_specs": {
            "mesh_topology": "Sitting fox silhouette with fluffy cloud plume tail and high triangular pointed ears",
            "light_direction": [-0.6, -0.8, 0.6],
            "ambient_occlusion_passes": [
                "Tail base behind body occlusion (cy+20)",
                "Neck fur collar depth layering",
                "Inner ear tuft shadow"
            ],
            "specular_power": 24.0,
            "rim_light_color": "0x077F"
        },
        "secondary_motion_specs": {
            "tail_aurora_drift": "Trailing sinusoidal wave with floating stardust sparkle emissions",
            "ear_twitch_physics": "Subtle alertness jitter added to smooth head breathing",
            "particle_system": "6 floating stardust sparks with oscillating alpha around tail tip"
        },
        "visual_breakdown": [
            "Bộ lông tuyết trắng muốt tinh khiết, phủ bóng đổ lam ngọc băng giá (#E0F2FE, #38BDF8)",
            "Đôi tai cáo dựng nhọn kiêu hãnh với sắc tím cực quang pastel (#C4B5FD) bên trong",
            "Ấn ký lam ngọc 4 cánh chữ thập phát quang rực rỡ giữa trán (#00F0FF)",
            "Mặt dây chuyền lam ngọc hình giọt nước buông nhẹ trước ngực",
            "Chiếc đuôi hồ ly ánh sáng bồng bềnh uốn lượn như mây bão tuyết, phát ra bụi sao lấp lánh",
            "Đôi mắt ngọc bích băng thanh khiết với 3 điểm sáng pha lê vĩnh cửu"
        ],
        "quote_vi": "Giữa đêm đông lạnh giá nhất, ánh sáng của em sưởi ấm trái tim anh.",
        "shader_effect": "Glacial Aurora Shimmer & Floating Stardust Embers",
        "cpp_render_snippet": """void drawLuminineSnowFox(ScaledCanvas* spr, int cx, int cy, float t) {
  // 1. Nhịp thở Squash & Stretch 5%
  float breathY = 1.0f + 0.05f * sinf(t * 2.2f);
  float breathX = 1.0f - 0.025f * sinf(t * 2.2f);
  float earLag = sinf(t * 2.2f - 0.40f) * 3.0f;
  float tailLag = sinf(t * 2.2f - 0.65f) * 8.0f;
  bool blink = (fmodf(t, 3.6f) < 0.13f);

  // 2. Chiếc đuôi ánh sáng bồng bềnh (Luminous Aurora Cloud Tail)
  int tx = cx - 28 + (int)tailLag;
  int ty = cy - 4;
  spr->fillCircle(tx + 4, ty + 16, 12, 0xE79F); // Gốc đuôi tuyết
  spr->fillCircle(tx - 4, ty + 6, 16, 0x3DFE);  // Thân đuôi lam ngọc
  spr->fillCircle(tx - 6, ty - 8, 14, 0x077F);  // Bụng đuôi cực quang
  spr->fillCircle(tx + 4, ty - 18, 10, 0xFFFF); // Chóp đuôi phát quang trắng

  // Bụi sao lấp lánh quanh chóp đuôi (Stardust Sparkles)
  for (int i = 0; i < 4; i++) {
    float a = t * 3.0f + i * 1.57f;
    int px = tx + (int)(cosf(a) * 16.0f);
    int py = ty - 12 + (int)(sinf(a) * 10.0f);
    spr->drawPixel(px, py, 0xFFFF);
    spr->drawPixel(px + 1, py, 0x077F);
  }

  // 3. Bóng tiếp xúc mặt đất
  spr->fillEllipse(cx, cy + 38, (int)(26 * breathX), 6, 0x18C3);

  // 4. Thân cáo tuyết (Snow Fox Torso)
  spr->fillEllipse(cx - 2, cy + 18, (int)(20 * breathX), (int)(22 * breathY), 0xE79F);
  spr->fillEllipse(cx + 2, cy + 6, (int)(16 * breathX), (int)(18 * breathY), 0xFFFF);

  // 5. Chân trước thon thả & đệm chân tuyết
  spr->fillRoundRect(cx - 10, cy + 18, 6, 20, 3, 0xFFFF);
  spr->fillRoundRect(cx + 4, cy + 18, 6, 20, 3, 0xFFFF);
  spr->fillCircle(cx - 7, cy + 37, 3, 0xE79F);
  spr->fillCircle(cx + 7, cy + 37, 3, 0xE79F);

  // 6. Đầu cáo hình nêm thanh thoát
  spr->fillEllipse(cx, cy - 16, (int)(19 * breathX), (int)(17 * breathY), 0xFFFF);
  // Má lông xòe hai bên
  spr->fillTriangle(cx - 18, cy - 12, cx - 10, cy - 18, cx - 10, cy - 8, 0xFFFF);
  spr->fillTriangle(cx + 18, cy - 12, cx + 10, cy - 18, cx + 10, cy - 8, 0xFFFF);

  // 7. Đôi tai cáo vểnh cao (Tall Arctic Fox Ears)
  for (int side = -1; side <= 1; side += 2) {
    int tipX = cx + side * 16 + (int)(earLag * 0.5f);
    int tipY = cy - 42;
    int b1x = cx + side * 6, b1y = cy - 24;
    int b2x = cx + side * 22, b2y = cy - 22;
    // Tai ngoài trắng muốt
    spr->fillTriangle(tipX, tipY, b1x, b1y, b2x, b2y, 0xFFFF);
    // Tai trong cực quang pastel tím-lam (#C4B5FD, #38BDF8)
    spr->fillTriangle(tipX, tipY + 4, b1x + side*2, b1y - 2, b2x - side*3, b2y - 1, 0xC5BF);
    spr->fillCircle(b1x + side*5, b1y - 4, 3, 0x3DFE);
  }

  // 8. Ấn ký Lam Ngọc 4 cánh chữ thập trước trán (Sapphire Cross Sigil)
  int sigY = cy - 26;
  spr->drawFastVLine(cx, sigY - 5, 11, 0x077F);
  spr->drawFastHLine(cx - 4, sigY, 9, 0x077F);
  spr->fillCircle(cx, sigY, 2, 0xFFFF);

  // Mắt dây chuyền giọt nước trước ngực
  spr->fillTriangle(cx, cy - 1, cx - 2, cy - 5, cx + 2, cy - 5, 0x077F);
  spr->drawPixel(cx, cy - 3, 0xFFFF);

  // 9. Mắt Lam Ngọc Pha Lê (3 Catchlights)
  for (int side = -1; side <= 1; side += 2) {
    int eyeX = cx + side * 10, eyeY = cy - 16;
    if (blink) {
      spr->drawFastHLine(eyeX - 3, eyeY, 7, 0x0354);
    } else {
      spr->fillEllipse(eyeX, eyeY, 4, 6, 0x0928); // Hốc mắt sâu
      spr->fillEllipse(eyeX, eyeY, 3, 5, 0x0354); // Tròng ngọc lam
      spr->fillCircle(eyeX, eyeY + 1, 2, 0x3DFE);  // Ánh vòm đáy
      // 3 Điểm sáng pha lê
      spr->fillCircle(eyeX - 1, eyeY - 2, 1, 0xFFFF); // Điểm 1: Tia cực quang đỉnh
      spr->drawPixel(eyeX + 1, eyeY, 0xFFFF);         // Điểm 2: Tinh thể phụ
      spr->drawPixel(eyeX, eyeY + 2, 0xE79F);         // Điểm 3: Phản xạ băng
    }
  }

  // 10. Mũi xinh & Nụ cười cáo nhỏ
  spr->drawPixel(cx, cy - 11, 0x0928);
  spr->drawPixel(cx - 1, cy - 9, 0x0438);
  spr->drawPixel(cx,     cy - 8, 0x0438);
  spr->drawPixel(cx + 1, cy - 9, 0x0438);
}""",
        "js_render_snippet": """function drawLuminineSnowFox(ctx, cx, cy, scale, t) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.scale(scale, scale);

  const breathY = 1.0 + 0.05 * Math.sin(t * 2.2);
  const breathX = 1.0 - 0.025 * Math.sin(t * 2.2);
  const earLag = Math.sin(t * 2.2 - 0.40) * 3.0;
  const tailLag = Math.sin(t * 2.2 - 0.65) * 8.0;
  const blink = (t % 3.6 < 0.13);

  // 1. Chiếc đuôi ánh sáng bồng bềnh (Luminous Aurora Cloud Tail)
  let tx = -28 + tailLag, ty = -4;
  ctx.save();
  let tailGrad = ctx.createRadialGradient(tx - 4, ty, 4, tx, ty, 32);
  tailGrad.addColorStop(0, '#FFFFFF');
  tailGrad.addColorStop(0.3, '#E0F2FE');
  tailGrad.addColorStop(0.65, '#38BDF8');
  tailGrad.addColorStop(0.9, '#818CF8');
  tailGrad.addColorStop(1, 'rgba(129, 140, 248, 0)');
  ctx.fillStyle = tailGrad;
  ctx.beginPath();
  ctx.arc(tx + 4, ty + 16, 12, 0, Math.PI * 2);
  ctx.arc(tx - 4, ty + 6, 16, 0, Math.PI * 2);
  ctx.arc(tx - 6, ty - 8, 14, 0, Math.PI * 2);
  ctx.arc(tx + 4, ty - 18, 10, 0, Math.PI * 2);
  ctx.fill();

  // Hạt bụi sao bay lượn (Stardust particle aura)
  for (let i = 0; i < 6; i++) {
    let a = t * 2.8 + i * (Math.PI / 3);
    let r = 18 + Math.sin(t * 4 + i) * 6;
    let px = tx + Math.cos(a) * r;
    let py = ty - 8 + Math.sin(a) * r;
    let alpha = 0.4 + 0.6 * Math.sin(t * 5 + i);
    ctx.fillStyle = `rgba(255, 255, 255, ${alpha})`;
    ctx.beginPath();
    ctx.arc(px, py, 1.2, 0, Math.PI * 2);
    ctx.fill();
  }
  ctx.restore();

  // 2. Bóng tiếp xúc mặt đất
  ctx.fillStyle = 'rgba(2, 132, 199, 0.22)';
  ctx.beginPath();
  ctx.ellipse(0, 38, 26 * breathX, 6, 0, 0, Math.PI * 2);
  ctx.fill();

  // 3. Thân cáo tuyết (Volumetric Snow Torso)
  ctx.save();
  ctx.scale(breathX, breathY);
  let bodyGrad = ctx.createLinearGradient(-10, 0, 10, 35);
  bodyGrad.addColorStop(0, '#FFFFFF');
  bodyGrad.addColorStop(0.7, '#F0F9FF');
  bodyGrad.addColorStop(1, '#BAE6FD');
  ctx.fillStyle = bodyGrad;
  ctx.beginPath();
  ctx.ellipse(-2, 18, 20, 22, 0, 0, Math.PI * 2);
  ctx.ellipse(2, 6, 16, 18, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 4. Chân trước & đệm chân
  ctx.fillStyle = '#FFFFFF';
  ctx.beginPath();
  ctx.roundRect(-10, 18, 6, 20, 3);
  ctx.roundRect(4, 18, 6, 20, 3);
  ctx.fill();
  ctx.fillStyle = '#BAE6FD';
  ctx.beginPath();
  ctx.arc(-7, 37, 3, 0, Math.PI * 2);
  ctx.arc(7, 37, 3, 0, Math.PI * 2);
  ctx.fill();

  // 5. Đầu cáo tuyết & má lông
  ctx.save();
  ctx.scale(breathX, breathY);
  let headGrad = ctx.createRadialGradient(0, -18, 4, 0, -16, 22);
  headGrad.addColorStop(0, '#FFFFFF');
  headGrad.addColorStop(0.85, '#F0F9FF');
  headGrad.addColorStop(1, '#BAE6FD');
  ctx.fillStyle = headGrad;
  ctx.beginPath();
  ctx.ellipse(0, -16, 19, 17, 0, 0, Math.PI * 2);
  ctx.fill();

  // Má lông xòe
  ctx.fillStyle = '#FFFFFF';
  ctx.beginPath();
  ctx.moveTo(-18, -12); ctx.lineTo(-10, -18); ctx.lineTo(-10, -8); ctx.closePath();
  ctx.moveTo(18, -12); ctx.lineTo(10, -18); ctx.lineTo(10, -8); ctx.closePath();
  ctx.fill();
  ctx.restore();

  // 6. Đôi tai cáo vểnh cao (Pointed Arctic Ears)
  for (let side of [-1, 1]) {
    let tipX = side * 16 + earLag * 0.5;
    let tipY = -42;
    let b1x = side * 6, b1y = -24;
    let b2x = side * 22, b2y = -22;

    ctx.fillStyle = '#FFFFFF';
    ctx.beginPath();
    ctx.moveTo(tipX, tipY); ctx.lineTo(b1x, b1y); ctx.lineTo(b2x, b2y); ctx.closePath();
    ctx.fill();
    ctx.strokeStyle = '#BAE6FD';
    ctx.lineWidth = 1;
    ctx.stroke();

    // Vòm tím cực quang & lam pastel
    let earGrad = ctx.createLinearGradient(tipX, tipY, b1x, b1y);
    earGrad.addColorStop(0, '#38BDF8');
    earGrad.addColorStop(0.6, '#C4B5FD');
    earGrad.addColorStop(1, '#E0F2FE');
    ctx.fillStyle = earGrad;
    ctx.beginPath();
    ctx.moveTo(tipX, tipY + 4); ctx.lineTo(b1x + side * 2, b1y - 2); ctx.lineTo(b2x - side * 3, b2y - 1); ctx.closePath();
    ctx.fill();
  }

  // 7. Ấn ký Lam Ngọc 4 cánh phát quang trước trán
  ctx.save();
  ctx.strokeStyle = '#00F0FF';
  ctx.lineWidth = 2.0;
  ctx.shadowColor = '#00F0FF';
  ctx.shadowBlur = 8;
  ctx.beginPath();
  ctx.moveTo(0, -31); ctx.lineTo(0, -21);
  ctx.moveTo(-4, -26); ctx.lineTo(4, -26);
  ctx.stroke();
  ctx.fillStyle = '#FFFFFF';
  ctx.beginPath();
  ctx.arc(0, -26, 2, 0, Math.PI * 2);
  ctx.fill();

  // Mặt dây chuyền giọt nước lam ngọc trước ngực
  ctx.fillStyle = '#00F0FF';
  ctx.beginPath();
  ctx.moveTo(0, -1); ctx.lineTo(-2.5, -5); ctx.lineTo(2.5, -5); ctx.closePath();
  ctx.fill();
  ctx.restore();

  // 8. Mắt Bích Ngọc Lam Pha Lê (3 Catchlights)
  for (let side of [-1, 1]) {
    let eyeX = side * 10, eyeY = -16;
    if (blink) {
      ctx.strokeStyle = '#0369A1';
      ctx.lineWidth = 2.0;
      ctx.beginPath();
      ctx.moveTo(eyeX - 3.5, eyeY); ctx.lineTo(eyeX + 3.5, eyeY);
      ctx.stroke();
    } else {
      let eyeGrad = ctx.createRadialGradient(eyeX, eyeY - 1, 1, eyeX, eyeY, 5);
      eyeGrad.addColorStop(0, '#38BDF8');
      eyeGrad.addColorStop(0.5, '#0284C7');
      eyeGrad.addColorStop(1, '#0C2340');
      ctx.fillStyle = eyeGrad;
      ctx.beginPath();
      ctx.ellipse(eyeX, eyeY, 4, 6, 0, 0, Math.PI * 2);
      ctx.fill();

      // 3 Điểm sáng phản quang
      ctx.fillStyle = '#FFFFFF';
      ctx.beginPath();
      ctx.arc(eyeX - 1.5, eyeY - 2.5, 1.8, 0, Math.PI * 2); // Điểm 1: Cực quang đỉnh
      ctx.fill();

      ctx.fillStyle = '#FFFFFF';
      ctx.beginPath();
      ctx.arc(eyeX + 1.2, eyeY + 1, 0.9, 0, Math.PI * 2);  // Điểm 2: Tinh thể phụ
      ctx.fill();

      ctx.fillStyle = '#E0F2FE';
      ctx.beginPath();
      ctx.arc(eyeX, eyeY + 2.2, 0.8, 0, Math.PI * 2);      // Điểm 3: Phản quang đáy
      ctx.fill();
    }
  }

  // 9. Mũi & Nụ cười cáo
  ctx.fillStyle = '#0C2340';
  ctx.beginPath();
  ctx.arc(0, -11, 1.2, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = '#0284C7';
  ctx.lineWidth = 1.0;
  ctx.beginPath();
  ctx.moveTo(-2, -9); ctx.lineTo(0, -8); ctx.lineTo(2, -9);
  ctx.stroke();

  ctx.restore();
}"""
    },
    {
        "id": 2,
        "codename": "PYROKI_FLAME_EMBER_FOX",
        "name_vi": "Cáo Lửa Rực Rỡ Pyroki",
        "name_en": "Pyroki Solar Flare Ember Fox",
        "korean_name": "파이로키 (불꽃 여우)",
        "archetype": "Hỏa Hồ Nham Thạch & Lửa Thiêng (Solar Flare Ember Fox)",
        "source_art_reference": "✨ 판타지 동물 도감 (파이로키) & CHAEON EMBER",
        "category": "Thần Thú & Linh Thú Rừng Thiêng",
        "mythology_lore": "Hỏa hồ ly sinh ra từ miệng núi lửa cổ đại và ngọn lửa tinh khôi của thái dương. Toàn thân khoác lớp lông màu mật ong ấm áp, đôi tai nhọn chóp đỏ thẫm luôn lắng nghe tiếng thì thầm của nham thạch. Chiếc đuôi lửa 3 tầng bập bùng như ngọn đuốc thần kỳ, mang theo tàn tro vàng rực xua tan mùa đông lạnh giá cho vạn vật.",
        "palette": {
            "primary_hex": "#FF8A00",
            "primary_name": "Warm Honey Amber",
            "rgb565_primary": "0xFC40",
            "secondary_hex": "#FF5500",
            "secondary_name": "Flame Orange Midtone",
            "rgb565_secondary": "0xFA80",
            "crimson_hex": "#DC2626",
            "crimson_name": "Molten Crimson Tips",
            "rgb565_crimson": "0xD924",
            "core_yellow_hex": "#FEF08A",
            "core_yellow_name": "Incandescent Flame Core",
            "rgb565_core_yellow": "0xFF91",
            "cream_chest_hex": "#FFFBEB",
            "cream_chest_name": "Warm Cream Chest Ruff",
            "rgb565_cream_chest": "0xFFDF",
            "eye_amber_hex": "#D97706",
            "rgb565_eye_amber": "0xD3A0",
            "eye_deep_obsidian_hex": "#451A03",
            "rgb565_eye_deep": "0x40E0"
        },
        "breathing_squash_stretch_specs": {
            "frequency_hz": 0.38,
            "squash_stretch_percent": 5.0,
            "vertical_scale_formula": "1.0 + 0.05 * sin(t * 2.4)",
            "horizontal_volume_formula": "1.0 - 0.025 * sin(t * 2.4)",
            "ear_lag_rad": 0.35,
            "ear_lag_formula": "sin(t * 2.4 - 0.35) * 3.5",
            "tail_lag_rad": 0.50,
            "tail_lag_formula": "sin(t * 2.4 - 0.50) * 10.0",
            "secondary_inertia_damping": 0.85
        },
        "eye_specs": {
            "eye_type": "topaz_amber_crystal",
            "blink_interval_ms": 3400,
            "blink_duration_ms": 125,
            "pupil_shape": "vertical_golden_almond",
            "catchlight_3points": [
                {
                    "point_id": 1,
                    "name": "Solar Diamond Specular",
                    "dx": -2,
                    "dy": -3,
                    "radius_px": 2.2,
                    "color_hex": "#FFFFFF",
                    "rgb565": "0xFFFF",
                    "role": "Blazing sunlight core catchlight"
                },
                {
                    "point_id": 2,
                    "name": "Ember Spark Glint",
                    "dx": 2,
                    "dy": 1,
                    "radius_px": 1.1,
                    "color_hex": "#FEF08A",
                    "rgb565": "0xFF91",
                    "role": "Secondary molten gold ember glint"
                },
                {
                    "point_id": 3,
                    "name": "Molten Gold Caustic",
                    "dx": 0,
                    "dy": 3,
                    "radius_px": 0.9,
                    "color_hex": "#FDE68A",
                    "rgb565": "0xFF31",
                    "role": "Bottom magma caustic rim"
                }
            ],
            "pupil_tracking_range_px": {"max_x": 4, "max_y": 3}
        },
        "volumetric_3d_specs": {
            "mesh_topology": "Energetic bouncy fox with layered triple-tongue fire plume tail and crimson ear tips",
            "light_direction": [-0.5, -0.7, 0.7],
            "ambient_occlusion_passes": [
                "Under-belly magma glow shadow",
                "Deep neck chest tuft separation",
                "Inner ear flame canal depth"
            ],
            "specular_power": 18.0,
            "rim_light_color": "0xFF91"
        },
        "secondary_motion_specs": {
            "tail_flame_turbulence": "High frequency ripple sin(t * 3.8) * 4.0 superimposed on base tail sway",
            "rising_ember_particles": "Procedural rising sparks with sinusoidal drift and fading alpha",
            "ear_flutter": "Agile perked ear motion responding to thermal convection"
        },
        "visual_breakdown": [
            "Toàn thân màu cam mật ong ấm áp (#FF8A00) phủ bóng cam lửa rực rỡ (#FF5500)",
            "Yếm ngực lông xù trắng kem mềm mại như đám mây ấm (#FFFBEB)",
            "Đôi tai cáo nhọn hoắt với chóp tai đỏ thẫm rực lửa (#DC2626) và lòng tai vàng rực",
            "Đuôi lửa 3 tầng bập bùng chuyển sắc nhịp nhàng: viền đỏ thẫm -> thân cam -> lõi vàng rực",
            "Đốm tàn lửa hoàng kim (Ember Sparks) bay bổng liên tục từ chóp đuôi lên không trung",
            "Đôi mắt ngọc hổ phách Topaz lấp lánh 3 điểm sáng phản chiếu ngọn lửa vĩnh cửu"
        ],
        "quote_vi": "Ngọn lửa trong tim anh bùng cháy rực rỡ nhất là khi ở cạnh em.",
        "shader_effect": "Blazing Fire Tongue Plasma & Rising Thermal Embers",
        "cpp_render_snippet": """void drawPyrokiFlameFox(ScaledCanvas* spr, int cx, int cy, float t) {
  // 1. Nhịp thở Squash & Stretch 5%
  float breathY = 1.0f + 0.05f * sinf(t * 2.4f);
  float breathX = 1.0f - 0.025f * sinf(t * 2.4f);
  float earLag = sinf(t * 2.4f - 0.35f) * 3.5f;
  float tailLag = sinf(t * 2.4f - 0.50f) * 10.0f;
  float flameTurb = sinf(t * 4.2f) * 3.5f;
  bool blink = (fmodf(t, 3.4f) < 0.12f);

  // 2. Chiếc đuôi lửa 3 tầng bập bùng (Layered Blazing Flame Tail)
  int tx = cx + 22 + (int)tailLag;
  int ty = cy - 2;

  // Tầng 1: Ngọn lửa đỏ thẫm ngoài cùng (#DC2626)
  spr->fillCircle(tx - 4, ty + 16, 13, 0xD924);
  spr->fillCircle(tx + 6, ty + 4, 16, 0xD924);
  spr->fillCircle(tx + 4 + (int)flameTurb, ty - 12, 13, 0xD924);
  spr->fillTriangle(tx + 4 + (int)flameTurb, ty - 24, tx - 4, ty - 8, tx + 14, ty - 6, 0xD924);

  // Tầng 2: Thân lửa cam rực rỡ (#FF5500)
  spr->fillCircle(tx - 2, ty + 14, 10, 0xFA80);
  spr->fillCircle(tx + 4, ty + 4, 12, 0xFA80);
  spr->fillCircle(tx + 3 + (int)flameTurb, ty - 10, 9, 0xFA80);
  spr->fillTriangle(tx + 3 + (int)flameTurb, ty - 20, tx - 2, ty - 7, tx + 11, ty - 5, 0xFA80);

  // Tầng 3: Lõi lửa vàng rực sáng (#FEF08A)
  spr->fillCircle(tx, ty + 12, 6, 0xFF91);
  spr->fillCircle(tx + 3, ty + 3, 7, 0xFF91);
  spr->fillCircle(tx + 2 + (int)flameTurb, ty - 8, 5, 0xFF91);

  // Tàn lửa bay lên (Floating Ember Sparks)
  for (int i = 0; i < 4; i++) {
    int sparkY = ty - 16 - (int)(fmodf(t * 35.0f + i * 18.0f, 40.0f));
    int sparkX = tx + (int)(sinf(t * 3.0f + i * 1.8f) * 8.0f);
    spr->drawPixel(sparkX, sparkY, 0xFF91);
    spr->drawPixel(sparkX + 1, sparkY, 0xFA80);
  }

  // 3. Bóng tiếp xúc mặt đất với ánh lửa ấm
  spr->fillEllipse(cx, cy + 38, (int)(26 * breathX), 6, 0x40E0);

  // 4. Thân cáo mật ong (Warm Honey Body)
  spr->fillEllipse(cx, cy + 16, (int)(22 * breathX), (int)(22 * breathY), 0xFC40);
  spr->fillEllipse(cx, cy + 24, (int)(18 * breathX), (int)(14 * breathY), 0xFA80);

  // Yếm ngực lông kem mềm mại
  spr->fillEllipse(cx, cy + 8, (int)(14 * breathX), (int)(14 * breathY), 0xFFDF);

  // 5. Bốn chân nhỏ xinh
  spr->fillRoundRect(cx - 14, cy + 18, 7, 20, 3, 0xFC40);
  spr->fillRoundRect(cx + 7, cy + 18, 7, 20, 3, 0xFC40);
  spr->fillCircle(cx - 10, cy + 37, 3, 0xFA80);
  spr->fillCircle(cx + 10, cy + 37, 3, 0xFA80);

  // 6. Đầu cáo tròn má phúng phính
  spr->fillEllipse(cx, cy - 14, (int)(21 * breathX), (int)(19 * breathY), 0xFC40);
  spr->fillTriangle(cx - 20, cy - 10, cx - 12, cy - 16, cx - 12, cy - 6, 0xFC40);
  spr->fillTriangle(cx + 20, cy - 10, cx + 12, cy - 16, cx + 12, cy - 6, 0xFC40);
  // Má ửng hồng cam
  spr->fillCircle(cx - 12, cy - 10, 3, 0xFA80);
  spr->fillCircle(cx + 12, cy - 10, 3, 0xFA80);

  // 7. Đôi tai cáo chóp đỏ thẫm (Flame Ears with Crimson Tips)
  for (int side = -1; side <= 1; side += 2) {
    int tipX = cx + side * 18 + (int)(earLag * 0.5f);
    int tipY = cy - 42;
    int b1x = cx + side * 6, b1y = cy - 24;
    int b2x = cx + side * 24, b2y = cy - 20;
    // Thân tai cam
    spr->fillTriangle(tipX, tipY, b1x, b1y, b2x, b2y, 0xFC40);
    // Chóp tai đỏ thẫm (#DC2626)
    spr->fillTriangle(tipX, tipY, tipX - side*4, tipY + 10, tipX + side*3, tipY + 9, 0xD924);
    // Lòng tai vàng rực
    spr->fillTriangle(tipX, tipY + 8, b1x + side*3, b1y - 2, b2x - side*3, b2y - 2, 0xFF91);
  }

  // 8. Mắt Hổ Phách Topaz Lấp Lánh (3 Catchlights)
  for (int side = -1; side <= 1; side += 2) {
    int eyeX = cx + side * 11, eyeY = cy - 15;
    if (blink) {
      spr->drawFastHLine(eyeX - 4, eyeY, 8, 0x40E0);
    } else {
      spr->fillEllipse(eyeX, eyeY, 5, 6, 0x40E0); // Hốc mắt sâu
      spr->fillEllipse(eyeX, eyeY, 4, 5, 0xD3A0); // Tròng hổ phách
      spr->fillCircle(eyeX, eyeY + 1, 2, 0xFF91);  // Vòm sáng đáy
      // 3 Điểm sáng pha lê
      spr->fillCircle(eyeX - 2, eyeY - 2, 2, 0xFFFF); // Điểm 1: Lóa thái dương
      spr->drawPixel(eyeX + 1, eyeY + 1, 0xFF91);     // Điểm 2: Tàn lửa phản xạ
      spr->drawPixel(eyeX - 1, eyeY + 2, 0xFF31);     // Điểm 3: Ánh nham thạch
    }
  }

  // 9. Mũi & Nụ cười cáo ngộ nghĩnh
  spr->fillCircle(cx, cy - 10, 2, 0x40E0);
  spr->drawPixel(cx - 2, cy - 8, 0xFA80);
  spr->drawPixel(cx - 1, cy - 7, 0xFA80);
  spr->drawPixel(cx,     cy - 8, 0xFA80);
  spr->drawPixel(cx + 1, cy - 7, 0xFA80);
  spr->drawPixel(cx + 2, cy - 8, 0xFA80);
}""",
        "js_render_snippet": """function drawPyrokiFlameFox(ctx, cx, cy, scale, t) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.scale(scale, scale);

  const breathY = 1.0 + 0.05 * Math.sin(t * 2.4);
  const breathX = 1.0 - 0.025 * Math.sin(t * 2.4);
  const earLag = Math.sin(t * 2.4 - 0.35) * 3.5;
  const tailLag = Math.sin(t * 2.4 - 0.50) * 10.0;
  const flameTurb = Math.sin(t * 4.2) * 3.5;
  const blink = (t % 3.4 < 0.12);

  // 1. Chiếc đuôi lửa 3 tầng bập bùng (Dynamic Flame Tail)
  let tx = 22 + tailLag, ty = -2;
  ctx.save();

  // Tầng 1: Vỏ lửa đỏ thẫm (#DC2626)
  ctx.fillStyle = '#DC2626';
  ctx.beginPath();
  ctx.arc(tx - 4, ty + 16, 13, 0, Math.PI * 2);
  ctx.arc(tx + 6, ty + 4, 16, 0, Math.PI * 2);
  ctx.arc(tx + 4 + flameTurb, ty - 12, 13, 0, Math.PI * 2);
  ctx.moveTo(tx + 4 + flameTurb, ty - 24);
  ctx.lineTo(tx - 4, ty - 8);
  ctx.lineTo(tx + 14, ty - 6);
  ctx.closePath();
  ctx.fill();

  // Tầng 2: Thân lửa cam (#FF5500)
  ctx.fillStyle = '#FF5500';
  ctx.beginPath();
  ctx.arc(tx - 2, ty + 14, 10, 0, Math.PI * 2);
  ctx.arc(tx + 4, ty + 4, 12, 0, Math.PI * 2);
  ctx.arc(tx + 3 + flameTurb, ty - 10, 9, 0, Math.PI * 2);
  ctx.moveTo(tx + 3 + flameTurb, ty - 20);
  ctx.lineTo(tx - 2, ty - 7);
  ctx.lineTo(tx + 11, ty - 5);
  ctx.closePath();
  ctx.fill();

  // Tầng 3: Lõi lửa hoàng kim phát sáng (#FEF08A)
  ctx.fillStyle = '#FEF08A';
  ctx.shadowColor = '#FBBF24';
  ctx.shadowBlur = 10;
  ctx.beginPath();
  ctx.arc(tx, ty + 12, 6, 0, Math.PI * 2);
  ctx.arc(tx + 3, ty + 3, 7, 0, Math.PI * 2);
  ctx.arc(tx + 2 + flameTurb, ty - 8, 5, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // Tàn lửa bốc lên không trung (Floating Embers)
  for (let i = 0; i < 5; i++) {
    let sparkY = ty - 16 - ((t * 35 + i * 18) % 44);
    let sparkX = tx + Math.sin(t * 3 + i * 1.8) * 9;
    let alpha = 0.4 + 0.6 * Math.sin(t * 6 + i);
    ctx.fillStyle = `rgba(254, 240, 138, ${alpha})`;
    ctx.beginPath();
    ctx.arc(sparkX, sparkY, 1.4, 0, Math.PI * 2);
    ctx.fill();
  }

  // 2. Bóng tiếp xúc mặt đất với sắc đỏ nham thạch
  ctx.fillStyle = 'rgba(69, 26, 3, 0.28)';
  ctx.beginPath();
  ctx.ellipse(0, 38, 26 * breathX, 6, 0, 0, Math.PI * 2);
  ctx.fill();

  // 3. Thân cáo cam mật ong (Warm Honey Torso)
  ctx.save();
  ctx.scale(breathX, breathY);
  let bodyGrad = ctx.createRadialGradient(0, 10, 6, 0, 16, 24);
  bodyGrad.addColorStop(0, '#FFAA00');
  bodyGrad.addColorStop(0.65, '#FF7A00');
  bodyGrad.addColorStop(1, '#DC2626');
  ctx.fillStyle = bodyGrad;
  ctx.beginPath();
  ctx.ellipse(0, 16, 22, 22, 0, 0, Math.PI * 2);
  ctx.fill();

  // Yếm ngực kem mềm mại
  ctx.fillStyle = '#FFFBEB';
  ctx.beginPath();
  ctx.ellipse(0, 8, 14, 14, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 4. Bốn chân nhỏ xinh
  ctx.fillStyle = '#FF7A00';
  ctx.beginPath();
  ctx.roundRect(-14, 18, 7, 20, 3);
  ctx.roundRect(7, 18, 7, 20, 3);
  ctx.fill();
  ctx.fillStyle = '#DC2626';
  ctx.beginPath();
  ctx.arc(-10, 37, 3, 0, Math.PI * 2);
  ctx.arc(10, 37, 3, 0, Math.PI * 2);
  ctx.fill();

  // 5. Đầu cáo & Má phúng phính
  ctx.save();
  ctx.scale(breathX, breathY);
  let headGrad = ctx.createRadialGradient(0, -14, 4, 0, -14, 22);
  headGrad.addColorStop(0, '#FFAA00');
  headGrad.addColorStop(0.7, '#FF7A00');
  headGrad.addColorStop(1, '#EA580C');
  ctx.fillStyle = headGrad;
  ctx.beginPath();
  ctx.ellipse(0, -14, 21, 19, 0, 0, Math.PI * 2);
  ctx.fill();

  // Má lông & ửng hồng cam
  ctx.fillStyle = '#FF7A00';
  ctx.beginPath();
  ctx.moveTo(-20, -10); ctx.lineTo(-12, -16); ctx.lineTo(-12, -6); ctx.closePath();
  ctx.moveTo(20, -10); ctx.lineTo(12, -16); ctx.lineTo(12, -6); ctx.closePath();
  ctx.fill();

  ctx.fillStyle = 'rgba(255, 107, 107, 0.45)';
  ctx.beginPath();
  ctx.arc(-12, -10, 3.5, 0, Math.PI * 2);
  ctx.arc(12, -10, 3.5, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 6. Đôi tai dựng nhọn chóp đỏ thẫm
  for (let side of [-1, 1]) {
    let tipX = side * 18 + earLag * 0.5;
    let tipY = -42;
    let b1x = side * 6, b1y = -24;
    let b2x = side * 24, b2y = -20;

    // Thân tai cam
    ctx.fillStyle = '#FF7A00';
    ctx.beginPath();
    ctx.moveTo(tipX, tipY); ctx.lineTo(b1x, b1y); ctx.lineTo(b2x, b2y); ctx.closePath();
    ctx.fill();

    // Chóp tai đỏ thẫm
    ctx.fillStyle = '#DC2626';
    ctx.beginPath();
    ctx.moveTo(tipX, tipY);
    ctx.lineTo(tipX - side * 5, tipY + 11);
    ctx.lineTo(tipX + side * 4, tipY + 10);
    ctx.closePath();
    ctx.fill();

    // Lòng tai vàng rực
    ctx.fillStyle = '#FEF08A';
    ctx.beginPath();
    ctx.moveTo(tipX, tipY + 8);
    ctx.lineTo(b1x + side * 3, b1y - 2);
    ctx.lineTo(b2x - side * 4, b2y - 2);
    ctx.closePath();
    ctx.fill();
  }

  // 7. Mắt Hổ Phách Topaz Lấp Lánh (3 Catchlights)
  for (let side of [-1, 1]) {
    let eyeX = side * 11, eyeY = -15;
    if (blink) {
      ctx.strokeStyle = '#451A03';
      ctx.lineWidth = 2.2;
      ctx.beginPath();
      ctx.moveTo(eyeX - 4, eyeY); ctx.lineTo(eyeX + 4, eyeY);
      ctx.stroke();
    } else {
      let eyeGrad = ctx.createRadialGradient(eyeX, eyeY - 1, 1, eyeX, eyeY, 6);
      eyeGrad.addColorStop(0, '#FEF08A');
      eyeGrad.addColorStop(0.5, '#D97706');
      eyeGrad.addColorStop(1, '#451A03');
      ctx.fillStyle = eyeGrad;
      ctx.beginPath();
      ctx.ellipse(eyeX, eyeY, 5, 6.5, 0, 0, Math.PI * 2);
      ctx.fill();

      // 3 Điểm sáng phản quang
      ctx.fillStyle = '#FFFFFF';
      ctx.beginPath();
      ctx.arc(eyeX - 2, eyeY - 2.5, 2.0, 0, Math.PI * 2); // Điểm 1: Lóa thái dương
      ctx.fill();

      ctx.fillStyle = '#FEF08A';
      ctx.beginPath();
      ctx.arc(eyeX + 1.2, eyeY + 1, 1.1, 0, Math.PI * 2);  // Điểm 2: Tàn lửa
      ctx.fill();

      ctx.fillStyle = '#FDE68A';
      ctx.beginPath();
      ctx.arc(eyeX - 0.5, eyeY + 2.5, 0.9, 0, Math.PI * 2); // Điểm 3: Ánh nham thạch
      ctx.fill();
    }
  }

  // 8. Mũi & Miệng cười
  ctx.fillStyle = '#451A03';
  ctx.beginPath();
  ctx.arc(0, -10, 1.8, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = '#EA580C';
  ctx.lineWidth = 1.3;
  ctx.beginPath();
  ctx.moveTo(-3, -8); ctx.quadraticCurveTo(-1.5, -6.5, 0, -8); ctx.quadraticCurveTo(1.5, -6.5, 3, -8);
  ctx.stroke();

  ctx.restore();
}"""
    },
    {
        "id": 3,
        "codename": "HETEROCHROMIA_FAIRY_RABBIT",
        "name_vi": "Thỏ Linh Thú Dị Sắc",
        "name_en": "Heterochromia Fairy-Eared Spirit Rabbit",
        "archetype": "Tiên Thỏ Cánh Vũ Dị Sắc Đồng Tử (Winged Heterochromia Celestine Rabbit)",
        "source_art_reference": "download (8).jpg",
        "category": "Thần Thú & Linh Thú Rừng Thiêng",
        "mythology_lore": "Linh thỏ tiên giới mang phong thái kiêu kỳ, lém lỉnh và tràn đầy ma lực huyền bí. Đôi tai xòe rộng như cánh thiên thần viền lông vũ tinh xảo, hai chóp tai đeo vòng vàng kép đính chuỗi hạt ngọc và dải tua rua bay bổng. Điểm đặc sắc nhất là đôi mắt Dị Sắc Đồng Tử: mắt phải mang sắc Hổ Phách mặt trời rực rỡ, mắt trái mang sắc Bích Ngọc sapphire mặt trăng sâu thẳm, cả hai đều có con ngươi hình ngôi sao 4 cánh linh thiêng.",
        "palette": {
            "primary_hex": "#FAF8F5",
            "primary_name": "Ivory Silk Fur",
            "rgb565_primary": "0xFFDF",
            "secondary_hex": "#F3EDE2",
            "secondary_name": "Cream Shadow Tone",
            "rgb565_secondary": "0xF77D",
            "taupe_hex": "#A89F91",
            "taupe_name": "Soft Chestnut Wing Tips & Paws",
            "rgb565_taupe": "0xACE2",
            "sigil_scarlet_hex": "#EF4444",
            "sigil_scarlet_name": "Vermilion Forehead Cross Sigil",
            "rgb565_sigil_scarlet": "0xEA28",
            "gold_metal_hex": "#F59E0B",
            "gold_metal_name": "Polished Kinpaku Gold (Jewelry)",
            "rgb565_gold_metal": "0xF4E1",
            "gold_pale_hex": "#FEF08A",
            "gold_pale_name": "Pale Gold Highlight",
            "rgb565_gold_pale": "0xFF91",
            "eye_amber_hex": "#D97706",
            "rgb565_eye_amber": "0xD3A0",
            "eye_sapphire_hex": "#0284C7",
            "rgb565_eye_sapphire": "0x0438"
        },
        "breathing_squash_stretch_specs": {
            "frequency_hz": 0.36,
            "squash_stretch_percent": 5.0,
            "vertical_scale_formula": "1.0 + 0.05 * sin(t * 2.3)",
            "horizontal_volume_formula": "1.0 - 0.025 * sin(t * 2.3)",
            "ear_lag_rad": 0.45,
            "ear_lag_formula": "sin(t * 2.3 - 0.45) * 4.0",
            "tassel_swing_formula": "sin(t * 2.6 - 0.70) * 0.22",
            "secondary_inertia_damping": 0.92
        },
        "eye_specs": {
            "eye_type": "heterochromia_star_crystal",
            "blink_interval_ms": 3700,
            "blink_duration_ms": 135,
            "pupil_shape": "four_pointed_star_pupil",
            "catchlight_3points": [
                {
                    "point_id": 1,
                    "name": "Star Specular Glint",
                    "dx": -2,
                    "dy": -3,
                    "radius_px": 2.0,
                    "color_hex": "#FFFFFF",
                    "rgb565": "0xFFFF",
                    "role": "Primary starlight specular glint on upper cornea"
                },
                {
                    "point_id": 2,
                    "name": "Star Point Reflection",
                    "dx": 2,
                    "dy": 1,
                    "radius_px": 1.0,
                    "color_hex": "#FFFFFF",
                    "rgb565": "0xFFFF",
                    "role": "Secondary crisp micro specular glint"
                },
                {
                    "point_id": 3,
                    "name": "Heterochromia Iris Caustic",
                    "dx": 0,
                    "dy": 3,
                    "radius_px": 0.8,
                    "color_hex": "#FDE68A / #7DD3FC",
                    "rgb565": "0xFF31 / 0x7EBF",
                    "role": "Bottom eyelid color-specific caustic bounce (Amber for Right, Sapphire for Left)"
                }
            ],
            "right_eye_amber": {
                "base_hex": "#78350F",
                "iris_hex": "#F59E0B",
                "star_pupil_hex": "#FEF08A",
                "catchlights": [
                    {"dx": -2, "dy": -3, "r": 2.0, "col": "#FFFFFF"},
                    {"dx": 2, "dy": 1, "r": 1.0, "col": "#FFFFFF"},
                    {"dx": 0, "dy": 3, "r": 0.8, "col": "#FDE68A"}
                ]
            },
            "left_eye_sapphire": {
                "base_hex": "#082F49",
                "iris_hex": "#0284C7",
                "star_pupil_hex": "#7DD3FC",
                "catchlights": [
                    {"dx": -2, "dy": -3, "r": 2.0, "col": "#FFFFFF"},
                    {"dx": 2, "dy": 1, "r": 1.0, "col": "#FFFFFF"},
                    {"dx": 0, "dy": 3, "r": 0.8, "col": "#7DD3FC"}
                ]
            },
            "pupil_tracking_range_px": {"max_x": 3, "max_y": 2}
        },
        "volumetric_3d_specs": {
            "mesh_topology": "Sassy standing posture with hands on hips, wide feathered wing ears and hanging pendulum tassels",
            "light_direction": [-0.4, -0.8, 0.6],
            "ambient_occlusion_passes": [
                "Under-arm and waist occlusion",
                "Behind-ear feather fringe depth",
                "Collar bell metallic drop shadow"
            ],
            "specular_power": 22.0,
            "rim_light_color": "0xFF91"
        },
        "secondary_motion_specs": {
            "fairy_wing_ear_flutter": "Harmonic feather flex with phase delay phi=0.45 rad",
            "hanging_tassel_pendulum": "Double-compound pendulum swing with harmonic inertia",
            "sassy_body_sway": "Micro hip tilt synced with breathing cycle"
        },
        "visual_breakdown": [
            "Dáng đứng 2 chân chống nạnh tự tin, kiêu kỳ và lém lỉnh vô cùng đáng yêu",
            "Đôi tai cánh tiên (Fairy Wing Ears) xòe rộng ngang tựa lông vũ thiên thần mềm mại",
            "Hai chóp tai đeo khuyên vàng đôi, đính hạt ngọc vàng và chùm tua rua trắng đung đưa",
            "Đôi mắt Dị Sắc Đồng Tử (Heterochromia): mắt phải Hổ Phách mặt trời, mắt trái Sapphire đại dương",
            "Con ngươi cả hai mắt đều mang hình Ngôi Sao 4 Cánh phát sáng cùng 3 điểm sáng pha lê",
            "Ấn ký chữ thập đỏ son kiêu sa ngay giữa trán (#EF4444)",
            "Vòng cổ chuông vàng và đôi vòng tay vàng óng nổi bật trên bộ lông trắng mướt"
        ],
        "quote_vi": "Đôi mắt anh nhìn thấu ngàn vì sao, nhưng chỉ dừng lại ở nụ cười của em.",
        "shader_effect": "Star Pupil Shimmer & Swaying Silk Tassel Physics",
        "cpp_render_snippet": """void drawHeterochromiaFairyRabbit(ScaledCanvas* spr, int cx, int cy, float t) {
  // 1. Nhịp thở Squash & Stretch 5%
  float breathY = 1.0f + 0.05f * sinf(t * 2.3f);
  float breathX = 1.0f - 0.025f * sinf(t * 2.3f);
  float earFlap = sinf(t * 2.3f - 0.45f) * 4.0f;
  float tasselSwing = sinf(t * 2.6f - 0.70f) * 6.0f;
  bool blink = (fmodf(t, 3.7f) < 0.13f);

  // 2. Bóng tiếp xúc mặt đất
  spr->fillEllipse(cx, cy + 45, (int)(24 * breathX), 6, 0x18C3);

  // 3. Đôi chân thỏ hạt dẻ & móng mềm
  spr->fillRoundRect(cx - 12, cy + 28, 8, 18, 4, 0xACE2);
  spr->fillRoundRect(cx + 4, cy + 28, 8, 18, 4, 0xACE2);
  spr->drawFastVLine(cx - 8, cy + 42, 4, 0x7B6C);
  spr->drawFastVLine(cx + 8, cy + 42, 4, 0x7B6C);

  // 4. Thân thỏ tròn múp míp (Chubby Bunny Torso)
  spr->fillEllipse(cx, cy + 18, (int)(20 * breathX), (int)(24 * breathY), 0xFFDF);
  spr->fillEllipse(cx, cy + 18, (int)(16 * breathX), (int)(20 * breathY), 0xFFFF);

  // 5. Tay chống nạnh kiêu kỳ & Vòng tay vàng (Akimbo Hands & Gold Cuffs)
  for (int side = -1; side <= 1; side += 2) {
    int elbowX = cx + side * 22;
    int handX = cx + side * 14;
    // Cánh tay trắng kem
    spr->drawLine(cx + side * 14, cy + 8, elbowX, cy + 14, 0xFFDF);
    spr->drawLine(elbowX, cy + 14, handX, cy + 20, 0xFFDF);
    spr->fillCircle(elbowX, cy + 14, 3, 0xFFDF);
    // Vòng vàng cổ tay
    spr->fillRect(handX - 2, cy + 18, 5, 4, 0xF4E1);
    // Bàn tay hạt dẻ
    spr->fillCircle(handX, cy + 21, 3, 0xACE2);
  }

  // 6. Vòng cổ & Chuông vàng
  spr->drawFastHLine(cx - 8, cy - 2, 16, 0x18C3);
  spr->fillCircle(cx, cy + 2, 4, 0xF4E1);
  spr->drawCircle(cx, cy + 2, 4, 0xFF91);

  // 7. Đầu thỏ bầu bĩnh (Wide Oval Head)
  spr->fillEllipse(cx, cy - 14, (int)(26 * breathX), (int)(20 * breathY), 0xFFFF);
  // Má hồng son
  spr->fillEllipse(cx - 16, cy - 10, 4, 2, 0xFBA0);
  spr->fillEllipse(cx + 16, cy - 10, 4, 2, 0xFBA0);

  // 8. Đôi tai cánh tiên xòe rộng (Fairy Wing Ears)
  for (int side = -1; side <= 1; side += 2) {
    int tipX = cx + side * 56 + (int)(side * earFlap);
    int tipY = cy - 8 + (int)earFlap;
    int rootX = cx + side * 16, rootY = cy - 20;

    // Viền cánh lông vũ
    spr->fillTriangle(rootX, rootY, tipX, tipY, cx + side * 36, cy - 2, 0xFFFF);
    spr->fillCircle(tipX, tipY, 4, 0xACE2); // Chóp tai ombre hạt dẻ

    // Răng cưa lông vũ cánh tiên
    spr->fillTriangle(cx + side * 32, cy - 2, cx + side * 38, cy + 6, cx + side * 44, cy, 0xACE2);
    spr->fillTriangle(cx + side * 44, cy, cx + side * 50, cy + 6, tipX, tipY, 0xACE2);

    // Khuyên vàng đôi & Hạt ngọc (Gold Hoop Earrings & Bead)
    spr->drawCircle(tipX, tipY + 6, 4, 0xF4E1);
    spr->drawCircle(tipX, tipY + 11, 4, 0xF4E1);
    spr->fillCircle(tipX, tipY + 16, 3, 0xF4E1);

    // Tua rua trắng đung đưa (Swaying Tassels)
    int botY = tipY + 30;
    int swX = tipX + (int)(tasselSwing * side);
    spr->drawLine(tipX, tipY + 18, swX, botY, 0xFFFF);
    spr->drawLine(tipX - 1, tipY + 18, swX - 2, botY, 0xF77D);
    spr->drawLine(tipX + 1, tipY + 18, swX + 2, botY, 0xF77D);
  }

  // 9. Ấn ký chữ thập đỏ son trước trán (Vermilion Forehead Cross Star)
  int sigY = cy - 25;
  spr->drawFastVLine(cx, sigY - 5, 11, 0xEA28);
  spr->drawFastHLine(cx - 4, sigY, 9, 0xEA28);
  spr->drawPixel(cx, sigY, 0xFFFF);

  // 10. Đôi Mắt Dị Sắc Đồng Tử (Heterochromia 3 Catchlights & Star Pupils)
  // Mắt Phải (Bên Trái người xem): HỔ PHÁCH (#D97706)
  int rEyeX = cx - 12, eyeY = cy - 14;
  if (blink) {
    spr->drawFastHLine(rEyeX - 4, eyeY, 8, 0x79A1);
  } else {
    spr->fillEllipse(rEyeX, eyeY, 5, 7, 0x79A1);
    spr->fillEllipse(rEyeX, eyeY, 4, 6, 0xD3A0);
    // Con ngươi Ngôi Sao 4 Cánh vàng
    spr->drawFastVLine(rEyeX, eyeY - 2, 5, 0xFF91);
    spr->drawFastHLine(rEyeX - 2, eyeY, 5, 0xFF91);
    // 3 Điểm sáng pha lê
    spr->fillCircle(rEyeX - 2, eyeY - 3, 2, 0xFFFF); // Điểm 1
    spr->drawPixel(rEyeX + 2, eyeY + 1, 0xFFFF);     // Điểm 2
    spr->drawPixel(rEyeX, eyeY + 3, 0xFF91);         // Điểm 3
  }

  // Mắt Trái (Bên Phải người xem): SAPPHIRE (#0284C7)
  int lEyeX = cx + 12;
  if (blink) {
    spr->drawFastHLine(lEyeX - 4, eyeY, 8, 0x0969);
  } else {
    spr->fillEllipse(lEyeX, eyeY, 5, 7, 0x0969);
    spr->fillEllipse(lEyeX, eyeY, 4, 6, 0x0438);
    // Con ngươi Ngôi Sao 4 Cánh lam
    spr->drawFastVLine(lEyeX, eyeY - 2, 5, 0x7EBF);
    spr->drawFastHLine(lEyeX - 2, eyeY, 5, 0x7EBF);
    // 3 Điểm sáng pha lê
    spr->fillCircle(lEyeX - 2, eyeY - 3, 2, 0xFFFF); // Điểm 1
    spr->drawPixel(lEyeX + 2, eyeY + 1, 0xFFFF);     // Điểm 2
    spr->drawPixel(lEyeX, eyeY + 3, 0x7EBF);         // Điểm 3
  }

  // 11. Mũi & Miệng cười lém lỉnh (^w^)
  spr->drawPixel(cx, cy - 9, 0x7B6C);
  spr->drawPixel(cx - 3, cy - 7, 0x7B6C);
  spr->drawPixel(cx - 2, cy - 6, 0x7B6C);
  spr->drawPixel(cx,     cy - 7, 0x7B6C);
  spr->drawPixel(cx + 2, cy - 6, 0x7B6C);
  spr->drawPixel(cx + 3, cy - 7, 0x7B6C);
}""",
        "js_render_snippet": """function drawHeterochromiaFairyRabbit(ctx, cx, cy, scale, t) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.scale(scale, scale);

  const breathY = 1.0 + 0.05 * Math.sin(t * 2.3);
  const breathX = 1.0 - 0.025 * Math.sin(t * 2.3);
  const earFlap = Math.sin(t * 2.3 - 0.45) * 4.0;
  const tasselSwing = Math.sin(t * 2.6 - 0.70) * 6.0;
  const blink = (t % 3.7 < 0.13);

  // 1. Bóng tiếp xúc mặt đất
  ctx.fillStyle = 'rgba(30, 41, 59, 0.25)';
  ctx.beginPath();
  ctx.ellipse(0, 45, 24 * breathX, 6, 0, 0, Math.PI * 2);
  ctx.fill();

  // 2. Đôi chân thỏ màu hạt dẻ
  ctx.fillStyle = '#A89F91';
  ctx.beginPath();
  ctx.roundRect(-12, 28, 8, 18, 4);
  ctx.roundRect(4, 28, 8, 18, 4);
  ctx.fill();
  ctx.strokeStyle = '#786F63';
  ctx.lineWidth = 1.0;
  ctx.beginPath();
  ctx.moveTo(-8, 42); ctx.lineTo(-8, 46);
  ctx.moveTo(8, 42); ctx.lineTo(8, 46);
  ctx.stroke();

  // 3. Thân thỏ tròn múp míp
  ctx.save();
  ctx.scale(breathX, breathY);
  let bodyGrad = ctx.createRadialGradient(0, 14, 4, 0, 18, 26);
  bodyGrad.addColorStop(0, '#FFFFFF');
  bodyGrad.addColorStop(0.8, '#FAF8F5');
  bodyGrad.addColorStop(1, '#F3EDE2');
  ctx.fillStyle = bodyGrad;
  ctx.beginPath();
  ctx.ellipse(0, 18, 20, 24, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 4. Tay chống nạnh kiêu kỳ & Vòng vàng cổ tay
  for (let side of [-1, 1]) {
    let elbowX = side * 22, handX = side * 14;
    ctx.strokeStyle = '#FAF8F5';
    ctx.lineWidth = 4.0;
    ctx.lineCap = 'round';
    ctx.beginPath();
    ctx.moveTo(side * 14, 8);
    ctx.lineTo(elbowX, 14);
    ctx.lineTo(handX, 20);
    ctx.stroke();

    // Vòng vàng
    ctx.fillStyle = '#F59E0B';
    ctx.fillRect(handX - 2.5, 17, 5, 4);

    // Bàn tay hạt dẻ
    ctx.fillStyle = '#A89F91';
    ctx.beginPath();
    ctx.arc(handX, 21, 3.2, 0, Math.PI * 2);
    ctx.fill();
  }

  // 5. Vòng cổ & Chuông vàng
  ctx.strokeStyle = '#334155';
  ctx.lineWidth = 2.0;
  ctx.beginPath();
  ctx.moveTo(-8, -2); ctx.lineTo(8, -2);
  ctx.stroke();

  let bellGrad = ctx.createRadialGradient(0, 1, 1, 0, 2, 5);
  bellGrad.addColorStop(0, '#FEF08A');
  bellGrad.addColorStop(0.7, '#F59E0B');
  bellGrad.addColorStop(1, '#B45309');
  ctx.fillStyle = bellGrad;
  ctx.beginPath();
  ctx.arc(0, 2, 4.2, 0, Math.PI * 2);
  ctx.fill();

  // 6. Đầu thỏ bầu bĩnh & Má hồng son
  ctx.save();
  ctx.scale(breathX, breathY);
  let headGrad = ctx.createRadialGradient(0, -14, 6, 0, -14, 28);
  headGrad.addColorStop(0, '#FFFFFF');
  headGrad.addColorStop(0.85, '#FAF8F5');
  headGrad.addColorStop(1, '#F3EDE2');
  ctx.fillStyle = headGrad;
  ctx.beginPath();
  ctx.ellipse(0, -14, 26, 20, 0, 0, Math.PI * 2);
  ctx.fill();

  // Má hồng son
  ctx.fillStyle = 'rgba(251, 113, 133, 0.45)';
  ctx.beginPath();
  ctx.ellipse(-16, -10, 4.5, 2.5, 0, 0, Math.PI * 2);
  ctx.ellipse(16, -10, 4.5, 2.5, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 7. Đôi tai cánh tiên xòe rộng & Khuyên vàng tua rua
  for (let side of [-1, 1]) {
    let tipX = side * 56 + side * earFlap;
    let tipY = -8 + earFlap;
    let rootX = side * 16, rootY = -20;

    ctx.save();
    // Cánh lông vũ mềm mại
    let wingGrad = ctx.createLinearGradient(rootX, rootY, tipX, tipY);
    wingGrad.addColorStop(0, '#FAF8F5');
    wingGrad.addColorStop(0.7, '#FFFFFF');
    wingGrad.addColorStop(1, '#A89F91');
    ctx.fillStyle = wingGrad;
    ctx.beginPath();
    ctx.moveTo(rootX, rootY);
    ctx.quadraticCurveTo(side * 36, -26, tipX, tipY);
    ctx.lineTo(side * 50, 4);
    ctx.lineTo(side * 42, 0);
    ctx.lineTo(side * 34, 6);
    ctx.quadraticCurveTo(side * 24, -4, rootX, -10);
    ctx.closePath();
    ctx.fill();
    ctx.strokeStyle = '#D6C7B2';
    ctx.lineWidth = 1.0;
    ctx.stroke();

    // Khuyên vàng kép & Hạt ngọc tròn
    ctx.strokeStyle = '#F59E0B';
    ctx.lineWidth = 1.8;
    ctx.beginPath();
    ctx.arc(tipX, tipY + 6, 4, 0, Math.PI * 2);
    ctx.arc(tipX, tipY + 12, 4, 0, Math.PI * 2);
    ctx.stroke();

    ctx.fillStyle = '#F59E0B';
    ctx.beginPath();
    ctx.arc(tipX, tipY + 17, 3.2, 0, Math.PI * 2);
    ctx.fill();

    // Tua rua lụa trắng đung đưa (Swaying Silk Tassels)
    let swX = tipX + tasselSwing * side;
    let botY = tipY + 32;
    ctx.strokeStyle = '#FFFFFF';
    ctx.lineWidth = 2.0;
    ctx.beginPath();
    ctx.moveTo(tipX, tipY + 19); ctx.lineTo(swX, botY);
    ctx.moveTo(tipX - 1.5, tipY + 19); ctx.lineTo(swX - 2.5, botY);
    ctx.moveTo(tipX + 1.5, tipY + 19); ctx.lineTo(swX + 2.5, botY);
    ctx.stroke();
    ctx.restore();
  }

  // 8. Ấn ký chữ thập đỏ son trước trán (Vermilion Forehead Star)
  ctx.save();
  ctx.strokeStyle = '#EF4444';
  ctx.lineWidth = 2.2;
  ctx.beginPath();
  ctx.moveTo(0, -30); ctx.lineTo(0, -20);
  ctx.moveTo(-4, -25); ctx.lineTo(4, -25);
  ctx.stroke();
  ctx.fillStyle = '#FFFFFF';
  ctx.fillRect(-1, -26, 2, 2);
  ctx.restore();

  // 9. Đôi Mắt Dị Sắc Đồng Tử (Heterochromia 3 Catchlights)
  // Mắt Phải (người xem nhìn vào bên trái): HỔ PHÁCH (#F59E0B)
  let rEyeX = -12, eyeY = -14;
  if (blink) {
    ctx.strokeStyle = '#78350F';
    ctx.lineWidth = 2.2;
    ctx.beginPath();
    ctx.moveTo(rEyeX - 4, eyeY); ctx.lineTo(rEyeX + 4, eyeY);
    ctx.stroke();
  } else {
    let rGrad = ctx.createRadialGradient(rEyeX, eyeY - 1, 1, rEyeX, eyeY, 6);
    rGrad.addColorStop(0, '#FEF08A');
    rGrad.addColorStop(0.5, '#F59E0B');
    rGrad.addColorStop(1, '#78350F');
    ctx.fillStyle = rGrad;
    ctx.beginPath();
    ctx.ellipse(rEyeX, eyeY, 5, 7, 0, 0, Math.PI * 2);
    ctx.fill();

    // Con ngươi Ngôi Sao 4 Cánh vàng
    ctx.strokeStyle = '#FEF08A';
    ctx.lineWidth = 1.2;
    ctx.beginPath();
    ctx.moveTo(rEyeX, eyeY - 2.5); ctx.lineTo(rEyeX, eyeY + 2.5);
    ctx.moveTo(rEyeX - 2.5, eyeY); ctx.lineTo(rEyeX + 2.5, eyeY);
    ctx.stroke();

    // 3 Điểm sáng phản quang
    ctx.fillStyle = '#FFFFFF';
    ctx.beginPath();
    ctx.arc(rEyeX - 2, eyeY - 3, 2.0, 0, Math.PI * 2);
    ctx.arc(rEyeX + 2, eyeY + 1, 1.0, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillStyle = '#FDE68A';
    ctx.beginPath();
    ctx.arc(rEyeX, eyeY + 3, 0.8, 0, Math.PI * 2);
    ctx.fill();
  }

  // Mắt Trái (người xem nhìn vào bên phải): SAPPHIRE (#0284C7)
  let lEyeX = 12;
  if (blink) {
    ctx.strokeStyle = '#082F49';
    ctx.lineWidth = 2.2;
    ctx.beginPath();
    ctx.moveTo(lEyeX - 4, eyeY); ctx.lineTo(lEyeX + 4, eyeY);
    ctx.stroke();
  } else {
    let lGrad = ctx.createRadialGradient(lEyeX, eyeY - 1, 1, lEyeX, eyeY, 6);
    lGrad.addColorStop(0, '#7DD3FC');
    lGrad.addColorStop(0.5, '#0284C7');
    lGrad.addColorStop(1, '#082F49');
    ctx.fillStyle = lGrad;
    ctx.beginPath();
    ctx.ellipse(lEyeX, eyeY, 5, 7, 0, 0, Math.PI * 2);
    ctx.fill();

    // Con ngươi Ngôi Sao 4 Cánh lam
    ctx.strokeStyle = '#7DD3FC';
    ctx.lineWidth = 1.2;
    ctx.beginPath();
    ctx.moveTo(lEyeX, eyeY - 2.5); ctx.lineTo(lEyeX, eyeY + 2.5);
    ctx.moveTo(lEyeX - 2.5, eyeY); ctx.lineTo(lEyeX + 2.5, eyeY);
    ctx.stroke();

    // 3 Điểm sáng phản quang
    ctx.fillStyle = '#FFFFFF';
    ctx.beginPath();
    ctx.arc(lEyeX - 2, eyeY - 3, 2.0, 0, Math.PI * 2);
    ctx.arc(lEyeX + 2, eyeY + 1, 1.0, 0, Math.PI * 2);
    ctx.fill();
    ctx.fillStyle = '#7DD3FC';
    ctx.beginPath();
    ctx.arc(lEyeX, eyeY + 3, 0.8, 0, Math.PI * 2);
    ctx.fill();
  }

  // 10. Miệng cười nhếch mép lém lỉnh
  ctx.strokeStyle = '#786F63';
  ctx.lineWidth = 1.4;
  ctx.beginPath();
  ctx.moveTo(-3, -7); ctx.quadraticCurveTo(-1.5, -5.5, 0, -7); ctx.quadraticCurveTo(1.5, -5.5, 3, -7);
  ctx.stroke();

  ctx.restore();
}"""
    },
    {
        "id": 4,
        "codename": "STAR_KIRIN_CELESTIAL_STAG",
        "name_vi": "Kỳ Lân Sao Star Kirin",
        "name_en": "Star Kirin Celestial Starlight Stag",
        "korean_name": "스타키린 (별빛 사슴)",
        "archetype": "Kỳ Lân Ánh Sao & Bầu Trời Đêm (Cosmic Constellation Kirin)",
        "source_art_reference": "✨ 판타지 동물 도감 (스타키린)",
        "category": "Thần Thú & Linh Thú Rừng Thiêng",
        "mythology_lore": "Thần thú Kirin ánh sao dạo bước trên bầu trời đêm tĩnh lặng. Toàn thân mang sắc xanh đen thăm thẳm của vũ trụ vô tận, lấm tấm vô vàn tinh tú và chòm sao lấp lánh. Đôi sừng vàng rực phân nhánh như cành cây ánh sáng, bờm sao bồng bềnh chuyển sắc cực quang tím biếc, chiếc đuôi sao chổi dẫn lối cho những linh hồn lạc lối giữa màn đêm bao la.",
        "palette": {
            "primary_hex": "#0A0E27",
            "primary_name": "Midnight Cosmic Navy",
            "rgb565_primary": "0x0864",
            "secondary_hex": "#1E2958",
            "secondary_name": "Deep Celestial Blue",
            "rgb565_secondary": "0x194B",
            "mane_indigo_hex": "#6366F1",
            "mane_indigo_name": "Aurora Indigo Nebula Mane",
            "rgb565_mane_indigo": "0x633E",
            "mane_cyan_hex": "#38BDF8",
            "mane_cyan_name": "Starlight Cyan Edge",
            "rgb565_mane_cyan": "0x3DFE",
            "antler_gold_hex": "#F59E0B",
            "antler_gold_name": "Pure Celestial Gold Horns",
            "rgb565_antler_gold": "0xF4E1",
            "star_flare_hex": "#FDE047",
            "star_flare_name": "Luminous Star Flare",
            "rgb565_star_flare": "0xFF08",
            "stardust_hex": "#A5F3FC",
            "stardust_name": "Diamond Stardust Speckles",
            "rgb565_stardust": "0xA7BF",
            "eye_void_hex": "#1E1B4B",
            "rgb565_eye_void": "0x18CA",
            "eye_violet_hex": "#7C3AED",
            "rgb565_eye_violet": "0x79FD"
        },
        "breathing_squash_stretch_specs": {
            "frequency_hz": 0.30,
            "squash_stretch_percent": 5.0,
            "vertical_scale_formula": "1.0 + 0.05 * sin(t * 1.9)",
            "horizontal_volume_formula": "1.0 - 0.025 * sin(t * 1.9)",
            "horn_pulse_formula": "1.0 + 0.30 * sin(t * 3.2)",
            "mane_wave_formula": "sin(t * 1.9 - 0.40) * 4.5",
            "tail_lag_rad": 0.75,
            "tail_lag_formula": "sin(t * 1.9 - 0.75) * 7.0",
            "secondary_inertia_damping": 0.94
        },
        "eye_specs": {
            "eye_type": "cosmic_violet_crystal",
            "blink_interval_ms": 4000,
            "blink_duration_ms": 140,
            "pupil_shape": "starlight_cross_pupil",
            "catchlight_3points": [
                {
                    "point_id": 1,
                    "name": "Pulsing Nova Specular",
                    "dx": -2,
                    "dy": -3,
                    "radius_px": 2.2,
                    "color_hex": "#FFFFFF",
                    "rgb565": "0xFFFF",
                    "role": "Supernova core glint reflection on celestial cornea"
                },
                {
                    "point_id": 2,
                    "name": "Stardust Spark",
                    "dx": 2,
                    "dy": 1,
                    "radius_px": 1.0,
                    "color_hex": "#FDE047",
                    "rgb565": "0xFF08",
                    "role": "Golden constellation stellar spark on iris margin"
                },
                {
                    "point_id": 3,
                    "name": "Nebula Violet Caustic",
                    "dx": -1,
                    "dy": 2,
                    "radius_px": 0.8,
                    "color_hex": "#38BDF8",
                    "rgb565": "0x3DFE",
                    "role": "Lower galactic rim caustic reflection"
                }
            ],
            "pupil_tracking_range_px": {"max_x": 3, "max_y": 2}
        },
        "volumetric_3d_specs": {
            "mesh_topology": "Majestic celestial deer silhouette with branching radiant antlers, flowing cosmic mane and comet plume",
            "light_direction": [-0.5, -0.9, 0.5],
            "ambient_occlusion_passes": [
                "Under-belly deep cosmos depth occlusion",
                "Neck nape mane layering occlusion",
                "Cloven golden hoof shadow"
            ],
            "specular_power": 28.0,
            "rim_light_color": "0xFF08"
        },
        "secondary_motion_specs": {
            "antler_starlight_flare": "Pulsing 4-point cross star flares on each antler tip",
            "nebula_mane_wave": "Harmonic fluid motion simulating galactic gas clouds in stellar wind",
            "constellation_shimmer": "Starlight points on flanks twinkling with sinusoidal phase offsets"
        },
        "visual_breakdown": [
            "Thân hình xanh đen thăm thẳm của bầu trời đêm (#0A0E27) điểm xuyết các chòm sao phát quang",
            "Đôi sừng hoàng kim vương giả phân 3 nhánh phát sáng rực rỡ (#F59E0B, #FDE047)",
            "Chóp các nhánh sừng phát ra chùm tia sao 4 cánh (Star Flares) nhấp nháy theo nhịp thở",
            "Bờm sao bồng bềnh chuyển sắc cực quang từ tím than (#6366F1) sang lam ngọc (#38BDF8)",
            "Chiếc đuôi sao chổi dài thướt tha mang theo bụi sao lấp lánh",
            "Móng guốc thanh mảnh bọc vàng hoàng gia vững chãi",
            "Đôi mắt vũ trụ tím thẫm đính sao vàng với 3 điểm sáng pha lê bất tử"
        ],
        "quote_vi": "Dưới bầu trời đêm vĩnh hằng, vì sao sáng nhất luôn thuộc về em.",
        "shader_effect": "Constellation Twinkle & Galactic Nebula Fluid Drift",
        "cpp_render_snippet": """void drawStarKirin(ScaledCanvas* spr, int cx, int cy, float t) {
  // 1. Nhịp thở Squash & Stretch 5%
  float breathY = 1.0f + 0.05f * sinf(t * 1.9f);
  float breathX = 1.0f - 0.025f * sinf(t * 1.9f);
  float maneWave = sinf(t * 1.9f - 0.40f) * 4.5f;
  float tailLag = sinf(t * 1.9f - 0.75f) * 7.0f;
  float starPulse = 1.0f + 0.35f * sinf(t * 3.2f);
  bool blink = (fmodf(t, 4.0f) < 0.14f);

  // 2. Chiếc đuôi sao chổi lấp lánh (Comet Plume Tail)
  int tx = cx + 22 + (int)tailLag;
  int ty = cy + 10;
  spr->fillCircle(tx - 4, ty + 6, 10, 0x194B);
  spr->fillCircle(tx + 6, ty - 2, 12, 0x633E);
  spr->fillCircle(tx + 8, ty - 14, 8, 0x3DFE);
  spr->drawPixel(tx + 12, ty - 18, 0xFFFF);
  spr->drawPixel(tx + 14, ty - 10, 0xFF08);

  // 3. Bóng tiếp xúc mặt đất
  spr->fillEllipse(cx, cy + 42, (int)(28 * breathX), 6, 0x0864);

  // 4. Bờm sao bồng bềnh (Nebula Mane - Layer sau lưng)
  for (int i = 0; i < 4; i++) {
    int my = cy - 20 + i * 8;
    int mx = cx - 12 - (int)(maneWave * (0.4f + i * 0.2f));
    spr->fillCircle(mx, my, 8 - i, 0x633E);
    spr->fillCircle(mx - 2, my, 6 - i, 0x3DFE);
    spr->drawPixel(mx - 3, my, 0xFFFF);
  }

  // 5. Thân kỳ lân đêm dạ vũ (Midnight Cosmic Body)
  spr->fillEllipse(cx + 2, cy + 18, (int)(20 * breathX), (int)(24 * breathY), 0x0864);
  spr->fillEllipse(cx - 2, cy + 8, (int)(16 * breathX), (int)(18 * breathY), 0x194B);

  // Chòm sao lấp lánh trên hông (Constellation dots)
  spr->drawPixel(cx + 6, cy + 14, 0xFFFF);
  spr->drawPixel(cx + 12, cy + 12, 0xA7BF);
  spr->drawPixel(cx + 14, cy + 20, 0xFFFF);
  spr->drawPixel(cx + 8, cy + 24, 0xA7BF);
  spr->drawLine(cx + 6, cy + 14, cx + 12, cy + 12, 0x194B);
  spr->drawLine(cx + 12, cy + 12, cx + 14, cy + 20, 0x194B);

  // 6. Bốn chân thon mảnh & Móng guốc vàng (Golden Cloven Hooves)
  spr->fillRoundRect(cx - 14, cy + 20, 6, 22, 3, 0x0864);
  spr->fillRoundRect(cx + 8, cy + 20, 6, 22, 3, 0x0864);
  spr->fillRect(cx - 14, cy + 39, 6, 4, 0xF4E1);
  spr->fillRect(cx + 8, cy + 39, 6, 4, 0xF4E1);

  // 7. Đầu hươu sao thanh tú
  spr->fillEllipse(cx - 4, cy - 16, (int)(16 * breathX), (int)(18 * breathY), 0x0864);
  spr->fillEllipse(cx - 10, cy - 14, 10, 8, 0x194B);

  // 8. Đôi sừng hoàng kim phân nhánh tỏa tinh tú (Radiant Branching Horns)
  for (int side = -1; side <= 1; side += 2) {
    int rootX = cx + side * 7, rootY = cy - 28;
    int tip1X = cx + side * 18, tip1Y = cy - 54;
    int tip2X = cx + side * 26, tip2Y = cy - 42;
    int tip3X = cx + side * 10, tip3Y = cy - 44;

    // Nhánh sừng chính
    spr->drawLine(rootX, rootY, tip1X, tip1Y, 0xF4E1);
    spr->drawLine(rootX + side*2, rootY, tip1X + side, tip1Y, 0xFF08);
    // Nhánh phụ 1 & 2
    spr->drawLine(cx + side * 12, cy - 38, tip2X, tip2Y, 0xF4E1);
    spr->drawLine(cx + side * 9, cy - 35, tip3X, tip3Y, 0xF4E1);

    // Chùm tia sao 4 cánh phát quang ở chóp sừng (Star Flares)
    int fLen = (int)(3 * starPulse);
    spr->drawFastVLine(tip1X, tip1Y - fLen, fLen * 2 + 1, 0xFFFF);
    spr->drawFastHLine(tip1X - fLen, tip1Y, fLen * 2 + 1, 0xFFFF);
    spr->fillCircle(tip1X, tip1Y, 2, 0xFF08);

    spr->drawFastVLine(tip2X, tip2Y - 2, 5, 0xFF08);
    spr->drawFastHLine(tip2X - 2, tip2Y, 5, 0xFF08);
  }

  // 9. Mắt Vũ Trụ Tím Thẫm (3 Catchlights Pha Lê)
  int eyeX = cx - 6, eyeY = cy - 17;
  if (blink) {
    spr->drawFastHLine(eyeX - 4, eyeY, 8, 0x18CA);
  } else {
    spr->fillEllipse(eyeX, eyeY, 5, 7, 0x18CA); // Hốc mắt sâu
    spr->fillEllipse(eyeX, eyeY, 4, 6, 0x79FD); // Tròng tím vũ trụ
    spr->fillCircle(eyeX, eyeY + 1, 2, 0x3DFE);  // Ánh vòm ngọc
    // 3 Điểm sáng pha lê
    spr->fillCircle(eyeX - 2, eyeY - 2, 2, 0xFFFF); // Điểm 1: Tinh vân lóa
    spr->drawPixel(eyeX + 1, eyeY + 1, 0xFF08);     // Điểm 2: Tinh tú vàng
    spr->drawPixel(eyeX - 1, eyeY + 2, 0x3DFE);     // Điểm 3: Khúc xạ đáy
  }

  // 10. Chóp mũi & Miệng thanh nhã
  spr->drawPixel(cx - 16, cy - 14, 0x3DFE);
  spr->drawFastHLine(cx - 16, cy - 12, 3, 0x194B);
}""",
        "js_render_snippet": """function drawStarKirin(ctx, cx, cy, scale, t) {
  ctx.save();
  ctx.translate(cx, cy);
  ctx.scale(scale, scale);

  const breathY = 1.0 + 0.05 * Math.sin(t * 1.9);
  const breathX = 1.0 - 0.025 * Math.sin(t * 1.9);
  const maneWave = Math.sin(t * 1.9 - 0.40) * 4.5;
  const tailLag = Math.sin(t * 1.9 - 0.75) * 7.0;
  const starPulse = 1.0 + 0.35 * Math.sin(t * 3.2);
  const blink = (t % 4.0 < 0.14);

  // 1. Chiếc đuôi sao chổi lấp lánh (Comet Plume Tail)
  let tx = 22 + tailLag, ty = 10;
  ctx.save();
  let tailGrad = ctx.createRadialGradient(tx + 6, ty - 4, 2, tx, ty, 24);
  tailGrad.addColorStop(0, '#38BDF8');
  tailGrad.addColorStop(0.5, '#6366F1');
  tailGrad.addColorStop(1, 'rgba(10, 14, 39, 0)');
  ctx.fillStyle = tailGrad;
  ctx.beginPath();
  ctx.arc(tx - 4, ty + 6, 10, 0, Math.PI * 2);
  ctx.arc(tx + 6, ty - 2, 12, 0, Math.PI * 2);
  ctx.arc(tx + 8, ty - 14, 8, 0, Math.PI * 2);
  ctx.fill();

  // Tinh tú bay quanh đuôi
  ctx.fillStyle = '#FFFFFF';
  ctx.beginPath();
  ctx.arc(tx + 12, ty - 18, 1.5, 0, Math.PI * 2);
  ctx.arc(tx + 14, ty - 10, 1.2, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 2. Bóng tiếp xúc mặt đất
  ctx.fillStyle = 'rgba(10, 14, 39, 0.4)';
  ctx.beginPath();
  ctx.ellipse(0, 42, 28 * breathX, 6, 0, 0, Math.PI * 2);
  ctx.fill();

  // 3. Bờm sao bồng bềnh (Nebula Mane)
  ctx.save();
  for (let i = 0; i < 5; i++) {
    let my = -22 + i * 8;
    let mx = -12 - maneWave * (0.4 + i * 0.2);
    let maneGrad = ctx.createRadialGradient(mx, my, 1, mx, my, 10);
    maneGrad.addColorStop(0, '#A5F3FC');
    maneGrad.addColorStop(0.4, '#38BDF8');
    maneGrad.addColorStop(0.8, '#6366F1');
    maneGrad.addColorStop(1, 'rgba(99, 102, 241, 0)');
    ctx.fillStyle = maneGrad;
    ctx.beginPath();
    ctx.arc(mx, my, 9 - i * 0.8, 0, Math.PI * 2);
    ctx.fill();

    // Điểm sao nhấp nháy trong bờm
    ctx.fillStyle = '#FFFFFF';
    ctx.beginPath();
    ctx.arc(mx - 2, my, 1, 0, Math.PI * 2);
    ctx.fill();
  }
  ctx.restore();

  // 4. Thân kỳ lân đêm dạ vũ (Midnight Cosmic Body)
  ctx.save();
  ctx.scale(breathX, breathY);
  let bodyGrad = ctx.createLinearGradient(0, 0, 15, 35);
  bodyGrad.addColorStop(0, '#1E2958');
  bodyGrad.addColorStop(0.6, '#0A0E27');
  bodyGrad.addColorStop(1, '#050714');
  ctx.fillStyle = bodyGrad;
  ctx.beginPath();
  ctx.ellipse(2, 18, 20, 24, 0, 0, Math.PI * 2);
  ctx.ellipse(-2, 8, 16, 18, 0, 0, Math.PI * 2);
  ctx.fill();

  // Chòm sao lấp lánh trên hông (Constellation lines & stars)
  ctx.strokeStyle = 'rgba(56, 189, 248, 0.4)';
  ctx.lineWidth = 0.8;
  ctx.beginPath();
  ctx.moveTo(6, 14); ctx.lineTo(12, 12); ctx.lineTo(14, 20); ctx.lineTo(8, 24);
  ctx.stroke();

  ctx.fillStyle = '#FFFFFF';
  ctx.shadowColor = '#38BDF8';
  ctx.shadowBlur = 6;
  ctx.beginPath();
  ctx.arc(6, 14, 1.5, 0, Math.PI * 2);
  ctx.arc(12, 12, 1.2, 0, Math.PI * 2);
  ctx.arc(14, 20, 1.8, 0, Math.PI * 2);
  ctx.arc(8, 24, 1.2, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 5. Bốn chân thon & Móng guốc vàng
  ctx.fillStyle = '#0A0E27';
  ctx.beginPath();
  ctx.roundRect(-14, 20, 6, 22, 3);
  ctx.roundRect(8, 20, 6, 22, 3);
  ctx.fill();

  ctx.fillStyle = '#F59E0B';
  ctx.fillRect(-14, 39, 6, 4);
  ctx.fillRect(8, 39, 6, 4);

  // 6. Đầu hươu sao thanh tú
  ctx.save();
  ctx.scale(breathX, breathY);
  let headGrad = ctx.createRadialGradient(-6, -16, 2, -4, -16, 18);
  headGrad.addColorStop(0, '#1E2958');
  headGrad.addColorStop(0.8, '#0A0E27');
  headGrad.addColorStop(1, '#050714');
  ctx.fillStyle = headGrad;
  ctx.beginPath();
  ctx.ellipse(-4, -16, 16, 18, 0, 0, Math.PI * 2);
  ctx.ellipse(-10, -14, 10, 8, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();

  // 7. Đôi sừng hoàng kim phân nhánh tỏa tinh tú (Radiant Branching Horns)
  for (let side of [-1, 1]) {
    let rootX = side * 7, rootY = -28;
    let tip1X = side * 18, tip1Y = -54;
    let tip2X = side * 26, tip2Y = -42;
    let tip3X = side * 10, tip3Y = -44;

    ctx.save();
    ctx.strokeStyle = '#F59E0B';
    ctx.lineWidth = 2.4;
    ctx.lineCap = 'round';
    ctx.beginPath();
    ctx.moveTo(rootX, rootY); ctx.lineTo(tip1X, tip1Y);
    ctx.moveTo(side * 12, -38); ctx.lineTo(tip2X, tip2Y);
    ctx.moveTo(side * 9, -35); ctx.lineTo(tip3X, tip3Y);
    ctx.stroke();

    // Chùm tia sao 4 cánh phát quang ở chóp sừng (Star Flares)
    let fLen = 3.5 * starPulse;
    ctx.strokeStyle = '#FFFFFF';
    ctx.lineWidth = 1.6;
    ctx.shadowColor = '#FDE047';
    ctx.shadowBlur = 8;
    ctx.beginPath();
    ctx.moveTo(tip1X, tip1Y - fLen); ctx.lineTo(tip1X, tip1Y + fLen);
    ctx.moveTo(tip1X - fLen, tip1Y); ctx.lineTo(tip1X + fLen, tip1Y);
    ctx.stroke();

    ctx.fillStyle = '#FEF08A';
    ctx.beginPath();
    ctx.arc(tip1X, tip1Y, 2.2, 0, Math.PI * 2);
    ctx.fill();

    ctx.strokeStyle = '#FDE047';
    ctx.lineWidth = 1.0;
    ctx.beginPath();
    ctx.moveTo(tip2X, tip2Y - 2.5); ctx.lineTo(tip2X, tip2Y + 2.5);
    ctx.moveTo(tip2X - 2.5, tip2Y); ctx.lineTo(tip2X + 2.5, tip2Y);
    ctx.stroke();
    ctx.restore();
  }

  // 8. Mắt Vũ Trụ Tím Thẫm (3 Catchlights)
  let eyeX = -6, eyeY = -17;
  if (blink) {
    ctx.strokeStyle = '#1E1B4B';
    ctx.lineWidth = 2.2;
    ctx.beginPath();
    ctx.moveTo(eyeX - 4, eyeY); ctx.lineTo(eyeX + 4, eyeY);
    ctx.stroke();
  } else {
    let eyeGrad = ctx.createRadialGradient(eyeX, eyeY - 1, 1, eyeX, eyeY, 6);
    eyeGrad.addColorStop(0, '#A855F7');
    eyeGrad.addColorStop(0.5, '#6366F1');
    eyeGrad.addColorStop(1, '#0A0E27');
    ctx.fillStyle = eyeGrad;
    ctx.beginPath();
    ctx.ellipse(eyeX, eyeY, 5, 7, 0, 0, Math.PI * 2);
    ctx.fill();

    // 3 Điểm sáng phản quang
    ctx.fillStyle = '#FFFFFF';
    ctx.beginPath();
    ctx.arc(eyeX - 2, eyeY - 2.5, 2.0, 0, Math.PI * 2); // Điểm 1: Tinh vân lóa
    ctx.fill();

    ctx.fillStyle = '#FDE047';
    ctx.beginPath();
    ctx.arc(eyeX + 1.2, eyeY + 1, 1.0, 0, Math.PI * 2);  // Điểm 2: Tinh tú vàng
    ctx.fill();

    ctx.fillStyle = '#38BDF8';
    ctx.beginPath();
    ctx.arc(eyeX - 0.5, eyeY + 2.5, 0.8, 0, Math.PI * 2); // Điểm 3: Khúc xạ đáy
    ctx.fill();
  }

  // 9. Mũi & Miệng thanh nhã
  ctx.fillStyle = '#38BDF8';
  ctx.beginPath();
  ctx.arc(-16, -14, 1.5, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = '#1E2958';
  ctx.lineWidth = 1.0;
  ctx.beginPath();
  ctx.moveTo(-16, -12); ctx.lineTo(-13, -12);
  ctx.stroke();

  ctx.restore();
}"""
    }
]

output_dir = os.path.join(os.path.dirname(__file__), "..", "data")
os.makedirs(output_dir, exist_ok=True)
output_path = os.path.join(output_dir, "agent3_fantasy_beasts.json")

with open(output_path, "w", encoding="utf-8") as f:
    json.dump(beasts, f, ensure_ascii=False, indent=2)

print(f"Successfully generated {len(beasts)} fantasy beasts at: {output_path}")
