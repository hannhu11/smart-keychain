#!/usr/bin/env python3
import subprocess
import sys
import serial.tools.list_ports

def get_com_port():
    ports = list(serial.tools.list_ports.comports())
    if not ports:
        return None
    for p in ports:
        if "CP210" in p.description or "CH340" in p.description or "USB" in p.description:
            return p.device
    return ports[0].device

def upload():
    port = sys.argv[1] if len(sys.argv) > 1 else get_com_port()
    if not port:
        print("[ERROR] Không tìm thấy bo mạch nào được cắm vào cổng USB!")
        print("👉 Hãy cắm bo mạch ESP8266 vào máy tính bằng cáp Micro-USB rồi chạy lại lệnh.")
        sys.exit(1)
        
    print("==================================================")
    print(f"   BIÊN DỊCH & NẠP CODE CHO ESP8266 ({port})     ")
    print("==================================================")
    
    cmd = [
        sys.executable, "-m", "platformio", "run",
        "-e", "nodemcuv2",
        "--target", "upload",
        "--upload-port", port
    ]
    res = subprocess.run(cmd)
    if res.returncode == 0:
        print("\n🎉🎉🎉 NẠP CODE CHO ESP8266 THÀNH CÔNG 100%!")
    return res.returncode

if __name__ == "__main__":
    sys.exit(upload())
