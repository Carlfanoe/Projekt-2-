#pragma once
#include <avr/io.h>
#include <stdint.h>

class VandPumpe {
	private:
	uint8_t pin_;           // Pin nummer til at styre pumpen

	public:
	VandPumpe(uint8_t pin);  // Constructor til at initialisere pumpens pin
	void Start();            // Metode til at starte pumpen
	void Stop();             // Metode til at stoppe pumpen
};
