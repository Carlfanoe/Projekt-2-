#include <avr/io.h>

// Define the UART baud rate for 9600 (adjust depending on your system clock)
#define F_CPU 16000000UL  // Assuming a 16MHz clock (adjust if different)
#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

class brugergraenseflade {
	private:
	uint32_t baudrate_;  // Baudrate attribute

	
	public:
	// Send a single character via UART1
	void sendChar(char c);

	// Receive a single character from UART1
	char receiveChar();

	
	// Constructor: Initialize with a given baudrate
	brugergraenseflade(uint32_t baudrate);

	// Initialize or reinitialize UART1
	void initUART();

	// Check if a message is ready to be read
	bool IsMessageReady();

	// Read a message from Bluetooth as a C-style string
	void ReadMessage(char* message, uint8_t maxLength);

	// Send a message via Bluetooth (C-style string)
	void SendMessage(const char* message);
};
