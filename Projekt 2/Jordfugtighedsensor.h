#pragma once 
#include <avr/io.h> // giver os alle registre så som DDRB


class Jordfugtighedsensor{
private:
	int humidity;
	int threshold;
	
	// Ikke med i klassediagram, fordi det har været umuligt at forudsige:
	int adcPin = 0;  // ADC0 PIN på arduino: Vi SKAL finde på en løsning her, fordi lige nu er adcPin den samme for hvert object af plante, hvilket den ikke må være.
	
public:
	Jordfugtighedsensor(int NytThreshold, int pin);
 	
	int GetHumidity();
	int GetThreshold();
	void SetThreshold(int NytTreshold);
	void SetHumidity(); // Anderledes fra klassediagram, tror klassediagram har en lille fejl her 
	
	// Ikke med i klassediagram, fordi det har været umuligt at forudsige:
	void ADC_init();
	double ADC_readAsPercentage();  // Retunere Humidity som procent
};