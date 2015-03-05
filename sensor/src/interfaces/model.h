/*
* Interface for general Kalman filter models.
*/

#ifndef MODEL_H_
#define MODEL_H_

#include "../headers/smart_pointer_typedefs.h"
#include "../headers/numeric_typedefs.h"
#include "../interfaces/measurement_visitor.h"

class Model : public MeasurementVisitor
{
public:
    virtual ~Model() {}
    virtual void TimeUpdate(const F32 dt) = 0;
    virtual StatePtr GetState() const = 0;
};

#endif
