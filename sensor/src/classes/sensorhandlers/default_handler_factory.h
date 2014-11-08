/*
* Declaration of a default concrete factory for the abstract factory pattern.
* This factory returns different concrete implementations I2Chandler interface.
* The factory is intended to be used by the IMU-class for dependency injection.
*/

#ifndef DEFAULT_HANDLER_FACTORY_H_
#define DEFAULT_HANDLER_FACTORY_H_

#include "../../headers/smart_pointer_typedefs.h"
#include "../../interfaces/sensor_handler_factory.h"

class DefaultHandlerFactory : public SensorHandlerFactory
{
public:
	DefaultHandlerFactory() = default;
	virtual ~DefaultHandlerFactory() {};
	virtual SensorHandlerPtr MakeAccAndMagHandler() const override;
	virtual SensorHandlerPtr MakeGyroscopeHandler() const override;
	virtual SensorHandlerPtr MakeBarometerHandler() const override;
private:
	DefaultHandlerFactory(const DefaultHandlerFactory&) = delete;
	DefaultHandlerFactory& operator=(const DefaultHandlerFactory&) = delete;
};

#endif
