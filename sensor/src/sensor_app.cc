#include <iostream>

#include "interfaces/imu.h"
#include "interfaces/clock.h"
#include "interfaces/measurement.h"
#include "classes/alt_imu.h"
#include "classes/filter/gyro_input_model.h"

#include "sensor_app.h"

SensorApp::SensorApp(const SensorHandlerFactoryPtr& sensorHandlerFactory, Clock& clock)
    : clock(clock), imu{new AltIMU{sensorHandlerFactory}}, model{new GyroInputModel{state}}
{
}

void SensorApp::Update()
{
    MeasurementBatch measurementBatch{imu->GetNextMeasurementBatch()};

    filter.Update(model, measurementBatch);
    std::cout << "EulerAngles:" << std::endl << state.GetEulerAngles() << std::endl;

    clock.IncreaseTimeStamp(1.f / 20.f);
}
