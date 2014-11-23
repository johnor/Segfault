/*
* This file declares the BarometerHandler class which handles
* I2C-communication with the barometer on the IMU-chip.
*/

#ifndef BAROMETER_HANDLER_H_
#define BAROMETER_HANDLER_H_

#include "../../headers/smart_pointer_typedefs.h"
#include "../../interfaces/sensorhandler.h"
#include "../i2cdevice.h"

class BarometerHandler : public SensorHandler
{
public:
    BarometerHandler();
    virtual ~BarometerHandler() {}
    virtual MeasurementBatch GetMeasurements() const override;
    virtual bool HasAvailableMeasurements() const override;
private:
    BarometerHandler(const BarometerHandler&) = delete;
    BarometerHandler& operator=(const BarometerHandler&) = delete;
    void SetupRegisters();

    I2CDevice i2cDevice;
};

#endif
