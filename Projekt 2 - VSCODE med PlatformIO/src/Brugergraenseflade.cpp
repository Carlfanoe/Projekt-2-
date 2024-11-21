#include "Brugergraenseflade.h"

Brugergraenseflade::Brugergraenseflade(int baudRate)
{
    Serial1.begin(baudRate);
}

bool Brugergraenseflade::IsMessageReady()
{
    return Serial1.available();
}

String Brugergraenseflade::ReadMessage()
{
    return Serial1.readString();
}

void Brugergraenseflade::SendMessage(String message)
{
    Serial1.print(message);
}