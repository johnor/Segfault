#ifndef LOG_READER_HANDLER_H_
#define LOG_READER_HANDLER_H_

#include <string>
#include "../../headers/smart_pointer_typedefs.h"
#include "../../interfaces/sensorhandler.h"
#include "../../interfaces/measurement.h"

class LogReaderHandler : public SensorHandler
{
public:
    LogReaderHandler(ClockPtr clock, const std::string& logFile);
    virtual ~LogReaderHandler() {}
    virtual MeasurementBatch GetMeasurements() const override;
    virtual bool HasAvailableMeasurements() const override;
private:
    LogReaderHandler(const LogReaderHandler&) = delete;
    LogReaderHandler& operator=(const LogReaderHandler&) = delete;

    MeasurementPtr CreateMeasurement(const std::string& inputLine) const;
    std::vector<std::string> SplitString(const std::string& input, const char delim) const;

    ClockPtr clock;
    mutable MeasurementBatch measurementList;
};

#endif
