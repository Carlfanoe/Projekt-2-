#include "Koer_automatisk_plantepleje.h"

koer_automatisk_plantepleje::koer_automatisk_plantepleje(
    Hoejtaler& speaker,
    Skaerm& display,
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
    int waterLevel = waterContainer_.ReadWaterLevel();
    int waterLevelThreshold = waterContainer_.GetThreshold();
    
    if (VerifyWaterLevel(waterLevel, waterLevelThreshold)) {
        for (int i = 0; i < numPlants_; i++) {
            Potteplante& plant = plants_[i];
            if (!plant.VerifyHumidity()) plant.WaterPlant();
        }
    }
    else AlertLowWaterLevel();

    // Print til brugergreanseflade og skærm
    String dataMessage = CreateDataMessage(waterLevel);
    String detailedMessage = CreateDetailedMessage(waterLevel, waterLevelThreshold);
    display_.Update(dataMessage);
    ui_.SendMessage(detailedMessage);
}


bool koer_automatisk_plantepleje::VerifyWaterLevel(int waterLevel, int threshold)
{
    return (waterLevel >= threshold);
}

// Genererer besked med info til skærmen. 
String koer_automatisk_plantepleje::CreateDataMessage(int waterLevel)
{
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
    //display_.Update(message);
    return message;
}

// Genererer besked med info til brugergrænseflade. 
String koer_automatisk_plantepleje::CreateDetailedMessage(int waterLevel, int waterLevelThreshold)
{
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
    //ui_.SendMessage(detailedMessage + "\r\n");
    return detailedMessage;
}

void koer_automatisk_plantepleje::AlertLowWaterLevel()
{
    // tjekker vandstand, kalder højtaler, sender til skærm
    speaker_.tune(500, 50);
    ui_.SendMessage("FEJL: Vandstand i beholderen er for lav!\r\n");
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

        if (function == "start_plantcare") running_ = true;
        else if (function == "stop_plantcare") running_ = false;
        else if (function == "read_values") {
            int waterLevel = waterContainer_.ReadWaterLevel();
            int waterLevelThreshold = waterContainer_.GetThreshold();
            String dataMessage = CreateDataMessage(waterLevel);
            String detailedMessage = CreateDetailedMessage(waterLevel, waterLevelThreshold);
            display_.Update(dataMessage);
            ui_.SendMessage(detailedMessage);
        }
        else if (function == "change_humidity_threshold") {
            int plantID = param1.toInt();
            int newThreshold = param2.toInt();
            if ((plantID == 0 && param1 != "0") || (newThreshold == 0 && param2 != "0")) {
                ui_.SendMessage("FEJL: Én eller flere af de indtastede parametre er ugyldig!\r\n");
            }
            else {
                if (plantID >= 0) {
                    bool plantFound = false;
                    for (int i = 0; i < numPlants_; i++) {
                        auto& plant = plants_[i];
                        if (plantID == plant.GetID()) {
                            plant.SetHumidityThreshold(newThreshold);
                            ui_.SendMessage("Threshold has been updated to " + String(newThreshold) + '%' + " for plant" + String(plantID));
                            plantFound = true;
                        }
                    }
                    if (!plantFound) ui_.SendMessage("FEJL: Invalid plantID argument!\r\n");
                }
            }
        }
        else {
            ui_.SendMessage("FEJL: Indtastet funktion er ugyldig!\r\n");
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