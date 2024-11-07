#include "AutomatiskPlanteplejesystem.h"
#include <avr/io.h>
#include <util/delay.h>

AutomatiskPlanteplejesystem::AutomatiskPlanteplejesystem() {
	// Initialize components required by the system (UART, ADC, etc.)
	InitializeComponents();
}

void AutomatiskPlanteplejesystem::InitializeComponents() {
	uart_.init(MYUBRR); // Initialize UART for serial communication

	// Initialize other components, like ADC (this may be done within plant sensors)
	// For example: Initialize ADC and other needed peripherals
}

void AutomatiskPlanteplejesystem::StartAutomaticPlantCare() {
	// Infinite loop to keep checking and watering as needed
	while (1) {
		CheckAndWaterPlants();
		_delay_ms(10000); // Wait 10 seconds between checks
	}
}

void AutomatiskPlanteplejesystem::StopAutomaticPlantCare() {
	// Stop any ongoing watering by iterating through plants and calling Stop on each pump
	for (Plante& plant : plants_) {
		plant.WaterPlant(0); // This should ensure any ongoing watering stops
	}
}

void AutomatiskPlanteplejesystem::CheckAndWaterPlants() {
	for (Plante& plant : plants_) {
		uint8_t humidity = plant.ReadHumidity();

		uart_.print("Current Humidity: ");
		uart_.printNumber(humidity);
		uart_.print("%\n");

		if (humidity < plant.GetHumidityThreshold()) {
			uart_.print("Humidity below threshold! Starting watering...\n");
			plant.WaterPlant(plant.GetWateringDuration());
			uart_.print("Watering complete.\n");
			} else {
			uart_.print("Humidity is above threshold. No watering needed.\n");
		}
	}
}
