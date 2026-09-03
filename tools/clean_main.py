import os
import json
from typing import List
from fastapi import FastAPI, WebSocket, WebSocketDisconnect, Form
from fastapi.responses import HTMLResponse, JSONResponse
import uvicorn

app = FastAPI(title="Smart Keychain - Ultimate 50 Animations Studio")

CATALOG_PATH = os.path.join(os.path.dirname(__file__), "catalog_animations.json")
if not os.path.exists(CATALOG_PATH):
    CATALOG_PATH = os.path.join(os.path.dirname(__file__), "..", "..", "data", "catalog_animations.json")

try:
    with open(CATALOG_PATH, "r", encoding="utf-8") as f:
        ANIMATIONS = json.load(f)
except Exception:
    ANIMATIONS = []

state = {
    "sprite_id": 0,
    "palette_id": 0,
    "brightness": 255,
    "quote": "Dù ở thế giới nào, anh vẫn luôn tìm thấy em."
}

class ConnectionManager:
    def __init__(self):
        self.active_connections: List[WebSocket] = []

    async def connect(self, websocket: WebSocket):
        await websocket.accept()
        self.active_connections.append(websocket)
        await websocket.send_text(json.dumps({"type": "SYNC", "data": state}))

    def disconnect(self, websocket: WebSocket):
        if websocket in self.active_connections:
            self.active_connections.remove(websocket)

    async def broadcast(self, message: dict):
        msg_str = json.dumps(message)
        for connection in self.active_connections:
            try:
                await connection.send_text(msg_str)
            except Exception:
                pass

manager = ConnectionManager()

@app.websocket("/ws/keychain")
async def websocket_endpoint(websocket: WebSocket):
    await manager.connect(websocket)
    try:
        while True:
            data = await websocket.receive_text()
            try:
                payload = json.loads(data)
                action = payload.get("action")
                if action == "SET_SPRITE":
                    state["sprite_id"] = payload.get("value", 0)
                    if 0 <= state["sprite_id"] < len(ANIMATIONS):
                        state["quote"] = ANIMATIONS[state["sprite_id"]]["quote"]
                elif action == "SET_PALETTE":
                    state["palette_id"] = payload.get("value", 0)
                elif action == "SET_BRIGHTNESS":
                    state["brightness"] = payload.get("value", 255)
                elif action == "SET_QUOTE":
                    state["quote"] = payload.get("value", "")
                elif action == "SET_QR":
                    state["qr_mode"] = payload.get("value", True)
                await manager.broadcast({"type": "UPDATE", "data": state})
            except Exception:
                pass
    except WebSocketDisconnect:
        manager.disconnect(websocket)

@app.get("/api/catalog")
async def get_catalog():
    return JSONResponse(ANIMATIONS)

@app.get("/api/state")
async def get_state():
    return JSONResponse(state)

@app.post("/api/sprite")
async def set_sprite(id: int = Form(...)):
    state["sprite_id"] = id
    if 0 <= id < len(ANIMATIONS):
        state["quote"] = ANIMATIONS[id]["quote"]
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "sprite_id": id}

@app.post("/api/palette")
async def set_palette(id: int = Form(...)):
    state["palette_id"] = id
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "palette_id": id}

@app.post("/api/brightness")
async def set_brightness(value: int = Form(...)):
    state["brightness"] = value
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "brightness": value}

@app.post("/api/quote")
async def set_quote(text: str = Form(...)):
    state["quote"] = text
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "quote": text}

@app.post("/api/qr")
async def trigger_qr():
    state["qr_mode"] = True
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "qr_mode": True}

@app.get("/", response_class=HTMLResponse)
async def serve_index():
    catalog_json = json.dumps(ANIMATIONS, ensure_ascii=False)
    return f"""<!DOCTYPE html>
<html lang="vi">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Smart Keychain — 50 Animations Studio (Modern Split Edition)</title>
  <style>
    :root {{
      --bg: #030407;
      --bg-surface: #080a11;
      --bg-card: #0d101a;
      --bg-card-hover: #141826;
      --border-subtle: rgba(255, 255, 255, 0.08);
      --border-active: #00f0ff;
      --cyan: #00f0ff;
      --cyan-glow: rgba(0, 240, 255, 0.35);
      --pink: #ff0055;
      --gold: #ffb800;
      --green: #00ff88;
      --purple: #9d00ff;
      --text-1: #ffffff;
      --text-2: #8e95a5;
      --text-muted: #555d71;
      --font-mono: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, monospace;
    }}
    * {{ box-sizing: border-box; margin: 0; padding: 0; }}
    body {{
      background: var(--bg);
      color: var(--text-1);
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Helvetica, Arial, sans-serif;
      min-height: 100vh;
      -webkit-font-smoothing: antialiased;
      overflow-x: hidden;
    }}

    /* TOP NAVBAR */
    .top-navbar {{
      display: flex;
      align-items: center;
      justify-content: space-between;
      padding: 14px 28px;
      background: rgba(8, 10, 17, 0.85);
      backdrop-filter: blur(16px);
      border-bottom: 1px solid var(--border-subtle);
      position: sticky;
      top: 0;
      z-index: 50;
    }}
    .brand-group {{
      display: flex;
      align-items: center;
      gap: 12px;
    }}
    .brand-logo {{
      width: 28px;
      height: 28px;
      border-radius: 7px;
      background: linear-gradient(135deg, #00f0ff, #0088ff);
      display: flex;
      align-items: center;
      justify-content: center;
      font-weight: 900;
      color: #000;
      font-size: 14px;
      box-shadow: 0 0 12px var(--cyan-glow);
    }}
    .brand-title {{
      font-size: 16px;
      font-weight: 800;
      letter-spacing: 0.5px;
    }}
    .status-telemetry {{
      display: flex;
      align-items: center;
      gap: 8px;
      background: rgba(0, 255, 136, 0.08);
      border: 1px solid rgba(0, 255, 136, 0.25);
      padding: 6px 14px;
      border-radius: 999px;
      font-size: 11px;
      font-weight: 700;
      font-family: var(--font-mono);
      color: var(--green);
    }}
    .pulse-dot {{
      width: 7px;
      height: 7px;
      border-radius: 50%;
      background: var(--green);
      box-shadow: 0 0 8px var(--green);
      animation: pulse 1.6s infinite ease-in-out;
    }}
    @keyframes pulse {{
      0%, 100% {{ transform: scale(1); opacity: 1; }}
      50% {{ transform: scale(1.4); opacity: 0.6; }}
    }}

    /* MAIN STUDIO LAYOUT (2 COLUMNS) */
    .studio-layout {{
      max-width: 1380px;
      margin: 0 auto;
      padding: 24px 28px 60px;
      display: grid;
      grid-template-columns: 360px 1fr;
      gap: 28px;
      align-items: start;
    }}

    /* LEFT COLUMN: STICKY SIMULATOR & HARDWARE CONTROLS */
    .left-pod {{
      position: sticky;
      top: 80px;
      background: var(--bg-surface);
      border: 1px solid var(--border-subtle);
      border-radius: 20px;
      padding: 20px;
      display: flex;
      flex-direction: column;
      gap: 18px;
      box-shadow: 0 12px 32px rgba(0,0,0,0.4);
    }}
    .bezel-container {{
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 10px;
    }}
    .device-bezel {{
      width: 196px;
      height: 348px;
      background: #000;
      border: 3px solid #1c2130;
      border-radius: 28px;
      padding: 11px;
      box-shadow: 0 16px 40px rgba(0,0,0,0.8), 0 0 0 1px rgba(255,255,255,0.05);
      cursor: pointer;
      position: relative;
      transition: transform 0.15s ease, border-color 0.2s ease;
    }}
    .device-bezel:hover {{
      border-color: var(--cyan);
      box-shadow: 0 16px 40px rgba(0,0,0,0.8), 0 0 20px rgba(0,240,255,0.25);
    }}
    .device-bezel:active {{ transform: scale(0.98); }}
    .screen-canvas {{
      width: 172px;
      height: 320px;
      border-radius: 18px;
      background: #000;
      display: block;
    }}
    .bezel-hint {{
      font-size: 10px;
      font-family: var(--font-mono);
      color: var(--text-muted);
      letter-spacing: 0.5px;
    }}

    .pod-telemetry {{
      display: flex;
      justify-content: space-between;
      align-items: center;
      padding: 8px 12px;
      background: rgba(255,255,255,0.03);
      border-radius: 10px;
      font-family: var(--font-mono);
      font-size: 11px;
    }}
    .pod-title {{ color: var(--cyan); font-weight: 800; }}
    .pod-fps {{ color: var(--green); font-weight: 700; }}

    /* CONTROL GROUPS */
    .control-group {{
      display: flex;
      flex-direction: column;
      gap: 8px;
    }}
    .control-label {{
      font-size: 11px;
      font-weight: 700;
      letter-spacing: 0.8px;
      text-transform: uppercase;
      color: var(--text-2);
      font-family: var(--font-mono);
    }}
    .gem-palette-grid {{
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 6px;
    }}
    .gem-btn {{
      background: #0e121d;
      border: 1px solid var(--border-subtle);
      border-radius: 8px;
      padding: 8px 6px;
      display: flex;
      align-items: center;
      gap: 6px;
      font-size: 11px;
      font-weight: 600;
      color: #fff;
      cursor: pointer;
      transition: all 0.15s ease;
    }}
    .gem-btn:hover {{ border-color: rgba(255,255,255,0.3); }}
    .gem-btn.active {{
      border-color: var(--cyan);
      background: rgba(0, 240, 255, 0.12);
      box-shadow: 0 0 10px rgba(0, 240, 255, 0.2);
    }}
    .gem-circle {{
      width: 8px;
      height: 8px;
      border-radius: 50%;
      flex-shrink: 0;
    }}

     input[type=range] {{
      -webkit-appearance: none;
      width: 100%;
      background: #171b26;
      height: 6px;
      border-radius: 3px;
      outline: none;
    }}
    input[type=range]::-webkit-slider-thumb {{
      -webkit-appearance: none;
      width: 16px;
      height: 16px;
      border-radius: 50%;
      background: var(--cyan);
      cursor: pointer;
      box-shadow: 0 0 8px var(--cyan);
    }}
    input[type=range]::-webkit-slider-thumb:hover {{
      background: #33f3ff;
      box-shadow: 0 0 10px var(--cyan);
    }}

    .qr-action-btn {{
      width: 100%;
      padding: 10px 14px;
      border-radius: 10px;
      background: rgba(0, 240, 255, 0.08);
      border: 1px solid rgba(0, 240, 255, 0.3);
      color: var(--cyan);
      font-weight: 700;
      font-size: 11.5px;
      letter-spacing: 0.5px;
      cursor: pointer;
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 8px;
      transition: all 0.15s ease;
      margin-top: 6px;
    }}
    .qr-action-btn:hover {{
      background: rgba(0, 240, 255, 0.18);
      border-color: var(--cyan);
      box-shadow: 0 0 14px var(--cyan-glow);
    }}
    .qr-action-btn:active {{ transform: scale(0.98); }}

    /* RIGHT COLUMN: QUICK CHIPS & 50 THEMES GALLERY */
    .right-pod {{
      display: flex;
      flex-direction: column;
      gap: 22px;
    }}

    /* QUICK MESSAGE TRANSMITTER */
    .msg-card {{
      background: var(--bg-surface);
      border: 1px solid var(--border-subtle);
      border-radius: 18px;
      padding: 18px 22px;
      display: flex;
      flex-direction: column;
      gap: 14px;
      box-shadow: 0 8px 24px rgba(0,0,0,0.3);
    }}
    .msg-row {{
      display: flex;
      gap: 10px;
    }}
    .msg-input {{
      flex: 1;
      background: #040508;
      border: 1px solid var(--border-subtle);
      border-radius: 10px;
      padding: 12px 16px;
      font-size: 13px;
      color: #fff;
      outline: none;
      transition: border-color 0.15s ease;
    }}
    .msg-input:focus {{ border-color: var(--cyan); }}
    .send-action-btn {{
      background: var(--cyan);
      color: #000;
      border: none;
      border-radius: 10px;
      padding: 0 20px;
      font-size: 12px;
      font-weight: 800;
      letter-spacing: 0.5px;
      cursor: pointer;
      transition: transform 0.1s ease, opacity 0.1s ease;
      white-space: nowrap;
    }}
    .send-action-btn:hover {{ opacity: 0.92; }}
    .send-action-btn:active {{ transform: scale(0.97); }}

    /* QUICK LOVE CHIPS */
    .chips-label {{
      font-size: 11px;
      color: var(--text-2);
      font-weight: 700;
      font-family: var(--font-mono);
      text-transform: uppercase;
    }}
    .chips-row {{
      display: flex;
      flex-wrap: wrap;
      gap: 8px;
    }}
    .love-chip {{
      background: #111420;
      border: 1px solid rgba(255, 255, 255, 0.08);
      border-radius: 999px;
      padding: 6px 14px;
      font-size: 11.5px;
      font-weight: 600;
      color: #e2e8f0;
      cursor: pointer;
      transition: all 0.15s ease;
      user-select: none;
    }}
    .love-chip:hover {{
      border-color: var(--cyan);
      background: rgba(0, 240, 255, 0.08);
      color: var(--cyan);
      transform: translateY(-1px);
    }}
    .love-chip:active {{ transform: scale(0.96); }}

    /* TABS & SEARCH */
    .filter-bar {{
      display: flex;
      align-items: center;
      justify-content: space-between;
      gap: 14px;
      flex-wrap: wrap;
    }}
    .tabs-group {{
      display: flex;
      gap: 8px;
      overflow-x: auto;
      padding-bottom: 4px;
    }}
    .tab-btn {{
      background: #0a0d15;
      border: 1px solid var(--border-subtle);
      border-radius: 10px;
      padding: 8px 14px;
      font-size: 12px;
      font-weight: 700;
      color: var(--text-2);
      cursor: pointer;
      white-space: nowrap;
      transition: all 0.15s ease;
    }}
    .tab-btn:hover {{ color: #fff; border-color: rgba(255,255,255,0.2); }}
    .tab-btn.active {{
      background: #151928;
      color: var(--cyan);
      border-color: var(--cyan);
    }}
    .tab-counter {{
      font-size: 10px;
      padding: 2px 6px;
      border-radius: 999px;
      background: rgba(255,255,255,0.1);
      margin-left: 4px;
    }}

    .search-box {{
      background: #040508;
      border: 1px solid var(--border-subtle);
      border-radius: 10px;
      padding: 8px 14px;
      font-size: 12px;
      color: #fff;
      outline: none;
      width: 200px;
      transition: border-color 0.15s ease;
    }}
    .search-box:focus {{ border-color: var(--cyan); }}

    /* 50 CARDS GRID */
    .cards-grid {{
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(180px, 1fr));
      gap: 14px;
    }}
    .card-item {{
      background: var(--bg-card);
      border: 1px solid var(--border-subtle);
      border-radius: 14px;
      padding: 14px 10px;
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 10px;
      cursor: pointer;
      position: relative;
      transition: all 0.2s cubic-bezier(0.16, 1, 0.3, 1);
      overflow: hidden;
    }}
    .card-item:hover {{
      background: var(--bg-card-hover);
      border-color: rgba(255, 255, 255, 0.22);
      transform: translateY(-2px);
    }}
    .card-item.active-card {{
      border-color: var(--cyan);
      background: rgba(0, 240, 255, 0.05);
      box-shadow: 0 0 16px rgba(0, 240, 255, 0.25);
    }}
    .active-badge {{
      position: absolute;
      top: 8px;
      right: 8px;
      background: var(--cyan);
      color: #000;
      font-size: 8px;
      font-weight: 900;
      padding: 2px 6px;
      border-radius: 4px;
      letter-spacing: 0.5px;
      display: none;
    }}
    .card-item.active-card .active-badge {{ display: block; }}
    .preview-canvas {{
      width: 72px;
      height: 72px;
      border-radius: 10px;
      background: #000;
    }}
    .card-name {{
      font-size: 11.5px;
      font-weight: 700;
      text-align: center;
      color: #fff;
      line-height: 1.3;
      white-space: nowrap;
      overflow: hidden;
      text-overflow: ellipsis;
      max-width: 100%;
    }}
    .card-category {{
      font-size: 9px;
      font-family: var(--font-mono);
      color: var(--cyan);
      text-transform: uppercase;
      letter-spacing: 0.5px;
    }}

    /* TOAST */
    .toast-pill {{
      position: fixed;
      bottom: 24px;
      right: 28px;
      transform: translateY(100px);
      background: var(--cyan);
      color: #000;
      font-weight: 800;
      font-size: 12px;
      padding: 10px 22px;
      border-radius: 999px;
      box-shadow: 0 8px 24px var(--cyan-glow);
      transition: transform 0.25s cubic-bezier(0.16, 1, 0.3, 1);
      z-index: 100;
      letter-spacing: 0.5px;
    }}
    .toast-pill.visible {{ transform: translateY(0); }}

    /* RESPONSIVE MOBILE */
    @media (max-width: 960px) {{
      .studio-layout {{
        grid-template-columns: 1fr;
        padding: 16px;
      }}
      .left-pod {{
        position: relative;
        top: 0;
        align-items: center;
      }}
      .cards-grid {{
        grid-template-columns: repeat(auto-fill, minmax(140px, 1fr));
      }}
      .search-box {{ width: 100%; }}
      .msg-row {{ flex-direction: column; }}
      .send-action-btn {{ padding: 12px; }}
    }}
  </style>
</head>
<body>
  <!-- NAVBAR -->
  <div class="top-navbar">
    <div class="brand-group">
      <div class="brand-logo">K</div>
      <div class="brand-title">SMART KEYCHAIN STUDIO</div>
    </div>
    <div class="status-telemetry">
      <span class="pulse-dot"></span>
      <span id="telemetryText">CLOUD SYNC: 0ms &bull; 50 THEMES READY</span>
    </div>
  </div>

  <!-- STUDIO MAIN CONTAINER -->
  <div class="studio-layout">
    
    <!-- LEFT COLUMN: STICKY SIMULATOR -->
    <div class="left-pod">
      <div class="bezel-container">
        <div class="device-bezel" onclick="triggerNextThemeClick()" title="Nhấp để đổi sang Theme kế tiếp (Giống nút bấm thật)">
          <canvas id="heroCanvas" class="screen-canvas" width="172" height="320"></canvas>
        </div>
        <div class="bezel-hint">CHẠM VÀO MÀN HÌNH ĐỂ ĐỔI THEME</div>
      </div>

      <div class="pod-telemetry">
        <span class="pod-title" id="podTitle">HU TAO & BOO</span>
        <span class="pod-fps">60.0 FPS</span>
      </div>

      <!-- PALETTES -->
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
      </div>

      <!-- BRIGHTNESS -->
      <div class="control-group">
        <div class="control-label" style="display:flex; justify-content:space-between;">
          <span>Độ Sáng Màn Hình ST7789</span>
          <span id="brightVal" style="color:var(--cyan)">100%</span>
        </div>
        <input type="range" id="brightRange" min="25" max="255" value="255" oninput="sendBrightness(this.value)">
      </div>

      <!-- REMOTE QR CODE ACTION -->
      <div class="control-group">
        <button class="qr-action-btn" onclick="triggerRemoteQR()">
          <span style="font-size:14px;">📱</span> MỞ MÃ QR CẤU HÌNH (TRIPLE-CLICK)
        </button>
      </div>
    </div>

    <!-- RIGHT COLUMN: QUICK CHIPS & THEMES GALLERY -->
    <div class="right-pod">
      
      <!-- QUICK LOVE MESSAGE TRANSMITTER -->
      <div class="msg-card">
        <div class="control-label">Gửi Lời Nhắn Từ Xa Lên Móc Khóa</div>
        <div class="msg-row">
          <input type="text" class="msg-input" id="quoteField" placeholder="Nhập lời chúc hoặc kỷ niệm dành riêng cho người ấy..." maxlength="80">
          <button class="send-action-btn" onclick="sendCustomQuote()">GỬI LÊN MÓC KHÓA</button>
        </div>

        <div class="chips-label">Gợi ý 1-Chạm Gửi Nhanh</div>
        <div class="chips-row">
          <div class="love-chip" onclick="sendQuickChip('Anh yêu em ❤️')">Anh yêu em ❤️</div>
          <div class="love-chip" onclick="sendQuickChip('I love you 3000 ✨')">I love you 3000 ✨</div>
          <div class="love-chip" onclick="sendQuickChip('Nhớ em nhiều 🌙')">Nhớ em nhiều 🌙</div>
          <div class="love-chip" onclick="sendQuickChip('Chúc ngày mới rạng rỡ ☀️')">Chúc ngày mới rạng rỡ ☀️</div>
          <div class="love-chip" onclick="sendQuickChip('Đang bận nhưng vẫn nhớ em 💬')">Đang bận nhưng vẫn nhớ em 💬</div>
          <div class="love-chip" onclick="sendQuickChip('Phát đi phát lại bản tình ca 🎵')">Phát đi phát lại bản tình ca 🎵</div>
          <div class="love-chip" onclick="sendQuickChip('Dù ở thế giới nào, anh vẫn tìm thấy em 🌌')">Dù ở thế giới nào, anh vẫn tìm thấy em 🌌</div>
        </div>
      </div>

      <!-- FILTER & SEARCH BAR -->
      <div class="filter-bar">
        <div class="tabs-group">
          <button class="tab-btn active" onclick="switchCategory('all', this)">Tất Cả <span class="tab-counter">50</span></button>
          <button class="tab-btn" onclick="switchCategory('anime', this)">Anime & Genshin <span class="tab-counter">12</span></button>
          <button class="tab-btn" onclick="switchCategory('weapons', this)">Vũ Khí & Cyber <span class="tab-counter">10</span></button>
          <button class="tab-btn" onclick="switchCategory('love', this)">Tình Yêu & Bling <span class="tab-counter">10</span></button>
          <button class="tab-btn" onclick="switchCategory('pets', this)">Thú Cưng <span class="tab-counter">10</span></button>
          <button class="tab-btn" onclick="switchCategory('retro', this)">Retro Gaming <span class="tab-counter">8</span></button>
        </div>
        <input type="text" class="search-box" placeholder="🔍 Tìm kiếm Theme..." oninput="filterThemes(this.value)">
      </div>

      <!-- 50 CARDS GRID -->
      <div class="cards-grid" id="cardsContainer"></div>

    </div>
  </div>

  <div class="toast-pill" id="toastPill">Đã kích hoạt hoạt ảnh!</div>

  <script>
    const CATALOG = {catalog_json};
    let currentSpriteId = 0;
    let currentPaletteId = 0;
    let currentQuote = "Dù ở thế giới nào, anh vẫn luôn tìm thấy em.";
    let ws;
    let time = 0;
    const heroCanvas = document.getElementById('heroCanvas');
    const heroCtx = heroCanvas.getContext('2d');

    // WEBSOCKET INITIALIZER
    function initWebSocket() {{
      const proto = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
      ws = new WebSocket(`${{proto}}//${{window.location.host}}/ws/keychain`);
      ws.onmessage = (event) => {{
        try {{
          const res = JSON.parse(event.data);
          if (res.data) {{
            if (res.data.sprite_id !== undefined) selectCard(res.data.sprite_id, false);
            if (res.data.palette_id !== undefined) currentPaletteId = res.data.palette_id;
            if (res.data.quote) currentQuote = res.data.quote;
            if (res.data.brightness) {{
              document.getElementById('brightRange').value = res.data.brightness;
              document.getElementById('brightVal').innerText = Math.round((res.data.brightness / 255) * 100) + '%';
            }}
          }}
        }} catch(e) {{}}
      }};
      ws.onclose = () => setTimeout(initWebSocket, 2000);
    }}
    initWebSocket();

    // POPULATE 50 CARDS
    function populateGrid() {{
      const container = document.getElementById('cardsContainer');
      container.innerHTML = '';
      CATALOG.forEach(item => {{
        const card = document.createElement('div');
        card.className = 'card-item' + (item.id === currentSpriteId ? ' active-card' : '');
        card.id = `card-${{item.id}}`;
        card.dataset.tab = item.tab;
        card.dataset.name = item.name.toLowerCase();
        card.onclick = () => selectCard(item.id, true);

        card.innerHTML = `
          <div class="active-badge">ĐANG CHIẾU</div>
          <canvas class="preview-canvas" id="mini-${{item.id}}" width="72" height="72"></canvas>
          <div class="card-name">${{item.name}}</div>
          <div class="card-category">${{item.palette}}</div>
        `;
        container.appendChild(card);
      }});
    }}
    populateGrid();

    // CATEGORY FILTER
    function switchCategory(cat, btn) {{
      document.querySelectorAll('.tab-btn').forEach(b => b.classList.remove('active'));
      btn.classList.add('active');
      document.querySelectorAll('.card-item').forEach(c => {{
        c.style.display = (cat === 'all' || c.dataset.tab === cat) ? 'flex' : 'none';
      }});
    }}

    // SEARCH FILTER
    function filterThemes(q) {{
      const query = q.trim().toLowerCase();
      document.querySelectorAll('.card-item').forEach(c => {{
        const match = !query || c.dataset.name.includes(query);
        c.style.display = match ? 'flex' : 'none';
      }});
    }}

    // SELECT CARD
    function selectCard(id, pushNetwork = true) {{
      currentSpriteId = id;
      document.querySelectorAll('.card-item').forEach((c, idx) => {{
        c.classList.toggle('active-card', idx === id);
      }});
      if (CATALOG[id]) {{
        currentQuote = CATALOG[id].quote;
        document.getElementById('podTitle').innerText = CATALOG[id].name.toUpperCase();
      }}
      if (pushNetwork) {{
        if (ws && ws.readyState === WebSocket.OPEN) {{
          ws.send(JSON.stringify({{action: 'SET_SPRITE', value: id}}));
        }}
        fetch('/api/sprite', {{ method: 'POST', body: new URLSearchParams({{id: id}}) }});
        showToast(`Kích hoạt: ${{CATALOG[id].name}}`);
      }}
    }}

    // INTERACTIVE CLICK ON SIMULATOR
    function triggerNextThemeClick() {{
      const nextId = (currentSpriteId + 1) % CATALOG.length;
      selectCard(nextId, true);
    }}

    // SET PALETTE
    function setPaletteChoice(id) {{
      currentPaletteId = id;
      document.querySelectorAll('.gem-btn').forEach((p, idx) => {{
        p.classList.toggle('active', idx === id);
      }});
      if (ws && ws.readyState === WebSocket.OPEN) {{
        ws.send(JSON.stringify({{action: 'SET_PALETTE', value: id}}));
      }}
      fetch('/api/palette', {{ method: 'POST', body: new URLSearchParams({{id: id}}) }});
      showToast('Đã đổi màu kim cương!');
    }}

    // BRIGHTNESS
    function sendBrightness(val) {{
      document.getElementById('brightVal').innerText = Math.round((val / 255) * 100) + '%';
      if (ws && ws.readyState === WebSocket.OPEN) {{
        ws.send(JSON.stringify({{action: 'SET_BRIGHTNESS', value: parseInt(val)}}));
      }}
      fetch('/api/brightness', {{ method: 'POST', body: new URLSearchParams({{value: val}})}});
    }}

    // REMOTE QR ACTION
    function triggerRemoteQR() {{
      if (ws && ws.readyState === WebSocket.OPEN) {{
        ws.send(JSON.stringify({{action: 'SET_QR', value: true}}));
      }}
      fetch('/api/qr', {{ method: 'POST' }});
      showToast('Đang mở màn hình QR trên móc khóa...');
    }}

    // CUSTOM QUOTE
    function sendCustomQuote() {{
      const input = document.getElementById('quoteField');
      const val = input.value.trim();
      if (!val) return;
      currentQuote = val;
      if (ws && ws.readyState === WebSocket.OPEN) {{
        ws.send(JSON.stringify({{action: 'SET_QUOTE', value: val}}));
      }}
      fetch('/api/quote', {{ method: 'POST', body: new URLSearchParams({{text: val}})}});
      showToast('Lời nhắn đã gửi tới móc khóa!');
      input.value = '';
    }}

    // QUICK LOVE CHIP
    function sendQuickChip(text) {{
      currentQuote = text;
      if (ws && ws.readyState === WebSocket.OPEN) {{
        ws.send(JSON.stringify({{action: 'SET_QUOTE', value: text}}));
      }}
      fetch('/api/quote', {{ method: 'POST', body: new URLSearchParams({{text: text}})}});
      showToast(`Đã gửi: "${{text}}"`);
    }}

    // TOAST
    function showToast(msg) {{
      const toast = document.getElementById('toastPill');
      toast.innerText = msg;
      toast.classList.add('visible');
      setTimeout(() => toast.classList.remove('visible'), 2200);
    }}

    // PALETTE COLOR RESOLVER
    function resolvePaletteHex(pid) {{
      switch(pid % 6) {{
        case 0: return '#00f0ff';
        case 1: return '#ff0055';
        case 2: return '#ffb800';
        case 3: return '#fcaeae';
        case 4: return '#00ff88';
        case 5: return '#9d00ff';
        default: return '#00f0ff';
      }}
    }}

    // 50 ANIMATIONS VECTOR/CANVAS ENGINE
    function renderSpecificAnimation(ctx, id, cx, cy, scale, t) {{
      ctx.save();
      ctx.translate(cx, cy);
      ctx.scale(scale, scale);

      const breath = Math.sin(t * 3.5) * 2.5;

      switch (id) {{
        // 1. ANIME & GENSHIN (0..11)
        case 0: // Hu Tao & Boo Tao
          ctx.fillStyle = '#410000';
          ctx.fillRect(-18, -10 + breath, 7, 24); ctx.fillRect(11, -10 + breath, 7, 24);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-11, -8, 22, 18);
          ctx.fillStyle = '#18121f'; ctx.fillRect(-14, -20, 28, 12);
          ctx.fillStyle = '#ff0033'; ctx.fillRect(-7, -3, 5, 5); ctx.fillRect(2, -3, 5, 5);
          const bx = 18 + Math.cos(t * 3) * 5;
          const by = -14 + Math.sin(t * 3) * 5;
          ctx.fillStyle = 'rgba(255,255,255,0.9)';
          ctx.beginPath(); ctx.arc(bx, by, 7, 0, Math.PI * 2); ctx.fill();
          break;

        case 1: // Anya
          ctx.fillStyle = '#fdb8c0'; ctx.fillRect(-15, -18, 30, 28);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-11, -8, 22, 16);
          ctx.fillStyle = '#000000';
          ctx.beginPath(); ctx.moveTo(-15, -16); ctx.lineTo(-9, -28); ctx.lineTo(-3, -16); ctx.fill();
          ctx.beginPath(); ctx.moveTo(3, -16); ctx.lineTo(9, -28); ctx.lineTo(15, -16); ctx.fill();
          ctx.fillStyle = '#2d5a27'; ctx.fillRect(-8, -4, 5, 6); ctx.fillRect(3, -4, 5, 6);
          break;

        case 2: // Raiden Shogun
          ctx.fillStyle = '#691582'; ctx.fillRect(-13, -16, 26, 24);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-9, -6, 18, 16);
          ctx.strokeStyle = '#a970ff'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.arc(0, 0, 22 + breath, 0, Math.PI * 2); ctx.stroke();
          break;

        case 3: // Furina
          ctx.fillStyle = '#041f4a'; ctx.fillRect(-12, -22, 24, 14);
          ctx.fillStyle = '#ffffff'; ctx.fillRect(-15, -8, 30, 4);
          ctx.fillStyle = '#defbff'; ctx.fillRect(-10, -4, 20, 18);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-8, -2, 16, 12);
          break;

        case 4: // Nahida
          ctx.fillStyle = '#ffffff'; ctx.fillRect(-12, -16, 24, 20);
          ctx.fillStyle = '#066020'; ctx.fillRect(-15, -12, 5, 10);
          ctx.fillStyle = '#00ff88'; ctx.fillRect(-6, -2, 4, 4); ctx.fillRect(2, -2, 4, 4);
          break;

        case 5: // Xiao
          ctx.fillStyle = '#03453d'; ctx.fillRect(-12, -16, 24, 20);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-9, -6, 18, 14);
          ctx.strokeStyle = '#00f0ff'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.moveTo(-18, 18); ctx.lineTo(-10, -22); ctx.stroke();
          break;

        case 6: // Gojo Satoru
          ctx.fillStyle = '#ffffff'; ctx.fillRect(-12, -20, 24, 18);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-9, -6, 18, 14);
          ctx.fillStyle = '#101018'; ctx.fillRect(-10, -5, 20, 6);
          ctx.fillStyle = '#0088ff'; ctx.beginPath(); ctx.arc(-18, -8, 5, 0, Math.PI*2); ctx.fill();
          ctx.fillStyle = '#ff0055'; ctx.beginPath(); ctx.arc(18, -8, 5, 0, Math.PI*2); ctx.fill();
          break;

        case 7: // Nezuko
          ctx.fillStyle = '#111111'; ctx.fillRect(-12, -18, 24, 24);
          ctx.fillStyle = '#fa6070'; ctx.fillRect(-12, 0, 7, 12); ctx.fillRect(5, 0, 7, 12);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-9, -6, 18, 14);
          ctx.fillStyle = '#00ff88'; ctx.fillRect(-7, 2, 14, 5);
          break;

        case 8: // Tanjiro
          ctx.fillStyle = '#802020'; ctx.fillRect(-12, -18, 24, 18);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-9, -6, 18, 14);
          ctx.strokeStyle = '#ff6600'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.arc(0, 0, 20, 0, Math.PI * 2); ctx.stroke();
          break;

        case 9: // Zoro
          ctx.fillStyle = '#058030'; ctx.fillRect(-12, -16, 24, 16);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-9, -4, 18, 14);
          ctx.strokeStyle = '#00ff88'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.moveTo(-20, -16); ctx.lineTo(20, 16); ctx.stroke();
          ctx.beginPath(); ctx.moveTo(-20, 16); ctx.lineTo(20, -16); ctx.stroke();
          break;

        case 10: // Luffy Gear 5
          ctx.fillStyle = '#ffffff'; ctx.fillRect(-14, -20, 28, 22);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-9, -4, 18, 14);
          ctx.strokeStyle = '#ff6600'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.arc(-4, -1, 3, 0, Math.PI*2); ctx.stroke();
          ctx.beginPath(); ctx.arc(4, -1, 3, 0, Math.PI*2); ctx.stroke();
          break;

        case 11: // Naruto Sage
          ctx.fillStyle = '#ffcc00'; ctx.fillRect(-12, -20, 24, 18);
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-9, -6, 18, 14);
          ctx.fillStyle = '#ff6600'; ctx.fillRect(-8, -3, 5, 5); ctx.fillRect(3, -3, 5, 5);
          ctx.strokeStyle = '#00f0ff'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.arc(16, 8, 7, 0, Math.PI*2); ctx.stroke();
          break;

        // 2. WEAPONS & CYBER (12..21)
        case 12: // Cyber Greatsword
          ctx.fillStyle = '#ffd700'; ctx.fillRect(-3, -28, 6, 38);
          ctx.fillStyle = '#ffffff'; ctx.fillRect(-1, -26, 2, 34);
          ctx.fillStyle = '#8a6000'; ctx.fillRect(-9, 10, 18, 5);
          break;

        case 13: // Katana Muramasa
          ctx.fillStyle = '#ff0033'; ctx.fillRect(-2.5, -28, 5, 38);
          ctx.fillStyle = '#800000'; ctx.fillRect(-7, 10, 14, 4);
          break;

        case 14: // Thermal Katana
          ctx.fillStyle = '#00f0ff'; ctx.fillRect(-2.5, -28, 5, 38);
          ctx.fillStyle = '#ff0055'; ctx.fillRect(-1, -24, 2, 32);
          ctx.fillStyle = '#1c2130'; ctx.fillRect(-7, 10, 14, 5);
          break;

        case 15: // Plasma Buster
          ctx.fillStyle = '#041f4a'; ctx.fillRect(-13, -11, 26, 22);
          ctx.fillStyle = '#00f0ff'; ctx.beginPath(); ctx.arc(0, 0, 8 + breath, 0, Math.PI*2); ctx.fill();
          break;

        case 16: // Frostmourne
          ctx.fillStyle = '#5dffff'; ctx.fillRect(-4, -28, 8, 38);
          ctx.fillStyle = '#021020'; ctx.fillRect(-10, 10, 20, 6);
          break;

        case 17: // Mjolnir
          ctx.fillStyle = '#6b6d76'; ctx.fillRect(-14, -20, 28, 18);
          ctx.fillStyle = '#31869b'; ctx.fillRect(-3, -2, 6, 22);
          break;

        case 18: // Darksaber
          ctx.fillStyle = '#000000'; ctx.strokeStyle = '#ffffff'; ctx.lineWidth = 2;
          ctx.fillRect(-3, -28, 6, 38); ctx.strokeRect(-3, -28, 6, 38);
          break;

        case 19: // Energy Dual Daggers
          ctx.fillStyle = '#00f0ff'; ctx.fillRect(-2, -22, 4, 44);
          ctx.fillStyle = '#ff0055'; ctx.fillRect(-22, -2, 44, 4);
          break;

        case 20: // Plasma Scythe
          ctx.strokeStyle = '#a81fff'; ctx.lineWidth = 3;
          ctx.beginPath(); ctx.arc(0, -8, 20, 0, Math.PI); ctx.stroke();
          ctx.strokeStyle = '#ffffff'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.moveTo(0, -28); ctx.lineTo(0, 24); ctx.stroke();
          break;

        case 21: // Quantum Blaster
          ctx.strokeStyle = '#00f0ff'; ctx.lineWidth = 2;
          ctx.strokeRect(-18, -8, 36, 16);
          ctx.beginPath(); ctx.arc(0, 0, 10, 0, Math.PI*2); ctx.stroke();
          break;

        // 3. LOVE & BLING (22..31)
        case 22: // Crystal Faceted Heart
          ctx.fillStyle = '#ff0055';
          const s = 14 + breath * 2;
          ctx.beginPath();
          ctx.arc(-s/2, -s/3, s/2, 0, Math.PI * 2);
          ctx.arc(s/2, -s/3, s/2, 0, Math.PI * 2);
          ctx.fill();
          ctx.beginPath();
          ctx.moveTo(-s, -s/4); ctx.lineTo(s, -s/4); ctx.lineTo(0, s);
          ctx.fill();
          break;

        case 23: // Double Hearts
          ctx.fillStyle = '#00f0ff'; ctx.beginPath(); ctx.arc(-8, -3, 8, 0, Math.PI*2); ctx.fill();
          ctx.fillStyle = '#ff0055'; ctx.beginPath(); ctx.arc(8, 3, 8, 0, Math.PI*2); ctx.fill();
          break;

        case 24: // ECG Heartbeat
          ctx.strokeStyle = '#00ff88'; ctx.lineWidth = 2;
          ctx.beginPath();
          ctx.moveTo(-22, 0); ctx.lineTo(-10, 0); ctx.lineTo(-5, -15);
          ctx.lineTo(0, 16); ctx.lineTo(5, -8); ctx.lineTo(22, 0);
          ctx.stroke();
          break;

        case 25: // Rose Bouquet
          ctx.fillStyle = '#ff0033'; ctx.beginPath(); ctx.arc(0, -6, 12, 0, Math.PI*2); ctx.fill();
          ctx.fillStyle = '#00ff88'; ctx.fillRect(-2, 6, 4, 18);
          break;

        case 26: // Diamond Sparkle
          ctx.fillStyle = '#00f0ff';
          ctx.beginPath(); ctx.moveTo(0, -18); ctx.lineTo(14, 0); ctx.lineTo(0, 18); ctx.lineTo(-14, 0); ctx.fill();
          break;

        case 27: // Infinity Love
          ctx.strokeStyle = '#ff0055'; ctx.lineWidth = 3;
          ctx.beginPath(); ctx.arc(-10, 0, 10, 0, Math.PI*2); ctx.stroke();
          ctx.beginPath(); ctx.arc(10, 0, 10, 0, Math.PI*2); ctx.stroke();
          break;

        case 28: // Neon Wings
          ctx.strokeStyle = '#00f0ff'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.arc(-14, 0, 14, 0, Math.PI*2); ctx.stroke();
          ctx.beginPath(); ctx.arc(14, 0, 14, 0, Math.PI*2); ctx.stroke();
          break;

        case 29: // Halo Crown
          ctx.strokeStyle = '#ffd700'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.ellipse(0, -14, 18, 6, 0, 0, Math.PI*2); ctx.stroke();
          break;

        case 30: // Shooting Star
          const sx = Math.cos(t * 2) * 18;
          const sy = Math.sin(t * 2) * 18;
          ctx.fillStyle = '#ffd700';
          ctx.beginPath(); ctx.arc(sx, sy, 5, 0, Math.PI*2); ctx.fill();
          ctx.strokeStyle = 'rgba(255,215,0,0.4)'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.moveTo(0, 0); ctx.lineTo(sx, sy); ctx.stroke();
          break;

        case 31: // Fireworks
          for (let i = 0; i < 8; i++) {{
            const a = i * (Math.PI / 4) + t;
            ctx.fillStyle = i % 2 === 0 ? '#ff0055' : '#ffd700';
            ctx.fillRect(Math.cos(a) * 16, Math.sin(a) * 16, 3, 3);
          }}
          break;

        // 4. COSMIC PETS (32..41)
        case 32: // Red Panda
          ctx.fillStyle = '#fa6020'; ctx.fillRect(-14, -10, 28, 22);
          ctx.fillStyle = '#ffffff'; ctx.fillRect(-10, -4, 20, 14);
          ctx.fillStyle = '#000000'; ctx.fillRect(-5, -1, 3, 3); ctx.fillRect(2, -1, 3, 3);
          break;

        case 33: // Space Cat Astronaut
          ctx.strokeStyle = '#4a6984'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.arc(0, 0, 18, 0, Math.PI*2); ctx.stroke();
          ctx.fillStyle = '#ffffff'; ctx.fillRect(-10, -8, 20, 16);
          break;

        case 34: // Shiba Inu
          ctx.fillStyle = '#fdb040'; ctx.fillRect(-14, -10, 28, 22);
          ctx.fillStyle = '#ffffff'; ctx.fillRect(-10, -2, 20, 12);
          break;

        case 35: // Cyber Bunny
          ctx.fillStyle = '#ffffff'; ctx.fillRect(-10, -8, 20, 20);
          ctx.fillRect(-8, -26, 6, 18); ctx.fillRect(2, -26, 6, 18);
          ctx.fillStyle = '#ff0055'; ctx.fillRect(-5, -2, 3, 3); ctx.fillRect(2, -2, 3, 3);
          break;

        case 36: // Hamster
          ctx.fillStyle = '#ed8020'; ctx.beginPath(); ctx.arc(0, 0, 16, 0, Math.PI*2); ctx.fill();
          break;

        case 37: // Sleeping Fox
          ctx.fillStyle = '#fa6020'; ctx.beginPath(); ctx.arc(0, 0, 16, 0, Math.PI*2); ctx.fill();
          ctx.strokeStyle = '#000'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.arc(-5, -2, 3, 0, Math.PI); ctx.stroke();
          ctx.beginPath(); ctx.arc(5, -2, 3, 0, Math.PI); ctx.stroke();
          break;

        case 38: // Cyber Dragon
          ctx.strokeStyle = '#00ff88'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.arc(0, 0, 18, 0, Math.PI*2); ctx.stroke();
          ctx.fillStyle = '#00ff88'; ctx.beginPath(); ctx.moveTo(-8, -18); ctx.lineTo(0, -28); ctx.lineTo(8, -18); ctx.fill();
          break;

        case 39: // Phoenix
          ctx.fillStyle = '#ff0033'; ctx.beginPath(); ctx.arc(0, 0, 12, 0, Math.PI*2); ctx.fill();
          ctx.strokeStyle = '#ffd700'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.arc(-14, -4, 12, 0, Math.PI*2); ctx.stroke();
          ctx.beginPath(); ctx.arc(14, -4, 12, 0, Math.PI*2); ctx.stroke();
          break;

        case 40: // Penguin Cyber
          ctx.fillStyle = '#111111'; ctx.fillRect(-12, -14, 24, 28);
          ctx.fillStyle = '#ffffff'; ctx.fillRect(-8, -8, 16, 20);
          ctx.fillStyle = '#ffd700'; ctx.fillRect(-3, -2, 6, 4);
          break;

        case 41: // Axolotl Glow
          ctx.fillStyle = '#fd1580'; ctx.fillRect(-14, -10, 28, 22);
          ctx.fillStyle = '#ff00aa'; ctx.beginPath(); ctx.arc(-16, -4, 5, 0, Math.PI*2); ctx.fill();
          ctx.beginPath(); ctx.arc(16, -4, 5, 0, Math.PI*2); ctx.fill();
          break;

        // 5. RETRO GAMING (42..49)
        case 42: // Pac-Man
          ctx.fillStyle = '#ffd700';
          ctx.beginPath(); ctx.arc(0, 0, 16, 0.25 * Math.PI, 1.75 * Math.PI); ctx.lineTo(0, 0); ctx.fill();
          break;

        case 43: // Space Invader
          ctx.fillStyle = '#00ff88'; ctx.fillRect(-14, -10, 28, 20);
          ctx.fillStyle = '#000000'; ctx.fillRect(-8, -4, 4, 4); ctx.fillRect(4, -4, 4, 4);
          break;

        case 44: // Tetris T-Block
          ctx.fillStyle = '#a81fff'; ctx.fillRect(-18, -6, 36, 12); ctx.fillRect(-6, 6, 12, 12);
          break;

        case 45: // Megaman Buster
          ctx.fillStyle = '#041f4a'; ctx.fillRect(-16, -12, 32, 24);
          ctx.fillStyle = '#ffd700'; ctx.beginPath(); ctx.arc(14, 0, 8, 0, Math.PI*2); ctx.fill();
          break;

        case 46: // Mario Mushroom
          ctx.fillStyle = '#ff0033'; ctx.fillRect(-16, -16, 32, 20);
          ctx.fillStyle = '#ffffff'; ctx.beginPath(); ctx.arc(-8, -8, 5, 0, Math.PI*2); ctx.fill();
          ctx.beginPath(); ctx.arc(8, -8, 5, 0, Math.PI*2); ctx.fill();
          ctx.fillStyle = '#fff2db'; ctx.fillRect(-10, 4, 20, 12);
          break;

        case 47: // Zelda Triforce
          ctx.fillStyle = '#ffd700';
          ctx.beginPath(); ctx.moveTo(0, -20); ctx.lineTo(-18, 14); ctx.lineTo(18, 14); ctx.fill();
          break;

        case 48: // Sonic Ring
          ctx.strokeStyle = '#ffd700'; ctx.lineWidth = 4;
          ctx.beginPath(); ctx.arc(0, 0, 18, 0, Math.PI*2); ctx.stroke();
          break;

        case 49: // Disco Mirror Ball (49)
        default:
          ctx.strokeStyle = '#ffffff'; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.arc(0, 0, 18, 0, Math.PI*2); ctx.stroke();
          for (let i = -12; i <= 12; i += 6) {{
            ctx.beginPath(); ctx.moveTo(-14, i); ctx.lineTo(14, i); ctx.stroke();
          }}
          break;
      }}

      ctx.restore();
    }}

    // PARALLAX BACKGROUND PARTICLES
    function renderParallaxBackground(ctx, id, t) {{
      const cat = Math.floor(id / 10);
      if (cat === 0) {{
        // Anime: Trăng vàng khuyết + cánh hoa đào rơi
        ctx.fillStyle = '#ffe000';
        ctx.beginPath(); ctx.arc(142, 42, 14, 0, Math.PI * 2); ctx.fill();
        ctx.fillStyle = '#000000';
        ctx.beginPath(); ctx.arc(136, 38, 12, 0, Math.PI * 2); ctx.fill();
        ctx.fillStyle = '#fd1480';
        for (let i = 0; i < 6; i++) {{
          const px = (Math.sin(t * 0.5 + i) * 30 + 30 * i) % 172;
          const py = (t * 25 + i * 50) % 240;
          ctx.fillRect(px, py, 2, 2);
        }}
      }} else if (cat === 1) {{
        // Cyber: Lưới ma trận Perspective 3D Grid dưới chân
        ctx.strokeStyle = '#00ff88';
        ctx.lineWidth = 1;
        for (let y = 195; y <= 245; y += 12) {{
          ctx.beginPath(); ctx.moveTo(10, y); ctx.lineTo(162, y); ctx.stroke();
        }}
        ctx.strokeStyle = '#004422';
        for (let x = 20; x <= 152; x += 30) {{
          ctx.beginPath(); ctx.moveTo(86, 175); ctx.lineTo(x, 245); ctx.stroke();
        }}
      }} else if (cat === 2) {{
        // Love: Cực quang Aurora lượn sóng
        ctx.fillStyle = 'rgba(255, 0, 85, 0.25)';
        for (let x = 10; x < 162; x += 4) {{
          const waveY = 55 + Math.sin(t + x * 0.05) * 10;
          ctx.fillRect(x, waveY, 3, 18);
        }}
      }}
    }}

    // 60 FPS MAIN LOOP
    function loop() {{
      time += 0.035;

      // 1. Render Hero Screen (172x320) - Pure AMOLED Black
      heroCtx.fillStyle = '#000000';
      heroCtx.fillRect(0, 0, 172, 320);

      // Ambient background particles full-screen (0 - 320px)
      const pal = resolvePaletteHex(currentPaletteId);
      heroCtx.fillStyle = pal;
      for (let i = 0; i < 20; i++) {{
        const py = (time * (20 + i * 5) + i * 16) % 320;
        const px = (i * 9 + 4) % 172;
        heroCtx.fillRect(px, 320 - py, 1.5, 1.5);
      }}

      // Top Header: Centered pristine typography
      heroCtx.fillStyle = '#00f0ff';
      heroCtx.font = 'bold 10px monospace';
      heroCtx.textAlign = 'center';
      const itemTitle = currentQuote ? currentQuote.substring(0, 24) : (CATALOG[currentSpriteId] ? CATALOG[currentSpriteId].name.toUpperCase() : 'THEME');
      heroCtx.fillText(itemTitle, 172 / 2, 16);

      // Render Parallax Background
      renderParallaxBackground(heroCtx, currentSpriteId, time);

      // Render Active Character / Scene at Safe Stage Center (cy = 138, scale = 1.55) matching ESP32
      renderSpecificAnimation(heroCtx, currentSpriteId, 172 / 2, 138, 1.55, time);

      // SAFE-AREA VISUAL NOVEL DIALOGUE BOX (Y = 256 - 306, H = 50, W = 156 at X = 8)
      heroCtx.save();
      heroCtx.fillStyle = 'rgba(8, 10, 18, 0.88)';
      heroCtx.strokeStyle = 'rgba(0, 240, 255, 0.35)';
      heroCtx.lineWidth = 1;
      heroCtx.beginPath();
      heroCtx.roundRect(8, 256, 156, 50, 8);
      heroCtx.fill();
      heroCtx.stroke();

      // Theme Title Badge at top-left of the box
      heroCtx.fillStyle = '#00f0ff';
      heroCtx.font = 'bold 9px monospace';
      heroCtx.textAlign = 'left';
      const badgeTitle = CATALOG[currentSpriteId] ? CATALOG[currentSpriteId].name.toUpperCase() : 'SMART KEYCHAIN';
      heroCtx.fillText(badgeTitle.substring(0, 22), 16, 268);

      // Custom Quote or Love Message (centered or 2-line smart word-wrap)
      heroCtx.fillStyle = '#ffffff';
      heroCtx.font = '9px monospace';
      const quoteText = currentQuote || (CATALOG[currentSpriteId] ? CATALOG[currentSpriteId].quote : 'Du o the gioi nao, anh van tim thay em.');
      if (quoteText.length <= 20) {{
        heroCtx.textAlign = 'center';
        heroCtx.fillText(quoteText, 172 / 2, 288);
      }} else {{
        heroCtx.textAlign = 'left';
        heroCtx.fillText(quoteText.substring(0, 20), 16, 284);
        heroCtx.fillText(quoteText.substring(20, 42), 16, 298);
      }}
      heroCtx.restore();

      // 2. Render 50 Mini-Canvases in Grid
      CATALOG.forEach(item => {{
        const card = document.getElementById(`card-${{item.id}}`);
        if (card && card.style.display !== 'none') {{
          const mini = document.getElementById(`mini-${{item.id}}`);
          if (mini) {{
            const mCtx = mini.getContext('2d');
            mCtx.fillStyle = '#000000';
            mCtx.fillRect(0, 0, 72, 72);
            renderSpecificAnimation(mCtx, item.id, 36, 36, 0.9, time);
          }}
        }}
      }});

      requestAnimationFrame(loop);
    }}
    loop();
  </script>
</body>
</html>
"""

if __name__ == "__main__":
    uvicorn.run("main:app", host="0.0.0.0", port=8000, reload=False)
