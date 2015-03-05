#ifndef SENSOR_APP_H
#define SENSOR_APP_H

#include "headers/smart_pointer_typedefs.h"
#include "classes/filter/ekf_filter.h"

class SensorApp
{
public:
    SensorApp(IMUPtr imu, KalmanModelPtr model, ClockPtr clock);
    ~SensorApp() = default;
    void Update();

    static const U16 serverPort{ 5001 };
private:
    SensorApp(const SensorApp&) = delete;
    SensorApp& operator=(const SensorApp&) = delete;

    IMUPtr imu;
    KalmanModelPtr model;
    ClockPtr clock;
    EkfFilter filter;
};

#endif
