#pragma once
#include <Arduino.h>

class Jordfugtighedsensor {
private:
    int moistPin = A0;
    double moistVal = 0;
    double moistValMin = 348;   //Disse skal lige kalibreres ordentligt så det passer med jord
    double moistValMax = 1023;  //Disse skal lige kalibreres ordentligt så det passer med jord
    double moistValRange = moistValMax - moistValMin;
    int percentArray[4];

    

    // Referencemålinger:
// Måling med kortslutning: moistVal = ~1023
// Måling i luften (afbrudt) = ~350

public:
    // Konstruktor, der initialiserer sensorens pin
    Jordfugtighedsensor(int MoistPin);
    // Funktion til at hente den aktuelle læsning af luftfugtigheden
    int GetHumidity();
};
    