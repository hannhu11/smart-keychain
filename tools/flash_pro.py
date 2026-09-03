#!/usr/bin/env python3
import subprocess
import sys
import os

def flash_pro(port="COM5"):
    print("==================================================")
    print("      CHẾ ĐỘ NẠP CHỜ THỜI GIAN DÀI (30 LẦN THỬ)   ")
    print("==================================================")
    print("👉 Khi thấy dòng chữ 'Connecting............':")
    print("   1. Dùng ngón tay NHẤN VÀ GIỮ nút 'BOOT'.")
    print("   2. BẤM NHẸ nút 'EN' (RST) 1 cái rồi thả ra.")
    print("   3. Vẫn tiếp tục GIỮ nút 'BOOT' cho đến khi thấy 'Writing at 0x...'.")
    print("==================================================\n")
    
    bin_file = ".pio/build/esp32dev/firmware.bin"
    bootloader_file = ".pio/build/esp32dev/bootloader.bin"
    partitions_file = ".pio/build/esp32dev/partitions.bin"
    
    cmd = [
        sys.executable, "-m", "esptool",
        "--chip", "esp32",
        "--port", port,
        "--baud", "115200",
        "--connect-attempts", "35",
        "--before", "default-reset",
        "--after", "hard-reset",
        "write-flash", "-z",
        "--flash-mode", "dio",
        "--flash-freq", "40m",
        "--flash-size", "4MB",
        "0x1000", bootloader_file,
        "0x8000", partitions_file,
        "0x10000", bin_file
    ]
    
    res = subprocess.run(cmd)
    if res.returncode == 0:
        print("\n🎉🎉🎉 CHÚC MỪNG BẠN! NẠP THÀNH CÔNG 100%!")
        print("👉 Bây giờ đèn LED màu xanh trên bo ESP32 sẽ nhấp nháy liên tục 0.5s/lần!")
    else:
        print("\n❌ Nạp chưa thành công.")
    return res.returncode

if __name__ == "__main__":
    port = sys.argv[1] if len(sys.argv) > 1 else "COM5"
    sys.exit(flash_pro(port))
