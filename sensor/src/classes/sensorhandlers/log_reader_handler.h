#ifndef LOGREADER_H_
#define LOGREADER_H_

#include <string>
#include <fstream>
#include "../../interfaces/sensorhandler.h"
#include "../softwareclock.h"

class LogReader : public SensorHandler
{
public:
    LogReader(const SoftwareClock &clock_, const std::string& logFile_);
    virtual ~LogReader() {}

    virtual MeasurementBatch GetMeasurements() const override;
    virtual bool HasAvailableMeasurements() const override;
private:
    LogReader(const LogReader&) = delete;
    LogReader& operator=(const LogReader&) = delete;

    MeasurementPtr CreateMeasurement(const std::string &inputLine) const;

    mutable std::ifstream logStream;
    const SoftwareClock &clock;
};

#endif
