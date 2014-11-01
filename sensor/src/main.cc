/* This file contains the entry point for the OrientationFilter application */

#include "interfaces\imu.h"
#include "interfaces\measurement.h"
#include "classes\i2chandlers\default_handler_factory.h"
#include "classes\alt_imu.h"

#include "classes/Logger.h"

#include <iostream>
#include <vector>
#include <memory>

void PrintMeasurements(const std::vector<std::unique_ptr<Measurement>>& measurementBatch);

int main(int argc, char* argv[])
{
	Logger::Log(LogLevel::Info) << "SensorApp initialized";

	/* Create factory and IMU */
	std::unique_ptr<I2CHandlerFactory> factory{new DefaultHandlerFactory{}};
	std::unique_ptr<IMU> imu{new AltIMU{factory}};

	std::vector<std::unique_ptr<Measurement>> measurementBatch{imu->GetNextMeasurementBatch()};
	PrintMeasurements(measurementBatch);

	/* Do not close console immediately */
	std::cout << "Press any key to exit the application." << std::endl;
	std::cin.get();

	return 0;
}

void PrintMeasurements(const std::vector<std::unique_ptr<Measurement>>& measurementBatch)
{
	for (const auto& measurement : measurementBatch)
	{
		Logger::Log(LogLevel::Debug, measurement->ToString());
	}
}
