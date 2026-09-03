#!/usr/bin/env python3
import subprocess
import sys
import time

def upload_loop(port="COM5", retries=10):
    print("==================================================")
    print(f"  ĐANG BẮT ĐẦU CHẾ ĐỘ NẠP TỰ ĐỘNG ({port})")
    print("👉 HÃY NHẤN VÀ GIỮ NÚT 'BOOT' TRÊN ESP32 NGAY BÂY GIỜ!")
    print("==================================================\n")
    
    cmd = [sys.executable, "-m", "platformio", "run", "--target", "upload", "--upload-port", port]
    
    for attempt in range(1, retries + 1):
        print(f"\n[LẦN THỬ {attempt}/{retries}] Đang kết nối tới ESP32... (Hãy giữ nút BOOT)")
        res = subprocess.run(cmd, capture_output=True, text=True)
        out = res.stdout + "\n" + res.stderr
        
        if "Writing at 0x" in out or res.returncode == 0:
            print(out)
            print("\n🎉 [THÀNH CÔNG] ĐÃ NẠP XONG FIRMWARE VÀO ESP32!")
            print("👉 Bạn hãy THẢ TAY khỏi nút BOOT và nhấn nhẹ nút EN/RST một lần!")
            return 0
        else:
            if "Connecting" in out:
                print("... Chưa bắt được tín hiệu Bootloader, đang thử lại ngay ...")
            time.sleep(1)
            
    print("\n[LỖI] Đã hết số lần thử. Vui lòng kiểm tra lại cáp USB và nhấn giữ nút BOOT.")
    return 1

if __name__ == "__main__":
    port = sys.argv[1] if len(sys.argv) > 1 else "COM5"
    sys.exit(upload_loop(port))
