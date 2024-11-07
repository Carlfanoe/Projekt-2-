#pragma once
#include <avr/io.h>
#include <stdint.h>  // For faste datatyper som uint16_t

class UART {
	public:
	void init(uint16_t ubrr);        // Initialiserer UART med UBRR som parameter
	void transmit(char data);        // Sender ét tegn
	void print(const char* str);     // Sender en streng
	void printNumber(uint8_t number); // Sender et tal
};
