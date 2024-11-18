#pragma once
#include <Arduino.h>
#include "Potteplante.h"

class Brugergraenseflade {
private:
    Potteplante* planter; // Pointer til array af plante-objekter
    int antalPlanter;     // Antal planter i systemet
    Potteplante* selectedPlant; // Pointer til den valgte plante

    // Helper functions
    void selectPlant(int plantID);
    void changeThreshold(int newThreshold);
    void changeWaterDuration(int duration);
    void waterPlant();
    void displayPlantStatus();

public:
    // Constructor
    Brugergraenseflade(Potteplante* planter, int antalPlanter);

    // Funktion til at læse serielle data
    void read();

};
