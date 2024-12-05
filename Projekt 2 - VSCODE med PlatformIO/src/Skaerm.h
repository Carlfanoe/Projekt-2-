#pragma once

// Arduino Core libraries
#include <Arduino.h>

// Library til display
#include "LiquidCrystal_I2C.h"

class Skaerm {
public:
    Skaerm(LiquidCrystal_I2C& display);
    void SetState(bool state);
    void Update(String message);
private:
    void Initialize();
    LiquidCrystal_I2C& display_; // = LiquidCrystal_I2C(0x27, 20, 4);
};