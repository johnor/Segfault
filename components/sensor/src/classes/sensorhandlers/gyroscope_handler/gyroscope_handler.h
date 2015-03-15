/*
* This file declares the GyroscopeHandler class which handles
* I2C-communication with the gyroscope on the IMU-chip.
*/

#ifndef GYROSCOPE_HANDLER_H_
#define GYROSCOPE_HANDLER_H_

#include "headers/smart_pointer_typedefs.h"
#include "interfaces/sensorhandler.h"
#include "../i2cdevice/i2cdevice.h"

class GyroscopeHandler : public SensorHandler
{
public:
    explicit GyroscopeHandler(ClockPtr clock);
    virtual ~GyroscopeHandler() {}
    virtual MeasurementBatch GetMeasurements() const override;
private:
    GyroscopeHandler(const GyroscopeHandler&) = delete;
    GyroscopeHandler& operator=(const GyroscopeHandler&) = delete;

    void SetupRegisters();

    bool HasNewGyroscopeMeasurement() const;

    MeasurementPtr GetNextGyroscopeMeasurement() const;

    I2CDevice i2cDevice;
    ClockPtr clock;
};

#endif
