// Arduino Core libraries
#include "Arduino.h"

// Klasser
#include "Potteplante.h"
#include "Koer_automatisk_plantepleje.h"

//Parameters: humiditySensorPin, waterPumpPin, id, humidityThreshold, duration
Potteplante plant1(A0, 8, 21, 1, 20, 5);
//Potteplante plant2(A1, 9, 22, 2, 20, 5);
Potteplante plants[] = {plant1};

int numPlants = sizeof(plants) / sizeof(plants[0]);
koer_automatisk_plantepleje plantepleje(plants, numPlants);

void serialEvent1() {plantepleje.ProcessInput();}

void setup() {
    Serial.begin(9600); // Midlertidigt til debugging
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);

}

unsigned long threeHours = 5000; //1000 * 60 * 60 * 3; // I milliseconds
/*      Bemærk at threeHours lige nu er
        indstillet til 1000ms --> 1 sekund      */
unsigned long lastCheckTime = millis() - threeHours; // Sikrer at systemet tjekker ved start
void loop() {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastCheckTime;

    if (plantepleje.GetRunningState() && (elapsedTime > threeHours)) {
        lastCheckTime = currentTime;
        plantepleje.CheckPlants();
    }
}