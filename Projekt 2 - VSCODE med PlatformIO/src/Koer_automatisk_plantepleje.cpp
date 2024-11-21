#include "Koer_automatisk_plantepleje.h"

// Constructor

    koer_automatisk_plantepleje::koer_automatisk_plantepleje(Potteplante* planter, int antalPlanter)
    : planter(planter), antalPlanter(antalPlanter), selectedPlant(nullptr), previousMillis_(0) {}




void koer_automatisk_plantepleje::ToggleAutomaticPlantCare() {
    const unsigned long interval = 10800000;  // 3 hours in ms

    // Display status message for each plant immediately at startup (only once)
    static bool firstRun = true;  // Flag to check if it's the first run
    if (firstRun) {
        Serial.println("Welcome to the automatic plant care system!");
        Serial.println("The system will now check all your plants' sensor data.");
        firstRun = false;  // Set the flag to false after the first run

        // Print the status message for each plant immediately at startup
        for (int i = 0; i < antalPlanter; i++) {
            planter[i].UpdateSensor();
            String statusMessage = "Plant " + String(planter[i].GetID()) +
                                   ": Humidity - " + String(planter[i].GetHumidity()) + "%" +
                                   ", Threshold - " + String(planter[i].GetThreshold()) +
                                   ", Duration - " + String(planter[i].GetDuration()) + " seconds";
            Serial.println(statusMessage);
        }
    }

    // Check if the time interval has passed (3 hours)
    if (millis() - previousMillis_ >= interval) {
        previousMillis_ = millis();  // Reset the timer

        // Perform automatic plant care check and print the status
        Serial.println("Performing automatic plant care check...");

        for (int i = 0; i < antalPlanter; i++) {
            planter[i].UpdateSensor();  // Update sensor for each plant

            // Construct and print the status message for each plant
            String statusMessage = "Plant " + String(planter[i].GetID()) +
                                   ": Humidity - " + String(planter[i].GetHumidity()) + "%" +
                                   ", Threshold - " + String(planter[i].GetThreshold()) +
                                   ", Duration - " + String(planter[i].GetDuration()) + " seconds";
            Serial.println(statusMessage);
        }

        // A message indicating the system has completed checking all plants
        Serial.println("Plant care check completed. The system will check again in 3 hours.");
    }
}


void koer_automatisk_plantepleje::read() {
    if (brugergraenseflade.IsMessageReady()) {  // Check if there's a message ready
        String input = brugergraenseflade.ReadMessage();  // Read the input message
        input.trim();  // Remove leading/trailing spaces
        input.toLowerCase();  // Convert to lowercase for easier comparison

        if (input.startsWith("select:")) {  // If the command starts with "select:"
            String idStr = input.substring(7);  // Extract the plant ID (after "select:")
            int plantID = idStr.toInt();  // Convert the plant ID to an integer
            selectPlant(plantID);  // Select the plant with the given ID
            Serial.println("Plant selected: " + String(plantID));  // Feedback to user
        } else if (input.startsWith("treshold:")) {  // If the command starts with "treshold:"
            String thresholdStr = input.substring(9);  // Extract the threshold value (after "treshold:")
            int newThreshold = thresholdStr.toInt();  // Convert the threshold to an integer
            if (selectedPlant != nullptr) {
                selectedPlant->SetThreshold(newThreshold);  // Set the new threshold for the selected plant
                Serial.println("Threshold updated to: " + String(newThreshold));  // Feedback to user
            } else {
                Serial.println("No plant selected. Please select a plant first.");  // Error message
            }
        } else if (input.startsWith("duration:")) {  // If the command starts with "duration:"
            String durationStr = input.substring(9);  // Extract the duration value (after "duration:")
            int duration = durationStr.toInt();  // Convert the duration to an integer
            if (selectedPlant != nullptr) {
                selectedPlant->SetDuration(duration);  // Set the new watering duration for the selected plant
                Serial.println("Watering duration updated to: " + String(duration) + " seconds.");  // Feedback to user
            } else {
                Serial.println("No plant selected. Please select a plant first.");  // Error message
            }
        } else if (input == "waterplant") {  // If the command is "waterplant"
            if (selectedPlant != nullptr) {
                selectedPlant->WaterPlant();  // Water the selected plant
                Serial.println("Watering the selected plant...");  // Feedback to user
            } else {
                Serial.println("No plant selected. Please select a plant first.");  // Error message
            }
        } else if (input == "status") {  // If the command is "st"
            if (selectedPlant != nullptr) {
                // Print the selected plant's status
                selectedPlant->UpdateSensor();
                Serial.println("Selected Plant ID: " + String(selectedPlant->GetID()) +
                               ", Humidity: " + String(selectedPlant->GetHumidity()) +
                               ", Threshold: " + String(selectedPlant->GetThreshold()) +
                               ", Duration: " + String(selectedPlant->GetDuration()) + " sec");
            } else {
                Serial.println("No plant selected. Please select a plant first.");  // Error message
            }
        } else {
            Serial.println("Invalid command. Please use a valid command (select:, treshold:, duration:, waterplant, st).");  // Error message for invalid commands
        }
    }
}



void koer_automatisk_plantepleje::selectPlant(int plantID) {
    selectedPlant = nullptr;  // Reset selected plant
    for (int i = 0; i < antalPlanter; i++) {
        if (planter[i].GetID() == plantID) {  // Check if the plant ID matches
            // Deselect all plants before selecting the new one
            for (int j = 0; j < antalPlanter; j++) {
                planter[j].setSelected(false);  // Deselect all plants
            }
            planter[i].setSelected(true);  // Select the plant
            selectedPlant = &planter[i];  // Set the selected plant pointer
            Serial.println("Plant " + String(plantID) + " selected successfully.");  // Feedback to user
            return;
        }
    }
    Serial.println("Plant with ID " + String(plantID) + " not found. Please check the ID and try again.");  // Error message if plant not found
}
