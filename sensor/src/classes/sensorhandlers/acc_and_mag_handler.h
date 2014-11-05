/*
* This file declares the AccAndMagHandler class which handles
* I2C-communication with the accelerometer and magnetometer on the IMU-chip.
*/

#ifndef ACC_AND_MAG_HANDLER_H_
#define ACC_AND_MAG_HANDLER_H_

#include "../../headers/smart_pointer_typedefs.h"
#include "../../interfaces/sensorhandler.h"
#include "classes/i2cdevice.h"

class AccAndMagHandler : public SensorHandler
{
public:
	AccAndMagHandler();
	virtual ~AccAndMagHandler() {}
    virtual void Update() override;
	virtual MeasurementBatch GetMeasurements() const override;
	virtual bool HasAvailableMeasurements() const override;
private:
	AccAndMagHandler(const AccAndMagHandler&) = delete;
	AccAndMagHandler& operator=(const AccAndMagHandler&) = delete;
	void SetUpRegisters();

	I2CDevice i2cDevice;
	F32 accelerometerScale{ 0.f };
};

#endif
