#pragma once

#include <Arduino.h>
#include <util/delay.h>

class Vandbeholder {
public:
    Vandbeholder(
        int trigPin,
        int echoPin,
        int threshold,
        int filledDistance,
        int emptyDistance
    );
    int ReadWaterLevel();
private:
    int trigPin_,
        echoPin_,
        threshold_,
        filledDistance_,
        emptyDistance_;
    void InitializeSensor();
    int TranslateToPercentage(float distance);
    // bool ReadPINA(int pin);
    // void WritePORTA(int pin, bool state);
};