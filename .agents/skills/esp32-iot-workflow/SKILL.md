---
name: esp32-iot-workflow
description: >-
  Comprehensive guide and runbook for ESP32 firmware development, building,
  flashing over COM ports (CP2102/CH340), reading serial logs, LittleFS filesystem
  management, and diagnosing Guru Meditation Errors. Use when compiling, debugging,
  or testing the Smart Keychain IoT firmware.
---

# ESP32 IoT Development & Debugging Workflow

This skill provides operational procedures for compiling, flashing, monitoring, and debugging the ESP32 NodeMCU DevKit V1 (ESP-WROOM-32) with 1.47" ST7789 display.

---

## Hardware Pinout Reference (ESP32 DevKit V1 <-> 1.47" ST7789 LCD 172x320)

| ST7789 Pin | ESP32 Pin | Function | Notes |
| :--- | :--- | :--- | :--- |
| **GND** | **GND** | Ground | Common ground |
| **VCC / VDD** | **3V3** | Power 3.3V | DO NOT connect to 5V / VIN |
| **SCL** | **GPIO 18** | SPI Clock (SCK) | VSPI Hardware SPI |
| **SDA** | **GPIO 23** | SPI MOSI (Data) | VSPI Hardware SPI |
| **RES / RST** | **GPIO 4** | Hardware Reset | Screen reset line |
| **DC** | **GPIO 2** | Data / Command | Command/Data toggle |
| **CS** | **GPIO 15** | Chip Select | Active low |
| **BL / BLK** | **3V3** or **GPIO 32** | Backlight | Connect to GPIO 32 for PWM dimming |

---

## 1. Build Firmware (PlatformIO)

To compile the project cleanly:
```bash
python -m platformio run
```

---

## 2. Flash Firmware to ESP32

To upload firmware to COM5:
```bash
python -m platformio run --target upload --upload-port COM5
```

> [!TIP]
> **If upload fails with "Failed to connect to Espressif device"**:
> 1. Press and **HOLD the `BOOT` (or `IO0`) button** on the ESP32 board.
> 2. Start the upload command.
> 3. Release the `BOOT` button as soon as you see `Connecting........___` change to `Writing at 0x...`.

---

## 3. Flash LittleFS Filesystem (Images / Web Assets)

To package and upload the `data/` directory to Flash:
```bash
python -m platformio run --target uploadfs --upload-port COM5
```

---

## 4. Real-time Serial Monitor & Crash Diagnostics

### Read Serial Logs (115200 Baud):
```bash
python .agents/skills/esp32-iot-workflow/scripts/serial_reader.py -p COM5 -b 115200 -t 15
```

### Decode Guru Meditation / Backtrace Logs:
```bash
python .agents/skills/esp32-iot-workflow/scripts/decode_stacktrace.py < serial_log.txt
```

To resolve exact source lines from backtrace addresses:
```bash
python -m platformio exec -- xtensa-esp32-elf-addr2line -pfia -e .pio/build/esp32dev/firmware.elf <addresses>
```
