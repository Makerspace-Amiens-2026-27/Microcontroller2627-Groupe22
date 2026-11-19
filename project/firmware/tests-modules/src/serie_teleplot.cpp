// Port série + TelePlot : envoie un sinus et un cosinus
#include <Arduino.h>

float i = 0;

void teleplot(const char* label, float value)
{
  Serial.printf(">%s:%.3f\n", label, value);
}

void setup()
{
  Serial.begin(115200);
  delay(1500);   // USB natif : laisse le temps au PC de rouvrir le port
}

void loop()
{
  i += 0.1;
  teleplot("sin", sin(i));
  teleplot("cos", cos(i));
  delay(10);
}
