#ifndef LOG_READER_H_
#define LOG_READER_H_

#include <string>
#include "headers/smart_pointer_typedefs.h"
#include "interfaces/sensor_handler.h"
#include "interfaces/measurement.h"

class LogReader : public SensorHandler
{
public:
    LogReader(ClockPtr clock, const std::string& logFile);
    virtual ~LogReader() {}
    virtual MeasurementBatch GetMeasurements() const override;
private:
    LogReader(const LogReader&) = delete;
    LogReader& operator=(const LogReader&) = delete;

    bool HasNewMeasurements() const;

    MeasurementPtr CreateMeasurement(const std::string& inputLine) const;
    std::vector<std::string> SplitString(const std::string& input, const char delim) const;

    ClockPtr clock;
    mutable MeasurementBatch measurementList;
};

#endif
