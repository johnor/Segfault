/*
* This file declares the AltIMU class which models the specific IMU used in
* the project. It uses an I2CHandler factory to initialize its I2CHandlers.
*/

#ifndef ALT_IMU_H_
#define ALT_IMU_H_

#include "../interfaces/imu.h"
#include "../interfaces/i2chandler.h"

class AltIMU : public IMU
{
public:
	explicit AltIMU(const I2CHandlerFactoryPtr& handlerFactory);
	virtual ~AltIMU() {}
	virtual MeasurementBatch GetNextMeasurementBatch() const override;
private:
	AltIMU(const AltIMU&) = delete;
	AltIMU& operator=(const AltIMU&) = delete;

	void GetAllAvailableMeasurementsFromHandler(MeasurementBatch& measurementBatch,
		                                        const I2CHandlerPtr& handler) const;
	I2CHandlerPtr accAndMagHandler;
	I2CHandlerPtr gyroscopeHandler;
	I2CHandlerPtr barometerHandler;
};

#endif
