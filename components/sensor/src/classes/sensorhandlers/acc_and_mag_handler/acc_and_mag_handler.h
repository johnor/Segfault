/*
* This file declares the AccAndMagHandler class which handles
* I2C-communication with the accelerometer and magnetometer on the IMU-chip.
*/

#ifndef ACC_AND_MAG_HANDLER_H_
#define ACC_AND_MAG_HANDLER_H_

#include "headers/smart_pointer_typedefs.h"
#include "interfaces/sensorhandler.h"
#include "../i2cdevice/i2cdevice.h"

class AccAndMagHandler : public SensorHandler
{
public:
    explicit AccAndMagHandler(ClockPtr clock);
    virtual ~AccAndMagHandler() {}
    virtual MeasurementBatch GetMeasurements() const override;
    virtual bool HasAvailableMeasurements() const override;
private:
    AccAndMagHandler(const AccAndMagHandler&) = delete;
    AccAndMagHandler& operator=(const AccAndMagHandler&) = delete;

    void SetUpRegisters();
    bool HasNewAccelerometerMeasurement() const;
    bool HasNewMagnetometerMeasurement() const;

    MeasurementPtr GetNextAccelerometerMeasurement() const;
    MeasurementPtr GetNextMagnetometerMeasurement() const;

    I2CDevice i2cDevice;
    ClockPtr clock;
};

#endif
