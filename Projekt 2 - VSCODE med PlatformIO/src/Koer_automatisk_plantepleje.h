#pragma once

// Arduino Core libraries
#include "Arduino.h"

// Klasser
#include "Brugergraenseflade.h"
#include "Potteplante.h"
#include "Vandbeholder.h"
#include "Skaerm.h"


class koer_automatisk_plantepleje {
public:
    koer_automatisk_plantepleje(Potteplante* plants, int numPlants);

    void CheckPlants();
    bool VerifyWaterLevel();
    String CreateDataMessage();
    void AlertLowWaterLevel();
    void ProcessInput();
    bool GetRunningState();
private:
// instanser af klasser 
    Potteplante* plants_;
    Brugergraenseflade ui_ = {9600}; // UART1 ved baud-rate på 9600
    Vandbeholder waterContainer_ = {
            22, // trigPin
            23, // echoPin
            30, // Afstand i cm ved tom vandbeholder
            3   // Afstand i cm ved fyldt vandbeholder
        };    
    Skaerm display_;

// attributter
    int numPlants_;
    bool running_ = true; // Begynder plantepleje ved opstart
    int waterLevelThreshold_ = 20;
    
    void InterpretInput(
        String &input,
        String &function,
        String &param1,
        String &param2
    );
};