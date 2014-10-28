/*
* This file defines the GyroscopeHandler class which handles
* I2C-communication with the gyroscope on the IMU-chip.
*/

#include "gyroscope_handler.h"
#include "../measurements.h"

class Measurement;

GyroscopeHandler::GyroscopeHandler()
{
	/* Not implemented yet */
}

GyroscopeHandler::~GyroscopeHandler()
{
	/* Not implemented yet */
}

const Measurement* GyroscopeHandler::GetNextMeasurement() const
{
	/* For testing purposes only */
	return new GyroscopeMeasurement(1.f, 2.f, 3.f);
}

bool GyroscopeHandler::HasAvailableMeasurements() const
{
	/* For testing purposes only */
	return true;
}
