#include <stdexcept>
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

Eigen::Matrix4f GyroInputModel::GetS(const Eigen::Vector3f& omega)
{
    Eigen::Matrix4f result{Eigen::Matrix4f::Zero()};

    result(0, 1) = -omega(0);
    result(0, 2) = -omega(1);
    result(0, 3) = -omega(2);

    result(1, 0) = omega(0);
    result(1, 2) = omega(2);
    result(1, 3) = -omega(1);

    result(2, 0) = omega(1);
    result(2, 1) = -omega(2);
    result(2, 3) = omega(0);

    result(3, 0) = omega(2);
    result(3, 1) = omega(1);
    result(3, 2) = -omega(0);

    return result;
}
