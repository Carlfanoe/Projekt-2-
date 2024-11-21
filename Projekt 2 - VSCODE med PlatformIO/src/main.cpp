//#include "Potteplante.h"
#include "Arduino.h"
//#include "avr8-stub.h" // For at debug
#include "Koer_automatisk_plantepleje.h"


// Man skal have objekter uden for setup()
Potteplante plant1(1, A0, 20, 4); // (ID, PIN, HumidityTreshold, WateringDuration)
Potteplante plant2(2, A1, 20, 4); // (ID, PIN, HumidityTreshold, WateringDuration)
Potteplante planter[] = {plant1, plant2}; // Array af planter
koer_automatisk_plantepleje Automatiser(planter, 2);

// Interrupt der kaldes når der er noget på UART buffer
void serialEvent() {
    Automatiser.InterpretUserInput();  
}

void setup() {
    //debug_init(); // Debugging
    Serial1.begin(9600); // initiere med 9600 baudrate. Deafaulter til RX1 og TX. Men kan ændres // VIGTIG! Serial1 for bluetooth Serial for USB
	delay(1000);           // Wait for HC-05 to initialize
    analogReference(DEFAULT); // Sætter "Reference voltage til 5v (default)"

    // Midlertidigt for debugging
    Serial.begin(9600);
}

void loop() {
    //Automatiser.ToggleAutomaticPlantCare();

    // Midlertidigt
    Serial.println("Testing serial connection...");
    delay(1000);
}
