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
	// Initialize UART
	uart.init(MY_UBRR);

	// Create a Potteplante instance with an ID, Sensor Pin, Humidity Threshold, and Watering Duration
	Potteplante plant(1, 0, 60, 10);  // Example values

	

	// Main loop
	while (1) {
		// Update the sensor (this will call SetHumidity in the sensor class)
		plant.UpdateSensor();

		// Send humidity value via UART
		uart.print("Humidity: ");
		uart.printNumber(plant.GetHumidity());
		uart.print("\r\n");

		// Send threshold value via UART
		uart.print("Threshold: ");
		uart.printNumber(plant.GetThreshold());
		uart.print("\r\n");

		// Set a new threshold and print it
		plant.SetThreshold(50);
		uart.print("New Threshold: ");
		uart.printNumber(plant.GetThreshold());
		uart.print("\r\n");

		// Delay 1 second (1000 milliseconds)
		_delay_ms(1000);
	}

	return 0;
}
