#!/usr/bin/env python3
import serial
import time
import sys

port = "COM5" if len(sys.argv) <= 1 else sys.argv[1]

print(f"=== ĐANG LẮNG NGHE TÍN HIỆU TỪ ESP32 TRÊN {port} ===")
print("👉 Hãy thử:")
print("   1. Cắm chặt lại đầu cáp Micro-USB trên ESP32.")
print("   2. Nhấn nút 'EN' (nút bên phải) trên ESP32.")
print("   3. Nhấn nút 'BOOT' (nút bên trái).")
print("====================================================\n")

try:
    s = serial.Serial(port, 115200, timeout=0.1)
    start = time.time()
    while time.time() - start < 15:
        if s.in_waiting:
            data = s.read(s.in_waiting)
            try:
                text = data.decode('utf-8', errors='replace')
                print(f"[NHẬN TÍN HIỆU]: {text}", end="")
            except:
                print(f"[BYTE DATA]: {data}")
        time.sleep(0.02)
    s.close()
    print("\n[HẾT THỜI GIAN] Nếu không có tín hiệu, hãy kiểm tra lại tiếp xúc cổng cắm cáp USB.")
except Exception as e:
    print("[ERROR]", e)
