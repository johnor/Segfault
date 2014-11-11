/*
* This file defines the GyroscopeHandler class which handles
* I2C-communication with the gyroscope on the IMU-chip.
*/

#include "gyroscope_handler.h"
#include "../measurements.h"

MeasurementBatch GyroscopeHandler::GetMeasurements() const
{
	MeasurementBatch measurements;
	measurements.push_back(MeasurementPtr{ new GyroscopeMeasurement{ 0, 1.f, 2.f, 3.f } });

	return measurements;
}

bool GyroscopeHandler::HasAvailableMeasurements() const
{
	/* For testing purposes only */
	return true;
}
