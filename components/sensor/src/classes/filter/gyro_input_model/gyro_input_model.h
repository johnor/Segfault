#ifndef GYRO_INPUT_MODEL_H_
#define GYRO_INPUT_MODEL_H_

#include <eigen/Eigen>
#include "common/src/numeric_typedefs.h"
#include "headers/smart_pointer_typedefs.h"

#include "../model.h"

class GyroInputModel : public Model
{
public:
    GyroInputModel();
    ~GyroInputModel() = default;

    virtual void TimeUpdate(const F32 dt) override;

    virtual void Visit(const AccelerometerMeasurement& accMeas) override;
    virtual void Visit(const GyroscopeMeasurement& gyroMeas) override;
    virtual void Visit(const CompassMeasurement& compassMeas) override;
    virtual void Visit(const PressureMeasurement& pressureMeas) override;
    virtual void Visit(const TemperatureMeasurement& tempMeas) override;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
    GyroInputModel(const GyroInputModel&) = delete;
    GyroInputModel& operator=(const GyroInputModel&) = delete;

    static Eigen::Matrix4f GetS(const Eigen::Vector3f& omega);
};

#endif
