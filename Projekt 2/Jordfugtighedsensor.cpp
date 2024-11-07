#include "Jordfugtighedsensor.h"

// Foruddefineret ADC-kanalmapping
const uint8_t adcMapping[3] = {0, 1, 2};  // Map valg til ADC kanaler (f.eks. ADC0, ADC1, ADC2)

Jordfugtighedsensor::Jordfugtighedsensor(uint8_t adcChoice)
: adcChannel_(adcMapping[adcChoice - 1]) {}  // Mapping fra valg til faktisk ADC kanal

void Jordfugtighedsensor::ADC_init() {
	ADMUX = (1 << REFS0);  // Sætter reference til AVcc (5V)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Aktiverer ADC og sætter prescaler
}

uint16_t Jordfugtighedsensor::ADC_readAsPercentage() {
	// Vælger ADC-kanal og starter konvertering
	ADMUX = (ADMUX & 0xF0) | (adcChannel_ & 0x0F);
	ADCSRA |= (1 << ADSC); // Starter konvertering
	while (ADCSRA & (1 << ADSC));  // Venter på, at konvertering er færdig

	// Konverterer ADC-værdi til fugtighedsprocent
	uint16_t adcValue = ADC;
	uint16_t moisturePercentage = ((1023 - adcValue) * 100) / (1023 - 300);

	return moisturePercentage;  // Returnerer fugtighedsniveau som procent
}
