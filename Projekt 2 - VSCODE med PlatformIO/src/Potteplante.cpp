#include "Potteplante.h"

Potteplante::Potteplante(
    int humiditySensorPin,
    int waterPumpPin,
    int id,
    int humidityThreshold,
    int wateringDuration
)
    :   id_(id),
        humidityThreshold_(humidityThreshold),
        wateringDuration_(wateringDuration)//,
        // waterPump_(waterPumpPin),
        // humiditySensor(humiditySensorPin)
{}

int Potteplante::GetID()
{
    return id_;
}

void Potteplante::WaterPlant()
{
    //Kode mangler
}

int Potteplante::GetHumidity()
{
    //return humiditySensor_.GetHumidity();

    //Midletidigt, slet det her efter implementering:
    return 0;
}

void Potteplante::UpdateHumidity()
{
    //humiditySensor_.UpdateHumidity();
}

int Potteplante::GetHumidityThreshold()
{
    return humidityThreshold_;
}

void Potteplante::SetHumidityThreshold(int newThreshold)
{
    humidityThreshold_ = newThreshold;
}