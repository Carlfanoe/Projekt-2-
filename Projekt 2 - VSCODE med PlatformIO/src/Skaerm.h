#pragma once

// Arduino Core libraries
#include <Arduino.h>

// Library til display
#include "LiquidCrystal_I2C.h"

class Skaerm {
public:
    Skaerm(uint8_t address, uint8_t columns, uint8_t rows);
    void Initialize();
    void SetState(bool state);
    void Update(String message);
private:
    LiquidCrystal_I2C lcd_;
};