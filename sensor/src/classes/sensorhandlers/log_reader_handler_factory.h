#ifndef LOG_READER_HANDLER_FACTORY_H_
#define LOG_READER_HANDLER_FACTORY_H_

#include "../../headers/smart_pointer_typedefs.h"
#include "../../interfaces/sensor_handler_factory.h"

class LogReaderHandlerFactory : public SensorHandlerFactory
{
public:
    LogReaderHandlerFactory() = default;
    virtual ~LogReaderHandlerFactory() {};

    virtual SensorHandlerPtr MakeAccAndMagHandler() const override;
    virtual SensorHandlerPtr MakeGyroscopeHandler() const override;
    virtual SensorHandlerPtr MakeBarometerHandler() const override;
private:
    LogReaderHandlerFactory(const LogReaderHandlerFactory&) = delete;
    LogReaderHandlerFactory& operator=(const LogReaderHandlerFactory&) = delete;
};

#endif

