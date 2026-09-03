# -*- coding: utf-8 -*-
import math
import os
from PIL import Image, ImageDraw

def hex_to_rgb(hex_str):
    hex_str = hex_str.lstrip('#')
    return (int(hex_str[0:2], 16), int(hex_str[2:4], 16), int(hex_str[4:6], 16))

COLORS = {
    "C_FRESNEL_LAVENDER":   hex_to_rgb("#F3E8FF"),
    "C_HEAD_PASTEL_LIGHT":  hex_to_rgb("#DDD6FE"),
    "C_HEAD_PASTEL_MID":    hex_to_rgb("#C4B5FD"),
    "C_HEAD_PURPLE":        hex_to_rgb("#6D28D9"), # Tím hoàng gia Pop Mart
    "C_HEAD_PURPLE_LIGHT":  hex_to_rgb("#8B5CF6"), # Tím oải hương đón sáng
    "C_HEAD_PURPLE_DARK":   hex_to_rgb("#4C1D95"), # Tím đậm đổ bóng khối
    "C_HELMET_DEEP":        hex_to_rgb("#2E1065"), # Khe rãnh múi giáp tím sâu thẳm
    "C_BODY_DARK":          hex_to_rgb("#4C1D95"), # Thân tím thẫm ngoài hành tinh
    "C_BODY_SHADOW":        hex_to_rgb("#1E0A40"), # Hốc tối thân và chân sâu thẳm
    "C_MAGENTA_LIGHT":      hex_to_rgb("#F472B6"), # Đón sáng giác cắt hồng fuchsia
    "C_MAGENTA_CORE":       hex_to_rgb("#E11D48"), # Mặt nạ vùng mắt, vành mũ và yếm ngực
    "C_MAGENTA_DEEP":       hex_to_rgb("#9F1239"), # Đáy bóng tối hồng magenta
    "C_CYAN_GLOW":          hex_to_rgb("#A5F3FC"), # Quầng hào quang lam ngọc rực sáng
    "C_CYAN_BRIGHT":        hex_to_rgb("#22D3EE"), # Sọc dạ quang cyan cổ, ngực và chóp kim
    "C_CYAN_CORE":          hex_to_rgb("#06B6D4"), # Mắt hình thoi lam ngọc phát sáng
    "C_CYAN_DARK":          hex_to_rgb("#0E7490"), # Viền hốc mắt lam ngọc đậm
    "C_HORN_TIP_WHITE":     hex_to_rgb("#FFFFFF"), # Đỉnh chóp kim tiêm men sứ bắt sáng
    "C_HORN_STEM":          hex_to_rgb("#E9D5FF"), # Thân kim tiêm ngọc lam tím nhạt
    "C_BLUSH_PINK":         hex_to_rgb("#F43F5E"), # Đôi má ửng hồng tím ngộ nghĩnh
    "C_MOUTH_DEEP":         hex_to_rgb("#4C0519"), # Khóe miệng cười chữ V tinh nghịch
    "C_CONTACT_SHADOW":     hex_to_rgb("#1E1B4B"), # Bóng tiếp xúc mờ ảo trên mặt sàn
    "C_WHITE":              hex_to_rgb("#FFFFFF")
}

class MockScaledCanvas:
    def __init__(self, draw, originX, originY, scale=1.0):
        self.draw = draw
        self.originX = originX
        self.originY = originY
        self.scale = scale

    def sx(self, x):
        return int(round(self.originX + (x - self.originX) * self.scale))

    def sy(self, y):
        return int(round(self.originY + (y - self.originY) * self.scale))

    def sr(self, r):
        return max(1, int(round(r * self.scale)))

    def fillCircle(self, x, y, r, col):
        cx, cy, cr = self.sx(x), self.sy(y), self.sr(r)
        self.draw.ellipse([cx - cr, cy - cr, cx + cr, cy + cr], fill=col)

    def drawCircle(self, x, y, r, col):
        cx, cy, cr = self.sx(x), self.sy(y), self.sr(r)
        self.draw.ellipse([cx - cr, cy - cr, cx + cr, cy + cr], outline=col)

    def fillRoundRect(self, x, y, w, h, r, col):
        x0, y0 = self.sx(x), self.sy(y)
        sw, sh, sr = self.sr(w), self.sr(h), self.sr(r)
        self.draw.rounded_rectangle([x0, y0, x0 + sw, y0 + sh], radius=sr, fill=col)

    def drawRoundRect(self, x, y, w, h, r, col):
        x0, y0 = self.sx(x), self.sy(y)
        sw, sh, sr = self.sr(w), self.sr(h), self.sr(r)
        self.draw.rounded_rectangle([x0, y0, x0 + sw, y0 + sh], radius=sr, outline=col)

    def fillRect(self, x, y, w, h, col):
        x0, y0 = self.sx(x), self.sy(y)
        sw, sh = self.sr(w), self.sr(h)
        self.draw.rectangle([x0, y0, x0 + sw, y0 + sh], fill=col)

    def drawPixel(self, x, y, col):
        x0, y0 = self.sx(x), self.sy(y)
        s = self.sr(1)
        self.draw.rectangle([x0, y0, x0 + s, y0 + s], fill=col)

    def drawLine(self, x0, y0, x1, y1, col):
        self.draw.line([(self.sx(x0), self.sy(y0)), (self.sx(x1), self.sy(y1))], fill=col, width=max(1, int(round(self.scale))))

    def drawFastVLine(self, x, y, h, col):
        x0, y0 = self.sx(x), self.sy(y)
        sh = self.sr(h)
        self.draw.line([(x0, y0), (x0, y0 + sh)], fill=col, width=max(1, int(round(self.scale))))

    def drawFastHLine(self, x, y, w, col):
        x0, y0 = self.sx(x), self.sy(y)
        sw = self.sr(w)
        self.draw.line([(x0, y0), (x0 + sw, y0)], fill=col, width=max(1, int(round(self.scale))))

    def fillEllipse(self, x, y, rx, ry, col):
        cx, cy = self.sx(x), self.sy(y)
        srx, sry = self.sr(rx), self.sr(ry)
        self.draw.ellipse([cx - srx, cy - sry, cx + srx, cy + sry], fill=col)

    def drawEllipse(self, x, y, rx, ry, col):
        cx, cy = self.sx(x), self.sy(y)
        srx, sry = self.sr(rx), self.sr(ry)
        self.draw.ellipse([cx - srx, cy - sry, cx + srx, cy + sry], outline=col, width=max(1, int(round(self.scale))))

    def fillTriangle(self, x0, y0, x1, y1, x2, y2, col):
        pts = [(self.sx(x0), self.sy(y0)), (self.sx(x1), self.sy(y1)), (self.sx(x2), self.sy(y2))]
        self.draw.polygon(pts, fill=col)

def draw_poipole(spr, cx, cy, angle, blink=False):
    breathPhase = angle * 2.0
    breathSin = math.sin(breathPhase)

    # Squash & Stretch 5%
    sY = 1.0 + 0.05 * breathSin
    sX = 1.0 - 0.025 * breathSin
    by = cy + int(breathSin * 3.5)

    # Kinematics Phase Lags
    hornLag = breathPhase - 0.45
    hornSwayX = int(math.sin(hornLag) * 2.5)
    hornSwayY = int(math.cos(hornLag) * 1.8)

    tailLag = breathPhase - 0.65
    tailSway = int(math.sin(tailLag) * 4.5)

    C = COLORS

    # 1. LAYER 0: BÓNG TIẾP XÚC MẶT SÀN (Ground Contact Shadow)
    groundY = cy + 46
    shadowRx = int((28.0 - breathSin * 3.0) * sX)
    shadowRy = int(6.0 - breathSin * 0.8)
    spr.fillEllipse(cx + 2, groundY, shadowRx + 4, shadowRy + 1, C["C_CONTACT_SHADOW"])
    spr.fillEllipse(cx + 2, groundY, shadowRx, shadowRy, (16, 10, 68))

    # 2. LAYER 1: BỌT ĐỘC DẠ QUANG PHÁT SÁNG (Bioluminescent Poison Plasma Droplets)
    dropletOffsets = [(-34, -22), (36, -18), (-40, 14), (38, 22), (-22, -44), (26, -50)]
    dropletPhases = [0.0, 1.2, 2.4, 3.6, 4.8, 5.5]
    for b in range(6):
        bLag = breathPhase * 0.8 + dropletPhases[b]
        bx = cx + dropletOffsets[b][0] + int(math.cos(bLag) * 3.0)
        bby = cy + dropletOffsets[b][1] + int(math.sin(bLag) * 3.5)
        br = 3 if (b % 2 == 0) else 2
        spr.drawCircle(bx, bby, br, C["C_CYAN_GLOW"])
        spr.fillCircle(bx, bby, br - 1, C["C_CYAN_BRIGHT"])
        spr.drawPixel(bx, bby, C["C_WHITE"])

    # 3. LAYER 2: CHIẾC ĐUÔI CONG NGOE NGUẨY VUI VẺ (Curved Alien Tail with Fin & Pink Tip)
    tRootX = cx + int(6 * sX)
    tRootY = by + int(14 * sY)
    tMidX  = cx + int(24 * sX) + tailSway
    tMidY  = by + int(20 * sY)
    tArchX = cx + int(36 * sX) + int(tailSway * 1.2)
    tArchY = by + int(32 * sY)
    tTipX  = cx + int(38 * sX) + int(tailSway * 1.5)
    tTipY  = by + int(48 * sY)

    spr.fillTriangle(tRootX, tRootY - 3, tMidX, tMidY - 3, tRootX, tRootY + 4, C["C_BODY_DARK"])
    spr.fillTriangle(tMidX, tMidY - 3, tArchX, tArchY - 2, tMidX, tMidY + 3, C["C_BODY_DARK"])
    spr.fillTriangle(tArchX, tArchY - 2, tTipX, tTipY, tArchX, tArchY + 3, C["C_BODY_SHADOW"])

    # Vây gai nhọn trên sống đuôi (Dorsal Fin)
    spr.fillTriangle(tMidX + 2, tMidY - 2, tMidX + 10, tMidY - 8, tMidX + 11, tMidY - 1, C["C_HEAD_PURPLE_DARK"])
    spr.drawLine(tMidX + 2, tMidY - 2, tMidX + 10, tMidY - 8, C["C_FRESNEL_LAVENDER"])

    # Viền sống đuôi
    spr.drawLine(tRootX, tRootY - 3, tMidX, tMidY - 3, C["C_HEAD_PURPLE_LIGHT"])
    spr.drawLine(tMidX, tMidY - 3, tArchX, tArchY - 2, C["C_HEAD_PURPLE"])
    spr.drawLine(tArchX, tArchY - 2, tTipX, tTipY, C["C_MAGENTA_CORE"])

    # Chóp đuôi màu hồng fuchsia vuốt nhọn với đốm cyan phát quang
    spr.fillTriangle(tArchX + 1, tArchY + 1, tTipX, tTipY, tTipX - 3, tTipY + 4, C["C_MAGENTA_CORE"])
    spr.drawPixel(tTipX, tTipY, C["C_CYAN_BRIGHT"])

    # 4. LAYER 3: ĐÔI CHÂN CO BÁNH BAO & KHỐI THÂN TÍM ĐẬM (Chubby Legs & Tiny Torso)
    # Chân trái (viewer's left)
    intLegLX = cx - int(8 * sX)
    spr.fillRoundRect(intLegLX - 4, by + 17, int(8 * sX), int(13 * sY), 4, C["C_BODY_DARK"])
    spr.fillCircle(intLegLX, by + 27, int(3.5 * sX), C["C_HEAD_PURPLE_DARK"])
    spr.drawPixel(intLegLX, by + 28, C["C_FRESNEL_LAVENDER"])

    # Chân phải (viewer's right)
    intLegRX = cx + int(5 * sX)
    spr.fillRoundRect(intLegRX - 4, by + 17, int(8 * sX), int(13 * sY), 4, C["C_BODY_DARK"])
    spr.fillCircle(intLegRX, by + 27, int(3.5 * sX), C["C_HEAD_PURPLE_DARK"])
    spr.drawPixel(intLegRX, by + 28, C["C_FRESNEL_LAVENDER"])

    # Khối thân tím đậm nhỏ bé mũm mĩm
    bRy = int(14 * sY)
    bRx = int(13 * sX)
    spr.fillEllipse(cx - int(1 * sX), by + 10, bRx + 1, bRy + 1, C["C_HEAD_PURPLE_DARK"])
    spr.fillEllipse(cx - int(1 * sX), by + 10, bRx, bRy, C["C_BODY_DARK"])
    spr.fillEllipse(cx - int(1 * sX), by + 13, int(10 * sX), int(8 * sY), C["C_BODY_SHADOW"])
    spr.fillEllipse(cx - int(4 * sX), by + 7, int(6 * sX), int(5 * sY), C["C_HEAD_PURPLE_LIGHT"])

    # 5. LAYER 4: YẾM CHEVRON MAGENTA & SỌC DẠ QUANG CYAN CỔ VÀ NGỰC
    chestY = by + 4
    spr.fillTriangle(cx - int(8 * sX), chestY, cx + int(6 * sX), chestY, cx - int(1 * sX), chestY + int(9 * sY), C["C_MAGENTA_CORE"])
    spr.fillTriangle(cx - int(5 * sX), chestY, cx + int(4 * sX), chestY, cx - int(1 * sX), chestY + int(7 * sY), C["C_MAGENTA_LIGHT"])

    # Sọc dạ quang cyan phát quang viền yếm
    spr.drawLine(cx - int(8 * sX), chestY, cx - int(1 * sX), chestY + int(9 * sY), C["C_CYAN_BRIGHT"])
    spr.drawLine(cx + int(6 * sX), chestY, cx - int(1 * sX), chestY + int(9 * sY), C["C_CYAN_BRIGHT"])
    spr.drawLine(cx - int(9 * sX), chestY, cx - int(1 * sX), chestY + int(10 * sY), C["C_CYAN_GLOW"])
    spr.drawLine(cx + int(7 * sX), chestY, cx - int(1 * sX), chestY + int(10 * sY), C["C_CYAN_GLOW"])
    spr.drawFastHLine(cx - int(8 * sX), chestY - 2, int(15 * sX), C["C_CYAN_BRIGHT"])
    spr.drawPixel(cx - int(1 * sX), chestY + int(9 * sY), C["C_WHITE"])

    # 6. LAYER 5: TỨ CHI TÍ HON
    armRx1 = cx + int(8 * sX)
    armRy1 = by + 6
    armRx2 = cx + int(22 * sX)
    armRy2 = by + 7 + int(math.sin(breathPhase) * 2.0)
    spr.fillTriangle(armRx1, armRy1 - 3, armRx1, armRy1 + 3, armRx2, armRy2, C["C_BODY_DARK"])
    spr.fillCircle(armRx2, armRy2, 2, C["C_HEAD_PURPLE_LIGHT"])
    spr.drawLine(armRx1, armRy1 - 3, armRx2, armRy2, C["C_FRESNEL_LAVENDER"])

    # Tay trái giơ lên má
    armLx1 = cx - int(7 * sX)
    armLy1 = by + 6
    armLx2 = cx - int(15 * sX)
    armLy2 = by + 2
    armLx3 = cx - int(13 * sX)
    armLy3 = by - 4
    spr.fillTriangle(armLx1, armLy1 - 2, armLx2, armLy2, armLx1, armLy1 + 3, C["C_BODY_DARK"])
    spr.fillTriangle(armLx2, armLy2 - 2, armLx3, armLy3, armLx2, armLy2 + 2, C["C_BODY_DARK"])
    spr.fillCircle(armLx3, armLy3, 2, C["C_HEAD_PURPLE_LIGHT"])
    spr.drawPixel(armLx3, armLy3 - 1, C["C_FRESNEL_LAVENDER"])

    # 7. LAYER 6: ĐẦU DÁNG QUẢ LÊ / GIỌT NƯỚC NGƯỢC (Tapered Acorn/Flask Head)
    hy = by - 16
    hRy = int(28 * sY)
    hRx = int(25 * sX)

    # 7.1 Thùy má hai bên phúng phính
    spr.fillEllipse(cx - int(15 * sX), hy + int(5 * sY), int(14 * sX), int(17 * sY), C["C_HEAD_PURPLE"])
    spr.fillEllipse(cx + int(15 * sX), hy + int(5 * sY), int(14 * sX), int(17 * sY), C["C_HEAD_PURPLE"])

    # 7.2 Khối vòm đầu chính
    spr.fillEllipse(cx, hy, hRx + 2, hRy + 2, C["C_FRESNEL_LAVENDER"])
    spr.fillEllipse(cx, hy, hRx, hRy, C["C_HEAD_PURPLE"])
    spr.fillEllipse(cx, hy - int(4 * sY), int(22 * sX), int(22 * sY), C["C_HEAD_PURPLE_LIGHT"])
    spr.fillEllipse(cx - int(6 * sX), hy - int(12 * sY), int(13 * sX), int(12 * sY), C["C_HEAD_PASTEL_LIGHT"])

    # 7.3 Chóp nón vươn lên đỉnh
    spr.fillTriangle(cx - int(15 * sX), hy - int(16 * sY), cx + int(15 * sX), hy - int(16 * sY), cx, hy - int(32 * sY), C["C_HEAD_PURPLE"])
    spr.fillTriangle(cx - int(10 * sX), hy - int(16 * sY), cx + int(10 * sX), hy - int(16 * sY), cx, hy - int(32 * sY), C["C_HEAD_PURPLE_LIGHT"])
    spr.drawLine(cx - int(15 * sX), hy - int(16 * sY), cx, hy - int(32 * sY), C["C_FRESNEL_LAVENDER"])
    spr.drawLine(cx + int(15 * sX), hy - int(16 * sY), cx, hy - int(32 * sY), C["C_HEAD_PURPLE_DARK"])

    # 7.4 Cằm bo tròn mềm mại dưới má
    spr.fillEllipse(cx, hy + int(17 * sY), int(13 * sX), int(8 * sY), C["C_HEAD_PURPLE"])
    spr.drawEllipse(cx, hy + int(17 * sY), int(13 * sX), int(8 * sY), C["C_HEAD_PURPLE_DARK"])

    # 7.5 Múi giáp cánh hoa xòe hai bên tai
    spr.fillTriangle(cx - int(23 * sX), hy + int(6 * sY), cx - int(34 * sX), hy - int(7 * sY), cx - int(18 * sX), hy - int(14 * sY), C["C_HEAD_PURPLE_DARK"])
    spr.fillTriangle(cx + int(23 * sX), hy + int(6 * sY), cx + int(34 * sX), hy - int(7 * sY), cx + int(18 * sX), hy - int(14 * sY), C["C_HEAD_PURPLE_DARK"])
    spr.drawLine(cx - int(23 * sX), hy + int(6 * sY), cx - int(34 * sX), hy - int(7 * sY), C["C_FRESNEL_LAVENDER"])
    spr.drawLine(cx + int(23 * sX), hy + int(6 * sY), cx + int(34 * sX), hy - int(7 * sY), C["C_FRESNEL_LAVENDER"])

    # 7.6 Vành nón đỉnh đầu magenta
    spr.fillEllipse(cx, hy - int(22 * sY), int(13 * sX), int(6 * sY), C["C_MAGENTA_DEEP"])
    spr.fillEllipse(cx, hy - int(23 * sY), int(12 * sX), int(5 * sY), C["C_MAGENTA_CORE"])
    spr.fillEllipse(cx - int(3 * sX), hy - int(24 * sY), int(6 * sX), int(2.5 * sY), C["C_MAGENTA_LIGHT"])

    # 7.7 Cánh hoa kim cương magenta giữa trán
    fX = cx
    fY = hy - int(8 * sY)
    spr.fillTriangle(fX, fY - int(11 * sY), fX - int(6 * sX), fY, fX + int(6 * sX), fY, C["C_MAGENTA_CORE"])
    spr.fillTriangle(fX, fY + int(9 * sY), fX - int(6 * sX), fY, fX + int(6 * sX), fY, C["C_MAGENTA_CORE"])
    spr.drawLine(fX, fY - int(11 * sY), fX - int(6 * sX), fY, C["C_MAGENTA_LIGHT"])
    spr.drawLine(fX, fY - int(11 * sY), fX + int(6 * sX), fY, C["C_MAGENTA_LIGHT"])
    spr.drawPixel(fX, fY, C["C_WHITE"])

    # 7.8 Rãnh múi giáp tím thẫm
    spr.drawLine(cx - int(7 * sX), hy - int(18 * sY), cx - int(15 * sX), hy - int(3 * sY), C["C_HELMET_DEEP"])
    spr.drawLine(cx + int(7 * sX), hy - int(18 * sY), cx + int(15 * sX), hy - int(3 * sY), C["C_HELMET_DEEP"])

    # 8. LAYER 7: 3 CHIẾC KIM TIÊM / SỪNG NGỌC LAM CYAN PHÁT QUANG
    # 8.1 Sừng giữa đỉnh đầu
    s0BaseX = cx
    s0BaseY = hy - int(28 * sY)
    s0TipX  = cx + int(hornSwayX * 0.7)
    s0TipY  = hy - int(54 * sY) + hornSwayY

    spr.fillTriangle(s0BaseX - 3, s0BaseY, s0BaseX + 3, s0BaseY, s0TipX, s0TipY, C["C_HORN_STEM"])
    spr.drawLine(s0BaseX, s0BaseY, s0TipX, s0TipY, C["C_FRESNEL_LAVENDER"])
    spr.fillCircle(s0TipX, s0TipY, 4, C["C_CYAN_GLOW"])
    spr.fillCircle(s0TipX, s0TipY, 2, C["C_CYAN_BRIGHT"])
    spr.drawPixel(s0TipX, s0TipY - 1, C["C_HORN_TIP_WHITE"])

    # 8.2 Sừng trái
    sLBaseX = cx - int(24 * sX)
    sLBaseY = hy - int(8 * sY)
    sLTipX  = cx - int(41 * sX) + hornSwayX
    sLTipY  = hy - int(26 * sY) + hornSwayY

    spr.fillCircle(sLBaseX, sLBaseY, 5, C["C_MAGENTA_CORE"])
    spr.fillCircle(sLBaseX - 1, sLBaseY - 1, 3, C["C_MAGENTA_LIGHT"])
    spr.fillTriangle(sLBaseX, sLBaseY - 2, sLBaseX, sLBaseY + 2, sLTipX, sLTipY, C["C_HORN_STEM"])
    spr.drawLine(sLBaseX, sLBaseY - 2, sLTipX, sLTipY, C["C_FRESNEL_LAVENDER"])
    spr.fillCircle(sLTipX, sLTipY, 3, C["C_CYAN_GLOW"])
    spr.fillCircle(sLTipX, sLTipY, 2, C["C_CYAN_BRIGHT"])
    spr.drawPixel(sLTipX, sLTipY, C["C_HORN_TIP_WHITE"])

    # 8.3 Sừng phải
    sRBaseX = cx + int(24 * sX)
    sRBaseY = hy - int(8 * sY)
    sRTipX  = cx + int(41 * sX) + hornSwayX
    sRTipY  = hy - int(26 * sY) + hornSwayY

    spr.fillCircle(sRBaseX, sRBaseY, 5, C["C_MAGENTA_CORE"])
    spr.fillCircle(sRBaseX + 1, sRBaseY - 1, 3, C["C_MAGENTA_LIGHT"])
    spr.fillTriangle(sRBaseX, sRBaseY - 2, sRBaseX, sRBaseY + 2, sRTipX, sRTipY, C["C_HORN_STEM"])
    spr.drawLine(sRBaseX, sRBaseY - 2, sRTipX, sRTipY, C["C_FRESNEL_LAVENDER"])
    spr.fillCircle(sRTipX, sRTipY, 3, C["C_CYAN_GLOW"])
    spr.fillCircle(sRTipX, sRTipY, 2, C["C_CYAN_BRIGHT"])
    spr.drawPixel(sRTipX, sRTipY, C["C_HORN_TIP_WHITE"])

    # 9. LAYER 8: MẶT NẠ MẮT HỒNG MAGENTA & ĐÔI MÁ HỒNG TÍM
    maskY = hy + 4
    spr.fillEllipse(cx, maskY, int(18 * sX), int(8 * sY), C["C_MAGENTA_CORE"])
    spr.fillEllipse(cx, maskY - 1, int(16 * sX), int(6 * sY), C["C_MAGENTA_LIGHT"])

    # Đôi má hồng tím ngộ nghĩnh Pop Mart
    spr.fillEllipse(cx - int(17 * sX), hy + 9, 4, 3, C["C_BLUSH_PINK"])
    spr.fillEllipse(cx + int(17 * sX), hy + 9, 4, 3, C["C_BLUSH_PINK"])

    # 10. LAYER 9: ĐÔI MẮT HÌNH THOI MÀU LAM NGỌC PHÁT SÁNG (Tilted Rhombus Cyan Eyes)
    eyeY  = hy + 3
    eyeXL = cx - int(11 * sX)
    eyeXR = cx + int(11 * sX)

    if blink:
        spr.drawLine(eyeXL - 6, eyeY, eyeXL, eyeY + 2, C["C_CYAN_BRIGHT"])
        spr.drawLine(eyeXL, eyeY + 2, eyeXL + 6, eyeY - 1, C["C_CYAN_BRIGHT"])
        spr.drawLine(eyeXL - 6, eyeY - 1, eyeXL, eyeY + 1, C["C_CYAN_GLOW"])

        spr.drawLine(eyeXR - 6, eyeY - 1, eyeXR, eyeY + 2, C["C_CYAN_BRIGHT"])
        spr.drawLine(eyeXR, eyeY + 2, eyeXR + 6, eyeY, C["C_CYAN_BRIGHT"])
        spr.drawLine(eyeXR + 1, eyeY + 1, eyeXR + 6, eyeY - 1, C["C_CYAN_GLOW"])
    else:
        # Mắt trái: Tilted Quadrilateral / Rhombus (đỉnh ngoài nhọn hếch lên)
        xl1 = (eyeXL + 3, eyeY - 6) # đỉnh trên
        xl2 = (eyeXL + 6, eyeY)     # đỉnh phải
        xl3 = (eyeXL - 2, eyeY + 6) # đỉnh dưới
        xl4 = (eyeXL - 8, eyeY - 2) # đỉnh ngoài nhọn

        spr.fillTriangle(xl1[0], xl1[1], xl2[0], xl2[1], xl4[0], xl4[1], C["C_CYAN_DARK"])
        spr.fillTriangle(xl3[0], xl3[1], xl2[0], xl2[1], xl4[0], xl4[1], C["C_CYAN_DARK"])
        spr.fillTriangle(xl1[0] - 1, xl1[1] + 1, xl2[0] - 1, xl2[1], xl4[0] + 1, xl4[1], C["C_CYAN_CORE"])
        spr.fillTriangle(xl3[0] + 1, xl3[1] - 1, xl2[0] - 1, xl2[1], xl4[0] + 1, xl4[1], C["C_CYAN_BRIGHT"])

        # Điểm bắt sáng kim cương trắng trong mắt trái
        spr.fillCircle(eyeXL, eyeY - 2, 2, C["C_WHITE"])
        spr.drawPixel(eyeXL + 3, eyeY + 2, C["C_CYAN_GLOW"])

        # Mắt phải: Tilted Quadrilateral / Rhombus
        xr1 = (eyeXR - 3, eyeY - 6) # đỉnh trên
        xr2 = (eyeXR + 8, eyeY - 2) # đỉnh ngoài nhọn
        xr3 = (eyeXR + 2, eyeY + 6) # đỉnh dưới
        xr4 = (eyeXR - 6, eyeY)     # đỉnh trái

        spr.fillTriangle(xr1[0], xr1[1], xr2[0], xr2[1], xr4[0], xr4[1], C["C_CYAN_DARK"])
        spr.fillTriangle(xr3[0], xr3[1], xr2[0], xr2[1], xr4[0], xr4[1], C["C_CYAN_DARK"])
        spr.fillTriangle(xr1[0] + 1, xr1[1] + 1, xr2[0] - 1, xr2[1], xr4[0] + 1, xr4[1], C["C_CYAN_CORE"])
        spr.fillTriangle(xr3[0] - 1, xr3[1] - 1, xr2[0] - 1, xr2[1], xr4[0] + 1, xr4[1], C["C_CYAN_BRIGHT"])

        # Điểm bắt sáng kim cương trắng trong mắt phải
        spr.fillCircle(eyeXR, eyeY - 2, 2, C["C_WHITE"])
        spr.drawPixel(eyeXR - 3, eyeY + 2, C["C_CYAN_GLOW"])

    # 11. LAYER 10: MIỆNG CƯỜI CHỮ V TINH NGHỊCH (Mischievous V-Smile)
    mY = hy + 13
    spr.fillTriangle(cx - 5, mY - 1, cx + 5, mY - 1, cx, mY + 3, C["C_MOUTH_DEEP"])
    spr.drawLine(cx - 5, mY - 1, cx, mY + 3, C["C_CYAN_BRIGHT"])
    spr.drawLine(cx, mY + 3, cx + 5, mY - 1, C["C_CYAN_BRIGHT"])

def render_test_images():
    w, h = 240, 280
    img = Image.new("RGB", (w, h), (17, 12, 40))
    draw = ImageDraw.Draw(img)

    canvas = MockScaledCanvas(draw, w // 2, h // 2, scale=1.35)
    draw_poipole(canvas, w // 2, h // 2, angle=0.0, blink=False)

    out_file = "tools/poipole_render_test.png"
    img.save(out_file)
    print(f"Rendered test image: {out_file}")

if __name__ == "__main__":
    render_test_images()
