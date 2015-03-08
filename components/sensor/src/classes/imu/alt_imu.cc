/*
* This file defines the AltIMU class which models the specific IMU used in
* the project. It uses an I2CHandler factory to initialize its I2CHandlers.
*/

#include "interfaces/sensor_handler_factory.h"
#include "interfaces/measurement.h"
#include "common/src/logger.h"

#include "alt_imu.h"

AltIMU::AltIMU(const SensorHandlerFactoryPtr& handlerFactory)
{
    accAndMagHandler = handlerFactory->MakeAccAndMagHandler();
    gyroscopeHandler = handlerFactory->MakeGyroscopeHandler();
    barometerHandler = handlerFactory->MakeBarometerHandler();
}

MeasurementBatch AltIMU::GetNextMeasurementBatch() const
{
    MeasurementBatch measurementBatch;

    if (accAndMagHandler != nullptr)
    {
        MeasurementBatch accMeasurements{accAndMagHandler->GetMeasurements()};
        std::move(accMeasurements.begin(), accMeasurements.end(), std::inserter(measurementBatch, measurementBatch.end()));
    }

    if (gyroscopeHandler != nullptr)
    {
        MeasurementBatch gyroMeasurements{gyroscopeHandler->GetMeasurements()};
        std::move(gyroMeasurements.begin(), gyroMeasurements.end(), std::inserter(measurementBatch, measurementBatch.end()));
    }

    if (barometerHandler != nullptr)
    {
        MeasurementBatch barometerMeasurements{barometerHandler->GetMeasurements()};
        std::move(barometerMeasurements.begin(), barometerMeasurements.end(), std::inserter(measurementBatch, measurementBatch.end()));
    }

    return measurementBatch;
}
