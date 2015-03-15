#ifndef LOG_READER_IMU_H_
#define LOG_READER_IMU_H_

#include "headers/smart_pointer_typedefs.h"
#include "interfaces/imu.h"

class LogReaderIMU : public IMU
{
public:
    explicit LogReaderIMU(SensorHandlerPtr logReader);
    virtual ~LogReaderIMU() {}
    virtual MeasurementBatch GetNextMeasurementBatch() const override;
private:
    LogReaderIMU(const LogReaderIMU&) = delete;
    LogReaderIMU& operator=(const LogReaderIMU&) = delete;

    SensorHandlerPtr logReader;
};

#endif
