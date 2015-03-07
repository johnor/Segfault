#ifndef STATE_H_
#define STATE_H_

#include <eigen/Eigen>
#include "../headers/numeric_typedefs.h"
#include "../headers/smart_pointer_typedefs.h"

class State
{
public:
    virtual ~State() {}

    virtual Eigen::VectorXf GetX() const = 0;

    virtual Eigen::MatrixXf GetP() const = 0;

    virtual U32 GetTimeStamp() const = 0;

    virtual Eigen::Quaternionf GetQuaternion() const = 0;

    virtual Eigen::Vector3f GetEulerAngles() const = 0;

    virtual Eigen::Matrix3f GetRotationMatrix() const = 0;

    virtual StatePtr Clone() const = 0;
};

#endif
