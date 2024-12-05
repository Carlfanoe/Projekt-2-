#include "Jordfugtighedsensor.h"

Jordfugtighedsensor::Jordfugtighedsensor(int pin) : pin_(pin) {}

// Returnerer fugtighed som procent mellem 0 til 100
int Jordfugtighedsensor::GetHumidity(){
  int humidity_raw = analogRead(pin_);
  float humidity_percent = (static_cast<float>(humidity_raw)/1023.0) * 100;
  return constrain(humidity_percent, 0, 100);
}