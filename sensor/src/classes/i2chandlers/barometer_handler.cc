/*
* This file defines the BarometerHandler class which handles
* I2C-communication with the barometer on the IMU-chip.
*/

#include "barometer_handler.h"
#include "../measurements.h"

class Measurement;

BarometerHandler::BarometerHandler()
{
	/* Not implemented yet */
}

BarometerHandler::~BarometerHandler()
{
	/* Not implemented yet */
}

Measurement* BarometerHandler::GetNextMeasurement() const
{
	/* For testing purposes only */
	static bool returnPressure = true;
	if (returnPressure)
	{
		returnPressure = false;
		return new PressureMeasurement(1.f);
	}
	else
	{
		returnPressure = true;
		return new TemperatureMeasurement(1.f);
	}
}

bool BarometerHandler::HasAvailableMeasurements() const
{
	/* For testing purposes only */
	return true;
}
