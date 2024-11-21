// Arduino Core libraries
#include "Arduino.h"

#include "Potteplante.h"
#include "Koer_automatisk_plantepleje.h"


//Parameters: humiditySensorPin, waterPumpPin, id, humidityThreshold
Potteplante plant1(A0, 21, 1, 20);
Potteplante plant2(A1, 22, 2, 20);
Potteplante planter[] = {plant1, plant2};
koer_automatisk_plantepleje Automatiser(planter);

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println("Testing serial connection...");
    delay(1000);
}