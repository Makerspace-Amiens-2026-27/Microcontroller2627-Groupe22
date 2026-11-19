// Capteur de son KY-037 : volume crête à crête sur 50 ms + état de la sortie DO
#include "config.h"

constexpr uint32_t WINDOW_MS = 50;   // fenêtre de mesure

void setup() {
    Serial.begin(115200);
    delay(1500);
    pinMode(PIN_SOUND_DO, INPUT);
    analogReadResolution(12);
}

void loop() {
    int minValue = 4095, maxValue = 0;
    int samples = 0, highCount = 0;
    uint32_t start = millis();

    while (millis() - start < WINDOW_MS) {
        int v = analogRead(PIN_SOUND_AO);
        if (v < minValue) minValue = v;
        if (v > maxValue) maxValue = v;
        if (digitalRead(PIN_SOUND_DO) == HIGH) highCount++;
        samples++;
    }

    Serial.printf(">volume:%d\n", maxValue - minValue);      // crête à crête
    Serial.printf(">AO_moyen:%d\n", (maxValue + minValue) / 2);
    Serial.printf(">DO_pourcent_HIGH:%d\n", highCount * 100 / samples);
}
