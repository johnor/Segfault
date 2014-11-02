/*
* This file declares the AccAndMagHandler class which handles
* I2C-communication with the accelerometer and magnetometer on the IMU-chip.
*/

#ifndef ACC_AND_MAG_HANDLER_H_
#define ACC_AND_MAG_HANDLER_H_

#include "../../interfaces/i2chandler.h"
#include "../../interfaces/measurement.h"
#include <memory>

class AccAndMagHandler : public I2CHandler
{
public:
	AccAndMagHandler() = default;
	virtual ~AccAndMagHandler() {}
    virtual void Update() override;
	virtual std::unique_ptr<Measurement> GetNextMeasurement() const override;
	virtual bool HasAvailableMeasurements() const override;
private:
	AccAndMagHandler(const AccAndMagHandler&) = delete;
	AccAndMagHandler& operator=(const AccAndMagHandler&) = delete;
	void Init(const U8 devId);

	F32 accelerometerScale{ 0.f };
};

#endif
