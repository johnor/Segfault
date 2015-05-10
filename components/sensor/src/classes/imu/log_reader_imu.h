#ifndef LOG_READER_IMU_H_
#define LOG_READER_IMU_H_

#include <string>

#include "headers/smart_pointer_typedefs.h"
#include "interfaces/imu.h"

class LogReaderIMU : public IMU
{
public:
    explicit LogReaderIMU(const std::string& logFile);
    virtual ~LogReaderIMU() {}
    virtual MeasurementBatch GetNextMeasurementBatch() const override;
private:
    LogReaderIMU(const LogReaderIMU&) = delete;
    LogReaderIMU& operator=(const LogReaderIMU&) = delete;

    bool HasNewMeasurements() const;
    MeasurementPtr CreateMeasurement(const std::string& inputLine) const;
    std::vector<std::string> SplitString(const std::string& input, const char delim) const;

    mutable MeasurementBatch measurementList;
};

#endif
