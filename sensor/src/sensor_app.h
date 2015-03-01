#ifndef SENSOR_APP_H
#define SENSOR_APP_H

#include "headers/smart_pointer_typedefs.h"
#include "classes/filter/quaternion_state.h"
#include "classes/filter/ekf_filter.h"

class Clock;

class SensorApp
{
public:
    SensorApp(const SensorHandlerFactoryPtr& sensorHandlerFactory, Clock& clock);
    ~SensorApp() = default;
    void Update();
private:
    SensorApp(const SensorApp&) = delete;
    SensorApp& operator=(const SensorApp&) = delete;

    QuaternionState state;
    EkfFilter filter;
    Clock& clock;
    IMUPtr imu;
    KalmanModelPtr model;
};

#endif
