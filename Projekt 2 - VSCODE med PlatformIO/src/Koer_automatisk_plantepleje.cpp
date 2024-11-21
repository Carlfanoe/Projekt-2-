#include "Koer_automatisk_plantepleje.h"

koer_automatisk_plantepleje::koer_automatisk_plantepleje(Potteplante* plants, int numPlants)
    : plants_(plants), numPlants_(numPlants)
{}

void koer_automatisk_plantepleje::CheckPlants()
{
    Serial.println("Checking plants...");
    // Kode mangler
}

bool koer_automatisk_plantepleje::VerifyHumidity(Potteplante &plant)
{
    // Kode mangler
    return false;
}

bool koer_automatisk_plantepleje::VerifyWaterLevel()
{
    // Kode mangler
    return false;
}

String koer_automatisk_plantepleje::CreateDataMessage()
{
    // int waterLevel = waterContainer_.ReadWaterLevel();
    // String message =
    //         "Vandbeholder: " + String(waterLevel) + "%\n"
    //         + "Jordfugtighed\n";
    // for (int i = 0; i < antalPlanter_; i++) {
    //     auto& plante = planter_[i];
    //     plante.UpdateSensor();
    //     int humidity = plante.GetHumidity();
    //     int plantID = plante.GetID();
    //     message += "Plante" + String(plantID) + ": " + String(humidity) + "%";
    //     if (i < (antalPlanter_ - 1)) message += "\n";
    // }
    // return message;

    return String();
}

void koer_automatisk_plantepleje::AlertLowWaterLevel()
{
    // Kode mangler
}

void koer_automatisk_plantepleje::ProcessInput()
{
    if (ui_.IsMessageReady()) {
        String input = ui_.ReadMessage();
        String function, param1, param2 = "";
        InterpretInput(input, function, param1, param2);
        
        if (function == "toggle_plantcare") running_ = !running_;
        else if (function == "read_values") {
            // Kode mangler
        }
        else if (function == "change_humidity_threshold") {
            // Kode mangler
        }
        else if (function == "PrintInput") { // Testfunktion
            Serial.println(input);
            String messageToSend =
                "f:" + function
                + ", p1:" + param1
                + ", p2:" + param2
                + "\r\n";
            ui_.SendMessage(messageToSend);
        }
        else ui_.SendMessage("Indtastet funktion er ugyldig.");
    }
}

bool koer_automatisk_plantepleje::GetRunningState()
{
    return running_;
}

int koer_automatisk_plantepleje::GetPlantsAmount()
{
    // int amount = 0;
    // for (auto& Potteplante : plants_) amount += 1;
    // return amount;

    return sizeof(plants_) / sizeof(plants_[0]);
}

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
