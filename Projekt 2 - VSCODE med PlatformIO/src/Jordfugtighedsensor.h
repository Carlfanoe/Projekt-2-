#pragma once
#include <Arduino.h>

class Jordfugtighedsensor {
private:
    uint8_t sensorPin;   // Pin, der er tilsluttet jordfugtighedssensoren
    int humidity;        // Variabel til at gemme sensorens læsning

public:
    // Konstruktor, der initialiserer sensorens pin
    Jordfugtighedsensor(uint8_t pin);

    // Funktion til at hente den aktuelle læsning af luftfugtigheden
    int GetHumidity();

    // Funktion til at opdatere sensorens læsning
    void UpdateSensor();
};
