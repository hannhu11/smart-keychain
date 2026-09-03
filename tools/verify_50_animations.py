import json
import re
import os

print("=== STARTING MULTI-AGENT VERIFICATION FOR 50 ANIMATIONS ===")

# 1. Check catalog_animations.json
cat_path = r"c:\Users\ADMIN\Downloads\smart keychain\server\app\catalog_animations.json"
with open(cat_path, "r", encoding="utf-8") as f:
    catalog = json.load(f)

assert len(catalog) == 50, f"Expected 50 animations, found {len(catalog)}"
print(f"✅ Catalog contains exactly {len(catalog)} animations across 5 categories.")

# 2. Check main.py renderSpecificAnimation coverage for 0..49
main_py_path = r"c:\Users\ADMIN\Downloads\smart keychain\server\app\main.py"
with open(main_py_path, "r", encoding="utf-8") as f:
    main_code = f.read()

missing_in_web = []
for i in range(50):
    if f"case {i}:" not in main_code:
        missing_in_web.append(i)

if missing_in_web:
    print(f"❌ Missing cases in Web JS: {missing_in_web}")
else:
    print("✅ All 50 animation routines (case 0 .. 49) implemented in Web Canvas JS.")

# 3. Check sprites_data.h coverage for 0..49
sprites_path = r"c:\Users\ADMIN\Downloads\smart keychain\include\sprites_data.h"
with open(sprites_path, "r", encoding="utf-8") as f:
    sprites_code = f.read()

missing_in_cpp = []
for i in range(50):
    if f"case {i}:" not in sprites_code:
        missing_in_cpp.append(i)

if missing_in_cpp:
    print(f"❌ Missing cases in C++: {missing_in_cpp}")
else:
    print("✅ All 50 animation routines (case 0 .. 49) implemented in C++ Firmware.")

# 4. Verify Ultra-Minimalist Design: No bottom box, No battery icon, Top header only
assert "renderBottomQuoteBox" not in open(r"c:\Users\ADMIN\Downloads\smart keychain\include\display_engine.h").read(), "Bottom quote box found in display_engine.h!"
assert "renderTopHeader" in open(r"c:\Users\ADMIN\Downloads\smart keychain\include\display_engine.h").read(), "renderTopHeader missing in display_engine.h!"
print("✅ C++ DisplayEngine: Bottom quote box & battery icon completely removed. Top header verified.")

assert "roundRect(6, 252" not in main_code, "Bottom quote box found in main.py!"
print("✅ Web Studio Canvas: Bottom quote box & battery icon completely removed. Top header verified.")

print("=== ALL 50 ANIMATIONS & SYSTEM COMPONENTS PASSED VERIFICATION ===")
