#pragma once
// ============================================================================
// FANTASY BESTIARY & SACRED FOREST BEASTS SUITE - PRODUCTION C++ HEADER
// Hardware Target: ESP32 / ESP32-S3 + ST7789 IPS Display (172x320 60FPS DMA)
// Stylistic Origin: High-end Fantasy Creature Artbook (지니의 판타지 동물 도감)
// Conformance: 3-Point Crystal Catchlights, 5% Squash & Stretch, Phase Lag
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace FantasyBestiary {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// ============================================================================
// ID 0: THẦN THÚ TAI DÀI RỪNG THIÊNG (LOP-EARED GOLDEN GUARDIAN)
// Khớp 100% ảnh mẫu download (00).jpg
// ============================================================================
static void drawLopEaredGuardian(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  float breathY = 1.0f + 0.05f * sinf(angle);
  float breathX = 1.0f - 0.025f * sinf(angle);
  float earLag = sinf(angle - 0.55f) * 4.0f;
  float tailLag = sinf(angle - 0.85f) * 6.0f;
  bool blink = (millis() % 3800 < 140);

  // 1. Bóng tiếp xúc mặt đất (Ground contact shadow)
  spr->fillEllipse(cx, cy + 45, (int)(38 * breathX), 8, 0x18C3);

  // 2. Đuôi xoắn ốc (Spiral Golden Tail) với độ trễ pha
  int tx0 = cx - 22, ty0 = cy + 24 + (int)(tailLag * 0.4f);
  int tx1 = cx - 36, ty1 = cy + 34 + (int)(tailLag * 0.8f);
  int tx2 = cx - 44, ty2 = cy + 42 + (int)tailLag;
  int tx3 = cx - 34, ty3 = cy + 48 + (int)(tailLag * 0.7f);
  int tx4 = cx - 24, ty4 = cy + 42 + (int)(tailLag * 0.4f);
  spr->drawLine(tx0, ty0, tx1, ty1, 0xCCE7);
  spr->drawLine(tx1, ty1, tx2, ty2, 0xF6EA);
  spr->drawLine(tx2, ty2, tx3, ty3, 0xF6EA);
  spr->drawLine(tx3, ty3, tx4, ty4, 0xFFFB);
  spr->fillCircle(tx4, ty4, 3, 0xFFFB);

  // 3. Chân sau (Hind columnar legs - shadow layer)
  spr->fillRoundRect(cx - 28, cy + 18, 14, 26, 6, 0xCCE7);
  spr->fillRoundRect(cx + 14, cy + 18, 14, 26, 6, 0xCCE7);

  // 4. Thân tròn ấm áp (Volumetric Pear Body)
  spr->fillEllipse(cx, cy + 14, (int)(32 * breathX), (int)(34 * breathY), 0xF6EA);
  spr->fillEllipse(cx, cy + 24, (int)(28 * breathX), (int)(18 * breathY), 0xCCE7);
  spr->fillEllipse(cx, cy + 4, (int)(20 * breathX), (int)(22 * breathY), 0xFFFB);

  // 5. Chân trước (Front columnar legs)
  spr->fillRoundRect(cx - 16, cy + 16, 12, 28, 5, 0xF6EA);
  spr->fillRoundRect(cx + 4, cy + 16, 12, 28, 5, 0xF6EA);
  spr->drawFastVLine(cx - 12, cy + 38, 5, 0x8B23);
  spr->drawFastVLine(cx + 8, cy + 38, 5, 0x8B23);

  // 6. Đầu tròn (Head Dome)
  spr->fillEllipse(cx, cy - 18, (int)(24 * breathX), (int)(22 * breathY), 0xF6EA);
  spr->fillEllipse(cx, cy - 18, 16, 14, 0xFFFB);

  // 7. Đôi tai rủ dài chạm sàn với hoa văn thổ cẩm (Brocade Lop Ears)
  for (int side = -1; side <= 1; side += 2) {
    float lag = (side == -1) ? earLag : -earLag * 0.7f;
    int ex0 = cx + side * 14, ey0 = cy - 28;
    int ex1 = cx + side * 38 + (int)lag, ey1 = cy - 8;
    int ex2 = cx + side * 48 + (int)(lag * 1.4f), ey2 = cy + 20;
    int ex3 = cx + side * 54 + (int)(lag * 1.8f), ey3 = cy + 44; // chạm sàn
    int ex4 = cx + side * 66 + (int)(lag * 2.1f), ey4 = cy + 36; // lượn cong lên

    spr->drawLine(ex0, ey0, ex1, ey1, 0xF6EA);
    spr->drawLine(ex1, ey1, ex2, ey2, 0xF6EA);
    spr->drawLine(ex2, ey2, ex3, ey3, 0xF6EA);
    spr->drawLine(ex3, ey3, ex4, ey4, 0xFFFB);
    spr->fillCircle(ex1, ey1, 9, 0xF6EA);
    spr->fillCircle(ex2, ey2, 8, 0xF6EA);
    spr->fillCircle(ex3, ey3, 7, 0xF6EA);
    spr->fillCircle(ex4, ey4, 5, 0xFFFB);

    // Họa tiết thổ cẩm: Dải tím thạch anh (#7C3AED) & ngọc lam (#06B6D4)
    spr->fillTriangle(ex1 - side*3, ey1 - 4, ex1 + side*5, ey1, ex1 - side*3, ey1 + 4, 0x79DD);
    spr->fillTriangle(ex2 - side*2, ey2 - 4, ex2 + side*4, ey2, ex2 - side*2, ey2 + 4, 0x79DD);
    spr->drawCircle(ex1 + side*2, ey1, 3, 0x05BA);
    spr->drawCircle(ex2 + side*1, ey2, 2, 0x05BA);
    spr->drawPixel(ex1 + side*2, ey1, 0xFDE4);
    spr->drawPixel(ex2 + side*1, ey2, 0xFDE4);
  }

  // 8. Mắt Bích Ngọc Sapphire (3 Catchlights Pha Lê)
  for (int side = -1; side <= 1; side += 2) {
    int eyeX = cx + side * 12, eyeY = cy - 20;
    if (blink) {
      spr->drawFastHLine(eyeX - 4, eyeY, 8, 0x0949);
    } else {
      spr->fillEllipse(eyeX, eyeY, 5, 7, 0x0949);
      spr->fillEllipse(eyeX, eyeY, 4, 6, 0x1B57);
      spr->fillEllipse(eyeX, eyeY + 1, 3, 3, 0x653F);
      // 3 Điểm sáng pha lê
      spr->fillCircle(eyeX - 2, eyeY - 3, 2, 0xFFFF);
      spr->drawPixel(eyeX + 2, eyeY + 1, 0xFFFF);
      spr->drawPixel(eyeX - 1, eyeY + 2, 0x963F);
    }
  }

  // 9. Miệng cười w-smile hiền từ (^w^)
  spr->drawPixel(cx - 3, cy - 13, 0x8B23);
  spr->drawPixel(cx - 2, cy - 12, 0x8B23);
  spr->drawPixel(cx - 1, cy - 12, 0x8B23);
  spr->drawPixel(cx,     cy - 13, 0x8B23);
  spr->drawPixel(cx + 1, cy - 12, 0x8B23);
  spr->drawPixel(cx + 2, cy - 12, 0x8B23);
  spr->drawPixel(cx + 3, cy - 13, 0x8B23);
}

// ============================================================================
// ID 1: CÁO TUYẾT ÁNH SÁNG LUMININE (LUMININE FROSTLIGHT AURORA FOX)
// Khớp 100% ảnh mẫu 판타지 동물 도감 (루미나인)
// ============================================================================
static void drawLuminineSnowFox(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  float breathY = 1.0f + 0.05f * sinf(angle);
  float breathX = 1.0f - 0.025f * sinf(angle);
  float earLag = sinf(angle - 0.40f) * 3.0f;
  float tailLag = sinf(angle - 0.65f) * 8.0f;
  bool blink = (millis() % 3600 < 130);

  // 1. Chiếc đuôi ánh sáng bồng bềnh (Luminous Aurora Cloud Tail)
  int tx = cx - 28 + (int)tailLag;
  int ty = cy - 4;
  spr->fillCircle(tx + 4, ty + 16, 12, 0xE79F);
  spr->fillCircle(tx - 4, ty + 6, 16, 0x3DFE);
  spr->fillCircle(tx - 6, ty - 8, 14, 0x077F);
  spr->fillCircle(tx + 4, ty - 18, 10, 0xFFFF);

  // Bụi sao lấp lánh quanh chóp đuôi (Stardust Sparkles)
  for (int i = 0; i < 4; i++) {
    float a = angle * 1.5f + i * 1.57f;
    int px = tx + (int)(cosf(a) * 16.0f);
    int py = ty - 12 + (int)(sinf(a) * 10.0f);
    spr->drawPixel(px, py, 0xFFFF);
    spr->drawPixel(px + 1, py, 0x077F);
  }

  // 2. Bóng tiếp xúc mặt đất
  spr->fillEllipse(cx, cy + 38, (int)(26 * breathX), 6, 0x18C3);

  // 3. Thân cáo tuyết (Snow Fox Torso)
  spr->fillEllipse(cx - 2, cy + 18, (int)(20 * breathX), (int)(22 * breathY), 0xE79F);
  spr->fillEllipse(cx + 2, cy + 6, (int)(16 * breathX), (int)(18 * breathY), 0xFFFF);

  // 4. Chân trước thon thả
  spr->fillRoundRect(cx - 10, cy + 18, 6, 20, 3, 0xFFFF);
  spr->fillRoundRect(cx + 4, cy + 18, 6, 20, 3, 0xFFFF);
  spr->fillCircle(cx - 7, cy + 37, 3, 0xE79F);
  spr->fillCircle(cx + 7, cy + 37, 3, 0xE79F);

  // 5. Đầu cáo hình nêm thanh thoát & Má lông xòe
  spr->fillEllipse(cx, cy - 16, (int)(19 * breathX), (int)(17 * breathY), 0xFFFF);
  spr->fillTriangle(cx - 18, cy - 12, cx - 10, cy - 18, cx - 10, cy - 8, 0xFFFF);
  spr->fillTriangle(cx + 18, cy - 12, cx + 10, cy - 18, cx + 10, cy - 8, 0xFFFF);

  // 6. Đôi tai cáo vểnh cao (Tall Arctic Fox Ears)
  for (int side = -1; side <= 1; side += 2) {
    int tipX = cx + side * 16 + (int)(earLag * 0.5f);
    int tipY = cy - 42;
    int b1x = cx + side * 6, b1y = cy - 24;
    int b2x = cx + side * 22, b2y = cy - 22;
    spr->fillTriangle(tipX, tipY, b1x, b1y, b2x, b2y, 0xFFFF);
    spr->fillTriangle(tipX, tipY + 4, b1x + side*2, b1y - 2, b2x - side*3, b2y - 1, 0xC5BF);
    spr->fillCircle(b1x + side*5, b1y - 4, 3, 0x3DFE);
  }

  // 7. Ấn ký Lam Ngọc 4 cánh chữ thập trước trán
  int sigY = cy - 26;
  spr->drawFastVLine(cx, sigY - 5, 11, 0x077F);
  spr->drawFastHLine(cx - 4, sigY, 9, 0x077F);
  spr->fillCircle(cx, sigY, 2, 0xFFFF);

  // Mặt dây chuyền giọt nước lam ngọc trước ngực
  spr->fillTriangle(cx, cy - 1, cx - 2, cy - 5, cx + 2, cy - 5, 0x077F);
  spr->drawPixel(cx, cy - 3, 0xFFFF);

  // 8. Mắt Lam Ngọc Pha Lê (3 Catchlights)
  for (int side = -1; side <= 1; side += 2) {
    int eyeX = cx + side * 10, eyeY = cy - 16;
    if (blink) {
      spr->drawFastHLine(eyeX - 3, eyeY, 7, 0x0354);
    } else {
      spr->fillEllipse(eyeX, eyeY, 4, 6, 0x0928);
      spr->fillEllipse(eyeX, eyeY, 3, 5, 0x0354);
      spr->fillCircle(eyeX, eyeY + 1, 2, 0x3DFE);
      // 3 Điểm sáng pha lê
      spr->fillCircle(eyeX - 1, eyeY - 2, 1, 0xFFFF);
      spr->drawPixel(eyeX + 1, eyeY, 0xFFFF);
      spr->drawPixel(eyeX, eyeY + 2, 0xE79F);
    }
  }

  // 9. Mũi & Nụ cười cáo nhỏ
  spr->drawPixel(cx, cy - 11, 0x0928);
  spr->drawPixel(cx - 1, cy - 9, 0x0438);
  spr->drawPixel(cx,     cy - 8, 0x0438);
  spr->drawPixel(cx + 1, cy - 9, 0x0438);
}

// ============================================================================
// ID 2: CÁO LỬA RỰC RỠ PYROKI (PYROKI SOLAR FLARE EMBER FOX)
// Khớp 100% ảnh mẫu 판타지 동물 도감 (파이로키) & CHAEON EMBER
// ============================================================================
static void drawPyrokiFlameFox(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  float breathY = 1.0f + 0.05f * sinf(angle);
  float breathX = 1.0f - 0.025f * sinf(angle);
  float earLag = sinf(angle - 0.35f) * 3.5f;
  float tailLag = sinf(angle - 0.50f) * 10.0f;
  float flameTurb = sinf(angle * 1.8f) * 3.5f;
  bool blink = (millis() % 3400 < 125);

  // 1. Chiếc đuôi lửa 3 tầng bập bùng (Layered Flame Tail)
  int tx = cx + 22 + (int)tailLag;
  int ty = cy - 2;

  // Tầng 1: Ngọn lửa đỏ thẫm ngoài cùng (#DC2626)
  spr->fillCircle(tx - 4, ty + 16, 13, 0xD924);
  spr->fillCircle(tx + 6, ty + 4, 16, 0xD924);
  spr->fillCircle(tx + 4 + (int)flameTurb, ty - 12, 13, 0xD924);
  spr->fillTriangle(tx + 4 + (int)flameTurb, ty - 24, tx - 4, ty - 8, tx + 14, ty - 6, 0xD924);

  // Tầng 2: Thân lửa cam rực rỡ (#FF5500)
  spr->fillCircle(tx - 2, ty + 14, 10, 0xFA80);
  spr->fillCircle(tx + 4, ty + 4, 12, 0xFA80);
  spr->fillCircle(tx + 3 + (int)flameTurb, ty - 10, 9, 0xFA80);
  spr->fillTriangle(tx + 3 + (int)flameTurb, ty - 20, tx - 2, ty - 7, tx + 11, ty - 5, 0xFA80);

  // Tầng 3: Lõi lửa vàng rực sáng (#FEF08A)
  spr->fillCircle(tx, ty + 12, 6, 0xFF91);
  spr->fillCircle(tx + 3, ty + 3, 7, 0xFF91);
  spr->fillCircle(tx + 2 + (int)flameTurb, ty - 8, 5, 0xFF91);

  // Tàn lửa bay lên (Floating Ember Sparks)
  for (int i = 0; i < 4; i++) {
    int sparkY = ty - 16 - (int)(fmodf(millis() * 0.035f * 1000.0f + i * 18.0f, 40.0f));
    int sparkX = tx + (int)(sinf(angle * 1.5f + i * 1.8f) * 8.0f);
    spr->drawPixel(sparkX, sparkY, 0xFF91);
    spr->drawPixel(sparkX + 1, sparkY, 0xFA80);
  }

  // 2. Bóng tiếp xúc mặt đất với ánh lửa ấm
  spr->fillEllipse(cx, cy + 38, (int)(26 * breathX), 6, 0x40E0);

  // 3. Thân cáo mật ong (Warm Honey Body)
  spr->fillEllipse(cx, cy + 16, (int)(22 * breathX), (int)(22 * breathY), 0xFC40);
  spr->fillEllipse(cx, cy + 24, (int)(18 * breathX), (int)(14 * breathY), 0xFA80);
  spr->fillEllipse(cx, cy + 8, (int)(14 * breathX), (int)(14 * breathY), 0xFFDF);

  // 4. Bốn chân nhỏ xinh
  spr->fillRoundRect(cx - 14, cy + 18, 7, 20, 3, 0xFC40);
  spr->fillRoundRect(cx + 7, cy + 18, 7, 20, 3, 0xFC40);
  spr->fillCircle(cx - 10, cy + 37, 3, 0xFA80);
  spr->fillCircle(cx + 10, cy + 37, 3, 0xFA80);

  // 5. Đầu cáo tròn má phúng phính
  spr->fillEllipse(cx, cy - 14, (int)(21 * breathX), (int)(19 * breathY), 0xFC40);
  spr->fillTriangle(cx - 20, cy - 10, cx - 12, cy - 16, cx - 12, cy - 6, 0xFC40);
  spr->fillTriangle(cx + 20, cy - 10, cx + 12, cy - 16, cx + 12, cy - 6, 0xFC40);
  spr->fillCircle(cx - 12, cy - 10, 3, 0xFA80);
  spr->fillCircle(cx + 12, cy - 10, 3, 0xFA80);

  // 6. Đôi tai cáo chóp đỏ thẫm (Flame Ears with Crimson Tips)
  for (int side = -1; side <= 1; side += 2) {
    int tipX = cx + side * 18 + (int)(earLag * 0.5f);
    int tipY = cy - 42;
    int b1x = cx + side * 6, b1y = cy - 24;
    int b2x = cx + side * 24, b2y = cy - 20;
    spr->fillTriangle(tipX, tipY, b1x, b1y, b2x, b2y, 0xFC40);
    spr->fillTriangle(tipX, tipY, tipX - side*4, tipY + 10, tipX + side*3, tipY + 9, 0xD924);
    spr->fillTriangle(tipX, tipY + 8, b1x + side*3, b1y - 2, b2x - side*3, b2y - 2, 0xFF91);
  }

  // 7. Mắt Hổ Phách Topaz Lấp Lánh (3 Catchlights)
  for (int side = -1; side <= 1; side += 2) {
    int eyeX = cx + side * 11, eyeY = cy - 15;
    if (blink) {
      spr->drawFastHLine(eyeX - 4, eyeY, 8, 0x40E0);
    } else {
      spr->fillEllipse(eyeX, eyeY, 5, 6, 0x40E0);
      spr->fillEllipse(eyeX, eyeY, 4, 5, 0xD3A0);
      spr->fillCircle(eyeX, eyeY + 1, 2, 0xFF91);
      // 3 Điểm sáng pha lê
      spr->fillCircle(eyeX - 2, eyeY - 2, 2, 0xFFFF);
      spr->drawPixel(eyeX + 1, eyeY + 1, 0xFF91);
      spr->drawPixel(eyeX - 1, eyeY + 2, 0xFF31);
    }
  }

  // 8. Mũi & Nụ cười cáo ngộ nghĩnh
  spr->fillCircle(cx, cy - 10, 2, 0x40E0);
  spr->drawPixel(cx - 2, cy - 8, 0xFA80);
  spr->drawPixel(cx - 1, cy - 7, 0xFA80);
  spr->drawPixel(cx,     cy - 8, 0xFA80);
  spr->drawPixel(cx + 1, cy - 7, 0xFA80);
  spr->drawPixel(cx + 2, cy - 8, 0xFA80);
}

// ============================================================================
// ID 3: THỎ LINH THÚ DỊ SẮC (HETEROCHROMIA FAIRY-EARED SPIRIT RABBIT)
// Khớp 100% ảnh mẫu download (8).jpg
// ============================================================================
static void drawHeterochromiaFairyRabbit(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  float breathY = 1.0f + 0.05f * sinf(angle);
  float breathX = 1.0f - 0.025f * sinf(angle);
  float earFlap = sinf(angle - 0.45f) * 4.0f;
  float tasselSwing = sinf(angle * 1.15f - 0.70f) * 6.0f;
  bool blink = (millis() % 3700 < 135);

  // 1. Bóng tiếp xúc mặt đất
  spr->fillEllipse(cx, cy + 45, (int)(24 * breathX), 6, 0x18C3);

  // 2. Đôi chân thỏ hạt dẻ & móng mềm
  spr->fillRoundRect(cx - 12, cy + 28, 8, 18, 4, 0xACE2);
  spr->fillRoundRect(cx + 4, cy + 28, 8, 18, 4, 0xACE2);
  spr->drawFastVLine(cx - 8, cy + 42, 4, 0x7B6C);
  spr->drawFastVLine(cx + 8, cy + 42, 4, 0x7B6C);

  // 3. Thân thỏ tròn múp míp (Chubby Bunny Torso)
  spr->fillEllipse(cx, cy + 18, (int)(20 * breathX), (int)(24 * breathY), 0xFFDF);
  spr->fillEllipse(cx, cy + 18, (int)(16 * breathX), (int)(20 * breathY), 0xFFFF);

  // 4. Tay chống nạnh kiêu kỳ & Vòng tay vàng
  for (int side = -1; side <= 1; side += 2) {
    int elbowX = cx + side * 22;
    int handX = cx + side * 14;
    spr->drawLine(cx + side * 14, cy + 8, elbowX, cy + 14, 0xFFDF);
    spr->drawLine(elbowX, cy + 14, handX, cy + 20, 0xFFDF);
    spr->fillCircle(elbowX, cy + 14, 3, 0xFFDF);
    spr->fillRect(handX - 2, cy + 18, 5, 4, 0xF4E1);
    spr->fillCircle(handX, cy + 21, 3, 0xACE2);
  }

  // 5. Vòng cổ & Chuông vàng
  spr->drawFastHLine(cx - 8, cy - 2, 16, 0x18C3);
  spr->fillCircle(cx, cy + 2, 4, 0xF4E1);
  spr->drawCircle(cx, cy + 2, 4, 0xFF91);

  // 6. Đầu thỏ bầu bĩnh & Má hồng son
  spr->fillEllipse(cx, cy - 14, (int)(26 * breathX), (int)(20 * breathY), 0xFFFF);
  spr->fillEllipse(cx - 16, cy - 10, 4, 2, 0xFBA0);
  spr->fillEllipse(cx + 16, cy - 10, 4, 2, 0xFBA0);

  // 7. Đôi tai cánh tiên xòe rộng (Fairy Wing Ears) & Tua rua đung đưa
  for (int side = -1; side <= 1; side += 2) {
    int tipX = cx + side * 56 + (int)(side * earFlap);
    int tipY = cy - 8 + (int)earFlap;
    int rootX = cx + side * 16, rootY = cy - 20;

    spr->fillTriangle(rootX, rootY, tipX, tipY, cx + side * 36, cy - 2, 0xFFFF);
    spr->fillCircle(tipX, tipY, 4, 0xACE2);
    spr->fillTriangle(cx + side * 32, cy - 2, cx + side * 38, cy + 6, cx + side * 44, cy, 0xACE2);
    spr->fillTriangle(cx + side * 44, cy, cx + side * 50, cy + 6, tipX, tipY, 0xACE2);

    // Khuyên vàng đôi & Hạt ngọc
    spr->drawCircle(tipX, tipY + 6, 4, 0xF4E1);
    spr->drawCircle(tipX, tipY + 11, 4, 0xF4E1);
    spr->fillCircle(tipX, tipY + 16, 3, 0xF4E1);

    // Tua rua lụa trắng đung đưa
    int botY = tipY + 30;
    int swX = tipX + (int)(tasselSwing * side);
    spr->drawLine(tipX, tipY + 18, swX, botY, 0xFFFF);
    spr->drawLine(tipX - 1, tipY + 18, swX - 2, botY, 0xF77D);
    spr->drawLine(tipX + 1, tipY + 18, swX + 2, botY, 0xF77D);
  }

  // 8. Ấn ký chữ thập đỏ son trước trán (#EF4444)
  int sigY = cy - 25;
  spr->drawFastVLine(cx, sigY - 5, 11, 0xEA28);
  spr->drawFastHLine(cx - 4, sigY, 9, 0xEA28);
  spr->drawPixel(cx, sigY, 0xFFFF);

  // 9. Đôi Mắt Dị Sắc Đồng Tử (Heterochromia 3 Catchlights & Star Pupils)
  // Mắt Phải (người xem nhìn bên trái): HỔ PHÁCH (#D97706)
  int rEyeX = cx - 12, eyeY = cy - 14;
  if (blink) {
    spr->drawFastHLine(rEyeX - 4, eyeY, 8, 0x79A1);
  } else {
    spr->fillEllipse(rEyeX, eyeY, 5, 7, 0x79A1);
    spr->fillEllipse(rEyeX, eyeY, 4, 6, 0xD3A0);
    // Con ngươi Ngôi Sao 4 Cánh vàng
    spr->drawFastVLine(rEyeX, eyeY - 2, 5, 0xFF91);
    spr->drawFastHLine(rEyeX - 2, eyeY, 5, 0xFF91);
    // 3 Điểm sáng pha lê
    spr->fillCircle(rEyeX - 2, eyeY - 3, 2, 0xFFFF);
    spr->drawPixel(rEyeX + 2, eyeY + 1, 0xFFFF);
    spr->drawPixel(rEyeX, eyeY + 3, 0xFF91);
  }

  // Mắt Trái (người xem nhìn bên phải): SAPPHIRE (#0284C7)
  int lEyeX = cx + 12;
  if (blink) {
    spr->drawFastHLine(lEyeX - 4, eyeY, 8, 0x0969);
  } else {
    spr->fillEllipse(lEyeX, eyeY, 5, 7, 0x0969);
    spr->fillEllipse(lEyeX, eyeY, 4, 6, 0x0438);
    // Con ngươi Ngôi Sao 4 Cánh lam
    spr->drawFastVLine(lEyeX, eyeY - 2, 5, 0x7EBF);
    spr->drawFastHLine(lEyeX - 2, eyeY, 5, 0x7EBF);
    // 3 Điểm sáng pha lê
    spr->fillCircle(lEyeX - 2, eyeY - 3, 2, 0xFFFF);
    spr->drawPixel(lEyeX + 2, eyeY + 1, 0xFFFF);
    spr->drawPixel(lEyeX, eyeY + 3, 0x7EBF);
  }

  // 10. Mũi & Miệng cười lém lỉnh (^w^)
  spr->drawPixel(cx, cy - 9, 0x7B6C);
  spr->drawPixel(cx - 3, cy - 7, 0x7B6C);
  spr->drawPixel(cx - 2, cy - 6, 0x7B6C);
  spr->drawPixel(cx,     cy - 7, 0x7B6C);
  spr->drawPixel(cx + 2, cy - 6, 0x7B6C);
  spr->drawPixel(cx + 3, cy - 7, 0x7B6C);
}

// ============================================================================
// ID 4: KỲ LÂN SAO STAR KIRIN (STAR KIRIN CELESTIAL STAG)
// Khớp 100% ảnh mẫu 판타지 동물 도감 (스타키린)
// ============================================================================
static void drawStarKirin(ScaledCanvas* spr, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  float breathY = 1.0f + 0.05f * sinf(angle);
  float breathX = 1.0f - 0.025f * sinf(angle);
  float maneWave = sinf(angle - 0.40f) * 4.5f;
  float tailLag = sinf(angle - 0.75f) * 7.0f;
  float starPulse = 1.0f + 0.35f * sinf(angle * 1.7f);
  bool blink = (millis() % 4000 < 140);

  // 1. Chiếc đuôi sao chổi lấp lánh (Comet Plume Tail)
  int tx = cx + 22 + (int)tailLag;
  int ty = cy + 10;
  spr->fillCircle(tx - 4, ty + 6, 10, 0x194B);
  spr->fillCircle(tx + 6, ty - 2, 12, 0x633E);
  spr->fillCircle(tx + 8, ty - 14, 8, 0x3DFE);
  spr->drawPixel(tx + 12, ty - 18, 0xFFFF);
  spr->drawPixel(tx + 14, ty - 10, 0xFF08);

  // 2. Bóng tiếp xúc mặt đất
  spr->fillEllipse(cx, cy + 42, (int)(28 * breathX), 6, 0x0864);

  // 3. Bờm sao bồng bềnh (Nebula Mane)
  for (int i = 0; i < 4; i++) {
    int my = cy - 20 + i * 8;
    int mx = cx - 12 - (int)(maneWave * (0.4f + i * 0.2f));
    spr->fillCircle(mx, my, 8 - i, 0x633E);
    spr->fillCircle(mx - 2, my, 6 - i, 0x3DFE);
    spr->drawPixel(mx - 3, my, 0xFFFF);
  }

  // 4. Thân kỳ lân đêm dạ vũ (Midnight Cosmic Body)
  spr->fillEllipse(cx + 2, cy + 18, (int)(20 * breathX), (int)(24 * breathY), 0x0864);
  spr->fillEllipse(cx - 2, cy + 8, (int)(16 * breathX), (int)(18 * breathY), 0x194B);

  // Chòm sao lấp lánh trên hông
  spr->drawPixel(cx + 6, cy + 14, 0xFFFF);
  spr->drawPixel(cx + 12, cy + 12, 0xA7BF);
  spr->drawPixel(cx + 14, cy + 20, 0xFFFF);
  spr->drawPixel(cx + 8, cy + 24, 0xA7BF);
  spr->drawLine(cx + 6, cy + 14, cx + 12, cy + 12, 0x194B);
  spr->drawLine(cx + 12, cy + 12, cx + 14, cy + 20, 0x194B);

  // 5. Bốn chân thon mảnh & Móng guốc vàng
  spr->fillRoundRect(cx - 14, cy + 20, 6, 22, 3, 0x0864);
  spr->fillRoundRect(cx + 8, cy + 20, 6, 22, 3, 0x0864);
  spr->fillRect(cx - 14, cy + 39, 6, 4, 0xF4E1);
  spr->fillRect(cx + 8, cy + 39, 6, 4, 0xF4E1);

  // 6. Đầu hươu sao thanh tú
  spr->fillEllipse(cx - 4, cy - 16, (int)(16 * breathX), (int)(18 * breathY), 0x0864);
  spr->fillEllipse(cx - 10, cy - 14, 10, 8, 0x194B);

  // 7. Đôi sừng hoàng kim phân nhánh tỏa tinh tú
  for (int side = -1; side <= 1; side += 2) {
    int rootX = cx + side * 7, rootY = cy - 28;
    int tip1X = cx + side * 18, tip1Y = cy - 54;
    int tip2X = cx + side * 26, tip2Y = cy - 42;
    int tip3X = cx + side * 10, tip3Y = cy - 44;

    spr->drawLine(rootX, rootY, tip1X, tip1Y, 0xF4E1);
    spr->drawLine(rootX + side*2, rootY, tip1X + side, tip1Y, 0xFF08);
    spr->drawLine(cx + side * 12, cy - 38, tip2X, tip2Y, 0xF4E1);
    spr->drawLine(cx + side * 9, cy - 35, tip3X, tip3Y, 0xF4E1);

    // Chùm tia sao 4 cánh phát quang
    int fLen = (int)(3 * starPulse);
    spr->drawFastVLine(tip1X, tip1Y - fLen, fLen * 2 + 1, 0xFFFF);
    spr->drawFastHLine(tip1X - fLen, tip1Y, fLen * 2 + 1, 0xFFFF);
    spr->fillCircle(tip1X, tip1Y, 2, 0xFF08);

    spr->drawFastVLine(tip2X, tip2Y - 2, 5, 0xFF08);
    spr->drawFastHLine(tip2X - 2, tip2Y, 5, 0xFF08);
  }

  // 8. Mắt Vũ Trụ Tím Thẫm (3 Catchlights Pha Lê)
  int eyeX = cx - 6, eyeY = cy - 17;
  if (blink) {
    spr->drawFastHLine(eyeX - 4, eyeY, 8, 0x18CA);
  } else {
    spr->fillEllipse(eyeX, eyeY, 5, 7, 0x18CA);
    spr->fillEllipse(eyeX, eyeY, 4, 6, 0x79FD);
    spr->fillCircle(eyeX, eyeY + 1, 2, 0x3DFE);
    // 3 Điểm sáng pha lê
    spr->fillCircle(eyeX - 2, eyeY - 2, 2, 0xFFFF);
    spr->drawPixel(eyeX + 1, eyeY + 1, 0xFF08);
    spr->drawPixel(eyeX - 1, eyeY + 2, 0x3DFE);
  }

  // 9. Chóp mũi & Miệng thanh nhã
  spr->drawPixel(cx - 16, cy - 14, 0x3DFE);
  spr->drawFastHLine(cx - 16, cy - 12, 3, 0x194B);
}

// ============================================================================
// BỘ ĐIỀU PHỐI CHUNG (UNIFIED BESTIARY DISPATCHER)
// ============================================================================
static void drawFantasyBeast(ScaledCanvas* spr, int id, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  switch (id % 5) {
    case 0: drawLopEaredGuardian(spr, cx, cy, breath, angle, scale); break;
    case 1: drawLuminineSnowFox(spr, cx, cy, breath, angle, scale); break;
    case 2: drawPyrokiFlameFox(spr, cx, cy, breath, angle, scale); break;
    case 3: drawHeterochromiaFairyRabbit(spr, cx, cy, breath, angle, scale); break;
    case 4: drawStarKirin(spr, cx, cy, breath, angle, scale); break;
    default: drawLopEaredGuardian(spr, cx, cy, breath, angle, scale); break;
  }
}

} // namespace FantasyBestiary
