#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Figma MCP Server (Official MCP Protocol for Antigravity & AI IDEs)
Enables AI agents to query Figma design files, components, styles, comments,
and export high-res assets or 16-bit RGB565 arrays for ESP32 displays.
"""

import sys
import json
import os
import urllib.request
import urllib.parse
from typing import Optional, List
from PIL import Image
import io
from mcp.server.mcpserver import MCPServer

server = MCPServer(
    name="figma",
    version="1.0.0",
    description="Figma MCP Server for design inspection, token extraction, and RGB565 export"
)

FIGMA_API_BASE = "https://api.figma.com/v1"
DEFAULT_TOKEN = os.environ.get("FIGMA_ACCESS_TOKEN", os.environ.get("FIGMA_PERSONAL_ACCESS_TOKEN", ""))

def make_figma_request(endpoint: str, token: Optional[str] = None, method: str = "GET", data: Optional[dict] = None) -> dict:
    auth_token = token or DEFAULT_TOKEN
    if not auth_token:
        return {"error": "Missing Figma Access Token. Set FIGMA_ACCESS_TOKEN env variable or pass 'api_token'."}
    
    url = f"{FIGMA_API_BASE}/{endpoint}"
    req = urllib.request.Request(url, method=method)
    req.add_header("X-Figma-Token", auth_token)
    req.add_header("User-Agent", "Antigravity-Figma-MCP/1.0")
    
    if data:
        json_data = json.dumps(data).encode("utf-8")
        req.add_header("Content-Type", "application/json")
        req.data = json_data

    try:
        with urllib.request.urlopen(req, timeout=30) as resp:
            return json.loads(resp.read().decode("utf-8"))
    except urllib.error.HTTPError as e:
        err_msg = e.read().decode("utf-8")
        return {"error": f"Figma API HTTP {e.code}: {err_msg}"}
    except Exception as e:
        return {"error": f"Figma Request Failed: {str(e)}"}

def extract_file_key(key_or_url: str) -> str:
    if "figma.com" in key_or_url:
        parts = key_or_url.split("/")
        for idx, part in enumerate(parts):
            if part in ("file", "design", "board") and idx + 1 < len(parts):
                return parts[idx + 1]
    return key_or_url

@server.tool(description="Fetch Figma file JSON tree, components, frames, and vector geometry.")
def figma_get_file(file_key: str, depth: int = 2, api_token: Optional[str] = None) -> str:
    k = extract_file_key(file_key)
    res = make_figma_request(f"files/{k}?depth={depth}", api_token)
    return json.dumps(res, ensure_ascii=False, indent=2)

@server.tool(description="Get detailed properties of specific node IDs in a Figma file.")
def figma_get_node(file_key: str, node_ids: List[str], api_token: Optional[str] = None) -> str:
    k = extract_file_key(file_key)
    node_str = ",".join(node_ids) if isinstance(node_ids, list) else str(node_ids)
    res = make_figma_request(f"files/{k}/nodes?ids={urllib.parse.quote(node_str)}", api_token)
    return json.dumps(res, ensure_ascii=False, indent=2)

@server.tool(description="Render and download images of specific frames/nodes from a Figma file.")
def figma_get_image(file_key: str, node_ids: List[str], format: str = "png", scale: float = 2.0, api_token: Optional[str] = None) -> str:
    k = extract_file_key(file_key)
    node_str = ",".join(node_ids) if isinstance(node_ids, list) else str(node_ids)
    res = make_figma_request(f"images/{k}?ids={urllib.parse.quote(node_str)}&format={format}&scale={scale}", api_token)
    return json.dumps(res, ensure_ascii=False, indent=2)

@server.tool(description="Get design tokens, typography styles, and color palettes from a Figma file.")
def figma_get_styles(file_key: str, api_token: Optional[str] = None) -> str:
    k = extract_file_key(file_key)
    res = make_figma_request(f"files/{k}/styles", api_token)
    return json.dumps(res, ensure_ascii=False, indent=2)

@server.tool(description="Get comments on a Figma file for feedback loops.")
def figma_get_comments(file_key: str, api_token: Optional[str] = None) -> str:
    k = extract_file_key(file_key)
    res = make_figma_request(f"files/{k}/comments", api_token)
    return json.dumps(res, ensure_ascii=False, indent=2)

@server.tool(description="Post a comment on a Figma file.")
def figma_post_comment(file_key: str, message: str, api_token: Optional[str] = None) -> str:
    k = extract_file_key(file_key)
    res = make_figma_request(f"files/{k}/comments", api_token, method="POST", data={"message": message})
    return json.dumps(res, ensure_ascii=False, indent=2)

@server.tool(description="Download an image URL and convert to 16-bit RGB565 C++ PROGMEM array for ESP32 displays.")
def figma_export_rgb565(image_url: str, var_name: str = "figma_sprite", width: int = 172, height: int = 320) -> str:
    if not image_url:
        return json.dumps({"error": "Missing 'image_url'"}, indent=2)
        
    try:
        req = urllib.request.Request(image_url, headers={"User-Agent": "Antigravity/1.0"})
        with urllib.request.urlopen(req, timeout=30) as resp:
            img_bytes = resp.read()
            
        img = Image.open(io.BytesIO(img_bytes)).convert("RGB")
        if width and height:
            img = img.resize((width, height), Image.Resampling.LANCZOS)
        
        w, h = img.size
        c_lines = [
            f"// Auto-generated from Figma MCP Exporter ({w}x{h} RGB565)",
            f"const uint16_t {var_name}[{w * h}] PROGMEM = {{"
        ]
        
        row = []
        for y in range(h):
            for x in range(w):
                r, g, b = img.getpixel((x, y))
                r5 = (r >> 3) & 0x1F
                g6 = (g >> 2) & 0x3F
                b5 = (b >> 3) & 0x1F
                rgb565 = (r5 << 11) | (g6 << 5) | b5
                row.append(f"0x{rgb565:04X}")
                if len(row) >= 12:
                    c_lines.append("  " + ", ".join(row) + ",")
                    row = []
        if row:
            c_lines.append("  " + ", ".join(row))
        c_lines.append("};")
        
        res = {
            "status": "success",
            "width": w,
            "height": h,
            "total_pixels": w * h,
            "c_header": "\n".join(c_lines)
        }
        return json.dumps(res, ensure_ascii=False, indent=2)
    except Exception as e:
        return json.dumps({"error": f"RGB565 Conversion Failed: {str(e)}"}, indent=2)

if __name__ == "__main__":
    server.run(transport="stdio")
