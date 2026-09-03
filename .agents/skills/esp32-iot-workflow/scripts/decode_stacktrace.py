#!/usr/bin/env python3
"""
ESP32 Stacktrace and Guru Meditation Error Decoder
"""

import sys
import re

EXCEPTION_CAUSES = {
    0: "IllegalInstruction (Instruction is invalid or unimplemented)",
    1: "Syscall",
    2: "InstructionFetchError",
    3: "LoadStoreError",
    4: "Level1Interrupt",
    5: "AllocaCause",
    6: "IntegerDivideByZero",
    12: "InstrCheckFailed",
    14: "LoadProhibited (Attempted to read from an invalid memory address / NULL pointer dereference)",
    15: "StoreProhibited (Attempted to write to a read-only or invalid memory address / buffer overflow)",
    28: "StackOverflow (Corrupted stack canary)",
    29: "UnhandledInterrupt",
}

def analyze_log(log_text):
    print("=== ESP32 DIAGNOSTIC REPORT ===")
    
    # Check for Guru Meditation Error
    guru_match = re.search(r"Guru Meditation Error: Core\s+(\d+)\s+panic'ed \((.*?)\)", log_text)
    if guru_match:
        core = guru_match.group(1)
        reason = guru_match.group(2)
        print(f"[CRITICAL] Guru Meditation Error on Core {core}: {reason}")
        if "LoadProhibited" in reason:
            print("  -> Root Cause: NULL pointer dereference or accessing deleted object.")
            print("  -> Suggestion: Check uninitialized pointers (e.g. nullptr sprite, unmounted LittleFS, unallocated buffer).")
        elif "StoreProhibited" in reason:
            print("  -> Root Cause: Writing out of bounds or to Flash memory/const pointer.")
            print("  -> Suggestion: Verify array boundary indices and buffer allocations.")
        elif "Stack canary" in reason or "StackOverflow" in reason:
            print("  -> Root Cause: Stack memory overflow inside a FreeRTOS task or ISR.")
            print("  -> Suggestion: Increase task stack size in xTaskCreate or move large local arrays to heap/static.")
        elif "Watchdog" in reason or "TG1WDT" in reason or "TG0WDT" in reason:
            print("  -> Root Cause: Task starved CPU core without yielding / delay().")
            print("  -> Suggestion: Add `vTaskDelay(1)` or `delay(1)` inside long while/for loops.")
    
    # Check Backtrace
    bt_match = re.search(r"Backtrace:(.*)", log_text)
    if bt_match:
        addresses = bt_match.group(1).strip().split()
        print(f"\n[BACKTRACE] Found {len(addresses)} call addresses in execution stack:")
        for idx, addr in enumerate(addresses):
            print(f"  Frame #{idx}: {addr}")
        print("\nTo resolve exact source code line numbers, run:")
        print("  python -m platformio exec -- xtensa-esp32-elf-addr2line -pfia -e .pio/build/esp32dev/firmware.elf " + " ".join(addresses))

    # Check WiFi / Heap issues
    if "Free Heap: 0" in log_text or "out of memory" in log_text.lower():
        print("[MEMORY ERROR] Out of Memory / Heap Exhaustion detected.")
        print("  -> Suggestion: Allocate sprites dynamically or check memory leaks.")
        
    print("================================")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        with open(sys.argv[1], 'r', errors='ignore') as f:
            text = f.read()
    else:
        text = sys.stdin.read()
    analyze_log(text)
