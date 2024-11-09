#include <avr/io.h>
#include "Potteplante.h"
#include "UART.h"

// Define the UART baud rate for 9600 (adjust depending on your system clock)
#define F_CPU 16000000UL  // Assuming a 16MHz clock (adjust if different)
#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

#include <util/delay.h>


UART uart;  // Create an instance of the UART class

int main(void) {
	
	// Test kommentar, slet det her!!!
	
	// Initialize UART
	uart.init(MY_UBRR);

	// Create a Potteplante instance with an ID, Sensor Pin, Humidity Threshold, and Watering Duration
	Potteplante plant1(1, 0, 20, 5); // Brug ADC0 til plant1
	Potteplante plant2(2, 1, 20, 5); // Brug ADC1 til plant2

	// Main loop
	while (1) {
		// Update the sensor (this will call SetHumidity in the sensor class)
		plant1.UpdateSensor();
		// Send humidity value via UART
		uart.print("Humidity for plant 1: ");
		uart.printNumber(plant1.GetHumidity());
		uart.print("\r\n");
		// Send threshold value via UART
		uart.print("Threshold for plant 1: ");
		uart.printNumber(plant1.GetThreshold());
		uart.print("\r\n");
		uart.print("\r\n");
		
		_delay_ms(500);

		plant2.UpdateSensor();
		// Send humidity value via UART
		uart.print("Humidity for plant 2: ");
		uart.printNumber(plant2.GetHumidity());
		uart.print("\r\n");
		// Send threshold value via UART
		uart.print("Threshold for plant 2: ");
		uart.printNumber(plant2.GetThreshold());
		uart.print("\r\n");
		uart.print("\r\n");

	
		// Delay 1 second (1000 milliseconds)
		_delay_ms(10000);
	}

	return 0;
}
