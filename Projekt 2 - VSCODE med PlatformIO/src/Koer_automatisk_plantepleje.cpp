#include "Koer_automatisk_plantepleje.h"

koer_automatisk_plantepleje::koer_automatisk_plantepleje(
    Hoejtaler& speaker, // Reference til højttaleren.
    Skaerm& display,    // Reference til skærmen.
    Brugergraenseflade& ui, // Reference til brugergrænseflade.
    Vandbeholder& waterContainer, // Reference til vandbeholderen.
    Potteplante* plants, // Pointer til en array af potteplanter.
    int numPlants // Antallet af planter i systemet : Bruges til at loope gennem planterne.
) :
    speaker_(speaker),
    display_(display),
    ui_(ui),
    waterContainer_(waterContainer),
    plants_(plants),
    numPlants_(numPlants)
{}

// Funktion til at tjekke planter og vande dem, hvis nødvendigt.
void koer_automatisk_plantepleje::CheckPlants()
{
    int waterLevel = waterContainer_.ReadWaterLevel(); // Læser aktuel vandstand fra beholderen.
    int waterLevelThreshold = waterContainer_.GetThreshold(); // Læser minimumskrav til vandstand.

    // Hvis vandstanden er tilstrækkelig, gennemgå alle planter.
    if (VerifyWaterLevel(waterLevel, waterLevelThreshold)) {
        for (int i = 0; i < numPlants_; i++) {
            Potteplante& plant = plants_[i]; // Reference til den aktuelle plante.
            if (!plant.VerifyHumidity()) // Tjek om planten har brug for vand.
                plant.WaterPlant(); // Vand planten, hvis nødvendigt.
        }
    }
    else AlertLowWaterLevel(); // Advar, hvis vandstanden er for lav.

    // Opdater skærm og brugergrænseflade med vandstand- og planteinformation.
    String dataMessage = CreateDataMessage(waterLevel); 
    String detailedMessage = CreateDetailedMessage(waterLevel, waterLevelThreshold);
    display_.Update(dataMessage);
    ui_.SendMessage(detailedMessage);
}

// Funktion til at verificere, om vandstanden er tilstrækkelig.
bool koer_automatisk_plantepleje::VerifyWaterLevel(int waterLevel, int threshold)
{
    return (waterLevel >= threshold); // Returner true, hvis vandstanden er over grænsen.
}

// Opret kort data-meddelelse, som egnes til visning på skærmen.
String koer_automatisk_plantepleje::CreateDataMessage(int waterLevel)
{
    String message =
        "Vandbeholder: " + String(waterLevel) + "%\n" // Tilføj vandstandsdata.
        + "Jordfugtighed\n";
    for (int i = 0; i < numPlants_; i++) {
        auto& plant = plants_[i];
        int humidity = plant.GetHumidity(); // Få plantens fugtighedsprocent.
        int plantID = plant.GetID(); // Få plantens ID.
        message += "Plante" + String(plantID) + ": " + String(humidity) + "%";
        if (i < (numPlants_ - 1)) message += "\n"; // Tilføj ny linje, hvis der er flere planter.
    }
    return message; // Returner den samlede meddelelse.
}

// Opret detaljeret data-meddelelse til brugergrænsefladen.
String koer_automatisk_plantepleje::CreateDetailedMessage(int waterLevel, int waterLevelThreshold)
{
    String detailedMessage = "                  Vaerdier     Graense\r\n"
        + String("Vandbeholder:     ")
        + String(waterLevel) + String("%           ")
        + String(waterLevelThreshold) + String("%")
        + "\r\n";

    for (int i = 0; i < numPlants_; i++) {
        auto& plant = plants_[i];
        int humidity = plant.GetHumidity(); // Få fugtighed for den aktuelle plante.
        int humidityThreshold = plant.GetHumidityThreshold(); // Få grænse for fugtighed.
        detailedMessage +=
            "Plante" + String(plant.GetID()) + ":          "
            + String(humidity) + String("%           ")
            + String(humidityThreshold) + String("%\r\n");
    }
    return detailedMessage; // Returner den detaljerede meddelelse.
}

// Advarsel om lav vandstand.
void koer_automatisk_plantepleje::AlertLowWaterLevel()
{
    speaker_.tune(500, 50); // Afspil en tone for at indikere lav vandsstand.
    ui_.SendMessage("FEJL: Vandstand i beholderen er for lav!\r\n"); // Send også en advarselsmeddelelse til ui.
}

// Behandler input fra brugergrænsefladen.
void koer_automatisk_plantepleje::ProcessInput()
{
    if (ui_.IsMessageReady()) { // Tjek om der er en besked klar.
        String input = ui_.ReadMessage(); // Læs beskeden.
        String function, param1, param2 = "";
        InterpretInput(input, function, param1, param2);
        /*
            InterpretInput() opdeler inputtet ved mellemrum.
            Herefter indeler den det i:
                1. ord: function
                2. ord: param1
                3. ord: param2
        */ 

        if (function == "start_plantcare") { // Start plantpleje.
            running_ = true;
            ui_.SendMessage("Automatiseret plantepleje er startet!\r\n");
        }
        else if (function == "stop_plantcare") { // Stop plantpleje.
            running_ = false;
            ui_.SendMessage("Automatiseret plantepleje er stoppet!\r\n");
        }
        else if (function == "read_values") { // Læs aktuelle værdier og opdater brugergrænsefladen.
            int waterLevel = waterContainer_.ReadWaterLevel();
            int waterLevelThreshold = waterContainer_.GetThreshold();
            String dataMessage = CreateDataMessage(waterLevel);
            String detailedMessage = CreateDetailedMessage(waterLevel, waterLevelThreshold);
            display_.Update(dataMessage);
            ui_.SendMessage(detailedMessage);
        }
        else if (function == "change_humidity_threshold") { // Ændr fugtighedsgrænse for en plante.
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
                        if (plantID == plant.GetID()) { // Tjek om plante-ID matcher.
                            plant.SetHumidityThreshold(newThreshold); // Opdater grænsen.
                            ui_.SendMessage(
                                "Threshold has been updated to "
                                + String(newThreshold) + '%'
                                + " for plant"
                                + String(plantID));
                            plantFound = true;
                        }
                    }
                    if (!plantFound) ui_.SendMessage("FEJL: Invalid plantID argument!\r\n");
                }
            }
        }
        else {
            // Fejlmeddelelse for ugyldig funktion.
            ui_.SendMessage("FEJL: Indtastet funktion er ugyldig!\r\n");
        }
    }
}

// Returnerer den nuværende kørselstilstand.
bool koer_automatisk_plantepleje::GetRunningState() { return running_; }

// Hjælpefunktion til at fortolke input.
void koer_automatisk_plantepleje::InterpretInput(
    String &input,      // Brugerinput.
    String &function,   // Funktion identificeret i input.
    String &param1,     // Første parameter i input.
    String &param2      // Anden parameter i input.
) {
    input.trim(); // Fjern overflødige mellemrum.
    input.toLowerCase(); // Konverter til små bogstaver.

    int firstSpaceIndex = input.indexOf(' '); // Find første mellemrum.

    if (firstSpaceIndex != -1) {
        function = input.substring(0, firstSpaceIndex); // Udtræk funktion.
        String parameters = input.substring(firstSpaceIndex + 1); // Udtræk parametre.
        int secondsSpaceIndex = parameters.indexOf(' '); // Find næste mellemrum.
        if (secondsSpaceIndex != -1) {
            param1 = parameters.substring(0, secondsSpaceIndex); // Første parameter.
            param2 = parameters.substring(secondsSpaceIndex + 1); // Anden parameter.
        }
        else param1 = parameters; // Hvis kun én parameter findes.
    }
    else function = input; // Hvis der kun er en funktion.
}