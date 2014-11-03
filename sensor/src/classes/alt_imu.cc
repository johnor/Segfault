/*
* This file defines the AltIMU class which models the specific IMU used in
* the project. It uses an I2CHandler factory to initialize its I2CHandlers.
*/

#include <stdexcept>
#include "alt_imu.h"
#include "classes/logger.h"
#include "../interfaces/sensor_handler_factory.h"
#include "../interfaces/measurement.h"

AltIMU::AltIMU(const SensorHandlerFactoryPtr& handlerFactory)
{
	try
	{
		accAndMagHandler = handlerFactory->MakeAccAndMagHandler();
	}
	catch (std::runtime_error &e)
	{
		Logger::Log(LogLevel::Error) << "Exception in AltIMU::AltIMU: " << e.what();
	}
	gyroscopeHandler = handlerFactory->MakeGyroscopeHandler();
	barometerHandler = handlerFactory->MakeBarometerHandler();
}

MeasurementBatch AltIMU::GetNextMeasurementBatch() const
{
	MeasurementBatch measurementBatch{};

	/* For testing purposes only */
	if (accAndMagHandler)
	{
		measurementBatch.push_back(accAndMagHandler->GetNextMeasurement());
		measurementBatch.push_back(accAndMagHandler->GetNextMeasurement());
		accAndMagHandler->Update();
	}
	
	measurementBatch.push_back(gyroscopeHandler->GetNextMeasurement());
	measurementBatch.push_back(barometerHandler->GetNextMeasurement());
	measurementBatch.push_back(barometerHandler->GetNextMeasurement());

	return measurementBatch;
}

void AltIMU::GetAllAvailableMeasurementsFromHandler(MeasurementBatch& measurementBatch,
	                                                const SensorHandlerPtr& handler) const
{
	while (handler->HasAvailableMeasurements())
	{
		measurementBatch.push_back(handler->GetNextMeasurement());
	}
}
