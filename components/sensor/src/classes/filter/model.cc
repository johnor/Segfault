#include "model.h"

Model::Model(const S32 numberOfStates)
    : state{numberOfStates}
{
}

const State& Model::GetState() const
{
    return state;
}

Eigen::Matrix4f Model::GetS(const Eigen::Vector3f& w)
{
    Eigen::Matrix4f result{Eigen::Matrix4f::Zero()};

    result << 0.f,  -w(0), -w(1), -w(2),
              w(0),  0.f,   w(2), -w(1),
              w(1), -w(2),  0.f,   w(0),
              w(2),  w(1), -w(0),  0.f;

    return result;
}

Eigen::Matrix<F32, Model::Q_SIZE, Model::W_SIZE> Model::GetS(const Eigen::Vector4f& q)
{
    Eigen::Matrix<F32, Q_SIZE, W_SIZE> result{Eigen::Matrix<F32, Q_SIZE, W_SIZE>::Zero()};

    result << -q(1), -q(2), -q(3),
               q(0),  q(3),  q(2),
               q(3),  q(0), -q(1),
              -q(2),  q(1),  q(0);

    return result;
}
