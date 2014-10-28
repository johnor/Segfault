/*
* This file defines the AccAndMagHandler class which handles
* I2C-communication with the accelerometer and magnetometer on the IMU-chip.
*/

#include "acc_and_mag_handler.h"
#include "../measurements.h"

class Measurement;

AccAndMagHandler::AccAndMagHandler()
{
	/* Not implemented yet */
}

AccAndMagHandler::~AccAndMagHandler()
{
	/* Not implemented yet */
}

const Measurement* AccAndMagHandler::GetNextMeasurement() const
{
	/* For testing purposes only */
	static bool returnAcc = true;
	if (returnAcc)
	{
		returnAcc = false;
		return new AccelerometerMeasurement(1.f, 2.f, 3.f);
	}
	else
	{
		returnAcc = true;
		return new CompassMeasurement(1.f, 2.f, 3.f);
	}
}

bool AccAndMagHandler::HasAvailableMeasurements() const
{
	/* For testing purposes only */
	return true;
}
