#include "classes/sensorhandlers/factories/default_handler_factory.h"
#include "classes/imu/alt_imu.h"
#include "classes/imu/log_reader_imu.h"
#include "classes/measurements/measurements.h"

#include "imu_factory.h"

IMUFactory::IMUFactory(ClockPtr clock)
    : clock{clock}
{
}

IMUPtr IMUFactory::GetAltIMU() const
{
    return IMUPtr{new AltIMU{SensorHandlerFactoryPtr{new DefaultHandlerFactory{clock}}}};
}

IMUPtr IMUFactory::GetLogReaderIMU(const std::string& logFileName) const
{
    return IMUPtr{new LogReaderIMU{clock, logFileName}};
}
