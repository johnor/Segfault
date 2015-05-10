/*
* This file declares the BarometerHandler class which handles
* I2C-communication with the barometer on the IMU-chip.
*/

#ifndef BAROMETER_HANDLER_H_
#define BAROMETER_HANDLER_H_

#include "components/common/src/numeric_typedefs.h"
#include "headers/smart_pointer_typedefs.h"
#include "../i2cdevice/i2cdevice.h"

class BarometerHandler
{
public:
    BarometerHandler();
    MeasurementBatch GetMeasurements() const;
private:
    BarometerHandler(const BarometerHandler&) = delete;
    BarometerHandler& operator=(const BarometerHandler&) = delete;

    void SetupRegisters();

    bool HasAvailablePressureMeasurement(const U8 statusReg) const;
    bool HasAvailableTemperatureMeasurement(const U8 statusReg) const;

    MeasurementPtr GetNextPressureMeasurement() const;
    MeasurementPtr GetNextTemperatureMeasurement() const;

    I2CDevice i2cDevice;
};

#endif
