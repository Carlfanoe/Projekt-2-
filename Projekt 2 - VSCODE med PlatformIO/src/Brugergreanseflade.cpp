#include "Brugergraenseflade.h"

// Constructor
Brugergraenseflade::Brugergraenseflade(Potteplante* planter, int antalPlanter)
    : planter(planter), antalPlanter(antalPlanter) {}

// Læser serielle data og håndterer kommandoer
void Brugergraenseflade::read() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n'); // Læser hele kommandoen
        input.trim(); // Fjerner unødvendige mellemrum

        // Håndtering af "select plantX"-kommando
        if (input.startsWith("select plant")) {
            int plantID = input.substring(12).toInt(); // Uddrager ID
            bool found = false;
            for (int i = 0; i < antalPlanter; i++) {
                if (planter[i].GetID() == plantID) {
                    // Nulstil alle planter til ikke-valgt
                    for (int j = 0; j < antalPlanter; j++) {
                        planter[j].setSelected(false);
                    }
                    // Sæt den valgte plante som valgt
                    planter[i].setSelected(true);
                    write("Plante fundet! Angiv Threshold eller Duration.");
                    found = true;
                    break; // Afslut efter plantens ID er fundet
                }
            }
            if (!found) {
                write("Plante ikke fundet. Prøv igen.");
            }
        } 
        // Håndtering af "Threshold = X"-kommando
        else if (input.startsWith("Threshold =")) {
            int threshold = input.substring(11).toInt(); // Uddrager værdi
            bool updated = false;
            for (int i = 0; i < antalPlanter; i++) {
                if (planter[i].isSelected()) { // Kontroller om planten er valgt
                    planter[i].SetThreshold(threshold);
                    write("Threshold opdateret.");
                    updated = true;
                    break;
                }
            }
            if (!updated) {
                write("Ingen plante valgt. Brug 'select plantX' først.");
            }
        } 
        // Håndtering af "Duration = X"-kommando
        else if (input.startsWith("Duration =")) {
            int duration = input.substring(10).toInt(); // Uddrager værdi
            bool updated = false;
            for (int i = 0; i < antalPlanter; i++) {
                if (planter[i].isSelected()) { // Kontroller om planten er valgt
                    planter[i].SetDuration(duration);
                    write("Duration opdateret.");
                    updated = true;
                    break;
                }
            }
            if (!updated) {
                write("Ingen plante valgt. Brug 'select plantX' først.");
            }
        } 
        // Ugyldig kommando
        else {
            write("Ugyldigt input. Prøv igen.");
        }
    }
}

// Sender feedback til brugeren
void Brugergraenseflade::write(const String& besked) {
    Serial.println(besked); // Skriver besked til den serielle port
}
