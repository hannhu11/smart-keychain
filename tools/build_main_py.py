import re

with open('server/app/main.py', 'r', encoding='utf-8') as f:
    code = f.read()

# 1. Update Left Pod HTML to include God-Mode Controls (Text Color, Text Size, 5 Sceneries)
old_palette_section = '''      <!-- PALETTES -->
      <div class="control-group">
        <div class="control-label">Bảng Màu Kim Cương</div>
        <div class="gem-palette-grid">
          <button class="gem-btn active" onclick="setPaletteChoice(0)"><div class="gem-circle" style="background:#00f0ff;"></div>Băng Neon</button>
          <button class="gem-btn" onclick="setPaletteChoice(1)"><div class="gem-circle" style="background:#ff0055;"></div>Ruby Pink</button>
          <button class="gem-btn" onclick="setPaletteChoice(2)"><div class="gem-circle" style="background:#ffb800;"></div>Hổ Phách</button>
          <button class="gem-btn" onclick="setPaletteChoice(3)"><div class="gem-circle" style="background:#fcaeae;"></div>Anya Pastel</button>
          <button class="gem-btn" onclick="setPaletteChoice(4)"><div class="gem-circle" style="background:#00ff88;"></div>Ma Trận</button>
          <button class="gem-btn" onclick="setPaletteChoice(5)"><div class="gem-circle" style="background:#9d00ff;"></div>Galaxy</button>
        </div>
      </div>'''

new_god_mode_section = '''      <!-- GOD-MODE DESIGN STUDIO CONTROLS -->
      <!-- 1. TEXT COLOR -->
      <div class="control-group">
        <div class="control-label" style="display:flex; justify-content:space-between; align-items:center;">
          <span>Màu Chữ Hoàng Gia</span>
          <input type="color" id="customColorInput" value="#ffb800" style="width:24px; height:24px; border:none; border-radius:50%; cursor:pointer; background:none;" oninput="onCustomColorInput(this.value)" onchange="onCustomColorCommit(this.value)">
        </div>
        <div class="gem-palette-grid" id="textColorGrid">
          <button class="gem-btn active" onclick="setTextColorChoice('#FFB800', this)"><div class="gem-circle" style="background:#ffb800;"></div>Vàng Kim</button>
          <button class="gem-btn" onclick="setTextColorChoice('#FFFFFF', this)"><div class="gem-circle" style="background:#ffffff;"></div>Trắng KC</button>
          <button class="gem-btn" onclick="setTextColorChoice('#00F0FF', this)"><div class="gem-circle" style="background:#00f0ff;"></div>Xanh Neon</button>
          <button class="gem-btn" onclick="setTextColorChoice('#FF7597', this)"><div class="gem-circle" style="background:#ff7597;"></div>Hồng Sakura</button>
          <button class="gem-btn" onclick="setTextColorChoice('#00FF88', this)"><div class="gem-circle" style="background:#00ff88;"></div>Xanh Ngọc</button>
          <button class="gem-btn" onclick="setTextColorChoice('#B388FF', this)"><div class="gem-circle" style="background:#b388ff;"></div>Tím Galaxy</button>
        </div>
      </div>

      <!-- 2. TEXT SIZE -->
      <div class="control-group">
        <div class="control-label">Kích Cỡ Chữ Màn Hình</div>
        <div style="display:grid; grid-template-columns: 1fr 1fr; gap:8px;">
          <button id="btnSize1" class="gem-btn active" onclick="setTextSizeChoice(1)">Tiêu Chuẩn (16px)</button>
          <button id="btnSize2" class="gem-btn" onclick="setTextSizeChoice(2)">Nét To Rõ (24px)</button>
        </div>
      </div>

      <!-- 3. LIVING DIORAMAS (5 BỐI CẢNH) -->
      <div class="control-group">
        <div class="control-label">Bối Cảnh Sống (5 Dioramas)</div>
        <div class="gem-palette-grid" id="sceneryGrid">
          <button class="gem-btn active" onclick="setSceneryChoice(0, this)">🛏️ Phòng Ngủ</button>
          <button class="gem-btn" onclick="setSceneryChoice(1, this)">🌸 Anh Đào</button>
          <button class="gem-btn" onclick="setSceneryChoice(2, this)">🌧️ Mưa Cyber</button>
          <button class="gem-btn" onclick="setSceneryChoice(3, this)">🍄 Rừng Đom Đóm</button>
          <button class="gem-btn" onclick="setSceneryChoice(4, this)">🌊 Biển Chiều</button>
        </div>
      </div>'''

if old_palette_section in code:
    code = code.replace(old_palette_section, new_god_mode_section)
    print("Injected God-Mode UI controls into HTML!")

# 2. Replace Case 32, 33, 34 in renderSpecificAnimation in JavaScript
old_case_32_34 = '''        case 32: {
          // Mèo Vũ Trụ Cosmic Cat
          dCirc(ctx, 0, 0, 32, "#4a4c4a");
          dCirc(ctx, 0, 0, 33, "#7b7d7b");
          frRect(ctx, -18, -12, 36, 26, 7, "#ffffff");
          fTri(ctx, -18, -12, -12, -26, -6, -12, "#ffffff");
          fTri(ctx, 6, -12, 12, -26, 18, -12, "#ffffff");
          fTri(ctx, -15, -12, -12, -22, -9, -12, "#ff9573");
          fTri(ctx, 9, -12, 12, -22, 15, -12, "#ff9573");
          dArc(ctx, -8, -4, 4, 3, 0, 180, "#000000");
          dArc(ctx, 8, -4, 4, 3, 0, 180, "#000000");
          fCirc(ctx, 0, 2, 2, "#ff00ff");
          break;
        }

        case 33: {
          // Cún Cyber Shiba Inu
          frRect(ctx, -24, -20, 48, 38, 8, "#ffb683");
          frRect(ctx, -16, -2, 32, 20, 6, "#ffffff");
          fTri(ctx, -24, -20, -16, -36, -8, -20, "#ffb683");
          fTri(ctx, 8, -20, 16, -36, 24, -20, "#ffb683");
          frRect(ctx, -18, -8, 36, 8, 2, "#00f0ff");
          dLine(ctx, -16, -5, -16 + 32, -5, "#ffffff");
          dCirc(ctx, 26, 8 + (Math.sin(angle * 8) * 3), 6, "#ffb683");
          break;
        }

        case 34: {
          // Khủng Long Axolotl Trà Sữa (Boba Dinosaur)
          frRect(ctx, -22, -22, 44, 40, 8, "#ffa1ac");
          fCirc(ctx, -26, -16, 6, "#ff00ff");
          fCirc(ctx, -26, -4, 6, "#ff00ff");
          fCirc(ctx, 26, -16, 6, "#ff00ff");
          fCirc(ctx, 26, -4, 6, "#ff00ff");
          frRect(ctx, -8, 6, 16, 20, 3, "#ffff94");
          fCirc(ctx, -4, 20, 2, "#000000");
          fCirc(ctx, 4, 20, 2, "#000000");
          dLine(ctx, 0, -2, 0, -2 + 10, "#00be00");
          break;
        }'''

new_case_32_34 = '''        case 32: {
          // Mèo Con Cuộn Tròn 2.5D Volumetric
          let blink = ((Date.now() % 3500) >= 3350);
          let tailWave = Math.sin(t * 3.5) * 6.0;
          let earTwitch = Math.sin(t * 7.0) * 2.0;

          // Đuôi ngoáy nhịp nhàng phía sau
          dArc(ctx, 18, 8, 14, 16, 260 + tailWave, 360 + tailWave, "#ed8000");
          fCirc(ctx, 18 + Math.cos((360+tailWave)*0.0174)*15.0, 8 + Math.sin((360+tailWave)*0.0174)*15.0, 3, "#ffffff");

          // Thân cuộn tròn 2.5D (Shadow -> Midtone -> Highlight)
          fCirc(ctx, 0, 4, 24, "#8b0000");
          fCirc(ctx, 0, 3, 23, "#ed8000");
          fCirc(ctx, -4, 0, 15, "#ffa040");

          // Tai vẫy
          fTri(ctx, -18, -14, -12 + earTwitch, -28, -4, -14, "#ed8000");
          fTri(ctx, -16, -14, -12 + earTwitch, -25, -6, -14, "#fbaeae");
          fTri(ctx, 4, -14, 12 - earTwitch, -28, 18, -14, "#ed8000");
          fTri(ctx, 6, -14, 12 - earTwitch, -25, 16, -14, "#fbaeae");

          // Mặt bầu bĩnh & mắt nhắm
          fCirc(ctx, -12, 2, 11, "#ed8000");
          fCirc(ctx, -12, 5, 8, "#ffffff");
          if (blink) {
            fCirc(ctx, -14, -1, 3, "#000000");
          } else {
            dArc(ctx, -14, -1, 4, 3, 180, 360, "#300000");
          }
          fTri(ctx, -19, 2, -17, 2, -18, 4, "#fbaeae");
          dLine(ctx, -24, 1, -20, 1, "#8b0000");
          dLine(ctx, -24, 4, -20, 4, "#8b0000");
          break;
        }

        case 33: {
          // Cún Cyber Shiba Inu 2.5D Volumetric
          let blink = ((Date.now() % 3500) >= 3350);
          let tailWave = Math.sin(t * 6.0) * 4.0;
          dArc(ctx, 22, -4, 8, 10, 0, 240, "#ffb683");
          fCirc(ctx, 26 + tailWave, -6, 4, "#ffffff");
          frRect(ctx, -24, -18, 48, 36, 12, "#c44000");
          frRect(ctx, -23, -19, 46, 35, 11, "#fdb000");
          frRect(ctx, -16, -2, 32, 18, 6, "#ffffff");
          fTri(ctx, -22, -18, -16, -34, -8, -18, "#fdb000");
          fTri(ctx, -20, -18, -16, -31, -10, -18, "#fbaeae");
          fTri(ctx, 8, -18, 16, -34, 22, -18, "#fdb000");
          fTri(ctx, 10, -18, 16, -31, 20, -18, "#fbaeae");
          frRect(ctx, -18, -8, 36, 8, 3, "#00f0ff");
          dLine(ctx, -16, -5, 16, -5, "#ffffff");
          fCirc(ctx, 0, 4, 2, "#000000");
          break;
        }

        case 34: {
          // Kỳ Nhông Axolotl 2.5D Volumetric Glow (1:1 VỚI ESP32)
          let blink = ((Date.now() % 3500) >= 3350);
          let wave = Math.sin(t * 4.0);
          let tailW = Math.sin(t * 3.0);

          // 1. Đuôi uốn lượn
          let tx = (tailW * 10.0);
          fTri(ctx, -8, 10, 8, 10, tx, 34, "#fd1580");
          fTri(ctx, -4, 10, 4, 10, tx, 32, "#fbaeae");

          // 2. Thân 3 dải màu Volumetric
          frRect(ctx, -24, -18, 48, 36, 14, "#c26e80");
          frRect(ctx, -23, -20, 46, 35, 13, "#fbaeae");
          frRect(ctx, -18, -22, 36, 18, 9, "#ff7597");

          // 3. 3 Nhánh mang xòe mềm mại
          for (let g = 0; g < 3; g++) {
            let gAngle = wave + g * 0.5;
            let gxL = -24 - Math.cos(gAngle) * 8.0;
            let gyL = -14 + g * 8 + Math.sin(gAngle) * 4.0;
            fCirc(ctx, gxL, gyL, 5 - g, "#f81f80");
            fCirc(ctx, gxL + 2, gyL, 3, "#fd1580");

            let gxR = 24 + Math.cos(gAngle) * 8.0;
            let gyR = -14 + g * 8 + Math.sin(gAngle) * 4.0;
            fCirc(ctx, gxR, gyR, 5 - g, "#f81f80");
            fCirc(ctx, gxR - 2, gyR, 3, "#fd1580");
          }

          // 4. Bụng kem
          frRect(ctx, -14, -2, 28, 16, 7, "#fff8f8");

          // 5. Mắt long lanh
          if (blink) {
            dLine(ctx, -14, -8, -6, -8, "#300000");
            dLine(ctx, 6, -8, 14, -8, "#300000");
          } else {
            fCirc(ctx, -10, -8, 5, "#000000");
            fCirc(ctx, -11, -10, 2, "#ffffff");
            dPixel(ctx, -8, -6, "#ffffff");

            fCirc(ctx, 10, -8, 5, "#000000");
            fCirc(ctx, 9, -10, 2, "#ffffff");
            dPixel(ctx, 12, -6, "#ffffff");
          }

          // 6. Má hồng & miệng
          fCirc(ctx, -16, -1, 3, "#f81f80");
          fCirc(ctx, 16, -1, 3, "#f81f80");
          dArc(ctx, 0, -2, 4, 3, 0, 180, "#800000");

          // 7. Chân bơi
          fCirc(ctx, -16, 14, 4, "#fbaeae");
          fCirc(ctx, 16, 14, 4, "#fbaeae");
          break;
        }'''

if old_case_32_34 in code:
    code = code.replace(old_case_32_34, new_case_32_34)
    print("Updated Case 32, 33, 34 in JavaScript canvas!")

# 3. Update Case 12 Excalibur in JavaScript canvas
old_case_12 = '''        case 12: {
          // Thanh Kiếm Thánh Excalibur
          fTri(ctx, 0, -58, -7, 20, 0, 20, "#ffffff");
          fTri(ctx, 0, -58, 0, 20, 7, 20, "#ce9e00");
          dLine(ctx, 0, -56, 0, -56 + 74, "#00f0ff");
          frRect(ctx, -20, 20, 40, 10, 3, "#ffee00");
          fCirc(ctx, 0, 25, 4, "#0000ff");
          fRect(ctx, -4, 30, 8, 22, "#4a4c4a");
          fCirc(ctx, 0, 54, 6, "#ffee00");
          break;
        }'''

new_case_12 = '''        case 12: {
          // Thanh Kiếm Thánh Excalibur 3D Bevel Metal
          let shineY = (-45) + Math.floor((Date.now() / 25) % 65);
          fRect(ctx, -5, -35, 5, 55, "#ffffff");
          fRect(ctx, 0, -35, 5, 55, "#848284");
          fTri(ctx, -5, -35, 0, -52, 0, -35, "#ffffff");
          fTri(ctx, 0, -35, 0, -52, 5, -35, "#848284");
          dLine(ctx, 0, -48, 0, 17, "#00f0ff");
          if (shineY >= -48 && shineY <= 18) {
            fCirc(ctx, 0, shineY, 4, "#ffffff");
            dPixel(ctx, -2, shineY, "#ffee00");
            dPixel(ctx, 2, shineY, "#ffee00");
            dPixel(ctx, 0, shineY - 2, "#ffee00");
            dPixel(ctx, 0, shineY + 2, "#ffee00");
          }
          frRect(ctx, -20, 20, 40, 8, 3, "#ffee00");
          fRect(ctx, -16, 22, 32, 2, "#fbe000");
          fCirc(ctx, 0, 24, 4, "#ff0000");
          dCirc(ctx, 0, 24, 4, "#ffee00");
          fRect(ctx, -3, 28, 6, 20, "#001440");
          for (let r = 0; r < 4; r++) {
            dLine(ctx, -3, 30 + r * 5, 3, 30 + r * 5, "#ffee00");
          }
          fCirc(ctx, 0, 50, 6, "#ffee00");
          break;
        }'''

if old_case_12 in code:
    code = code.replace(old_case_12, new_case_12)
    print("Updated Case 12 Excalibur in JavaScript canvas!")

with open('server/app/main.py', 'w', encoding='utf-8') as f:
    f.write(code)
print("build_main_py.py completed!")
