#!/usr/bin/env python3
import subprocess
import sys
import os

def flash(port="COM5"):
    print("==================================================")
    print(f"  CHẾ ĐỘ NẠP TRỰC TIẾP (DIRECT BOOTLOADER) - {port}")
    print("==================================================")
    print("👉 Hãy làm theo đúng 3 thao tác bấm nút sau:")
    print("   1. Nhấn và GIỮ nút 'BOOT' (bên trái cổng USB).")
    print("   2. Bấm nhả nút 'EN' (bên phải cổng USB) 1 cái.")
    print("   3. Thả nút 'BOOT' ra.")
    print("==================================================")
    
    bin_path = os.path.join(".pio", "build", "esp32dev", "firmware.bin")
    bootloader_path = os.path.join(".pio", "build", "esp32dev", "bootloader.bin")
    partitions_path = os.path.join(".pio", "build", "esp32dev", "partitions.bin")
    
    if not os.path.exists(bin_path):
        print(f"[ERROR] Không tìm thấy file {bin_path}. Đang biên dịch lại...")
        subprocess.run([sys.executable, "-m", "platformio", "run"])
        
    cmd = [
        sys.executable, "-m", "esptool",
        "--port", port,
        "-b", "460800",
        "--before", "no-reset",
        "--after", "hard-reset",
        "write_flash", "-z",
        "--flash_mode", "dio",
        "--flash_freq", "40m",
        "--flash_size", "4MB",
        "0x1000", bootloader_path if os.path.exists(bootloader_path) else "0x1000",
        "0x8000", partitions_path if os.path.exists(partitions_path) else "0x8000",
        "0x10000", bin_path
    ]
    
    # Fallback to standard platformio upload if paths differ
    print("\n[BƯỚC 2] Đang nạp firmware...")
    res = subprocess.run([sys.executable, "-m", "platformio", "run", "--target", "upload", "--upload-port", port])
    return res.returncode

if __name__ == "__main__":
    port = sys.argv[1] if len(sys.argv) > 1 else "COM5"
    sys.exit(flash(port))
