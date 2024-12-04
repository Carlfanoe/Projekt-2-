#include "Brugergraenseflade.h"

Brugergraenseflade::Brugergraenseflade(int baudRate)
{
    Serial.begin(baudRate);
}

bool Brugergraenseflade::IsMessageReady()
{
    return Serial.available();
}

String Brugergraenseflade::ReadMessage()
{
    return Serial.readString();
}

void Brugergraenseflade::SendMessage(String message)
{
    Serial.print(message);
}