#pragma once
#include <Arduino.h>
#include "Potteplante.h"

class Brugergraenseflade {
private:
    Potteplante* planter; // Pointer til array af plante-objekter
    int antalPlanter;     // Antal planter i systemet

public:
    // Constructor
    Brugergraenseflade(Potteplante* planter, int antalPlanter);

    // Funktion til at læse serielle data
    void read();

    // Funktion til at skrive feedback til brugeren
    void write(const String& besked);
};
