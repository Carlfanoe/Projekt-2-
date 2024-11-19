#pragma once
#include "Potteplante.h"
#include "Brugergraenseflade.h"

class koer_automatisk_plantepleje {
private:
    Potteplante* planter;       // Array of plants
    int antalPlanter;           // Number of plants
    Potteplante* selectedPlant; // Pointer to the currently selected plant
	Brugergraenseflade brugergraenseflade;
    unsigned long previousMillis_; // Variable for timing


public:
    koer_automatisk_plantepleje(Potteplante* planter, int antalPlanter);

    void InterpretUserInput();
    void selectPlant(int plantID);
    void ToggleAutomaticPlantCare();
};
