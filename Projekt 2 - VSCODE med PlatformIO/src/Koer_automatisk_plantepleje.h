#pragma once

// Arduino Core libraries
#include "Arduino.h"

// Klasser
#include "Brugergraenseflade.h"
#include "Potteplante.h"
#include "Vandbeholder.h"
#include "Skaerm.h"
#include "Hoejtaler.h"


class koer_automatisk_plantepleje {
public:
    koer_automatisk_plantepleje(
        Hoejtaler& speaker,
        LiquidCrystal_I2C& display,
        Brugergraenseflade& ui,
        Vandbeholder& waterContainer,
        Potteplante* plants,
        int numPlants
    );

    void ProcessInput();
    void CheckPlants();
    bool GetRunningState();
private:
    // instanser af klasser
    Hoejtaler& speaker_;
    Skaerm display_; // DETTTE VIRKER IKKE!!!!!
    Brugergraenseflade& ui_;
    Vandbeholder& waterContainer_;
    Potteplante* plants_;

    // attributter
    int numPlants_;
    bool running_ = true; // Begynder plantepleje ved opstart
    
    bool VerifyWaterLevel();
    void SendDataMessage();
    void SendDetailedMessage();
    void AlertLowWaterLevel();
    void InterpretInput(
        String &input,
        String &function,
        String &param1,
        String &param2
    );
};