#include "Potteplante.h"

// Constructor
Potteplante::Potteplante(int ID, uint8_t HumiditySensorPin, int HumidityThreshold, int WateringDuration)
    : selected(false), jordfugtighedsensor(HumiditySensorPin), id(ID), humidityThreshold(HumidityThreshold), wateringDuration(WateringDuration) {
    // Constructor initializes variables and the Jordfugtighedsensor object
}

// Method to water the plant (example, currently a placeholder for actual water pump control)
void Potteplante::WaterPlant() {
    // Example action: Control a water pump, e.g. pump.PumpWater();
}

// Method to get current humidity value
int Potteplante::GetHumidity() {
    return jordfugtighedsensor.GetHumidity();  // Assuming GetHumidity is a method of Jordfugtighedsensor
}

// Method to get the threshold value
int Potteplante::GetThreshold() {
    return humidityThreshold;  // Return the current humidity threshold
}

// Method to set a new threshold value
void Potteplante::SetThreshold(int NewHumidityThreshold) {
    humidityThreshold = NewHumidityThreshold;  // Update the threshold
}

// Method to update the sensor reading
void Potteplante::UpdateSensor() {
    jordfugtighedsensor.SetHumidity();  // Assuming SetHumidity updates sensor reading
}

int Potteplante::GetDuration(){
return wateringDuration;

}


// Method to get the plant's ID
int Potteplante::GetID() {
    return id;  // Return the plant's ID
}

// Method to check if plant is selected
bool Potteplante::isSelected() const {
    return selected;  // Return the selected status
}

// Method to set the plant's selected status
void Potteplante::setSelected(bool value) {
    selected = value;  // Set the selected status
}

// Sætter varigheden for vanding
void Potteplante::SetDuration(int NewDuration){
	wateringDuration = NewDuration;
}
