import urllib.request

url = 'https://raw.githubusercontent.com/olikraus/u8g2/master/csrc/u8g2_fonts.c'
req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
with urllib.request.urlopen(req, timeout=20) as resp:
    content = resp.read().decode('latin-1')

p1 = content.find('const uint8_t u8g2_font_unifont_t_vietnamese1')
p1_end = content.find('const uint8_t ', p1 + 50)
font1 = content[p1:p1_end].strip()
if not font1.endswith('};'):
    semi = font1.rfind('};')
    if semi != -1:
        font1 = font1[:semi+2]

font1 = font1.replace('U8G2_FONT_SECTION("u8g2_font_unifont_t_vietnamese1")', 'PROGMEM')

header = f'''#pragma once
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

{font1}

namespace fonts {{
  static const lgfx::U8g2font fontVietnamese(u8g2_font_unifont_t_vietnamese1);
}}
'''

with open('include/u8g2_vietnamese.h', 'w', encoding='utf-8') as f:
    f.write(header)

print("Saved exact include/u8g2_vietnamese.h with unifont_t_vietnamese1!")
