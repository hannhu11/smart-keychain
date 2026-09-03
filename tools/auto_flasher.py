import subprocess
import time
import sys

print(">>> AUTO-FLASHER: Starting rapid handshake on COM5...")
for attempt in range(1, 5):
    print(f"\n--- Attempt {attempt}/4 ---")
    cmd = [sys.executable, "-m", "esptool", "--port", "COM5", "--baud", "460800", "--before", "default_reset", "--after", "hard_reset", "write_flash", "-z", "0x10000", r".pio\build\esp32dev\firmware.bin"]
    res = subprocess.run(cmd, capture_output=True, text=True)
    if res.returncode == 0:
        print("🎉 FLASH SUCCESSFUL!")
        print(res.stdout)
        sys.exit(0)
    else:
        print("Retrying in 1s...")
        time.sleep(1)

print("Flash finished.")
