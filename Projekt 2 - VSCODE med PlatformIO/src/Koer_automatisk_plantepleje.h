#pragma once

class koer_automatisk_plantepleje {
public:
    koer_automatisk_plantepleje(Potteplante* planter, int antalPlanter);

    void InterpretUserInput();
    void selectPlant(int plantID);
    void ToggleAutomaticPlantCare();
private:
    Potteplante* planter_;       // Array of plants
    int antalPlanter_;           // Number of plants
    Potteplante* selectedPlant_ = nullptr; // Pointer to the currently selected plant
	Brugergraenseflade ui_ = {};
    Skaerm display_ = {};
    Vandbeholder waterContainer_ = {
        22, // trigPin
        23, // echoPin
        30, // Afstand i cm ved tom vandbeholder
        3   // Afstand i cm ved fyldt vandbeholder
    };
    int waterLevelThreshold_ = 20;
    unsigned long previousMillis_ = 0; // Variable for timing

    String CreateDataMessage();
};
