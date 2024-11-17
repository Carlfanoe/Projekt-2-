#include "Jordfugtighedsensor.h"

Jordfugtighedsensor::Jordfugtighedsensor(uint8_t pin)
: humidity_(0), pin_(pin) {
}
	
int Jordfugtighedsensor::GetHumidity(){
	return humidity_;
}

void Jordfugtighedsensor::SetHumidity(){ // Anderledes fra klassediagram, tror klassediagram har en lille fejl her
	humidity_ = ADC_readAsPercentage();
}


	
double Jordfugtighedsensor::ADC_readAsPercentage(){  // Retunere Humidity som procent
  // Læs værdien fra den angivne analog pin (adcPin skal være en analog pin som f.eks. A0)
    int rawValue = analogRead(pin_); 

    // Omregn værdien til procent. Her antages det, at 300 svarer til 0% og 1023 til 100%.
    double moisturePercentage = ((1023 - rawValue) * 100.0) / (1023 - 300); 
    
    // Returnér fugtighedsprocenten
    return moisturePercentage;
}