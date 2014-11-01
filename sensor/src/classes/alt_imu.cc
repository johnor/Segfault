/*
* This file defines the AltIMU class which models the specific IMU used in
* the project. It uses an I2CHandler factory to initialize its I2CHandlers.
*/

#include <stdexcept>
#include "alt_imu.h"
#include "classes/logger.h"

AltIMU::AltIMU(const std::unique_ptr<I2CHandlerFactory>& handlerFactory)
{
	accAndMagHandler = handlerFactory->MakeAccAndMagHandler();
	gyroscopeHandler = handlerFactory->MakeGyroscopeHandler();
	barometerHandler = handlerFactory->MakeBarometerHandler();
}

std::vector<std::unique_ptr<Measurement>> AltIMU::GetNextMeasurementBatch() const
{
	std::vector<std::unique_ptr<Measurement>> measurementBatch{};

	/* For testing purposes only */
	measurementBatch.push_back(accAndMagHandler->GetNextMeasurement());
	measurementBatch.push_back(accAndMagHandler->GetNextMeasurement());
	measurementBatch.push_back(gyroscopeHandler->GetNextMeasurement());
	measurementBatch.push_back(barometerHandler->GetNextMeasurement());
	measurementBatch.push_back(barometerHandler->GetNextMeasurement());

	// For testing
	try
	{
		accAndMagHandler->Update();
	}
	catch (std::runtime_error &e)
	{
		Logger::Log(LogLevel::Error) << "Exception in GetNextMeasurementBatch(): " << e.what();
	}

	return measurementBatch;
}

void AltIMU::GetAllAvailableMeasurementsFromHandler(std::vector<std::unique_ptr<Measurement>>& measurementBatch,
													const std::unique_ptr<I2CHandler>& handler) const
{
	while (handler->HasAvailableMeasurements())
	{
		measurementBatch.push_back(handler->GetNextMeasurement());
	}
}
