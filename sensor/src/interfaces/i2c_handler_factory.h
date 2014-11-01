/*
* Interface for the abstract factory pattern.
* An I2C factory returns implementations of I2CHandlers
* that are needed by an IMU to communicate with its sensors.
*/

#ifndef I2C_HANDLER_FACTORY_H_
#define I2C_HANDLER_FACTORY_H_

#include "../interfaces/i2chandler.h"
#include <memory>

class I2CHandlerFactory
{
public:
	virtual ~I2CHandlerFactory() = default;
	virtual std::unique_ptr<I2CHandler> MakeAccAndMagHandler() const = 0;
	virtual std::unique_ptr<I2CHandler> MakeGyroscopeHandler() const = 0;
	virtual std::unique_ptr<I2CHandler> MakeBarometerHandler() const = 0;
};

#endif
