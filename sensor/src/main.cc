/* This file contains the entry point for the OrientationFilter application */

#include "interfaces\imu.h"
#include "interfaces\measurement.h"
#include "classes\i2chandlers\default_handler_factory.h"
#include "classes\alt_imu.h"

#include "wiringPi/headers/wiringPiI2C.h"

#include <iostream>
#include <vector>

class I2CHandlerFactory;

void PrintMeasurements(const std::vector<const Measurement*>& measurementBatch);
void DeleteMeasurements(const std::vector<const Measurement*>& measurementBatch);

int main(int argc, char* argv[])
{
	/* Create factory and IMU */
	I2CHandlerFactory* factory{new DefaultHandlerFactory{}};
	IMU* imu{new AltIMU{factory}};

	std::vector<const Measurement*> measurementBatch{imu->GetNextMeasurementBatch()};
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

void PrintMeasurements(const std::vector<const Measurement*>& measurementBatch)
{
	for (const auto measurement : measurementBatch)
	{
		std::cout << measurement->ToString() << std::endl;
	}
}

void DeleteMeasurements(const std::vector<const Measurement*>& measurementBatch)
{
	for (auto measurement : measurementBatch)
	{
		delete measurement;
		measurement = nullptr;
	}
}
