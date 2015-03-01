#ifndef EKF_FILTER_H_
#define EKF_FILTER_H_

#include "../../headers/smart_pointer_typedefs.h"

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
