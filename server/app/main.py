import os
import json
from typing import List, Dict, Optional
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
    "quote": "Dù ở thế giới nào, anh vẫn luôn tìm thấy em.",
    "text_color": "#FFB800",
    "text_size": 1,
    "scenery_id": 0
}

class ConnectionManager:
    def __init__(self):
        self.browser_connections: List[WebSocket] = []
        self.device_connections: Dict[WebSocket, dict] = {}

    async def connect_browser(self, websocket: WebSocket):
        subprotocol = websocket.headers.get("sec-websocket-protocol")
        await websocket.accept(subprotocol=subprotocol)
        self.browser_connections.append(websocket)
        is_online = len(self.device_connections) > 0
        info = list(self.device_connections.values())[0] if is_online else None
        await websocket.send_text(json.dumps({
            "type": "SYNC",
            "data": state,
            "device_online": is_online,
            "device_info": info
        }))

    async def connect_device(self, websocket: WebSocket, client_info: dict):
        subprotocol = websocket.headers.get("sec-websocket-protocol")
        await websocket.accept(subprotocol=subprotocol)
        self.device_connections[websocket] = client_info
        print(f"[DEVICE CONNECTED] IP: {client_info.get('ip')}")
        await websocket.send_text(json.dumps({"type": "SYNC", "data": state}))
        await self.broadcast_presence()

    def disconnect(self, websocket: WebSocket):
        if websocket in self.browser_connections:
            self.browser_connections.remove(websocket)
        if websocket in self.device_connections:
            del self.device_connections[websocket]
            print("[DEVICE DISCONNECTED]")

    async def broadcast_presence(self):
        is_online = len(self.device_connections) > 0
        info = list(self.device_connections.values())[0] if is_online else None
        msg_str = json.dumps({"type": "DEVICE_PRESENCE", "online": is_online, "info": info})
        for ws in self.browser_connections:
            try:
                await ws.send_text(msg_str)
            except Exception:
                pass

    async def broadcast(self, message: dict):
        msg_str = json.dumps(message)
        for ws in self.browser_connections:
            try:
                await ws.send_text(msg_str)
            except Exception:
                pass
        for ws in self.device_connections.keys():
            try:
                await ws.send_text(msg_str)
            except Exception:
                pass

manager = ConnectionManager()

@app.websocket("/ws/keychain")
async def websocket_endpoint(websocket: WebSocket, client: Optional[str] = None):
    client_ip = websocket.client.host if websocket.client else "Unknown"
    is_device = (client == "esp32")
    if is_device:
        await manager.connect_device(websocket, {"ip": client_ip, "type": "ESP32S"})
    else:
        await manager.connect_browser(websocket)

    try:
        while True:
            data = await websocket.receive_text()
            try:
                payload = json.loads(data)
                action = payload.get("action")
                if action == "REGISTER_DEVICE":
                    if websocket in manager.browser_connections:
                        manager.browser_connections.remove(websocket)
                    info = {"ip": payload.get("ip", client_ip), "type": payload.get("device", "ESP32S")}
                    manager.device_connections[websocket] = info
                    await manager.broadcast_presence()
                    await websocket.send_text(json.dumps({"type": "SYNC", "data": state}))
                    continue

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
                elif action == "SET_DESIGN":
                    if "sprite_id" in payload:
                        state["sprite_id"] = int(payload["sprite_id"])
                        if 0 <= state["sprite_id"] < len(ANIMATIONS):
                            state["quote"] = ANIMATIONS[state["sprite_id"]]["quote"]
                    if "text_color" in payload:
                        state["text_color"] = str(payload["text_color"])
                    if "text_size" in payload:
                        state["text_size"] = int(payload["text_size"])
                    if "scenery_id" in payload:
                        state["scenery_id"] = int(payload["scenery_id"])
                    if "quote" in payload:
                        state["quote"] = str(payload["quote"])
                    if "brightness" in payload:
                        state["brightness"] = int(payload["brightness"])
                    await manager.broadcast({"type": "UPDATE", "data": state})
                    continue
                elif action == "SET_QR":
                    state["qr_mode"] = payload.get("value", True)
                elif action == "PING":
                    await websocket.send_text(json.dumps({"type": "PONG"}))
                    continue

                await manager.broadcast({"type": "UPDATE", "data": state})
            except Exception:
                pass
    except WebSocketDisconnect:
        manager.disconnect(websocket)
        await manager.broadcast_presence()
    except Exception:
        manager.disconnect(websocket)
        await manager.broadcast_presence()

@app.get("/api/presence")
def get_presence():
    is_online = len(manager.device_connections) > 0
    info = list(manager.device_connections.values())[0] if is_online else None
    return {"online": is_online, "device_info": info}

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

@app.post("/api/design")
async def api_design(
    quote: Optional[str] = Form(None),
    text_color: Optional[str] = Form(None),
    text_size: Optional[int] = Form(None),
    scenery_id: Optional[int] = Form(None),
    sprite_id: Optional[int] = Form(None),
    brightness: Optional[int] = Form(None)
):
    if quote is not None: state["quote"] = quote
    if text_color is not None: state["text_color"] = text_color
    if text_size is not None: state["text_size"] = text_size
    if scenery_id is not None: state["scenery_id"] = scenery_id
    if sprite_id is not None: state["sprite_id"] = sprite_id
    if brightness is not None: state["brightness"] = brightness
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "data": state}

INDEX_HTML = """<!DOCTYPE html>
<html lang="vi">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Smart Keychain — 50 Animations Studio (Modern Split Edition)</title>
  <style>
    :root {
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
    }
    * { box-sizing: border-box; margin: 0; padding: 0; }
    body {
      background: var(--bg);
      color: var(--text-1);
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Helvetica, Arial, sans-serif;
      min-height: 100vh;
      -webkit-font-smoothing: antialiased;
      overflow-x: hidden;
    }

    /* TOP NAVBAR */
    .top-navbar {
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
    }
    .brand-group {
      display: flex;
      align-items: center;
      gap: 12px;
    }
    .brand-logo {
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
    }
    .brand-title {
      font-size: 16px;
      font-weight: 800;
      letter-spacing: 0.5px;
    }
    .status-telemetry {
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
    }
    .pulse-dot {
      width: 7px;
      height: 7px;
      border-radius: 50%;
      background: var(--green);
      box-shadow: 0 0 8px var(--green);
      animation: pulse 1.6s infinite ease-in-out;
    }
    @keyframes pulse {
      0%, 100% { transform: scale(1); opacity: 1; }
      50% { transform: scale(1.4); opacity: 0.6; }
    }

    /* MAIN STUDIO LAYOUT (2 COLUMNS) */
    .studio-layout {
      max-width: 1380px;
      margin: 0 auto;
      padding: 24px 28px 60px;
      display: grid;
      grid-template-columns: 360px 1fr;
      gap: 28px;
      align-items: start;
    }

    /* LEFT COLUMN: STICKY SIMULATOR & HARDWARE CONTROLS */
    .left-pod {
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
    }
    .bezel-container {
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 10px;
    }
    .device-bezel {
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
    }
    .device-bezel:hover {
      border-color: var(--cyan);
      box-shadow: 0 16px 40px rgba(0,0,0,0.8), 0 0 20px rgba(0,240,255,0.25);
    }
    .device-bezel:active { transform: scale(0.98); }
    .screen-canvas {
      width: 172px;
      height: 320px;
      border-radius: 18px;
      background: #000;
      display: block;
    }
    .bezel-hint {
      font-size: 10px;
      font-family: var(--font-mono);
      color: var(--text-muted);
      letter-spacing: 0.5px;
    }

    .pod-telemetry {
      display: flex;
      justify-content: space-between;
      align-items: center;
      padding: 8px 12px;
      background: rgba(255,255,255,0.03);
      border-radius: 10px;
      font-family: var(--font-mono);
      font-size: 11px;
    }
    .pod-title { color: var(--cyan); font-weight: 800; }
    .pod-fps { color: var(--green); font-weight: 700; }

    /* CONTROL GROUPS */
    .control-group {
      display: flex;
      flex-direction: column;
      gap: 8px;
    }
    .control-label {
      font-size: 11px;
      font-weight: 700;
      letter-spacing: 0.8px;
      text-transform: uppercase;
      color: var(--text-2);
      font-family: var(--font-mono);
    }
    .gem-palette-grid {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 6px;
    }
    .gem-btn {
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
    }
    .gem-btn:hover { border-color: rgba(255,255,255,0.3); }
    .gem-btn.active {
      border-color: var(--cyan);
      background: rgba(0, 240, 255, 0.12);
      box-shadow: 0 0 10px rgba(0, 240, 255, 0.2);
    }
    .gem-circle {
      width: 8px;
      height: 8px;
      border-radius: 50%;
      flex-shrink: 0;
    }

     input[type=range] {
      -webkit-appearance: none;
      width: 100%;
      background: #171b26;
      height: 6px;
      border-radius: 3px;
      outline: none;
    }
    input[type=range]::-webkit-slider-thumb {
      -webkit-appearance: none;
      width: 16px;
      height: 16px;
      border-radius: 50%;
      background: var(--cyan);
      cursor: pointer;
      box-shadow: 0 0 8px var(--cyan);
    }
    input[type=range]::-webkit-slider-thumb:hover {
      background: #33f3ff;
      box-shadow: 0 0 10px var(--cyan);
    }

    .qr-action-btn {
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
    }
    .qr-action-btn:hover {
      background: rgba(0, 240, 255, 0.18);
      border-color: var(--cyan);
      box-shadow: 0 0 14px var(--cyan-glow);
    }
    .qr-action-btn:active { transform: scale(0.98); }

    /* RIGHT COLUMN: QUICK CHIPS & 50 THEMES GALLERY */
    .right-pod {
      display: flex;
      flex-direction: column;
      gap: 22px;
    }

    /* QUICK MESSAGE TRANSMITTER */
    .msg-card {
      background: var(--bg-surface);
      border: 1px solid var(--border-subtle);
      border-radius: 18px;
      padding: 18px 22px;
      display: flex;
      flex-direction: column;
      gap: 14px;
      box-shadow: 0 8px 24px rgba(0,0,0,0.3);
    }
    .msg-row {
      display: flex;
      gap: 10px;
    }
    .msg-input {
      flex: 1;
      background: #040508;
      border: 1px solid var(--border-subtle);
      border-radius: 10px;
      padding: 12px 16px;
      font-size: 13px;
      color: #fff;
      outline: none;
      transition: border-color 0.15s ease;
    }
    .msg-input:focus { border-color: var(--cyan); }
    .send-action-btn {
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
    }
    .send-action-btn:hover { opacity: 0.92; }
    .send-action-btn:active { transform: scale(0.97); }

    /* QUICK LOVE CHIPS */
    .chips-label {
      font-size: 11px;
      color: var(--text-2);
      font-weight: 700;
      font-family: var(--font-mono);
      text-transform: uppercase;
    }
    .chips-row {
      display: flex;
      flex-wrap: wrap;
      gap: 8px;
    }
    .love-chip {
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
    }
    .love-chip:hover {
      border-color: var(--cyan);
      background: rgba(0, 240, 255, 0.08);
      color: var(--cyan);
      transform: translateY(-1px);
    }
    .love-chip:active { transform: scale(0.96); }

    /* TABS & SEARCH */
    .filter-bar {
      display: flex;
      align-items: center;
      justify-content: space-between;
      gap: 14px;
      flex-wrap: wrap;
    }
    .tabs-group {
      display: flex;
      gap: 8px;
      overflow-x: auto;
      padding-bottom: 4px;
    }
    .tab-btn {
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
    }
    .tab-btn:hover { color: #fff; border-color: rgba(255,255,255,0.2); }
    .tab-btn.active {
      background: #151928;
      color: var(--cyan);
      border-color: var(--cyan);
    }
    .tab-counter {
      font-size: 10px;
      padding: 2px 6px;
      border-radius: 999px;
      background: rgba(255,255,255,0.1);
      margin-left: 4px;
    }

    .search-box {
      background: #040508;
      border: 1px solid var(--border-subtle);
      border-radius: 10px;
      padding: 8px 14px;
      font-size: 12px;
      color: #fff;
      outline: none;
      width: 200px;
      transition: border-color 0.15s ease;
    }
    .search-box:focus { border-color: var(--cyan); }

    /* 50 CARDS GRID */
    .cards-grid {
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(180px, 1fr));
      gap: 14px;
    }
    .card-item {
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
    }
    .card-item:hover {
      background: var(--bg-card-hover);
      border-color: rgba(255, 255, 255, 0.22);
      transform: translateY(-2px);
    }
    .card-item.active-card {
      border-color: var(--cyan);
      background: rgba(0, 240, 255, 0.05);
      box-shadow: 0 0 16px rgba(0, 240, 255, 0.25);
    }
    .active-badge {
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
    }
    .card-item.active-card .active-badge { display: block; }
    .preview-canvas {
      width: 72px;
      height: 72px;
      border-radius: 10px;
      background: #000;
    }
    .card-name {
      font-size: 11.5px;
      font-weight: 700;
      text-align: center;
      color: #fff;
      line-height: 1.3;
      white-space: nowrap;
      overflow: hidden;
      text-overflow: ellipsis;
      max-width: 100%;
    }
    .card-category {
      font-size: 9px;
      font-family: var(--font-mono);
      color: var(--cyan);
      text-transform: uppercase;
      letter-spacing: 0.5px;
    }

    /* TOAST */
    .toast-pill {
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
    }
    .toast-pill.visible { transform: translateY(0); }

    /* RESPONSIVE MOBILE */
    @media (max-width: 960px) {
      .studio-layout {
        grid-template-columns: 1fr;
        padding: 16px;
      }
      .left-pod {
        position: relative;
        top: 0;
        align-items: center;
      }
      .cards-grid {
        grid-template-columns: repeat(auto-fill, minmax(140px, 1fr));
      }
      .search-box { width: 100%; }
      .msg-row { flex-direction: column; }
      .send-action-btn { padding: 12px; }
    }
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

      <!-- GOD-MODE DESIGN STUDIO CONTROLS -->
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
    const CATALOG = __CATALOG_JSON__;
    let currentSpriteId = 0;
    let currentPaletteId = 0;
    let currentQuote = "Dù ở thế giới nào, anh vẫn luôn tìm thấy em.";
    let ws;
    let time = 0;
    const heroCanvas = document.getElementById('heroCanvas');
    const heroCtx = heroCanvas.getContext('2d');

    // WEBSOCKET INITIALIZER
    function initWebSocket() {
      const proto = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
      ws = new WebSocket(`${proto}//${window.location.host}/ws/keychain`);
      ws.onmessage = (event) => {
        try {
          const res = JSON.parse(event.data);
          if (res.data) {
            if (res.data.sprite_id !== undefined) selectCard(res.data.sprite_id, false);
            if (res.data.palette_id !== undefined) currentPaletteId = res.data.palette_id;
            if (res.data.quote) currentQuote = res.data.quote;
            if (res.data.brightness) {
              document.getElementById('brightRange').value = res.data.brightness;
              document.getElementById('brightVal').innerText = Math.round((res.data.brightness / 255) * 100) + '%';
            }
          }
        } catch(e) {}
      };
      ws.onclose = () => setTimeout(initWebSocket, 2000);
    }
    initWebSocket();

    // POPULATE 50 CARDS
    function populateGrid() {
      const container = document.getElementById('cardsContainer');
      container.innerHTML = '';
      CATALOG.forEach(item => {
        const card = document.createElement('div');
        card.className = 'card-item' + (item.id === currentSpriteId ? ' active-card' : '');
        card.id = `card-${item.id}`;
        card.dataset.tab = item.tab;
        card.dataset.name = item.name.toLowerCase();
        card.onclick = () => selectCard(item.id, true);

        card.innerHTML = `
          <div class="active-badge">ĐANG CHIẾU</div>
          <canvas class="preview-canvas" id="mini-${item.id}" width="72" height="72"></canvas>
          <div class="card-name">${item.name}</div>
          <div class="card-category">${item.palette}</div>
        `;
        container.appendChild(card);
      });
    }
    populateGrid();

    // CATEGORY FILTER
    function switchCategory(cat, btn) {
      document.querySelectorAll('.tab-btn').forEach(b => b.classList.remove('active'));
      btn.classList.add('active');
      document.querySelectorAll('.card-item').forEach(c => {
        c.style.display = (cat === 'all' || c.dataset.tab === cat) ? 'flex' : 'none';
      });
    }

    // SEARCH FILTER
    function filterThemes(q) {
      const query = q.trim().toLowerCase();
      document.querySelectorAll('.card-item').forEach(c => {
        const match = !query || c.dataset.name.includes(query);
        c.style.display = match ? 'flex' : 'none';
      });
    }

    // SELECT CARD
    function selectCard(id, pushNetwork = true) {
      currentSpriteId = id;
      document.querySelectorAll('.card-item').forEach((c, idx) => {
        c.classList.toggle('active-card', idx === id);
      });
      if (CATALOG[id]) {
        currentQuote = CATALOG[id].quote;
        document.getElementById('podTitle').innerText = CATALOG[id].name.toUpperCase();
      }
      if (pushNetwork) {
        if (ws && ws.readyState === WebSocket.OPEN) {
          ws.send(JSON.stringify({action: 'SET_SPRITE', value: id}));
        }
        fetch('/api/sprite', { method: 'POST', body: new URLSearchParams({id: id}) });
        showToast(`Kích hoạt: ${CATALOG[id].name}`);
      }
    }

    // INTERACTIVE CLICK ON SIMULATOR
    function triggerNextThemeClick() {
      const nextId = (currentSpriteId + 1) % CATALOG.length;
      selectCard(nextId, true);
    }

    // SET PALETTE
    function setPaletteChoice(id) {
      currentPaletteId = id;
      document.querySelectorAll('.gem-btn').forEach((p, idx) => {
        p.classList.toggle('active', idx === id);
      });
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({action: 'SET_PALETTE', value: id}));
      }
      fetch('/api/palette', { method: 'POST', body: new URLSearchParams({id: id}) });
      showToast('Đã đổi màu kim cương!');
    }

    // BRIGHTNESS
    function sendBrightness(val) {
      document.getElementById('brightVal').innerText = Math.round((val / 255) * 100) + '%';
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({action: 'SET_BRIGHTNESS', value: parseInt(val)}));
      }
      fetch('/api/brightness', { method: 'POST', body: new URLSearchParams({value: val})});
    }

    // REMOTE QR ACTION
    function triggerRemoteQR() {
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({action: 'SET_QR', value: true}));
      }
      fetch('/api/qr', { method: 'POST' });
      showToast('Đang mở màn hình QR trên móc khóa...');
    }

    // CUSTOM QUOTE
    function sendCustomQuote() {
      const input = document.getElementById('quoteField');
      const val = input.value.trim();
      if (!val) return;
      currentQuote = val;
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({action: 'SET_QUOTE', value: val}));
      }
      fetch('/api/quote', { method: 'POST', body: new URLSearchParams({text: val})});
      showToast('Lời nhắn đã gửi tới móc khóa!');
      input.value = '';
    }

    // QUICK LOVE CHIP
    function sendQuickChip(text) {
      currentQuote = text;
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({action: 'SET_QUOTE', value: text}));
      }
      fetch('/api/quote', { method: 'POST', body: new URLSearchParams({text: text})});
      showToast(`Đã gửi: "${text}"`);
    }

    // TOAST
    function showToast(msg) {
      const toast = document.getElementById('toastPill');
      toast.innerText = msg;
      toast.classList.add('visible');
      setTimeout(() => toast.classList.remove('visible'), 2200);
    }

    // PALETTE COLOR RESOLVER
    function resolvePaletteHex(pid) {
      switch(pid % 6) {
        case 0: return '#00f0ff';
        case 1: return '#ff0055';
        case 2: return '#ffb800';
        case 3: return '#fcaeae';
        case 4: return '#00ff88';
        case 5: return '#9d00ff';
        default: return '#00f0ff';
      }
    }

    // 50 ANIMATIONS VECTOR/CANVAS ENGINE
    // HELPER DRAWING PRIMITIVES MATCHING LOVYANGFX
    function frRect(ctx, x, y, w, h, r, color) {
      ctx.fillStyle = color;
      ctx.beginPath();
      if (ctx.roundRect) ctx.roundRect(x, y, w, h, r);
      else ctx.rect(x, y, w, h);
      ctx.fill();
    }
    function drRect(ctx, x, y, w, h, r, color, lw=1) {
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.beginPath();
      if (ctx.roundRect) ctx.roundRect(x, y, w, h, r);
      else ctx.rect(x, y, w, h);
      ctx.stroke();
    }
    function fCirc(ctx, x, y, r, color) {
      ctx.fillStyle = color;
      ctx.beginPath();
      ctx.arc(x, y, Math.max(0.5, r), 0, Math.PI*2);
      ctx.fill();
    }
    function dCirc(ctx, x, y, r, color, lw=1) {
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.beginPath();
      ctx.arc(x, y, Math.max(0.5, r), 0, Math.PI*2);
      ctx.stroke();
    }
    function fTri(ctx, x1, y1, x2, y2, x3, y3, color) {
      ctx.fillStyle = color;
      ctx.beginPath();
      ctx.moveTo(x1, y1); ctx.lineTo(x2, y2); ctx.lineTo(x3, y3); ctx.closePath();
      ctx.fill();
    }
    function dTri(ctx, x1, y1, x2, y2, x3, y3, color, lw=1) {
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.beginPath();
      ctx.moveTo(x1, y1); ctx.lineTo(x2, y2); ctx.lineTo(x3, y3); ctx.closePath();
      ctx.stroke();
    }
    function fRect(ctx, x, y, w, h, color) {
      ctx.fillStyle = color;
      ctx.fillRect(x, y, w, h);
    }
    function dRect(ctx, x, y, w, h, color, lw=1) {
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.strokeRect(x, y, w, h);
    }
    function dLine(ctx, x1, y1, x2, y2, color, lw=1) {
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.beginPath();
      ctx.moveTo(x1, y1); ctx.lineTo(x2, y2);
      ctx.stroke();
    }
    function dPixel(ctx, x, y, color, sz=2) {
      ctx.fillStyle = color;
      ctx.fillRect(x - sz/2, y - sz/2, sz, sz);
    }
    function fEllip(ctx, x, y, rx, ry, color) {
      ctx.fillStyle = color;
      ctx.beginPath();
      ctx.ellipse(x, y, Math.max(0.5, rx), Math.max(0.5, ry), 0, 0, Math.PI*2);
      ctx.fill();
    }
    function dEllip(ctx, x, y, rx, ry, color, lw=1) {
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.beginPath();
      ctx.ellipse(x, y, Math.max(0.5, rx), Math.max(0.5, ry), 0, 0, Math.PI*2);
      ctx.stroke();
    }
    function dArc(ctx, x, y, r1, r2, sa, ea, color) {
      ctx.strokeStyle = color;
      ctx.lineWidth = Math.max(1, r2 - r1);
      ctx.beginPath();
      ctx.arc(x, y, (r1+r2)/2, sa * Math.PI/180, ea * Math.PI/180);
      ctx.stroke();
    }

    // 50 ANIMATIONS VECTOR/CANVAS ENGINE 1:1 LOVYANGFX
    function renderSpecificAnimation(ctx, id, cx, cy, scale, t) {
      ctx.save();
      ctx.translate(cx, cy);
      ctx.scale(scale, scale);

      const breath = Math.sin(t * 3.5);
      const angle = t * 2.0;

      switch (id) {
        case 0: {
          // Hu Tao & Boo Tao
          // Tóc twintails bồng bềnh 3 lớp màu (bóng đổ 0x2800 -> nâu đỏ 0x5100 -> ngọn cam 0xA960)
          frRect(ctx, -36, -18 + (Math.sin(breath * 6.28) * 4), 14, 46, 6, "#290000");
          frRect(ctx, -34, -16 + (Math.sin(breath * 6.28) * 4), 10, 42, 5, "#522000");
          frRect(ctx, 22, -18 + (Math.sin(breath * 6.28 + 1.2) * 4), 14, 46, 6, "#290000");
          frRect(ctx, 24, -16 + (Math.sin(breath * 6.28 + 1.2) * 4), 10, 42, 5, "#522000");
          
          // Khuôn mặt anime & bóng cổ
          frRect(ctx, -18, -14, 36, 30, 6, "#ffff94");
          fRect(ctx, -14, 12, 28, 4, "#ff9d00"); // Bóng cằm
          
          // Mũ Bát Phương (Porkpie Hat) + Hoa Mận Đỏ thêu viền vàng
          frRect(ctx, -26, -38, 52, 24, 6, "#181818");
          drRect(ctx, -26, -38, 52, 24, 6, "#080808");
          fCirc(ctx, -12, -28, 5, "#ff0000"); // Hoa mận đỏ
          dPixel(ctx, -12, -28, "#ffee00"); // Nhụy vàng
          dPixel(ctx, -14, -28, "#ff3c00");
          dPixel(ctx, -10, -28, "#ff3c00");
          
          // Đôi mắt hoa đào (Đỏ mận + đồng tử sao + đốm sáng trắng)
          frRect(ctx, -14, -6, 9, 11, 3, "#bd0000");
          frRect(ctx, 5, -6, 9, 11, 3, "#bd0000");
          fRect(ctx, -12, -5, 5, 8, "#ff0000");
          fRect(ctx, 7, -5, 5, 8, "#ff0000");
          dPixel(ctx, -11, -4, "#ffffff"); // Anime shine
          dPixel(ctx, 8, -4, "#ffffff");
          fCirc(ctx, -10, 6, 2, "#ff9573"); // Má hồng
          fCirc(ctx, 10, 6, 2, "#ff9573");
          
          // Hồn ma Boo Tao bay lượn quanh chủ nhân
          {
          let gx = 34 + (Math.cos(angle * 2.2) * 10);
          let gy = -28 + (Math.sin(angle * 2.2) * 10);
          fCirc(ctx, gx, gy, 12, "#ffffff");
          fTri(ctx, gx - 8, gy + 4, gx + 8, gy + 4, gx, gy + 16, "#ffffff"); // Đuôi ma
          fCirc(ctx, gx - 4, gy - 3, 2, "#000000"); // Mắt ma
          fCirc(ctx, gx + 4, gy - 3, 2, "#000000");
          frRect(ctx, gx - 3, gy + 2, 6, 3, 1, "#ff0000"); // Miệng cười mở
          dPixel(ctx, gx + (Math.sin(angle * 4) * 5), gy - 12, "#ff4c00");
          }
          break;
        }

        case 1: {
          // Anya Forger (Waku Waku)
          // Mái tóc hồng pastel bồng bềnh + bóng khối
          frRect(ctx, -26, -36, 52, 48, 9, "#ffb6c5");
          frRect(ctx, -20, -16, 40, 28, 6, "#ffff94"); // Mặt trắng hồng
          
          // Cặp sừng trang sức đen viền vàng Chimera
          fTri(ctx, -26, -30, -17, -50, -8, -30, "#000000");
          dTri(ctx, -26, -30, -17, -50, -8, -30, "#ffff00");
          fTri(ctx, 8, -30, 17, -50, 26, -30, "#000000");
          dTri(ctx, 8, -30, 17, -50, 26, -30, "#ffff00");
          
          // Mắt Waku Waku long lanh (Xanh lục bảo + đốm sáng 4 cánh sao)
          frRect(ctx, -15, -9, 10, 13, 3, "#009900");
          frRect(ctx, 5, -9, 10, 13, 3, "#009900");
          fRect(ctx, -13, -7, 6, 8, "#00ff00");
          fRect(ctx, 7, -7, 6, 8, "#00ff00");
          fRect(ctx, -13, -7, 3, 3, "#ffffff"); // Star shine
          fRect(ctx, 7, -7, 3, 3, "#ffffff");
          fCirc(ctx, -11, 6, 3, "#ff7573"); // Má hồng to
          fCirc(ctx, 11, 6, 3, "#ff7573");
          
          // Hạt sao lấp lánh Waku Waku bay quanh
          dPixel(ctx, 30 + (Math.cos(angle * 3) * 4), -24, "#ffee00");
          dPixel(ctx, -30 + (Math.sin(angle * 3) * 4), -20, "#ffee00");
          break;
        }

        case 2: {
          // Raiden Shogun (Tia Sét Vĩnh Cửu)
          // Mái tóc tím thắt bím dài + Trâm cài Kanzashi hoa vàng
          frRect(ctx, -24, -32, 48, 40, 7, "#4a0083");
          frRect(ctx, -20, -28, 40, 36, 6, "#6a20ac");
          frRect(ctx, -16, -14, 32, 28, 6, "#ffff94");
          dLine(ctx, 10, -34, 22, -42, "#ffee00");
          
          // Vòng sấm sét 3-Tomoe (Chakra Desiderata) sau lưng
          {
          let ringR = 40 + (breath * 6);
          dCirc(ctx, 0, 0, ringR, "#9c00ff");
          dCirc(ctx, 0, 0, ringR + 1, "#deffff");
          for (let i = 0; i < 3; i++) {
          let a = i * 2.094 + angle * 1.5;
          let tx = (Math.cos(a) * ringR);
          let ty = (Math.sin(a) * ringR);
          fCirc(ctx, tx, ty, 3, "#e6ffff");
          }
          }
          
          // Mắt Lôi Thần tím sáng
          fRect(ctx, -12, -6, 7, 9, "#8359ff");
          fRect(ctx, 5, -6, 7, 9, "#8359ff");
          dPixel(ctx, -10, -5, "#ffffff");
          dPixel(ctx, 7, -5, "#ffffff");
          break;
        }

        case 3: {
          // Furina Fontaine (Sân Khấu Thủy Thần)
          // Mũ quý tộc chóp cao xanh biển + viền ruy băng trắng
          frRect(ctx, -24, -44, 48, 28, 6, "#004083");
          fRect(ctx, -30, -18, 60, 6, "#ffffff"); // Vành nón
          frRect(ctx, -20, -14, 40, 34, 6, "#dedede"); // Tóc xanh nhạt gợn sóng
          frRect(ctx, -15, -10, 30, 24, 5, "#ffff94"); // Mặt
          
          // Mắt Thủy Thần dị sắc (Xanh lam & xanh dương đậm)
          fRect(ctx, -11, -5, 7, 8, "#00beff");
          fRect(ctx, 4, -5, 7, 8, "#0059ff");
          dPixel(ctx, -9, -4, "#ffffff");
          dPixel(ctx, 6, -4, "#ffffff");
          
          // Bong bóng nước nổi lững lờ
          for (let i = 0; i < 4; i++) {
          let bx = -28 + i * 18 + (Math.sin(angle * 2 + i) * 6);
          let by = -20 + (Math.cos(angle * 2 + i) * 12);
          dCirc(ctx, bx, by, 4, "#00ffff");
          dPixel(ctx, bx - 1, by - 1, "#ffffff");
          }
          break;
        }

        case 4: {
          // Nahida Dendro (Thảo Thần)
          // Mái tóc trắng xanh mầm cây + lá sen
          frRect(ctx, -24, -34, 48, 38, 7, "#f6f6f6");
          frRect(ctx, -28, -24, 12, 22, 4, "#00be00"); // Lọn tóc xanh
          frRect(ctx, -16, -12, 32, 26, 5, "#ffff94");
          
          // Đôi mắt Thảo thần màu ngọc bích lục bảo
          fRect(ctx, -12, -5, 8, 9, "#00ff00");
          fRect(ctx, 4, -5, 8, 9, "#00ff00");
          dPixel(ctx, -10, -4, "#ffffff");
          dPixel(ctx, 6, -4, "#ffffff");
          
          // Bàn phím số Ma trận Thảo (Sanctuary Grid)
          dRect(ctx, -24, 22, 48, 6, "#00ff00");
          for (let x = -20; x <= 20; x += 10) dLine(ctx, x, 22, x, 22 + 6, "#a4ff00");
          break;
        }

        case 5: {
          // Xiao Vigilant Yaksha (Dạ Xoa Giáng Ma)
          // Tóc xanh lục đậm phong lôi + Vệt highlight xanh ngọc
          frRect(ctx, -24, -34, 48, 38, 6, "#005052");
          frRect(ctx, -16, -14, 32, 26, 5, "#ffff94");
          
          // Mắt vàng hổ phách sắc bén + viền đỏ đuôi mắt
          fRect(ctx, -12, -6, 8, 7, "#ffb600");
          fRect(ctx, 4, -6, 8, 7, "#ffb600");
          dLine(ctx, -14, -7, -14 + 10, -7, "#ff0000"); // Eyeliner đỏ
          dLine(ctx, 4, -7, 4 + 10, -7, "#ff0000");
          
          // Mặt nạ Dạ Xoa Dạ Xoa bên hông
          frRect(ctx, 16, -26, 18, 22, 4, "#006dac");
          dPixel(ctx, 20, -20, "#ff0000");
          dPixel(ctx, 28, -20, "#ff0000");
          
          // Hòa Diệp Thương (Primordial Jade Spear) phóng tia sáng
          dLine(ctx, -36, 36, -22, -42, "#00ffff");
          dLine(ctx, -35, 36, -21, -42, "#ffffff");
          break;
        }

        case 6: {
          // Gojo Satoru (Vô Hạ Hạn)
          // Mái tóc trắng nhọn dựng đặc trưng
          frRect(ctx, -24, -40, 48, 34, 6, "#ffffff");
          drRect(ctx, -24, -40, 48, 34, 6, "#cdcacd");
          frRect(ctx, -16, -14, 32, 26, 5, "#ffff94");
          
          // Bịt mắt đen huyền thoại
          fRect(ctx, -18, -12, 36, 12, "#101410");
          dLine(ctx, -18, -6, -18 + 36, -6, "#313031");
          
          // Quả cầu Hách (Đỏ) và Xanh (Lam) Vô Hạ Hạn xoay tròn
          {
          let ox = (Math.cos(angle * 3.0) * 32.0);
          let oy = (Math.sin(angle * 3.0) * 16.0);
          fCirc(ctx, -ox, oy, 9, "#0044ff");
          fCirc(ctx, -ox, oy, 5, "#7bffff");
          fCirc(ctx, ox, -oy, 9, "#ff0000");
          fCirc(ctx, ox, -oy, 5, "#ff9573");
          }
          break;
        }

        case 7: {
          // Nezuko Kamado (Huyết Quỷ Thuật)
          // Mái tóc đen dài uốn lượn + Ngọn tóc chuyển màu cam lửa
          frRect(ctx, -24, -36, 48, 44, 6, "#101410");
          fRect(ctx, -24, 4, 14, 24, "#ff4c00"); // Đuôi tóc cam
          fRect(ctx, 10, 4, 14, 24, "#ff4c00");
          frRect(ctx, -16, -14, 32, 26, 5, "#ffff94");
          
          // Mắt hồng ngọc lấp lánh
          fRect(ctx, -12, -6, 8, 8, "#ff507b");
          fRect(ctx, 4, -6, 8, 8, "#ff507b");
          
          // Ống tre ngậm miệng + Dây buộc đỏ
          frRect(ctx, -14, 3, 28, 10, 3, "#00be00");
          drRect(ctx, -14, 3, 28, 10, 3, "#006d00");
          dLine(ctx, -4, 3, -4, 3 + 10, "#006d00");
          dLine(ctx, 4, 3, 4, 3 + 10, "#006d00");
          dLine(ctx, -18, 8, -18 + 4, 8, "#ff0000");
          dLine(ctx, 14, 8, 14 + 4, 8, "#ff0000");
          break;
        }

        case 8: {
          // Tanjiro Kamado (Hỏa Thần Điệu Múa)
          // Tóc nâu đỏ vuốt ngược + Vết sẹo Hỏa Thần trên trán
          frRect(ctx, -24, -36, 48, 34, 6, "#623010");
          frRect(ctx, -16, -14, 32, 26, 5, "#ffff94");
          fRect(ctx, -14, -12, 6, 6, "#a40000");
          
          // Hoa tai Hanafuda đung đưa
          fRect(ctx, -20, -2, 4, 12, "#ffffff");
          dPixel(ctx, -18, 4, "#ff0000");
          
          // Vòng Rồng Lửa Hinokami Kagura cuốn quanh người
          {
          let arcR = 42 + (breath * 4);
          dCirc(ctx, 0, 0, arcR, "#ff4c00");
          dCirc(ctx, 0, 0, arcR + 1, "#ffee00");
          dCirc(ctx, 0, 0, arcR + 2, "#ffffff");
          dPixel(ctx, (Math.cos(angle * 5) * arcR), (Math.sin(angle * 5) * arcR), "#ffee00");
          }
          break;
        }

        case 9: {
          // Roronoa Zoro (Tam Kiếm Phái)
          // Tóc xanh rêu + Băng đeo tay xanh đen
          frRect(ctx, -22, -34, 44, 30, 6, "#009900");
          frRect(ctx, -16, -10, 32, 26, 5, "#ffff94");
          dLine(ctx, -10, -8, -10, -1, "#000000");
          
          // 3 Thanh Kiếm (Wado Ichimonji, Sandai Kitetsu, Enma)
          dLine(ctx, -40, -34, 40, 34, "#00ff00");
          dLine(ctx, -39, -34, 41, 34, "#ffffff");
          dLine(ctx, -40, 34, 40, -34, "#00ff00");
          dLine(ctx, -39, 34, 41, -34, "#ffffff");
          dLine(ctx, -30, 4, -30 + 60, 4, "#ffee00");
          break;
        }

        case 10: {
          // Luffy Gear 5 Nika (Thần Mặt Trời)
          // Tóc mây trắng cuồn cuộn bay phấp phới
          frRect(ctx, -28, -42, 56, 42, 10, "#ffffff");
          drRect(ctx, -28, -42, 56, 42, 10, "#dedede");
          frRect(ctx, -16, -10, 32, 26, 5, "#ffff94");
          
          // Mắt xoắn ốc vui tươi đặc trưng Nika
          dCirc(ctx, -8, -3, 5, "#ff4c00");
          dCirc(ctx, 8, -3, 5, "#ff4c00");
          fCirc(ctx, -8, -3, 2, "#000000");
          fCirc(ctx, 8, -3, 2, "#000000");
          
          // Dải mây vũ y Hagoromo lượn quanh cổ
          dArc(ctx, 0, 16, 26, 28, 40, 140, "#ffffff");
          dArc(ctx, 0, 16, 28, 30, 40, 140, "#dedede");
          break;
        }

        case 11: {
          // Naruto Sage Mode (Hiền Nhân Cửu Vĩ)
          // Mái tóc vàng nhọn + Băng trán Konoha lá bạc
          frRect(ctx, -24, -40, 48, 34, 6, "#ffee00");
          fRect(ctx, -18, -18, 36, 8, "#7b7d7b");
          dPixel(ctx, 0, -14, "#ffffff");
          frRect(ctx, -16, -10, 32, 26, 5, "#ffff94");
          
          // Mắt Hiền Nhân cam + Đồng tử cóc ngang
          fRect(ctx, -15, -6, 10, 9, "#ff4c00");
          fRect(ctx, 5, -6, 10, 9, "#ff4c00");
          dLine(ctx, -13, -2, -13 + 6, -2, "#000000");
          dLine(ctx, 7, -2, 7 + 6, -2, "#000000");
          
          // Quả cầu Rasengan xoáy tốc độ cao
          {
          let rx = 30;
          let ry = 14;
          fCirc(ctx, rx, ry, 12, "#00ffff");
          dCirc(ctx, rx, ry, 13, "#ffffff");
          for (let i = 0; i < 4; i++) {
          let a = angle * 6.0 + i * 1.57;
          dPixel(ctx, rx + (Math.cos(a) * 10), ry + (Math.sin(a) * 10), "#ffffff");
          }
          }
          break;
        }

        case 12: {
          // Thanh Kiếm Thánh Excalibur
          // Lưỡi kiếm 3D Bevel: Mặt sáng Vàng Bạch Kim, mặt tối Vàng Đồng
          fTri(ctx, 0, -58, -7, 20, 0, 20, "#ffffff");
          fTri(ctx, 0, -58, 0, 20, 7, 20, "#cdca00");
          dLine(ctx, 0, -56, 0, -56 + 74, "#00ffff");
          
          // Chuôi kiếm cánh chim mạ vàng hoàng gia
          frRect(ctx, -20, 20, 40, 10, 3, "#ffff00");
          fCirc(ctx, 0, 25, 4, "#0000ff");
          fRect(ctx, -4, 30, 8, 22, "#4a4c4a");
          fCirc(ctx, 0, 54, 6, "#ffff00");
          break;
        }

        case 13: {
          // Huyết Kiếm Muramasa
          // Lưỡi katana cong vát 3D Huyết Nguyệt
          fTri(ctx, -2, -56, -6, 20, 0, 20, "#ff0000");
          fTri(ctx, -2, -56, 0, 20, 5, 20, "#830000");
          dLine(ctx, 0, -50, 0, 18, "#ff8100");
          
          // Tsuba tròn vàng + Cán kiếm quấn dây đen Ito
          fCirc(ctx, 0, 22, 10, "#c5c2c5");
          fRect(ctx, -4, 24, 8, 26, "#000000");
          for (let y = 26; y <= 46; y += 5) dLine(ctx, -3, y, -3 + 6, y, "#ff4c00");
          
          // Vệt chém huyết ảnh xoay quanh lưỡi kiếm
          dArc(ctx, 0, -16, 28, 30, 200, 340, "#ff0000");
          break;
        }

        case 14: {
          // Cyberpunk Thermal Katana (3000°C Plasma)
          // Lưỡi kiếm sợi Carbon đen bóng + Cạnh nhiệt Plasma phát quang
          fRect(ctx, -5, -54, 6, 74, "#101410");
          dLine(ctx, 1, -52, 1, -52 + 70, "#00f0ff");
          dLine(ctx, 2, -50, 2, -50 + 66, "#ffa1a4");
          fRect(ctx, -14, 20, 28, 8, "#292829");
          fRect(ctx, -4, 28, 8, 24, "#181818");
          break;
        }

        case 15: {
          // Plasma Buster Cannon
          // Khẩu pháo năng lượng hạng nặng 2 nòng Isometric
          frRect(ctx, -24, -24, 48, 44, 6, "#202420");
          drRect(ctx, -24, -24, 48, 44, 6, "#4a4c4a");
          fRect(ctx, -16, -46, 12, 24, "#313031");
          fRect(ctx, 4, -46, 12, 24, "#313031");
          
          // Lõi sạc Plasma phát sáng ở tâm pháo
          fCirc(ctx, 0, -2, 14 + (breath * 4), "#00ffff");
          fCirc(ctx, 0, -2, 7, "#ffffff");
          break;
        }

        case 16: {
          // Frostmourne Rune Blade (Tử Khí Băng Giá)
          // Lưỡi kiếm runic băng khắc chữ cổ
          fTri(ctx, 0, -56, -8, 18, 0, 18, "#dedede");
          fTri(ctx, 0, -56, 0, 18, 8, 18, "#4a4c4a");
          for (let y = -36; y <= 8; y += 12) dPixel(ctx, 0, y, "#00ffff");
          
          // Đầu lâu Ram Skull ở cán kiếm
          frRect(ctx, -16, 18, 32, 14, 4, "#6a696a");
          fCirc(ctx, -6, 24, 2, "#00ffff");
          fCirc(ctx, 6, 24, 2, "#00ffff");
          fRect(ctx, -4, 32, 8, 22, "#181818");
          break;
        }

        case 17: {
          // Búa Sấm Sét Mjolnir (Asgardian Uru Metal)
          // Đầu búa Isometric đúc kim loại Uru
          frRect(ctx, -28, -38, 56, 36, 6, "#7b7d7b");
          drRect(ctx, -28, -38, 56, 36, 6, "#4a4c4a");
          dRect(ctx, -22, -32, 44, 24, "#9c999c");
          
          // Cán búa quấn dây da nâu + Vòng cổ tay
          fRect(ctx, -5, -2, 10, 44, "#8b4410");
          dCirc(ctx, 0, 44, 4, "#8b4410");
          
          // Tia sét điện quang nứt nẻ từ các góc búa
          dLine(ctx, -28, -38, -40, -52, "#00f0ff");
          dLine(ctx, 28, -38, 38, -48, "#ffffff");
          break;
        }

        case 18: {
          // Hắc Kiếm Darksaber (Mandalorian Beskar)
          // Lưỡi kiếm đen tuyền góc cạnh + Vầng hào quang trắng rung động
          fTri(ctx, 0, -58, -6, 20, 6, 20, "#000000");
          dLine(ctx, 0, -58, -6, 20, "#ffffff");
          dLine(ctx, 0, -58, 6, 20, "#ffffff");
          dLine(ctx, 0, -58, 0, 20, "#cdcacd");
          
          // Chuôi kiếm hình chữ nhật Beskar truyền thống
          fRect(ctx, -8, 20, 16, 28, "#7b7d7b");
          dRect(ctx, -8, 20, 16, 28, "#181818");
          break;
        }

        case 19: {
          // Song Đao Năng Lượng Laser (Dual Blades)
          // Hai thanh đao chéo góc chữ X tỏa hào quang Cyan & Magenta
          dLine(ctx, -38, -38, 38, 38, "#00f0ff");
          dLine(ctx, -37, -38, 39, 38, "#ffffff");
          dLine(ctx, -38, 38, 38, -38, "#ff00ff");
          dLine(ctx, -37, 38, 39, -38, "#ffffff");
          fCirc(ctx, 0, 0, 7, "#181818");
          break;
        }

        case 20: {
          // Lưỡi Hái Tử Thần Reaper (Soul Harvest)
          // Cán dài kim loại hắc ám
          dLine(ctx, 0, -54, 0, 50, "#313031");
          dLine(ctx, 1, -54, 1, 50, "#525052");
          
          // Lưỡi hái cong hình trăng khuyết tím phát sáng
          dArc(ctx, -4, -16, 36, 42, 220, 360, "#9c00ff");
          dArc(ctx, -4, -16, 38, 40, 220, 360, "#ffffff");
          fCirc(ctx, -32, -32, 4, "#00ffff");
          break;
        }

        case 21: {
          // Laser Railgun Sniper (Ngắm Bắn Chính Xác)
          // Thân súng bắn tỉa công nghệ cao + Vòng gia tốc từ trường
          fRect(ctx, -34, -14, 68, 20, "#181818");
          dRect(ctx, -34, -14, 68, 20, "#00f0ff");
          for (let x = -24; x <= 24; x += 16) {
          dCirc(ctx, x, -4, 9, "#00f0ff");
          }
          // Tâm ngắm hồng ngoại Laser Scope
          dCirc(ctx, 28, -4, 5, "#ff0000");
          dLine(ctx, 20, -4, 20 + 16, -4, "#ff0000");
          break;
        }

        case 22: {
          // Trái Tim Pha Lê Diamond (8 Mặt Cắt Phản Chiếu)
          {
          let s = 34 + (breath * 8.0);
          fCirc(ctx, -s/2, -s/3, s/2, "#ff0000");
          fCirc(ctx, s/2, -s/3, s/2, "#ff0000");
          fTri(ctx, -s + 4, -s/4, s - 4, -s/4, 0, s, "#ff0000");
          
          dLine(ctx, 0, -s/3, -s/2, s/3, "#ff9573");
          dLine(ctx, 0, -s/3, s/2, s/3, "#ff9573");
          dLine(ctx, 0, -s/3, 0, s, "#ffffff");
          dLine(ctx, -s/2, -s/3, 0, -s/3, "#ffffff");
          dLine(ctx, s/2, -s/3, 0, -s/3, "#ffffff");
          dPixel(ctx, -s/2 - 2, -s/3 - 4, "#ffffff");
          }
          break;
        }

        case 23: {
          // Song Tâm Lồng Nhau (Dual Hearts Interlocked)
          fCirc(ctx, -16, -8, 14, "#00ffff");
          fTri(ctx, -30, -6, -2, -6, -16, 18, "#00ffff");
          fCirc(ctx, 16, 4, 14, "#ff00ff");
          fTri(ctx, 2, 6, 30, 6, 16, 30, "#ff00ff");
          dPixel(ctx, 0, 2, "#ffffff");
          break;
        }

        case 24: {
          // Nhịp Tim Điện Tâm Đồ ECG (Live Heartbeat Wave)
          for (let y = -24; y <= 24; y += 12) dLine(ctx, -42, y, -42 + 84, y, "#003000");
          dLine(ctx, -42, 0, -18, 0, "#00ff00");
          dLine(ctx, -18, 0, -10, -30, "#00ff00");
          dLine(ctx, -10, -30, 0, 32, "#ffffff");
          dLine(ctx, 0, 32, 10, -16, "#00ff00");
          dLine(ctx, 10, -16, 42, 0, "#00ff00");
          fCirc(ctx, 0, 32, 3, "#ff0000");
          break;
        }

        case 25: {
          // Thư Tình Có Cánh (Winged Love Letter)
          frRect(ctx, -24, -14, 48, 30, 4, "#ffff94");
          drRect(ctx, -24, -14, 48, 30, 4, "#cdcacd");
          dLine(ctx, -24, -14, 0, 2, "#cdcacd");
          dLine(ctx, 24, -14, 0, 2, "#cdcacd");
          fCirc(ctx, 0, 2, 5, "#ff0000");
          
          {
          let wy = (Math.sin(angle * 4.0) * 6.0);
          dArc(ctx, -28, -8 + wy, 16, 20, 160, 320, "#ffffff");
          dArc(ctx, 28, -8 + wy, 16, 20, 220, 380, "#ffffff");
          }
          break;
        }

        case 26: {
          // Biểu Tượng Vô Cực Infinity (Endless Love)
          dCirc(ctx, -20, 0, 20, "#00ffff");
          dCirc(ctx, 20, 0, 20, "#ff00ff");
          dCirc(ctx, -20, 0, 18, "#ffffff");
          dCirc(ctx, 20, 0, 18, "#ffffff");
          {
          let lx = (Math.cos(angle * 2.0) * 20.0) * ((Math.sin(angle * 2.0) > 0) ? 1 : -1);
          let ly = (Math.sin(angle * 2.0) * 16.0);
          fCirc(ctx, lx, ly, 3, "#ffee00");
          }
          break;
        }

        case 27: {
          // Hoa Hồng Pha Lê (Crystal Rose)
          fCirc(ctx, 0, -12, 18, "#ff0000");
          dCirc(ctx, 0, -12, 14, "#ff8100");
          fCirc(ctx, -8, 2, 10, "#de0000");
          fCirc(ctx, 8, 2, 10, "#de0000");
          dPixel(ctx, -4, -16, "#ffffff");
          
          fRect(ctx, -3, 12, 6, 32, "#00be00");
          fTri(ctx, -3, 20, -14, 16, -3, 26, "#00ff00");
          fTri(ctx, 3, 26, 14, 22, 3, 32, "#00ff00");
          break;
        }

        case 28: {
          // Mũi Tên Thần Cupid (Star Trail Arrow)
          fCirc(ctx, -10, -6, 12, "#ff00ff");
          fCirc(ctx, 10, -6, 12, "#ff00ff");
          fTri(ctx, -22, -4, 22, -4, 0, 20, "#ff00ff");
          
          dLine(ctx, -38, -38, 38, 38, "#ffee00");
          dLine(ctx, -37, -38, 39, 38, "#ffffff");
          fTri(ctx, 38, 38, 28, 36, 36, 28, "#ffee00");
          break;
        }

        case 29: {
          // Chòm Sao Đôi Tình Nhân (Lovers Constellation)
          {
          const pts = {{-30, -20}, {-10, -32}, {16, -26}, {32, -8}, {10, 14}, {-18, 18}};
          for (let i = 0; i < 5; i++) {
          dLine(ctx, pts[i][0], pts[i][1], pts[i+1][0], pts[i+1][1], "#4a4c4a");
          }
          dLine(ctx, pts[5][0], pts[5][1], pts[0][0], pts[0][1], "#4a4c4a");
          for (let i = 0; i < 6; i++) {
          fCirc(ctx, pts[i][0], pts[i][1], 3, "#ffee00");
          dPixel(ctx, pts[i][0], pts[i][1], "#ffffff");
          }
          }
          break;
        }

        case 30: {
          // Đống Lửa Trại Ấm Áp (Cozy Campfire)
          fRect(ctx, -26, 18, 52, 10, "#8b4410");
          fRect(ctx, -20, 22, 40, 8, "#522800");
          {
          let fy = (Math.sin(angle * 6.0) * 4.0);
          fTri(ctx, -20, 18, 20, 18, 0, -32 + fy, "#ff0000");
          fTri(ctx, -14, 18, 14, 18, 0, -22 + fy, "#ff4c00");
          fTri(ctx, -8, 18, 8, 18, 0, -12 + fy, "#ffee00");
          dPixel(ctx, -4, -38 + fy, "#ffee00");
          dPixel(ctx, 8, -44 + fy, "#ff4c00");
          }
          break;
        }

        case 31: {
          // Bình Thuốc Tình Yêu Magic (Love Potion)
          fCirc(ctx, 0, 6, 22, "#292829");
          fCirc(ctx, 0, 6, 18, "#ff00ff");
          fRect(ctx, -8, -24, 16, 12, "#292829");
          fRect(ctx, -6, -30, 12, 8, "#8b4410");
          fCirc(ctx, -4, 2 + (Math.sin(angle * 3) * 6), 3, "#ffffff");
          fCirc(ctx, 6, -8 + (Math.cos(angle * 3) * 6), 2, "#ffffff");
          break;
        }

        case 32: {
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
        }

        case 35: {
          // Thỏ Ngọc Cung Trăng (Moon Rabbit)
          fCirc(ctx, 12, -10, 26, "#ffee00");
          fCirc(ctx, 6, -14, 24, "#000000");
          frRect(ctx, -20, -10, 32, 28, 7, "#ffffff");
          frRect(ctx, -16, -38, 8, 30, 4, "#ffffff");
          frRect(ctx, -4, -38, 8, 30, 4, "#ffffff");
          fRect(ctx, -14, -34, 4, 22, "#ff9573");
          fRect(ctx, -2, -34, 4, 22, "#ff9573");
          fCirc(ctx, -12, -2, 2, "#ff0000");
          break;
        }

        case 36: {
          // Pixel Corgi Tung Tăng (Heart Butt Corgi)
          fCirc(ctx, -14, 0, 18, "#ffb683");
          fCirc(ctx, 14, 0, 18, "#ffb683");
          fCirc(ctx, -8, 4, 10, "#ffffff");
          fCirc(ctx, 8, 4, 10, "#ffffff");
          fCirc(ctx, 0, -8 + (Math.sin(angle * 10) * 3), 4, "#ffb683");
          fCirc(ctx, 0, -22, 5, "#ff0000");
          break;
        }

        case 37: {
          // Ma Nhỏ Cute Boo Spook
          {
          let my = (Math.sin(angle * 3) * 6);
          frRect(ctx, -20, my - 24, 40, 42, 10, "#ffffff");
          for (let x = -16; x <= 16; x += 8) {
          fCirc(ctx, x, my + 18, 4, "#ffffff");
          }
          fCirc(ctx, -8, my - 6, 4, "#000000");
          fCirc(ctx, 8, my - 6, 4, "#000000");
          dPixel(ctx, -7, my - 7, "#ffffff");
          dPixel(ctx, 9, my - 7, "#ffffff");
          fCirc(ctx, -12, my, 3, "#ff9573");
          fCirc(ctx, 12, my, 3, "#ff9573");
          }
          break;
        }

        case 38: {
          // Rồng Con Thở Lửa (Baby Dragon)
          frRect(ctx, -20, -16, 40, 36, 8, "#00be00");
          fTri(ctx, -18, -16, -12, -30, -6, -16, "#00ff00");
          fTri(ctx, 6, -16, 12, -30, 18, -16, "#00ff00");
          {
          let fx = 22 + (Math.sin(angle * 6) * 4);
          fCirc(ctx, fx, -4, 6, "#ff4c00");
          fCirc(ctx, fx + 6, -4, 4, "#ffee00");
          }
          break;
        }

        case 39: {
          // Chuột Hamster Phi Hành Gia (Space Hamster)
          dCirc(ctx, 0, 0, 30, "#00ffff");
          fCirc(ctx, 0, 2, 22, "#eeb200");
          fCirc(ctx, -16, 8, 9, "#ff5000");
          fCirc(ctx, 16, 8, 9, "#ff5000");
          fCirc(ctx, -7, 0, 3, "#000000");
          fCirc(ctx, 7, 0, 3, "#000000");
          break;
        }

        case 40: {
          // Gấu Trúc Đỏ Cyber Red Panda
          frRect(ctx, -24, -20, 48, 38, 8, "#ff4c00");
          frRect(ctx, -16, -4, 32, 20, 6, "#ffffff");
          fCirc(ctx, -22, -24, 8, "#831000");
          fCirc(ctx, 22, -24, 8, "#831000");
          frRect(ctx, -26, 12, 52, 12, 4, "#8b4410");
          for (let x = -20; x <= 20; x += 12) dLine(ctx, x, 12, x, 12 + 12, "#ff4c00");
          break;
        }

        case 41: {
          // Cáo Sao Say Giấc Star Fox
          fCirc(ctx, 0, 0, 26, "#ff4c00");
          fCirc(ctx, 10, 0, 18, "#8b4410");
          dArc(ctx, -10, -2, 6, 4, 0, 180, "#000000");
          dArc(ctx, 6, -2, 6, 4, 0, 180, "#000000");
          fCirc(ctx, 0, -32, 4, "#ffee00");
          break;
        }

        case 42: {
          // Lò Phản Ứng Arc Reactor 3000 (Iron Man)
          dCirc(ctx, 0, 0, 34, "#7b7d7b");
          dCirc(ctx, 0, 0, 32, "#00f0ff");
          dCirc(ctx, 0, 0, 22, "#00ffff");
          for (let i = 0; i < 10; i++) {
          let a = i * 0.628 + angle;
          let bx = (Math.cos(a) * 27.0);
          let by = (Math.sin(a) * 27.0);
          fCirc(ctx, bx, by, 3, "#8b4410");
          }
          fCirc(ctx, 0, 0, 12 + (breath * 3), "#ffffff");
          dCirc(ctx, 0, 0, 14 + (breath * 3), "#00f0ff");
          break;
        }

        case 43: {
          // Cyberpunk Radar HUD (Quét Mục Tiêu)
          dCirc(ctx, 0, 0, 36, "#00ff00");
          dCirc(ctx, 0, 0, 24, "#00be00");
          dCirc(ctx, 0, 0, 12, "#007d00");
          dLine(ctx, -36, 0, -36 + 72, 0, "#007d00");
          dLine(ctx, 0, -36, 0, -36 + 72, "#007d00");
          {
          let rx = (Math.cos(angle * 2.5) * 36.0);
          let ry = (Math.sin(angle * 2.5) * 36.0);
          dLine(ctx, 0, 0, rx, ry, "#ffffff");
          fCirc(ctx, 14, -16, 3, "#ff0000");
          dCirc(ctx, 14, -16, 6, "#ff0000");
          }
          break;
        }

        case 44: {
          // Máy Game Boy Cổ Điển (Retro Handheld)
          frRect(ctx, -26, -42, 52, 84, 8, "#cdcacd");
          drRect(ctx, -26, -42, 52, 84, 8, "#7b7d7b");
          fRect(ctx, -20, -34, 40, 36, "#83ca00");
          fRect(ctx, -16, -30, 32, 28, "#9cda00");
          dRect(ctx, -10, -20, 20, 10, "#316900");
          fRect(ctx, -18, 14, 14, 5, "#000000");
          fRect(ctx, -14, 10, 5, 14, "#000000");
          fCirc(ctx, 10, 20, 4, "#830000");
          fCirc(ctx, 18, 14, 4, "#830000");
          break;
        }

        case 45: {
          // Bình Máu Pixel 8-Bit Zelda (Health Potion)
          fRect(ctx, -18, -12, 36, 44, "#000000");
          fRect(ctx, -14, -8, 28, 38, "#ff0000");
          fRect(ctx, -8, -24, 16, 12, "#000000");
          fRect(ctx, -4, -22, 8, 10, "#cdcacd");
          dLine(ctx, -10, -4, -10, -4 + 28, "#ffffff");
          dLine(ctx, -8, -4, -8, -4 + 28, "#ffffff");
          break;
        }

        case 46: {
          // Băng Cát-sét Synthwave (80s Neon Tape)
          frRect(ctx, -36, -22, 72, 44, 4, "#181818");
          drRect(ctx, -36, -22, 72, 44, 4, "#ff00ff");
          fRect(ctx, -28, -16, 56, 24, "#ff4c00");
          fCirc(ctx, -14, -4, 7, "#ffffff");
          fCirc(ctx, 14, -4, 7, "#ffffff");
          fCirc(ctx, -14, -4, 3, "#000000");
          fCirc(ctx, 14, -4, 3, "#000000");
          break;
        }

        case 47: {
          // Đầu Lâu Glitch Hologram (Cyber Skull)
          dCirc(ctx, 0, -10, 22, "#00f0ff");
          fRect(ctx, -12, 8, 24, 14, "#000000");
          dRect(ctx, -12, 8, 24, 14, "#00f0ff");
          fCirc(ctx, -8, -8, 5, "#00f0ff");
          fCirc(ctx, 8, -8, 5, "#00f0ff");
          for (let y = -28; y <= 28; y += 8) {
          let offset = (Math.sin(angle * 8 + y) * 4);
          dLine(ctx, -30 + offset, y, -30 + offset + 60, y, "#00ffff");
          }
          break;
        }

        case 48: {
          // Cơn Mưa Ký Tự Matrix Code Rain
          for (let col = 0; col < 7; col++) {
          let px = -36 + col * 12;
          for (let row = 0; row < 6; row++) {
          let py = -36 + ((row * 14 + (angle * 20.0 + col * 15)) % 80);
          uint16_t clr = (row == 5) ? TFT_WHITE : (row > 3 ? 0x07E0 : 0x03E0);
          dRect(ctx, px, py, 4, 6, "clr");
          }
          }
          break;
        }

        case 49: {
          // Lõi Lượng Tử Quantum Core (3 Trục Gyro)
          default:
          dCirc(ctx, 0, 0, 34, "#9c00ff");
          dEllip(ctx, 0, 0, 30, 16 + (Math.sin(angle * 2) * 10), "#00ffff");
          dEllip(ctx, 0, 0, 16 + (Math.cos(angle * 2) * 10), 30, "#ffee00");
          fCirc(ctx, 0, 0, 8 + (breath * 4), "#ffffff");
          dCirc(ctx, 0, 0, 10 + (breath * 4), "#ff00ff");
          break;
        }
      }
      ctx.restore();
    }

    function renderParallaxBackground(ctx, id, t) {
      const cat = Math.floor(id / 10);
      if (cat === 0) {
        // Anime: Trăng vàng khuyết + cánh hoa đào rơi
        ctx.fillStyle = '#ffe000';
        ctx.beginPath(); ctx.arc(142, 42, 14, 0, Math.PI * 2); ctx.fill();
        ctx.fillStyle = '#000000';
        ctx.beginPath(); ctx.arc(136, 38, 12, 0, Math.PI * 2); ctx.fill();
        ctx.fillStyle = '#fd1480';
        for (let i = 0; i < 6; i++) {
          const px = (Math.sin(t * 0.5 + i) * 30 + 30 * i) % 172;
          const py = (t * 25 + i * 50) % 240;
          ctx.fillRect(px, py, 2, 2);
        }
      } else if (cat === 1) {
        // Cyber: Lưới ma trận Perspective 3D Grid dưới chân
        ctx.strokeStyle = '#00ff88';
        ctx.lineWidth = 1;
        for (let y = 195; y <= 245; y += 12) {
          ctx.beginPath(); ctx.moveTo(10, y); ctx.lineTo(162, y); ctx.stroke();
        }
        ctx.strokeStyle = '#004422';
        for (let x = 20; x <= 152; x += 30) {
          ctx.beginPath(); ctx.moveTo(86, 175); ctx.lineTo(x, 245); ctx.stroke();
        }
      } else if (cat === 2) {
        // Love: Cực quang Aurora lượn sóng
        ctx.fillStyle = 'rgba(255, 0, 85, 0.25)';
        for (let x = 10; x < 162; x += 4) {
          const waveY = 55 + Math.sin(t + x * 0.05) * 10;
          ctx.fillRect(x, waveY, 3, 18);
        }
      }
    }

        // 60 FPS MAIN LOOP (1:1 VỚI ESP32)
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
    }
    loop();
  </script>
</body>
</html>
"""

if __name__ == "__main__":
    uvicorn.run("main:app", host="0.0.0.0", port=8000, reload=False)


@app.get("/", response_class=HTMLResponse)
async def serve_index():
    catalog_json = json.dumps(ANIMATIONS, ensure_ascii=False)
    return HTMLResponse(INDEX_HTML.replace("__CATALOG_JSON__", catalog_json))
