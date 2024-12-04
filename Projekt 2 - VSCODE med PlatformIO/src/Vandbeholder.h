#pragma once

// Arduino Core libraries
#include <Arduino.h>

class Vandbeholder {
public:
    Vandbeholder(
        int trigPin,
        int echoPin,
        int filledDistance,
        int emptyDistance
    );
    int ReadWaterLevel();
private:
    int trigPin_,
        echoPin_,
        filledDistance_,
        emptyDistance_;
    void InitializeSensor();
    int TranslateToPercentage(float distance);
};