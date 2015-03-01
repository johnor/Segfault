/*
* Interface for general Kalman filter models.
*/

#ifndef MODEL_H_
#define MODEL_H_

#include <eigen/Eigen>
#include "../headers/numeric_typedefs.h"

class State;

class Model
{
public:
    virtual ~Model() {}

    virtual State& GetState() = 0;

    virtual Eigen::VectorXf GetPredictedState() const = 0;

    virtual Eigen::VectorXf GetInnovation() const = 0;

    virtual Eigen::MatrixXf GetF() const = 0;
    virtual Eigen::MatrixXf GetH() const = 0;
    virtual Eigen::MatrixXf GetQ() const = 0;
    virtual Eigen::MatrixXf GetR() const = 0;
};

#endif
