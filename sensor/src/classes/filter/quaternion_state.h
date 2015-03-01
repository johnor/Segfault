#ifndef QUATERNION_STATE_H_
#define QUATERNION_STATE_H_

#include <eigen/Eigen>
#include "interfaces/state.h"

class QuaternionState : public State
{
public:
    QuaternionState();
    virtual ~QuaternionState() {};

    virtual const Eigen::VectorXf& GetX() const override;
    virtual Eigen::VectorXf& GetX() override;

    virtual const Eigen::MatrixXf& GetP() const override;
    virtual Eigen::MatrixXf& GetP() override;

    virtual U32 GetTimeStamp() const override;
    virtual void SetTimeStamp(const U32 timeStamp) override;

    Eigen::Quaternionf GetQuaternion() const;
    Eigen::Vector3f GetEulerAngles() const;
    Eigen::Matrix3f GetRotationMatrix() const;
private:
    QuaternionState(const QuaternionState&) = delete;
    QuaternionState& operator=(const QuaternionState&) = delete;

    Eigen::VectorXf state;
    Eigen::MatrixXf P;
    U32 timeStamp{0u};
};

#endif
