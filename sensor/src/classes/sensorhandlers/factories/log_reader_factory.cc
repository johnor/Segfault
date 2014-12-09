#include "log_reader_factory.h"
#include "../acc_and_mag_handler.h"
#include "../gyroscope_handler.h"
#include "../barometer_handler.h"
#include "../log_reader_handler.h"
#include "../../clock/softwareclock.h"
#include "../../logger.h"

LogReaderFactory::LogReaderFactory(Clock& clock, const std::string& logFileName) : clock(clock), logFileName(logFileName)
{
}

SensorHandlerPtr LogReaderFactory::MakeAccAndMagHandler() const
{
    Logger::Log(LogLevel::Info) << "LogReaderHandlerFactory creating LogReader as AccAndMagHandler";
    return SensorHandlerPtr{ new LogReader{ clock, logFileName } };
}

SensorHandlerPtr LogReaderFactory::MakeGyroscopeHandler() const
{
    Logger::Log(LogLevel::Info) << "LogReaderHandlerFactory creating no GyroscopeHandler";
    return SensorHandlerPtr{ nullptr };
}

SensorHandlerPtr LogReaderFactory::MakeBarometerHandler() const
{
    Logger::Log(LogLevel::Info) << "LogReaderHandlerFactory creating no BarometerHandler";
    return SensorHandlerPtr{ nullptr };
}
