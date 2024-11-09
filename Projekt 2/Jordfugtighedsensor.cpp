#include "Jordfugtighedsensor.h"

Jordfugtighedsensor::Jordfugtighedsensor(int pin)
: humidity(0), adcPin(pin) {
	ADC_init(); // Call ADC_init() here
}
	
int Jordfugtighedsensor::GetHumidity(){
	return humidity;
}

void Jordfugtighedsensor::SetHumidity(){ // Anderledes fra klassediagram, tror klassediagram har en lille fejl her
	humidity = ADC_readAsPercentage();
}


void Jordfugtighedsensor::ADC_init() {
	ADMUX = (1 << REFS0);  // Sætter reference til AVcc (5V)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Aktiverer ADC og sætter prescaler
}
	
double Jordfugtighedsensor::ADC_readAsPercentage(){  // Retunere Humidity som procent
	
	ADMUX = (ADMUX & 0xF0) | (adcPin & 0x0F);
	ADCSRA |= (1 << ADSC); // Starter konvertering
	while (ADCSRA & (1 << ADSC));  // Venter på, at konvertering er færdig
	
	double moisturePercentage = ((1023 - ADC) * 100) / (1023 - 300); // ADC registeret indeholder værdien for det digitale signal 
return moisturePercentage;
}