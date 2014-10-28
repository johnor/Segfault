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
	GyroscopeHandler();
	virtual ~GyroscopeHandler();
	virtual const Measurement* GetNextMeasurement() const;
	virtual bool HasAvailableMeasurements() const;
private:
	GyroscopeHandler(const GyroscopeHandler&);
	GyroscopeHandler& operator=(const GyroscopeHandler&);
};

#endif
