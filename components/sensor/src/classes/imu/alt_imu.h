/*
* This file declares the AltIMU class which models the specific IMU used in
* the project. It uses an I2CHandler factory to initialize its I2CHandlers.
*/

#ifndef ALT_IMU_H_
#define ALT_IMU_H_

#include "classes/sensorhandlers/acc_and_mag_handler/acc_and_mag_handler.h"
#include "classes/sensorhandlers/gyroscope_handler/gyroscope_handler.h"
#include "classes/sensorhandlers/barometer_handler/barometer_handler.h"

#include "interfaces/imu.h"

class AltIMU : public IMU
{
public:
    AltIMU();
    virtual ~AltIMU() {};
    virtual MeasurementBatch GetNextMeasurementBatch() const override;
private:
    AltIMU(const AltIMU&) = delete;
    AltIMU& operator=(const AltIMU&) = delete;

    AccAndMagHandler accAndMagHandler;
    GyroscopeHandler gyroscopeHandler;
    BarometerHandler barometerHandler;
};

#endif
