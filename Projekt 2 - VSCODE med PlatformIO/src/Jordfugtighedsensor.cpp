#include "Jordfugtighedsensor.h"
#include <Arduino.h>

Jordfugtighedsensor::Jordfugtighedsensor(int MoistPin){
    moistPin = MoistPin;
}

// returnere fugtigheds som en procent
int Jordfugtighedsensor::GetHumidity(){

  moistVal = analogRead(moistPin);
  
  double percent = ((moistVal-moistValMin) * 100.0)/(moistValMax-moistValMin);
  // int percent = 2.718282 * 2.718282 * (.008985 * moistVal + 0.207762); //calculate percent for probes about 1 - 1.5 inches apart
  
  delay(1000); // for stability

return percent; // returnere en int, så der fjernes nogle nuller
    
}
