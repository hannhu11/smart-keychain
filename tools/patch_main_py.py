import re
import json
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from build_web import parse_sprites_data

def generate_main_py():
    with open('tools/clean_main.py', 'r', encoding='utf-8') as f:
        src = f.read()

    # 1. Update ConnectionManager
    old_cm = '''class ConnectionManager:
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

manager = ConnectionManager()'''

    new_cm = '''class ConnectionManager:
    def __init__(self):
        self.browser_connections: List[WebSocket] = []
        self.device_connections: Dict[WebSocket, dict] = {}

    async def connect_browser(self, websocket: WebSocket):
        await websocket.accept()
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
        await websocket.accept()
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

manager = ConnectionManager()'''

    src = src.replace(old_cm, new_cm)

    # 2. Update websocket_endpoint and add presence
    old_ws = '''@app.websocket("/ws/keychain")
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
        manager.disconnect(websocket)'''

    new_ws = '''@app.websocket("/ws/keychain")
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
    return {"online": is_online, "device_info": info}'''

    src = src.replace(old_ws, new_ws)

    # 3. Convert HTML from f-string to raw string with __CATALOG_JSON__ replacement
    # Change:
    # @app.get("/", response_class=HTMLResponse)
    # async def serve_index():
    #     catalog_json = json.dumps(ANIMATIONS, ensure_ascii=False)
    #     return f"""<!DOCTYPE html>
    # ...
    # </html>
    # """
    html_marker = '@app.get("/", response_class=HTMLResponse)'
    html_idx = src.find(html_marker)
    if html_idx != -1:
        f_start = src.find('return f"""', html_idx)
        if f_start != -1:
            code_before_html = src[:f_start]
            html_content = src[f_start + len('return f"""'):]
            # Replace {catalog_json} with __CATALOG_JSON__
            html_content = html_content.replace('{catalog_json}', '__CATALOG_JSON__')
            # Unescape {{ and }} to single { and }
            html_content = html_content.replace('{{', '{').replace('}}', '}')

            # 4. Transpile 50 cases from sprites_data.h
            t_cases = parse_sprites_data()
            cases_code = []
            for cid in range(50):
                if cid in t_cases:
                    cases_code.append(f"        case {cid}: {{\n{t_cases[cid]}\n          break;\n        }}")
                else:
                    cases_code.append(f"        case {cid}: break;")

            cases_joined = "\n\n".join(cases_code)

            # Replace renderSpecificAnimation in html_content
            anim_start = html_content.find('function renderSpecificAnimation(ctx, id, cx, cy, scale, t)')
            anim_end = html_content.find('function renderParallaxBackground(ctx, id, t)', anim_start)
            if anim_start != -1 and anim_end != -1:
                new_render_func = f'''// HELPER DRAWING PRIMITIVES MATCHING LOVYANGFX
    function frRect(ctx, x, y, w, h, r, color) {{
      ctx.fillStyle = color;
      ctx.beginPath();
      if (ctx.roundRect) ctx.roundRect(x, y, w, h, r);
      else ctx.rect(x, y, w, h);
      ctx.fill();
    }}
    function drRect(ctx, x, y, w, h, r, color, lw=1) {{
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.beginPath();
      if (ctx.roundRect) ctx.roundRect(x, y, w, h, r);
      else ctx.rect(x, y, w, h);
      ctx.stroke();
    }}
    function fCirc(ctx, x, y, r, color) {{
      ctx.fillStyle = color;
      ctx.beginPath();
      ctx.arc(x, y, Math.max(0.5, r), 0, Math.PI*2);
      ctx.fill();
    }}
    function dCirc(ctx, x, y, r, color, lw=1) {{
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.beginPath();
      ctx.arc(x, y, Math.max(0.5, r), 0, Math.PI*2);
      ctx.stroke();
    }}
    function fTri(ctx, x1, y1, x2, y2, x3, y3, color) {{
      ctx.fillStyle = color;
      ctx.beginPath();
      ctx.moveTo(x1, y1); ctx.lineTo(x2, y2); ctx.lineTo(x3, y3); ctx.closePath();
      ctx.fill();
    }}
    function dTri(ctx, x1, y1, x2, y2, x3, y3, color, lw=1) {{
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.beginPath();
      ctx.moveTo(x1, y1); ctx.lineTo(x2, y2); ctx.lineTo(x3, y3); ctx.closePath();
      ctx.stroke();
    }}
    function fRect(ctx, x, y, w, h, color) {{
      ctx.fillStyle = color;
      ctx.fillRect(x, y, w, h);
    }}
    function dRect(ctx, x, y, w, h, color, lw=1) {{
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.strokeRect(x, y, w, h);
    }}
    function dLine(ctx, x1, y1, x2, y2, color, lw=1) {{
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.beginPath();
      ctx.moveTo(x1, y1); ctx.lineTo(x2, y2);
      ctx.stroke();
    }}
    function dPixel(ctx, x, y, color, sz=2) {{
      ctx.fillStyle = color;
      ctx.fillRect(x - sz/2, y - sz/2, sz, sz);
    }}
    function fEllip(ctx, x, y, rx, ry, color) {{
      ctx.fillStyle = color;
      ctx.beginPath();
      ctx.ellipse(x, y, Math.max(0.5, rx), Math.max(0.5, ry), 0, 0, Math.PI*2);
      ctx.fill();
    }}
    function dEllip(ctx, x, y, rx, ry, color, lw=1) {{
      ctx.strokeStyle = color;
      ctx.lineWidth = lw;
      ctx.beginPath();
      ctx.ellipse(x, y, Math.max(0.5, rx), Math.max(0.5, ry), 0, 0, Math.PI*2);
      ctx.stroke();
    }}
    function dArc(ctx, x, y, r1, r2, sa, ea, color) {{
      ctx.strokeStyle = color;
      ctx.lineWidth = Math.max(1, r2 - r1);
      ctx.beginPath();
      ctx.arc(x, y, (r1+r2)/2, sa * Math.PI/180, ea * Math.PI/180);
      ctx.stroke();
    }}

    // 50 ANIMATIONS VECTOR/CANVAS ENGINE 1:1 LOVYANGFX
    function renderSpecificAnimation(ctx, id, cx, cy, scale, t) {{
      ctx.save();
      ctx.translate(cx, cy);
      ctx.scale(scale, scale);

      const breath = Math.sin(t * 3.5);
      const angle = t * 2.0;

      switch (id) {{
{cases_joined}
      }}
      ctx.restore();
    }}

    '''
                html_content = html_content[:anim_start] + new_render_func + html_content[anim_end:]

            # Update Header presence badge in HTML
            html_content = html_content.replace(
                '''      <div class="status-telemetry">
        <div class="pulse-dot"></div>
        <span>CLOUD SYNC: 0ms &bull; 50 THEMES READY</span>
      </div>''',
                '''      <div class="status-telemetry" id="presenceBadge" style="transition: all 0.3s ease;">
        <div class="pulse-dot" id="presenceDot"></div>
        <span id="presenceText">ĐANG KẾT NỐI SERVER...</span>
      </div>'''
            )

            # Update WebSocket message handler in JavaScript
            old_ws_onmessage = '''      ws.onmessage = (e) => {
        try {
          const msg = JSON.parse(e.data);
          if (msg.type === 'SYNC' || msg.type === 'UPDATE') {
            const d = msg.data;
            if (d.sprite_id !== undefined) selectCard(d.sprite_id, false);
            if (d.palette_id !== undefined) selectPalette(d.palette_id, false);
            if (d.brightness !== undefined) {
              document.getElementById('brSlider').value = d.brightness;
              document.getElementById('brVal').textContent = d.brightness;
            }
            if (d.quote !== undefined) {
              currentQuote = d.quote;
              document.getElementById('quoteInput').value = d.quote;
            }
          }
        } catch(err) {}
      };'''

            new_ws_onmessage = '''      function updatePresence(online, info) {
        const dot = document.getElementById('presenceDot');
        const txt = document.getElementById('presenceText');
        const badge = document.getElementById('presenceBadge');
        if (!dot || !txt || !badge) return;

        if (online) {
          dot.style.background = '#00ff88';
          dot.style.boxShadow = '0 0 10px #00ff88';
          txt.innerHTML = `🟢 KEYCHAIN ONLINE &bull; ${info && info.ip ? info.ip : '192.168.1.88'}`;
          badge.style.borderColor = 'rgba(0, 255, 136, 0.4)';
          badge.style.background = 'rgba(0, 255, 136, 0.08)';
          txt.style.color = '#00ff88';
        } else {
          dot.style.background = '#ff3366';
          dot.style.boxShadow = '0 0 10px rgba(255, 51, 102, 0.6)';
          txt.innerHTML = `🔴 KEYCHAIN OFFLINE &bull; CHỜ WI-FI`;
          badge.style.borderColor = 'rgba(255, 51, 102, 0.4)';
          badge.style.background = 'rgba(255, 51, 102, 0.08)';
          txt.style.color = '#ff6b8b';
        }
      }

      ws.onmessage = (e) => {
        try {
          const msg = JSON.parse(e.data);
          if (msg.type === 'SYNC' || msg.type === 'UPDATE') {
            const d = msg.data;
            if (d.sprite_id !== undefined) selectCard(d.sprite_id, false);
            if (d.palette_id !== undefined) selectPalette(d.palette_id, false);
            if (d.brightness !== undefined) {
              document.getElementById('brSlider').value = d.brightness;
              document.getElementById('brVal').textContent = d.brightness;
            }
            if (d.quote !== undefined) {
              currentQuote = d.quote;
              document.getElementById('quoteInput').value = d.quote;
            }
            if (msg.device_online !== undefined) {
              updatePresence(msg.device_online, msg.device_info);
            }
          }
          if (msg.type === 'DEVICE_PRESENCE') {
            updatePresence(msg.online, msg.info);
          }
        } catch(err) {}
      };'''

            html_content = html_content.replace(old_ws_onmessage, new_ws_onmessage)

            # Assemble clean final file
            final_code = code_before_html + '\nINDEX_HTML = """' + html_content
            # Add endpoint
            final_code += '''

@app.get("/", response_class=HTMLResponse)
async def serve_index():
    catalog_json = json.dumps(ANIMATIONS, ensure_ascii=False)
    return HTMLResponse(INDEX_HTML.replace("__CATALOG_JSON__", catalog_json))
'''
            with open('server/app/main.py', 'w', encoding='utf-8') as f:
                f.write(final_code)
            print("Successfully patched server/app/main.py with non-f-string HTML and 50 rich animations!")

if __name__ == '__main__':
    generate_main_py()
