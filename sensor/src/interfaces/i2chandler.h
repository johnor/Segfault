/*
* Interface for I2CHandler.
* An I2CHandler can communicate with a sensor over
* the I2C bus and return collected measurements.
*/

#ifndef I2C_HANDLER_H_
#define I2C_HANDLER_H_

#include "../interfaces/measurement.h"
#include <memory>

class I2CHandler
{
public:
	virtual ~I2CHandler() {}
	virtual std::unique_ptr<Measurement> GetNextMeasurement() const = 0;
	virtual bool HasAvailableMeasurements() const = 0;
};

#endif
