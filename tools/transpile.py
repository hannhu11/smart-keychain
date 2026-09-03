import re

def rgb565_to_hex(val):
    val = val.strip()
    named = {
        'TFT_WHITE': '#ffffff', 'TFT_BLACK': '#000000', 'TFT_RED': '#ff0000',
        'TFT_GREEN': '#00ff00', 'TFT_BLUE': '#0033ff', 'TFT_YELLOW': '#ffee00',
        'TFT_CYAN': '#00f0ff', 'TFT_MAGENTA': '#ff00ff'
    }
    if val in named:
        return named[val]
    if val.startswith('0x') or val.startswith('0X'):
        try:
            c = int(val, 16)
            r = ((c >> 11) & 0x1F) * 255 // 31
            g = ((c >> 5) & 0x3F) * 255 // 63
            b = (c & 0x1F) * 255 // 31
            return f'#{r:02x}{g:02x}{b:02x}'
        except:
            pass
    return f'{val}'

print(RGB565 test:, rgb565_to_hex('0x2800'), rgb565_to_hex('TFT_CYAN'))
