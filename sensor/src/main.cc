/* This file contains the entry point for the OrientationFilter application */

#include "interfaces\imu.h"
#include "interfaces\i2c_handler_factory.h"
#include "interfaces\measurement.h"

#include "classes\i2chandlers\default_handler_factory.h"
#include "classes\alt_imu.h"

#include "wiringPi/headers/wiringPiI2C.h"

#include <iostream>

void PrintMeasurements(const std::vector<const Measurement*>& measurementBatch)
{
	std::vector<const Measurement*>::const_iterator iter;
	for (iter = measurementBatch.cbegin(); iter != measurementBatch.cend(); ++iter)
	{
		const Measurement *const measurement = *iter;
		std::cout << measurement->ToString() << std::endl;
	}
}

void DeleteMeasurements(const std::vector<const Measurement*>& measurementBatch)
{
	std::vector<const Measurement*>::const_iterator iter;
	for (iter = measurementBatch.cbegin(); iter != measurementBatch.cend(); ++iter)
	{
		const Measurement* measurement = *iter;
		delete measurement;
		measurement = NULL;
	}
}

int main(int argc, char* argv[])
{
	/* Create factory and IMU */
	I2CHandlerFactory* factory = new DefaultHandlerFactory;
	IMU* imu = new AltIMU(factory);

	std::vector<const Measurement*> measurementBatch = imu->GetNextMeasurementBatch();
	PrintMeasurements(measurementBatch);

	/* Cleanup allocated memory */
	DeleteMeasurements(measurementBatch);
	delete factory;
	delete imu;

	wiringPiI2CSetup(0);

	/* Do not close console immediately */
	std::cout << "Press any key to exit the application." << std::endl;
	std::cin.get();

	return 0;
}
