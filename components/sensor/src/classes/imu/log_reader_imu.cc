#include <utility>

#include "interfaces/sensor_handler.h"
#include "classes/measurements/measurements.h"
#include "log_reader_imu.h"

LogReaderIMU::LogReaderIMU(SensorHandlerPtr logReader)
    : logReader{std::move(logReader)}
{
}

MeasurementBatch LogReaderIMU::GetNextMeasurementBatch() const
{
    return logReader->GetMeasurements();
}
