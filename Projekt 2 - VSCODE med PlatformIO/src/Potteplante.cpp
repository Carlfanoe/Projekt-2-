#include "Potteplante.h"


	
Potteplante::Potteplante(int ID, uint8_t HumiditySensorPin, int HumidityThreshold, int WateringDuration)
: id(ID),
humiditySensorPin(HumiditySensorPin),
humidityTreshold(HumidityThreshold),
wateringDuration(WateringDuration),
jordfugtighedsensor(HumiditySensorPin)  // Pass the pin here
{}

	
void Potteplante::WaterPlant(){
	// vandpumpe.PumpWater();
}

int Potteplante::GetHumidity(){
	return jordfugtighedsensor.GetHumidity();
}


int Potteplante::GetThreshold(){
	return humidityTreshold;
}

void Potteplante::SetThreshold(int NyHumidityTreshold){
	humidityTreshold = NyHumidityTreshold;
}

void Potteplante::UpdateSensor(){
	jordfugtighedsensor.SetHumidity();
}
 
