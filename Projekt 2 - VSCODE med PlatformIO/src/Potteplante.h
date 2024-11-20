#pragma once

#include <Arduino.h>
#include "Jordfugtighedsensor.h" // Inkluderer jordfugtighedsensor.h for at bruge sensor-klassen

class Potteplante {
private:
    int id;                           // ID for potteplante
    uint8_t humiditySensorPin;         // Pin til jordfugtighedssensor
    int humidityThreshold;             // Humiditetströskelværdi
    int wateringDuration;              // Vandingens varighed
    bool selected;                     // Boolean for at holde styr på om planten er valgt

    Jordfugtighedsensor jordfugtighedsensor;  // Instantiating jordfugtighedsensor

public:
    // Konstruktor for potteplante
    Potteplante(int ID, uint8_t HumiditySensorPin, int HumidityThreshold, int WateringDuration);

    // Funktion til at vande planten
    void WaterPlant();

    // Funktion til at hente den aktuelle luftfugtighed
    int GetHumidity();

    // Funktion til at hente grænseværdien for luftfugtighed
    int GetThreshold();

    // Funktion til at ændre grænseværdien for luftfugtighed
    void SetThreshold(int NewHumidityThreshold);

    // Funktion til at opdatere sensorens læsning
    void UpdateSensor();

    // Funktion til at sætte vandingens varighed
    void SetDuration(int NewDuration);

    // Funktion til at hente vandingens varighed
    int GetDuration();

    // Funktion til at hente plantens ID
    int GetID();

    // Setter and Getter for 'selected' status
    void setSelected(bool status);
    bool isSelected() const;
};
