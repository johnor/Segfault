/*
* This file declares the BarometerHandler class which handles
* I2C-communication with the barometer on the IMU-chip.
*/

#ifndef BAROMETER_HANDLER_H_
#define BAROMETER_HANDLER_H_

#include "../../interfaces/i2chandler.h"

class Measurement;

class BarometerHandler : public I2CHandler
{
public:
	BarometerHandler();
	virtual ~BarometerHandler();
	virtual Measurement* GetNextMeasurement() const;
	virtual bool HasAvailableMeasurements() const;
private:
	BarometerHandler(const BarometerHandler&);
	BarometerHandler& operator=(const BarometerHandler&);
};

#endif
