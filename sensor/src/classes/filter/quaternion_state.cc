#include "quaternion_state.h"
#include <stdexcept>

QuaternionState::QuaternionState()
    : state{4, 1}
{
    state(0) = 1.f;
    state(1) = 0.f;
    state(2) = 0.f;
    state(3) = 0.f;
}

Eigen::Quaternionf QuaternionState::GetQuaternion() const
{
    return{ state(0), state(1), state(2), state(3) };
}

Eigen::Vector3f QuaternionState::GetEulerAngles() const
{
    Eigen::Quaternionf quat{state(0), state(1), state(2), state(3)};
    return quat.toRotationMatrix().eulerAngles(0, 1, 2) * 180/3.1415926;
}

Eigen::Matrix3f QuaternionState::GetRotationMatrix() const
{
    return Eigen::Matrix3f::Identity();
}

const Eigen::VectorXf& QuaternionState::GetX() const
{
    return state;
}

Eigen::VectorXf& QuaternionState::GetX()
{
    return state;
}

const Eigen::MatrixXf& QuaternionState::GetP() const
{
    return P;
}

Eigen::MatrixXf& QuaternionState::GetP()
{
    return P;
}

U32 QuaternionState::GetTimeStamp() const
{
    return timeStamp;
}

void QuaternionState::SetTimeStamp(const U32 timeStamp)
{
    this->timeStamp = timeStamp;
}
