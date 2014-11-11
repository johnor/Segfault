#ifndef LOG_READER_HANDLER_FACTORY_H_
#define LOG_READER_HANDLER_FACTORY_H_

#include "../../headers/smart_pointer_typedefs.h"
#include "../../interfaces/sensor_handler_factory.h"

class LogReaderFactory : public SensorHandlerFactory
{
public:
    LogReaderFactory() = default;
    virtual ~LogReaderFactory() {};

    virtual SensorHandlerPtr MakeAccAndMagHandler() const override;
    virtual SensorHandlerPtr MakeGyroscopeHandler() const override;
    virtual SensorHandlerPtr MakeBarometerHandler() const override;
private:
    LogReaderFactory(const LogReaderFactory&) = delete;
    LogReaderFactory& operator=(const LogReaderFactory&) = delete;
};

#endif

