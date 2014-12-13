/*
* Interface for I2CHandler.
* An I2CHandler can communicate with a sensor over
* the I2C bus and return collected measurements.
*/

#ifndef I2C_HANDLER_H_
#define I2C_HANDLER_H_

#include "../headers/smart_pointer_typedefs.h"

class SensorHandler
{
public:
    virtual ~SensorHandler() {}
    virtual MeasurementBatch GetMeasurements() const = 0;
    virtual bool HasAvailableMeasurements() const = 0;
};

#endif
