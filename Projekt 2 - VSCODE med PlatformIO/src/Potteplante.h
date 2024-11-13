#include "Jordfugtighedsensor.h"

class Potteplante{
	private:
	int id;
	int humiditySensorPin;
	int humidityTreshold;
	int wateringDuration;
	double HumidityPercent;
	
	
	Jordfugtighedsensor jordfugtighedsensor;
	
	public:
	
	// HumiditySensorPin(0) = ADC0, HumiditySensorPin(1) = ADC1 osv....
Potteplante(int ID, int HumiditySensorPin, int HumidityThreshold, int WateringDuration);
	void WaterPlant();
	int GetHumidity();
	int GetThreshold();
	void SetThreshold(int NyHumidityTreshold);
	void UpdateSensor();
	
	};