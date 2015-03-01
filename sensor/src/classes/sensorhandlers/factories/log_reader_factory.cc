#include "../log_reader_handler.h"
#include "log_reader_factory.h"

LogReaderFactory::LogReaderFactory(Clock& clock, const std::string& logFileName)
    : clock(clock), logFileName(logFileName)
{
}

SensorHandlerPtr LogReaderFactory::MakeAccAndMagHandler() const
{
    return SensorHandlerPtr{new LogReaderHandler{clock, logFileName}};
}

SensorHandlerPtr LogReaderFactory::MakeGyroscopeHandler() const
{
    return SensorHandlerPtr{nullptr};
}

SensorHandlerPtr LogReaderFactory::MakeBarometerHandler() const
{
    return SensorHandlerPtr{nullptr};
}
