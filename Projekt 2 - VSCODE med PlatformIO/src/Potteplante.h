#pragma once

// Arduino Core libraries
#include <Arduino.h>
#include "Jordfugtighedsensor.h"

class Potteplante {
public:
    Potteplante(
        int humiditySensorPin,
        int waterPumpPin,
        int id,
        int humidityThreshold,
        int wateringDuration
    );
    int GetID();
    void WaterPlant();
    int GetHumidity();
    void UpdateHumidity();
    bool VerifyHumidity();
    int GetHumidityThreshold();
    void SetHumidityThreshold(int newThreshold);
private:
    int id_;
    int humidity_; // = humiditySensor_.UpdateHumidity();
    int humidityThreshold_;
    int wateringDuration_;
    //Vandpumpe waterPump_;
    Jordfugtighedsensor humiditySensor_;
};
