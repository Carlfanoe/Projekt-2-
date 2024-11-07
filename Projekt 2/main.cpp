#include "UART.h"
#include "plante.h"
#include "VandPumpe.h"

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)

#include <avr/io.h>
#include <util/delay.h>

int main() {
	
	UART uart;
	uart.init(MYUBRR); // Initialiser UART til seriel kommunikation

	// Initialiser en plante med valg for ADC og pumpe pins
	// adcChoice og pumpChoice bruger værdierne 1, 2 eller 3, hvor:
	// 1 = ADC0 / PH5, 2 = ADC1 / PH6, 3 = ADC2 / PH7 på Mega2560
	plante plant1(1, 1, 20, 5);  // adcChoice = 1, pumpChoice = 1, threshold = 20%, varighed = 5 sek.

	
	while (1) {
		uint8_t humidity = plant1.ReadHumidity();
		uart.print("Current Humidity: ");
		uart.printNumber(humidity);
		uart.print("%\n");

		if (humidity < plant1.GetHumidityThreshold()) {
			uart.print("Humidity below threshold! Starting watering...\n");
			plant1.WaterAutomatically();
			uart.print("Watering complete.\n");
			} 
		else {
			uart.print("Humidity is above threshold. No watering needed.\n");
			}
			_delay_ms(10000); // Vent 10 sekunder før næste måling
		}
return 0;
}
	

