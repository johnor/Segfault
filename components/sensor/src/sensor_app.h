#ifndef SENSOR_APP_H
#define SENSOR_APP_H

#include "headers/smart_pointer_typedefs.h"
#include "classes/filter/bias_model/bias_model.h"
#include "classes/filter/gyro_input_model/gyro_input_model.h"

class SensorApp
{
public:
    explicit SensorApp(IMUPtr imu);
    ~SensorApp() = default;
    void Update();
    void SendData(ConnectionManager& connectionManager);

    static const U16 serverPort{5001};
private:
    SensorApp(const SensorApp&) = delete;
    SensorApp& operator=(const SensorApp&) = delete;

    IMUPtr imu;
    BiasModel biasModel;
    GyroInputModel gyroInputModel;
};

#endif
