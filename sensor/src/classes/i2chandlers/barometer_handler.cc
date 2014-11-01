/*
* This file defines the BarometerHandler class which handles
* I2C-communication with the barometer on the IMU-chip.
*/

#include "barometer_handler.h"
#include "../measurements.h"

std::unique_ptr<Measurement> BarometerHandler::GetNextMeasurement() const
{
	/* For testing purposes only */
	static bool returnPressure{true};
	if (returnPressure)
	{
		returnPressure = false;
		return std::unique_ptr<Measurement>{new PressureMeasurement{1.f}};
	}
	else
	{
		returnPressure = true;
		return std::unique_ptr<Measurement>{new TemperatureMeasurement{1.f}};
	}
}

bool BarometerHandler::HasAvailableMeasurements() const
{
	/* For testing purposes only */
	return true;
}
