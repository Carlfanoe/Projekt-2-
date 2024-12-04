#pragma once
#include <Arduino.h>

class Jordfugtighedsensor {
private:
    uint8_t moistPin;
    uint8_t supplyPin_;
    double moistVal = 0;
    double moistValMin = 348;   //Disse skal lige kalibreres ordentligt så det passer med jord
    double moistValMax = 1023;  //Disse skal lige kalibreres ordentligt så det passer med jord
    double moistValRange = moistValMax - moistValMin;
    double percentArray[4];

    

    // Referencemålinger:
// Måling med kortslutning: moistVal = ~1023
// Måling i luften (afbrudt) = ~350

public:
    // Konstruktor, der initialiserer sensorens pin
    Jordfugtighedsensor(uint8_t MoistPin, uint8_t supplyPin);
    // Funktion til at hente den aktuelle læsning af luftfugtigheden
    int GetHumidity();
};
    