// Bouton : un seul événement par appui (anti-rebond de 30 ms avec millis())
#include "config.h"

constexpr int PRESSED_LEVEL = LOW;           // niveau lu quand on appuie
constexpr unsigned long DEBOUNCE_MS = 30;

struct Button {
    int pin;
    int stableLevel;              // dernier niveau confirmé
    int lastRead;                 // dernière lecture brute
    unsigned long lastChangeMs;   // date du dernier mouvement du signal
};

Button button = {PIN_BUTTON, !PRESSED_LEVEL, !PRESSED_LEVEL, 0};

// Renvoie true une seule fois par appui, au moment où il est confirmé
bool justPressed(Button& b) {
    int level = digitalRead(b.pin);
    if (level != b.lastRead) {
        b.lastRead = level;
        b.lastChangeMs = millis();
    }
    if (millis() - b.lastChangeMs > DEBOUNCE_MS && level != b.stableLevel) {
        b.stableLevel = level;
        return level == PRESSED_LEVEL;
    }
    return false;
}

void setup() {
    Serial.begin(115200);
    delay(1500);
    pinMode(PIN_BUTTON, INPUT_PULLUP);
}

void loop() {
    static int count = 0;
    if (justPressed(button)) {
        count++;
        Serial.printf("Appui n°%d\n", count);
    }
}
