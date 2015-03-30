#include "gyro_input_model_state.h"

GyroInputModelState::GyroInputModelState()
    : X{4, 1}
{
    /* Initialize a unit quaternion */
    X(0) = 1.f;
    X(1) = 0.f;
    X(2) = 0.f;
    X(3) = 0.f;
}

Eigen::VectorXf GyroInputModelState::GetX() const
{
    return X;
}

Eigen::MatrixXf GyroInputModelState::GetP() const
{
    return P;
}

U32 GyroInputModelState::GetTimeStamp() const
{
    return timeStamp;
}

Eigen::Quaternionf GyroInputModelState::GetQuaternion() const
{
    return Eigen::Quaternionf{X(0), X(1), X(2), X(3)};
}

Eigen::Vector3f GyroInputModelState::GetEulerAngles() const
{
    const F32 radToDeg{180.f / 3.1415926f};
    const Eigen::Quaternionf quat{X(0), X(1), X(2), X(3)};
    return quat.toRotationMatrix().eulerAngles(0, 1, 2) * radToDeg;
}

Eigen::Matrix3f GyroInputModelState::GetRotationMatrix() const
{
    const Eigen::Quaternionf quat{X(0), X(1), X(2), X(3)};
    return quat.toRotationMatrix();
}

StatePtr GyroInputModelState::Clone() const
{
    StatePtr result{new GyroInputModelState{*this}};
    return result;
}
