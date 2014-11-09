/* This file contains the entry point for the OrientationFilter application */

#include "headers/smart_pointer_typedefs.h"

#include "interfaces/imu.h"
#include "interfaces/measurement.h"
#include "classes/sensorhandlers/default_handler_factory.h"
#include "classes/sensorhandlers/log_reader_handler_factory.h"
#include "classes/alt_imu.h"
#include "classes/logger.h"

#include <iostream>

void PrintMeasurements(const MeasurementBatch& measurementBatch);

int main(int argc, char* argv[])
{
	Logger::Log(LogLevel::Info) << "SensorApp initialized";

	/* Create factory and IMU */
#ifdef _MSC_VER
	SensorHandlerFactoryPtr factory{ new LogReaderHandlerFactory{} };
#else
    SensorHandlerFactoryPtr factory{ new DefaultHandlerFactory{} };
#endif
	IMUPtr imu{new AltIMU{factory}};

	MeasurementBatch measurementBatch{imu->GetNextMeasurementBatch()};
	PrintMeasurements(measurementBatch);

	/* Do not close console immediately */
	std::cout << "Press any key to exit the application." << std::endl;
	std::cin.get();

	return 0;
}

void PrintMeasurements(const MeasurementBatch& measurementBatch)
{
	for (const auto& measurement : measurementBatch)
	{
		Logger::Log(LogLevel::Debug, measurement->ToString());
	}
}
