#include "Potteplante.h"

Potteplante::Potteplante(
    int humiditySensorPin,
    int waterPumpPin,
    int id,
    int humidityThreshold,
    int wateringDuration
)
    :   humiditySensor_(humiditySensorPin),
        //waterPump_(waterPumpPin),
        id_(id),
        humidityThreshold_(humidityThreshold),
        wateringDuration_(wateringDuration)
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