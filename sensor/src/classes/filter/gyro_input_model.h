#ifndef GYROINPUTMODEL_H_
#define GYROINPUTMODEL_H_

#include "quaternion_state.h"
#include "interfaces/kalman_model.h"
#include "quaternion_state.h"
#include <eigen/Eigen>

class GyroInputModel : public KalmanModel
{
public:
    GyroInputModel(QuaternionState &state);

    virtual State& GetState() override;

    virtual Eigen::VectorXf GetPredictedState() const override;
    virtual Eigen::VectorXf GetInnovation() const override;

    virtual Eigen::MatrixXf GetF() const override;
    virtual Eigen::MatrixXf GetH() const override;
    virtual Eigen::MatrixXf GetQ() const override;
    virtual Eigen::MatrixXf GetR() const override;

    virtual void Visit(const AccelerometerMeasurement& accMeas) override;
    virtual void Visit(const GyroscopeMeasurement& gyroMeas) override;
    virtual void Visit(const CompassMeasurement& compassMeas) override;
    virtual void Visit(const PressureMeasurement& pressureMeas) override;
    virtual void Visit(const TemperatureMeasurement& tempMeas) override;

private:
    GyroInputModel(const GyroInputModel&) = delete;
    GyroInputModel& operator=(const GyroInputModel&) = delete;

    Eigen::Matrix4f GetS(const Eigen::Vector3f& omega) const;

    QuaternionState &state;
    Eigen::Matrix4f F;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};



#endif