# -*- coding: utf-8 -*-
import math
import os
from PIL import Image, ImageDraw

def hex_to_rgb(hex_str):
    hex_str = hex_str.lstrip('#')
    return (int(hex_str[0:2], 16), int(hex_str[2:4], 16), int(hex_str[4:6], 16))

COLORS = {
    "C_CREAM_LIGHT":      hex_to_rgb("#FFFDE0"),
    "C_CREAM_MAIN":       hex_to_rgb("#F6EC89"),
    "C_CREAM_SHADOW":     hex_to_rgb("#DDD06E"),
    "C_CREAM_DARK":       hex_to_rgb("#B8AA45"),
    "C_BROWN_LIGHT":      hex_to_rgb("#DEB275"),
    "C_BROWN_MAIN":       hex_to_rgb("#BD8D4E"),
    "C_BROWN_SHADOW":     hex_to_rgb("#966B33"),
    "C_BROWN_DARK":       hex_to_rgb("#6E4C1F"),
    "C_DARK_LIGHT":       hex_to_rgb("#5C586B"),
    "C_DARK_MAIN":        hex_to_rgb("#3E3A4B"),
    "C_DARK_SHADOW":      hex_to_rgb("#272432"),
    "C_DARK_DEEP":        hex_to_rgb("#16141F"),
    "C_BELLY_BAND":       hex_to_rgb("#EDE27C"),
    "C_BELLY_SHADOW":     hex_to_rgb("#C6BA50"),
    "C_CHEEK_PINK":       hex_to_rgb("#FF8095"),
    "C_CHEEK_LIGHT":      hex_to_rgb("#FFA8BA"),
    "C_CHEEK_SHADOW":     hex_to_rgb("#D8526B"),
    "C_EYE_BLACK":        hex_to_rgb("#14131A"),
    "C_EYE_RIM":          hex_to_rgb("#2A2735"),
    "C_EYE_CAUSTIC":      hex_to_rgb("#666276"),
    "C_WHITE":            hex_to_rgb("#FFFFFF"),
    "C_MOUTH_DARK":       hex_to_rgb("#7A1C2C"),
    "C_MOUTH_PINK":       hex_to_rgb("#DF546E"),
    "C_MOUTH_TONGUE":     hex_to_rgb("#FF8AA0"),
    "C_BERRY_GLOW":       hex_to_rgb("#BDF462"),
    "C_BERRY_MAIN":       hex_to_rgb("#72C42B"),
    "C_BERRY_SHADOW":     hex_to_rgb("#448416"),
    "C_BERRY_STEM":       hex_to_rgb("#55371C"),
    "C_STAR_SPARKLE":     hex_to_rgb("#FFF176"),
    "C_CONTACT_SHADOW":   hex_to_rgb("#121118")
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
        x1, y1 = self.sx(x + w), self.sy(y + h)
        if x0 > x1: x0, x1 = x1, x0
        if y0 > y1: y0, y1 = y1, y0
        rad = self.sr(r)
        self.draw.rounded_rectangle([x0, y0, x1, y1], radius=rad, fill=col)

    def drawRoundRect(self, x, y, w, h, r, col):
        x0, y0 = self.sx(x), self.sy(y)
        x1, y1 = self.sx(x + w), self.sy(y + h)
        if x0 > x1: x0, x1 = x1, x0
        if y0 > y1: y0, y1 = y1, y0
        rad = self.sr(r)
        self.draw.rounded_rectangle([x0, y0, x1, y1], radius=rad, outline=col)

    def fillRect(self, x, y, w, h, col):
        x0, y0 = self.sx(x), self.sy(y)
        x1, y1 = self.sx(x + w), self.sy(y + h)
        if x0 > x1: x0, x1 = x1, x0
        if y0 > y1: y0, y1 = y1, y0
        self.draw.rectangle([x0, y0, x1, y1], fill=col)

    def drawPixel(self, x, y, col):
        cx, cy = self.sx(x), self.sy(y)
        s = self.sr(1)
        if s <= 1:
            self.draw.point([cx, cy], fill=col)
        else:
            self.draw.rectangle([cx, cy, cx + s - 1, cy + s - 1], fill=col)

    def drawLine(self, x0, y0, x1, y1, col):
        self.draw.line([self.sx(x0), self.sy(y0), self.sx(x1), self.sy(y1)], fill=col, width=1)

    def fillEllipse(self, x, y, rx, ry, col):
        cx, cy, crx, cry = self.sx(x), self.sy(y), self.sr(rx), self.sr(ry)
        self.draw.ellipse([cx - crx, cy - cry, cx + crx, cy + cry], fill=col)

    def drawEllipse(self, x, y, rx, ry, col):
        cx, cy, crx, cry = self.sx(x), self.sy(y), self.sr(rx), self.sr(ry)
        self.draw.ellipse([cx - crx, cy - cry, cx + crx, cy + cry], outline=col)

    def fillTriangle(self, x0, y0, x1, y1, x2, y2, col):
        pts = [
            (self.sx(x0), self.sy(y0)),
            (self.sx(x1), self.sy(y1)),
            (self.sx(x2), self.sy(y2))
        ]
        self.draw.polygon(pts, fill=col)

def drawMorpekoMock(spr, cx, cy, angle, blink=False):
    C = COLORS
    # 1. Chuyển động vi vật lý hữu cơ
    breathPhase = angle * 2.2
    breathSin = math.sin(breathPhase)

    # Squash & Stretch 5%
    sY = 1.0 + 0.05 * breathSin
    sX = 1.0 - 0.025 * breathSin
    bounceY = int(-abs(breathSin) * 3.5)
    by = cy + bounceY

    # Nhịp nhai hạt micro-nibble
    chewY = math.sin(angle * 10.0) * 0.8
    chewOffset = int(round(chewY))

    # Hai tai nhỏ lúc lắc trễ pha 80ms (Delta Phi = 0.22 rad)
    earLag = breathPhase - 0.22
    earSwayX = int(round(math.sin(earLag) * 3.0))
    earSwayY = int(round(math.cos(earLag) * 1.5))

    # Hạt ánh sáng sao nhỏ lấp lánh quanh quả mọng
    spark1 = int(round(math.sin(angle * 12.0) * 3.0))
    spark2 = int(round(math.cos(angle * 15.0) * 3.0))
    spark3 = int(round(math.sin(angle * 18.0) * 2.5))

    # -------------------------------------------------------------
    # LAYER 0: BÓNG TIẾP XÚC CO GIÃN MỀM MẠI DƯỚI SÀN
    # -------------------------------------------------------------
    shadowW = int(48.0 * sX)
    shadowH = int(10.0 * sX)
    spr.fillEllipse(cx, cy + 52, shadowW, shadowH, C["C_CONTACT_SHADOW"])
    spr.fillEllipse(cx, cy + 52, int(shadowW * 0.65), int(shadowH * 0.6), (8, 7, 12))

    # -------------------------------------------------------------
    # LAYER 1: HAI CHÂN NGẮN HẠT ĐẬU (Bean feet)
    # -------------------------------------------------------------
    # Chân trái (viewer's left)
    spr.fillEllipse(cx - 16, by + 44, int(12 * sX), int(6 * sY), C["C_BELLY_SHADOW"])
    spr.fillEllipse(cx - 16, by + 43, int(11 * sX), int(5 * sY), C["C_BELLY_BAND"])
    spr.fillEllipse(cx - 17, by + 42, int(6 * sX), int(3 * sY), C["C_CREAM_LIGHT"])

    # Chân phải (viewer's right)
    spr.fillEllipse(cx + 16, by + 44, int(12 * sX), int(6 * sY), C["C_BELLY_SHADOW"])
    spr.fillEllipse(cx + 16, by + 43, int(11 * sX), int(5 * sY), C["C_BELLY_BAND"])
    spr.fillEllipse(cx + 15, by + 42, int(6 * sX), int(3 * sY), C["C_CREAM_LIGHT"])

    # -------------------------------------------------------------
    # LAYER 2: TAI HAMSTER 3D VỚI ĐỘ TRỄ PHA 80ms (Ears with Phase Lag)
    # -------------------------------------------------------------
    # Tai trái (Viewer's left: Nâu cà phê sữa, chếch trái ~20 độ, múi xòe sang trái)
    lx0, ly0 = cx - 18, by - 30
    lx_tip, ly_tip = cx - 30 + earSwayX, by - 68 + earSwayY
    # Cánh tai bầu dục
    spr.fillTriangle(lx0 - 8, ly0, lx_tip - 3, ly_tip, lx0 + 8, ly0 - 4, C["C_BROWN_MAIN"])
    spr.fillTriangle(lx0 - 6, ly0, lx_tip + 3, ly_tip, lx0 + 8, ly0 - 4, C["C_BROWN_MAIN"])
    spr.fillEllipse(lx_tip, ly_tip + 4, 7, 8, C["C_BROWN_MAIN"])
    # Múi xòe tai trái (side tuft)
    spr.fillTriangle(lx0 - 7, ly0 - 10, cx - 38 + earSwayX, by - 48 + earSwayY, lx0 - 2, ly0 - 22, C["C_BROWN_MAIN"])
    spr.fillTriangle(lx0 - 5, ly0 - 12, cx - 36 + earSwayX, by - 48 + earSwayY, lx0 - 2, ly0 - 20, C["C_BROWN_LIGHT"])
    # Lòng tai trái sâu
    spr.fillTriangle(lx0 - 2, ly0 - 4, lx_tip + 2, ly_tip + 10, lx0 + 5, ly0 - 6, C["C_BROWN_SHADOW"])
    spr.drawLine(lx0 - 7, ly0, lx_tip - 2, ly_tip + 4, C["C_BROWN_LIGHT"]) # Viền sáng

    # Tai phải (Viewer's right: Đen than, chếch phải ~20 độ, 2 múi xòe sang phải)
    rx0, ry0 = cx + 18, by - 30
    rx_tip, ry_tip = cx + 30 - earSwayX, by - 68 + earSwayY
    # Cánh tai bầu dục
    spr.fillTriangle(rx0 - 8, ry0 - 4, rx_tip - 3, ry_tip, rx0 + 8, ry0, C["C_DARK_MAIN"])
    spr.fillTriangle(rx0 - 8, ry0 - 4, rx_tip + 3, ry_tip, rx0 + 6, ry0, C["C_DARK_MAIN"])
    spr.fillEllipse(rx_tip, ry_tip + 4, 7, 8, C["C_DARK_MAIN"])
    # 2 Múi xòe tai phải (double side tufts)
    spr.fillTriangle(rx0 + 3, ry0 - 18, cx + 38 - earSwayX, by - 52 + earSwayY, rx0 + 6, ry0 - 27, C["C_DARK_MAIN"])
    spr.fillTriangle(rx0 + 4, ry0 - 8,  cx + 36 - earSwayX, by - 42 + earSwayY, rx0 + 5, ry0 - 17, C["C_DARK_MAIN"])
    spr.fillTriangle(rx0 + 4, ry0 - 17, cx + 36 - earSwayX, by - 51 + earSwayY, rx0 + 5, ry0 - 25, C["C_DARK_LIGHT"])
    # Lòng tai phải sâu
    spr.fillTriangle(rx0 - 5, ry0 - 6, rx_tip - 2, ry_tip + 10, rx0 + 2, ry0 - 4, C["C_DARK_SHADOW"])
    spr.drawLine(rx0 + 7, ry0, rx_tip + 2, ry_tip + 4, C["C_DARK_LIGHT"]) # Viền sáng

    # -------------------------------------------------------------
    # LAYER 3: THÂN HAMSTER TRÒN MŨM MĨM & PHÂN MẢNG 3 MÀU ĐẶC TRƯNG
    # -------------------------------------------------------------
    # Thân chính bo tròn hình hạt đậu / quả lê mũm mĩm Pop Mart
    # Nửa sườn trái: Nâu cà phê sữa
    spr.fillRoundRect(cx - 36, by - 32, 38, 72, 18, C["C_BROWN_MAIN"])
    spr.fillEllipse(cx - 16, by + 8, int(22 * sX), int(38 * sY), C["C_BROWN_MAIN"])
    spr.fillEllipse(cx - 26, by + 6, 10, 24, C["C_BROWN_LIGHT"]) # Đón sáng sườn trái

    # Nửa sườn phải: Đen than huyền bí
    spr.fillRoundRect(cx - 2, by - 32, 38, 72, 18, C["C_DARK_MAIN"])
    spr.fillEllipse(cx + 16, by + 8, int(22 * sX), int(38 * sY), C["C_DARK_MAIN"])
    spr.fillEllipse(cx + 26, by + 6, 10, 24, C["C_DARK_LIGHT"]) # Đón sáng sườn phải

    # Đáy bụng dưới và hông màu vàng kem mềm mại
    spr.fillRoundRect(cx - 24, by + 16, 48, 26, 12, C["C_BELLY_BAND"])
    spr.fillEllipse(cx, by + 34, int(24 * sX), int(8 * sY), C["C_BELLY_SHADOW"])
    spr.fillEllipse(cx, by + 32, int(22 * sX), int(7 * sY), C["C_BELLY_BAND"])

    # Mảng kem vani ở giữa (Central Cream Lightning Patch)
    spr.fillRoundRect(cx - 15, by - 32, 30, 70, 14, C["C_CREAM_MAIN"])
    spr.fillEllipse(cx, by - 12, int(17 * sX), int(22 * sY), C["C_CREAM_MAIN"])
    spr.fillEllipse(cx, by + 16, int(19 * sX), int(20 * sY), C["C_CREAM_MAIN"])

    # CÁC MÚI RĂNG CƯA TIA CHỚP (ZIGZAG LIGHTNING FLANGES):
    # --- Ranh giới Trái (Kem & Nâu) ---
    spr.fillTriangle(cx - 12, by - 30, cx - 22, by - 22, cx - 12, by - 15, C["C_CREAM_MAIN"]) # Zig trán trên
    spr.fillTriangle(cx - 13, by - 10, cx - 24, by - 2,  cx - 12, by + 6,  C["C_CREAM_MAIN"]) # Zig má dưới
    spr.fillTriangle(cx - 14, by + 12, cx - 25, by + 22, cx - 13, by + 30, C["C_CREAM_MAIN"]) # Zig eo hông

    # Nâu lấn sang Kem:
    spr.fillTriangle(cx - 22, by - 22, cx - 10, by - 15, cx - 13, by - 10, C["C_BROWN_MAIN"]) # Notch thái dương
    spr.fillTriangle(cx - 24, by - 2,  cx - 10, by + 6,  cx - 14, by + 12, C["C_BROWN_MAIN"]) # Notch nách

    # --- Ranh giới Phải (Kem & Đen) ---
    spr.fillTriangle(cx + 12, by - 30, cx + 22, by - 22, cx + 12, by - 15, C["C_CREAM_MAIN"]) # Zig trán trên
    spr.fillTriangle(cx + 13, by - 10, cx + 24, by - 2,  cx + 12, by + 6,  C["C_CREAM_MAIN"]) # Zig má dưới
    spr.fillTriangle(cx + 14, by + 12, cx + 25, by + 22, cx + 13, by + 30, C["C_CREAM_MAIN"]) # Zig eo hông

    # Đen lấn sang Kem:
    spr.fillTriangle(cx + 22, by - 22, cx + 10, by - 15, cx + 13, by - 10, C["C_DARK_MAIN"]) # Notch thái dương
    spr.fillTriangle(cx + 24, by - 2,  cx + 10, by + 6,  cx + 14, by + 12, C["C_DARK_MAIN"]) # Notch nách

    # Đón sáng vòm trán & bụng kem vani
    spr.fillEllipse(cx, by - 24, int(11 * sX), int(8 * sY), C["C_CREAM_LIGHT"])
    spr.fillEllipse(cx, by + 18, int(12 * sX), int(14 * sY), C["C_CREAM_LIGHT"])

    # -------------------------------------------------------------
    # LAYER 4: HAI MÁ TÚI ĐIỆN HỒNG ĐÀO TRÒN XOE CĂNG PHỒNG (Cheek Pouches)
    # -------------------------------------------------------------
    # Má trái (viewer's left) nằm trên nền nâu
    spr.fillCircle(cx - 28, by - 1, 11, C["C_CHEEK_SHADOW"])
    spr.fillCircle(cx - 28, by - 2, 11, C["C_CHEEK_PINK"])
    spr.fillCircle(cx - 29, by - 4, 7, C["C_CHEEK_LIGHT"])
    spr.drawPixel(cx - 30, by - 6, C["C_WHITE"])
    spr.drawPixel(cx - 31, by - 6, C["C_WHITE"])

    # Má phải (viewer's right) nằm trên nền đen
    spr.fillCircle(cx + 28, by - 1, 11, C["C_CHEEK_SHADOW"])
    spr.fillCircle(cx + 28, by - 2, 11, C["C_CHEEK_PINK"])
    spr.fillCircle(cx + 27, by - 4, 7, C["C_CHEEK_LIGHT"])
    spr.drawPixel(cx + 26, by - 6, C["C_WHITE"])
    spr.drawPixel(cx + 27, by - 6, C["C_WHITE"])

    # -------------------------------------------------------------
    # LAYER 5: ĐÔI MẮT PHA LÊ ĐEN LONG LANH 3 ĐIỂM BẮT SÁNG (Crystal Eyes)
    # -------------------------------------------------------------
    for eyeIdx in range(2):
        ex = (cx - 15) if eyeIdx == 0 else (cx + 15)
        ey = by - 13

        if blink:
            # Nhịp chớp mắt cong ngọt ngào
            spr.drawEllipse(ex, ey, 8, 3, C["C_EYE_BLACK"])
            spr.drawEllipse(ex, ey + 1, 8, 3, C["C_EYE_BLACK"])
            spr.drawLine(ex - 8 if eyeIdx == 0 else ex + 8, ey + 1, ex - 11 if eyeIdx == 0 else ex + 11, ey - 2, C["C_EYE_BLACK"])
        else:
            # Viền mí mắt sâu
            spr.fillCircle(ex, ey, 10, C["C_EYE_RIM"])
            # Tròng mắt pha lê đen
            spr.fillCircle(ex, ey, 9, C["C_EYE_BLACK"])
            # Cung phản xạ ánh sáng đáy mắt caustic
            spr.fillEllipse(ex, ey + 4, 6, 3, C["C_EYE_CAUSTIC"])

            # 3 ĐIỂM BẮT SÁNG PHA LÊ (3-Point Catchlights)
            # Điểm 1: Primary Keylight Specular (Lớn sáng, góc 10h)
            spr.fillCircle(ex - 3, ey - 3, 3, C["C_WHITE"])
            # Điểm 2: Secondary Caustic Bounce (Vừa, góc 4h)
            spr.fillCircle(ex + 3, ey + 3, 2, C["C_WHITE"])
            # Điểm 3: Tertiary Micro Glint (Hạt vi điểm, góc 2h)
            spr.drawPixel(ex + 4, ey - 1, C["C_WHITE"])

    # -------------------------------------------------------------
    # LAYER 6: MŨI NHỎ, MIỆNG CƯỜI CHÚM CHÍM & RĂNG THỎ VUÔNG XINH
    # -------------------------------------------------------------
    # Mũi chấm tròn nhỏ màu đen tuyền chính giữa
    spr.fillCircle(cx, by - 9, 2, C["C_EYE_BLACK"])

    # Miệng cười chúm chím mở rộng ngọt ngào
    # Khoang miệng đỏ vang sâu
    spr.fillRoundRect(cx - 9, by - 3, 18, 12, 6, C["C_MOUTH_DARK"])
    # Vòm miệng hồng anh đào
    spr.fillRoundRect(cx - 8, by - 2, 16, 10, 5, C["C_MOUTH_PINK"])
    # Chiếc lưỡi hồng đào nhỏ xinh
    spr.fillCircle(cx, by + 5, 5, C["C_MOUTH_TONGUE"])

    # Chiếc răng thỏ vuông màu trắng tinh khôi ở chính giữa hàm trên
    spr.fillRoundRect(cx - 3, by - 3, 6, 5, 1, C["C_WHITE"])
    spr.drawLine(cx - 3, by - 3, cx + 3, by - 3, C["C_MOUTH_DARK"])

    # -------------------------------------------------------------
    # LAYER 7: HAI BÀN TAY NHỎ XÍU ÔM QUẢ MỌNG / HẠT DẺ TRƯỚC NGỰC
    # -------------------------------------------------------------
    berryY = by + 20 + chewOffset

    # Tay trái (Nâu cà phê) duỗi ra ôm quả mọng
    spr.fillRoundRect(cx - 27, by + 10, 17, 12, 5, C["C_BROWN_MAIN"])
    spr.fillEllipse(cx - 15, by + 17, 8, 6, C["C_BROWN_MAIN"])

    # Tay phải (Đen than) duỗi ra ôm quả mọng
    spr.fillRoundRect(cx + 10, by + 10, 17, 12, 5, C["C_DARK_MAIN"])
    spr.fillEllipse(cx + 15, by + 17, 8, 6, C["C_DARK_MAIN"])

    # QUẢ MỌNG THẦN TIÊN CĂNG MỌNG (The Sacred Berry)
    # Đáy bóng quả mọng
    spr.fillCircle(cx, berryY + 1, 9, C["C_BERRY_SHADOW"])
    # Thân quả mọng xanh ngọc ngọt lành
    spr.fillCircle(cx, berryY, 8, C["C_BERRY_MAIN"])
    # Vùng đón sáng căng tròn
    spr.fillCircle(cx - 2, berryY - 2, 5, C["C_BERRY_GLOW"])
    # Điểm bóng sáng Pop Mart
    spr.drawPixel(cx - 3, berryY - 3, C["C_WHITE"])
    spr.drawPixel(cx - 2, berryY - 4, C["C_WHITE"])
    # Cuống hạt / lá nhỏ trên đỉnh quả mọng
    spr.fillRect(cx - 1, berryY - 9, 2, 3, C["C_BERRY_STEM"])
    spr.fillTriangle(cx - 1, berryY - 7, cx - 4, berryY - 8, cx - 2, berryY - 6, C["C_BERRY_MAIN"])

    # Hai bàn tay nhỏ xíu ôm chặt quả mọng (Paws clutching the berry)
    # Bàn tay trái hạt đậu (Nâu)
    spr.fillCircle(cx - 7, berryY + 1, 4, C["C_BROWN_MAIN"])
    spr.fillCircle(cx - 7, berryY, 3, C["C_BROWN_LIGHT"])

    # Bàn tay phải hạt đậu (Đen than)
    spr.fillCircle(cx + 7, berryY + 1, 4, C["C_DARK_MAIN"])
    spr.fillCircle(cx + 7, berryY, 3, C["C_DARK_LIGHT"])

    # -------------------------------------------------------------
    # LAYER 8: HẠT ÁNH SÁNG SAO NHỎ LẤP LÁNH QUANH QUẢ MỌNG (Star Sparkles)
    # -------------------------------------------------------------
    # Sao 1: Bên trái phía trên quả mọng
    sx1, sy1 = cx - 16 + spark1, berryY - 9 + spark2
    spr.drawLine(sx1 - 3, sy1, sx1 + 3, sy1, C["C_STAR_SPARKLE"])
    spr.drawLine(sx1, sy1 - 3, sx1, sy1 + 3, C["C_STAR_SPARKLE"])
    spr.drawPixel(sx1, sy1, C["C_WHITE"])

    # Sao 2: Bên phải phía trên quả mọng
    sx2, sy2 = cx + 17 + spark2, berryY - 7 + spark1
    spr.drawLine(sx2 - 3, sy2, sx2 + 3, sy2, C["C_STAR_SPARKLE"])
    spr.drawLine(sx2, sy2 - 3, sx2, sy2 + 3, C["C_STAR_SPARKLE"])
    spr.drawPixel(sx2, sy2, C["C_WHITE"])

    # Sao 3: Dưới đáy quả mọng
    sx3, sy3 = cx + 2 + spark3, berryY + 11 + spark1
    spr.drawLine(sx3 - 2, sy3, sx3 + 2, sy3, C["C_STAR_SPARKLE"])
    spr.drawLine(sx3, sy3 - 2, sx3, sy3 + 2, C["C_STAR_SPARKLE"])
    spr.drawPixel(sx3, sy3, C["C_WHITE"])

if __name__ == "__main__":
    W, H = 240, 280
    im = Image.new("RGB", (W, H), (15, 18, 28))
    draw = ImageDraw.Draw(im)
    spr = MockScaledCanvas(draw, W // 2, H // 2, scale=1.0)
    drawMorpekoMock(spr, W // 2, H // 2 - 5, angle=0.0, blink=False)
    out_path = os.path.join(os.path.dirname(__file__), "..", "data", "test_morpeko_render.png")
    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    im.save(out_path)
    print("Saved render test to:", out_path)
