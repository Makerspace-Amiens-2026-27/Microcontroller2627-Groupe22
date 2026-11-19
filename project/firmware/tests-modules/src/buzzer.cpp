// Buzzer : gamme avec tone() (passif) puis bip HIGH (actif)
#include "config.h"

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);

    // Test 1 : buzzer passif, gamme do-ré-mi-fa-sol
    const int notes[] = {262, 294, 330, 349, 392};  // fréquences en Hz
    for (int note : notes) {
        tone(PIN_BUZZER, note, 200);
        delay(250);
    }
    delay(1000);

    // Test 2 : buzzer actif, bip d'une demi-seconde
    digitalWrite(PIN_BUZZER, HIGH);
    delay(500);
    digitalWrite(PIN_BUZZER, LOW);
}

void loop() {}
