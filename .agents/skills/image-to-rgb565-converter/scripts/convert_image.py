#!/usr/bin/env python3
"""
Image to RGB565 & Sprite Converter for ESP32 / LovyanGFX / ST7789
Supports PNG, JPG, BMP, WEBP, and Animated GIFs.
Outputs C++ Header (PROGMEM) or LittleFS raw binary files.
"""

import os
import sys
import argparse
from PIL import Image, ImageSequence

def rgb888_to_rgb565(r, g, b, swap_bytes=False):
    """Converts 8-bit R, G, B to 16-bit RGB565 integer."""
    val = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
    if swap_bytes:
        # Swap high and low bytes for SPI big-endian streaming
        val = ((val & 0xFF) << 8) | ((val >> 8) & 0xFF)
    return val

def process_frame(img, target_width=None, target_height=None, bg_color=(0, 0, 0)):
    """Prepares PIL Image frame: converts RGBA/palette to RGB with background blending."""
    if target_width and target_height:
        img = img.resize((target_width, target_height), Image.Resampling.LANCZOS)
    
    if img.mode == 'RGBA':
        background = Image.new('RGB', img.size, bg_color)
        background.paste(img, mask=img.split()[3])
        return background
    else:
        return img.convert('RGB')

def convert_to_rgb565_array(img, swap_bytes=False):
    """Returns a list of uint16 RGB565 values for all pixels."""
    pixels = []
    width, height = img.size
    for y in range(height):
        for x in range(width):
            r, g, b = img.getpixel((x, y))
            pixels.append(rgb888_to_rgb565(r, g, b, swap_bytes))
    return pixels

def convert_single_image(input_path, output_path=None, target_width=None, target_height=None,
                         format_type='header', var_name=None, swap_bytes=False, output_dir=None):
    """Converts a static image file."""
    img = Image.open(input_path)
    img_rgb = process_frame(img, target_width, target_height)
    width, height = img_rgb.size
    
    base_name = os.path.splitext(os.path.basename(input_path))[0]
    var_name = var_name or base_name.replace('-', '_').replace(' ', '_')
    
    pixels = convert_to_rgb565_array(img_rgb, swap_bytes)
    
    if format_type == 'binary':
        out_file = output_path or os.path.join(output_dir or 'data', f"{var_name}_{width}x{height}.bin")
        os.makedirs(os.path.dirname(os.path.abspath(out_file)), exist_ok=True)
        with open(out_file, 'wb') as f:
            for p in pixels:
                f.write(p.to_bytes(2, byteorder='little' if not swap_bytes else 'big'))
        print(f"[SUCCESS] Wrote raw LittleFS binary: {out_file} ({width}x{height}, {len(pixels)*2} bytes)")
        return out_file
    else:
        out_file = output_path or f"{var_name}.h"
        os.makedirs(os.path.dirname(os.path.abspath(out_file)), exist_ok=True)
        with open(out_file, 'w', encoding='utf-8') as f:
            f.write(f"// Generated RGB565 sprite from: {os.path.basename(input_path)}\n")
            f.write(f"// Dimensions: {width} x {height} ({len(pixels)} pixels)\n")
            f.write(f"#pragma once\n#include <Arduino.h>\n\n")
            f.write(f"const uint16_t {var_name}_width = {width};\n")
            f.write(f"const uint16_t {var_name}_height = {height};\n\n")
            f.write(f"const uint16_t {var_name}_data[] PROGMEM = {{\n")
            for i, p in enumerate(pixels):
                if i % 16 == 0:
                    f.write("  ")
                f.write(f"0x{p:04X}, ")
                if i % 16 == 15:
                    f.write("\n")
            f.write("\n};\n")
        print(f"[SUCCESS] Wrote C++ header: {out_file} ({width}x{height}, {len(pixels)} pixels)")
        return out_file

def convert_gif_animation(input_path, output_path=None, target_width=None, target_height=None,
                          format_type='header', var_name=None, swap_bytes=False, output_dir=None):
    """Converts a multi-frame GIF animation."""
    gif = Image.open(input_path)
    base_name = os.path.splitext(os.path.basename(input_path))[0]
    var_name = var_name or base_name.replace('-', '_').replace(' ', '_')
    
    frames = []
    durations = []
    
    for frame in ImageSequence.Iterator(gif):
        duration = frame.info.get('duration', 100) # default 100ms
        durations.append(duration)
        processed = process_frame(frame, target_width, target_height)
        frames.append(processed)
        
    num_frames = len(frames)
    width, height = frames[0].size
    total_pixels_per_frame = width * height
    
    print(f"[INFO] GIF contains {num_frames} frames ({width}x{height})")
    
    if format_type == 'binary':
        target_folder = output_dir or os.path.join('data', var_name)
        os.makedirs(target_folder, exist_ok=True)
        meta_file = os.path.join(target_folder, "meta.txt")
        with open(meta_file, 'w') as mf:
            mf.write(f"width={width}\nheight={height}\nframes={num_frames}\ndelay={int(sum(durations)/max(1, len(durations)))}\n")
            
        for idx, frm in enumerate(frames):
            pixels = convert_to_rgb565_array(frm, swap_bytes)
            frame_bin = os.path.join(target_folder, f"frame_{idx:02d}.bin")
            with open(frame_bin, 'wb') as f:
                for p in pixels:
                    f.write(p.to_bytes(2, byteorder='little' if not swap_bytes else 'big'))
        print(f"[SUCCESS] Wrote {num_frames} LittleFS binary frames to directory: {target_folder}")
        return target_folder
    else:
        out_file = output_path or f"{var_name}_anim.h"
        os.makedirs(os.path.dirname(os.path.abspath(out_file)), exist_ok=True)
        with open(out_file, 'w', encoding='utf-8') as f:
            f.write(f"// Generated RGB565 GIF Animation: {os.path.basename(input_path)}\n")
            f.write(f"// Frames: {num_frames}, Dimensions: {width} x {height}\n")
            f.write(f"#pragma once\n#include <Arduino.h>\n\n")
            f.write(f"const uint16_t {var_name}_frame_count = {num_frames};\n")
            f.write(f"const uint16_t {var_name}_width = {width};\n")
            f.write(f"const uint16_t {var_name}_height = {height};\n")
            avg_delay = int(sum(durations) / max(1, len(durations)))
            f.write(f"const uint16_t {var_name}_frame_delay_ms = {avg_delay};\n\n")
            
            f.write(f"const uint16_t {var_name}_frames[{num_frames}][{total_pixels_per_frame}] PROGMEM = {{\n")
            for idx, frm in enumerate(frames):
                pixels = convert_to_rgb565_array(frm, swap_bytes)
                f.write(f"  // --- Frame {idx} ---\n  {{\n")
                for i, p in enumerate(pixels):
                    if i % 16 == 0:
                        f.write("    ")
                    f.write(f"0x{p:04X}, ")
                    if i % 16 == 15:
                        f.write("\n")
                f.write("\n  },\n")
            f.write("};\n")
        print(f"[SUCCESS] Wrote C++ Animated Header: {out_file} ({num_frames} frames)")
        return out_file

def main():
    parser = argparse.ArgumentParser(description="Convert images/GIFs to RGB565 format for ESP32/LovyanGFX")
    parser.add_argument("-i", "--input", required=True, help="Path to input image/gif")
    parser.add_argument("-o", "--output", help="Output file path (.h or .bin)")
    parser.add_argument("-w", "--width", type=int, help="Target resize width (e.g. 172)")
    parser.add_argument("-ht", "--height", type=int, help="Target resize height (e.g. 320)")
    parser.add_argument("-f", "--format", choices=['header', 'binary'], default='header', help="Output format")
    parser.add_argument("-n", "--name", help="C++ variable name")
    parser.add_argument("--swap-bytes", action="store_true", help="Swap high/low byte (for SPI raw big-endian)")
    parser.add_argument("-d", "--output-dir", help="Output directory for LittleFS binary files (e.g. data/)")
    
    args = parser.parse_args()
    
    if not os.path.exists(args.input):
        print(f"[ERROR] Input file not found: {args.input}", file=sys.stderr)
        sys.exit(1)
        
    ext = os.path.splitext(args.input)[1].lower()
    if ext == '.gif':
        convert_gif_animation(
            args.input, args.output, args.width, args.height,
            args.format, args.name, args.swap_bytes, args.output_dir
        )
    else:
        convert_single_image(
            args.input, args.output, args.width, args.height,
            args.format, args.name, args.swap_bytes, args.output_dir
        )

if __name__ == "__main__":
    main()
