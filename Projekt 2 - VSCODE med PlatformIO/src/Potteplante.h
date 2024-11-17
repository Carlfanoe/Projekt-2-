#include "Jordfugtighedsensor.h"


class Potteplante{
	private:
	int id;
	uint8_t humiditySensorPin;
	int humidityTreshold;
	int wateringDuration;
	double HumidityPercent;
	
	
	Jordfugtighedsensor jordfugtighedsensor;
	
	public:
	
	// HumiditySensorPin(0) = ADC0, HumiditySensorPin(1) = ADC1 osv....
Potteplante(int ID, uint8_t HumiditySensorPin, int HumidityThreshold, int WateringDuration);
	void WaterPlant();
	int GetHumidity();
	int GetThreshold();
	void SetThreshold(int NyHumidityTreshold);
	void UpdateSensor();
	
	};