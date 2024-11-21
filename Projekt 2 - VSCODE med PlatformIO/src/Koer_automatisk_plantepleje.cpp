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
    // Kode mangler
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
        else ui_.SendMessage("Indtastet funktion er ugyldig.\r\n");
    }
}

bool koer_automatisk_plantepleje::GetRunningState()
{
    return running_;
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
