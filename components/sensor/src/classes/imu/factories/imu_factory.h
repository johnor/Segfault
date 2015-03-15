#ifndef IMU_FACTORY_H_
#define IMU_FACTORY_H_

#include "headers/smart_pointer_typedefs.h"
#include <string>

class IMUFactory
{
public:
    explicit IMUFactory(ClockPtr clock);
    IMUPtr GetAltIMU() const;
    IMUPtr GetLogReaderIMU(const std::string& logFileName) const;
private:
    ClockPtr clock;
    std::string logFileName;
};

#endif
