#pragma once

#include "Arduino.h"

#include "Brugergraenseflade.h"
#include "Potteplante.h"

class koer_automatisk_plantepleje {
public:
    koer_automatisk_plantepleje(Potteplante* plants);

    void CheckPlants();
    bool VerifyHumidity(Potteplante& plant);
    bool VerifyWaterLevel();
    String CreateDataMessage();
    void AlertLowWaterLevel();
    void ProcessInput();
    bool GetRunningState();
private:
    bool running_ = true; // Begynder plantepleje ved opstart
    Potteplante* plants_;
    Brugergraenseflade ui_ = {9600}; // UART1 ved baud-rate på 9600
    //Skaerm display_;
    //Vandbeholder waterContainer_;
    int waterLevelThreshold_ = 20;
    void InterpretInput(
        String &input,
        String &function,
        String &param1,
        String &param2
    );
};