/*
* Interface for an inertial measurement unit.
* An IMU can return a batch of measurements collected
* from each of its sensors.
*/

#ifndef IMU_H_
#define IMU_H_

#include "../interfaces/measurement.h"
#include <memory>
#include <vector>

class IMU
{
public:
	virtual ~IMU() = default;
	virtual std::vector<std::unique_ptr<Measurement>> GetNextMeasurementBatch() const = 0;
};

#endif
