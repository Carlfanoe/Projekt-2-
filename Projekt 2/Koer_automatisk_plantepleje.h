#pragma once
#include <vector>
#include <string>
class Koer_automatisk_plantepleje{
	
private:
	bool plantCareRunning_;
	std::vector<Potteplante> plants_;
	// Brugergraenseflade brugergraenseflade;
	// Skaerm display_;
	// Vandbeholder WaterContainer;
	
public:
	void ToggleAutomaticPlantCare();
	bool VerifyHumidity();
	void CreateDataMessage();
	void AlertLowWaterLevel();
	void UpdateTimer();
	
	};