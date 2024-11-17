#pragma once
#include <Arduino.h>

class Jordfugtighedsensor {
private:
    int humidity_ = 0;
    uint8_t pin_;  // ADC pin på Arduino: Vi SKAL finde på en løsning her, fordi lige nu er adcPin den samme for hvert object af plante, hvilket den ikke må være.
    
public:
    Jordfugtighedsensor(uint8_t pin); // kalder automatisk ADC_init
    int GetHumidity();
    void SetHumidity(); // Opdaterer attributten humidity
    double ADC_readAsPercentage();  // Retunerer Humidity som procent
};
