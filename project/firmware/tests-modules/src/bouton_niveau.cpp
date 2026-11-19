// Bouton : affiche le niveau lu (HIGH relâché, LOW appuyé)
#include "config.h"

void setup() {
    Serial.begin(115200);
    delay(1500);
    pinMode(PIN_BUTTON, INPUT_PULLUP);
}

void loop() {
    Serial.println(digitalRead(PIN_BUTTON) == HIGH ? "HIGH" : "LOW");
    delay(200);  // programme de test : on ralentit l'affichage
}
