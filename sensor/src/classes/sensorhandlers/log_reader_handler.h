#ifndef LOG_READER_HANDLER_H_
#define LOG_READER_HANDLER_H_

#include <string>
#include "../../interfaces/sensorhandler.h"
#include "interfaces/measurement.h"

class Clock;

class LogReaderHandler : public SensorHandler
{
public:
    LogReaderHandler(const Clock& clock, const std::string& logFile);
    virtual ~LogReaderHandler() {}
    virtual MeasurementBatch GetMeasurements() const override;
    virtual bool HasAvailableMeasurements() const override;
private:
    LogReaderHandler(const LogReaderHandler&) = delete;
    LogReaderHandler& operator=(const LogReaderHandler&) = delete;

    MeasurementPtr CreateMeasurement(const std::string& inputLine) const;
    std::vector<std::string> SplitString(const std::string& input, const char delim) const;

    const Clock& clock;
    mutable MeasurementBatch measurementList;
};

#endif
