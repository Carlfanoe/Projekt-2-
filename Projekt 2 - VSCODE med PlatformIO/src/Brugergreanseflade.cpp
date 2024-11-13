#include "Brugergreanseflade.h"

// Constructor: Initialize with a given baudrate
brugergraenseflade::brugergraenseflade(uint32_t baudrate) : baudrate_(baudrate) {
	initUART();  // Initialize UART
}

// Initialize or reinitialize UART1
void brugergraenseflade::initUART() {
	uint16_t ubrr = F_CPU / 16 / baudrate_ - 1;

	UBRR1H = (ubrr >> 8);  // Set the upper 8 bits of the baudrate
	UBRR1L = ubrr;         // Set the lower 8 bits of the baudrate

	UCSR1B = (1 << TXEN1) | (1 << RXEN1);  // Enable TX and RX
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);  // Set data format to 8N1
}

// Check if a message is ready to be read
bool brugergraenseflade::IsMessageReady() {
	return (UCSR1A & (1 << RXC1));  // Check if there is data in the RX buffer
}

// Read a message from Bluetooth as a C-style string
void brugergraenseflade::ReadMessage(char* message, uint8_t maxLength) {
	uint8_t index = 0;
	while (IsMessageReady() && index < maxLength - 1) {
		char received = receiveChar();  // Receive one character at a time
		if (received == '\n' || received == '\r') {
			break;  // Stop reading at a newline or carriage return
		}
		message[index++] = received;  // Store the character
	}
	message[index] = '\0';  // Null-terminate the string
}

// Send a message via Bluetooth (C-style string)
void brugergraenseflade::SendMessage(const char* message) {
	while (*message) {           // Loop through each character of the string
		sendChar(*message++);    // Transmit each character and move to the next
	}
	sendChar('\n');  // End with a newline character
}

// Send a single character via UART1
void brugergraenseflade::sendChar(char c) {
	while (!(UCSR1A & (1 << UDRE1)));  // Wait for the transmit buffer to be empty
	UDR1 = c;  // Send the character
}

// Receive a single character from UART1
char brugergraenseflade::receiveChar() {
	while (!(UCSR1A & (1 << RXC1)));  // Wait for data to be received
	return UDR1;  // Return the received character
}