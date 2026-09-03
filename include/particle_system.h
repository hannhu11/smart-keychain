#pragma once
#include <Arduino.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "config.h"

struct SparkleParticle {
  float x;
  float y;
  float speedY;
  float speedX;
  float phase;
  uint8_t size;      // 1: Pixel đơn, 2: Dấu cộng (+), 3: Ngôi sao kim cương (*)
  uint16_t color;
  uint16_t glowColor;
};

class ParticleSystem {
private:
  static const int NUM_PARTICLES = 36;
  SparkleParticle particles[NUM_PARTICLES];
  int currentPalette = 0;
  float globalTick = 0.0f;

public:
  ParticleSystem() {}

  void init() {
    for (int i = 0; i < NUM_PARTICLES; i++) {
      resetParticle(i, true);
    }
  }

  void resetParticle(int index, bool randomY = false) {
    particles[index].x = random(4, SCREEN_WIDTH - 4);
    particles[index].y = randomY ? random(0, SCREEN_HEIGHT) : random(-20, 0);
    particles[index].speedY = random(15, 45) / 10.0f;
    particles[index].speedX = random(-5, 6) / 10.0f;
    particles[index].phase = random(0, 628) / 100.0f;
    particles[index].size = (index % 4 == 0) ? 3 : ((index % 2 == 0) ? 2 : 1);
    applyPalette(index);
  }

  void applyPalette(int index) {
    switch (currentPalette) {
      case 0: // 1. Xanh Băng & Kim Cương Pha Lê (Cyber Greatsword)
        particles[index].color = (random(0, 3) == 0) ? TFT_WHITE : TFT_CYAN;
        particles[index].glowColor = 0x0357; // Cyan đậm
        break;
      case 1: // 2. Hồng Ruby & Trái Tim Lấp Lánh (Crystal Heart)
        particles[index].color = (random(0, 3) == 0) ? TFT_WHITE : TFT_MAGENTA;
        particles[index].glowColor = 0x780E; // Hồng sẫm
        break;
      case 2: // 3. Vàng Hổ Phách & Sao Kim (Hu Tao / Genshin)
        particles[index].color = (random(0, 3) == 0) ? TFT_WHITE : TFT_YELLOW;
        particles[index].glowColor = 0x8400; // Vàng sẫm
        break;
      case 3: // 4. Hồng Pastel & Bụi Sao (Anya Forger)
        particles[index].color = (random(0, 2) == 0) ? TFT_PINK : TFT_WHITE;
        particles[index].glowColor = 0x9255;
        break;
      case 4: // 5. Xanh Ma Trận & Ngọc Lục Bảo (Matrix Emerald)
        particles[index].color = (random(0, 3) == 0) ? TFT_WHITE : TFT_GREEN;
        particles[index].glowColor = 0x03E0;
        break;
    }
  }

  void nextPalette() {
    currentPalette = (currentPalette + 1) % 5;
    for (int i = 0; i < NUM_PARTICLES; i++) {
      applyPalette(i);
    }
  }

  void setPalette(int p) {
    currentPalette = p % 5;
    for (int i = 0; i < NUM_PARTICLES; i++) {
      applyPalette(i);
    }
  }

  int getPalette() const {
    return currentPalette;
  }

  void updateAndRender(LGFX_Sprite* sprite) {
    globalTick += 0.08f;

    for (int i = 0; i < NUM_PARTICLES; i++) {
      int px = (int)particles[i].x;
      int py = (int)particles[i].y;

      // Độ lấp lánh (Shimmer) tính theo hàm sin
      float shimmer = sin(particles[i].phase + globalTick);

      if (py >= 0 && py < SCREEN_HEIGHT && px >= 2 && px < SCREEN_WIDTH - 2) {
        if (particles[i].size == 3 && shimmer > 0.3f) {
          // Ngôi sao kim cương lấp lánh 5 điểm (Diamond Star Flare)
          sprite->drawPixel(px, py, TFT_WHITE);
          sprite->drawPixel(px - 1, py, particles[i].color);
          sprite->drawPixel(px + 1, py, particles[i].color);
          sprite->drawPixel(px, py - 1, particles[i].color);
          sprite->drawPixel(px, py + 1, particles[i].color);
          if (shimmer > 0.8f) {
            sprite->drawPixel(px - 2, py, particles[i].glowColor);
            sprite->drawPixel(px + 2, py, particles[i].glowColor);
            sprite->drawPixel(px, py - 2, particles[i].glowColor);
            sprite->drawPixel(px, py + 2, particles[i].glowColor);
          }
        } else if (particles[i].size == 2) {
          // Hạt lấp lánh chữ thập (+)
          sprite->drawPixel(px, py, particles[i].color);
          sprite->drawPixel(px - 1, py, particles[i].glowColor);
          sprite->drawPixel(px + 1, py, particles[i].glowColor);
          sprite->drawPixel(px, py - 1, particles[i].glowColor);
          sprite->drawPixel(px, py + 1, particles[i].glowColor);
        } else {
          // Pixel đơn với vệt đuôi mờ
          sprite->drawPixel(px, py, particles[i].color);
          if (py > 2) {
            sprite->drawPixel(px, py - 1, particles[i].glowColor);
          }
        }
      }

      // Cập nhật tọa độ
      particles[i].y += particles[i].speedY;
      particles[i].x += sin(particles[i].phase + globalTick * 0.5f) * 0.4f + particles[i].speedX;

      // Reset khi chạm đáy hoặc bay ra ngoài biên
      if (particles[i].y >= SCREEN_HEIGHT || particles[i].x < 0 || particles[i].x >= SCREEN_WIDTH) {
        resetParticle(i, false);
      }
    }
  }
};
