#include "Koer_automatisk_plantepleje.h"

koer_automatisk_plantepleje::koer_automatisk_plantepleje(Potteplante* plants, int numPlants)
    : plants_(plants), numPlants_(numPlants)
{}

// Itterere gennem alle planter, printer alle sensorer til begge skærme 
void koer_automatisk_plantepleje::CheckPlants()
{
    for (int i = 0; i < numPlants_; i++) {

        Potteplante& plant = plants_[i];

    // Vand plante
        if (!plant.VerifyHumidity()) {
            // Vand plante
        }

    // Print til brugergreanseflade
            String dataMessage = CreateDataMessage();
            String waterLevel = String(waterContainer_.ReadWaterLevel());
            String message =
                "-----Værdier-----\r\n"
                + dataMessage + "\r\n"
                + "-----Thresholds-----\r\n"
                + "Vandbeholder: " + waterLevel + "%\r\n";
            for (int i = 0; i < numPlants_; i++) {
                String humidityThreshold = String(plants_[i].GetHumidityThreshold());
                message += "Plante" + String(i + 1) + ": " + humidityThreshold + "%\r\n";
            }
            ui_.SendMessage(message);
    }

    //Serial.println("Checking plants...");
}

bool koer_automatisk_plantepleje::VerifyWaterLevel()
{
    // Kode mangler
    return false;
}

// Sender beskede med info til skærmen. 
String koer_automatisk_plantepleje::CreateDataMessage()
{
    int waterLevel = 69; //waterContainer_.ReadWaterLevel();
    String message =
            "Vandbeholder: " + String(waterLevel) + "%\n"
            + "Jordfugtighed\n";
    for (int i = 0; i < numPlants_; i++) {
        auto& plant = plants_[i];
        //plant.UpdateSensor();
        int humidity = 69; //plant.GetHumidity();
        int plantID = plant.GetID();
        message += "Plante" + String(plantID) + ": " + String(humidity) + "%";
        if (i < (numPlants_ - 1)) message += "\n";
    }
    return message;
}

void koer_automatisk_plantepleje::AlertLowWaterLevel()
{
    // tjekker vandstand, kalder højtaler, sender til skærm 
}

// bruges til at sende beskede via interrupt 
void koer_automatisk_plantepleje::ProcessInput()
{
    if (ui_.IsMessageReady()) {
        String input = ui_.ReadMessage();
        String function, param1, param2 = "";
        InterpretInput(input, function, param1, param2);
        /*
            InterpretInput() opdeler inputtet ved mellemrum.
            Herefter indeler den det i:
                1. ord: function
                2. ord: param1
                3. ord: param2
        */ 

        if (function == "toggle_plantcare") { // ØHH FEJL? LIGE MEGET HVAD SLUKKER DEN?
            running_ = !running_;
        }
        else if (function == "read_values") {
            String dataMessage = CreateDataMessage();
            ui_.SendMessage(dataMessage);
        }
        else if (function == "read_all_data") { // Ikke en del af kravspec, men nice for debugging
            String dataMessage = CreateDataMessage();
            String waterLevel = String(waterContainer_.ReadWaterLevel());
            String message =
                "-----Værdier-----\r\n"
                + dataMessage + "\r\n"
                + "-----Thresholds-----\r\n"
                + "Vandbeholder: " + waterLevel + "%\r\n";
            for (int i = 0; i < numPlants_; i++) {
                String humidityThreshold = String(plants_[i].GetHumidityThreshold());
                message += "Plante" + String(i + 1) + ": " + humidityThreshold + "%\r\n";
            }
            ui_.SendMessage(message);
        }
        else if (function == "change_humidity_threshold") {
            int plantID = param1.toInt();
            int newThreshold = param2.toInt();
            if ((plantID == 0 && param1 != "0") || (newThreshold == 0 && param2 != "0")) {
                ui_.SendMessage("Én eller flere af de indtastede parametre er ugyldig.");
            }
            else {
                if (plantID >= 0 && plantID < numPlants_) {
                    plants_[plantID].SetHumidityThreshold(newThreshold);
                }
            }
        }
        else {
            ui_.SendMessage("Indtastet funktion er ugyldig.\r\n");
        }
    }
}

bool koer_automatisk_plantepleje::GetRunningState()
{
    return running_;
}

// hjælpefunktion til processinput, og bruges til at splitte beskeder 
void koer_automatisk_plantepleje::InterpretInput(
    String &input,
    String &function,
    String &param1,
    String &param2
) {
    input.trim(); // Fjerner spaces foran/efter input

    int firstSpaceIndex = input.indexOf(' ');

    if (firstSpaceIndex != -1) {
        function = input.substring(0, firstSpaceIndex);
        String parameters = input.substring(firstSpaceIndex + 1);
        int secondsSpaceIndex = parameters.indexOf(' ');
        if (secondsSpaceIndex != -1) {
            param1 = parameters.substring(0, secondsSpaceIndex);
            param2 = parameters.substring(secondsSpaceIndex + 1);
        }
        else param1 = parameters;
    }
    else function = input;
}