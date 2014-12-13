#ifndef EKFFILTER_H_
#define EKFFILTER_H_

#include "headers/numeric_typedefs.h"
#include "headers/smart_pointer_typedefs.h"

class ImuModel;

class EkfFilter
{
public:
    void TimeUpdate(const ImuModel& model, const MeasurementBatch& measurements, const F32 dt);

private:

};



#endif