#ifndef GYRO_INPUT_MODEL_H_
#define GYRO_INPUT_MODEL_H_

#include <eigen/Eigen>
#include "common/src/numeric_typedefs.h"
#include "../model.h"

class GyroInputModel : public Model
{
public:
    GyroInputModel();
    virtual ~GyroInputModel() {}

    virtual void TimeUpdate(const TimePoint& newTime) override;

    virtual void Visit(const AccelerometerMeasurement& accMeas) override;
    virtual void Visit(const GyroscopeMeasurement& gyroMeas) override;
    virtual void Visit(const CompassMeasurement& compassMeas) override;
    virtual void Visit(const PressureMeasurement& pressureMeas) override;
    virtual void Visit(const TemperatureMeasurement& tempMeas) override;
private:
    GyroInputModel(const GyroInputModel&) = delete;
    GyroInputModel& operator=(const GyroInputModel&) = delete;
};

#endif
