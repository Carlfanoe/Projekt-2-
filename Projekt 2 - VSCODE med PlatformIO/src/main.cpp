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


// Interrupt funktion i main
void serialEvent() {
    // Læser data fra den serielle port og sender det til brugerInterface
    brugerInterface.read();
}

void setup() {
    Serial.begin(9600); // initiere med 9600 baurdrate. Deafaulter til RX1 og TX. Men kan ændres 
	analogReference(DEFAULT); // Sætter "Reference voltage til 5v(deafult)"
}

void loop() {
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

	delay(1000);
}


/*
//////////////////////////////////////////////////////////////////////////////////////////////////////
Grunden til setup() og loop(): 
	Efter at have været frustreret i 2 timer er jeg kommet frem til: 
	Arduino funktioner så som delay() og serial.print() afhænger simpelthen af setup() og loop(). 
	Dvs. at vi ikke kan bruge int main(). - Dette skal vi nok forklarer i rapporten.

//////////////////////////////////////////////////////////////////////////////////////////////////////
Dokumentation på ALLE arduino.h funktioner: https://docs.arduino.cc/language-reference/en/functions/communication/Serial/
	Det er nødvendigt at kigge på, hvis vi f.eks skal bruge flere RX og TX porte, eftersom at Serial.Print
	deafulter til rx1 og tx1.

//////////////////////////////////////////////////////////////////////////////////////////////////////
*/
