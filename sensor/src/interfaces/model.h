/*
* Interface for general Kalman filter models.
*/

#ifndef MODEL_H_
#define MODEL_H_

#include "../headers/numeric_typedefs.h"
#include <eigen/Eigen>

class Model
{
public:
    virtual ~Model() {}
    virtual Eigen::MatrixXf GetF() const = 0;
    virtual Eigen::MatrixXf GetH() const = 0;
    virtual Eigen::MatrixXf GetQ() const = 0;
    virtual Eigen::MatrixXf GetR() const = 0;
};

#endif
