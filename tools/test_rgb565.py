def hex_to_rgb565(hex_str):
    hex_str = hex_str.lstrip('#')
    r = int(hex_str[0:2], 16)
    g = int(hex_str[2:4], 16)
    b = int(hex_str[4:6], 16)
    rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
    return f"0x{rgb565:04X}"

colors = {
    "C_FRESNEL_RIM": "#CCFBF1",
    "C_BODY_CYAN": "#22D3EE",
    "C_BODY_LIGHT": "#67E8F9",
    "C_BODY_CORE_SSS": "#0284C7",
    "C_DEEP_CYAN": "#0E7490",
    "C_JADE_CORE": "#34D399",
    "C_JADE_GLOW": "#6EE7B7",
    "C_RUBY_DEEP": "#991B1B",
    "C_RUBY_CORE": "#DC2626",
    "C_RUBY_BRIGHT": "#EF4444",
    "C_GOLD_CROWN": "#F59E0B",
    "C_GOLD_BRIGHT": "#FEF08A",
    "C_GOLD_EYE_RING": "#FACC15",
    "C_EYE_DARK": "#03254C",
    "C_EYE_IRIS_BLUE": "#1D4ED8",
    "C_EYE_IRIS_AQUA": "#38BDF8",
    "C_BLUSH_PINK": "#FB7185",
    "C_MOUTH_DEEP": "#9F1239",
    "C_MOUTH_TONGUE": "#FDA4AF",
    "C_BUBBLE_GLOW": "#7DD3FC",
    "C_SEABED_SHADOW": "#041E34",
    "C_WHITE": "#FFFFFF"
}

for name, hx in colors.items():
    print(f"const uint16_t {name:16} = {hex_to_rgb565(hx)}; // {hx}")
