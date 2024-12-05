#pragma once

// Arduino Core libraries
#include <Arduino.h>

class Vandbeholder {
public:
    Vandbeholder(
        int trigPin,
        int echoPin,
        int threshold,
        float filledDistance,
        float emptyDistance
    );
    int ReadWaterLevel();
    int GetThreshold();
private:
    int trigPin_,
        echoPin_,
        threshold_,
        filledDistance_,
        emptyDistance_;
    void InitializeSensor();
    int TranslateToPercentage(float distance);
};