#include "log_reader_factory.h"
#include "../acc_and_mag_handler.h"
#include "../gyroscope_handler.h"
#include "../barometer_handler.h"
#include "../log_reader_handler.h"
#include "../../logger.h"


LogReaderFactory::LogReaderFactory(SoftwareClock &clock_, const std::string &logFileName_) : clock(clock_), logFileName(logFileName_)
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
