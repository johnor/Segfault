#include "quaternion_state.h"


Eigen::Quaternionf QuaternionState::GetQuaternion() const
{
    return{ state(0), state(1), state(2), state(3) };
}

Eigen::Vector3f QuaternionState::GetEulerAngles() const
{
    return{ 0.f, 0.f, 0.f };
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

U32 QuaternionState::GetCurrentTimeStamp() const
{
    throw std::logic_error("The method or operation is not implemented.");
}
