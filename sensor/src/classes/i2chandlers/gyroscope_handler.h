/*
* This file declares the GyroscopeHandler class which handles
* I2C-communication with the gyroscope on the IMU-chip.
*/

#ifndef GYROSCOPE_HANDLER_H_
#define GYROSCOPE_HANDLER_H_

#include "../../interfaces/i2chandler.h"

class Measurement;

class GyroscopeHandler : public I2CHandler
{
public:
	GyroscopeHandler() = default;
	virtual ~GyroscopeHandler() = default;
	virtual const Measurement* GetNextMeasurement() const override;
	virtual bool HasAvailableMeasurements() const override;
private:
	GyroscopeHandler(const GyroscopeHandler&) = delete;
	GyroscopeHandler& operator=(const GyroscopeHandler&) = delete;
};

#endif
