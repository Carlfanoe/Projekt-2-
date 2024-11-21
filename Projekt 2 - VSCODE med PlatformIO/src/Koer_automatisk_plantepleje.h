#pragma once

#include "Arduino.h"

#include "Potteplante.h"

class koer_automatisk_plantepleje {
public:
    koer_automatisk_plantepleje(Potteplante* plants);

    void ToggleAutomaticPlantCare();
    bool VerifyHumidity(Potteplante& plant);
    bool VerifyWaterLevel();
    String CreateDataMessage();
    void AlertLowWaterLevel();
    void InterpretUserInput();
private:
    //tidsattributter mangler måske
    Potteplante* plants_;
    //Brugergraenseflade ui_;
    //Skaerm display_;
    //Vandbeholder waterContainer_;
    int waterLevelThreshold_ = 20;
};