#include "state.h"
#include "headers/exceptions.h"

State::State(const S32 numberOfStates)
    : X{numberOfStates},
      P{numberOfStates, numberOfStates},
      timeStamp{0u}
{
    if (numberOfStates < 4)
    {
        throw StateException{"At least four states are necessary to hold a quaternion."};
    }

    X.setZero();
    P.setIdentity();

    X(0) = 1.f; /* Unit quaternion */
}

const Eigen::VectorXf& State::GetX() const
{
    return X;
}

Eigen::VectorXf& State::GetX()
{
    return X;
}


const Eigen::MatrixXf& State::GetP() const
{
    return P;
}

Eigen::MatrixXf& State::GetP()
{
    return P;
}

U32 State::GetTimeStamp() const
{
    return timeStamp;
}

U32& State::GetTimeStamp()
{
    return timeStamp;
}

Eigen::Quaternionf State::GetQuaternion() const
{
    return Eigen::Quaternionf{X(0), X(1), X(2), X(3)};
}

Eigen::Vector3f State::GetEulerAngles() const
{
    const F32 radToDeg{180.f / 3.1415926f};
    const Eigen::Quaternionf quat{X(0), X(1), X(2), X(3)};
    return quat.toRotationMatrix().eulerAngles(0, 1, 2) * radToDeg;
}

Eigen::Matrix3f State::GetRotationMatrix() const
{
    const Eigen::Quaternionf quat{X(0), X(1), X(2), X(3)};
    return quat.toRotationMatrix();
}
