#include "Koer_automatisk_plantepleje.h"

String koer_automatisk_plantepleje::CreateDataMessage()
{
    int waterLevel = waterContainer_.ReadWaterLevel();
    String message =
            "Vandbeholder: " + String(waterLevel) + "%\n"
            + "Jordfugtighed\n";
    for (int i = 0; i < antalPlanter_; i++) {
        auto& plante = planter_[i];
        plante.UpdateSensor();
        int humidity = plante.GetHumidity();
        int plantID = plante.GetID();
        message += "Plante" + String(plantID) + ": " + String(humidity) + "%";
        if (i < (antalPlanter_ - 1)) message += "\n";
    }
    return message;
}

// Constructor
koer_automatisk_plantepleje::koer_automatisk_plantepleje(Potteplante* planter, int antalPlanter)
    :   planter_(planter), antalPlanter_(antalPlanter)
{}

void koer_automatisk_plantepleje::ToggleAutomaticPlantCare() {
    const unsigned long interval = 10800000;  // 3 hours in ms

    // Display status message for each plant immediately at startup (only once)
    static bool firstRun = true;  // Flag to check if it's the first run
    if (firstRun) {
        Serial.println();
        Serial.println("Welcome to the automatic plant care system!");
        Serial.println("The system will now check all your plants' sensor data.");
        firstRun = false;  // Set the flag to false after the first run

        // Print the status message for each plant immediately at startup
        String message = CreateDataMessage();
        Serial.println(message); // Til brugegrænsefladen
        display_.UpdateDisplay(message); // Til skærmen
    }

    // Check if the time interval has passed (3 hours)
    if (millis() - previousMillis_ >= interval) {
        previousMillis_ = millis();  // Reset the timer

        // Perform automatic plant care check and print the status
        Serial.println("Performing automatic plant care check...");

        String message = CreateDataMessage();
        Serial.println(message); // Til brugegrænsefladen
        display_.UpdateDisplay(message); // Til skærmen

        // A message indicating the system has completed checking all plants
        Serial.println("Plant care check completed. The system will check again in 3 hours.");
    }
}

void koer_automatisk_plantepleje::InterpretUserInput() {
    if (ui_.IsMessageReady()) {  // Check if there's a message ready
        String input = ui_.ReadMessage();  // Read the input message

        if (input.startsWith("select:")) {  // If the command starts with "select:"
            String idStr = input.substring(7);  // Extract the plant ID (after "select:")
            int plantID = idStr.toInt();  // Convert the plant ID to an integer
            selectPlant(plantID);  // Select the plant with the given ID
            Serial.println("Plant selected: " + String(plantID));  // Feedback to user
        } else if (input.startsWith("treshold:")) {  // If the command starts with "treshold:"
            String thresholdStr = input.substring(9);  // Extract the threshold value (after "treshold:")
            int newThreshold = thresholdStr.toInt();  // Convert the threshold to an integer
            if (selectedPlant_ != nullptr) {
                selectedPlant_->SetThreshold(newThreshold);  // Set the new threshold for the selected plant
                Serial.println("Threshold updated to: " + String(newThreshold));  // Feedback to user
            } else {
                Serial.println("No plant selected. Please select a plant first.");  // Error message
            }
        } else if (input.startsWith("duration:")) {  // If the command starts with "duration:"
            String durationStr = input.substring(9);  // Extract the duration value (after "duration:")
            int duration = durationStr.toInt();  // Convert the duration to an integer
            if (selectedPlant_ != nullptr) {
                selectedPlant_->SetDuration(duration);  // Set the new watering duration for the selected plant
                Serial.println("Watering duration updated to: " + String(duration) + " seconds.");  // Feedback to user
            } else {
                Serial.println("No plant selected. Please select a plant first.");  // Error message
            }
        } else if (input == "waterplant") {  // If the command is "waterplant"
            if (selectedPlant_ != nullptr) {
                selectedPlant_->WaterPlant();  // Water the selected plant
                Serial.println("Watering the selected plant...");  // Feedback to user
            } else {
                Serial.println("No plant selected. Please select a plant first.");  // Error message
            }
        } else if (input == "status") {  // If the command is "status"
            if (selectedPlant_ != nullptr) {
                // Print the selected plant's status
                Serial.println("Selected Plant ID: " + String(selectedPlant_->GetID()) +
                                ", Humidity: " + String(selectedPlant_->GetHumidity()) +
                                ", Threshold: " + String(selectedPlant_->GetThreshold()) +
                                ", Duration: " + String(selectedPlant_->GetDuration()) + " sec");
            } else {
                Serial.println("No plant selected. Please select a plant first.");  // Error message
            }
        } else {
            Serial.println("Invalid command. Please use a valid command (select:, treshold:, duration:, waterplant, status).");  // Error message for invalid commands
        }
    }
}

void koer_automatisk_plantepleje::selectPlant(int plantID) {
    selectedPlant_ = nullptr;  // Reset selected plant
    for (int i = 0; i < antalPlanter_; i++) {
        if (planter_[i].GetID() == plantID) {  // Check if the plant ID matches
            // Deselect all plants before selecting the new one
            for (int j = 0; j < antalPlanter_; j++) {
                planter_[j].setSelected(false);  // Deselect all plants
            }
            planter_[i].setSelected(true);  // Select the plant
            selectedPlant_ = &planter_[i];  // Set the selected plant pointer
            Serial.println("Plant " + String(plantID) + " selected successfully.");  // Feedback to user
            return;
        }
    }
    Serial.println("Plant with ID " + String(plantID) + " not found. Please check the ID and try again.");  // Error message if plant not found
}
