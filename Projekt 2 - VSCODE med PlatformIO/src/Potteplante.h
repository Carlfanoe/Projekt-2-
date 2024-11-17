#pragma once
#include <Arduino.h>
#include "Jordfugtighedsensor.h"

class Potteplante {
private:
    int id;                           // ID for potteplante
    uint8_t humiditySensorPin;         // Sensor pin for humidity sensor
    int humidityThreshold;             // Threshold for humidity
    int wateringDuration;              // Duration for watering
    bool selected;                     // If the plant is selected
    
    Jordfugtighedsensor jordfugtighedsensor;  // Instantiating Jordfugtighedsensor

public:
    // Constructor
    Potteplante(int ID, uint8_t HumiditySensorPin, int HumidityThreshold, int WateringDuration);    
    
    // Method to water the plant
    void WaterPlant();
    
    // Method to get current humidity value
    int GetHumidity();
    
    // Method to get the threshold value
    int GetThreshold();
    
    // Method to set a new threshold
    void SetThreshold(int NewHumidityThreshold);
    
    // Method to update sensor
    void UpdateSensor();

    // Sætter en ny varighed for vanding
	void SetDuration(int NewDuration);
    
    // Method to get the plant ID
    int GetID();
    
    // Method to check if plant is selected
    bool isSelected() const;
    
    // Method to set plant's selected status
    void setSelected(bool value);  
}; 
