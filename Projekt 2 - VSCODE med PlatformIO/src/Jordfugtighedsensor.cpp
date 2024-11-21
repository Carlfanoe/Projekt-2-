#include "Jordfugtighedsensor.h"

// Konstruktor
// Initialiserer sensorens pin og sætter den som input
Jordfugtighedsensor::Jordfugtighedsensor(uint8_t pin) {
    sensorPin = pin;  // Sæt pin
}

// Funktion til at hente den aktuelle luftfugtighed
// Læs sensorens værdi og returner den
int Jordfugtighedsensor::GetHumidity() {
    return humidity;  // Returner den læste værdi
}

// Funktion til at opdatere sensorens læsning
void Jordfugtighedsensor::UpdateSensor() {
    int rawValue = analogRead(sensorPin); // Read raw sensor value (0–1023)
    humidity = (rawValue * 100) / 1023;   // Convert to percentage (0–100%)
}