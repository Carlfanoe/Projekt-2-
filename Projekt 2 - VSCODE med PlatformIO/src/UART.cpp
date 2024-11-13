#include "UART.h"
#include <stdlib.h>  // Inkluderer stdlib.h for itoa funktion

// Initialiserer UART ved hjælp af den angivne UBRR værdi
void UART::init(uint16_t ubrr) {
	UBRR0H = (ubrr >> 8);      // Sætter den høje byte af UBRR
	UBRR0L = ubrr;             // Sætter den lave byte af UBRR
	UCSR0B = (1 << TXEN0);     // Aktiverer transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Sætter 8 data bits og 1 stop bit
}

void UART::transmit(char data) {
	while (!(UCSR0A & (1 << UDRE0)));  // Venter på, at transmit-bufferen er klar
	UDR0 = data;                       // Skriver data til transmit-bufferen
}

void UART::print(const char* str) {
	while (*str) {
		transmit(*str++);
	}
}

void UART::printNumber(uint8_t number) {
	char buffer[4];
	itoa(number, buffer, 10);  // Konverterer tallet til tekst (decimal-basis)
	print(buffer);             // Sender tallet som tekst
}
