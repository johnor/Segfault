/*
* Interface for I2CHandler.
* An I2CHandler can communicate with a sensor over
* the I2C bus and return collected measurements.
*/

#ifndef I2C_HANDLER_H_
#define I2C_HANDLER_H_

#include "classes/i2cdevice.h"
#include "../headers/smart_pointer_typedefs.h"

class I2CHandler
{
public:
	virtual ~I2CHandler() {}
 	virtual void Update() = 0;
	virtual MeasurementPtr GetNextMeasurement() const = 0;
	virtual bool HasAvailableMeasurements() const = 0;

protected:
	I2CDevice i2cDevice;
	int i2cFd{ -1 };
};

#endif
