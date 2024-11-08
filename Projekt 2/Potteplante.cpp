#include "Potteplante.h"


	
Potteplante::Potteplante(int ID, int HumiditySensorPin, int HumidityTreshold, int WateringDuration)
: id(ID),
humiditySensorPin(HumiditySensorPin),
humidityTreshold(HumidityTreshold),
wateringDuration(WateringDuration),
jordfugtighedsensor(HumidityTreshold) // Initialiser Jordfugtighedsensor her
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
