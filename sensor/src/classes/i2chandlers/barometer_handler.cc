/*
* This file defines the BarometerHandler class which handles
* I2C-communication with the barometer on the IMU-chip.
*/

#include "barometer_handler.h"
#include "../measurements.h"

MeasurementPtr BarometerHandler::GetNextMeasurement() const
{
	/* For testing purposes only */
	static bool returnPressure{true};
	if (returnPressure)
	{
		returnPressure = false;
		return MeasurementPtr{new PressureMeasurement{1.f}};
	}
	else
	{
		returnPressure = true;
		return MeasurementPtr{new TemperatureMeasurement{1.f}};
	}
}

bool BarometerHandler::HasAvailableMeasurements() const
{
	/* For testing purposes only */
	return true;
}

void BarometerHandler::Update()
{
}
