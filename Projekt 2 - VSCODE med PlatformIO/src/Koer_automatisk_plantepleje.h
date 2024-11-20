#pragma once
#include "Potteplante.h"
#include "Brugergraenseflade.h"
#include "Vandbeholder.h"
#include "Display.h"

class koer_automatisk_plantepleje {
private:
    Potteplante* planter;       // Array of plants
    int antalPlanter;           // Number of plants
    Potteplante* selectedPlant; // Pointer to the currently selected plant
	Brugergraenseflade brugergraenseflade;
    Display display_;
    Vandbeholder waterContainer_;
    int waterLevelThreshold_;
    unsigned long previousMillis_; // Variable for timing
    String CreateDataMessage();

public:
    koer_automatisk_plantepleje(Potteplante* planter, int antalPlanter);

    void InterpretUserInput();
    void selectPlant(int plantID);
    void ToggleAutomaticPlantCare();
};
