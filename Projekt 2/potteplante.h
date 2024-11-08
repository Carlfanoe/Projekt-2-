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
	Potteplante(int ID, int HumiditySensorPin, int NyHumidityTreshold, int WateringDuration);
	
	void WaterPlant();
	int GetHumidity();
	int GetThreshold();
	void SetThreshold(int NyHumidityTreshold);
	void UpdateSensor();
	
	};