#include "Potteplante.h"

Potteplante::Potteplante(
    int id,
    int humiditySensorPin,
    int waterPumpPin,
    int humidityThreshold,
    int wateringDuration
)
    :   id_(id),
        humidityThreshold_(humidityThreshold),
        wateringDuration_(wateringDuration),
        //waterPump_(waterPumpPin),
        humiditySensor_(humiditySensorPin)
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
    return humiditySensor_.GetHumidity();
}

bool Potteplante::VerifyHumidity()
{
    return GetHumidity() >= humidityThreshold_;
}

int Potteplante::GetHumidityThreshold()
{
    return humidityThreshold_;
}

void Potteplante::SetHumidityThreshold(int newThreshold)
{
    humidityThreshold_ = newThreshold;
}