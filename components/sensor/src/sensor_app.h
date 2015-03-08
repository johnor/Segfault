#ifndef SENSOR_APP_H
#define SENSOR_APP_H

#include "headers/smart_pointer_typedefs.h"

class SensorApp
{
public:
    SensorApp(IMUPtr imu, ModelPtr model, ClockPtr clock);
    ~SensorApp() = default;
    void Update();
    void SendData(ConnectionManager& connectionManager);

    static const U16 serverPort{5001};
private:
    SensorApp(const SensorApp&) = delete;
    SensorApp& operator=(const SensorApp&) = delete;

    IMUPtr imu;
    ModelPtr model;
    ClockPtr clock;
};

#endif
