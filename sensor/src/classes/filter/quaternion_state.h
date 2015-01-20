#ifndef QUATERNIONSTATE_H_
#define QUATERNIONSTATE_H_

#include "interfaces/state.h"

#include <eigen/Eigen>

class QuaternionState : public State
{
public:
    QuaternionState() = default;
    virtual ~QuaternionState() {};

    virtual Eigen::Quaternionf GetQuaternion() const override;
    virtual Eigen::Vector3f GetEulerAngles() const override;
    virtual Eigen::Matrix3f GetRotationMatrix() const override;
private:
    QuaternionState(const QuaternionState&) = delete;
    QuaternionState& operator=(const QuaternionState&) = delete;

    Eigen::Vector4f state;
};



#endif