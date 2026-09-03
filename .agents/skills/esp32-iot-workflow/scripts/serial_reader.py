#!/usr/bin/env python3
"""
Real-time Serial Reader & Crash Monitor for ESP32
"""

import sys
import time
import argparse
import serial
import serial.tools.list_ports

def list_ports():
    ports = serial.tools.list_ports.comports()
    print("=== AVAILABLE SERIAL COM PORTS ===")
    for p in ports:
        print(f"  {p.device} - {p.description} (VID:PID = {p.vid}:{p.pid})")
    return [p.device for p in ports]

def monitor_serial(port, baudrate=115200, timeout_sec=10, capture_errors=True):
    print(f"[INFO] Opening serial port {port} at {baudrate} baud...")
    try:
        ser = serial.Serial(port, baudrate, timeout=1)
    except Exception as e:
        print(f"[ERROR] Could not open {port}: {e}")
        return
        
    start_time = time.time()
    buffer = []
    print(f"[INFO] Listening for {timeout_sec} seconds (Press Ctrl+C to stop)...\n" + "-"*40)
    
    try:
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8', errors='replace')
                sys.stdout.write(line)
                sys.stdout.flush()
                buffer.append(line)
                
                if capture_errors and ("Guru Meditation" in line or "Backtrace:" in line):
                    print("\n[ALERT] Crash detected in log stream!")
            else:
                time.sleep(0.01)
                
            if timeout_sec and (time.time() - start_time > timeout_sec):
                print("\n" + "-"*40 + f"\n[INFO] Timeout of {timeout_sec}s reached.")
                break
    except KeyboardInterrupt:
        print("\n[INFO] Stopped by user.")
    finally:
        ser.close()
        
    return "".join(buffer)

def main():
    parser = argparse.ArgumentParser(description="ESP32 Serial Monitor & Crash Logger")
    parser.add_argument("-p", "--port", default="COM5", help="COM Port (default COM5)")
    parser.add_argument("-b", "--baud", type=int, default=115200, help="Baud rate (default 115200)")
    parser.add_argument("-t", "--timeout", type=int, default=10, help="Listen duration in seconds (0 = forever)")
    parser.add_argument("-l", "--list", action="store_true", help="List COM ports")
    
    args = parser.parse_args()
    if args.list:
        list_ports()
    else:
        monitor_serial(args.port, args.baud, args.timeout)

if __name__ == "__main__":
    main()
