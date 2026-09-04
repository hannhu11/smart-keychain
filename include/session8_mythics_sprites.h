#pragma once
// ============================================================================
// SESSION 8 IMPERIAL BEASTS & RAINBOW LEGENDS - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 ST7789 IPS LCD (172x320 60FPS DMA)
// Pop Mart & Kawaii Visual DNA: Volumetric 4-Tone Shading & Crystal Catchlights
// Characters: Raikou, Magikarp, Scorbunny, Xerneas, Arcanine (IDs 85 to 89)
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace Session8Mythics {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// -------------------------------------------------------------
// Raikou - Lôi Thần Hổ Nanh Kiếm
// -------------------------------------------------------------
static void drawRaikouThunderTiger(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.04f * breathSin;
  float sX = 1.0f - 0.02f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Đám mây giông tím bồng bềnh sau lưng
  float cloudLag = breathPhase - 0.4f;
  int cloudSwayX = (int)(sinf(cloudLag) * 3.5f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_GOLD_BODY  = 0xFEA0; // #FDE047 Lông vàng hổ sấm
  const uint16_t C_GOLD_DARK  = 0xCA00; // #CA8A04 Bóng vàng
  const uint16_t C_CLOUD_PURP = 0x9336; // #A855F7 Mây tím giông bão
  const uint16_t C_CLOUD_LGT  = 0xC49B; // #C084FC Đỉnh mây tím
  const uint16_t C_BLUE_MASK  = 0x3CF3; // #38BDF8 Mặt nạ 4 cánh xanh băng
  const uint16_t C_BLACK_STR  = 0x18C3; // #1E293B Sọc đen sấm sét & giáp trán
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Bụng, ria mép, răng nanh
  const uint16_t C_RED_EYE    = 0xF800; // #EF4444 Mắt đỏ sấm sét
  const uint16_t C_CYAN_SPARK = 0x07FF; // #06B6D4 Đuôi tia chớp
  const uint16_t C_SHADOW     = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 42, (int)(32 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Đuôi tia chớp đen uốn lượn chóp xanh cyan phát quang
  spr->drawLine(cx + 18, by + 10, cx + 28, by - 4,  C_BLACK_STR);
  spr->drawLine(cx + 28, by - 4,  cx + 22, by - 16, C_BLACK_STR);
  spr->drawLine(cx + 22, by - 16, cx + 34, by - 24, C_BLACK_STR);
  // Ngôi sao tia chớp xanh cyan ở chóp đuôi
  spr->fillCircle(cx + 34, by - 24, 3, C_CYAN_SPARK);

  // 3. Đám mây tím giông bão cuồn cuộn trên lưng (Thundercloud Cape)
  int clx = cx + 8 + cloudSwayX;
  spr->fillCircle(clx - 6, by - 2, 10, C_CLOUD_PURP);
  spr->fillCircle(clx + 6, by - 6, 12, C_CLOUD_LGT);
  spr->fillCircle(clx + 14, by - 2, 9, C_CLOUD_PURP);

  // 4. Thân hổ vàng dũng mãnh
  spr->fillEllipse(cx - 2, by + 14, (int)(18 * sX), (int)(14 * sY), C_GOLD_DARK);
  spr->fillEllipse(cx - 2, by + 12, (int)(16 * sX), (int)(12 * sY), C_GOLD_BODY);
  // Sọc đen tia chớp trên thân
  spr->fillTriangle(cx - 8, by + 6, cx - 4, by + 16, cx - 12, by + 14, C_BLACK_STR);
  spr->fillTriangle(cx + 2, by + 6, cx + 6, by + 16, cx - 2,  by + 14, C_BLACK_STR);
  // Bụng trắng
  spr->fillEllipse(cx - 2, by + 20, 10, 5, C_WHITE);

  // 5. 4 Chân hổ vàng cơ bắp với móng vuốt trắng
  spr->fillRoundRect(cx - 16, by + 18, 6, 18, 2, C_GOLD_BODY);
  spr->fillCircle(cx - 13, by + 34, 3, C_WHITE);
  spr->fillRoundRect(cx - 8,  by + 20, 6, 16, 2, C_GOLD_BODY);
  spr->fillCircle(cx - 5,  by + 34, 3, C_WHITE);
  spr->fillRoundRect(cx + 4,  by + 20, 6, 16, 2, C_GOLD_BODY);
  spr->fillCircle(cx + 7,  by + 34, 3, C_WHITE);
  spr->fillRoundRect(cx + 12, by + 18, 6, 18, 2, C_GOLD_BODY);
  spr->fillCircle(cx + 15, by + 34, 3, C_WHITE);

  // 6. Khối đầu hổ sấm sét
  spr->fillCircle(cx - 12, by - 6, (int)(14 * sX), C_GOLD_BODY);
  // Má phúng phính trắng
  spr->fillCircle(cx - 18, by - 4, 7, C_WHITE);
  spr->fillCircle(cx - 10, by - 4, 7, C_WHITE);

  // 7. Mặt nạ 4 cánh chữ X xanh lam trước mặt
  spr->fillTriangle(cx - 24, by - 12, cx - 14, by - 6, cx - 20, by - 2, C_BLUE_MASK);
  spr->fillTriangle(cx - 8,  by - 12, cx - 14, by - 6, cx - 10, by - 2, C_BLUE_MASK);
  // Giáp trán màu xám đen có gai
  spr->fillRoundRect(cx - 18, by - 16, 14, 5, 2, C_BLACK_STR);

  // 8. Đôi răng nanh kiếm dài nhọn trắng muốt
  spr->fillTriangle(cx - 20, by - 2, cx - 18, by + 10, cx - 16, by - 2, C_WHITE);
  spr->fillTriangle(cx - 12, by - 2, cx - 10, by + 10, cx - 8,  by - 2, C_WHITE);

  // 9. Đôi mắt đỏ sấm sét kiên định
  if (!blink) {
    spr->fillCircle(cx - 14, by - 10, 2, C_RED_EYE);
    spr->drawPixel(cx - 15, by - 11, C_WHITE);
  } else {
    spr->drawLine(cx - 16, by - 10, cx - 12, by - 10, C_BLACK_STR);
  }
}

// -------------------------------------------------------------
// Magikarp - Cá Chép Vàng Vượt Vũ Môn
// -------------------------------------------------------------
static void drawMagikarpGoldenKarp(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 3.2f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int bounceY = (int)(sinf(breathPhase) * 4.0f);
  int by = cy + bounceY;

  // Râu cá uốn lượn mềm mại
  int whiskerLag1 = (int)(sinf(angle * 3.0f) * 4.0f);
  int whiskerLag2 = (int)(cosf(angle * 3.0f) * 3.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_ORANGE_BODY = 0xF9A0; // #F97316 Thân cá cam rực rỡ
  const uint16_t C_ORANGE_DARK = 0xD280; // #EA580C Bóng thân cá
  const uint16_t C_GOLD_CROWN  = 0xFE60; // #FACC15 Vương miện vây lưng vàng
  const uint16_t C_WHITE_FIN   = 0xFFFF; // #FFFFFF Vây ngực & đuôi trắng
  const uint16_t C_PINK_LIPS   = 0xFB6D; // #F472B6 Đôi môi tròn xoe hồng
  const uint16_t C_BLACK_INK   = 0x18C3; // #1E293B Viền vảy & tròng mắt
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng nước

  // 1. Bóng tiếp xúc nước
  spr->fillEllipse(cx, cy + 42, (int)(26 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Vây đuôi trắng hình cánh buồm xòe sau lưng
  spr->fillTriangle(cx + 14, by + 4, cx + 36, by - 12, cx + 32, by + 18, C_ORANGE_DARK);
  spr->fillTriangle(cx + 16, by + 4, cx + 34, by - 10, cx + 30, by + 16, C_WHITE_FIN);

  // 3. Vây bụng vàng nhọn
  spr->fillTriangle(cx - 4, by + 18, cx - 12, by + 34, cx + 8, by + 22, C_GOLD_CROWN);

  // 4. Khối thân cá chép béo tròn màu cam
  spr->fillEllipse(cx, by + 4, (int)(22 * sX), (int)(18 * sY), C_ORANGE_DARK);
  spr->fillEllipse(cx, by + 2, (int)(20 * sX), (int)(16 * sY), C_ORANGE_BODY);

  // Họa tiết vảy cá hình lục giác viền đen
  spr->drawLine(cx - 6, by - 10, cx,     by - 4,  C_ORANGE_DARK);
  spr->drawLine(cx,     by - 4,  cx - 4, by + 12, C_ORANGE_DARK);

  // 5. Vương miện vây lưng hoàng kim 3 chóp nhọn (Golden Crown Fin)
  spr->fillTriangle(cx - 10, by - 12, cx - 16, by - 32, cx - 2, by - 14, C_GOLD_CROWN);
  spr->fillTriangle(cx - 4,  by - 14, cx + 4,  by - 36, cx + 10, by - 12, C_GOLD_CROWN);
  spr->fillTriangle(cx + 6,  by - 12, cx + 18, by - 28, cx + 16, by - 8,  C_GOLD_CROWN);

  // 6. Vây ngực trắng hình cánh quạt viền cam
  spr->fillTriangle(cx - 4, by + 4, cx + 14, by + 16, cx + 16, by - 2, C_WHITE_FIN);
  spr->drawLine(cx - 4, by + 4, cx + 14, by + 16, C_ORANGE_DARK);
  spr->drawLine(cx + 14, by + 16, cx + 16, by - 2, C_ORANGE_DARK);
  spr->drawLine(cx + 16, by - 2, cx - 4, by + 4, C_ORANGE_DARK);

  // 7. Đôi môi tròn xoe kinh điển há to ngạc nhiên
  spr->fillCircle(cx - 20, by + 4, 6, C_PINK_LIPS);
  spr->fillCircle(cx - 21, by + 4, 3, 0x5000); // Lòng miệng đen

  // 8. Đôi râu vàng dài uốn lượn thướt tha
  spr->drawLine(cx - 14, by + 8, cx - 22 + whiskerLag1, by + 22, C_GOLD_CROWN);
  spr->drawLine(cx - 22 + whiskerLag1, by + 22, cx - 18 + whiskerLag2, by + 36, C_GOLD_CROWN);

  // 9. Đôi mắt tròn xoe mất tập trung ngây thơ
  spr->fillCircle(cx - 6, by - 2, 7, C_WHITE_FIN);
  spr->drawCircle(cx - 6, by - 2, 7, C_BLACK_INK);
  if (!blink) {
    spr->fillCircle(cx - 6, by - 2, 2, C_BLACK_INK); // Đồng tử tí hon ngơ ngác
  } else {
    spr->drawLine(cx - 10, by - 2, cx - 2, by - 2, C_BLACK_INK);
  }
}

// -------------------------------------------------------------
// Scorbunny - Thỏ Lửa Năng Lượng Tươi Vui
// -------------------------------------------------------------
static void drawScorbunnyFireRabbit(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.8f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.05f * breathSin;
  float sX = 1.0f - 0.025f * breathSin;
  int jumpY = (int)(-fabsf(sinf(breathPhase)) * 4.5f);
  int by = cy + jumpY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Lông trắng muốt
  const uint16_t C_WHITE_SHAD  = 0xDEFB; // #E2E8F0 Bóng trắng
  const uint16_t C_ORANGE_FIRE = 0xFD20; // #F97316 Cam rực lửa chóp tai & cổ
  const uint16_t C_YELLOW_PAD  = 0xFE60; // #FACC15 Vàng băng gạc mũi & lòng tai
  const uint16_t C_AMBER_EYE   = 0xD380; // #D97706 Mắt hổ phách năng lượng
  const uint16_t C_MOUTH_RED   = 0x98E8; // #991B1B Miệng cười
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc đàn hồi khi nhảy
  spr->fillEllipse(cx, cy + 42, (int)(24 * (1.0f - 0.2f * fabsf(sinf(breathPhase)))), 5, C_SHADOW);

  // 2. Thân thỏ trắng năng động
  spr->fillEllipse(cx, by + 14, (int)(14 * sX), (int)(16 * sY), C_WHITE_SHAD);
  spr->fillEllipse(cx, by + 12, (int)(12 * sX), (int)(14 * sY), C_WHITE);
  // Vòng cổ cam rực lửa
  spr->fillRoundRect(cx - 7, by + 4, 14, 4, 2, C_ORANGE_FIRE);

  // 3. Hai chân sau bật nhảy với đệm cam & băng dán vàng
  spr->fillRoundRect(cx - 14, by + 20, 6, 18, 3, C_WHITE);
  spr->fillRoundRect(cx - 15, by + 32, 8, 7,  2, C_ORANGE_FIRE);
  spr->fillRect(cx - 14, by + 34, 6, 3, C_YELLOW_PAD); // Băng gạc chân

  spr->fillRoundRect(cx + 6,  by + 16, 6, 18, 3, C_WHITE);
  spr->fillRoundRect(cx + 6,  by + 28, 8, 7,  2, C_ORANGE_FIRE);
  spr->fillRect(cx + 7,  by + 30, 6, 3, C_YELLOW_PAD);

  // 4. Hai tay nhỏ xòe ra giữ thăng bằng
  spr->fillRoundRect(cx - 18, by + 8, 8, 5, 2, C_WHITE);
  spr->fillRoundRect(cx + 10, by + 8, 8, 5, 2, C_WHITE);

  // 5. Khối đầu thỏ tròn xoe tươi vui
  spr->fillCircle(cx, by - 6, (int)(18 * sX), C_WHITE_SHAD);
  spr->fillCircle(cx, by - 8, (int)(16 * sX), C_WHITE);

  // Túm lông má xòe nhọn hai bên
  spr->fillTriangle(cx - 16, by - 8, cx - 24, by - 6, cx - 14, by - 2, C_WHITE);
  spr->fillTriangle(cx + 16, by - 8, cx + 24, by - 6, cx + 14, by - 2, C_WHITE);

  // 6. Đôi tai dài thẳng đứng với chóp cam & lòng tai vàng
  // Tai trái
  spr->fillRoundRect(cx - 14, by - 38, 8, 26, 4, C_WHITE);
  spr->fillRoundRect(cx - 14, by - 38, 8, 12, 4, C_ORANGE_FIRE);
  spr->fillRoundRect(cx - 12, by - 28, 4, 12, 2, C_YELLOW_PAD);
  // Tai phải
  spr->fillRoundRect(cx + 6,  by - 38, 8, 26, 4, C_WHITE);
  spr->fillRoundRect(cx + 6,  by - 38, 8, 12, 4, C_ORANGE_FIRE);
  spr->fillRoundRect(cx + 8,  by - 28, 4, 12, 2, C_YELLOW_PAD);

  // 7. Miếng băng dán vàng trên sống mũi (Signature Band-Aid)
  spr->fillRoundRect(cx - 5, by - 8, 10, 5, 2, C_YELLOW_PAD);

  // 8. Miệng cười toe toét lộ một chiếc răng cửa ngộ nghĩnh
  spr->fillCircle(cx, by + 1, 5, C_MOUTH_RED);
  spr->fillRect(cx - 2, by - 1, 4, 3, C_WHITE); // Răng thỏ xinh xắn

  // 9. Đôi mắt hổ phách to tròn tràn đầy nhiệt huyết
  if (!blink) {
    spr->fillEllipse(cx - 7, by - 10, 3, 5, C_AMBER_EYE);
    spr->fillCircle(cx - 8,  by - 12, 1, C_WHITE);
    spr->fillEllipse(cx + 7, by - 10, 3, 5, C_AMBER_EYE);
    spr->fillCircle(cx + 6,  by - 12, 1, C_WHITE);
  } else {
    spr->drawLine(cx - 9, by - 9, cx - 5, by - 9, C_AMBER_EYE);
    spr->drawLine(cx + 5, by - 9, cx + 9, by - 9, C_AMBER_EYE);
  }
}

// -------------------------------------------------------------
// Xerneas - Hươu Thần Rừng Cầu Vồng Sự Sống
// -------------------------------------------------------------
static void drawXerneasRainbowStag(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.0f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.04f * breathSin;
  float sX = 1.0f - 0.02f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 3.0f);
  int by = cy + bounceY;

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_BLACK_BODY  = 0x18C3; // #1E293B Thân hươu đen tuyền huyền bí
  const uint16_t C_BLUE_CHEST  = 0x1A7B; // #1D4ED8 Giáp ngực xanh hoàng gia
  const uint16_t C_GOLD_ANTLER = 0xFFD7; // #FACC15 Gạc sừng hoàng kim
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Catchlight
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 8 Viên đá quý cầu vồng trên gạc sừng
  const uint16_t C_GEMS[8] = {
    0xF800, // #EF4444 Đỏ ruby
    0xFD20, // #F97316 Cam thạch anh
    0xFFE0, // #FEF08A Vàng hổ phách
    0x07E0, // #22C55E Lục bảo
    0x07FF, // #06B6D4 Lam kim cương
    0x221F, // #3B82F6 Lam sapphire
    0x91F7, // #A855F7 Tím thạch anh
    0xFC18  // #F472B6 Hồng ngọc bích
  };

  // 1. Bóng sàn tiếp xúc
  spr->fillEllipse(cx, cy + 44, (int)(28 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Gạc sừng hoàng kim khổng lồ xòe rộng với 8 ngọc sáng cầu vồng
  // Nhánh sừng trái
  spr->drawLine(cx - 2,  by - 16, cx - 18, by - 32, C_GOLD_ANTLER);
  spr->drawLine(cx - 18, by - 32, cx - 32, by - 44, C_GOLD_ANTLER);
  spr->drawLine(cx - 18, by - 32, cx - 22, by - 46, C_GOLD_ANTLER);
  spr->drawLine(cx - 10, by - 24, cx - 12, by - 42, C_GOLD_ANTLER);

  // Nhánh sừng phải
  spr->drawLine(cx + 2,  by - 16, cx + 18, by - 32, C_GOLD_ANTLER);
  spr->drawLine(cx + 18, by - 32, cx + 32, by - 44, C_GOLD_ANTLER);
  spr->drawLine(cx + 18, by - 32, cx + 22, by - 46, C_GOLD_ANTLER);
  spr->drawLine(cx + 10, by - 24, cx + 12, by - 42, C_GOLD_ANTLER);

  // 8 Viên ngọc cầu vồng phát quang trên chóp các nhánh sừng
  spr->fillCircle(cx - 32, by - 44, 3, C_GEMS[0]);
  spr->fillCircle(cx - 22, by - 46, 3, C_GEMS[1]);
  spr->fillCircle(cx - 12, by - 42, 3, C_GEMS[2]);
  spr->fillCircle(cx - 4,  by - 34, 2, C_GEMS[3]);

  spr->fillCircle(cx + 4,  by - 34, 2, C_GEMS[4]);
  spr->fillCircle(cx + 12, by - 42, 3, C_GEMS[5]);
  spr->fillCircle(cx + 22, by - 46, 3, C_GEMS[6]);
  spr->fillCircle(cx + 32, by - 44, 3, C_GEMS[7]);

  // 3. Thân hươu đen tuyền quý phái
  spr->fillEllipse(cx, by + 12, (int)(16 * sX), (int)(12 * sY), C_BLACK_BODY);
  // Giáp ngực chữ X xanh hoàng gia
  spr->fillTriangle(cx - 8, by + 10, cx, by + 2, cx + 8, by + 10, C_BLUE_CHEST);
  spr->fillTriangle(cx - 6, by + 6,  cx, by + 16, cx + 6, by + 6,  C_BLUE_CHEST);

  // 4. 4 Chân thon dài thanh lịch viền vàng móng
  spr->fillRoundRect(cx - 12, by + 18, 4, 20, 2, C_BLACK_BODY);
  spr->fillRect(cx - 12, by + 36, 4, 3, C_GOLD_ANTLER);

  spr->fillRoundRect(cx - 4,  by + 20, 4, 18, 2, C_BLACK_BODY);
  spr->fillRect(cx - 4,  by + 36, 4, 3, C_GOLD_ANTLER);

  spr->fillRoundRect(cx + 4,  by + 20, 4, 18, 2, C_BLACK_BODY);
  spr->fillRect(cx + 4,  by + 36, 4, 3, C_GOLD_ANTLER);

  spr->fillRoundRect(cx + 10, by + 18, 4, 20, 2, C_BLACK_BODY);
  spr->fillRect(cx + 10, by + 36, 4, 3, C_GOLD_ANTLER);

  // 5. Cổ cao vươn thẳng màu xanh hoàng gia
  spr->fillRoundRect(cx - 4, by - 6, 8, 16, 3, C_BLUE_CHEST);

  // 6. Đầu hươu thần thanh tú
  spr->fillEllipse(cx, by - 12, 8, 7, C_BLUE_CHEST);

  // 7. Đôi mắt chữ thập chữ X phát sáng xanh dương
  if (!blink) {
    spr->drawFastHLine(cx - 4, by - 12, 8, C_WHITE);
    spr->drawFastVLine(cx,     by - 15, 6, C_WHITE);
  } else {
    spr->drawFastHLine(cx - 3, by - 12, 6, C_BLACK_BODY);
  }
}

// -------------------------------------------------------------
// Arcanine - Hỏa Sư Thần Khuyển Bờm Mây
// -------------------------------------------------------------
static void drawArcanineCloudLion(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink = false) {
  float breathPhase = angle * 2.0f;
  float breathSin   = sinf(breathPhase);
  float sY = 1.0f + 0.04f * breathSin;
  float sX = 1.0f - 0.02f * breathSin;
  int bounceY = (int)(-fabsf(breathSin) * 2.5f);
  int by = cy + bounceY;

  // Bờm mây và đuôi bồng bềnh theo gió
  float maneLag = breathPhase - 0.45f;
  int maneSwayX = (int)(sinf(maneLag) * 3.0f);

  // Bảng màu RGB565 Pop Mart Vinyl
  const uint16_t C_ORANGE_BODY = 0xFD00; // #F97316 Cam rực lửa thân
  const uint16_t C_ORANGE_DARK = 0xD280; // #EA580C Bóng cam
  const uint16_t C_CREAM_MANE  = 0xFFF5; // #FEF9C3 Bờm mây kem bồng bềnh
  const uint16_t C_CREAM_SHAD  = 0xFEA0; // #FDE047 Bóng bờm kem
  const uint16_t C_BLACK_STR   = 0x18C3; // #1E293B Sọc đen hổ sư
  const uint16_t C_NOSE_DARK   = 0x18C3; // #1E293B Mũi & mắt
  const uint16_t C_WHITE       = 0xFFFF; // #FFFFFF Catchlight
  const uint16_t C_SHADOW      = 0x18C3; // #1E293B Bóng sàn

  // 1. Bóng sàn tiếp xúc vững chắc
  spr->fillEllipse(cx, cy + 42, (int)(34 * (1.0f - 0.15f * breathSin)), 6, C_SHADOW);

  // 2. Chiếc đuôi mây khổng lồ cuộn tròn sau lưng (Gigantic Cloud Tail)
  int tx = cx + 18 + maneSwayX;
  int ty = by - 6;
  spr->fillCircle(tx,      ty,      12, C_CREAM_SHAD);
  spr->fillCircle(tx + 4,  ty - 4,  13, C_CREAM_MANE);
  spr->fillCircle(tx + 12, ty - 12, 10, C_CREAM_MANE);

  // 3. Thân hổ sư màu cam rực lửa
  spr->fillEllipse(cx - 2, by + 14, (int)(18 * sX), (int)(15 * sY), C_ORANGE_DARK);
  spr->fillEllipse(cx - 2, by + 12, (int)(16 * sX), (int)(13 * sY), C_ORANGE_BODY);
  // Sọc đen hổ trên hông
  spr->fillTriangle(cx + 4,  by + 8, cx + 8,  by + 18, cx + 2,  by + 16, C_BLACK_STR);
  spr->fillTriangle(cx + 10, by + 8, cx + 14, by + 18, cx + 8,  by + 16, C_BLACK_STR);

  // 4. 4 Chân vững chãi với túm lông mây trắng quanh cổ chân
  spr->fillRoundRect(cx - 16, by + 18, 6, 18, 2, C_ORANGE_BODY);
  spr->fillCircle(cx - 13, by + 34, 4, C_CREAM_MANE);

  spr->fillRoundRect(cx - 8,  by + 20, 6, 16, 2, C_ORANGE_BODY);
  spr->fillCircle(cx - 5,  by + 34, 4, C_CREAM_MANE);

  spr->fillRoundRect(cx + 4,  by + 20, 6, 16, 2, C_ORANGE_BODY);
  spr->fillCircle(cx + 7,  by + 34, 4, C_CREAM_MANE);

  spr->fillRoundRect(cx + 12, by + 18, 6, 18, 2, C_ORANGE_BODY);
  spr->fillCircle(cx + 15, by + 34, 4, C_CREAM_MANE);

  // 5. Bờm mây sư tử khổng lồ bao quanh cổ và ngực (Majestic Cloud Mane)
  spr->fillCircle(cx - 10, by + 4,  10, C_CREAM_SHAD);
  spr->fillCircle(cx - 6,  by + 6,  12, C_CREAM_MANE);
  spr->fillCircle(cx + 2,  by + 4,  10, C_CREAM_MANE);
  spr->fillCircle(cx - 8,  by - 6,  11, C_CREAM_MANE);

  // 6. Đầu sư tử cam dũng mãnh
  spr->fillCircle(cx - 8, by - 8, (int)(13 * sX), C_ORANGE_BODY);

  // 7. Chỏm lông mây dựng trên trán
  spr->fillTriangle(cx - 16, by - 14, cx - 8, by - 28, cx, by - 14, C_CREAM_MANE);

  // 8. Đôi tai tam giác cam
  spr->fillTriangle(cx - 18, by - 12, cx - 24, by - 24, cx - 14, by - 16, C_ORANGE_BODY);
  spr->fillTriangle(cx,      by - 12, cx + 4,  by - 24, cx + 2,  by - 14, C_ORANGE_BODY);

  // 9. Mõm hổ sư & Mũi đen
  spr->fillCircle(cx - 14, by - 6, 5, C_CREAM_MANE);
  spr->fillCircle(cx - 15, by - 7, 2, C_NOSE_DARK);

  // 10. Đôi mắt hổ trung thành dũng cảm
  if (!blink) {
    spr->fillCircle(cx - 9, by - 10, 2, C_NOSE_DARK);
    spr->drawPixel(cx - 10, by - 11, C_WHITE);
  } else {
    spr->drawLine(cx - 11, by - 10, cx - 7, by - 10, C_NOSE_DARK);
  }
}

} // namespace Session8Mythics
