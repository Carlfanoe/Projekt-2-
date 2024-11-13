#pragma once
#include <Arduino.h>
#include <avr/io.h> // giver os alle registre s� som DDRB
//poppyhead

class Jordfugtighedsensor{
private:
	int humidity;
	
	// Ikke med i klassediagram, fordi det har v�ret umuligt at forudsige:
	int adcPin = 0;  // ADC0 PIN p� arduino: Vi SKAL finde p� en l�sning her, fordi lige nu er adcPin den samme for hvert object af plante, hvilket den ikke m� v�re.
	
public:
	Jordfugtighedsensor(int pin);
 	
	int GetHumidity();
	void SetHumidity(); // Anderledes fra klassediagram, tror klassediagram har en lille fejl her 
	
	// Ikke med i klassediagram, fordi det har v�ret umuligt at forudsige:
	void ADC_init();
	double ADC_readAsPercentage();  // Retunere Humidity som procent
};