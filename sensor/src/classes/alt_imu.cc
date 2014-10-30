/*
* This file defines the AltIMU class which models the specific IMU used in
* the project. It uses an I2CHandler factory to initialize its I2CHandlers.
*/

#include "alt_imu.h"
#include "../interfaces/i2c_handler_factory.h"
#include "../interfaces/i2chandler.h"
#include <vector>

AltIMU::AltIMU(const I2CHandlerFactory *const handlerFactory)
{
	accAndMagHandler = handlerFactory->MakeAccAndMagHandler();
	gyroscopeHandler = handlerFactory->MakeGyroscopeHandler();
	barometerHandler = handlerFactory->MakeBarometerHandler();
}

AltIMU::~AltIMU()
{
	delete accAndMagHandler;
	delete gyroscopeHandler;
	delete barometerHandler;
}

std::vector<const Measurement*> AltIMU::GetNextMeasurementBatch() const
{
	std::vector<const Measurement*> measurementBatch{};

	/* For testing purposes only */
	measurementBatch.push_back(accAndMagHandler->GetNextMeasurement());
	measurementBatch.push_back(accAndMagHandler->GetNextMeasurement());
	measurementBatch.push_back(gyroscopeHandler->GetNextMeasurement());
	measurementBatch.push_back(barometerHandler->GetNextMeasurement());
	measurementBatch.push_back(barometerHandler->GetNextMeasurement());

	return measurementBatch;
}

void AltIMU::GetAllAvailableMeasurementsFromHandler(std::vector<const Measurement*>& measurementBatch,
													const I2CHandler *const handler) const
{
	while (handler->HasAvailableMeasurements())
	{
		measurementBatch.push_back(handler->GetNextMeasurement());
	}
}
