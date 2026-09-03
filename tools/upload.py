#!/usr/bin/env python3
import subprocess
import sys
import time

def upload_firmware(port="COM5", baud="115200"):
    print("==================================================")
    print(f"  NẠP FIRMWARE ESP32 QUA CỔNG {port} ({baud} BAUD)")
    print("==================================================")
    print("👉 HƯỚNG DẪN QUAN TRỌNG:")
    print("   Nếu màn hình hiện 'Connecting........___', bạn hãy:")
    print("   1. Nhấn và GIỮ nút 'BOOT' trên bo mạch ESP32.")
    print("   2. Thả tay ra ngay khi thấy chữ 'Writing at 0x...'.")
    print("==================================================\n")
    
    cmd = [sys.executable, "-m", "platformio", "run", "--target", "upload", "--upload-port", port]
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, bufsize=1)
    
    for line in proc.stdout:
        print(line, end="")
        
    proc.wait()
    return proc.returncode

if __name__ == "__main__":
    port = sys.argv[1] if len(sys.argv) > 1 else "COM5"
    sys.exit(upload_firmware(port))
