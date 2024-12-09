#include "Arduino.h" // Arduino Core libraries

// Klasser
#include "Koer_automatisk_plantepleje.h" // Kontrol-klassen
#include "Potteplante.h"

// Initialisering af globale objekter.
Hoejtaler speaker = {6}; // Initialiserer højttaler på pin 6.
Skaerm display(
    0x27,   // I2C-adresse
    20,     // 20 kolonner
    4       // 4 rækker
);
Brugergraenseflade ui = {9600}; // UART1 til kommunikation ved 9600 baud.
Vandbeholder waterContainer = {
    22, // trigPin: Pin til at trigge ultralydssensoren.
    23, // echoPin: Pin til at modtage ultralydseko.
    20, // Threshold: Minimumsvandstand i procent.
    30, // Afstand (cm) ved tom vandbeholder.
    3   // Afstand (cm) ved fyldt vandbeholder.
};

Potteplante plants[] = { // Definerer planter med parametre, som set nedenunder.
    {1, A1, 7, 20, 1000},
    {2, A2, 10, 20, 1000}
};
/*
    Plante parametre:
    • id: Unikt ID for planten.
    • humiditySensorPin: Analog pin for fugtighedssensor.
    • waterPumpPin: Digital pin for vandpumpe.
    • humidityThreshold: Minimum fugtighed i procent.
    • duration: Varighed af vanding i millisekunder.
*/

// Antallet af planter beregnes automatisk:
int numPlants = sizeof(plants) / sizeof(plants[0]);

// Initialiserer plantepleje med referencer til modulerne
koer_automatisk_plantepleje plantepleje(
    speaker,
    display,
    ui,
    waterContainer,
    plants,
    numPlants
);

// Kaldes automatisk vha. Arduino Core Libraries, når der er ny data på Serial1 (UART1).
void serialEvent1() { plantepleje.ProcessInput(); }

void setup() { // Kaldes automatisk vha. Arduino Core Libraries.
    display.Initialize(); // Initialiser skærmen.
}

unsigned long threeHours = 1000 * 60 * 60 * 3; // Definering af tre timer i sekunder

// Tidsforskel mellem sidste tjek af planter: 0 i starten, så der tjekkes ved start:
unsigned long lastCheckTime = millis() - threeHours;

void loop() { // Kaldes automatisk vha. Arduino Core Libraries
    unsigned long currentTime = millis(); // Få den aktuelle tid i millisekunder.
    unsigned long elapsedTime = currentTime - lastCheckTime; // Aktuel tidsforskel

    if (plantepleje.GetRunningState() && (elapsedTime > threeHours)) {
        // Hvis systemet er aktivt og der er gået tre timer siden sidste tjek:
        lastCheckTime = currentTime; // Opdater sidste tjek-tid.
        plantepleje.CheckPlants(); // Udfør tjek og evt. vanding af planter.
    }
}