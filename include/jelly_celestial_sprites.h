#pragma once
// ============================================================================
// JELLY DRAGON & CELESTIAL SPIRITS SUITE - PRODUCTION C++ SCALEDCANVAS HEADER
// Hardware Target: ESP32 / ESP32-C3 + ST7789P3 LCD (172x320 60FPS DMA)
// Stylistic Origin: 젤리드레곤 동물도감 & download (7).jpg
// ============================================================================
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites_data.h"

namespace JellyCelestial {
using ScaledCanvas = SpriteRenderer::ScaledCanvas;

// JELLY_DRAGON_LAVENDER - Thạch Long Tím Lavender (Bé Rồng Thạch Nho Pháp)
// =========================================================================
// THẠCH LONG TÍM LAVENDER (LAVENDER JELLY DRAGON - 젤리드레곤 포도맛)
// ScaledCanvas C++ Implementation - 100% Hardware Compatible
// =========================================================================
void drawJellyDragonLavender(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink) {
  // 1. Nhịp thở Squash & Stretch 5%
  float breathPhase = angle * 2.2f;
  int by = cy + (int)(sinf(breathPhase) * 3.0f);
  float sY = 1.0f + 0.05f * sinf(breathPhase);
  float sX = 1.0f - 0.03f * sinf(breathPhase);

  // 2. Bảng màu 16-bit RGB565 chuẩn xác
  const uint16_t C_RIM       = 0xF79F; // #F5F3FF Viền Fresnel trắng tím
  const uint16_t C_BODY      = 0xC43F; // #C084FC Thạch tím lavender
  const uint16_t C_CORE      = 0x7919; // #7E22CE Lõi thạch SSS sâu
  const uint16_t C_SHADOW    = 0x48F2; // #4C1D95 Vùng đổ bóng khuất
  const uint16_t C_BELLY     = 0xEEBF; // #E9D5FF Bụng thạch trong suốt
  const uint16_t C_HORN_BASE = 0xDEBF; // #DDD6FE Sừng ngọc nhạt
  const uint16_t C_HORN_TIP  = 0x919D; // #9333EA Chóp sừng pha lê
  const uint16_t C_BLUSH     = 0xF396; // #F472B6 Má hồng squishy
  const uint16_t C_EYE_DARK  = 0x1886; // #1E1035 Đáy mắt tím đen
  const uint16_t C_EYE_IRIS  = 0xC43F; // #C084FC Mống mắt thạch anh
  const uint16_t C_STAR_GOLD = 0xFF91; // #FEF08A Bụi sao vàng
  const uint16_t C_STAR_CYAN = 0xA79F; // #A5F3FC Bụi sao lam ngọc
  const uint16_t C_WHITE     = 0xFFFF; // #FFFFFF Ánh sáng kim cương

  // 3. Cánh trái (phía sau) với trễ pha 0.45 rad
  float wLag = breathPhase - 0.45f;
  int wFlapL = (int)(sinf(wLag) * 4.0f);
  spr->fillTriangle(cx - 12, by - 4, cx - 28, by - 18 + wFlapL, cx - 22, by - 6 + wFlapL, C_CORE);
  spr->fillTriangle(cx - 22, by - 6 + wFlapL, cx - 34, by - 8 + wFlapL, cx - 18, by + 2, C_BODY);
  spr->drawLine(cx - 28, by - 18 + wFlapL, cx - 22, by - 6 + wFlapL, C_RIM);
  spr->drawLine(cx - 22, by - 6 + wFlapL, cx - 34, by - 8 + wFlapL, C_RIM);

  // 4. Đuôi thạch uốn lượn bên hông
  spr->fillCircle(cx + 16, by + 12, (int)(8 * sX), C_BODY);
  spr->fillCircle(cx + 22, by + 8, (int)(6 * sX), C_BODY);
  spr->fillCircle(cx + 26, by + 3, (int)(4 * sX), C_RIM);
  // Gai đuôi mềm mại
  spr->fillTriangle(cx + 17, by + 6, cx + 20, by + 1, cx + 22, by + 6, C_HORN_BASE);
  spr->fillTriangle(cx + 23, by + 3, cx + 27, by - 1, cx + 26, by + 5, C_HORN_BASE);

  // 5. Thân thạch chính (Khối SSS Gelatinous Body)
  int bRy = (int)(18 * sY);
  int bRx = (int)(22 * sX);
  spr->fillEllipse(cx, by + 4, bRx + 2, bRy + 2, C_RIM);   // Lớp Fresnel ngoài
  spr->fillEllipse(cx, by + 4, bRx, bRy, C_BODY);           // Lớp thạch bán trong
  spr->fillEllipse(cx - 2, by + 5, (int)(14 * sX), (int)(11 * sY), C_CORE); // Lõi thạch sâu
  spr->fillEllipse(cx, by + 7, (int)(12 * sX), (int)(8 * sY), C_BELLY);    // Khoang sáng bụng

  // 6. Hạt sao kim cương phát quang chìm dưới bụng ✨ (Embedded Stardust)
  // Ngôi sao 4 cánh 1 (Lam ngọc)
  spr->drawFastHLine(cx - 5, by + 5, 5, C_STAR_CYAN);
  spr->drawFastVLine(cx - 3, by + 3, 5, C_STAR_CYAN);
  spr->drawPixel(cx - 3, by + 5, C_WHITE);
  // Ngôi sao 4 cánh 2 (Hoàng kim)
  spr->drawFastHLine(cx + 2, by + 7, 5, C_STAR_GOLD);
  spr->drawFastVLine(cx + 4, by + 5, 5, C_STAR_GOLD);
  spr->drawPixel(cx + 4, by + 7, C_WHITE);
  // Hạt lấp lánh phụ
  spr->drawFastHLine(cx - 1, by + 10, 3, C_WHITE);
  spr->drawFastVLine(cx, by + 9, 3, C_WHITE);
  spr->drawPixel(cx - 7, by + 8, C_STAR_GOLD);
  spr->drawPixel(cx + 7, by + 4, C_STAR_CYAN);

  // 7. Chân & Bàn chân bánh bao squishy
  spr->fillCircle(cx - 16, by + 12, (int)(8 * sX), C_BODY); // Đùi trái
  spr->fillCircle(cx + 14, by + 13, (int)(9 * sX), C_BODY); // Đùi phải
  spr->fillRoundRect(cx - 10, by + 14, (int)(8 * sX), (int)(7 * sY), 3, C_RIM); // Bàn chân trước L
  spr->fillRoundRect(cx + 2, by + 14, (int)(8 * sX), (int)(7 * sY), 3, C_RIM);  // Bàn chân trước R
  spr->drawPixel(cx - 9, by + 19, C_WHITE); // Đệm ngón lấp lánh
  spr->drawPixel(cx - 7, by + 20, C_WHITE);
  spr->drawPixel(cx + 4, by + 20, C_WHITE);
  spr->drawPixel(cx + 6, by + 19, C_WHITE);

  // 8. Cánh phải (phía trước) đón sáng
  int wFlapR = (int)(sinf(wLag + 0.1f) * 4.0f);
  spr->fillTriangle(cx + 10, by - 2, cx + 28, by - 16 + wFlapR, cx + 22, by - 4 + wFlapR, C_BODY);
  spr->fillTriangle(cx + 22, by - 4 + wFlapR, cx + 33, by - 6 + wFlapR, cx + 18, by + 4, C_BELLY);
  spr->drawLine(cx + 10, by - 2, cx + 28, by - 16 + wFlapR, C_RIM);
  spr->fillCircle(cx + 28, by - 16 + wFlapR, 2, C_WHITE); // Giọt pha lê chóp cánh

  // 9. Đầu rồng thạch Chibi (Head & Cheeks)
  int hy = by - 12;
  spr->fillEllipse(cx - 1, hy, (int)(18 * sX), (int)(16 * sY), C_RIM);
  spr->fillEllipse(cx - 1, hy, (int)(16 * sX), (int)(14 * sY), C_BODY);
  spr->fillCircle(cx - 12, hy + 4, (int)(7 * sX), C_BODY); // Má trái phúng phính
  spr->fillCircle(cx + 9, hy + 4, (int)(7 * sX), C_BODY);  // Má phải phúng phính

  // 10. Cặp sừng pha lê đa diện (Faceted Crystal Horns - Trễ pha 0.25 rad)
  float hLag = breathPhase - 0.25f;
  int hTilt = (int)(sinf(hLag) * 2.0f);
  // Sừng trái
  spr->fillTriangle(cx - 13, hy - 8, cx - 16 + hTilt, hy - 24, cx - 6, hy - 11, C_HORN_TIP);
  spr->fillTriangle(cx - 11, hy - 8, cx - 16 + hTilt, hy - 24, cx - 7, hy - 11, C_HORN_BASE);
  spr->drawLine(cx - 16 + hTilt, hy - 24, cx - 9, hy - 9, C_WHITE); // Cạnh vát lóa sáng
  // Sừng phải
  spr->fillTriangle(cx + 4, hy - 10, cx + 14 + hTilt, hy - 25, cx + 11, hy - 8, C_HORN_TIP);
  spr->fillTriangle(cx + 6, hy - 10, cx + 14 + hTilt, hy - 25, cx + 10, hy - 8, C_HORN_BASE);
  spr->drawLine(cx + 14 + hTilt, hy - 25, cx + 8, hy - 9, C_WHITE);
  // Gai vương miện nhỏ giữa trán
  spr->fillTriangle(cx - 3, hy - 13, cx - 1, hy - 17, cx + 1, hy - 13, C_HORN_BASE);

  // 11. Má hồng squishy & Miệng cười ngọt ngào
  spr->fillCircle(cx - 11, hy + 4, 4, C_BLUSH);
  spr->fillCircle(cx + 8, hy + 4, 4, C_BLUSH);
  // Mũi nhỏ xíu
  spr->drawPixel(cx - 3, hy + 3, C_CORE);
  spr->drawPixel(cx + 1, hy + 3, C_CORE);
  // Nụ cười bé bỏng
  spr->drawPixel(cx - 2, hy + 6, C_CORE);
  spr->drawPixel(cx - 1, hy + 7, C_CORE);
  spr->drawPixel(cx, hy + 7, C_CORE);
  spr->drawPixel(cx + 1, hy + 6, C_CORE);

  // 12. MẮT PHA LÊ 3 ĐIỂM SÁNG (3-Point Specular Crystal Eyes)
  int ey = hy - 1;
  int exL = cx - 8;
  int exR = cx + 5;

  if (blink) {
    // Mắt chớp cong hình lưỡi liềm hạnh phúc
    spr->drawEllipse(exL, ey + 2, 5, 2, C_EYE_DARK);
    spr->drawEllipse(exR, ey + 2, 5, 2, C_EYE_DARK);
  } else {
    // Vẽ từng bên mắt với chiều sâu quang học
    for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
      int ex = (eyeIdx == 0) ? exL : exR;
      // 12.1 Hốc mắt tối thẳm
      spr->fillEllipse(ex, ey, 6, 8, C_EYE_DARK);
      // 12.2 Mống mắt thạch anh phát quang đáy (Caustic Crescent)
      spr->fillEllipse(ex, ey + 3, 5, 4, C_EYE_IRIS);
      spr->fillEllipse(ex, ey + 4, 3, 2, C_RIM);
      // 12.3 Đồng tử đen
      spr->fillCircle(ex, ey, 4, C_EYE_DARK);
      // 12.4 Ngôi sao 4 cánh chìm trong đồng tử (Inner Diamond Star)
      spr->drawPixel(ex, ey - 1, C_STAR_CYAN);
      spr->drawPixel(ex, ey + 1, C_STAR_CYAN);
      spr->drawPixel(ex - 1, ey, C_STAR_CYAN);
      spr->drawPixel(ex + 1, ey, C_STAR_CYAN);
      spr->drawPixel(ex, ey, C_WHITE);
      // 12.5 ĐIỂM SÁNG 1 (Primary Keylight Specular - Góc trên trái lớn)
      spr->fillCircle(ex - 2, ey - 3, 2, C_WHITE);
      // 12.6 ĐIỂM SÁNG 2 (Secondary Caustic Bounce - Góc dưới phải vừa)
      spr->fillCircle(ex + 2, ey + 3, 1, C_WHITE);
      // 12.7 ĐIỂM SÁNG 3 (Tertiary Surface Sparkle - Điểm bắt sáng ướt góc trên phải)
      spr->drawPixel(ex + 2, ey - 2, C_WHITE);
    }
  }

  // 13. Ngôi sao phản quang 4 cánh trên trán (Đặc trưng poster gốc ✨)
  int starX = cx - 6;
  int starY = hy - 8;
  spr->drawFastHLine(starX - 4, starY, 9, C_WHITE);
  spr->drawFastVLine(starX, starY - 4, 9, C_WHITE);
  spr->drawPixel(starX, starY, C_WHITE);
  spr->drawPixel(starX - 1, starY - 1, C_RIM);
  spr->drawPixel(starX + 1, starY + 1, C_RIM);
  spr->drawPixel(starX - 1, starY + 1, C_RIM);
  spr->drawPixel(starX + 1, starY - 1, C_RIM);
}


// JELLY_DRAGON_STRAWBERRY - Thạch Long Hồng Dâu (Bé Rồng Thạch Dâu Tây)
// =========================================================================
// THẠCH LONG HỒNG DÂU (STRAWBERRY JELLY DRAGON - 젤리드레곤 딸기맛)
// ScaledCanvas C++ Implementation - 100% Hardware Compatible
// =========================================================================
void drawJellyDragonStrawberry(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink) {
  // 1. Nhịp thở Squash & Stretch 5%
  float breathPhase = angle * 2.2f;
  int by = cy + (int)(sinf(breathPhase) * 3.0f);
  float sY = 1.0f + 0.05f * sinf(breathPhase);
  float sX = 1.0f - 0.03f * sinf(breathPhase);

  // 2. Bảng màu 16-bit RGB565 Dâu Tây chuẩn xác
  const uint16_t C_RIM       = 0xFF9E; // #FFF1F2 Viền kem dâu trắng hồng
  const uint16_t C_BODY      = 0xFB8F; // #FB7185 Thạch dâu tây hồng tươi
  const uint16_t C_CORE      = 0xBE07; // #BE123C Lõi si-rô dâu đậm SSS
  const uint16_t C_SHADOW    = 0x8886; // #881337 Bóng mận tối
  const uint16_t C_BELLY     = 0xFF3C; // #FFE4E6 Bụng thạch dâu sữa
  const uint16_t C_HORN_BASE = 0xFE7A; // #FECDD3 Sừng hồng phấn pastel
  const uint16_t C_HORN_TIP  = 0xE0E9; // #E11D48 Chóp sừng ruby
  const uint16_t C_BLUSH     = 0xF20B; // #F43F5E Má hồng đỏ dâu
  const uint16_t C_EYE_DARK  = 0x4823; // #4C0519 Đáy mắt mận ruby
  const uint16_t C_EYE_IRIS  = 0xFB8F; // #FB7185 Mống mắt hồng tươi
  const uint16_t C_STAR_GOLD = 0xFEA8; // #FDE047 Bụi sao hoàng kim
  const uint16_t C_STAR_ROSE = 0xFE19; // #FDA4AF Bụi sao thạch anh
  const uint16_t C_WHITE     = 0xFFFF; // #FFFFFF Kim cương trắng

  // 3. Cánh sau
  float wLag = breathPhase - 0.45f;
  int wFlapL = (int)(sinf(wLag) * 4.0f);
  spr->fillTriangle(cx - 12, by - 4, cx - 28, by - 18 + wFlapL, cx - 22, by - 6 + wFlapL, C_CORE);
  spr->fillTriangle(cx - 22, by - 6 + wFlapL, cx - 34, by - 8 + wFlapL, cx - 18, by + 2, C_BODY);
  spr->drawLine(cx - 28, by - 18 + wFlapL, cx - 22, by - 6 + wFlapL, C_RIM);
  spr->drawLine(cx - 22, by - 6 + wFlapL, cx - 34, by - 8 + wFlapL, C_RIM);

  // 4. Đuôi uốn lượn
  spr->fillCircle(cx + 16, by + 12, (int)(8 * sX), C_BODY);
  spr->fillCircle(cx + 22, by + 8, (int)(6 * sX), C_BODY);
  spr->fillCircle(cx + 26, by + 3, (int)(4 * sX), C_RIM);
  spr->fillTriangle(cx + 17, by + 6, cx + 20, by + 1, cx + 22, by + 6, C_HORN_BASE);
  spr->fillTriangle(cx + 23, by + 3, cx + 27, by - 1, cx + 26, by + 5, C_HORN_BASE);

  // 5. Thân thạch SSS Dâu Tây
  int bRy = (int)(18 * sY);
  int bRx = (int)(22 * sX);
  spr->fillEllipse(cx, by + 4, bRx + 2, bRy + 2, C_RIM);
  spr->fillEllipse(cx, by + 4, bRx, bRy, C_BODY);
  spr->fillEllipse(cx - 2, by + 5, (int)(14 * sX), (int)(11 * sY), C_CORE);
  spr->fillEllipse(cx, by + 7, (int)(12 * sX), (int)(8 * sY), C_BELLY);

  // 6. Hạt sao kim cương phát quang chìm dưới bụng ✨
  spr->drawFastHLine(cx - 5, by + 5, 5, C_STAR_ROSE);
  spr->drawFastVLine(cx - 3, by + 3, 5, C_STAR_ROSE);
  spr->drawPixel(cx - 3, by + 5, C_WHITE);
  spr->drawFastHLine(cx + 2, by + 7, 5, C_STAR_GOLD);
  spr->drawFastVLine(cx + 4, by + 5, 5, C_STAR_GOLD);
  spr->drawPixel(cx + 4, by + 7, C_WHITE);
  spr->drawFastHLine(cx - 1, by + 10, 3, C_WHITE);
  spr->drawFastVLine(cx, by + 9, 3, C_WHITE);
  spr->drawPixel(cx - 7, by + 8, C_STAR_GOLD);
  spr->drawPixel(cx + 7, by + 4, C_STAR_ROSE);

  // 7. Chân & Bàn chân
  spr->fillCircle(cx - 16, by + 12, (int)(8 * sX), C_BODY);
  spr->fillCircle(cx + 14, by + 13, (int)(9 * sX), C_BODY);
  spr->fillRoundRect(cx - 10, by + 14, (int)(8 * sX), (int)(7 * sY), 3, C_RIM);
  spr->fillRoundRect(cx + 2, by + 14, (int)(8 * sX), (int)(7 * sY), 3, C_RIM);
  spr->drawPixel(cx - 9, by + 19, C_WHITE);
  spr->drawPixel(cx - 7, by + 20, C_WHITE);
  spr->drawPixel(cx + 4, by + 20, C_WHITE);
  spr->drawPixel(cx + 6, by + 19, C_WHITE);

  // 8. Cánh trước
  int wFlapR = (int)(sinf(wLag + 0.1f) * 4.0f);
  spr->fillTriangle(cx + 10, by - 2, cx + 28, by - 16 + wFlapR, cx + 22, by - 4 + wFlapR, C_BODY);
  spr->fillTriangle(cx + 22, by - 4 + wFlapR, cx + 33, by - 6 + wFlapR, cx + 18, by + 4, C_BELLY);
  spr->drawLine(cx + 10, by - 2, cx + 28, by - 16 + wFlapR, C_RIM);
  spr->fillCircle(cx + 28, by - 16 + wFlapR, 2, C_WHITE);

  // 9. Đầu Chibi
  int hy = by - 12;
  spr->fillEllipse(cx - 1, hy, (int)(18 * sX), (int)(16 * sY), C_RIM);
  spr->fillEllipse(cx - 1, hy, (int)(16 * sX), (int)(14 * sY), C_BODY);
  spr->fillCircle(cx - 12, hy + 4, (int)(7 * sX), C_BODY);
  spr->fillCircle(cx + 9, hy + 4, (int)(7 * sX), C_BODY);

  // 10. Sừng Rose Quartz
  float hLag = breathPhase - 0.25f;
  int hTilt = (int)(sinf(hLag) * 2.0f);
  spr->fillTriangle(cx - 13, hy - 8, cx - 16 + hTilt, hy - 24, cx - 6, hy - 11, C_HORN_TIP);
  spr->fillTriangle(cx - 11, hy - 8, cx - 16 + hTilt, hy - 24, cx - 7, hy - 11, C_HORN_BASE);
  spr->drawLine(cx - 16 + hTilt, hy - 24, cx - 9, hy - 9, C_WHITE);
  spr->fillTriangle(cx + 4, hy - 10, cx + 14 + hTilt, hy - 25, cx + 11, hy - 8, C_HORN_TIP);
  spr->fillTriangle(cx + 6, hy - 10, cx + 14 + hTilt, hy - 25, cx + 10, hy - 8, C_HORN_BASE);
  spr->drawLine(cx + 14 + hTilt, hy - 25, cx + 8, hy - 9, C_WHITE);
  spr->fillTriangle(cx - 3, hy - 13, cx - 1, hy - 17, cx + 1, hy - 13, C_HORN_BASE);

  // 11. Má hồng dâu tây & Miệng cười
  spr->fillCircle(cx - 11, hy + 4, 4, C_BLUSH);
  spr->fillCircle(cx + 8, hy + 4, 4, C_BLUSH);
  spr->drawPixel(cx - 3, hy + 3, C_CORE);
  spr->drawPixel(cx + 1, hy + 3, C_CORE);
  spr->drawPixel(cx - 2, hy + 6, C_CORE);
  spr->drawPixel(cx - 1, hy + 7, C_CORE);
  spr->drawPixel(cx, hy + 7, C_CORE);
  spr->drawPixel(cx + 1, hy + 6, C_CORE);

  // 12. MẮT PHA LÊ RUBY 3 ĐIỂM SÁNG
  int ey = hy - 1;
  int exL = cx - 8;
  int exR = cx + 5;

  if (blink) {
    spr->drawEllipse(exL, ey + 2, 5, 2, C_EYE_DARK);
    spr->drawEllipse(exR, ey + 2, 5, 2, C_EYE_DARK);
  } else {
    for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
      int ex = (eyeIdx == 0) ? exL : exR;
      spr->fillEllipse(ex, ey, 6, 8, C_EYE_DARK);
      spr->fillEllipse(ex, ey + 3, 5, 4, C_EYE_IRIS);
      spr->fillEllipse(ex, ey + 4, 3, 2, C_RIM);
      spr->fillCircle(ex, ey, 4, C_EYE_DARK);
      spr->drawPixel(ex, ey - 1, C_STAR_ROSE);
      spr->drawPixel(ex, ey + 1, C_STAR_ROSE);
      spr->drawPixel(ex - 1, ey, C_STAR_ROSE);
      spr->drawPixel(ex + 1, ey, C_STAR_ROSE);
      spr->drawPixel(ex, ey, C_WHITE);
      // ĐIỂM SÁNG 1
      spr->fillCircle(ex - 2, ey - 3, 2, C_WHITE);
      // ĐIỂM SÁNG 2
      spr->fillCircle(ex + 2, ey + 3, 1, C_WHITE);
      // ĐIỂM SÁNG 3
      spr->drawPixel(ex + 2, ey - 2, C_WHITE);
    }
  }

  // 13. Ngôi sao 4 cánh trán
  int starX = cx - 6;
  int starY = hy - 8;
  spr->drawFastHLine(starX - 4, starY, 9, C_WHITE);
  spr->drawFastVLine(starX, starY - 4, 9, C_WHITE);
  spr->drawPixel(starX, starY, C_WHITE);
  spr->drawPixel(starX - 1, starY - 1, C_RIM);
  spr->drawPixel(starX + 1, starY + 1, C_RIM);
  spr->drawPixel(starX - 1, starY + 1, C_RIM);
  spr->drawPixel(starX + 1, starY - 1, C_RIM);
}


// JELLY_DRAGON_SODA - Thạch Long Lam Soda (Bé Rồng Thạch Kem Soda)
// =========================================================================
// THẠCH LONG LAM SODA (SODA BLUE JELLY DRAGON - 젤리드레곤 소다맛)
// ScaledCanvas C++ Implementation - 100% Hardware Compatible
// =========================================================================
void drawJellyDragonSoda(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink) {
  // 1. Nhịp thở Squash & Stretch 5%
  float breathPhase = angle * 2.2f;
  int by = cy + (int)(sinf(breathPhase) * 3.0f);
  float sY = 1.0f + 0.05f * sinf(breathPhase);
  float sX = 1.0f - 0.03f * sinf(breathPhase);

  // 2. Bảng màu 16-bit RGB565 Lam Soda chuẩn xác
  const uint16_t C_RIM       = 0xEF7F; // #ECFEFF Viền băng tuyết trắng lam
  const uint16_t C_BODY      = 0x269D; // #22D3EE Thạch lam soda thanh mát
  const uint16_t C_CORE      = 0x0496; // #0891B2 Lõi lam đại dương SSS
  const uint16_t C_SHADOW    = 0x12F2; // #155E75 Vùng bóng sâu đại dương
  const uint16_t C_BELLY     = 0xC7DF; // #CFFAFE Bụng thạch bọt khí soda
  const uint16_t C_HORN_BASE = 0xA7BF; // #A5F3FC Sừng Aquamarine nhạt
  const uint16_t C_HORN_TIP  = 0x0438; // #0284C7 Chóp sừng Sapphire
  const uint16_t C_BLUSH     = 0xFE19; // #FDA4AF Má hồng cam đào ấm áp
  const uint16_t C_EYE_DARK  = 0x0969; // #082F49 Đáy mắt vực sâu
  const uint16_t C_EYE_IRIS  = 0x06DD; // #00D8F6 Mống mắt ngọc lam
  const uint16_t C_STAR_GOLD = 0xFF91; // #FEF08A Bụi sao hoàng kim
  const uint16_t C_STAR_CYAN = 0x675F; // #67E8F9 Bọt khí soda sủi tăm
  const uint16_t C_WHITE     = 0xFFFF; // #FFFFFF Kim cương trắng

  // 3. Cánh sau
  float wLag = breathPhase - 0.45f;
  int wFlapL = (int)(sinf(wLag) * 4.0f);
  spr->fillTriangle(cx - 12, by - 4, cx - 28, by - 18 + wFlapL, cx - 22, by - 6 + wFlapL, C_CORE);
  spr->fillTriangle(cx - 22, by - 6 + wFlapL, cx - 34, by - 8 + wFlapL, cx - 18, by + 2, C_BODY);
  spr->drawLine(cx - 28, by - 18 + wFlapL, cx - 22, by - 6 + wFlapL, C_RIM);
  spr->drawLine(cx - 22, by - 6 + wFlapL, cx - 34, by - 8 + wFlapL, C_RIM);

  // 4. Đuôi uốn lượn
  spr->fillCircle(cx + 16, by + 12, (int)(8 * sX), C_BODY);
  spr->fillCircle(cx + 22, by + 8, (int)(6 * sX), C_BODY);
  spr->fillCircle(cx + 26, by + 3, (int)(4 * sX), C_RIM);
  spr->fillTriangle(cx + 17, by + 6, cx + 20, by + 1, cx + 22, by + 6, C_HORN_BASE);
  spr->fillTriangle(cx + 23, by + 3, cx + 27, by - 1, cx + 26, by + 5, C_HORN_BASE);

  // 5. Thân thạch SSS Lam Soda
  int bRy = (int)(18 * sY);
  int bRx = (int)(22 * sX);
  spr->fillEllipse(cx, by + 4, bRx + 2, bRy + 2, C_RIM);
  spr->fillEllipse(cx, by + 4, bRx, bRy, C_BODY);
  spr->fillEllipse(cx - 2, by + 5, (int)(14 * sX), (int)(11 * sY), C_CORE);
  spr->fillEllipse(cx, by + 7, (int)(12 * sX), (int)(8 * sY), C_BELLY);

  // 6. Hạt sao & Bọt khí kim cương chìm dưới bụng ✨
  spr->drawFastHLine(cx - 5, by + 5, 5, C_STAR_CYAN);
  spr->drawFastVLine(cx - 3, by + 3, 5, C_STAR_CYAN);
  spr->drawPixel(cx - 3, by + 5, C_WHITE);
  spr->drawFastHLine(cx + 2, by + 7, 5, C_STAR_GOLD);
  spr->drawFastVLine(cx + 4, by + 5, 5, C_STAR_GOLD);
  spr->drawPixel(cx + 4, by + 7, C_WHITE);
  spr->drawFastHLine(cx - 1, by + 10, 3, C_WHITE);
  spr->drawFastVLine(cx, by + 9, 3, C_WHITE);
  spr->drawPixel(cx - 7, by + 8, C_STAR_GOLD);
  spr->drawPixel(cx + 7, by + 4, C_STAR_CYAN);

  // 7. Chân & Bàn chân
  spr->fillCircle(cx - 16, by + 12, (int)(8 * sX), C_BODY);
  spr->fillCircle(cx + 14, by + 13, (int)(9 * sX), C_BODY);
  spr->fillRoundRect(cx - 10, by + 14, (int)(8 * sX), (int)(7 * sY), 3, C_RIM);
  spr->fillRoundRect(cx + 2, by + 14, (int)(8 * sX), (int)(7 * sY), 3, C_RIM);
  spr->drawPixel(cx - 9, by + 19, C_WHITE);
  spr->drawPixel(cx - 7, by + 20, C_WHITE);
  spr->drawPixel(cx + 4, by + 20, C_WHITE);
  spr->drawPixel(cx + 6, by + 19, C_WHITE);

  // 8. Cánh trước
  int wFlapR = (int)(sinf(wLag + 0.1f) * 4.0f);
  spr->fillTriangle(cx + 10, by - 2, cx + 28, by - 16 + wFlapR, cx + 22, by - 4 + wFlapR, C_BODY);
  spr->fillTriangle(cx + 22, by - 4 + wFlapR, cx + 33, by - 6 + wFlapR, cx + 18, by + 4, C_BELLY);
  spr->drawLine(cx + 10, by - 2, cx + 28, by - 16 + wFlapR, C_RIM);
  spr->fillCircle(cx + 28, by - 16 + wFlapR, 2, C_WHITE);

  // 9. Đầu Chibi
  int hy = by - 12;
  spr->fillEllipse(cx - 1, hy, (int)(18 * sX), (int)(16 * sY), C_RIM);
  spr->fillEllipse(cx - 1, hy, (int)(16 * sX), (int)(14 * sY), C_BODY);
  spr->fillCircle(cx - 12, hy + 4, (int)(7 * sX), C_BODY);
  spr->fillCircle(cx + 9, hy + 4, (int)(7 * sX), C_BODY);

  // 10. Sừng Aquamarine
  float hLag = breathPhase - 0.25f;
  int hTilt = (int)(sinf(hLag) * 2.0f);
  spr->fillTriangle(cx - 13, hy - 8, cx - 16 + hTilt, hy - 24, cx - 6, hy - 11, C_HORN_TIP);
  spr->fillTriangle(cx - 11, hy - 8, cx - 16 + hTilt, hy - 24, cx - 7, hy - 11, C_HORN_BASE);
  spr->drawLine(cx - 16 + hTilt, hy - 24, cx - 9, hy - 9, C_WHITE);
  spr->fillTriangle(cx + 4, hy - 10, cx + 14 + hTilt, hy - 25, cx + 11, hy - 8, C_HORN_TIP);
  spr->fillTriangle(cx + 6, hy - 10, cx + 14 + hTilt, hy - 25, cx + 10, hy - 8, C_HORN_BASE);
  spr->drawLine(cx + 14 + hTilt, hy - 25, cx + 8, hy - 9, C_WHITE);
  spr->fillTriangle(cx - 3, hy - 13, cx - 1, hy - 17, cx + 1, hy - 13, C_HORN_BASE);

  // 11. Má hồng cam đào & Miệng
  spr->fillCircle(cx - 11, hy + 4, 4, C_BLUSH);
  spr->fillCircle(cx + 8, hy + 4, 4, C_BLUSH);
  spr->drawPixel(cx - 3, hy + 3, C_CORE);
  spr->drawPixel(cx + 1, hy + 3, C_CORE);
  spr->drawPixel(cx - 2, hy + 6, C_CORE);
  spr->drawPixel(cx - 1, hy + 7, C_CORE);
  spr->drawPixel(cx, hy + 7, C_CORE);
  spr->drawPixel(cx + 1, hy + 6, C_CORE);

  // 12. MẮT PHA LÊ SAPPHIRE 3 ĐIỂM SÁNG
  int ey = hy - 1;
  int exL = cx - 8;
  int exR = cx + 5;

  if (blink) {
    spr->drawEllipse(exL, ey + 2, 5, 2, C_EYE_DARK);
    spr->drawEllipse(exR, ey + 2, 5, 2, C_EYE_DARK);
  } else {
    for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
      int ex = (eyeIdx == 0) ? exL : exR;
      spr->fillEllipse(ex, ey, 6, 8, C_EYE_DARK);
      spr->fillEllipse(ex, ey + 3, 5, 4, C_EYE_IRIS);
      spr->fillEllipse(ex, ey + 4, 3, 2, C_RIM);
      spr->fillCircle(ex, ey, 4, C_EYE_DARK);
      spr->drawPixel(ex, ey - 1, C_STAR_CYAN);
      spr->drawPixel(ex, ey + 1, C_STAR_CYAN);
      spr->drawPixel(ex - 1, ey, C_STAR_CYAN);
      spr->drawPixel(ex + 1, ey, C_STAR_CYAN);
      spr->drawPixel(ex, ey, C_WHITE);
      // ĐIỂM SÁNG 1
      spr->fillCircle(ex - 2, ey - 3, 2, C_WHITE);
      // ĐIỂM SÁNG 2
      spr->fillCircle(ex + 2, ey + 3, 1, C_WHITE);
      // ĐIỂM SÁNG 3
      spr->drawPixel(ex + 2, ey - 2, C_WHITE);
    }
  }

  // 13. Ngôi sao trán
  int starX = cx - 6;
  int starY = hy - 8;
  spr->drawFastHLine(starX - 4, starY, 9, C_WHITE);
  spr->drawFastVLine(starX, starY - 4, 9, C_WHITE);
  spr->drawPixel(starX, starY, C_WHITE);
  spr->drawPixel(starX - 1, starY - 1, C_RIM);
  spr->drawPixel(starX + 1, starY + 1, C_RIM);
  spr->drawPixel(starX - 1, starY + 1, C_RIM);
  spr->drawPixel(starX + 1, starY - 1, C_RIM);
}


// CELESTIAL_ELEMENTAL_SNAIL - Sên Thần 5 Ngọc Nguyên Tố (Linh Quy Thần Sên Thiên Hà)
// =========================================================================
// SÊN THẦN 5 NGỌC NGUYÊN TỐ (ELEMENTAL CELESTIAL SNAIL - 1:1 download (7).jpg)
// ScaledCanvas C++ Implementation - 100% Hardware Compatible
// =========================================================================
void drawCelestialElementalSnail(SpriteRenderer::ScaledCanvas* spr, int cx, int cy, float angle, bool blink) {
  // 1. Nhịp thở linh thú Squash & Stretch
  float breathPhase = angle * 1.8f;
  int by = cy + (int)(sinf(breathPhase) * 2.5f);
  float sY = 1.0f + 0.045f * sinf(breathPhase);
  float sX = 1.0f - 0.025f * sinf(breathPhase);

  // 2. Bảng màu 16-bit RGB565 Thần Thánh chuẩn xác
  const uint16_t C_WHITE      = 0xFFFF; // #FFFFFF Bạch ngọc xà cừ tinh khiết
  const uint16_t C_SILVER_L   = 0xF7BE; // #F1F5F9 Bạc xà cừ sáng
  const uint16_t C_SILVER_M   = 0xCE79; // #CBD5E1 Bạc kim loại
  const uint16_t C_SILVER_D   = 0x9536; // #94A3B8 Bóng nacre xám bạc
  const uint16_t C_GOLD_DARK  = 0xF4E0; // #F59E0B Vàng hoàng kim đậm
  const uint16_t C_GOLD_BRT   = 0xFF91; // #FDE047 Vàng chói lọi
  const uint16_t C_ORB_BLUE   = 0x05BF; // #00B4D8 Ngọc Thủy (Water)
  const uint16_t C_ORB_RED    = 0xF224; // #EF4444 Ngọc Hỏa (Fire)
  const uint16_t C_ORB_SUN    = 0xFE60; // #FACC15 Ngọc Thái Dương (Sun)
  const uint16_t C_ORB_GREEN  = 0x262B; // #22C55E Ngọc Mộc (Earth)
  const uint16_t C_EYE_DARK   = 0x28A0; // #2D1802 Đáy mắt hổ phách
  const uint16_t C_EYE_IRIS   = 0xF4E0; // #F59E0B Mống mắt hoàng kim
  const uint16_t C_AURA_SILV  = 0xE71C; // #E2E8F0 Vòng hào quang bụi sao

  // 3. VÒNG HÀO QUANG STARDUST QUANH ĐÁY (Cosmic Stardust Base Ring)
  int auraY = by + 22;
  spr->drawEllipse(cx, auraY, (int)(38 * sX), (int)(10 * sY), C_AURA_SILV);
  spr->drawEllipse(cx, auraY, (int)(34 * sX), (int)(8 * sY), C_GOLD_BRT);
  // Các hạt bụi sao xoay quanh quỹ đạo
  for (int i = 0; i < 8; i++) {
    float a = i * 0.7853f + angle * 1.5f;
    int px = cx + (int)(cosf(a) * 36.0f * sX);
    int py = auraY + (int)(sinf(a) * 9.0f * sY);
    spr->drawPixel(px, py, C_WHITE);
    if (i % 2 == 0) {
      spr->drawPixel(px - 1, py, C_GOLD_BRT);
      spr->drawPixel(px + 1, py, C_GOLD_BRT);
    }
  }

  // 4. THÂN SÊN BẠC XÀ CỪ (Pearlescent Nacre Body Silhouette)
  // Bụng dưới tiếp đất
  spr->fillEllipse(cx + 6, by + 14, (int)(26 * sX), (int)(10 * sY), C_SILVER_D);
  spr->fillEllipse(cx + 4, by + 12, (int)(24 * sX), (int)(8 * sY), C_SILVER_M);
  spr->fillEllipse(cx + 2, by + 10, (int)(22 * sX), (int)(6 * sY), C_SILVER_L);
  // Đuôi sên uốn lượn nhọn thanh thoát
  spr->fillTriangle(cx + 20, by + 14, cx + 36, by + 14, cx + 28, by + 8, C_SILVER_M);
  spr->drawLine(cx + 24, by + 10, cx + 36, by + 14, C_WHITE);

  // Thân vươn cao & Nếp gấp cổ xà cừ
  spr->fillRoundRect(cx - 14, by - 12, (int)(24 * sX), (int)(26 * sY), 12, C_SILVER_M);
  spr->fillRoundRect(cx - 12, by - 10, (int)(20 * sX), (int)(24 * sY), 10, C_SILVER_L);
  spr->fillRoundRect(cx - 10, by - 8, (int)(16 * sX), (int)(20 * sY), 8, C_WHITE);

  // 5. ẤN CHÚ PHÉP THUẬT NGUYÊN TỐ XOAY VẦN (Rotating Alchemy Magic Seal trên mai)
  int mx = cx + 14;
  int my = by + 4;
  int mr = 13;
  spr->drawCircle(mx, my, mr, C_GOLD_DARK);
  spr->drawCircle(mx, my, mr - 3, C_GOLD_BRT);
  // 5 đỉnh ngôi sao ngũ giác xoay vĩnh cửu
  float sealRot = angle * 0.5f;
  int pX[5], pY[5];
  const uint16_t elemCol[5] = { C_ORB_RED, C_ORB_SUN, C_ORB_GREEN, C_WHITE, C_ORB_BLUE };
  for (int k = 0; k < 5; k++) {
    float th = sealRot + k * 1.2566f;
    pX[k] = mx + (int)(cosf(th) * 8.5f);
    pY[k] = my + (int)(sinf(th) * 8.5f);
  }
  // Nối các đỉnh ngũ giác (Pentagram lines)
  for (int k = 0; k < 5; k++) {
    int nextK = (k + 2) % 5;
    spr->drawLine(pX[k], pY[k], pX[nextK], pY[nextK], C_GOLD_DARK);
  }
  // 5 viên ngọc nguyên tố xoay quanh ấn chú
  for (int k = 0; k < 5; k++) {
    spr->fillCircle(pX[k], pY[k], 2, elemCol[k]);
    spr->drawPixel(pX[k], pY[k], C_WHITE);
  }
  spr->fillCircle(mx, my, 2, C_WHITE); // Tâm phát sáng của ấn chú

  // 6. HUY HIỆU NGỰC NGỌC CẦU VỒNG (Rainbow Prismatic Chest Amulet)
  int ax = cx - 3;
  int ay = by + 4;
  // Khung vàng giọt lệ
  spr->fillTriangle(ax - 5, ay - 1, ax + 3, ay - 1, ax - 1, ay + 8, C_GOLD_DARK);
  spr->fillCircle(ax - 1, ay + 2, 4, C_GOLD_BRT);
  // Ngọc cầu vồng khúc xạ đa sắc
  spr->fillCircle(ax - 1, ay + 2, 3, C_SILVER_M);
  spr->drawPixel(ax - 2, ay + 1, C_ORB_RED);
  spr->drawPixel(ax - 1, ay + 1, C_ORB_SUN);
  spr->drawPixel(ax, ay + 2, C_ORB_GREEN);
  spr->drawPixel(ax - 1, ay + 3, C_ORB_BLUE);
  spr->drawPixel(ax - 2, ay + 2, C_WHITE); // Specular highlight
  // Tia sáng tỏa ra ngực
  spr->drawLine(ax - 1, ay + 2, ax - 7, ay - 2, C_GOLD_BRT);
  spr->drawLine(ax - 1, ay + 2, ax + 5, ay - 2, C_GOLD_BRT);
  spr->drawLine(ax - 1, ay + 2, ax - 1, ay - 4, C_WHITE);

  // 7. ĐẦU VƯƠNG GIẢ & NỤ CƯỜI BÁNH MÌ HIỀN TỪ
  int hy = by - 12;
  spr->fillCircle(cx - 4, hy, (int)(14 * sX), C_SILVER_M);
  spr->fillCircle(cx - 3, hy + 1, (int)(12 * sX), C_WHITE);
  // Nụ cười thần thái
  spr->drawPixel(cx - 4, hy + 8, C_SILVER_D);
  spr->drawPixel(cx - 3, hy + 9, C_SILVER_D);
  spr->drawPixel(cx - 2, hy + 9, C_SILVER_D);
  spr->drawPixel(cx - 1, hy + 8, C_SILVER_D);

  // 8. 5 SỪNG VƯƠNG MIỆN & 5 VIÊN NGỌC THẦN (5 Horn Stalks & 5 Elemental Orbs)
  float hLag = breathPhase - 0.20f;
  int hSway = (int)(sinf(hLag) * 2.0f);

  // Stalk 1 (Ngoài cùng trái: Ngọc Thủy Blue)
  int ox1 = cx - 25 + hSway, oy1 = by - 26;
  spr->drawLine(cx - 8, by - 20, ox1, oy1, C_WHITE);
  spr->drawLine(cx - 7, by - 20, ox1 + 1, oy1, C_SILVER_M);
  spr->fillCircle(ox1, oy1, 4, C_ORB_BLUE);
  spr->fillCircle(ox1, oy1, 2, 0x56BF); // Cyan glow
  spr->drawPixel(ox1 - 1, oy1 - 1, C_WHITE);

  // Stalk 2 (Trái trên: Ngọc Hỏa Red)
  int ox2 = cx - 15 + hSway, oy2 = by - 38;
  spr->drawLine(cx - 6, by - 22, ox2, oy2, C_WHITE);
  spr->drawLine(cx - 5, by - 22, ox2 + 1, oy2, C_SILVER_M);
  spr->fillCircle(ox2, oy2, 4, C_ORB_RED);
  spr->fillCircle(ox2, oy2, 2, 0xFC08); // Fiery glow
  spr->drawPixel(ox2 - 1, oy2 - 1, C_WHITE);

  // Stalk 3 (Trung tâm cao nhất: Ngọc Thái Dương Sun Topaz có Hào Quang 8 Tia)
  int ox3 = cx - 2 + hSway, oy3 = by - 46;
  spr->drawLine(cx - 3, by - 24, ox3, oy3, C_WHITE);
  spr->drawLine(cx - 2, by - 24, ox3 + 1, oy3, C_SILVER_M);
  spr->fillCircle(ox3, oy3, 5, C_GOLD_DARK);
  spr->fillCircle(ox3, oy3, 3, C_GOLD_BRT);
  spr->fillCircle(ox3, oy3, 1, C_WHITE);
  // Hào quang 8 tia sáng thiên giới chói lọi
  spr->drawFastHLine(ox3 - 7, oy3, 15, C_GOLD_BRT);
  spr->drawFastVLine(ox3, oy3 - 7, 15, C_GOLD_BRT);
  spr->drawLine(ox3 - 4, oy3 - 4, ox3 + 4, oy3 + 4, C_WHITE);
  spr->drawLine(ox3 + 4, oy3 - 4, ox3 - 4, oy3 + 4, C_WHITE);

  // Stalk 4 (Phải trên: Ngọc Mộc Green)
  int ox4 = cx + 13 + hSway, oy4 = by - 38;
  spr->drawLine(cx - 1, by - 22, ox4, oy4, C_WHITE);
  spr->drawLine(cx, by - 22, ox4 + 1, oy4, C_SILVER_M);
  spr->fillCircle(ox4, oy4, 4, C_ORB_GREEN);
  spr->fillCircle(ox4, oy4, 2, 0x67E8); // Emerald glow
  spr->drawPixel(ox4 - 1, oy4 - 1, C_WHITE);

  // Stalk 5 (Ngoài cùng phải: Ngọc Khí Linh White Pearl có chữ thập lấp lánh)
  int ox5 = cx + 24 + hSway, oy5 = by - 26;
  spr->drawLine(cx + 2, by - 20, ox5, oy5, C_WHITE);
  spr->drawLine(cx + 3, by - 20, ox5 + 1, oy5, C_SILVER_M);
  spr->fillCircle(ox5, oy5, 4, C_SILVER_M);
  spr->fillCircle(ox5, oy5, 3, C_WHITE);
  spr->drawFastHLine(ox5 - 4, oy5, 9, C_WHITE);
  spr->drawFastVLine(ox5, oy5 - 4, 9, C_WHITE);

  // 9. MẮT PHA LÊ HỔ PHÁCH 3 ĐIỂM SÁNG (Molten Amber Crystal Eyes)
  int ey = hy - 2;
  int exL = cx - 8;
  int exR = cx + 3;

  if (blink) {
    spr->drawEllipse(exL, ey + 2, 5, 2, C_EYE_DARK);
    spr->drawEllipse(exR, ey + 2, 5, 2, C_EYE_DARK);
  } else {
    for (int eyeIdx = 0; eyeIdx < 2; eyeIdx++) {
      int ex = (eyeIdx == 0) ? exL : exR;
      // 9.1 Hốc mắt hổ phách thẳm
      spr->fillEllipse(ex, ey, 6, 8, C_EYE_DARK);
      // 9.2 Mống mắt hoàng kim nóng chảy
      spr->fillEllipse(ex, ey + 2, 5, 6, C_EYE_IRIS);
      spr->fillEllipse(ex, ey + 4, 4, 3, C_GOLD_BRT);
      // 9.3 Đồng tử
      spr->fillCircle(ex, ey, 3, C_EYE_DARK);
      // 9.4 ĐIỂM SÁNG 1 (Primary Specular - Lưỡi liềm ánh sáng lớn trên)
      spr->fillCircle(ex - 2, ey - 3, 2, C_WHITE);
      // 9.5 ĐIỂM SÁNG 2 (Secondary Caustic - Bắt sáng ấm đáy mắt)
      spr->fillCircle(ex + 2, ey + 3, 1, C_GOLD_BRT);
      // 9.6 ĐIỂM SÁNG 3 (Tertiary Wetness - Bắt sáng góc trên phải)
      spr->drawPixel(ex + 2, ey - 2, C_WHITE);
      // Tia sáng tâm
      spr->drawPixel(ex, ey, C_WHITE);
    }
  }
}



static void drawJellyCelestialCreature(ScaledCanvas* spr, int subId, int cx, int cy, float breath, float angle, float scale = 1.0f) {
  bool blink = (millis() % 3500 < 160);
  switch (subId) {
    case 0: drawJellyDragonLavender(spr, cx, cy, angle, blink); break;
    case 1: drawJellyDragonStrawberry(spr, cx, cy, angle, blink); break;
    case 2: drawJellyDragonSoda(spr, cx, cy, angle, blink); break;
    case 3: drawCelestialElementalSnail(spr, cx, cy, angle, blink); break;
    default: drawJellyDragonLavender(spr, cx, cy, angle, blink); break;
  }
}

} // namespace JellyCelestial
