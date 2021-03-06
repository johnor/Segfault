#ifndef STATE_H_
#define STATE_H_

#include <eigen/Eigen>
#include "components/common/src/numeric_typedefs.h"
#include "common/src/time_point.h"

class State
{
public:
    explicit State(const S32 numberOfStates);
    /* Compiler generated destruction, copy and move is safe. */

     const Eigen::VectorXf& GetX() const;
     Eigen::VectorXf& GetX();

     const Eigen::MatrixXf& GetP() const;
     Eigen::MatrixXf& GetP();

     const TimePoint& GetTime() const;
     TimePoint& GetTime();

     Eigen::Quaternionf GetQuaternion() const;

     Eigen::Vector3f GetEulerAngles() const;

     Eigen::Matrix3f GetRotationMatrix() const;

     EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
    Eigen::VectorXf X;
    Eigen::MatrixXf P;
    TimePoint timePoint;
};

#endif
