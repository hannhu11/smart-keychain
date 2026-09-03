import subprocess
import sys
import serial.tools.list_ports

def get_com_port():
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        desc = p.description.lower()
        if "cp210" in desc or "ch340" in desc or "usb-serial" in desc or "uart" in desc:
            return p.device
    if ports:
        return ports[0].device
    return "COM5"

port = sys.argv[1] if len(sys.argv) > 1 else get_com_port()

print("="*60)
print(f"  NẠP FIRMWARE DIGITAL KEYCHAIN CHO ESP32S QUA CỔNG {port}")
print("="*60)

cmd = ["python", "-m", "platformio", "run", "-e", "esp32dev", "--target", "upload", "--upload-port", port]
res = subprocess.run(cmd)

if res.returncode == 0:
    print("\n" + "="*60)
    print("  🎉 NẠP CODE THÀNH CÔNG 100% VÀO ESP32S!")
    print("="*60)
else:
    print("\n" + "="*60)
    print("  ⚠️ NẠP CHƯA THÀNH CÔNG. HÃY GIỮ NÚT BOOT TRÊN ESP32 KHI NẠP!")
    print("="*60)
