/*
* This file defines the AltIMU class which models the specific IMU used in
* the project. It uses an I2CHandler factory to initialize its I2CHandlers.
*/

#include "alt_imu.h"
#include "interfaces/measurement.h"

AltIMU::AltIMU(ClockPtr clock)
    : accAndMagHandler{clock},
      gyroscopeHandler{clock},
      barometerHandler{clock}
{
}

MeasurementBatch AltIMU::GetNextMeasurementBatch() const
{
    MeasurementBatch measurementBatch;

    MeasurementBatch accMeasurements{accAndMagHandler.GetMeasurements()};
    std::move(accMeasurements.begin(), accMeasurements.end(), std::inserter(measurementBatch, measurementBatch.end()));

    MeasurementBatch gyroMeasurements{gyroscopeHandler.GetMeasurements()};
    std::move(gyroMeasurements.begin(), gyroMeasurements.end(), std::inserter(measurementBatch, measurementBatch.end()));

    MeasurementBatch barometerMeasurements{barometerHandler.GetMeasurements()};
    std::move(barometerMeasurements.begin(), barometerMeasurements.end(), std::inserter(measurementBatch, measurementBatch.end()));

    return measurementBatch;
}
