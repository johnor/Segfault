/*
* Interface for an inertial measurement unit.
* An IMU can return a batch of measurements collected
* from each of its sensors.
*/

#ifndef IMU_H_
#define IMU_H_

#include "headers/smart_pointer_typedefs.h"

class IMU
{
public:
    virtual ~IMU() {}
    virtual MeasurementBatch GetNextMeasurementBatch() const = 0;
};

#endif
