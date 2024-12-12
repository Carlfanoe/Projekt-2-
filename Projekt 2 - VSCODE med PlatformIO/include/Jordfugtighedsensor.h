#pragma once

#include <Arduino.h>

class Jordfugtighedsensor {
private:
    int pin_;
    // double humidityValMin = 348;   //Disse skal lige kalibreres ordentligt så det passer med jord
    // double humidityValMax = 1023;  //Disse skal lige kalibreres ordentligt så det passer med jord
public:
    Jordfugtighedsensor(int pin); // Konstruktor, der initialiserer sensorens pin
    int GetHumidity(); // Funktion til aflæse og returnere luftfugtigheden
};