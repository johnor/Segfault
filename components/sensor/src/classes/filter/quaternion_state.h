#ifndef QUATERNION_STATE_H_
#define QUATERNION_STATE_H_

#include <eigen/Eigen>
#include "headers/smart_pointer_typedefs.h"
#include "interfaces/state.h"

class QuaternionState : public State
{
public:
    QuaternionState();
    virtual ~QuaternionState() {};

    virtual Eigen::VectorXf GetX() const override;

    virtual Eigen::MatrixXf GetP() const override;

    virtual U32 GetTimeStamp() const override;

    virtual Eigen::Quaternionf GetQuaternion() const override;
    virtual Eigen::Vector3f GetEulerAngles() const override;
    virtual Eigen::Matrix3f GetRotationMatrix() const override;

    virtual StatePtr Clone() const override;

    friend class GyroInputModel;
private:
    QuaternionState(const QuaternionState&) = default;
    QuaternionState& operator=(const QuaternionState&) = delete;

    Eigen::VectorXf X;
    Eigen::MatrixXf P;
    U32 timeStamp{0u};
};

#endif
