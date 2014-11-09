#include "log_reader_handler_factory.h"
#include "acc_and_mag_handler.h"
#include "gyroscope_handler.h"
#include "barometer_handler.h"
#include "classes/logger.h"

SensorHandlerPtr LogReaderHandlerFactory::MakeAccAndMagHandler() const
{
    Logger::Log(LogLevel::Info) << "LogReaderHandlerFactory creating AccAndMagHandler";
    return SensorHandlerPtr{ nullptr };
}

SensorHandlerPtr LogReaderHandlerFactory::MakeGyroscopeHandler() const
{
    Logger::Log(LogLevel::Info) << "LogReaderHandlerFactory creating GyroscopeHandler";
    return SensorHandlerPtr{ nullptr };
}

SensorHandlerPtr LogReaderHandlerFactory::MakeBarometerHandler() const
{
    Logger::Log(LogLevel::Info) << "LogReaderHandlerFactory creating BarometerHandler";
    return SensorHandlerPtr{ nullptr };
}
