#include "plante.h"


plante::plante(uint8_t adcChoice, uint8_t pumpChoice, uint8_t threshold, uint8_t wateringDuration)
: sensor_(adcChoice),
pump_(pumpChoice),
humidityThreshold_(threshold),
wateringDuration_(wateringDuration) {
	sensor_.ADC_init();
}

uint8_t plante::ReadHumidity() {
	return sensor_.ADC_readAsPercentage();
}

void plante::WaterAutomatically() {
	pump_.Start();  // Start pumpen

	for (uint8_t i = 0; i < wateringDuration_; i++) {
		_delay_ms(1000);  // Delay i sekunder, baseret på varighed
	}
	pump_.Stop();  // Stop pumpen efter varighed
}

uint8_t plante::GetHumidityThreshold() {
	return humidityThreshold_;
}

uint8_t plante::GetWateringDuration() {
	return wateringDuration_;
}
