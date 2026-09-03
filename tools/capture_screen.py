#!/usr/bin/env python3
import serial
import time
import sys
from PIL import Image

PORT = 'COM5'
BAUD = 115200
WIDTH = 172
HEIGHT = 320
TOTAL_BYTES = WIDTH * HEIGHT * 2

def capture():
    print(f'[CAPTURE] Dang ket noi toi {PORT}...')
    try:
        ser = serial.Serial()
        ser.port = PORT
        ser.baudrate = BAUD
        ser.timeout = 15.0
        ser.dtr = False
        ser.rts = False
        ser.open()
    except Exception as e:
        print(f'[ERROR] Khong the mo cong {PORT}: {e}')
        return False

    time.sleep(2.5) # Cho phep ESP32 render vai chuc frames on dinh
    ser.reset_input_buffer()
    
    print('[CAPTURE] Gui lenh #DUMP_SCREEN...')
    ser.write(b'#DUMP_SCREEN\n')
    
    start_time = time.time()
    line = ser.readline().decode('utf-8', errors='ignore').strip()
    while '#RAW_START' not in line and time.time() - start_time < 4.0:
        line = ser.readline().decode('utf-8', errors='ignore').strip()
        if line:
            print('[LOG]', line)

    if '#RAW_START' not in line:
        print('[ERROR] ESP32S khong phan hoi tin hieu bat dau frame!')
        ser.close()
        return False

    print('[CAPTURE] Dang doc 110,080 bytes RGB565...')
    raw_data = bytearray()
    read_start = time.time()
    while len(raw_data) < TOTAL_BYTES and time.time() - read_start < 15.0:
        chunk = ser.read(TOTAL_BYTES - len(raw_data))
        if chunk:
            raw_data.extend(chunk)

    ser.close()

    if len(raw_data) != TOTAL_BYTES:
        print(f'[ERROR] Nhan thieu du lieu: {len(raw_data)}/{TOTAL_BYTES} bytes')
        return False

    print('[CAPTURE] Chuyen doi sang anh RGB888 PNG...')
    img = Image.new('RGB', (WIDTH, HEIGHT))
    pixels = img.load()

    for y in range(HEIGHT):
        for x in range(WIDTH):
            idx = (y * WIDTH + x) * 2
            pixel565 = (raw_data[idx] << 8) | raw_data[idx + 1]
            r = ((pixel565 >> 11) & 0x1F) * 255 // 31
            g = ((pixel565 >> 5) & 0x3F) * 255 // 63
            b = (pixel565 & 0x1F) * 255 // 31
            pixels[x, y] = (r, g, b)

    output_path = 'tools/screen_dump.png'
    img.save(output_path)
    print(f'[SUCCESS] Da xuat anh thanh cong tai {output_path}!')
    return True

if __name__ == '__main__':
    success = capture()
    sys.exit(0 if success else 1)
