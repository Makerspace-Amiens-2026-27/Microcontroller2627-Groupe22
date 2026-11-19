// include/config.h : brochage de la console (XIAO ESP32S3 Plus)
#pragma once

#include <Arduino.h>

// Modules de la mallette
constexpr int PIN_BUTTON          = D5;
constexpr int PIN_JOYSTICK_X      = D0;
constexpr int PIN_JOYSTICK_Y      = D1;
constexpr int PIN_JOYSTICK_SELECT = D2;
constexpr int PIN_BUZZER          = D3;   // seulement sur breadboard

// Écran TFT ST7789 (SPI)
constexpr int PIN_TFT_RESET = D7;
constexpr int PIN_TFT_DC    = D8;
constexpr int PIN_TFT_SCK   = D9;
constexpr int PIN_TFT_MOSI  = D10;
constexpr int PIN_TFT_CS    = -1;   // CS relié à GND : pas de broche

// Capteurs supplémentaires (broches libres D4 et D6)
constexpr int PIN_DHT      = D4;   // KY-015 (DHT11), broche S
constexpr int PIN_SOUND_AO = D4;   // KY-037, sortie analogique
constexpr int PIN_SOUND_DO = D6;   // KY-037, sortie numérique
constexpr int PIN_LASER    = D6;   // KY-008, broche S
