#include "quaternion_state.h"


Eigen::Quaternionf QuaternionState::GetQuaternion() const
{
    return{ state(0), state(1), state(2), state(3) };
}

Eigen::Vector3f QuaternionState::GetEulerAngles() const
{
    throw std::logic_error("The method or operation is not implemented.");
}

Eigen::Matrix3f QuaternionState::GetRotationMatrix() const
{
    throw std::logic_error("The method or operation is not implemented.");
}
