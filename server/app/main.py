# -*- coding: utf-8 -*-
import os
import json
import time
import asyncio
from typing import List, Dict, Optional
from fastapi import FastAPI, WebSocket, WebSocketDisconnect, Form, Body
from fastapi.responses import HTMLResponse, JSONResponse
import uvicorn

app = FastAPI(title="Smart Keychain — 50 Master Animations Studio")

CATALOG_PATH = os.path.join(os.path.dirname(__file__), "catalog_50_master.json")
if not os.path.exists(CATALOG_PATH):
    CATALOG_PATH = os.path.join(os.path.dirname(__file__), "..", "..", "data", "catalog_50_master.json")

try:
    with open(CATALOG_PATH, "r", encoding="utf-8") as f:
        ANIMATIONS = json.load(f)
except Exception:
    ANIMATIONS = []

EN_QUOTES_PATH = os.path.join(os.path.dirname(__file__), "motivational_quotes_en.json")
if not os.path.exists(EN_QUOTES_PATH):
    EN_QUOTES_PATH = os.path.join(os.path.dirname(__file__), "..", "..", "data", "motivational_quotes_en.json")

try:
    with open(EN_QUOTES_PATH, "r", encoding="utf-8") as f:
        EN_QUOTES = json.load(f)
except Exception:
    EN_QUOTES = []

state = {
    "sprite_id": 1,
    "palette_id": 0,
    "brightness": 255,
    "quote": "Stay hungry, stay foolish.",
    "text_color": "#FFFFFF",
    "text_size": 1,
    "scenery_id": 2,
    "qr_mode": False,
    "sprite_scale": 1.4,          # 140% Mũm mĩm to rõ
    "typewriter_speed": 65,       # ms mỗi ký tự
    "hold_time": 4000,            # 4s dừng đọc
    "freeze_text": False,         # True = Dừng sau khi gõ xong
    "auto_quote_cycle": True,     # Bật tự động đổi quotes 2 phút
    "quote_cycle_interval": 120,  # 120 giây = 2 phút
    "quote_index": 0
}

state["_last_quote_time"] = time.time()

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
        for ws in self.device_connections:
            try:
                await ws.send_text(msg_str)
            except Exception:
                pass

manager = ConnectionManager()

async def quote_rotator_task():
    while True:
        await asyncio.sleep(2)
        if state.get("auto_quote_cycle", True) and EN_QUOTES and not state.get("freeze_text", False):
            now = time.time()
            interval = state.get("quote_cycle_interval", 120)
            if now - state.get("_last_quote_time", 0) >= interval:
                state["_last_quote_time"] = now
                next_idx = (state.get("quote_index", 0) + 1) % len(EN_QUOTES)
                state["quote_index"] = next_idx
                state["quote"] = EN_QUOTES[next_idx]["quote"]
                print(f"[AUTO-ROTATE QUOTE 2-MIN] {state['quote']}")
                await manager.broadcast({"type": "UPDATE", "data": state})

@app.on_event("startup")
async def startup_event():
    asyncio.create_task(quote_rotator_task())

@app.websocket("/ws")
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
                    info = {"ip": payload.get("ip", client_ip), "device": payload.get("device", "ESP32S")}
                    manager.device_connections[websocket] = info
                    await manager.broadcast_presence()
                    await websocket.send_text(json.dumps({"type": "SYNC", "data": state}))
                    continue

                if action == "SET_SETTINGS":
                    payload_data = payload.get("data", {})
                    for k in ["sprite_scale", "typewriter_speed", "hold_time", "freeze_text",
                              "auto_quote_cycle", "quote_cycle_interval", "quote", "brightness",
                              "text_color", "text_size", "scenery_id", "sprite_id"]:
                        if k in payload_data:
                            state[k] = payload_data[k]
                    state["_last_quote_time"] = time.time()
                    await manager.broadcast({"type": "UPDATE", "data": state})
                    continue

                if action == "SET_SPRITE":
                    state["sprite_id"] = payload.get("value", 0)
                    if 0 <= state["sprite_id"] < len(ANIMATIONS):
                        state["quote"] = ANIMATIONS[state["sprite_id"]]["quote"]
                elif action == "SET_PALETTE":
                    state["palette_id"] = payload.get("value", 0)
                elif action == "SET_BRIGHTNESS":
                    state["brightness"] = payload.get("value", 255)
                elif action == "SET_TEXT":
                    state["quote"] = payload.get("value", "")
                    state["freeze_text"] = False
                    state["_last_quote_time"] = time.time()
                elif action == "SET_TEXT_COLOR":
                    state["text_color"] = payload.get("value", "#FFFFFF")
                elif action == "SET_TEXT_SIZE":
                    state["text_size"] = payload.get("value", 1)
                elif action == "SET_SCENERY":
                    state["scenery_id"] = payload.get("value", 0)
                elif action == "TOGGLE_QR":
                    state["qr_mode"] = not state.get("qr_mode", False)

                await manager.broadcast({"type": "UPDATE", "data": state})

            except json.JSONDecodeError:
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

@app.get("/api/quotes_en")
async def get_quotes_en():
    return JSONResponse(EN_QUOTES)

@app.get("/api/state")
async def get_state():
    return JSONResponse(state)

@app.post("/api/settings")
async def api_save_settings(payload: dict = Body(...)):
    for k in ["sprite_scale", "typewriter_speed", "hold_time", "freeze_text",
              "auto_quote_cycle", "quote_cycle_interval", "quote", "brightness",
              "text_color", "text_size", "scenery_id", "sprite_id"]:
        if k in payload:
            state[k] = payload[k]
    state["_last_quote_time"] = time.time()
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "data": state}

@app.post("/api/sprite")
async def set_sprite(id: int = Form(...)):
    state["sprite_id"] = id
    if 0 <= id < len(ANIMATIONS):
        state["quote"] = ANIMATIONS[id]["quote"]
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "sprite_id": id}

@app.post("/api/design")
async def api_design(
    quote: Optional[str] = Form(None),
    text_color: Optional[str] = Form(None),
    text_size: Optional[int] = Form(None),
    scenery_id: Optional[int] = Form(None),
    sprite_id: Optional[int] = Form(None),
    brightness: Optional[int] = Form(None),
    sprite_scale: Optional[float] = Form(None),
    typewriter_speed: Optional[int] = Form(None),
    hold_time: Optional[int] = Form(None),
    freeze_text: Optional[bool] = Form(None),
    auto_quote_cycle: Optional[bool] = Form(None)
):
    if quote is not None: state["quote"] = quote
    if text_color is not None: state["text_color"] = text_color
    if text_size is not None: state["text_size"] = text_size
    if scenery_id is not None: state["scenery_id"] = scenery_id
    if sprite_id is not None: state["sprite_id"] = sprite_id
    if brightness is not None: state["brightness"] = brightness
    if sprite_scale is not None: state["sprite_scale"] = sprite_scale
    if typewriter_speed is not None: state["typewriter_speed"] = typewriter_speed
    if hold_time is not None: state["hold_time"] = hold_time
    if freeze_text is not None: state["freeze_text"] = freeze_text
    if auto_quote_cycle is not None: state["auto_quote_cycle"] = auto_quote_cycle
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "data": state}

@app.get("/", response_class=HTMLResponse)
async def serve_index():
    index_path = os.path.join(os.path.dirname(__file__), "index.html")
    with open(index_path, "r", encoding="utf-8") as f:
        html_data = f.read()
    catalog_json = json.dumps(ANIMATIONS, ensure_ascii=False)
    en_quotes_json = json.dumps(EN_QUOTES, ensure_ascii=False)
    return HTMLResponse(
        html_data.replace("__CATALOG_JSON__", catalog_json).replace("__EN_QUOTES_JSON__", en_quotes_json),
        headers={"Cache-Control": "no-cache, no-store, must-revalidate", "Pragma": "no-cache", "Expires": "0"}
    )

if __name__ == "__main__":
    uvicorn.run("main:app", host="0.0.0.0", port=8000, reload=False)
