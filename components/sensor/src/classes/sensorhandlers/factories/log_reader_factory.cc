#include "../log_reader/log_reader.h"
#include "log_reader_factory.h"

LogReaderFactory::LogReaderFactory(ClockPtr clock, const std::string& logFileName)
    : clock{clock}, logFileName(logFileName)
{
}

SensorHandlerPtr LogReaderFactory::MakeAccAndMagHandler() const
{
    return SensorHandlerPtr{new LogReader{clock, logFileName}};
}

SensorHandlerPtr LogReaderFactory::MakeGyroscopeHandler() const
{
    return SensorHandlerPtr{nullptr};
}

SensorHandlerPtr LogReaderFactory::MakeBarometerHandler() const
{
    return SensorHandlerPtr{nullptr};
}
