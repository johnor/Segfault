#ifndef KALMANMODEL_H_
#define KALMANMODEL_H_

#include "model.h"
#include "measurement_visitor.h"

class KalmanModel : public Model, public MeasurementVisitor
{
public:
    virtual ~KalmanModel() {};
};


#endif