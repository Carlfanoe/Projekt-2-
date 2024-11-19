#include "Display.h"

Display::Display() {InitDisplay();}

void Display::SetDisplayState(bool state)
{
  if (state) {
    // Turn on the backlight and enable the display
    lcd.backlight();
    lcd.display();
  }
  else {
    // Turn off the backlight and disable the display
    lcd.noBacklight();
    lcd.noDisplay();
  }
}

void Display::UpdateDisplay(String message)
{
    int lineIndex = 0; // Track the current line on the display
    String messages[4]; // Array to hold up to 4 lines of text
    for (int i = 0; i < message.length(); i++) {
        char c = message[i];
        if (lineIndex >= 4) break; // Stop processing if more than 4 lines
        if (c == '\n') lineIndex++; // Move to the next line if '\n' is encountered
        else messages[lineIndex] += c; // Append character to the current line
    }
    lcd.clear(); // Clear the display before updating
    for (int i = 0; i < 4; i++) {
      // Set cursor to the beginning of each line and print the corresponding message
      lcd.setCursor(0, i);
      lcd.print(messages[i]);
    }
}

void Display::InitDisplay()
{
    lcd.init(); // Initialize the LCD display
    lcd.backlight(); // Turn on the backlight
}