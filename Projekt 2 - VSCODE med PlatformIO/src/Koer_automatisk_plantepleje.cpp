#include "Koer_automatisk_plantepleje.h"

koer_automatisk_plantepleje::koer_automatisk_plantepleje(
    Hoejtaler& speaker,
    LiquidCrystal_I2C& display,
    Brugergraenseflade& ui,
    Vandbeholder& waterContainer,
    Potteplante* plants,
    int numPlants
) :
    speaker_(speaker),
    display_(display),
    ui_(ui),
    waterContainer_(waterContainer),
    plants_(plants),
    numPlants_(numPlants)
{}

// Itterere gennem alle planter, printer alle sensorer til begge skærme og vande planter
void koer_automatisk_plantepleje::CheckPlants()
{
    // AlertLowWaterLevel(); //Midlertidig test

    if (!VerifyWaterLevel()) AlertLowWaterLevel();

    for (int i = 0; i < numPlants_; i++) {
        Potteplante& plant = plants_[i];
        if (!plant.VerifyHumidity()) plant.WaterPlant();
    }

    // Print til brugergreanseflade og skærm
    SendDetailedMessage();
}


bool koer_automatisk_plantepleje::VerifyWaterLevel()
{
    return waterContainer_.ReadWaterLevel() >= waterContainer_.GetThreshold();
}

// Genererer besked med info til skærmen. 
void koer_automatisk_plantepleje::SendDataMessage()
{
    int waterLevel = waterContainer_.ReadWaterLevel();
    String message =
        "Vandbeholder: " + String(waterLevel) + "%\n"
        + "Jordfugtighed\n";
    for (int i = 0; i < numPlants_; i++) {
        auto& plant = plants_[i];
        int humidity = plant.GetHumidity();
        int plantID = plant.GetID();
        message += "Plante" + String(plantID) + ": " + String(humidity) + "%";
        if (i < (numPlants_ - 1)) message += "\n";
    }
    ui_.SendMessage(message);
    display_.Update(message);
    //return message;
}

// Genererer besked med info til brugergrænseflade. 
void koer_automatisk_plantepleje::SendDetailedMessage()
{
    int waterLevel = waterContainer_.ReadWaterLevel();
    int waterLevelThreshold = waterContainer_.GetThreshold();

    String detailedMessage = "                  Vaerdier     Graense\r\n"
        + String("Vandbeholder:     ")
        + String(waterLevel) + String("%           ")
        + String(waterLevelThreshold) + String("%")
        + "\r\n";
    

    for (int i = 0; i < numPlants_; i++) {
        auto& plant = plants_[i];
        int humidity = plant.GetHumidity();
        int humidityThreshold = plant.GetHumidityThreshold();
        detailedMessage +=
            "Plante" + String(plant.GetID()) + ":          "
            + String(humidity) + String("%           ")
            + String(humidityThreshold) + String("%\r\n");
    }
    ui_.SendMessage(detailedMessage + "\r\n");
    //return detailedMessage;
}

void koer_automatisk_plantepleje::AlertLowWaterLevel()
{
    // tjekker vandstand, kalder højtaler, sender til skærm
    speaker_.tune(500, 50);
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
            SendDataMessage();
            SendDetailedMessage();
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
    input.toLowerCase(); // Gør hele inputtet til lowercase

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