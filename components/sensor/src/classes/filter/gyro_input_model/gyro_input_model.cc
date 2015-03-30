#include "classes/measurements/measurements.h"
#include "gyro_input_model.h"


GyroInputModel::GyroInputModel()
    : Model{4}
{

}

void GyroInputModel::TimeUpdate(const F32 dt)
{

}

void GyroInputModel::Visit(const AccelerometerMeasurement& accMeas)
{

}

void GyroInputModel::Visit(const GyroscopeMeasurement& gyroMeas)
{
    const F32 microsecondsToSeconds{1e-6f};
    const U32 measurementTimeStamp{gyroMeas.GetTimeStamp()};
    const F32 dt = static_cast<F32>((measurementTimeStamp - state.GetTimeStamp())) * microsecondsToSeconds;

    const Eigen::Vector3f omega{gyroMeas.GetXValue(), gyroMeas.GetYValue(), gyroMeas.GetZValue()};
    const Eigen::Matrix4f F{Eigen::Matrix4f::Identity() + 0.5f * GetS(omega) * dt};

    state.GetX() = F * state.GetX();
    state.GetX().normalize();
    state.GetTimeStamp() = measurementTimeStamp;
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
