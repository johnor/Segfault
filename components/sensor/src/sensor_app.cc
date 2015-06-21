#include <iostream>
#include <utility>

#include "interfaces/imu.h"
#include "interfaces/clock.h"
#include "interfaces/measurement.h"

#include "classes/filter/model.h"
#include "classes/service_locator/service_locator.h"

#include "components/server/src/connection_manager.h"
#include "components/server/src/message.h"

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
    Message gyroMsg;
    gyroMsg.SetMsgType(3);
    gyroMsg.WriteFloat(gyroInputModelQuaternion.w());
    gyroMsg.WriteFloat(gyroInputModelQuaternion.x());
    gyroMsg.WriteFloat(gyroInputModelQuaternion.y());
    gyroMsg.WriteFloat(gyroInputModelQuaternion.z());
    connectionManager.SendToAll(gyroMsg);

    const Eigen::Quaternionf biasModelQuaternion = biasModel.GetState().GetQuaternion();
    Message biasModelMsg;
    biasModelMsg.SetMsgType(4);
    biasModelMsg.WriteFloat(biasModelQuaternion.w());
    biasModelMsg.WriteFloat(biasModelQuaternion.x());
    biasModelMsg.WriteFloat(biasModelQuaternion.y());
    biasModelMsg.WriteFloat(biasModelQuaternion.z());
    connectionManager.SendToAll(biasModelMsg);
}
