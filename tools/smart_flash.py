#!/usr/bin/env python3
import subprocess
import sys
import time
import serial

PORT = "COM5"

print("==================================================")
print("     TOOL TỰ ĐỘNG BẮT TÍN HIỆU & NẠP CODE CHIP    ")
print("==================================================")
print("👉 BƯỚC ĐƠN GIẢN DUY NHẤT:")
print("   Dùng ngón tay NHẤN VÀ GIỮ NGUYÊN NÚT 'BOOT' trên ESP32...")
print("==================================================\n")

for attempt in range(1, 15):
    print(f"[{attempt}/14] Đang tìm bắt tín hiệu chip ESP32 (Hãy giữ nút BOOT)...")
    res = subprocess.run([
        sys.executable, "-m", "esptool",
        "--chip", "esp32",
        "--port", PORT,
        "--baud", "115200",
        "--before", "default-reset",
        "--after", "hard-reset",
        "chip-id"
    ], capture_output=True, text=True)
    
    if "Detecting chip type... ESP32" in res.stdout or "Chip is ESP32" in res.stdout or res.returncode == 0:
        print("\n🎉 ĐÃ KẾT NỐI ĐƯỢC CHIP ESP32 THÀNH CÔNG!")
        print(res.stdout)
        print(">>> BẮT ĐẦU NẠP CODE BLINK TEST NGAY LẬP TỨC...")
        
        flash_res = subprocess.run([
            sys.executable, "-m", "esptool",
            "--chip", "esp32",
            "--port", PORT,
            "--baud", "115200",
            "--before", "no-reset",
            "--after", "hard-reset",
            "write-flash", "-z",
            "--flash-mode", "dio",
            "--flash-freq", "40m",
            "--flash-size", "4MB",
            "0x1000", ".pio/build/esp32dev/bootloader.bin",
            "0x8000", ".pio/build/esp32dev/partitions.bin",
            "0x10000", ".pio/build/esp32dev/firmware.bin"
        ])
        if flash_res.returncode == 0:
            print("\n🎉🎉🎉 NẠP THÀNH CÔNG 100%! ĐÈN LED XANH TRÊN CHIP SẼ BẮT ĐẦU NHẤP NHÁY!")
            sys.exit(0)
    time.sleep(0.5)

print("\n❌ Chưa bắt được tín hiệu. Hãy thử nối 1 dây từ chân GND sang chân D0 (hoặc nút BOOT) rồi chạy lại!")
