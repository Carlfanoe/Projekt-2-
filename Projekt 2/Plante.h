#pragma once
#include <stdint.h>
#include "Jordfugtighedsensor.h"
#include "VandPumpe.h"
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

class plante {
	private:
	Jordfugtighedsensor sensor_;    // Hver plante har sin egen fugtighedssensor
	VandPumpe pump_;                // Hver plante har sin egen pumpe
	uint8_t humidityThreshold_;     // Fugtighedstærskel for planten
	uint8_t wateringDuration_;      // Vandingsvarighed i sekunder
	uint8_t adcPin_;                // ADC pin til fugtighedssensoren

	public:
	// Constructor initialiserer alle nødvendige parametre
	plante(uint8_t adcPin, uint8_t pumpPin, uint8_t threshold, uint8_t wateringDuration);

	void WaterAutomatically();         // Vand planten automatisk baseret på tærskelværdi
	uint8_t ReadHumidity();            // Læs det aktuelle fugtighedsniveau som en procentdel
	uint8_t GetHumidityThreshold();    // Få fugtighedstærskel
	uint8_t GetWateringDuration();     // Få vandingsvarighed
};
