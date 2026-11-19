// Capteur KY-015 (DHT11) : température et humidité, format TelePlot
#include <DHT.h>
#include "config.h"

DHT dht(PIN_DHT, DHT11);

void setup() {
    Serial.begin(115200);
    delay(1500);
    dht.begin();
}

void loop() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();   // en °C

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Erreur de lecture du DHT11");
    } else {
        Serial.printf(">temperature:%.1f\n", temperature);
        Serial.printf(">humidite:%.0f\n", humidity);
    }
    delay(2000);   // le DHT11 ne donne pas plus d'une mesure par seconde
}
