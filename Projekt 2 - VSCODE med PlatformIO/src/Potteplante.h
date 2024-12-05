#pragma once

// Arduino Core libraries
#include <Arduino.h>
#include "Jordfugtighedsensor.h"
#include "Vandpumpe.h"

class Potteplante {
public:
    Potteplante(
        int id,
        int humiditySensorPin,
        int waterPumpPin,
        int humidityThreshold,
        int wateringDuration
    );
    int GetID();
    void WaterPlant();
    int GetHumidity();
    bool VerifyHumidity();
    int GetHumidityThreshold();
    void SetHumidityThreshold(int newThreshold);
private:
    int id_;
    Jordfugtighedsensor humiditySensor_;
    Vandpumpe waterPump_;
    int humidityThreshold_;
    int wateringDuration_;
};
