#pragma once
#include "UART.h"
#include "Plante.h"

class AutomatiskPlanteplejesystem {
	private:
	UART uart_;                  // UART object for serial communication

	public:
	AutomatiskPlanteplejesystem();         // Constructor to initialize the system
	void InitializeComponents();           // Initializes ADC, UART, and other components
	void StartAutomaticPlantCare();        // Starts checking moisture and watering if needed
	void StopAutomaticPlantCare();         // Stops automatic watering

	private:
	void CheckAndWaterPlants();            // Checks each plant's moisture and waters if necessary
};
