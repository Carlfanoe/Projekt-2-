#include "Potteplante.h"
#include "Arduino.h"
#include "Jordfugtighedsensor.h"

int main(void) {

/*
Potteplante plant1(A0, 0, 20, 5); // Brug ADC0 til plant1
	Potteplante plant2(A1, 1, 20, 5); // Brug ADC1 til plant2

*/
/*

Jordfugtighedsensor test(A0);
*/

	// Initialize serial communication at 9600 baud with 5V refernce
	analogReference(DEFAULT); 
  	Serial.begin(9600);  
   

	while(!Serial) { 
        // Wait for the Serial connection to be established
    }


	while (1) {
		/*
		plant1.UpdateSensor();
		plant2.UpdateSensor();

		Serial.print("Humidity plant1: ");
		Serial.print(plant1.GetHumidity());
		Serial.println("%");

		Serial.print("Humidity plant2: ");
		Serial.print(plant2.GetHumidity());
		Serial.println("%");

		delay(4000);
		
		*/
		// Update the sensor (this will call SetHumidity in the sensor class)
		
		/*
			
		test.SetHumidity();
		Serial.print("Humidity test: ");
		Serial.print(test.GetHumidity());
		Serial.println("%");		
		delay(4000);
		*/
		Serial.print("Humidity test: ");

		delay(4000);
	}

	return 0;
}
