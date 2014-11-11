#ifndef LOGREADER_H_
#define LOGREADER_H_

#include "../../interfaces/sensorhandler.h"

class LogReader : public SensorHandler
{
public:
    LogReader() = default;
    virtual ~LogReader() {}

    virtual MeasurementBatch GetMeasurements() const override;
    virtual bool HasAvailableMeasurements() const override;
private:
    LogReader(const LogReader&) = delete;
    LogReader& operator=(const LogReader&) = delete;
};

#endif
