# -*- coding: utf-8 -*-
import os
import json
from typing import List, Dict, Optional
from fastapi import FastAPI, WebSocket, WebSocketDisconnect, Form
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

state = {
    "sprite_id": 12,        # Mặc định: Thần Kiếm Tuyệt Phẩm
    "palette_id": 0,
    "brightness": 255,
    "quote": "Dù ở thế giới nào, anh vẫn luôn tìm thấy em.",
    "text_color": "#FFFFFF",
    "text_size": 1,
    "scenery_id": 5         # Mặc định: Quỹ Đạo Trái Đất 3D Siêu Chân Thực
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
                    info = {"ip": payload.get("ip", client_ip), "device": payload.get("device", "ESP32S")}
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
async def trigger_qr(qr: Optional[str] = Form(None)):
    if qr == "false":
        state["qr_mode"] = False
    elif qr == "true":
        state["qr_mode"] = True
    else:
        state["qr_mode"] = not state.get("qr_mode", False)
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "qr_mode": state["qr_mode"]}

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

@app.get("/", response_class=HTMLResponse)
async def serve_index():
    index_path = os.path.join(os.path.dirname(__file__), "index.html")
    with open(index_path, "r", encoding="utf-8") as f:
        html_data = f.read()
    catalog_json = json.dumps(ANIMATIONS, ensure_ascii=False)
    return HTMLResponse(
        html_data.replace("__CATALOG_JSON__", catalog_json),
        headers={"Cache-Control": "no-cache, no-store, must-revalidate", "Pragma": "no-cache", "Expires": "0"}
    )

if __name__ == "__main__":
    uvicorn.run("main:app", host="0.0.0.0", port=8000, reload=False)
