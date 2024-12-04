#include "Jordfugtighedsensor.h"
#include <Arduino.h>

Jordfugtighedsensor::Jordfugtighedsensor(int MoistPin){
    moistPin = MoistPin;
}

// returnere fugtigheds som en procent
int Jordfugtighedsensor::GetHumidity(){

  digitalWrite(8,HIGH);
  int avrgPercent = 0;
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
  digitalWrite(8,LOW);
  delay(1000); // for stability

return avrgPercent; // returnere en int, så der fjernes nogle nuller
    
}
