# -*- coding: utf-8 -*-
import json

with open("data/agent3_fantasy_beasts.json", "r", encoding="utf-8") as f:
    data = json.load(f)

print(f"Valid JSON! Total beasts: {len(data)}")
for b in data:
    print(f"ID {b['id']}: {b['name_vi']} | {b['name_en']}")
    print(f"  Codename: {b['codename']}")
    print(f"  Palette primary: {b['palette']['primary_hex']} ({b['palette']['rgb565_primary']})")
    print(f"  Catchlights: {len(b['eye_specs'].get('catchlight_3points', []))} points")
    print(f"  C++ snippet length: {len(b['cpp_render_snippet'])} chars")
    print(f"  JS snippet length: {len(b['js_render_snippet'])} chars")
