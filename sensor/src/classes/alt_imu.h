/*
* This file declares the AltIMU class which models the specific IMU used in
* the project. It uses an I2CHandler factory to initialize its I2CHandlers.
*/

#ifndef ALT_IMU_H_
#define ALT_IMU_H_

#include "../interfaces/imu.h"
#include "../interfaces/measurement.h"
#include "../interfaces/i2c_handler_factory.h"
#include "../interfaces/i2chandler.h"
#include <memory>
#include <vector>

class AltIMU : public IMU
{
public:
	explicit AltIMU(const std::unique_ptr<I2CHandlerFactory>& handlerFactory);
	virtual ~AltIMU() {}
	virtual std::vector<std::unique_ptr<Measurement>> GetNextMeasurementBatch() const override;
private:
	AltIMU(const AltIMU&) = delete;
	AltIMU& operator=(const AltIMU&) = delete;

	void GetAllAvailableMeasurementsFromHandler(std::vector<std::unique_ptr<Measurement>>& measurementBatch,
												const std::unique_ptr<I2CHandler>& handler) const;
	std::unique_ptr<I2CHandler> accAndMagHandler;
	std::unique_ptr<I2CHandler> gyroscopeHandler;
	std::unique_ptr<I2CHandler> barometerHandler;
};

#endif
