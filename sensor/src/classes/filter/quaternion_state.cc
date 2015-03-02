#include "quaternion_state.h"

QuaternionState::QuaternionState()
    : state{4, 1}
{
    /* Initialize a unit quaternion */
    state(0) = 1.f;
    state(1) = 0.f;
    state(2) = 0.f;
    state(3) = 0.f;
}

Eigen::Quaternionf QuaternionState::GetQuaternion() const
{
    return Eigen::Quaternionf{state(0), state(1), state(2), state(3)};
}

Eigen::Vector3f QuaternionState::GetEulerAngles() const
{
    const F32 radToDeg{180.f / 3.1415926f};
    Eigen::Quaternionf quat{state(0), state(1), state(2), state(3)};
    return quat.toRotationMatrix().eulerAngles(0, 1, 2) * radToDeg;
}

Eigen::Matrix3f QuaternionState::GetRotationMatrix() const
{
    Eigen::Quaternionf quat{state(0), state(1), state(2), state(3)};
    return quat.toRotationMatrix();
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
