#ifndef LOG_READER_FACTORY_H_
#define LOG_READER_FACTORY_H_

#include <string>
#include "../../../headers/smart_pointer_typedefs.h"
#include "../../../interfaces/sensor_handler_factory.h"

class Clock;

class LogReaderFactory : public SensorHandlerFactory
{
public:
    LogReaderFactory(Clock& clock, const std::string& logFileName);
    virtual ~LogReaderFactory() {};

    virtual SensorHandlerPtr MakeAccAndMagHandler() const override;
    virtual SensorHandlerPtr MakeGyroscopeHandler() const override;
    virtual SensorHandlerPtr MakeBarometerHandler() const override;
private:
    LogReaderFactory(const LogReaderFactory&) = delete;
    LogReaderFactory& operator=(const LogReaderFactory&) = delete;

    Clock& clock;
    std::string logFileName;
};

#endif
