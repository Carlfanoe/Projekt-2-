#pragma once

// Arduino Core libraries
#include "Arduino.h"

// Klasser
#include "Brugergraenseflade.h"
#include "Potteplante.h"
#include "Vandbeholder.h"


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
    Vandbeholder waterContainer_;
    //Skaerm display_;

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