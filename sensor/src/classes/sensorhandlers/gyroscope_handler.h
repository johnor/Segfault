/*
* This file declares the GyroscopeHandler class which handles
* I2C-communication with the gyroscope on the IMU-chip.
*/

#ifndef GYROSCOPE_HANDLER_H_
#define GYROSCOPE_HANDLER_H_

#include "../../headers/smart_pointer_typedefs.h"
#include "../../interfaces/sensorhandler.h"
#include "../i2cdevice.h"
#include "../../interfaces/clock.h"

class GyroscopeHandler : public SensorHandler
{
public:
    GyroscopeHandler(Clock &clock_);
    virtual ~GyroscopeHandler() {}
    virtual MeasurementBatch GetMeasurements() const override;
    virtual bool HasAvailableMeasurements() const override;
private:
    GyroscopeHandler(const GyroscopeHandler&) = delete;
    GyroscopeHandler& operator=(const GyroscopeHandler&) = delete;
    void SetupRegisters();

    I2CDevice i2cDevice;
    Clock &clock;
};

#endif
