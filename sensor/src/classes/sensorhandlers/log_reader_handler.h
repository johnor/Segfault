#ifndef LOGREADER_H_
#define LOGREADER_H_

#include "../../interfaces/sensorhandler.h"

class LogReader : public SensorHandler
{
public:
    LogReader() = default;
    ~LogReader() = default;

    virtual MeasurementBatch GetMeasurements() const override;
    virtual bool HasAvailableMeasurements() const override;
};

#endif
