#include "Potteplante.h"

Potteplante::Potteplante(
    int humiditySensorPin,
    int waterPumpPin,
    int id,
    int humidityThreshold
)
    :   id_(id),
        humidityThreshold_(humidityThreshold)//,
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

void Potteplante::UpdateHumidityThreshold(int newThreshold)
{
    humidityThreshold_ = newThreshold;
}