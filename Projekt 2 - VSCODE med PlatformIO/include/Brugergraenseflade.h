#pragma once

// Arduino Core libraries
#include "Arduino.h"

class Brugergraenseflade {
public:
    Brugergraenseflade(int baudRate);
    bool IsMessageReady();
    String ReadMessage();
    void SendMessage(String message); // Husk at have \r\n med hvis du vil skrive på ny linje
};