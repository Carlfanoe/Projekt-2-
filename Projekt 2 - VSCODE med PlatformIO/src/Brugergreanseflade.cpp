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
                    write("Plante valgt: " + String(plantID));
                    found = true;
                    break;
                }
            }
            if (!found) {
                write("Plante ikke fundet");
            }
        }
        // Håndtering af "set threshold plantX Y"-kommando
        else if (input.startsWith("set threshold plant")) {
            int plantID = input.substring(18, 19).toInt(); // Uddrager ID
            int newThreshold = input.substring(20).toInt(); // Uddrager ny grænseværdi
            bool found = false;
            for (int i = 0; i < antalPlanter; i++) {
                if (planter[i].GetID() == plantID) {
                    planter[i].SetThreshold(newThreshold); // Sætter ny grænseværdi
                    write("Grænseværdi opdateret for plante " + String(plantID) + ": " + String(newThreshold));
                    found = true;
                    break;
                }
            }
            if (!found) {
                write("Plante ikke fundet");
            }
        }
        // Håndtering af "water plantX"-kommando
        else if (input.startsWith("water plant")) {
            int plantID = input.substring(12).toInt(); // Uddrager ID
            bool found = false;
            for (int i = 0; i < antalPlanter; i++) {
                if (planter[i].GetID() == plantID) {
                    planter[i].WaterPlant(); // Vand planten
                    write("Plante " + String(plantID) + " bliver vandet");
                    found = true;
                    break;
                }
            }
            if (!found) {
                write("Plante ikke fundet");
            }
        }
        // Håndtering af "status plantX"-kommando
        else if (input.startsWith("status plant")) {
            int plantID = input.substring(13).toInt(); // Uddrager ID
            bool found = false;
            for (int i = 0; i < antalPlanter; i++) {
                if (planter[i].GetID() == plantID) {
                    String statusMessage = "Plante " + String(plantID) + " status: Fugtighed - " + String(planter[i].GetHumidity()) + "%";
                    write(statusMessage);
                    found = true;
                    break;
                }
            }
            if (!found) {
                write("Plante ikke fundet");
            }
        }
    }
}

// Skriver besked til brugeren
void Brugergraenseflade::write(const String& besked) {
    Serial.println(besked);
}
