import re

with open('server/app/main.py', 'r', encoding='utf-8') as f:
    content = f.read()

# 1. Update state dictionary
old_state = '''state = {
    "sprite_id": 0,
    "palette_id": 0,
    "brightness": 255,
    "quote": "Dù ở thế giới nào, anh vẫn luôn tìm thấy em."
}'''

new_state = '''state = {
    "sprite_id": 0,
    "palette_id": 0,
    "brightness": 255,
    "quote": "Dù ở thế giới nào, anh vẫn luôn tìm thấy em.",
    "text_color": "#FFB800",
    "text_size": 1,
    "scenery_id": 0
}'''

if old_state in content:
    content = content.replace(old_state, new_state)
    print("Updated state dictionary!")

# 2. Add SET_DESIGN action in websocket
old_ws_action = '''                elif action == "SET_QUOTE":
                    state["quote"] = payload.get("value", "")'''

new_ws_action = '''                elif action == "SET_QUOTE":
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
                    continue'''

if old_ws_action in content:
    content = content.replace(old_ws_action, new_ws_action)
    print("Added SET_DESIGN WebSocket action!")

# 3. Add REST endpoint /api/design
old_rest = '''@app.post("/api/qr")
async def trigger_qr():
    state["qr_mode"] = True
    await manager.broadcast({"type": "UPDATE", "data": state})
    return {"status": "ok", "qr_mode": True}'''

new_rest = '''@app.post("/api/qr")
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
    return {"status": "ok", "data": state}'''

if old_rest in content:
    content = content.replace(old_rest, new_rest)
    print("Added /api/design endpoint!")

with open('server/app/main.py', 'w', encoding='utf-8') as f:
    f.write(content)
print("Saved server/app/main.py!")
