#include "VandPumpe.h"
#include <util/delay.h>

VandPumpe::VandPumpe(uint8_t pin)
: pin_(pin) {
	// Konfigurer den specificerede pin som output
	if (pin_ == 8) {
		DDRH |= (1 << PH5);  // Sæt PH5 (Pin 8) som output
		} else if (pin_ == 9) {
		DDRH |= (1 << PH6);  // Sæt PH6 (Pin 9) som output
		} else if (pin_ == 10) {
		DDRH |= (1 << PH7);  // Sæt PH7 (Pin 10) som output
	}
}

void VandPumpe::Start() {
	// Aktiver pumpen ved at sætte pin høj
	if (pin_ == 8) {
		PORTH |= (1 << PH5);
		} else if (pin_ == 9) {
		PORTH |= (1 << PH6);
		} else if (pin_ == 10) {
		PORTH |= (1 << PH7);
	}
}

void VandPumpe::Stop() {
	if (pin_ == 8) {
		PORTB &= ~(1 << PB4); // Try clearing both PORT and DDR
		DDRH &= ~(1 << PH5);  // Set PH5 as output low
		} else if (pin_ == 9) {
		PORTB &= ~(1 << PB5);
		DDRH &= ~(1 << PH6);
		} else if (pin_ == 10) {
		PORTB &= ~(1 << PB6);
		DDRH &= ~(1 << PH7);
	}
}

