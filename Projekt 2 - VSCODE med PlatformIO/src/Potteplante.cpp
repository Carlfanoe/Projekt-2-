#include "Potteplante.h"

// Konstruktor
Potteplante::Potteplante(int ID, uint8_t HumiditySensorPin, int HumidityThreshold, int WateringDuration)
    : jordfugtighedsensor(HumiditySensorPin), id(ID), humidityThreshold(HumidityThreshold), wateringDuration(WateringDuration), selected(false) {}

// Metode til at vande planten
void Potteplante::WaterPlant() {
    // Placeholder for vandingens funktionalitet
}

// Metode til at hente den aktuelle Jordfugtighed
int Potteplante::GetHumidity() {
    jordfugtighedsensor.UpdateSensor();  // Sørg for at opdatere sensorens værdi først
    int rawHumidity = jordfugtighedsensor.GetHumidity();  // Hent den opdaterede værdi
    int humidityPercent = map(rawHumidity, 0, 1023, 0, 100);  // Konverter til procent
    return humidityPercent;  // Returner den beregnede luftfugtighed i procent
}


int Potteplante::GetThreshold() {
    return humidityThreshold;
}

void Potteplante::SetThreshold(int NewHumidityThreshold) {
    humidityThreshold = NewHumidityThreshold;
}

void Potteplante::UpdateSensor() {
    jordfugtighedsensor.UpdateSensor();
}

void Potteplante::SetDuration(int NewDuration) {
    wateringDuration = NewDuration;
}

int Potteplante::GetDuration() {
    return wateringDuration;
}

int Potteplante::GetID() {
    return id;
}

// Setter for 'selected' status
void Potteplante::setSelected(bool status) {
    selected = status;
}

// Getter for 'selected' status
bool Potteplante::isSelected() const {
    return selected;
}
