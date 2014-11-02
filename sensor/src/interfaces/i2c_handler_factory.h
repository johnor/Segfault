/*
* Interface for the abstract factory pattern.
* An I2C factory returns implementations of I2CHandlers
* that are needed by an IMU to communicate with its sensors.
*/

#ifndef I2C_HANDLER_FACTORY_H_
#define I2C_HANDLER_FACTORY_H_

#include "../headers/smart_pointer_typedefs.h"

class I2CHandlerFactory
{
public:
	virtual ~I2CHandlerFactory() {}
	virtual I2CHandlerPtr MakeAccAndMagHandler() const = 0;
	virtual I2CHandlerPtr MakeGyroscopeHandler() const = 0;
	virtual I2CHandlerPtr MakeBarometerHandler() const = 0;
};

#endif
