#include "gyro_input_model.h"
#include "../measurements.h"
#include <stdexcept>

GyroInputModel::GyroInputModel(QuaternionState &state) : state(state)
{

}

State& GyroInputModel::GetState()
{
    return state;
}

Eigen::VectorXf GyroInputModel::GetPredictedState() const
{
    Eigen::Vector4f nextState = GetF() * state.GetX();

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
}

void GyroInputModel::Visit(const GyroscopeMeasurement& gyroMeas)
{
    const F32 dt = (F32)(gyroMeas.GetTimeStamp() - state.GetCurrentTimeStamp()); //TODO scale factor

    F = Eigen::Matrix4f::Identity();
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
