/*
* This file declares the AccAndMagHandler class which handles
* I2C-communication with the accelerometer and magnetometer on the IMU-chip.
*/

#ifndef ACC_AND_MAG_HANDLER_H_
#define ACC_AND_MAG_HANDLER_H_

#include "../../interfaces/i2chandler.h"

class Measurement;

class AccAndMagHandler : public I2CHandler
{
public:
	AccAndMagHandler();
	virtual ~AccAndMagHandler();
	virtual const Measurement* GetNextMeasurement() const;
	virtual bool HasAvailableMeasurements() const;
private:
	AccAndMagHandler(const AccAndMagHandler&);
	AccAndMagHandler& operator=(const AccAndMagHandler&);
};

#endif
