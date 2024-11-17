#include "Potteplante.h"
#include "Arduino.h"
#include "Jordfugtighedsensor.h"

/*
//////////////////////////////////////////////////////////////////////////////////////////////////////
Grunden til setup() og loop(): 
	Efter at have været frustreret i 2 timer er jeg kommet frem til: 
	Arduino funktioner så som delay() og serial.print() afhænger simpelthen af setup() og loop(). 
	Dvs. at vi ikke kan bruge int main(). - Dette skal vi nok forklarer i rapporten.
	
//////////////////////////////////////////////////////////////////////////////////////////////////////
*/

// Man skal have objekter uden for setup() loopet
Potteplante plante1(1, A0, 20, 4); // (ID, PIN, HumidityTreshold, WateringDuration)
Potteplante plante2(2, A1, 20, 4); // (ID, PIN, HumidityTreshold, WateringDuration)


void setup() {
    Serial.begin(9600); // initiere Serial kommunikation med 9600 baurdrate
	analogReference(DEFAULT); // Sætter "Reference voltage til 5v(deafult)"

}

void loop() {
   
   	// opdater sensorer
	plante1.UpdateSensor();
	plante2.UpdateSensor();


	// Plante 1
	Serial.print("Fugtighed for Plante 1: ");
	Serial.print(plante1.GetHumidity());
	Serial.print("%");
	Serial.println(); // ny linje

	// Plante 2
	Serial.print("Fugtighed for Plante 2: ");
	Serial.print(plante2.GetHumidity());
	Serial.print("%");
	Serial.println(); // ny linje

	delay(1000);
}
