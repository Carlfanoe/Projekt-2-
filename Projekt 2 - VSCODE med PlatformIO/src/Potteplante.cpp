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
    return humidity_;
}

void Potteplante::UpdateHumidity()
{
    //humidity_ = humiditySensor_.UpdateHumidity();
}

bool Potteplante::VerifyHumidity()
{
    UpdateHumidity();
    return humidity_ >= humidityThreshold_;
}

int Potteplante::GetHumidityThreshold()
{
    return humidityThreshold_;
}

void Potteplante::SetHumidityThreshold(int newThreshold)
{
    humidityThreshold_ = newThreshold;
}