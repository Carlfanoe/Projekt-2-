#pragma once
#include <Arduino.h>

class Brugergraenseflade {
public:
    static bool IsMessageReady();
    static String ReadMessage();
    static void SendMessage(String Message);
};
