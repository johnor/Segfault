#ifndef IMUMODEL_H_
#define IMUMODEL_H_

#include "quaternion_state.h"

#include <eigen/Eigen>

class ImuModel
{
public:
    Eigen::MatrixXf GetF(const Eigen::Vector3f &omega);

private:
    QuaternionState state;
};



#endif