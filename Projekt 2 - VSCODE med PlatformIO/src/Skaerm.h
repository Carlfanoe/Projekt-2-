#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Skaerm {
public:
    Skaerm();
    void SetDisplayState(bool state);
    void UpdateDisplay(String message);
private:
    void InitDisplay();
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
};