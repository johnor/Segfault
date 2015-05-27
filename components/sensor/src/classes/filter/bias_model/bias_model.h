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

    virtual void TimeUpdate(const TimePoint& newTime) override;

    virtual void Visit(const AccelerometerMeasurement& accMeas) override;
    virtual void Visit(const GyroscopeMeasurement& gyroMeas) override;
    virtual void Visit(const CompassMeasurement& compassMeas) override;
    virtual void Visit(const PressureMeasurement& pressureMeas) override;
    virtual void Visit(const TemperatureMeasurement& tempMeas) override;

private:
    enum BiasModelStates
    {
        Q0 = 0,
        Q1,
        Q2,
        Q3,
        WX,
        WY,
        WZ,
        BAX,
        BAY,
        BAZ,
        BGX,
        BGY,
        BGZ,
        NUM_STATES
    };

    enum BiasModelStateSizes
    {
        BA_SIZE = 3,
        BG_SIZE = 3
    };

    BiasModel(const BiasModel&) = delete;
    BiasModel& operator=(const BiasModel&) = delete;

    Eigen::MatrixXf GetF(const F32 dt) const;
    Eigen::MatrixXf GetHAcc() const;
    Eigen::MatrixXf GetHGyr() const;
    Eigen::VectorXf GetYGyr() const;
    Eigen::VectorXf GetYAcc() const;

    static Eigen::MatrixXf GetQ();
    static Eigen::MatrixXf GetRGyr();
    static Eigen::MatrixXf GetRAcc();
    static const F32 g;
};

#endif /* BIAS_MODEL_H_ */
