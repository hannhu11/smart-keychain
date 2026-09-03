#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ESP32 IoT & Debugger MCP Server for Antigravity
Provides compilation, flashing, serial monitoring, crash analysis,
and sprite conversion tools for ESP32 DevKit and ST7789 displays.
"""

import os
import sys
import time
import subprocess
from typing import Optional
import serial
import serial.tools.list_ports
from mcp.server.mcpserver import MCPServer

server = MCPServer(
    name="esp32-iot-server",
    version="1.0.0",
    description="ESP32 PlatformIO Compiler, Flasher, Serial Monitor and Sprite Converter"
)

DEFAULT_PROJECT_DIR = r"c:\Users\ADMIN\Downloads\smart keychain"

@server.tool(description="List all available Serial COM ports and identify connected ESP32 chips (CP2102/CH340).")
def esp32_scan_ports() -> str:
    ports = serial.tools.list_ports.comports()
    if not ports:
        return "No serial COM ports found."
    lines = ["Available Serial COM Ports:"]
    for p in ports:
        desc = f"- {p.device}: {p.description} (VID:{p.vid:04X} PID:{p.pid:04X})" if p.vid else f"- {p.device}: {p.description}"
        lines.append(desc)
    return "\n".join(lines)

@server.tool(description="Compile the ESP32 PlatformIO firmware project.")
def esp32_build(project_dir: Optional[str] = None) -> str:
    cwd = project_dir or DEFAULT_PROJECT_DIR
    cmd = [sys.executable, "-m", "platformio", "run"]
    try:
        res = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, timeout=180)
        output = res.stdout + "\n" + res.stderr
        if res.returncode == 0:
            return f"[BUILD SUCCESSFUL]\n\n{output}"
        else:
            return f"[BUILD FAILED with code {res.returncode}]\n\n{output}"
    except Exception as e:
        return f"[ERROR] Failed to run PlatformIO build: {str(e)}"

@server.tool(description="Flash compiled firmware onto the ESP32 over serial port.")
def esp32_upload(port: str = "COM5", project_dir: Optional[str] = None) -> str:
    cwd = project_dir or DEFAULT_PROJECT_DIR
    cmd = [sys.executable, "-m", "platformio", "run", "--target", "upload", "--upload-port", port]
    try:
        res = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, timeout=120)
        output = res.stdout + "\n" + res.stderr
        if res.returncode == 0:
            return f"[UPLOAD SUCCESSFUL]\n\n{output}"
        else:
            tip = "\n[TIP] If device failed to connect, press and hold the 'BOOT' (IO0) button on the ESP32 while initiating upload."
            return f"[UPLOAD FAILED with code {res.returncode}]\n\n{output}{tip}"
    except Exception as e:
        return f"[ERROR] Failed to run PlatformIO upload: {str(e)}"

@server.tool(description="Build and flash LittleFS / SPIFFS filesystem image containing data/ directory to ESP32.")
def esp32_upload_fs(port: str = "COM5", project_dir: Optional[str] = None) -> str:
    cwd = project_dir or DEFAULT_PROJECT_DIR
    cmd = [sys.executable, "-m", "platformio", "run", "--target", "uploadfs", "--upload-port", port]
    try:
        res = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, timeout=120)
        output = res.stdout + "\n" + res.stderr
        if res.returncode == 0:
            return f"[LITTLEFS UPLOAD SUCCESSFUL]\n\n{output}"
        else:
            return f"[LITTLEFS UPLOAD FAILED with code {res.returncode}]\n\n{output}"
    except Exception as e:
        return f"[ERROR] Failed to run uploadfs: {str(e)}"

@server.tool(description="Monitor real-time Serial output from ESP32, detect Guru Meditation Errors, heap leaks, and panics.")
def esp32_serial_monitor(port: str = "COM5", baudrate: int = 115200, duration_seconds: int = 5) -> str:
    try:
        ser = serial.Serial(port, baudrate, timeout=0.5)
    except Exception as e:
        return f"[ERROR] Unable to open serial port {port}: {str(e)}"
    
    logs = []
    start = time.time()
    has_crash = False
    crash_info = []

    try:
        while time.time() - start < duration_seconds:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8', errors='replace').rstrip()
                if line:
                    logs.append(line)
                    if "Guru Meditation Error" in line or "Backtrace:" in line or "abort()" in line:
                        has_crash = True
                        crash_info.append(line)
            else:
                time.sleep(0.02)
    finally:
        ser.close()
        
    result_text = f"=== SERIAL LOGS ({port} @ {baudrate} baud, {duration_seconds}s) ===\n"
    result_text += "\n".join(logs) if logs else "(No serial data received during window)"
    
    if has_crash:
        result_text += "\n\n⚠️ [CRASH DETECTED IN LOGS]:\n" + "\n".join(crash_info)
        result_text += "\n\nRun 'esp32_decode_backtrace' to analyze the root cause."
        
    return result_text

@server.tool(description="Send string command or data to ESP32 over serial COM port.")
def esp32_serial_send(message: str, port: str = "COM5", baudrate: int = 115200) -> str:
    try:
        ser = serial.Serial(port, baudrate, timeout=1)
        ser.write((message + "\n").encode('utf-8'))
        time.sleep(0.1)
        resp = ser.read_all().decode('utf-8', errors='replace')
        ser.close()
        return f"Sent: {message}\nReceived response: {resp}"
    except Exception as e:
        return f"[ERROR] Failed to send to {port}: {str(e)}"

@server.tool(description="Convert an image (.png, .jpg, .bmp) or animated GIF to 16-bit RGB565 C++ header or LittleFS binary.")
def esp32_convert_image(image_path: str, format_type: str = "header", width: int = 0, height: int = 0,
                        output_path: Optional[str] = None, var_name: Optional[str] = None, swap_bytes: bool = False) -> str:
    script_path = os.path.join(DEFAULT_PROJECT_DIR, ".agents", "skills", "image-to-rgb565-converter", "scripts", "convert_image.py")
    if not os.path.exists(script_path):
        return f"[ERROR] Conversion script not found at {script_path}"
    
    cmd = [sys.executable, script_path, "-i", image_path, "-f", format_type]
    if width > 0:
        cmd.extend(["-w", str(width)])
    if height > 0:
        cmd.extend(["-ht", str(height)])
    if output_path:
        cmd.extend(["-o", output_path])
    if var_name:
        cmd.extend(["-n", var_name])
    if swap_bytes:
        cmd.append("--swap-bytes")
        
    try:
        res = subprocess.run(cmd, capture_output=True, text=True, timeout=60)
        return res.stdout + ("\n" + res.stderr if res.stderr else "")
    except Exception as e:
        return f"[ERROR] Failed to run image conversion: {str(e)}"

@server.tool(description="Decode Guru Meditation Error reasons and backtraces to find bug origin.")
def esp32_decode_backtrace(log_text: str) -> str:
    script_path = os.path.join(DEFAULT_PROJECT_DIR, ".agents", "skills", "esp32-iot-workflow", "scripts", "decode_stacktrace.py")
    try:
        res = subprocess.run([sys.executable, script_path], input=log_text, capture_output=True, text=True, timeout=30)
        return res.stdout
    except Exception as e:
        return f"[ERROR] Failed to run stacktrace decoder: {str(e)}"

if __name__ == "__main__":
    server.run(transport="stdio")
