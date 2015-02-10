#ifndef EKFFILTER_H_
#define EKFFILTER_H_

#include "headers/numeric_typedefs.h"
#include "headers/smart_pointer_typedefs.h"

class EkfFilter
{
public:
    EkfFilter() = default;
    void Update(KalmanModelPtr& model, const MeasurementBatch& measurements);

private:
    EkfFilter(const EkfFilter&) = delete;
    EkfFilter& operator=(const EkfFilter&) = delete;

};

#endif
