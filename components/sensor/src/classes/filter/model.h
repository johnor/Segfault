/*
* Abstract base class for general Kalman filter models.
*/

#ifndef MODEL_H_
#define MODEL_H_

#include "components/common/src/numeric_typedefs.h"
#include "interfaces/measurement_visitor.h"
#include "state.h"

class Model : public MeasurementVisitor
{
public:
    explicit Model(const S32 numberOfStates);
    virtual ~Model() {}
    virtual void TimeUpdate(const F32 dt) = 0;
    const State& GetState() const;
protected:
    static Eigen::Matrix4f GetS(const Eigen::Vector3f& omega);
    static Eigen::Matrix<F32, 4, 3> GetS(const Eigen::Vector4f& q);

    State state;
};

#endif
