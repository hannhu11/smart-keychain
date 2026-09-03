# -*- coding: utf-8 -*-
import math
import os
from PIL import Image, ImageDraw

def hex_to_rgb(hex_str):
    hex_str = hex_str.lstrip('#')
    return (int(hex_str[0:2], 16), int(hex_str[2:4], 16), int(hex_str[4:6], 16))

COLORS = {
    "C_FRESNEL": hex_to_rgb("#F4FDF0"),
    "C_BODY_BASE": hex_to_rgb("#C8F0A6"),
    "C_BODY_MID": hex_to_rgb("#B2E58B"),
    "C_BODY_SHADOW": hex_to_rgb("#8FD065"),
    "C_BODY_DEEP": hex_to_rgb("#68A843"),
    "C_CREST_TIP": hex_to_rgb("#3E8E2D"),
    "C_CREST_DARK": hex_to_rgb("#245C1A"),
    "C_CREST_GLOW": hex_to_rgb("#95E46A"),
    "C_PANTS_DARK": hex_to_rgb("#488A2E"),
    "C_PANTS_LIGHT": hex_to_rgb("#6EBD4D"),
    "C_LEGS_DARK": hex_to_rgb("#3D7527"),
    "C_LEGS_LIGHT": hex_to_rgb("#64A648"),
    "C_ANT_STEM": hex_to_rgb("#B2E88F"),
    "C_ANT_MID": hex_to_rgb("#64D8CB"),
    "C_ANT_TIP": hex_to_rgb("#00B4D8"),
    "C_ANT_GLOW": hex_to_rgb("#72EFDD"),
    "C_ANT_CORE": hex_to_rgb("#0077B6"),
    "C_EYE_RING": hex_to_rgb("#121812"),
    "C_EYE_SOCKET": hex_to_rgb("#0A0F0A"),
    "C_IRIS_DEEP": hex_to_rgb("#023E8A"),
    "C_IRIS_SAPPHIRE": hex_to_rgb("#0077B6"),
    "C_IRIS_BRIGHT": hex_to_rgb("#00B4D8"),
    "C_IRIS_CAUSTIC": hex_to_rgb("#90E0EF"),
    "C_WHITE": hex_to_rgb("#FFFFFF"),
    "C_SPEC_SEC": hex_to_rgb("#CAF0F8"),
    "C_BLUSH": hex_to_rgb("#FFAAA6"),
    "C_MOUTH": hex_to_rgb("#1A3818"),
    "C_WING_GLASS": hex_to_rgb("#E0F7FA"),
    "C_WING_GLOW": hex_to_rgb("#A7F3D0"),
    "C_WING_RIM": hex_to_rgb("#80DEEA"),
    "C_WING_VEIN": hex_to_rgb("#4DD0E1"),
    "C_SHADOW_GND": hex_to_rgb("#0A1C0A"),
    "C_SHADOW_DIFF": hex_to_rgb("#142E14"),
    "C_MAGIC_SPORE": hex_to_rgb("#E0FF4F"),
    "C_STAR_GOLD": hex_to_rgb("#FEF08A"),
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
        if self.scale <= 1.2:
            self.draw.point((x0, y0), fill=col)
        else:
            s = self.sr(1)
            self.draw.rectangle([x0, y0, x0 + s, y0 + s], fill=col)

    def drawLine(self, x0, y0, x1, y1, col):
        self.draw.line([(self.sx(x0), self.sy(y0)), (self.sx(x1), self.sy(y1))], fill=col)

    def drawFastVLine(self, x, y, h, col):
        x0, y0 = self.sx(x), self.sy(y)
        sh = self.sr(h)
        self.draw.line([(x0, y0), (x0, y0 + sh)], fill=col)

    def drawFastHLine(self, x, y, w, col):
        x0, y0 = self.sx(x), self.sy(y)
        sw = self.sr(w)
        self.draw.line([(x0, y0), (x0 + sw, y0)], fill=col)

    def fillEllipse(self, x, y, rx, ry, col):
        cx, cy = self.sx(x), self.sy(y)
        srx, sry = self.sr(rx), self.sr(ry)
        self.draw.ellipse([cx - srx, cy - sry, cx + srx, cy + sry], fill=col)

    def drawEllipse(self, x, y, rx, ry, col):
        cx, cy = self.sx(x), self.sy(y)
        srx, sry = self.sr(rx), self.sr(ry)
        self.draw.ellipse([cx - srx, cy - sry, cx + srx, cy + sry], outline=col)

    def fillTriangle(self, x0, y0, x1, y1, x2, y2, col):
        pts = [(self.sx(x0), self.sy(y0)), (self.sx(x1), self.sy(y1)), (self.sx(x2), self.sy(y2))]
        self.draw.polygon(pts, fill=col)

def drawCelebiForestFairy(spr, cx, cy, angle, blink=False):
    # Palette aliases
    C_FRESNEL = COLORS["C_FRESNEL"]
    C_BODY_BASE = COLORS["C_BODY_BASE"]
    C_BODY_MID = COLORS["C_BODY_MID"]
    C_BODY_SHADOW = COLORS["C_BODY_SHADOW"]
    C_BODY_DEEP = COLORS["C_BODY_DEEP"]
    C_CREST_TIP = COLORS["C_CREST_TIP"]
    C_CREST_DARK = COLORS["C_CREST_DARK"]
    C_CREST_GLOW = COLORS["C_CREST_GLOW"]
    C_PANTS_DARK = COLORS["C_PANTS_DARK"]
    C_PANTS_LIGHT = COLORS["C_PANTS_LIGHT"]
    C_LEGS_DARK = COLORS["C_LEGS_DARK"]
    C_LEGS_LIGHT = COLORS["C_LEGS_LIGHT"]
    C_ANT_STEM = COLORS["C_ANT_STEM"]
    C_ANT_MID = COLORS["C_ANT_MID"]
    C_ANT_TIP = COLORS["C_ANT_TIP"]
    C_ANT_GLOW = COLORS["C_ANT_GLOW"]
    C_EYE_RING = COLORS["C_EYE_RING"]
    C_EYE_SOCKET = COLORS["C_EYE_SOCKET"]
    C_IRIS_DEEP = COLORS["C_IRIS_DEEP"]
    C_IRIS_SAPPHIRE = COLORS["C_IRIS_SAPPHIRE"]
    C_IRIS_BRIGHT = COLORS["C_IRIS_BRIGHT"]
    C_IRIS_CAUSTIC = COLORS["C_IRIS_CAUSTIC"]
    C_WHITE = COLORS["C_WHITE"]
    C_SPEC_SEC = COLORS["C_SPEC_SEC"]
    C_BLUSH = COLORS["C_BLUSH"]
    C_MOUTH = COLORS["C_MOUTH"]
    C_WING_GLASS = COLORS["C_WING_GLASS"]
    C_WING_GLOW = COLORS["C_WING_GLOW"]
    C_WING_RIM = COLORS["C_WING_RIM"]
    C_WING_VEIN = COLORS["C_WING_VEIN"]
    C_SHADOW_GND = COLORS["C_SHADOW_GND"]
    C_SHADOW_DIFF = COLORS["C_SHADOW_DIFF"]
    C_MAGIC_SPORE = COLORS["C_MAGIC_SPORE"]
    C_STAR_GOLD = COLORS["C_STAR_GOLD"]

    # 1. Nhịp thở Squash & Stretch 5% bảo toàn thể tích quanh tâm (cx, cy)
    breathFreq = 2.0
    breathPhase = angle * breathFreq
    breathSin = math.sin(breathPhase)

    by = cy + int(breathSin * 3.5)
    sY = 1.0 + 0.05 * breathSin
    sX = 1.0 - 0.025 * breathSin

    # 2. Cánh tiên đập trễ pha Delta Phi = 0.45 rad (dao động 15 độ tần số cao)
    wingPhase = angle * 7.5 - 0.45
    wingFlap = math.sin(wingPhase) * 5.0

    # 3. Ăng-ten quán tính khi bay lên xuống (Delta Phi = 0.25 rad)
    antPhase = breathPhase - 0.25
    antSwayX = int(math.cos(antPhase) * 2.5)
    antSwayY = int(math.sin(antPhase) * 2.0)

    # =========================================================================
    # LỚP 1: BÓNG TIẾP XÚC MẶT SÀN CO GIÃN THEO ĐỘ CAO
    # =========================================================================
    groundY = cy + 46
    diffRx = int((22 - breathSin * 3.5) * sX)
    diffRy = max(2, int(6.5 - breathSin * 1.2))
    coreRx = int((16 - breathSin * 2.8) * sX)
    coreRy = max(2, int(4.5 - breathSin * 1.0))
    spr.drawEllipse(cx + 4, groundY, diffRx, diffRy, C_SHADOW_DIFF)
    spr.fillEllipse(cx + 4, groundY, coreRx, coreRy, C_SHADOW_GND)

    # =========================================================================
    # LỚP 2: CÁNH TIÊN PHÍA SAU (Far Wing) - Trễ pha 0.45 rad
    # =========================================================================
    w1TipX = cx + 32
    w1TipY = by - 18 + int(wingFlap)
    w1MidX = cx + 24
    w1MidY = by - 8 + int(wingFlap * 0.7)
    spr.fillTriangle(cx + 6, by - 4, w1TipX, w1TipY, w1MidX, w1MidY, C_WING_GLASS)
    spr.fillTriangle(cx + 6, by - 2, w1MidX, w1MidY, cx + 18, by + 4, C_WING_GLOW)
    spr.drawLine(cx + 6, by - 4, w1TipX, w1TipY, C_WING_RIM)
    spr.drawLine(cx + 6, by - 4, w1MidX, w1MidY, C_WING_VEIN)

    # =========================================================================
    # LỚP 3: CÁNH TAY SAU (Left / Far Arm)
    # =========================================================================
    spr.fillTriangle(cx - 10, by + 7, cx - 8, by + 3, cx - 26, by - 2, C_BODY_BASE)
    spr.drawLine(cx - 10, by + 3, cx - 26, by - 2, C_FRESNEL)
    # 3 ngón tay nhỏ nhắn búp măng
    spr.fillCircle(cx - 28, by - 5, 1, C_BODY_BASE)
    spr.fillCircle(cx - 30, by - 2, 1, C_BODY_BASE)
    spr.fillCircle(cx - 27, by + 1, 1, C_BODY_BASE)

    # =========================================================================
    # LỚP 4: ĐÔI CHÂN & BÀN CHÂN BO TRÒN DỄ THƯƠNG
    # =========================================================================
    # Chân sau (Far leg)
    spr.fillRoundRect(cx + 6, by + 18, int(7 * sX), int(12 * sY), 3, C_LEGS_DARK)
    spr.fillCircle(cx + 9, by + 28, int(3 * sX), C_LEGS_LIGHT)
    # Chân trước (Near leg)
    spr.fillRoundRect(cx + 12, by + 21, int(8 * sX), int(14 * sY), 4, C_LEGS_DARK)
    spr.fillRoundRect(cx + 13, by + 22, int(6 * sX), int(9 * sY), 3, C_LEGS_LIGHT)
    spr.fillCircle(cx + 16, by + 33, int(4 * sX), C_LEGS_LIGHT)
    spr.drawPixel(cx + 16, by + 34, C_FRESNEL)

    # =========================================================================
    # LỚP 5: QUẦN LÁ XANH ĐẬM (Leaf Bloomers)
    # =========================================================================
    spr.fillEllipse(cx + 3, by + 14, int(13 * sX), int(10 * sY), C_PANTS_DARK)
    spr.fillEllipse(cx + 2, by + 13, int(11 * sX), int(8 * sY), C_PANTS_LIGHT)
    spr.drawRoundRect(cx - 5, by + 8, int(14 * sX), int(8 * sY), 3, C_CREST_TIP)

    # =========================================================================
    # LỚP 6: THÂN BÚP HÀNH TÂY (Onion Fairy Body)
    # =========================================================================
    spr.fillEllipse(cx + 1, by + 7, int(12 * sX), int(11 * sY), C_BODY_SHADOW)
    spr.fillEllipse(cx, by + 6, int(11 * sX), int(10 * sY), C_BODY_BASE)
    spr.fillEllipse(cx - 2, by + 5, int(8 * sX), int(7 * sY), C_FRESNEL)

    # =========================================================================
    # LỚP 7: CÁNH TIÊN PHÍA TRƯỚC (Near Wing)
    # =========================================================================
    frontFlap = math.sin(wingPhase + 0.2) * 5.0
    w2TipX = cx + 38
    w2TipY = by - 12 + int(frontFlap)
    w2MidX = cx + 28
    w2MidY = by + int(frontFlap * 0.7)
    spr.fillTriangle(cx + 8, by - 2, w2TipX, w2TipY, w2MidX, w2MidY, C_WING_GLASS)
    spr.fillTriangle(cx + 8, by, w2MidX, w2MidY, cx + 20, by + 8, C_WING_GLOW)
    spr.drawLine(cx + 8, by - 2, w2TipX, w2TipY, C_FRESNEL)
    spr.drawLine(cx + 8, by - 2, w2MidX, w2MidY, C_WING_VEIN)
    spr.fillCircle(w2TipX, w2TipY, 1, C_FRESNEL)

    # =========================================================================
    # LỚP 8: CÁNH TAY TRƯỚC (Right / Near Arm)
    # =========================================================================
    spr.fillTriangle(cx + 6, by + 6, cx + 8, by + 10, cx + 32, by + 10, C_BODY_BASE)
    spr.drawLine(cx + 6, by + 6, cx + 32, by + 9, C_FRESNEL)
    # 3 ngón tay búp măng dang rộng đón gió
    spr.fillCircle(cx + 34, by + 8, 1, C_BODY_BASE)
    spr.fillCircle(cx + 36, by + 10, 1, C_BODY_BASE)
    spr.fillCircle(cx + 33, by + 13, 1, C_BODY_BASE)

    # =========================================================================
    # LỚP 9: ĐẦU BÚP HÀNH TÂY & CHÓP XANH RỪNG VƯƠN CAO (Onion Sprout Crest)
    # =========================================================================
    hy = by - 8
    hrx = int(22 * sX)
    hry = int(22 * sY)
    # Khối đầu tròn mịn màng
    spr.drawEllipse(cx - 3, hy, hrx + 1, hry + 1, C_FRESNEL)
    spr.fillEllipse(cx - 3, hy, hrx, hry, C_BODY_BASE)
    spr.fillEllipse(cx + 5, hy + 4, int(14 * sX), int(12 * sY), C_BODY_SHADOW)
    spr.fillCircle(cx - 16, hy + 8, int(9 * sX), C_BODY_BASE)
    spr.fillCircle(cx - 7, hy + 14, int(8 * sX), C_BODY_BASE)

    # Chóp đầu nhọn uốn cong thanh thoát về phía sau-trên (Flame/Onion Sprout Crest)
    spr.fillTriangle(cx - 4, hy - 14, cx + 12, hy - 10, cx + 18, hy - 40, C_BODY_BASE)
    spr.fillTriangle(cx + 2, hy - 22, cx + 14, hy - 16, cx + 18, hy - 40, C_CREST_GLOW)
    spr.fillTriangle(cx + 6, hy - 26, cx + 16, hy - 22, cx + 18, hy - 40, C_CREST_TIP)
    # Đỉnh vuốt cong nhẹ
    spr.fillTriangle(cx + 12, hy - 36, cx + 18, hy - 40, cx + 16, hy - 44, C_CREST_DARK)
    # Các đường khía gân lá xanh rừng thẫm uốn lượn
    spr.drawLine(cx + 16, hy - 44, cx + 8, hy - 18, C_CREST_DARK)
    spr.drawLine(cx + 16, hy - 44, cx + 12, hy - 14, C_CREST_DARK)
    spr.drawLine(cx + 16, hy - 44, cx + 16, hy - 22, C_CREST_DARK)
    spr.drawFastVLine(cx + 15, hy - 38, 12, C_CREST_DARK)
    spr.drawLine(cx + 6, hy - 18, cx + 15, hy - 41, C_FRESNEL)

    # =========================================================================
    # LỚP 10: CẶP ĂNG-TEN KÉP XANH NGỌC VƯƠN CAO, CHÓP XANH LAM DẠ QUANG
    # (Cong uốn lượn hình cánh cung duyên dáng + Quán tính dao động)
    # =========================================================================
    # 10.1 Ăng-ten trái (Far Antenna)
    a1_x0, a1_y0 = cx - 11, hy - 12
    a1_x1, a1_y1 = cx - 21 + antSwayX, hy - 24 + antSwayY
    a1_x2, a1_y2 = cx - 23 + int(antSwayX * 1.2), hy - 34 + antSwayY
    a1_x3, a1_y3 = cx - 18 + int(antSwayX * 1.4), hy - 42 + antSwayY

    # Vẽ thân ăng-ten uốn cong nhiều đoạn
    spr.drawLine(a1_x0, a1_y0, a1_x1, a1_y1, C_ANT_STEM)
    spr.drawLine(a1_x0 + 1, a1_y0, a1_x1 + 1, a1_y1, C_BODY_BASE)
    spr.drawLine(a1_x1, a1_y1, a1_x2, a1_y2, C_ANT_MID)
    spr.drawLine(a1_x2, a1_y2, a1_x3, a1_y3, C_ANT_TIP)
    # Chóp dạ quang xanh lam
    spr.drawCircle(a1_x3, a1_y3, 3, C_ANT_GLOW)
    spr.fillCircle(a1_x3, a1_y3, 2, C_ANT_TIP)
    spr.drawPixel(a1_x3, a1_y3, C_FRESNEL)

    # 10.2 Ăng-ten phải (Near Antenna)
    a2_x0, a2_y0 = cx - 1, hy - 14
    a2_x1, a2_y1 = cx + 3 + antSwayX, hy - 26 + antSwayY
    a2_x2, a2_y2 = cx + 5 + int(antSwayX * 1.2), hy - 38 + antSwayY
    a2_x3, a2_y3 = cx + 1 + int(antSwayX * 1.4), hy - 46 + antSwayY

    spr.drawLine(a2_x0, a2_y0, a2_x1, a2_y1, C_ANT_STEM)
    spr.drawLine(a2_x0 + 1, a2_y0, a2_x1 + 1, a2_y1, C_FRESNEL)
    spr.drawLine(a2_x1, a2_y1, a2_x2, a2_y2, C_ANT_MID)
    spr.drawLine(a2_x2, a2_y2, a2_x3, a2_y3, C_ANT_TIP)
    # Chóp dạ quang xanh lam to hơn, bắt mắt
    spr.drawCircle(a2_x3, a2_y3, 4, C_ANT_GLOW)
    spr.fillCircle(a2_x3, a2_y3, 3, C_ANT_TIP)
    spr.fillCircle(a2_x3, a2_y3, 1, C_FRESNEL)

    # =========================================================================
    # LỚP 11: MÁ HỒNG ĐÀO TÁN MỊN & NỤ CƯỜI TÍ HON
    # =========================================================================
    spr.fillEllipse(cx - 19, hy + 9, 4, 3, C_BLUSH)
    spr.fillEllipse(cx + 6, hy + 12, 5, 3, C_BLUSH)
    # Khóe miệng nụ cười nhỏ nhắn ở góc dưới má trái
    spr.drawPixel(cx - 13, hy + 16, C_MOUTH)
    spr.drawPixel(cx - 12, hy + 17, C_MOUTH)
    spr.drawPixel(cx - 11, hy + 17, C_MOUTH)
    spr.drawPixel(cx - 10, hy + 16, C_MOUTH)

    # =========================================================================
    # LỚP 12: ĐÔI MẮT PHA LÊ TO TRÒN CHIẾM 35% KHUÔN MẶT VIỀN ĐEN SẮC NÉT
    # =========================================================================
    # 12.1 Mắt trái (Far eye trong góc 3/4)
    exL = cx - 17
    eyL = hy + 3
    if blink:
        spr.drawEllipse(exL, eyL + 2, 5, 2, C_EYE_RING)
    else:
        # Viền đen sắc nét
        spr.fillEllipse(exL, eyL, 6, 12, C_EYE_RING)
        # Mống mắt sapphire
        spr.fillEllipse(exL, eyL, 4, 10, C_IRIS_SAPPHIRE)
        # Mống mắt lam ngọc sáng
        spr.fillEllipse(exL, eyL + 1, 3, 7, C_IRIS_BRIGHT)
        # Vệt trăng khuyết đáy mắt
        spr.fillEllipse(exL, eyL + 5, 3, 4, C_IRIS_CAUSTIC)
        # Đáy mắt đồng tử đen thẳm
        spr.fillEllipse(exL, eyL, 3, 5, C_IRIS_DEEP)
        # 3 điểm bắt sáng mắt trái
        spr.fillRect(exL - 1, eyL - 3, 2, 2, C_WHITE)
        spr.drawPixel(exL + 1, eyL + 4, C_SPEC_SEC)
        spr.drawFastHLine(exL - 1, eyL + 6, 2, C_WHITE)

    # 12.2 Mắt phải (Near eye - Trực diện 35% khuôn mặt)
    exR = cx - 4
    eyR = hy + 6
    if blink:
        spr.drawEllipse(exR, eyR + 2, 9, 3, C_EYE_RING)
        spr.drawEllipse(exR, eyR + 3, 9, 3, C_EYE_RING)
    else:
        # Viền đen sắc nét nhung tuyền (Iconic thick black eye ring)
        spr.fillEllipse(exR, eyR, 11, 16, C_EYE_RING)
        # Mống mắt xanh sapphire
        spr.fillEllipse(exR, eyR, 9, 14, C_IRIS_SAPPHIRE)
        # Vùng xanh lam ngọc tươi sáng
        spr.fillEllipse(exR, eyR + 1, 8, 10, C_IRIS_BRIGHT)
        # Vệt trăng khuyết caustic phản quang đáy mắt
        spr.fillEllipse(exR, eyR + 6, 6, 4, C_IRIS_CAUSTIC)
        # Đồng tử xanh sapphire đen thẳm
        spr.fillEllipse(exR - 1, eyR - 1, 5, 8, C_IRIS_DEEP)
        # 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Specular Highlights)
        # 1. Đốm chính 2x2 góc 10h
        spr.fillRect(exR - 4, eyR - 5, 2, 2, C_WHITE)
        spr.drawPixel(exR - 3, eyR - 6, C_WHITE)
        # 2. Đốm phụ 1x1 góc 4h
        spr.drawPixel(exR + 2, eyR + 5, C_SPEC_SEC)
        # 3. Vệt trăng khuyết đáy mắt (Caustic crescent highlights)
        spr.drawFastHLine(exR - 3, eyR + 7, 4, C_WHITE)
        spr.drawFastHLine(exR - 2, eyR + 8, 2, C_SPEC_SEC)

    # =========================================================================
    # LỚP 13: BỤI BÀO TỬ RỪNG XANH PHÁT QUANG (Forest Magic Spores ✨)
    # =========================================================================
    spr.drawFastHLine(cx - 24, by + 16, 3, C_STAR_GOLD)
    spr.drawFastVLine(cx - 23, by + 15, 3, C_STAR_GOLD)
    spr.drawPixel(cx - 23, by + 16, C_WHITE)
    spr.drawFastHLine(cx + 28, by - 28, 3, C_ANT_GLOW)
    spr.drawFastVLine(cx + 29, by - 29, 3, C_ANT_GLOW)
    spr.drawPixel(cx + 29, by - 28, C_WHITE)
    spr.drawPixel(cx - 18, by - 22, C_MAGIC_SPORE)
    spr.drawPixel(cx + 22, by + 26, C_MAGIC_SPORE)

def main():
    w, h = 172, 320
    img = Image.new("RGB", (w, h), (10, 22, 14))
    draw = ImageDraw.Draw(img)

    canvas = MockScaledCanvas(draw, 86, 160, scale=1.0)
    drawCelebiForestFairy(canvas, 86, 150, angle=0.0, blink=False)
    img.save("tools/celebi_preview_1x.png")

    img2x = Image.new("RGB", (344, 640), (10, 22, 14))
    draw2x = ImageDraw.Draw(img2x)
    canvas2x = MockScaledCanvas(draw2x, 172, 320, scale=2.0)
    drawCelebiForestFairy(canvas2x, 172, 300, angle=0.0, blink=False)
    img2x.save("tools/celebi_preview_2x.png")

    print("Rendered preview images successfully!")

if __name__ == "__main__":
    main()
