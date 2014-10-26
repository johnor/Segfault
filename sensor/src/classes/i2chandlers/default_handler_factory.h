/*
* Declaration of a default concrete factory for the abstract factory pattern.
* This factory returns different concrete implementations I2Chandler interface.
* The factory is intended to be used by the IMU-class for dependency injection.
*/

#ifndef DEFAULT_HANDLER_FACTORY_H_
#define DEFAULT_HANDLER_FACTORY_H_

#include "../../interfaces/i2c_handler_factory.h"

class I2CHandler;

class DefaultHandlerFactory : public I2CHandlerFactory
{
public:
	virtual ~DefaultHandlerFactory() {}
	virtual I2CHandler* MakeAccAndMagHandler() const;
	virtual I2CHandler* MakeGyroscopeHandler() const;
	virtual I2CHandler* MakeBarometerHandler() const;
};

#endif
