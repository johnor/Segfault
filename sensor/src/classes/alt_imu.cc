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

    if (accAndMagHandler)
    {
        MeasurementBatch accMeasurements = accAndMagHandler->GetMeasurements();
        std::move(accMeasurements.begin(), accMeasurements.end(), std::inserter(measurementBatch, measurementBatch.end()));
    }

    if (gyroscopeHandler)
    {
        MeasurementBatch gyroMeasurements = gyroscopeHandler->GetMeasurements();
        std::move(gyroMeasurements.begin(), gyroMeasurements.end(), std::inserter(measurementBatch, measurementBatch.end()));
    }

    if (barometerHandler)
    {
        MeasurementBatch barometerMeasurements = barometerHandler->GetMeasurements();
        std::move(barometerMeasurements.begin(), barometerMeasurements.end(), std::inserter(measurementBatch, measurementBatch.end()));
    }

    return measurementBatch;
}

void AltIMU::GetAllAvailableMeasurementsFromHandler(MeasurementBatch& measurementBatch,
                                                    const SensorHandlerPtr& handler) const
{
}
