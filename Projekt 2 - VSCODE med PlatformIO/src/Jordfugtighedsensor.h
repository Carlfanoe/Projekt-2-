#pragma once
#include <Arduino.h>


class Jordfugtighedsensor{
private:
	int humidity_ = 0;
	// Ikke med i klassediagram, fordi det har v�ret umuligt at forudsige:
	uint8_t pin_;  // ADC0 PIN p� arduino: Vi SKAL finde p� en l�sning her, fordi lige nu er adcPin den samme for hvert object af plante, hvilket den ikke m� v�re.
	
public:
	Jordfugtighedsensor(uint8_t pin); // kalder automatisk ADC_init
 	
	int GetHumidity();
	void SetHumidity(); // Opdaterer attributten humidity
	
	double ADC_readAsPercentage();  // Retunere Humidity som procent
};