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
	AccAndMagHandler() = default;
	virtual ~AccAndMagHandler() = default;
	virtual const Measurement* GetNextMeasurement() const override;
	virtual bool HasAvailableMeasurements() const override;
private:
	AccAndMagHandler(const AccAndMagHandler&) = delete;
	AccAndMagHandler& operator=(const AccAndMagHandler&) = delete;
};

#endif
