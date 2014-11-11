#include "log_reader_handler.h"
#include "classes/logger.h"
#include "../measurements.h"

MeasurementBatch LogReader::GetMeasurements() const
{
    Logger::Log(LogLevel::Info) << "LogReader::GetMeasurements()";

    MeasurementBatch measurements{};
    return measurements;
}

bool LogReader::HasAvailableMeasurements() const
{
    Logger::Log(LogLevel::Info) << "LogReader::HasAvailableMeasurements()";
    return false;
}
