#include <iostream>
#include <utility>

#include "interfaces/imu.h"
#include "interfaces/clock.h"
#include "interfaces/measurement.h"

#include "classes/filter/model.h"
#include "classes/service_locator/service_locator.h"

#include "components/server/src/connection_manager.h"
#include "components/server/src/message.h"

#include "components/server/src/MessageIds.h"

#include "sensor_app.h"

SensorApp::SensorApp(IMUPtr imu)
    : imu{std::move(imu)}
{
}

void SensorApp::Update()
{
    MeasurementBatch measurementBatch{imu->GetNextMeasurementBatch()};

    for (MeasurementPtr& measurement : measurementBatch)
    {
        measurement->Accept(gyroInputModel);
        measurement->Accept(biasModel);
    }

    ServiceLocator::GetClock().IncreaseTime(1.f / 20.f);
}

void SensorApp::SendData(ConnectionManager& connectionManager)
{
    const Eigen::Quaternionf gyroInputModelQuaternion = gyroInputModel.GetState().GetQuaternion();
    Message gyroMsg{Message_GyroInputModel_Quaternion};
    gyroMsg << gyroInputModelQuaternion;
    connectionManager.SendToAll(gyroMsg);

    const Eigen::Quaternionf biasModelQuaternion = biasModel.GetState().GetQuaternion();
    Message biasModelMsg{Message_BiasModel_Quaternion};
    biasModelMsg << biasModelQuaternion;
    connectionManager.SendToAll(biasModelMsg);
}
