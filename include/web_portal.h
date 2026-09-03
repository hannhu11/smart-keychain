#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "config.h"

class WebPortal {
private:
  DNSServer dnsServer;
  AsyncWebServer server;
  bool isRunning = false;
  unsigned long apStartTime = 0;

  std::function<void(int)> onSelectSprite;
  std::function<void(int)> onSelectPalette;
  std::function<void(String)> onAddQuote;
  std::function<void(int)> onSetBrightness;
  std::function<void(String, String)> onConfigureWifi;

public:
  WebPortal() : server(80) {}

  void setCallbacks(
    std::function<void(int)> fnSprite,
    std::function<void(int)> fnPalette,
    std::function<void(String)> fnQuote,
    std::function<void(int)> fnBrightness,
    std::function<void(String, String)> fnWifi = nullptr
  ) {
    onSelectSprite = fnSprite;
    onSelectPalette = fnPalette;
    onAddQuote = fnQuote;
    onSetBrightness = fnBrightness;
    onConfigureWifi = fnWifi;
  }

  void start() {
    if (isRunning) return;

    Serial.println("[Wi-Fi] Đang kích hoạt SoftAP Love_Keychain với tốc độ cao...");
    WiFi.setSleep(false);
    esp_wifi_set_ps(WIFI_PS_NONE);

    dnsServer.start(53, "*", WiFi.softAPIP());

    setupWebRoutes();
    server.begin();
    isRunning = true;
    apStartTime = millis();
    Serial.printf("[Wi-Fi] SoftAP đã sẵn sàng tại IP: %s (Sleep disabled)\n", WiFi.softAPIP().toString().c_str());
  }

  void stop() {
    if (!isRunning) return;
    Serial.println("[Wi-Fi] Tạm dừng dịch vụ Web Captive Portal.");
    dnsServer.stop();
    isRunning = false;
  }

  void loop() {
    if (isRunning) {
      dnsServer.processNextRequest();
    }
  }

  bool active() {
    return isRunning;
  }

  int getSecondsRemaining() {
    if (!isRunning) return 0;
    long elapsed = (millis() - apStartTime) / 1000;
    int left = AP_TIMEOUT_SEC - elapsed;
    return (left > 0) ? left : 0;
  }

private:
  void setupWebRoutes() {
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
      request->send(200, "text/html; charset=utf-8", getLuxuryHTML());
    });

    server.on("/api/sprite", HTTP_POST, [this](AsyncWebServerRequest *request) {
      if (request->hasParam("id", true)) {
        int id = request->getParam("id", true)->value().toInt();
        if (onSelectSprite) onSelectSprite(id);
        request->send(200, "application/json", "{\"status\":\"ok\",\"action\":\"sprite\"}");
      } else {
        request->send(400, "text/plain", "Missing id");
      }
    });

    server.on("/api/palette", HTTP_POST, [this](AsyncWebServerRequest *request) {
      if (request->hasParam("id", true)) {
        int id = request->getParam("id", true)->value().toInt();
        if (onSelectPalette) onSelectPalette(id);
        request->send(200, "application/json", "{\"status\":\"ok\",\"action\":\"palette\"}");
      } else {
        request->send(400, "text/plain", "Missing id");
      }
    });

    server.on("/api/brightness", HTTP_POST, [this](AsyncWebServerRequest *request) {
      if (request->hasParam("value", true)) {
        int val = request->getParam("value", true)->value().toInt();
        if (onSetBrightness) onSetBrightness(val);
        request->send(200, "application/json", "{\"status\":\"ok\",\"action\":\"brightness\"}");
      } else {
        request->send(400, "text/plain", "Missing value");
      }
    });

    server.on("/api/quote", HTTP_POST, [this](AsyncWebServerRequest *request) {
      if (request->hasParam("text", true)) {
        String text = request->getParam("text", true)->value();
        if (onAddQuote) onAddQuote(text);
        request->send(200, "application/json", "{\"status\":\"ok\",\"action\":\"quote\"}");
      } else {
        request->send(400, "text/plain", "Missing text");
      }
    });

    server.on("/api/wifi", HTTP_POST, [this](AsyncWebServerRequest *request) {
      if (request->hasParam("ssid", true)) {
        String ssid = request->getParam("ssid", true)->value();
        String pass = request->hasParam("pass", true) ? request->getParam("pass", true)->value() : "";
        if (onConfigureWifi) onConfigureWifi(ssid, pass);
        request->send(200, "application/json", "{\"status\":\"ok\",\"action\":\"wifi_configured\"}");
      } else {
        request->send(400, "text/plain", "Missing ssid");
      }
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
      request->redirect("http://192.168.4.1/");
    });
  }

  String getLuxuryHTML() {
    return R"rawliteral(<!DOCTYPE html>
<html lang="vi">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Smart Keychain - 50 Animations Studio</title>
  <style>
    :root {
      --bg-deep: #020204;
      --card-bg: #0f1118;
      --border-hairline: rgba(255, 255, 255, 0.08);
      --border-active: #00f0ff;
      --cyan-accent: #00f0ff;
      --gold-accent: #f5c842;
      --text-main: #ffffff;
      --text-muted: #8a8f9d;
      --font-mono: ui-monospace, Menlo, Monaco, monospace;
    }
    * { box-sizing: border-box; margin: 0; padding: 0; }
    body {
      background: var(--bg-deep);
      color: var(--text-main);
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
      padding: 16px 14px 40px;
      max-width: 580px;
      margin: 0 auto;
      -webkit-font-smoothing: antialiased;
    }
    .header { text-align: center; padding: 14px 0 18px; }
    .status-pill {
      display: inline-flex;
      align-items: center;
      gap: 7px;
      font-size: 10px;
      font-weight: 700;
      letter-spacing: 1.5px;
      text-transform: uppercase;
      color: var(--cyan-accent);
      background: rgba(0, 240, 255, 0.06);
      border: 1px solid rgba(0, 240, 255, 0.2);
      padding: 5px 12px;
      border-radius: 999px;
      margin-bottom: 10px;
    }
    .pulse-dot { width: 6px; height: 6px; border-radius: 50%; background: #00ff88; box-shadow: 0 0 8px #00ff88; }
    h1 { font-size: 22px; font-weight: 800; }
    .subtitle { font-size: 12px; color: var(--text-muted); font-family: var(--font-mono); margin-top: 4px; }
    .hero-wrapper { display: flex; flex-direction: column; align-items: center; margin-bottom: 20px; }
    .hero-bezel {
      background: #11141f;
      border: 1px solid var(--border-hairline);
      border-radius: 20px;
      padding: 10px;
      box-shadow: 0 16px 36px rgba(0, 0, 0, 0.8), 0 0 24px rgba(0, 240, 255, 0.12);
    }
    .hero-canvas { display: block; border-radius: 10px; background: #000; width: 172px; height: 320px; }
    .hero-tag { font-size: 11px; font-weight: 700; color: var(--text-muted); font-family: var(--font-mono); margin-top: 8px; }
    
    .tabs-bar { display: flex; gap: 6px; overflow-x: auto; padding-bottom: 8px; margin-bottom: 14px; scrollbar-width: none; }
    .tab-item {
      background: var(--card-bg);
      border: 1px solid var(--border-hairline);
      border-radius: 8px;
      padding: 8px 12px;
      color: var(--text-muted);
      font-size: 12px;
      font-weight: 600;
      cursor: pointer;
      white-space: nowrap;
    }
    .tab-item.active { background: rgba(0, 240, 255, 0.1); border-color: var(--cyan-accent); color: var(--cyan-accent); }
    
    .cards-grid { display: grid; grid-template-columns: repeat(3, 1fr); gap: 9px; margin-bottom: 20px; }
    .anim-card {
      background: var(--card-bg);
      border: 1px solid var(--border-hairline);
      border-radius: 12px;
      padding: 10px 8px;
      cursor: pointer;
      display: flex;
      flex-direction: column;
      align-items: center;
      text-align: center;
      transition: all 0.15s ease;
    }
    .anim-card.selected { border-color: var(--cyan-accent); background: rgba(0, 240, 255, 0.08); box-shadow: 0 0 12px rgba(0, 240, 255, 0.22); }
    .mini-canvas { width: 64px; height: 64px; background: #000; border-radius: 8px; margin-bottom: 6px; }
    .card-title { font-size: 11px; font-weight: 700; height: 26px; overflow: hidden; }
    
    .luxury-section { background: var(--card-bg); border: 1px solid var(--border-hairline); border-radius: 14px; padding: 16px; margin-bottom: 14px; }
    .section-header { font-size: 11px; font-weight: 700; color: var(--text-muted); text-transform: uppercase; margin-bottom: 12px; font-family: var(--font-mono); }
    .palette-grid { display: grid; grid-template-columns: repeat(2, 1fr); gap: 8px; }
    .palette-btn { background: #12141c; border: 1px solid var(--border-hairline); border-radius: 8px; padding: 10px; font-size: 12px; font-weight: 600; cursor: pointer; display: flex; align-items: center; gap: 8px; color: #fff; }
    .color-swatch { width: 10px; height: 10px; border-radius: 50%; }
    
    input[type=range] { -webkit-appearance: none; width: 100%; background: #171b26; height: 6px; border-radius: 3px; outline: none; }
    input[type=range]::-webkit-slider-thumb { -webkit-appearance: none; width: 18px; height: 18px; border-radius: 50%; background: var(--cyan-accent); cursor: pointer; }
    .quote-field { width: 100%; background: #08090e; border: 1px solid var(--border-hairline); border-radius: 8px; padding: 12px; font-size: 13px; color: #fff; margin-bottom: 10px; outline: none; }
    .btn-action { width: 100%; background: var(--cyan-accent); color: #000; border: none; border-radius: 8px; padding: 12px; font-size: 12px; font-weight: 800; cursor: pointer; }
    .toast-pill { position: fixed; bottom: 24px; left: 50%; transform: translateX(-50%) translateY(100px); background: var(--cyan-accent); color: #000; font-weight: 800; font-size: 12px; padding: 10px 20px; border-radius: 999px; transition: transform 0.25s ease; z-index: 100; }
    .toast-pill.show { transform: translateX(-50%) translateY(0); }
  </style>
</head>
<body>
  <div class="header">
    <div class="status-pill"><span class="pulse-dot"></span>LOCAL 192.168.4.1 STUDIO LIVE</div>
    <h1>SMART KEYCHAIN</h1>
    <div class="subtitle">ST7789 IPS LCD &bull; 50 Animations Edition</div>
  </div>

  <div class="hero-wrapper">
    <div class="hero-bezel">
      <canvas id="heroCanvas" class="hero-canvas" width="172" height="320"></canvas>
    </div>
    <div class="hero-tag" id="heroLabel">1.47" ST7789 IPS LCD LIVE PREVIEW</div>
  </div>

  <div class="tabs-bar">
    <button class="tab-item active" onclick="switchTab('all', this)">Tất Cả (50)</button>
    <button class="tab-item" onclick="switchTab('anime', this)">Anime & Genshin</button>
    <button class="tab-item" onclick="switchTab('weapons', this)">Vũ Khí</button>
    <button class="tab-item" onclick="switchTab('love', this)">Tình Yêu</button>
    <button class="tab-item" onclick="switchTab('pets', this)">Thú Cưng</button>
    <button class="tab-item" onclick="switchTab('retro', this)">Retro HUD</button>
  </div>

  <div class="cards-grid" id="cardsGrid"></div>

  <div class="luxury-section">
    <div class="section-header">Cấu Hình Wi-Fi Nhà Để Kết Nối Cloud (app.signsafevn.online)</div>
    <input type="text" class="quote-field" id="wifiSsid" placeholder="Nhập tên Wi-Fi nhà bạn (SSID)..." style="margin-bottom:8px;">
    <input type="password" class="quote-field" id="wifiPass" placeholder="Nhập mật khẩu Wi-Fi..." style="margin-bottom:10px;">
    <button class="btn-action" style="background:var(--gold-accent);" onclick="sendWifiConfig()">LƯU VÀ KẾT NỐI INTERNET</button>
  </div>

  <div class="luxury-section">
    <div class="section-header">Bảng Màu Kim Cương Phát Sáng</div>
    <div class="palette-grid">
      <div class="palette-btn" onclick="selectPalette(0)"><div class="color-swatch" style="background:#00f0ff;"></div><span>Xanh Băng Neon</span></div>
      <div class="palette-btn" onclick="selectPalette(1)"><div class="color-swatch" style="background:#ff0055;"></div><span>Hồng Ruby Bling</span></div>
      <div class="palette-btn" onclick="selectPalette(2)"><div class="color-swatch" style="background:#ffb800;"></div><span>Vàng Hổ Phách</span></div>
      <div class="palette-btn" onclick="selectPalette(3)"><div class="color-swatch" style="background:#fcaeae;"></div><span>Hồng Pastel Anya</span></div>
      <div class="palette-btn" onclick="selectPalette(4)"><div class="color-swatch" style="background:#00ff88;"></div><span>Xanh Lục Ma Trận</span></div>
      <div class="palette-btn" onclick="selectPalette(5)"><div class="color-swatch" style="background:#9d00ff;"></div><span>Tím Astral Galaxy</span></div>
    </div>
  </div>

  <div class="luxury-section">
    <div class="section-header">Độ Sáng Màn Hình ST7789</div>
    <input type="range" id="brightSlider" min="25" max="255" value="255" oninput="changeBrightness(this.value)">
  </div>

  <div class="luxury-section">
    <div class="section-header">Gửi Lời Nhắn Yêu Thương</div>
    <input type="text" class="quote-field" id="quoteText" placeholder="Nhập lời chúc..." maxlength="80">
    <button class="btn-action" onclick="sendQuote()">GỬI NGAY LÊN MÓC KHÓA</button>
  </div>

  <div class="toast-pill" id="toastBox">Đã đổi trên móc khóa!</div>

  <script>
    const TITLES = [
      "Hu Tao & Boo", "Anya Forger", "Raiden Shogun", "Furina Fontaine", "Nahida Dendro", "Xiao Yaksha",
      "Gojo Satoru", "Nezuko Kamado", "Tanjiro Solar", "Zoro Three Sword", "Luffy Gear 5", "Naruto Sage",
      "Excalibur Holy", "Muramasa Blood", "Cyber Katana", "Plasma Buster", "Frostmourne Ice", "Mjolnir Thunder",
      "Darksaber Moon", "Energy Daggers", "Reaper Scythe", "Railgun Sniper", "Crystal Heart", "Double Hearts",
      "ECG Heartbeat", "Flying Letter", "Infinity Loop", "Crystal Rose", "Cupid Arrow", "Constellation",
      "Campfire Warm", "Magic Potion", "Red Panda Cyber", "Space Cat Astronaut", "Cyber Shiba Inu", "Cyber Bunny",
      "Hamster Explorer", "Sleeping Fox", "Cyber Dragon", "Phoenix Rebirth", "Cyber Penguin", "Axolotl Glow",
      "Arc Reactor", "Radar HUD", "Game Boy Retro", "Zelda Heart", "Synthwave Tape", "Glitch Skull",
      "Matrix Code", "Quantum Core"
    ];

    let currentSpriteId = 0;
    let currentPaletteId = 0;

    function buildGrid() {
      const grid = document.getElementById('cardsGrid');
      grid.innerHTML = '';
      TITLES.forEach((title, idx) => {
        const card = document.createElement('div');
        card.className = 'anim-card' + (idx === currentSpriteId ? ' selected' : '');
        card.id = `card-${idx}`;
        let tab = 'anime';
        if (idx >= 12 && idx < 22) tab = 'weapons';
        else if (idx >= 22 && idx < 32) tab = 'love';
        else if (idx >= 32 && idx < 42) tab = 'pets';
        else if (idx >= 42) tab = 'retro';
        card.dataset.tab = tab;
        card.onclick = () => selectCard(idx);

        card.innerHTML = `
          <canvas class="mini-canvas" id="mini-${idx}" width="64" height="64"></canvas>
          <div class="card-title">${title}</div>
        `;
        grid.appendChild(card);
      });
    }
    buildGrid();

    function switchTab(tab, btn) {
      document.querySelectorAll('.tab-item').forEach(b => b.classList.remove('active'));
      btn.classList.add('active');
      document.querySelectorAll('.anim-card').forEach(c => {
        c.style.display = (tab === 'all' || c.dataset.tab === tab) ? 'flex' : 'none';
      });
    }

    function selectCard(idx) {
      currentSpriteId = idx;
      document.querySelectorAll('.anim-card').forEach((c, i) => c.classList.toggle('selected', i === idx));
      document.getElementById('heroLabel').innerText = TITLES[idx].toUpperCase();
      fetch('/api/sprite', { method: 'POST', body: new URLSearchParams({id: idx}) });
      notify('Kích hoạt: ' + TITLES[idx]);
    }

    function selectPalette(id) {
      currentPaletteId = id;
      fetch('/api/palette', { method: 'POST', body: new URLSearchParams({id: id}) });
      notify('Đã đổi màu!');
    }

    function changeBrightness(val) {
      fetch('/api/brightness', { method: 'POST', body: new URLSearchParams({value: val}) });
    }

    function sendQuote() {
      const val = document.getElementById('quoteText').value.trim();
      if (!val) return;
      fetch('/api/quote', { method: 'POST', body: new URLSearchParams({text: val}) });
      notify('Đã gửi lời nhắn!');
      document.getElementById('quoteText').value = '';
    }

    function sendWifiConfig() {
      const ssid = document.getElementById('wifiSsid').value.trim();
      const pass = document.getElementById('wifiPass').value.trim();
      if (!ssid) { alert('Vui lòng nhập tên Wi-Fi!'); return; }
      fetch('/api/wifi', { method: 'POST', body: new URLSearchParams({ssid: ssid, pass: pass}) });
      notify('Đã lưu Wi-Fi! Đang kết nối Internet...');
    }

    function notify(msg) {
      const t = document.getElementById('toastBox');
      t.innerText = msg;
      t.classList.add('show');
      setTimeout(() => t.classList.remove('show'), 2000);
    }

    let time = 0;
    const heroCtx = document.getElementById('heroCanvas').getContext('2d');

    function drawThemeGraphic(ctx, id, cx, cy, scale, t) {
      const breath = Math.sin(t * 3.5) * 0.1 + 1.0;
      ctx.save();
      ctx.translate(cx, cy + Math.sin(t * 2.2) * 3);
      ctx.scale(scale * breath, scale * breath);
      
      if (id === 0) { // Hu Tao
        ctx.fillStyle = '#4a1506'; ctx.fillRect(-16, -10, 6, 20); ctx.fillRect(10, -10, 6, 20);
        ctx.fillStyle = '#ffdfba'; ctx.fillRect(-10, -8, 20, 16);
        ctx.fillStyle = '#181b22'; ctx.fillRect(-14, -18, 28, 10);
        ctx.fillStyle = '#ff2a2a'; ctx.fillRect(-6, -4, 4, 4); ctx.fillRect(2, -4, 4, 4);
      } else if (id === 1) { // Anya
        ctx.fillStyle = '#fcaeae'; ctx.fillRect(-12, -16, 24, 22);
        ctx.fillStyle = '#ffeedb'; ctx.fillRect(-8, -8, 16, 14);
        ctx.fillStyle = '#00c950'; ctx.fillRect(-6, -4, 4, 5); ctx.fillRect(2, -4, 4, 5);
      } else if (id < 12) {
        ctx.fillStyle = '#6b21a8'; ctx.fillRect(-10, -14, 20, 18);
        ctx.fillStyle = '#ffeedb'; ctx.fillRect(-8, -6, 16, 12);
      } else if (id < 22) { // Weapons
        ctx.rotate(0.35);
        ctx.fillStyle = '#00f0ff'; ctx.fillRect(-2, -24, 4, 36);
        ctx.fillStyle = '#f5c842'; ctx.fillRect(-6, 12, 12, 4);
      } else if (id < 32) { // Love
        ctx.fillStyle = '#ff0055';
        ctx.beginPath(); ctx.arc(-5, -4, 7, 0, Math.PI * 2); ctx.arc(5, -4, 7, 0, Math.PI * 2); ctx.fill();
        ctx.beginPath(); ctx.moveTo(-11, -1); ctx.lineTo(11, -1); ctx.lineTo(0, 11); ctx.closePath(); ctx.fill();
      } else if (id < 42) { // Pets
        ctx.fillStyle = '#ea580c'; ctx.beginPath(); ctx.arc(0, 0, 12, 0, Math.PI * 2); ctx.fill();
        ctx.fillStyle = '#fff'; ctx.fillRect(-6, -2, 4, 4); ctx.fillRect(2, -2, 4, 4);
      } else { // HUD
        ctx.strokeStyle = '#00f0ff'; ctx.lineWidth = 2; ctx.strokeRect(-12, -12, 24, 24);
        ctx.beginPath(); ctx.arc(0, 0, 7, 0, Math.PI * 2); ctx.stroke();
      }
      ctx.restore();
    }

    function animate() {
      time += 0.04;
      heroCtx.fillStyle = '#000000';
      heroCtx.fillRect(0, 0, 172, 320);
      drawThemeGraphic(heroCtx, currentSpriteId, 172 / 2, 140, 1.4, time);

      TITLES.forEach((_, idx) => {
        const c = document.getElementById(`mini-${idx}`);
        if (c && c.parentElement.style.display !== 'none') {
          const mCtx = c.getContext('2d');
          mCtx.fillStyle = '#000'; mCtx.fillRect(0, 0, 64, 64);
          drawThemeGraphic(mCtx, idx, 32, 32, 0.7, time);
        }
      });
      requestAnimationFrame(animate);
    }
    animate();
  </script>
</body>
</html>)rawliteral";
  }
};
