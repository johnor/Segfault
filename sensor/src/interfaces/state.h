#ifndef STATE_H_
#define STATE_H_

#include <eigen/Eigen>
#include "../headers/numeric_typedefs.h"

class State
{
public:
    virtual ~State() {}

    virtual const Eigen::VectorXf& GetX() const = 0;
    virtual Eigen::VectorXf& GetX() = 0;

    virtual const Eigen::MatrixXf& GetP() const = 0;
    virtual Eigen::MatrixXf& GetP() = 0;

    virtual U32 GetTimeStamp() const = 0;
    virtual void SetTimeStamp(const U32 timeStamp) = 0;
};

#endif
