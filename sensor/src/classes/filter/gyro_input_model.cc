#include <stdexcept>
#include "../measurements.h"

#include "gyro_input_model.h"

GyroInputModel::GyroInputModel(QuaternionState& state)
    : state(state)
{
}

State& GyroInputModel::GetState()
{
    return state;
}

Eigen::VectorXf GyroInputModel::GetPredictedState() const
{
    Eigen::VectorXf nextState{GetF() * state.GetX()};
    nextState.normalize();

    return nextState;
}

Eigen::VectorXf GyroInputModel::GetInnovation() const
{
    throw std::logic_error("The method or operation is not implemented.");
}

Eigen::MatrixXf GyroInputModel::GetF() const
{
    return F;
}

Eigen::MatrixXf GyroInputModel::GetH() const
{
    throw std::logic_error("The method or operation is not implemented.");
}

Eigen::MatrixXf GyroInputModel::GetQ() const
{
    throw std::logic_error("The method or operation is not implemented.");
}

Eigen::MatrixXf GyroInputModel::GetR() const
{
    throw std::logic_error("The method or operation is not implemented.");
}

void GyroInputModel::Visit(const AccelerometerMeasurement& accMeas)
{
    F = Eigen::Matrix4f::Identity();
}

void GyroInputModel::Visit(const GyroscopeMeasurement& gyroMeas)
{
    const F32 microsecondsToSeconds{1e-6f};
    const F32 dt = static_cast<F32>((gyroMeas.GetTimeStamp() - state.GetTimeStamp())) * microsecondsToSeconds;
    const Eigen::Vector3f omega{gyroMeas.GetXValue(), gyroMeas.GetYValue(), gyroMeas.GetZValue()};

    F = Eigen::Matrix4f::Identity() + 0.5f * GetS(omega) * dt;
}

void GyroInputModel::Visit(const CompassMeasurement& compassMeas)
{
    F = Eigen::Matrix4f::Identity();
}

void GyroInputModel::Visit(const PressureMeasurement& pressureMeas)
{
    F = Eigen::Matrix4f::Identity();
}

void GyroInputModel::Visit(const TemperatureMeasurement& tempMeas)
{
    F = Eigen::Matrix4f::Identity();
}

Eigen::Matrix4f GyroInputModel::GetS(const Eigen::Vector3f& omega) const
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
