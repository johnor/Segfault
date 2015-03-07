/*
* Interface for the abstract factory pattern.
* An I2C factory returns implementations of I2CHandlers
* that are needed by an IMU to communicate with its sensors.
*/

#ifndef SENSOR_HANDLER_FACTORY_H_
#define SENSOR_HANDLER_FACTORY_H_

#include "../headers/smart_pointer_typedefs.h"

class SensorHandlerFactory
{
public:
    virtual ~SensorHandlerFactory() {}
    virtual SensorHandlerPtr MakeAccAndMagHandler() const = 0;
    virtual SensorHandlerPtr MakeGyroscopeHandler() const = 0;
    virtual SensorHandlerPtr MakeBarometerHandler() const = 0;
};

#endif
