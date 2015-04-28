#include "classes/measurements/measurements.h"
#include "gyro_input_model.h"
#include "common/src/time_point.h"


GyroInputModel::GyroInputModel()
    : Model{4}
{

}

void GyroInputModel::TimeUpdate(const TimePoint& newTime)
{

}

void GyroInputModel::Visit(const AccelerometerMeasurement& accMeas)
{

}

void GyroInputModel::Visit(const GyroscopeMeasurement& gyroMeas)
{
    const TimePoint measurementTime{gyroMeas.GetTime()};

    const TimePoint timeDifference{measurementTime - state.GetTime()};
    const F32 dt = timeDifference.GetSeconds();

    const Eigen::Vector3f omega{gyroMeas.GetVector()};
    const Eigen::Matrix4f F{Eigen::Matrix4f::Identity() + 0.5f * GetS(omega) * dt};

    state.GetX() = F * state.GetX();
    state.GetX().normalize();
    state.GetTime() = measurementTime;
}

void GyroInputModel::Visit(const CompassMeasurement& compassMeas)
{
}

void GyroInputModel::Visit(const PressureMeasurement& pressureMeas)
{
}

void GyroInputModel::Visit(const TemperatureMeasurement& tempMeas)
{
}
