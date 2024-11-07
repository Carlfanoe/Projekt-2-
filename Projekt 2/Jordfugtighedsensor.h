#pragma once
#include <avr/io.h>
#include <stdint.h>

class Jordfugtighedsensor {
	private:
	uint8_t adcChannel_;  // ADC channel for the moisture sensor

	public:
	Jordfugtighedsensor(uint8_t adcChoice);
	void ADC_init();
	uint16_t ADC_readAsPercentage();  // Returns the moisture level as a percentage
};
