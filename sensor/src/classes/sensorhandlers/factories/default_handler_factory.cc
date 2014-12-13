/*
* Definition of a default concrete factory for the abstract factory pattern.
* This factory returns different concrete implementations I2Chandler interface.
* The factory is intended to be used by the IMU-class for dependency injection.
*/

#include "default_handler_factory.h"
#include "../../../interfaces/clock.h"
#include "../acc_and_mag_handler.h"
#include "../gyroscope_handler.h"
#include "../barometer_handler.h"
#include "../../logger.h"

DefaultHandlerFactory::DefaultHandlerFactory(const Clock& clock) : clock(clock)
{
}

SensorHandlerPtr DefaultHandlerFactory::MakeAccAndMagHandler() const
{
    Logger::Log(LogLevel::Info) << "DefaultHandlerFactory creating AccAndMagHandler";
    return SensorHandlerPtr{ new AccAndMagHandler{ clock } };
}

SensorHandlerPtr DefaultHandlerFactory::MakeGyroscopeHandler() const
{
    Logger::Log(LogLevel::Info) << "DefaultHandlerFactory creating GyroscopeHandler";
    return SensorHandlerPtr{ new GyroscopeHandler{ clock } };
}

SensorHandlerPtr DefaultHandlerFactory::MakeBarometerHandler() const
{
    Logger::Log(LogLevel::Info) << "DefaultHandlerFactory creating BarometerHandler";
    return SensorHandlerPtr{ new BarometerHandler{ clock } };
}
