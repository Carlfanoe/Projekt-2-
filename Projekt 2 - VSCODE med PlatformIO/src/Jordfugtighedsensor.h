#pragma once
#include <Arduino.h>

class Jordfugtighedsensor {
private:
    int moistPin = 0;
    int moistVal = 0;
    int moistValMin = 350;
    int moistValMax = 850;
    int moistValRange = moistValMax - moistValMin;
    

    // Referencemålinger:
// Måling i rent vand: moistVal = ~850
// Måling i luften (afbrudt) = ~350

public:
    // Konstruktor, der initialiserer sensorens pin
    Jordfugtighedsensor(int MoistPin);
    // Funktion til at hente den aktuelle læsning af luftfugtigheden
    int GetHumidity();
};
    