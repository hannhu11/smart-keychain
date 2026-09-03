#!/usr/bin/env python3
import subprocess
import sys

def erase(port="COM5"):
    print("==================================================")
    print(f"   XÓA SẠCH BỘ NHỚ FLASH ESP32 (ERASE FLASH) - {port}")
    print("==================================================")
    print("👉 Hãy nhấn và GIỮ NGUYÊN nút 'BOOT' trên ESP32...")
    print("==================================================\n")
    
    cmd = [
        sys.executable, "-m", "esptool",
        "--port", port,
        "-b", "115200",
        "erase_flash"
    ]
    res = subprocess.run(cmd)
    return res.returncode

if __name__ == "__main__":
    port = sys.argv[1] if len(sys.argv) > 1 else "COM5"
    sys.exit(erase(port))
