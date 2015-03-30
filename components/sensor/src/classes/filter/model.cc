#include "model.h"

Model::Model(const S32 numberOfStates)
    : state{numberOfStates}
{
}

const State& Model::GetState() const
{
    return state;
}

Eigen::Matrix4f Model::GetS(const Eigen::Vector3f& omega)
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

Eigen::Matrix<F32, 4, 3> Model::GetS(const Eigen::Vector4f& q)
{
    Eigen::Matrix<F32, 4, 3> result{Eigen::Matrix<F32, 4, 3>::Zero()};

    result(0, 0) = -q(1);
    result(0, 1) = -q(2);
    result(0, 2) = -q(3);

    result(1, 0) = q(0);
    result(1, 1) = q(3);
    result(1, 2) = q(2);

    result(2, 0) = q(3);
    result(2, 1) = q(0);
    result(2, 2) = -q(1);

    result(3, 0) = -q(2);
    result(3, 1) = q(1);
    result(3, 2) = q(0);

    return result;
}
