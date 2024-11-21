#pragma once

#include <Arduino.h>

class Potteplante {
public:
    Potteplante(int id, int humidityThreshold);

    int GetID();
    void WaterPlant();
    int GetHumidity();
    void UpdateHumidity();
    int GethumidityThreshold();
    void UpdateHumidityThreshold(int newThreshold);
private:
    int id_;
    //Vandpumpe waterPump_;
    //Jordfugtighedssensor humiditySensor_;
    int humidityThreshold_;
    //int wateringDuration_ = 5; //5 sekunder
};
