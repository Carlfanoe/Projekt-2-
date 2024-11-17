#include "Jordfugtighedsensor.h"

Jordfugtighedsensor::Jordfugtighedsensor(uint8_t pin)
: humidity_(0), pin_(pin) {}

int Jordfugtighedsensor::GetHumidity() {
    return humidity_;
}

void Jordfugtighedsensor::SetHumidity() { // Anderledes fra klassediagram, tror klassediagram har en lille fejl her
    humidity_ = ADC_readAsPercentage();
}

double Jordfugtighedsensor::ADC_readAsPercentage() {  // Retunere Humidity som procent
    int rawValue = analogRead(pin_);
    double moisturePercentage = ((1023 - rawValue) * 100.0) / (1023 - 300); 
    return moisturePercentage;
}
