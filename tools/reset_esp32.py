import time
import serial

def reset_to_bootloader(port="COM5"):
    print(f"Resetting ESP32 on {port} into bootloader...")
    ser = serial.Serial(port, 115200)
    ser.dtr = False
    ser.rts = False
    time.sleep(0.1)
    # IO0 = LOW, EN = LOW (Reset)
    ser.dtr = True
    ser.rts = True
    time.sleep(0.1)
    # EN = HIGH, IO0 = LOW (Enter bootloader)
    ser.rts = False
    ser.dtr = True
    time.sleep(0.1)
    ser.dtr = False
    time.sleep(0.1)
    ser.close()
    print("Reset sequence complete!")

if __name__ == "__main__":
    reset_to_bootloader()
