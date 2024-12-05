#include "Skaerm.h"

Skaerm::Skaerm(uint8_t address, uint8_t columns, uint8_t rows)
    : lcd_(address, columns, rows)
{}

void Skaerm::SetState(bool newState)
{
    if (newState) {
        lcd_.backlight();
        lcd_.display();
    } else {
        lcd_.noBacklight();
        lcd_.noDisplay();
    }
}

void Skaerm::Update(String message)
{
    int lineIndex = 0;
    String messages[4];
    for (unsigned int i = 0; i < message.length(); i++) {
        char c = message[i];
        if (lineIndex >= 4) break;
        if (c == '\n') lineIndex++;
        else messages[lineIndex] += c;
    }
    lcd_.clear();
    for (int i = 0; i < 4; i++) {
        lcd_.setCursor(0, i);
        lcd_.print(messages[i]);
    }
}

void Skaerm::Initialize()
{
    lcd_.init(); // Initialize the LCD display
    lcd_.backlight(); // Turn on the backlight
}