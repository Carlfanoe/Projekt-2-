#include <avr/io.h>
#include "Potteplante.h"
#include "UART.h"
#include "Brugergreanseflade.h"

// Define the UART baud rate for 9600 (adjust depending on your system clock)
#define F_CPU 16000000UL  // Assuming a 16MHz clock (adjust if different)
#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

#include <stdio.h>
#include <util/delay.h>

brugergraenseflade btInterface(9600);  // Baudrate sættes til 9600

int main(void) {

	Potteplante plant1(1, 0, 20, 5); // Brug ADC0 til plant1
	Potteplante plant2(2, 1, 20, 5); // Brug ADC1 til plant2

	while (1) {
		
		// Update the sensor (this will call SetHumidity in the sensor class)
		plant1.UpdateSensor();
		
		// Convert humidity to a string
		char humidityStr[10];  // Adjust size if needed
		sprintf(humidityStr, "%d", (int)plant1.GetHumidity());  // Convert humidity to string
		
		// Send humidity value via UART
		btInterface.SendMessage("Humidity for plant 1: ");
		btInterface.SendMessage(humidityStr);  // Send the string
		btInterface.SendMessage("\r\n");
		
// 		// Send threshold value via UART
// 		btInterface.SendMessage("Threshold for plant 1: ");
// 		char thresholdStr[10];
// 		sprintf(thresholdStr, "%d", (int)plant1.GetThreshold());
// 		btInterface.SendMessage(thresholdStr);
// 		btInterface.SendMessage("\r\n");
// 		btInterface.SendMessage("\r\n");
		
		

		// Repeat for plant2
		plant2.UpdateSensor();
		
		// Convert humidity for plant2 to string
		sprintf(humidityStr, "%d", (int)plant2.GetHumidity());
		
		// Send humidity value via UART
		btInterface.SendMessage("Humidity for plant 2: ");
		btInterface.SendMessage(humidityStr);  // Send the string
		btInterface.SendMessage("\r\n");
		
// 		// Send threshold value for plant2 via UART
// 		btInterface.SendMessage("Threshold for plant 2: ");
// 		sprintf(thresholdStr, "%d", (int)plant2.GetThreshold());
// 		btInterface.SendMessage(thresholdStr);
// 		btInterface.SendMessage("\r\n");
// 		btInterface.SendMessage("\r\n");
// 		
		_delay_ms(4000);

	}

	return 0;
}
