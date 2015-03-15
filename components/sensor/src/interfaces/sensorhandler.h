#ifndef SENSOR_HANDLER_H_
#define SENSOR_HANDLER_H_

#include "headers/smart_pointer_typedefs.h"

class SensorHandler
{
public:
    virtual ~SensorHandler() {}
    virtual MeasurementBatch GetMeasurements() const = 0;
};

#endif
