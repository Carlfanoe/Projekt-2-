// Arduino Core libraries
#include "Arduino.h"

// Klasser
#include "Potteplante.h"
#include "Koer_automatisk_plantepleje.h"

LiquidCrystal_I2C display = LiquidCrystal_I2C(0x27, 20, 4);
Brugergraenseflade ui = {9600}; // UART1 ved baud-rate på 9600
Vandbeholder waterContainer = {
    22, // trigPin
    23, // echoPin
    20, // Threshold
    30, // Afstand i cm ved tom vandbeholder
    3   // Afstand i cm ved fyldt vandbeholder
};

Potteplante plants[] = {
    {0, A0, 20, 20, 5}, // Test-plante: Fugtighed kan justeres ved potentiometer på A0
    {1, A1, 21, 20, 5}, // Plante nr. 1
    {2, A2, 22, 20, 5}  // Plante nr. 2
};
/* 
    Plante parametre:
    • id,
    • humiditySensorPin,
    • waterPumpPin,
    • humidityThreshold,
    • duration
*/

int numPlants = sizeof(plants) / sizeof(plants[0]);
koer_automatisk_plantepleje plantepleje(display, ui, waterContainer, plants, numPlants);

void serialEvent1() {plantepleje.ProcessInput();}

void setup() {
    Serial.begin(9600); // Midlertidigt til debugging
}

unsigned long threeHours = 1000;
/*
    Bemærk at threeHours lige nu er indstillet til 0ms,
    dvs. CheckPlants() kører konstant uden delay.
    I endelig version af koden, vil det være tre timer:
    1000 * 60 * 60 * 3
*/

unsigned long lastCheckTime = millis() - threeHours; // Sikrer at systemet tjekker ved start
void loop() {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastCheckTime;

    if (plantepleje.GetRunningState() && (elapsedTime > threeHours)) {
        lastCheckTime = currentTime;
        plantepleje.CheckPlants();
    }
}