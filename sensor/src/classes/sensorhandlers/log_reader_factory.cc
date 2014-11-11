#include "log_reader_factory.h"
#include "acc_and_mag_handler.h"
#include "gyroscope_handler.h"
#include "barometer_handler.h"
#include "log_reader_handler.h"
#include "classes/logger.h"

SensorHandlerPtr LogReaderFactory::MakeAccAndMagHandler() const
{
    Logger::Log(LogLevel::Info) << "LogReaderHandlerFactory creating AccAndMagHandler";
    return SensorHandlerPtr{ new LogReader };
}

SensorHandlerPtr LogReaderFactory::MakeGyroscopeHandler() const
{
    Logger::Log(LogLevel::Info) << "LogReaderHandlerFactory creating GyroscopeHandler";
    return SensorHandlerPtr{ new LogReader };
}

SensorHandlerPtr LogReaderFactory::MakeBarometerHandler() const
{
    Logger::Log(LogLevel::Info) << "LogReaderHandlerFactory creating BarometerHandler";
    return SensorHandlerPtr{ new LogReader };
}
