#include "Potteplante.h"
#include "Arduino.h"
#include "Jordfugtighedsensor.h"
#include "Brugergraenseflade.h"

// Man skal have objekter uden for setup() loopet
Potteplante plant1(1, A0, 20, 4); // (ID, PIN, HumidityTreshold, WateringDuration)
Potteplante plant2(2, A1, 20, 4); // (ID, PIN, HumidityTreshold, WateringDuration)

// Eftersom man ikke kan bruge Vectors, så må vi finde en anden løsning
Potteplante planter[] = {plant1, plant2};  // Array af planter
int antalPlanter = sizeof(planter) / sizeof(planter[0]);

Brugergraenseflade brugerInterface(planter, antalPlanter);

// Interrupt når der modtages data. Arduino.h funktion
void serialEvent() {
    // Læser data fra den serielle port og sender det til brugerInterface
    brugerInterface.read();
}

// Benyttes af millis(), vores delay
unsigned long previousMillis = 0;  // Stores the last time something happened
const unsigned long interval = 20000;  // 3 timer = 10800000 ms

void setup() {
    Serial.begin(9600); // initiere med 9600 baudrate. Deafaulter til RX1 og TX. Men kan ændres // VIGTIG! Serial1 for bluetooth Serial for USB
    
	delay(1000);           // Wait for HC-05 to initialize

    analogReference(DEFAULT); // Sætter "Reference voltage til 5v (default)"
}

void loop() {
    unsigned long currentMillis = millis();  // Get the current time in milliseconds

    // Check if the interval (3 hours) has passed
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  // Update previousMillis to current time

        // opdater sensorer
        plant1.UpdateSensor();
        plant2.UpdateSensor();

        // Plante 1
        Serial.print("Fugtighed for Plante 1: ");
        Serial.print(plant1.GetHumidity());
        Serial.print("%");
        Serial.println(); // ny linje

        // Plante 2
        Serial.print("Fugtighed for Plante 2: ");
        Serial.print(plant2.GetHumidity());
        Serial.print("%");
        Serial.println(); // ny linje
    }

    // You can add any other tasks here that should run continuously without delay
    // The rest of your program will continue to run without blocking
}
