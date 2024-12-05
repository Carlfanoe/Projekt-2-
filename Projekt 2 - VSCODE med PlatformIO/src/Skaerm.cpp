#include "Skaerm.h"

Skaerm::Skaerm(LiquidCrystal_I2C& display) : display_(display)
{
    //Initialize(); // Stopper pt. hele koden. Ikke så godt...
}

void Skaerm::SetState(bool state)
{
    if (state) {
        // Turn on the backlight and enable the display
        display_.backlight();
        display_.display();
    }
    else {
        // Turn off the backlight and disable the display
        display_.noBacklight();
        display_.noDisplay();
    }
}

void Skaerm::Update(String message)
{
    int lineIndex = 0; // Track the current line on the display
    String messages[4]; // Array to hold up to 4 lines of text
    for (unsigned int i = 0; i < message.length(); i++) {
        char c = message[i];
        if (lineIndex >= 4) break; // Stop processing if more than 4 lines
        if (c == '\n') lineIndex++; // Move to the next line if '\n' is encountered
        else messages[lineIndex] += c; // Append character to the current line
    }
    display_.clear(); // Clear the display before updating
    for (int i = 0; i < 4; i++) {
        // Set cursor to the beginning of each line and print the corresponding message
        display_.setCursor(0, i);
        display_.print(messages[i]);
    }
}

void Skaerm::Initialize()
{
    display_.init(); // Initialize the LCD display
    display_.backlight(); // Turn on the backlight
}