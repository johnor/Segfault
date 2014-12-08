#ifndef LOGREADER_H_
#define LOGREADER_H_

#include <string>
#include "../../interfaces/sensorhandler.h"
#include "interfaces/measurement.h"

class SoftwareClock;

class LogReader : public SensorHandler
{
public:
    LogReader(const SoftwareClock& clock, const std::string& logFile);
    virtual ~LogReader() {}
    virtual MeasurementBatch GetMeasurements() const override;
    virtual bool HasAvailableMeasurements() const override;
private:
    LogReader(const LogReader&) = delete;
    LogReader& operator=(const LogReader&) = delete;

    MeasurementPtr CreateMeasurement(const std::string& inputLine) const;

    const SoftwareClock& clock;
    mutable MeasurementBatch measurementList;
};

#endif
