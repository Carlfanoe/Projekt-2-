#include "Potteplante.h"
#include "Arduino.h"
#include "Koer_automatisk_plantepleje.h"


// Man skal have objekter uden for setup() loopet
Potteplante plant1(1, A0, 20, 4); // (ID, PIN, HumidityTreshold, WateringDuration)
Potteplante plant2(2, A1, 20, 4); // (ID, PIN, HumidityTreshold, WateringDuration)
Potteplante planter[] = {plant1, plant2};  // Array af planter
koer_automatisk_plantepleje Automatiser(planter, 2);

// Interrupt der kaldes når der er noget på UART buffer
void SerialEvent() {
    Automatiser.InterpretUserInput();  
}

void setup() {
    Serial.begin(9600); // initiere med 9600 baudrate. Deafaulter til RX1 og TX. Men kan ændres // VIGTIG! Serial1 for bluetooth Serial for USB
	delay(1000);           // Wait for HC-05 to initialize
    analogReference(DEFAULT); // Sætter "Reference voltage til 5v (default)"
}

void loop() {
    
   Automatiser.ToggleAutomaticPlantCare();

}
