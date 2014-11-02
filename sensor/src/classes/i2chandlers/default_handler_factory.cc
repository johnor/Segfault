/*
* Definition of a default concrete factory for the abstract factory pattern.
* This factory returns different concrete implementations I2Chandler interface.
* The factory is intended to be used by the IMU-class for dependency injection.
*/

#include "default_handler_factory.h"
#include "acc_and_mag_handler.h"
#include "gyroscope_handler.h"
#include "barometer_handler.h"

I2CHandlerPtr DefaultHandlerFactory::MakeAccAndMagHandler() const
{
	return I2CHandlerPtr{new AccAndMagHandler{}};
}

I2CHandlerPtr DefaultHandlerFactory::MakeGyroscopeHandler() const
{
	return I2CHandlerPtr{new GyroscopeHandler{}};
}

I2CHandlerPtr DefaultHandlerFactory::MakeBarometerHandler() const
{
	return I2CHandlerPtr{new BarometerHandler{}};
}
