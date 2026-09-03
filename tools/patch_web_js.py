import re

with open('server/app/main.py', 'r', encoding='utf-8') as f:
    code = f.read()

# 1. Add state variables in JS
old_js_vars = '''    let currentSpriteId = 0;
    let currentPaletteId = 0;
    let currentQuote = "";
    let time = 0;'''

new_js_vars = '''    let currentSpriteId = 0;
    let currentPaletteId = 0;
    let currentQuote = "";
    let currentTextColor = "#FFB800";
    let currentTextSize = 1;
    let currentSceneryId = 0;
    let time = 0;

    let designDebounceTimer = null;
    function sendDesignDebounced(payload) {
      if (designDebounceTimer) clearTimeout(designDebounceTimer);
      designDebounceTimer = setTimeout(() => {
        sendDesign(payload);
      }, 100);
    }

    function sendDesign(payload) {
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({ action: "SET_DESIGN", ...payload }));
      }
    }

    function setTextColorChoice(hex, btn) {
      currentTextColor = hex;
      document.querySelectorAll('#textColorGrid .gem-btn').forEach(b => b.classList.remove('active'));
      if (btn) btn.classList.add('active');
      const picker = document.getElementById('customColorInput');
      if (picker) picker.value = hex;
      sendDesign({ text_color: hex });
    }

    function onCustomColorInput(hex) {
      currentTextColor = hex;
      document.querySelectorAll('#textColorGrid .gem-btn').forEach(b => b.classList.remove('active'));
      sendDesignDebounced({ text_color: hex });
    }

    function onCustomColorCommit(hex) {
      currentTextColor = hex;
      sendDesign({ text_color: hex });
    }

    function setTextSizeChoice(sz) {
      currentTextSize = sz;
      const b1 = document.getElementById('btnSize1');
      const b2 = document.getElementById('btnSize2');
      if (b1) b1.classList.toggle('active', sz === 1);
      if (b2) b2.classList.toggle('active', sz === 2);
      sendDesign({ text_size: sz });
    }

    function setSceneryChoice(id, btn) {
      currentSceneryId = id;
      document.querySelectorAll('#sceneryGrid .gem-btn').forEach(b => b.classList.remove('active'));
      if (btn) btn.classList.add('active');
      sendDesign({ scenery_id: id });
    }'''

if old_js_vars in code:
    code = code.replace(old_js_vars, new_js_vars)
    print("Added JS state and handlers!")

# 2. Update SYNC handling in onmessage
old_sync = '''        if (msg.type === "SYNC" || msg.type === "UPDATE") {
          const d = msg.data;
          if (d.sprite_id !== undefined) currentSpriteId = d.sprite_id;
          if (d.palette_id !== undefined) currentPaletteId = d.palette_id;
          if (d.quote !== undefined) currentQuote = d.quote;
          if (d.brightness !== undefined) {
            document.getElementById('brightRange').value = d.brightness;
            document.getElementById('brightVal').innerText = `${Math.round(d.brightness / 255 * 100)}%`;
          }
          highlightActiveTheme(currentSpriteId);
        }'''

new_sync = '''        if (msg.type === "SYNC" || msg.type === "UPDATE") {
          const d = msg.data;
          if (d.sprite_id !== undefined) currentSpriteId = d.sprite_id;
          if (d.palette_id !== undefined) currentPaletteId = d.palette_id;
          if (d.quote !== undefined) currentQuote = d.quote;
          if (d.text_color !== undefined) {
            currentTextColor = d.text_color;
            const picker = document.getElementById('customColorInput');
            if (picker) picker.value = currentTextColor;
          }
          if (d.text_size !== undefined) {
            currentTextSize = d.text_size;
            const b1 = document.getElementById('btnSize1');
            const b2 = document.getElementById('btnSize2');
            if (b1) b1.classList.toggle('active', currentTextSize === 1);
            if (b2) b2.classList.toggle('active', currentTextSize === 2);
          }
          if (d.scenery_id !== undefined) {
            currentSceneryId = d.scenery_id;
            const btns = document.querySelectorAll('#sceneryGrid .gem-btn');
            btns.forEach((b, idx) => b.classList.toggle('active', idx === currentSceneryId));
          }
          if (d.brightness !== undefined) {
            document.getElementById('brightRange').value = d.brightness;
            document.getElementById('brightVal').innerText = `${Math.round(d.brightness / 255 * 100)}%`;
          }
          highlightActiveTheme(currentSpriteId);
        }'''

if old_sync in code:
    code = code.replace(old_sync, new_sync)
    print("Updated SYNC handling in JS!")

# 3. Replace loop() with Living Scenery, Contact Shadow, and Marquee Window Clipping (NO DIALOGUE BOX)
old_loop_pattern = re.compile(r'// 60 FPS MAIN LOOP\s+function loop\(\) \{[\s\S]+?requestAnimationFrame\(loop\);\s+\}', re.MULTILINE)

new_loop_func = '''    // 60 FPS MAIN LOOP (1:1 VỚI ESP32)
    function loop() {
      time += 0.045;

      // 1. Nền đen thuần AMOLED #000000
      heroCtx.fillStyle = '#000000';
      heroCtx.fillRect(0, 0, 172, 320);

      // 2. LAYER 0: HỆ THỐNG 5 LIVING DIORAMAS ĐA TẦNG
      switch (currentSceneryId) {
        case 0: // SCENE_COZY_BEDROOM
          heroCtx.fillStyle = '#182010';
          heroCtx.fillRect(0, 270, 172, 50);
          heroCtx.fillStyle = '#212220';
          heroCtx.fillRect(0, 290, 172, 30);
          heroCtx.strokeStyle = '#4a694a';
          heroCtx.lineWidth = 1;
          heroCtx.strokeRect(12, 42, 28, 38);
          heroCtx.beginPath(); heroCtx.moveTo(26, 42); heroCtx.lineTo(26, 80); heroCtx.stroke();
          heroCtx.beginPath(); heroCtx.moveTo(12, 61); heroCtx.lineTo(40, 61); heroCtx.stroke();
          heroCtx.fillStyle = '#ffe000';
          heroCtx.beginPath(); heroCtx.arc(22, 54, 6, 0, Math.PI*2); heroCtx.fill();
          for (let i = 0; i < 6; i++) {
            let px = 20 + i * 24 + Math.sin(time * 0.5 + i) * 6.0;
            let py = 300 - ((Date.now() / 30 + i * 40) % 240);
            heroCtx.fillStyle = (i % 2 === 0) ? '#fde080' : '#fca060';
            heroCtx.fillRect(px, py, 2, 2);
          }
          break;

        case 1: // SCENE_SAKURA_DUSK
          heroCtx.fillStyle = '#200420';
          heroCtx.fillRect(0, 260, 172, 60);
          heroCtx.fillStyle = '#180318';
          heroCtx.fillRect(0, 285, 172, 35);
          heroCtx.fillStyle = '#294545';
          heroCtx.beginPath(); heroCtx.moveTo(0, 320); heroCtx.lineTo(50, 275); heroCtx.lineTo(110, 320); heroCtx.fill();
          heroCtx.fillStyle = '#18c3c3';
          heroCtx.beginPath(); heroCtx.moveTo(70, 320); heroCtx.lineTo(130, 265); heroCtx.lineTo(172, 320); heroCtx.fill();
          heroCtx.fillStyle = '#b00000';
          heroCtx.fillRect(135, 275, 4, 35); heroCtx.fillRect(155, 275, 4, 35);
          heroCtx.fillStyle = '#f80000';
          heroCtx.fillRect(130, 278, 34, 4);
          for (let i = 0; i < 8; i++) {
            let px = (Math.sin(time * 0.7 + i * 1.3) * 35.0 + 22.0 * i + 172) % 172;
            let py = (time * 26.0 + i * 45) % 320;
            heroCtx.fillStyle = '#ff7597';
            heroCtx.fillRect(px, py, 2, 2);
          }
          break;

        case 2: // SCENE_CYBER_RAIN
          heroCtx.fillStyle = '#084141';
          heroCtx.fillRect(6, 275, 26, 45); heroCtx.fillRect(76, 280, 24, 40); heroCtx.fillRect(142, 285, 24, 35);
          heroCtx.fillStyle = '#108282';
          heroCtx.fillRect(38, 258, 32, 62); heroCtx.fillRect(106, 262, 30, 58);
          heroCtx.fillStyle = '#00f0ff';
          heroCtx.fillRect(46, 268, 2, 2); heroCtx.fillRect(114, 270, 2, 2);
          heroCtx.fillStyle = '#ffb800';
          heroCtx.fillRect(54, 278, 2, 2);
          heroCtx.strokeStyle = 'rgba(0, 240, 255, 0.45)';
          heroCtx.lineWidth = 1;
          for (let i = 0; i < 10; i++) {
            let rx = (i * 18 + Math.floor(Date.now() / 8)) % 172;
            let ry = (i * 37 + Math.floor(Date.now() / 2)) % 320;
            heroCtx.beginPath(); heroCtx.moveTo(rx, ry); heroCtx.lineTo(rx - 3, ry + 7); heroCtx.stroke();
          }
          break;

        case 3: // SCENE_MAGIC_FOREST
          heroCtx.fillStyle = '#01a050';
          heroCtx.fillRect(0, 275, 172, 45);
          heroCtx.fillStyle = '#318040';
          heroCtx.fillRect(0, 230, 16, 90);
          heroCtx.fillStyle = '#00f0ff';
          heroCtx.beginPath(); heroCtx.arc(38, 298, 5, 0, Math.PI*2); heroCtx.fill();
          heroCtx.fillStyle = '#00ff88';
          heroCtx.beginPath(); heroCtx.arc(128, 304, 4, 0, Math.PI*2); heroCtx.fill();
          for (let i = 0; i < 7; i++) {
            let fx = Math.cos(time * 0.7 + i * 1.4) * 45.0 + 86.0;
            let fy = Math.sin(time * 0.5 + i * 1.8) * 40.0 + 160.0;
            let glow = (Math.sin(time * 3.0 + i * 2.0) + 1.0) * 0.5;
            if (glow > 0.3) {
              heroCtx.fillStyle = (i % 2 === 0) ? '#ffb800' : '#00f0ff';
              heroCtx.fillRect(fx, fy, 2, 2);
            }
          }
          break;

        case 4: // SCENE_OCEAN_SUNSET
          heroCtx.fillStyle = '#814020';
          heroCtx.fillRect(0, 240, 172, 80);
          heroCtx.fillStyle = '#fa4000';
          heroCtx.beginPath(); heroCtx.arc(86, 245, 20, 0, Math.PI*2); heroCtx.fill();
          for (let layer = 0; layer < 3; layer++) {
            let yBase = 255 + layer * 18;
            heroCtx.fillStyle = (layer === 0) ? '#021040' : ((layer === 1) ? '#018c60' : '#00e880');
            heroCtx.fillRect(0, yBase, 172, 20);
            heroCtx.fillStyle = '#fde080';
            for (let x = 0; x < 172; x += 8) {
              let wy = yBase + Math.sin(time * 2.0 + x * 0.08 + layer) * 3.0;
              heroCtx.fillRect(x, wy, 5, 1);
            }
          }
          break;
      }

      // 3. LAYER 1: VẬT LÝ BÓNG TIẾP XÚC CO GIÃN (CONTACT SHADOW MICRO-PHYSICS) TỶ LỆ NGHỊCH
      let hover = -Math.sin(time); // > 0 khi bay cao
      let rx = 22 - hover * 5;
      let ry = 5 - hover * 1.5;
      heroCtx.fillStyle = (hover > 0.1) ? 'rgba(8, 12, 20, 0.4)' : 'rgba(2, 4, 8, 0.85)';
      heroCtx.beginPath();
      heroCtx.ellipse(86, 202, Math.max(12, rx), Math.max(3, ry), 0, 0, Math.PI * 2);
      heroCtx.fill();

      // 4. LAYER 2: ANIMATION 2.5D VOLUMETRIC TẠI TRUNG TÂM (86, 160 + sin*6)
      let cy = 160 + Math.sin(time) * 6.0;
      renderSpecificAnimation(heroCtx, currentSpriteId, 86, cy, 1.0, time);

      // 5. LAYER 3: CHỮ TIẾNG VIỆT CÓ DẤU 100% VỚI WINDOW CLIPPING & MARQUEE 3 PHA
      heroCtx.save();
      heroCtx.beginPath();
      heroCtx.rect(8, 8, 156, 26);
      heroCtx.clip();

      let topText = currentQuote || (CATALOG[currentSpriteId] ? CATALOG[currentSpriteId].quote : 'Dù ở thế giới nào, anh vẫn luôn tìm thấy em.');
      let fontSize = (currentTextSize >= 2) ? 14 : 11;
      heroCtx.font = `bold ${fontSize}px -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif`;
      let textW = heroCtx.measureText(topText).width;
      let viewW = 156;
      let topY = 22;

      if (textW <= viewW) {
        let x = 8 + (viewW - textW) / 2;
        heroCtx.fillStyle = '#000000';
        heroCtx.fillText(topText, x + 1, topY + 1);
        heroCtx.fillStyle = currentTextColor;
        heroCtx.fillText(topText, x, topY);
      } else {
        let maxScroll = textW - viewW + 36;
        let scrollDur = maxScroll * 35;
        let cycle = 2000 + scrollDur + 2000 + 200;
        let t = Date.now() % cycle;
        let xOffset = 0;
        if (t < 2000) {
          xOffset = 0;
        } else if (t < 2000 + scrollDur) {
          xOffset = Math.floor((t - 2000) / 35);
        } else if (t < 2000 + scrollDur + 2000) {
          xOffset = maxScroll;
        } else {
          xOffset = 0;
        }
        let x = 8 - xOffset;
        heroCtx.fillStyle = '#000000';
        heroCtx.fillText(topText, x + 1, topY + 1);
        heroCtx.fillStyle = currentTextColor;
        heroCtx.fillText(topText, x, topY);
      }
      heroCtx.restore();

      // 6. RENDER 50 MINI CARDS
      CATALOG.forEach(item => {
        const card = document.getElementById(`card-${item.id}`);
        if (card && card.style.display !== 'none') {
          const mini = document.getElementById(`mini-${item.id}`);
          if (mini) {
            const mCtx = mini.getContext('2d');
            mCtx.fillStyle = '#000000';
            mCtx.fillRect(0, 0, 72, 72);
            renderSpecificAnimation(mCtx, item.id, 36, 36, 0.9, time);
          }
        }
      });

      requestAnimationFrame(loop);
    }'''

code = old_loop_pattern.sub(new_loop_func, code)
print("Replaced loop() with Living Scenery, Contact Shadow, and Marquee Window Clipping!")

with open('server/app/main.py', 'w', encoding='utf-8') as f:
    f.write(code)
print("patch_web_js.py completed successfully!")
