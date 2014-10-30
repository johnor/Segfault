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
	DefaultHandlerFactory() = default;
	virtual ~DefaultHandlerFactory() = default;
	virtual I2CHandler* MakeAccAndMagHandler() const override;
	virtual I2CHandler* MakeGyroscopeHandler() const override;
	virtual I2CHandler* MakeBarometerHandler() const override;
private:
	DefaultHandlerFactory(const DefaultHandlerFactory&) = delete;
	DefaultHandlerFactory& operator=(const DefaultHandlerFactory&) = delete;
};

#endif
