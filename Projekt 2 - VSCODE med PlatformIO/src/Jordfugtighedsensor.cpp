#include "Jordfugtighedsensor.h"
#include <Arduino.h>

Jordfugtighedsensor::Jordfugtighedsensor(uint8_t MoistPin, uint8_t supplyPin)
  : moistPin(MoistPin), supplyPin_(supplyPin)
{
}

// returnere fugtigheds som en procent
int Jordfugtighedsensor::GetHumidity(){
  Serial.println(moistPin);
  Serial.println(supplyPin_);
  digitalWrite(supplyPin_, HIGH);
  double avrgPercent = 0.0;
  for (int i = 0; i < 3 ; i = i + 1) 
    {
      moistVal = analogRead(moistPin);
      double percent = ((moistVal-moistValMin) * 100)/(moistValMax-moistValMin);
      percentArray[i] = percent;
      delay(500);
    };
	
	for (int i = 0; i < 3; i++)
    {
      avrgPercent = avrgPercent + percentArray[i];   //Alle 3 samples af moistval i procent
    }
    avrgPercent = avrgPercent / 3;
  digitalWrite(supplyPin_, LOW);
  delay(1000); // for stability

  Serial.println(avrgPercent);

return static_cast <int> (avrgPercent); // returnere en int, så der fjernes nogle nuller
    
}
