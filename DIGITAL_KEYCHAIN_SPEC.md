# PROJECT SPECIFICATION: SMART DIGITAL PIXEL KEYCHAIN (LOVE COMPANION)

## 1. Hardware Specifications
- **MCU:** ESP32-WROOM-32 / ESP32-C3 SuperMini (Dual Core 240MHz, Wi-Fi 2.4GHz + BLE 4.2).
- **Display:** 1.47" TFT IPS LCD (ST7789P3 driver, 172x320 pixels, 247 PPI, 40MHz SPI bus).
- **Power Subsystem:** 
  - Battery: 3.7V LiPo 500mAh - 800mAh (Model 602535 / 802540).
  - Charger IC: TP4056 Type-C with DW01A + FS8205A overcharge/discharge protection.
  - Power Switch: SS12D00 SPDT Mini Switch.
- **Pinout Mapping (ESP32 DevKit V1):**
  - `TFT_MOSI (SDA)`: GPIO 23
  - `TFT_SCLK (SCL)`: GPIO 18
  - `TFT_CS`: GPIO 15
  - `TFT_DC`: GPIO 2
  - `TFT_RST`: GPIO 4
  - `TFT_BL (PWM)`: GPIO 32
  - `BTN_ACTION / TOUCH`: GPIO 33 (Internal Pull-Up)
  - `BAT_ADC`: GPIO 35 (Voltage Divider: 100kΩ / 100kΩ)

---

## 2. Software Architecture & Graphics Pipeline

### A. Memory Budget
- **Display Resolution:** 172 (W) × 320 (H).
- **Color Depth:** 16-bit RGB565 (2 bytes/pixel).
- **Framebuffer Size:** $172 \times 320 \times 2 = 110,080\text{ bytes} \approx 107.5\text{ KB}$.
- **RAM Footprint:** ~110 KB Sprite buffer + ~60 KB FreeRTOS/Wi-Fi stack < 320 KB Internal SRAM (Completely Safe).

### B. Graphics Rendering Loop (Locked 60 FPS)
```cpp
void renderFrame() {
  sprite.fillScreen(0x0000);            // 1. Clear background (Deep Black)
  drawParticleRain();                   // 2. Render 40 falling pixel rain particles
  drawFloatingSprite(currentX, sinY);   // 3. Render Pixel Art Sword/Cat with Sine wave offset
  drawTypewriterQuote();                // 4. Render typewriter text on top
  drawBatteryIndicator();               // 5. Render mini battery bar
  sprite.pushSprite(0, 0);              // 6. Push single DMA buffer to LCD (Zero Tear)
}