// Joystick : calibration du centre, zone morte et valeur entre -1 et +1
#include "config.h"

constexpr int JOYSTICK_DEADZONE = 300;
int joystickCenterX = 2048;

void calibrateJoystick() {
    long sum = 0;
    for (int i = 0; i < 16; i++) {
        sum += analogRead(PIN_JOYSTICK_X);
        delay(2);
    }
    joystickCenterX = sum / 16;
}

// Convertit une lecture brute (0..4095) en valeur entre -1.0 et +1.0
float normalizeJoystick(int raw, int center) {
    int offset = raw - center;
    if (abs(offset) < JOYSTICK_DEADZONE) {
        return 0.0f;
    }
    int range = (offset > 0) ? (4095 - center) : center;
    return constrain((float)offset / range, -1.0f, 1.0f);
}

void setup() {
    Serial.begin(115200);
    delay(1500);
    analogReadResolution(12);
    calibrateJoystick();   // ne pas toucher au joystick au démarrage
    Serial.printf("Centre calibre : %d\n", joystickCenterX);
}

void loop() {
    float x = normalizeJoystick(analogRead(PIN_JOYSTICK_X), joystickCenterX);
    Serial.printf("x=%.2f\n", x);
    delay(100);
}
