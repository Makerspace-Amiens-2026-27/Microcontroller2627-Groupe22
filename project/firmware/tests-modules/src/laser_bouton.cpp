// Laser KY-008 : 5 clignotements, puis allumé tant que le bouton est appuyé
// Attention : ne jamais regarder le faisceau ni le pointer vers quelqu'un
#include "config.h"

constexpr int PRESSED_LEVEL = LOW;

void setup() {
    pinMode(PIN_LASER, OUTPUT);
    pinMode(PIN_BUTTON, INPUT_PULLUP);

    // Test 1 : 5 clignotements
    for (int i = 0; i < 5; i++) {
        digitalWrite(PIN_LASER, HIGH);
        delay(300);
        digitalWrite(PIN_LASER, LOW);
        delay(300);
    }
}

void loop() {
    // Test 2 : laser allumé tant que le bouton est appuyé
    digitalWrite(PIN_LASER, digitalRead(PIN_BUTTON) == PRESSED_LEVEL ? HIGH : LOW);
}
