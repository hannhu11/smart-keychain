import re
import json

def rgb565_to_hex(val):
    val = val.strip()
    named = {
        'TFT_WHITE': '"#ffffff"', 'TFT_BLACK': '"#000000"', 'TFT_RED': '"#ff0000"',
        'TFT_GREEN': '"#00ff00"', 'TFT_BLUE': '"#0044ff"', 'TFT_YELLOW': '"#ffee00"',
        'TFT_CYAN': '"#00f0ff"', 'TFT_MAGENTA': '"#ff00ff"'
    }
    if val in named:
        return named[val]
    if val.startswith('0x') or val.startswith('0X'):
        try:
            c = int(val, 16)
            r = ((c >> 11) & 0x1F) * 255 // 31
            g = ((c >> 5) & 0x3F) * 255 // 63
            b = (c & 0x1F) * 255 // 31
            return f'"#{r:02x}{g:02x}{b:02x}"'
        except:
            pass
    return f'"{val}"'

def parse_sprites_data():
    with open('include/sprites_data.h', 'r', encoding='utf-8') as f:
        content = f.read()

    cases = re.split(r'case\s+(\d+):', content)
    transpiled_cases = {}

    for i in range(1, len(cases), 2):
        cid = int(cases[i])
        raw_body = cases[i+1]
        break_pos = raw_body.find('break;')
        if break_pos != -1:
            raw_body = raw_body[:break_pos]

        lines = raw_body.strip().splitlines()
        js_lines = []

        for line in lines:
            line_str = line.strip()
            if not line_str or line_str.startswith('//'):
                js_lines.append('          ' + line_str)
                continue

            l = line_str
            l = re.sub(r'\(int\)\s*', '', l)
            l = re.sub(r'\bsin\(', 'Math.sin(', l)
            l = re.sub(r'\bcos\(', 'Math.cos(', l)
            l = re.sub(r'(\d+)f\b', r'\1', l)
            l = re.sub(r'cx\s*\+\s*', '', l)
            l = re.sub(r'cx\s*-\s*', '-', l)
            l = re.sub(r'\bcx\b', '0', l)
            l = re.sub(r'cy\s*\+\s*', '', l)
            l = re.sub(r'cy\s*-\s*', '-', l)
            l = re.sub(r'\bcy\b', '0', l)

            def repl_fr(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 6:
                    x, y, w, h, r, c = args
                    return f"frRect(ctx, {x}, {y}, {w}, {h}, {r}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->fillRoundRect\((.*?)\);', repl_fr, l)

            def repl_dr(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 6:
                    x, y, w, h, r, c = args
                    return f"drRect(ctx, {x}, {y}, {w}, {h}, {r}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->drawRoundRect\((.*?)\);', repl_dr, l)

            def repl_fc(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 4:
                    x, y, r, c = args
                    return f"fCirc(ctx, {x}, {y}, {r}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->fillCircle\((.*?)\);', repl_fc, l)

            def repl_dc(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 4:
                    x, y, r, c = args
                    return f"dCirc(ctx, {x}, {y}, {r}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->drawCircle\((.*?)\);', repl_dc, l)

            def repl_ft(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 7:
                    x1, y1, x2, y2, x3, y3, c = args
                    return f"fTri(ctx, {x1}, {y1}, {x2}, {y2}, {x3}, {y3}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->fillTriangle\((.*?)\);', repl_ft, l)

            def repl_dt(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 7:
                    x1, y1, x2, y2, x3, y3, c = args
                    return f"dTri(ctx, {x1}, {y1}, {x2}, {y2}, {x3}, {y3}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->drawTriangle\((.*?)\);', repl_dt, l)

            def repl_frect(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 5:
                    x, y, w, h, c = args
                    return f"fRect(ctx, {x}, {y}, {w}, {h}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->fillRect\((.*?)\);', repl_frect, l)

            def repl_drect(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 5:
                    x, y, w, h, c = args
                    return f"dRect(ctx, {x}, {y}, {w}, {h}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->drawRect\((.*?)\);', repl_drect, l)

            def repl_line(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 5:
                    x1, y1, x2, y2, c = args
                    return f"dLine(ctx, {x1}, {y1}, {x2}, {y2}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->drawLine\((.*?)\);', repl_line, l)

            def repl_fvl(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 4:
                    x, y, h, c = args
                    return f"dLine(ctx, {x}, {y}, {x}, {y} + {h}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->drawFastVLine\((.*?)\);', repl_fvl, l)

            def repl_fhl(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 4:
                    x, y, w, c = args
                    return f"dLine(ctx, {x}, {y}, {x} + {w}, {y}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->drawFastHLine\((.*?)\);', repl_fhl, l)

            def repl_pix(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 3:
                    x, y, c = args
                    return f"dPixel(ctx, {x}, {y}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->drawPixel\((.*?)\);', repl_pix, l)

            def repl_arc(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 7:
                    x, y, r1, r2, sa, ea, c = args
                    return f"dArc(ctx, {x}, {y}, {r1}, {r2}, {sa}, {ea}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->drawArc\((.*?)\);', repl_arc, l)

            def repl_del(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 5:
                    x, y, rx, ry, c = args
                    return f"dEllip(ctx, {x}, {y}, {rx}, {ry}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->drawEllipse\((.*?)\);', repl_del, l)

            def repl_fel(m):
                args = [a.strip() for a in m.group(1).split(',')]
                if len(args) == 5:
                    x, y, rx, ry, c = args
                    return f"fEllip(ctx, {x}, {y}, {rx}, {ry}, {rgb565_to_hex(c)});"
                return m.group(0)
            l = re.sub(r'spr->fillEllipse\((.*?)\);', repl_fel, l)

            l = re.sub(r'\bint\s+', 'let ', l)
            l = re.sub(r'\bfloat\s+', 'let ', l)
            l = re.sub(r'let\s+pts\[(\d+)\]\[(\d+)\]\s*=', 'const pts =', l)

            js_lines.append('          ' + l)

        transpiled_cases[cid] = '\n'.join(js_lines)

    return transpiled_cases

if __name__ == '__main__':
    t_cases = parse_sprites_data()
    print("Clean Sample Case 0:\n", t_cases[0][:300])
