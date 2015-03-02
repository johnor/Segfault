#include <iostream>
#include <utility>

#include "interfaces/imu.h"
#include "interfaces/clock.h"
#include "interfaces/kalman_model.h"
#include "interfaces/measurement.h"
#include "classes/filter/quaternion_state.h"

#include "sensor_app.h"

SensorApp::SensorApp(IMUPtr imu, KalmanModelPtr model, Clock& clock)
    : imu{std::move(imu)}, model{std::move(model)}, clock(clock)
{
}

void SensorApp::Update()
{
    static QuaternionState* state{dynamic_cast<QuaternionState*>(&model->GetState())};

    MeasurementBatch measurementBatch{imu->GetNextMeasurementBatch()};

    filter.Update(model, measurementBatch);

    if (state != nullptr)
    {
        std::cout << "EulerAngles:\n" << state->GetEulerAngles() << std::endl;
    }

    clock.IncreaseTimeStamp(1.f / 20.f);
}
