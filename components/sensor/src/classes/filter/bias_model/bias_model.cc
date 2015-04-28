#include "classes/measurements/measurements.h"
#include "common/src/time_point.h"
#include "bias_model.h"

using namespace Eigen;

BiasModel::BiasModel()
    : Model{NUM_STATES}
{
}

void BiasModel::TimeUpdate(const TimePoint& newTime)
{
    const TimePoint timeDifference{newTime - state.GetTime()};
    const F32 dt = timeDifference.GetSeconds();

    const MatrixXf F{GetF(dt)};

    state.GetX() = F * state.GetX();
    state.GetX().segment(Q0, Q_SIZE).normalize();

    state.GetP() = F * state.GetP() * F.transpose() + GetQ();

    state.GetTime() = newTime;
}

void BiasModel::Visit(const AccelerometerMeasurement& accMeas)
{

}

void BiasModel::Visit(const GyroscopeMeasurement& gyroMeas)
{
    const TimePoint measurementTime{gyroMeas.GetTime()};
    TimeUpdate(measurementTime);

    const VectorXf omega{gyroMeas.GetVector()};
    const VectorXf innovation{omega - GetYGyr()};
    const MatrixXf H{GetHGyr()};
    const MatrixXf S{H * state.GetP() * H.transpose() + GetRGyr()};
    const MatrixXf K{state.GetP() * H.transpose() * S.inverse()};

    state.GetX() = state.GetX() + K * innovation;
    state.GetP() = (Matrix<F32, NUM_STATES, NUM_STATES>::Identity() - K * H) * state.GetP();
    state.GetX().segment(Q0, Q_SIZE).normalize();
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

MatrixXf BiasModel::GetF(const F32 dt) const
{
    MatrixXf F{Matrix<F32, NUM_STATES, NUM_STATES>::Zero()};

    const VectorXf& X{state.GetX()};
    const Vector3f omega{X.segment(WX, W_SIZE)};
    const Vector4f q{X.segment(Q0, Q_SIZE)};

    const MatrixXf sOmega{GetS(omega)};
    const MatrixXf sQ{GetS(q)};

    F.block(Q0, Q0, Q_SIZE, Q_SIZE) = MatrixXf::Identity(Q_SIZE, Q_SIZE) + (dt / 2.f) * sOmega;
    F.block(Q0, WX, Q_SIZE, W_SIZE) = (dt * dt / 2.f) * sQ;
    F.block(WX, WX, W_SIZE, W_SIZE).setIdentity();
    F.block(BAX, BAX, BA_SIZE, BA_SIZE).setIdentity();
    F.block(BGX, BGX, BG_SIZE, BG_SIZE).setIdentity();

    return F;
}

MatrixXf BiasModel::GetHAcc() const
{
    MatrixXf H{Matrix<F32, BA_SIZE, NUM_STATES>::Zero()};

    MatrixXf Hq{Matrix<F32, BA_SIZE, Q_SIZE>::Zero()};
    const VectorXf q{state.GetX().segment(Q0, Q_SIZE)};

    Hq << q(2),  q(3),  q(0), q(1),
         -q(1), -q(0),  q(3), q(2),
          q(0), -q(1), -q(2), q(3);
    Hq *= 2 * 9.82;

    H.block(0, Q0, BA_SIZE, Q_SIZE) = Hq;
    H.block(0, BAX, BA_SIZE, BA_SIZE).setIdentity();

    return H;
}

MatrixXf BiasModel::GetHGyr() const
{
    MatrixXf H{Matrix<F32, BG_SIZE, NUM_STATES>::Zero()};

    H.block(0, WX, W_SIZE, W_SIZE).setIdentity();
    H.block(0, BGX, BG_SIZE, BG_SIZE).setIdentity();

    return H;
}

VectorXf BiasModel::GetYGyr() const
{
    const VectorXf omega{state.GetX().segment(WX, W_SIZE)};
    const VectorXf gyroBias{state.GetX().segment(BGX, BG_SIZE)};

    return omega + gyroBias;
}

MatrixXf BiasModel::GetQ()
{
    return Matrix<F32, NUM_STATES, NUM_STATES>::Identity();
}

MatrixXf BiasModel::GetRGyr()
{
    return Matrix<F32, BG_SIZE, BG_SIZE>::Identity();
}

MatrixXf BiasModel::GetRAcc()
{
    return Matrix<F32, BA_SIZE, BA_SIZE>::Identity();
}
