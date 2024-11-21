#pragma once

#include <Arduino.h>

// #include <Vandbeholder.h>
// #include <Jordfugtighedssensor.h>

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
    int GetHumidityThreshold();
    void UpdateHumidityThreshold(int newThreshold);
private:
    int id_;
    int humidityThreshold_;
    int wateringDuration_;
    //Vandpumpe waterPump_;
    //Jordfugtighedssensor humiditySensor_;
};
