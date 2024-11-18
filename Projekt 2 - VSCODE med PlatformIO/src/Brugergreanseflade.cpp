#include "Brugergraenseflade.h"

// Constructor
Brugergraenseflade::Brugergraenseflade(Potteplante* planter, int antalPlanter)
    : planter(planter), antalPlanter(antalPlanter), selectedPlant(nullptr) {}

// Helper to normalize input by removing extra spaces and converting to lowercase
String normalizeInput(String input) {
    input.trim(); // Remove leading/trailing whitespace
    input.toLowerCase(); // Convert to lowercase
    input.replace(" ", ""); // Remove all spaces
    return input;
}

// Læser serielle data og håndterer kommandoer
void Brugergraenseflade::read() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n'); // Read the full command
        input = normalizeInput(input);

        if (input.startsWith("select:")) {
            String idStr = input.substring(7);
            if (idStr.toInt() > 0) { // Check for valid integer input
                int plantID = idStr.toInt();
                selectPlant(plantID);
            } else {
                Serial.println("Invalid ID. Please use 'Select: x' where x is a valid plant ID.");
            }
        } else if (input.startsWith("treshold:")) {
            String thresholdStr = input.substring(9);
            int newThreshold = thresholdStr.toInt();
            if (newThreshold >= 0 && newThreshold <= 100) { // Validate range
                changeThreshold(newThreshold);
            } else {
                Serial.println("Invalid threshold. Must be between 0 and 100.");
            }
        } else if (input.startsWith("duration:")) {
            String durationStr = input.substring(9);
            int duration = durationStr.toInt();
            if (duration > 0) { // Ensure positive duration
                changeWaterDuration(duration);
            } else {
                Serial.println("Invalid duration. Must be a positive integer.");
            }
        } else if (input == "waterplant") {
            waterPlant();
        } else if (input == "plantstatus") {
            displayPlantStatus();
        } else {
            Serial.println("Invalid command. Please use one of the following:");
            Serial.println("'Select: x' to select a plant.");
            Serial.println("'Treshold: x' to set a threshold (0-100).");
            Serial.println("'Duration: x' to set watering duration.");
            Serial.println("'Waterplant' to water the selected plant.");
            Serial.println("'Plant status' to display the status of all plants.");
        }
    }
}

// Vælger en plante baseret på ID
void Brugergraenseflade::selectPlant(int plantID) {
    selectedPlant = nullptr; // Nulstil valget
    for (int i = 0; i < antalPlanter; i++) {
        if (planter[i].GetID() == plantID) {
            // Nulstil alle planter til ikke-valgt
            for (int j = 0; j < antalPlanter; j++) {
                planter[j].setSelected(false);
            }
            // Sæt den valgte plante som valgt
            planter[i].setSelected(true);
            selectedPlant = &planter[i];
            Serial.println("Plante valgt: " + String(plantID));
            return;
        }
    }
    Serial.println("Plante ikke fundet");
}

// Ændrer tærskelværdi på den valgte plante
void Brugergraenseflade::changeThreshold(int newThreshold) {
    if (selectedPlant != nullptr) {
        selectedPlant->SetThreshold(newThreshold);
        Serial.println("Grænseværdi opdateret for plante " + String(selectedPlant->GetID()) + ": " + String(newThreshold));
    } else {
        Serial.println("Ingen plante valgt. Brug 'Select: x' først.");
    }
}

// Ændrer vandingsvarighed på den valgte plante
void Brugergraenseflade::changeWaterDuration(int duration) {
    if (selectedPlant != nullptr) {
        selectedPlant->SetDuration(duration);
        Serial.println("Vandingsvarighed opdateret for plante " + String(selectedPlant->GetID()) + ": " + String(duration) + " sekunder");
    } else {
        Serial.println("Ingen plante valgt. Brug 'Select: x' først.");
    }
}

// Vandes den valgte plante
void Brugergraenseflade::waterPlant() {
    if (selectedPlant != nullptr) {
        selectedPlant->WaterPlant();
        Serial.println("Plante " + String(selectedPlant->GetID()) + " bliver vandet");
    } else {
        Serial.println("Ingen plante valgt. Brug 'Select: x' først.");
    }
}

// Viser status for alle planter
void Brugergraenseflade::displayPlantStatus() {
    for (int i = 0; i < antalPlanter; i++) {
        planter[i].UpdateSensor(); // Opdater sensorværdier
        String statusMessage = "Plante " + String(planter[i].GetID()) +
                               ": Fugtighed - " + String(planter[i].GetHumidity()) + "%" +
                               ", Grænseværdi - " + String(planter[i].GetThreshold()) +
                               ", Varighed - " + String(planter[i].GetDuration()) + " sekunder";
        Serial.println(statusMessage);
    }
}
