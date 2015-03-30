#ifndef GYRO_INPUT_MODEL_STATE_H_
#define GYRO_INPUT_MODEL_STATE_H_

#include <eigen/Eigen>
#include "headers/smart_pointer_typedefs.h"
#include "interfaces/state.h"

class GyroInputModelState : public State
{
public:
    GyroInputModelState();
    virtual ~GyroInputModelState() {};

    virtual Eigen::VectorXf GetX() const override;

    virtual Eigen::MatrixXf GetP() const override;

    virtual U32 GetTimeStamp() const override;

    virtual Eigen::Quaternionf GetQuaternion() const override;
    virtual Eigen::Vector3f GetEulerAngles() const override;
    virtual Eigen::Matrix3f GetRotationMatrix() const override;

    virtual StatePtr Clone() const override;

    friend class GyroInputModel;
private:
    GyroInputModelState(const GyroInputModelState&) = default;
    GyroInputModelState& operator=(const GyroInputModelState&) = delete;

    Eigen::VectorXf X;
    Eigen::MatrixXf P;
    U32 timeStamp{0u};
};

#endif
