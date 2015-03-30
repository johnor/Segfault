#include "classes/measurements/measurements.h"
#include "bias_model.h"

BiasModel::BiasModel()
    : Model{13}
{

}

void BiasModel::TimeUpdate(const F32 dt)
{
}

void BiasModel::Visit(const AccelerometerMeasurement& accMeas)
{

}

void BiasModel::Visit(const GyroscopeMeasurement& gyroMeas)
{
    const F32 microsecondsToSeconds{1e-6f};
    const U32 measurementTimeStamp{gyroMeas.GetTimeStamp()};
    const F32 dt = static_cast<F32>((measurementTimeStamp - state.GetTimeStamp())) * microsecondsToSeconds;

    const Eigen::Vector3f omega{gyroMeas.GetXValue(), gyroMeas.GetYValue(), gyroMeas.GetZValue()};
    const Eigen::Matrix4f F{Eigen::Matrix4f::Identity() + 0.5f * GetS(omega) * dt};

    state.GetX() = F * state.GetX();
    state.GetX().normalize();
    state.GetTimeStamp() = measurementTimeStamp;
}

void BiasModel::Visit(const CompassMeasurement& compassMeas)
{
}

void BiasModel::Visit(const PressureMeasurement& pressureMeas)
{
}

void BiasModel::Visit(const TemperatureMeasurement& tempMeas)
{
}


Eigen::MatrixXf BiasModel::GetF() const
{
    /* Work in progress... */

    const Eigen::VectorXf& X{state.GetX()};
    const Eigen::Vector3f omega{X.segment(4, 3)};
    const Eigen::Vector4f q{X.segment(0, 4)};

    const Eigen::Matrix4f sOmega{GetS(omega)};
    const Eigen::Matrix<F32, 4, 3> sQ{GetS(q)};

    return Eigen::MatrixXf{13, 13};
}
