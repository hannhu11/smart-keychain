import urllib.request
import re

with open('include/u8g2_vietnamese.h', 'r', encoding='utf-8') as f:
    pass # test read

url = 'https://raw.githubusercontent.com/olikraus/u8g2/master/csrc/u8g2_fonts.c'
req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
with urllib.request.urlopen(req, timeout=20) as resp:
    content = resp.read().decode('latin-1')

# Find u8g2_font_unifont_t_vietnamese1[4264] or u8g2_font_unifont_t_vietnamese2[15244]
p2 = content.find('const uint8_t u8g2_font_unifont_t_vietnamese2[15244]')
if p2 != -1:
    # Next font starts after this one
    p_next = content.find('const uint8_t ', p2 + 50)
    font2_block = content[p2:p_next].strip()
    # Ensure it ends with };
    if not font2_block.endswith('};'):
        semi = font2_block.rfind('};')
        if semi != -1:
            font2_block = font2_block[:semi+2]

    print('Proper font 2 length:', len(font2_block))
    font2_block = font2_block.replace('U8G2_FONT_SECTION("u8g2_font_unifont_t_vietnamese2")', 'PROGMEM')

    header_code = f'''#pragma once
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

{font2_block}

namespace fonts {{
  static const lgfx::U8g2font fontVietnamese(u8g2_font_unifont_t_vietnamese2);
}}
'''
    with open('include/u8g2_vietnamese.h', 'w', encoding='utf-8') as f:
        f.write(header_code)
    print("Successfully wrote exact 15KB include/u8g2_vietnamese.h!")
