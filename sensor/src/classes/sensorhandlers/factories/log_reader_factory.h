#ifndef LOG_READER_HANDLER_FACTORY_H_
#define LOG_READER_HANDLER_FACTORY_H_

#include "../../../headers/smart_pointer_typedefs.h"
#include "../../../interfaces/sensor_handler_factory.h"
#include "../../clock/softwareclock.h"
#include <string>

class LogReaderFactory : public SensorHandlerFactory
{
public:
    LogReaderFactory(SoftwareClock &clock_, const std::string &logFileName_);
    virtual ~LogReaderFactory() {};

    virtual SensorHandlerPtr MakeAccAndMagHandler() const override;
    virtual SensorHandlerPtr MakeGyroscopeHandler() const override;
    virtual SensorHandlerPtr MakeBarometerHandler() const override;
private:
    LogReaderFactory(const LogReaderFactory&) = delete;
    LogReaderFactory& operator=(const LogReaderFactory&) = delete;

    SoftwareClock &clock;
    std::string logFileName;
};

#endif

