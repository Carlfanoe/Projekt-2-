// Arduino Core libraries
#include "Arduino.h"

#include "avr8-stub.h"

#include "Potteplante.h"
#include "Koer_automatisk_plantepleje.h"

//Parameters: humiditySensorPin, waterPumpPin, id, humidityThreshold
Potteplante plant1(A0, 21, 1, 20, 5);
Potteplante plant2(A1, 22, 2, 20, 5);
Potteplante planter[] = {plant1, plant2};
koer_automatisk_plantepleje Automatiser(planter);

// Skal måske hedde serial1
void serialEvent1() {
    Automatiser.InterpretUserInput();
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
}

void loop() {
    Serial.println("Loop is running as it should...");
    delay(1000);
}