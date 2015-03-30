#ifndef BIAS_MODEL_H_
#define BIAS_MODEL_H_

#include <eigen/Eigen>
#include "common/src/numeric_typedefs.h"
#include "../model.h"

class BiasModel : public Model
{
public:
    BiasModel();
    virtual ~BiasModel() {}

    virtual void TimeUpdate(const F32 dt) override;

    virtual void Visit(const AccelerometerMeasurement& accMeas) override;
    virtual void Visit(const GyroscopeMeasurement& gyroMeas) override;
    virtual void Visit(const CompassMeasurement& compassMeas) override;
    virtual void Visit(const PressureMeasurement& pressureMeas) override;
    virtual void Visit(const TemperatureMeasurement& tempMeas) override;
private:
    BiasModel(const BiasModel&) = delete;
    BiasModel& operator=(const BiasModel&) = delete;

    Eigen::MatrixXf GetF() const;
};

#endif /* BIAS_MODEL_H_ */
