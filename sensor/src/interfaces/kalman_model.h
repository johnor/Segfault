#ifndef KALMAN_MODEL_H_
#define KALMAN_MODEL_H_

#include "model.h"
#include "measurement_visitor.h"

class KalmanModel : public Model, public MeasurementVisitor
{
public:
    virtual ~KalmanModel() {};
};

#endif
