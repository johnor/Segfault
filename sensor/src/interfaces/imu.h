/*
* Interface for an inertial measurement unit.
* An IMU can return a batch of measurements collected
* from each of its sensors.
*/

#ifndef IMU_H_
#define IMU_H_

#include <vector>

class Measurement;

class IMU
{
public:
	virtual ~IMU() = default;
	virtual std::vector<const Measurement*> GetNextMeasurementBatch() const = 0;
};

#endif
