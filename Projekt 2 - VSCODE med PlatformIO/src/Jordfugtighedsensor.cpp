#include "Jordfugtighedsensor.h"

// Konstruktor
// Initialiserer sensorens pin og sætter den som input
Jordfugtighedsensor::Jordfugtighedsensor(uint8_t pin) {
    sensorPin = pin;  // Sæt pin
    pinMode(sensorPin, INPUT);  // Sæt pin-mode som input
}

// Funktion til at hente den aktuelle luftfugtighed
// Læs sensorens værdi og returner den
int Jordfugtighedsensor::GetHumidity() {
    humidity = analogRead(sensorPin);  // Læs sensorens værdi fra analog pin
    return humidity;  // Returner den læste værdi
}

// Funktion til at opdatere sensorens læsning
void Jordfugtighedsensor::UpdateSensor() {
    humidity = analogRead(sensorPin);  // Opdater læsningen fra sensor
}
