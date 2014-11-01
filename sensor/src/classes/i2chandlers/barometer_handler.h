/*
* This file declares the BarometerHandler class which handles
* I2C-communication with the barometer on the IMU-chip.
*/

#ifndef BAROMETER_HANDLER_H_
#define BAROMETER_HANDLER_H_

#include "../../interfaces/i2chandler.h"
#include "../../interfaces/measurement.h"
#include <memory>

class BarometerHandler : public I2CHandler
{
public:
	BarometerHandler() = default;
	virtual ~BarometerHandler() = default;
	virtual std::unique_ptr<Measurement> GetNextMeasurement() const override;
	virtual bool HasAvailableMeasurements() const override;
private:
	BarometerHandler(const BarometerHandler&) = delete;
	BarometerHandler& operator=(const BarometerHandler&) = delete;
};

#endif
