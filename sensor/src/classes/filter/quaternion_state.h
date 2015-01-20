#ifndef QUATERNIONSTATE_H_
#define QUATERNIONSTATE_H_

#include "interfaces/state.h"

#include <eigen/Eigen>

class QuaternionState : public State
{
public:
    QuaternionState() = default;
    virtual ~QuaternionState() {};

    virtual const Eigen::VectorXf& GetX() const override;
    virtual Eigen::VectorXf& GetX() override;

    virtual const Eigen::MatrixXf& GetP() const override;
    virtual Eigen::MatrixXf& GetP() override;

    virtual Eigen::Quaternionf GetQuaternion() const;
    virtual Eigen::Vector3f GetEulerAngles() const;
    virtual Eigen::Matrix3f GetRotationMatrix() const;

    virtual U32 GetCurrentTimeStamp() const override;
private:
    QuaternionState(const QuaternionState&) = delete;
    QuaternionState& operator=(const QuaternionState&) = delete;

    Eigen::VectorXf state;
    Eigen::MatrixXf P;
    U32 timeStamp{ 0u };
};



#endif