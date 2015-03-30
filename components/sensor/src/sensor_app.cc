#include <iostream>
#include <utility>

#include "interfaces/imu.h"
#include "interfaces/clock.h"
#include "interfaces/measurement.h"

#include "classes/filter/model.h"

#include "components/server/src/connection_manager.h"
#include "components/server/src/message.h"

#include "sensor_app.h"

SensorApp::SensorApp(IMUPtr imu, ModelPtr model, ClockPtr clock)
    : imu{std::move(imu)}, model{std::move(model)}, clock{clock}
{
}

void SensorApp::Update()
{
    MeasurementBatch measurementBatch{imu->GetNextMeasurementBatch()};

    for (MeasurementPtr& measurement : measurementBatch)
    {
        measurement->Accept(*model);
    }

    std::cout << "EulerAngles:\n" << model->GetState().GetEulerAngles() << std::endl;

    clock->IncreaseTimeStamp(1.f / 20.f);
}

void SensorApp::SendData(ConnectionManager& connectionManager)
{
    const auto quaternion = model->GetState().GetQuaternion();
    Message msg;
    msg.SetMsgType(3);
    msg.SetBodyLength(sizeof(F32)* 4);
    msg.EncodeHeader();
    msg.WriteFloat(quaternion.w());
    msg.WriteFloat(quaternion.x());
    msg.WriteFloat(quaternion.y());
    msg.WriteFloat(quaternion.z());
    connectionManager.SendToAll(msg);
}
