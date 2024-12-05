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
    koer_automatisk_plantepleje(
        LiquidCrystal_I2C& display,
        Brugergraenseflade& ui,
        Vandbeholder& waterContainer,
        Potteplante* plants,
        int numPlants
    );

    void CheckPlants();
    bool VerifyWaterLevel();
    String CreateDataMessage();
    void AlertLowWaterLevel();
    void ProcessInput();
    bool GetRunningState();
private:
    // instanser af klasser
    Skaerm display_;
    Brugergraenseflade& ui_;
    Vandbeholder& waterContainer_;
    Potteplante* plants_;

    // attributter
    int numPlants_;
    bool running_ = true; // Begynder plantepleje ved opstart
    
    void InterpretInput(
        String &input,
        String &function,
        String &param1,
        String &param2
    );
};