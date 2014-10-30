/*
* This file declares the AltIMU class which models the specific IMU used in
* the project. It uses an I2CHandler factory to initialize its I2CHandlers.
*/

#ifndef ALT_IMU_H_
#define ALT_IMU_H_

#include "../interfaces/imu.h"
#include <vector>

class I2CHandlerFactory;
class I2CHandler;
class Measurement;

class AltIMU : public IMU
{
public:
	explicit AltIMU(const I2CHandlerFactory *const handlerFactory);
	virtual ~AltIMU();
	virtual std::vector<const Measurement*> GetNextMeasurementBatch() const override;
private:
	AltIMU(const AltIMU&) = delete;
	AltIMU& operator=(const AltIMU&) = delete;

	void GetAllAvailableMeasurementsFromHandler(std::vector<const Measurement*>& measurementBatch,
												const I2CHandler *const handler) const;
	I2CHandler* accAndMagHandler;
	I2CHandler* gyroscopeHandler;
	I2CHandler* barometerHandler;
};

#endif
