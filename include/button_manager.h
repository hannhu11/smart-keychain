#pragma once
#include <Arduino.h>
#include "config.h"

enum KeychainState {
  STATE_ANIMATION,
  STATE_QR_CONFIG
};

class ButtonManager {
private:
  uint8_t pin;
  KeychainState currentState = STATE_ANIMATION;
  int idleState = HIGH; // Mức logic nhàn rỗi (tự động hiệu chuẩn lúc boot)

  volatile bool rawState = true;
  volatile unsigned long isrChangeTime = 0;
  volatile bool isrEventOccurred = false;

  unsigned long lastPressTime = 0;
  unsigned long lastReleaseTime = 0;
  unsigned long qrEnterTime = 0;
  unsigned long qrCooldownUntil = 0;

  bool isDown = false;
  bool holdHandled = false;

  const unsigned long DEBOUNCE_MS     = 20;   // 20ms chống dội phím phần cứng
  const unsigned long HOLD_QR_MS      = 2500; // Giữ >=2.5s để mở QR

  std::function<void()> onSingleClickCb;
  std::function<void()> onQREnterCb;
  std::function<void()> onQRExitClickCb;
  std::function<void()> onHoldPaletteCb;

  static void isrHandler(void* arg) {
    ButtonManager* self = reinterpret_cast<ButtonManager*>(arg);
    self->rawState = (digitalRead(self->pin) != self->idleState);
    self->isrChangeTime = millis();
    self->isrEventOccurred = true;
  }

public:
  ButtonManager(uint8_t btnPin = BTN_PIN)
    : pin(btnPin), currentState(STATE_ANIMATION), idleState(HIGH),
      lastPressTime(0), lastReleaseTime(0), qrEnterTime(0),
      isDown(false), holdHandled(false) {}

  void init(
    std::function<void()> onSingle,
    std::function<void()> onQREnter,
    std::function<void()> onQRExit,
    std::function<void()> onHoldPalette = nullptr
  ) {
    pinMode(pin, INPUT_PULLUP);
    delay(50); // Chờ đường tín hiệu ổn định

    // Tự động hiệu chuẩn mức nghỉ (IDLE LEVEL) trong 10 mẫu liên tiếp
    int highCount = 0;
    for (int i = 0; i < 10; i++) {
      if (digitalRead(pin) == HIGH) highCount++;
      delay(5);
    }
    idleState = (highCount >= 5) ? HIGH : LOW;

    onSingleClickCb   = onSingle;
    onQREnterCb       = onQREnter;
    onQRExitClickCb   = onQRExit;
    onHoldPaletteCb   = onHoldPalette;
    currentState      = STATE_ANIMATION;
    isDown            = false;
    holdHandled       = false;
    lastPressTime     = 0;
    lastReleaseTime   = millis();
    qrEnterTime       = 0;
    qrCooldownUntil   = 0;

    // Kích hoạt Hardware Interrupt trên chân GPIO 33
    attachInterruptArg(digitalPinToInterrupt(pin), isrHandler, this, CHANGE);

    Serial.printf("[BUTTON] Tự động hiệu chuẩn: Mức nghỉ (IDLE) = %s -> Nút bấm: %s (0ms Click + >=2.5s QR)!\n",
      (idleState == HIGH) ? "HIGH (3.3V)" : "LOW (0V)",
      (idleState == HIGH) ? "ACTIVE-LOW (Pull-Up)" : "ACTIVE-HIGH (Pull-Down)");
  }

  void setState(KeychainState st) {
    currentState = st;
    if (st == STATE_QR_CONFIG) {
      qrEnterTime = millis();
      qrCooldownUntil = millis() + 800; // Khóa 800ms chống nhấn nhầm khi vừa vào QR
    }
  }

  KeychainState getState() const {
    return currentState;
  }
  bool isPressed() const { return isDown; }

  // Hàm tick được gọi từ vòng lặp hiển thị / core task
  void tick() {
    unsigned long now = millis();

    // Bỏ qua 600ms đầu tiên sau boot để điện áp 3.3V và PULLUP ổn định hoàn toàn
    if (now < 600) {
      isDown = false;
      lastPressTime = 0;
      lastReleaseTime = now;
      return;
    }

    bool rawPin = (digitalRead(pin) != idleState); // Khác mức nghỉ = ĐANG NHẤN!

    // 1. NHẬN DIỆN NHẤN XUỐNG (EDGE ACTIVATION)
    if (rawPin && !isDown) {
      if (now - lastReleaseTime >= DEBOUNCE_MS) {
        isDown = true;
        lastPressTime = now;
        holdHandled = false;

        // Nếu đang ở màn hình QR -> BẤM 1 NHÁT LÀ THOÁT NGAY LẬP TỨC!
        if (currentState == STATE_QR_CONFIG) {
          if (now >= qrCooldownUntil) {
            Serial.printf("[BTN_TRACE] RAW: CLICK_IN_QR | Duration: 0 ms | Action: EXIT_TO_ANIMATION\n");
            currentState = STATE_ANIMATION;
            isDown = false;
            lastPressTime = 0;
            if (onQRExitClickCb) onQRExitClickCb();
            return;
          }
        }
      }
    }

    // 2. NHẬN DIỆN GIỮ LÂU >= 2500ms (MỞ MÃ QR CẤU HÌNH)
    if (rawPin && isDown && !holdHandled && lastPressTime > 0) {
      if (now - lastPressTime >= HOLD_QR_MS) {
        holdHandled = true;
        unsigned long dur = now - lastPressTime;
        if (currentState == STATE_ANIMATION) {
          Serial.printf("[BTN_TRACE] RAW: HOLD_2500MS | Duration: %lu ms | Action: OPEN_QR_SCREEN\n", dur);
          currentState = STATE_QR_CONFIG;
          qrEnterTime = now;
          qrCooldownUntil = now + 1000; // Khóa 1.0s
          if (onQREnterCb) onQREnterCb();
        }
      }
    }

    // 3. NHẬN DIỆN NHẢ TAY (RISING EDGE - PHẢN HỒI 0ms TỨC THÌ CHO 1-CLICK!)
    if (!rawPin) {
      if (isDown) {
        if (now - lastPressTime >= DEBOUNCE_MS) {
          isDown = false;
          lastReleaseTime = now;
          unsigned long dur = (lastPressTime > 0) ? (now - lastPressTime) : 0;
          lastPressTime = 0;

          if (!holdHandled) {
            if (currentState == STATE_ANIMATION && dur < 800) {
              // SINGLE CLICK TỨC THÌ (<10ms) KHÔNG CẦN CHỜ ĐỢI MULTI-CLICK!
              Serial.printf("[BTN_TRACE] RAW: SINGLE_CLICK | Duration: %lu ms | Action: NEXT_THEME (INSTANT <10ms)\n", dur);
              if (onSingleClickCb) onSingleClickCb();
            }
          }
          holdHandled = false;
        }
      } else {
        lastPressTime = 0;
        holdHandled = false;
      }
    }
  }
};
