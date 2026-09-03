---
name: image-to-rgb565-converter
description: >-
  Converts PNG, JPG, BMP, WEBP, and animated GIF files into 16-bit RGB565 arrays
  (C++ PROGMEM headers) or binary files for LittleFS/SPIFFS flash storage on ESP32
  with ST7789/LovyanGFX displays. Use when preparing sprites, boot animations,
  or pixel art frames for the Smart Keychain.
---

# Image to RGB565 / Sprite Converter Skill

This skill provides an automated workflow to process images and animated GIFs into optimal RGB565 format for the ESP32 and LovyanGFX display engine.

## Supported Formats & Workflows

1. **Static Sprites & Backgrounds (PNG / JPG / BMP)**:
   - Output as C++ Header: `const uint16_t sprite_data[] PROGMEM`
   - Output as LittleFS Binary: `data/sprite.bin`
2. **Animated GIFs**:
   - Extract individual frames, compute duration, and generate multi-frame C++ array or packed LittleFS folder (`data/<anim_name>/frame_XX.bin`).
3. **Display Compatibility**:
   - Tuned for 1.47" ST7789 IPS LCD (172x320 px).
   - Proper RGB565 16-bit color packing: `(R5 << 11) | (G6 << 5) | B5`.

---

## CLI Usage

### 1. Generate C++ PROGMEM Header (Small sprites / Fast rendering)
```bash
python .agents/skills/image-to-rgb565-converter/scripts/convert_image.py -i assets/heart.png -w 40 -ht 40 -o include/heart_sprite.h -n heart_sprite
```

### 2. Convert Animated GIF to C++ Multi-frame Array
```bash
python .agents/skills/image-to-rgb565-converter/scripts/convert_image.py -i assets/cat_walk.gif -w 172 -ht 320 -o include/cat_anim.h -n cat_walk
```

### 3. Export to LittleFS (`data/` directory for flashing)
```bash
python .agents/skills/image-to-rgb565-converter/scripts/convert_image.py -i assets/love_anim.gif -f binary -d data/love_anim
```

---

## C++ Code Snippets for LovyanGFX

### Rendering PROGMEM Header Sprite:
```cpp
#include "heart_sprite.h"

// Push sprite to Framebuffer at (x=66, y=120)
sprite.pushImage(66, 120, heart_sprite_width, heart_sprite_height, heart_sprite_data);
```

### Rendering GIF Animation from PROGMEM:
```cpp
#include "cat_anim.h"

int current_frame = 0;
void loop() {
  sprite.pushImage(0, 0, cat_walk_width, cat_walk_height, cat_walk_frames[current_frame]);
  sprite.pushSprite(0, 0); // Push framebuffer to LCD

  current_frame = (current_frame + 1) % cat_walk_frame_count;
  delay(cat_walk_frame_delay_ms);
}
```

### Rendering LittleFS Binary Sprite:
```cpp
#include <LittleFS.h>

void drawLittleFSFrame(const char* path, int x, int y, int w, int h) {
  File f = LittleFS.open(path, "r");
  if (!f) return;
  
  uint16_t line_buffer[w];
  for (int row = 0; row < h; row++) {
    f.read((uint8_t*)line_buffer, w * 2);
    sprite.pushImage(x, y + row, w, 1, line_buffer);
  }
  f.close();
}
```
