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
        Skaerm& display,
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
    Skaerm& display_;
    Brugergraenseflade& ui_;
    Vandbeholder& waterContainer_;
    Potteplante* plants_;

    // attributter
    int numPlants_;
    bool running_ = false; // Begynder IKKE plantepleje ved opstart
    
    bool VerifyWaterLevel(int waterLevel, int threshold);
    String CreateDataMessage(int waterLevel);
    String CreateDetailedMessage(int waterLevel, int waterLevelThreshold);
    void AlertLowWaterLevel();
    void InterpretInput(
        String &input,
        String &function,
        String &param1,
        String &param2
    );
};