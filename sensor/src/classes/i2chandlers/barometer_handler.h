/*
* This file declares the BarometerHandler class which handles
* I2C-communication with the barometer on the IMU-chip.
*/

#ifndef BAROMETER_HANDLER_H_
#define BAROMETER_HANDLER_H_

#include "../../headers/smart_pointer_typedefs.h"
#include "../../interfaces/i2chandler.h"

class BarometerHandler : public I2CHandler
{
public:
	BarometerHandler() = default;
	virtual ~BarometerHandler() {}
	virtual MeasurementPtr GetNextMeasurement() const override;
	virtual bool HasAvailableMeasurements() const override;

	virtual void Update() override;

private:
	BarometerHandler(const BarometerHandler&) = delete;
	BarometerHandler& operator=(const BarometerHandler&) = delete;
};

#endif
