#include "Potteplante.h"


	
Potteplante::Potteplante(int ID, int HumiditySensorPin, int HumidityThreshold, int WateringDuration)
: id(ID),
humiditySensorPin(HumiditySensorPin),
humidityTreshold(HumidityThreshold),
wateringDuration(WateringDuration),
jordfugtighedsensor(HumidityThreshold, HumiditySensorPin)  // Pass the pin here
{}

	
void Potteplante::WaterPlant(){
	// vandpumpe.PumpWater();
}

int Potteplante::GetHumidity(){
	return jordfugtighedsensor.GetHumidity();
}


int Potteplante::GetThreshold(){
	return jordfugtighedsensor.GetThreshold();
}

void Potteplante::SetThreshold(int NyHumidityTreshold){
	jordfugtighedsensor.SetThreshold(NyHumidityTreshold);
}

void Potteplante::UpdateSensor(){
	jordfugtighedsensor.SetHumidity();
}
