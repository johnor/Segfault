/*
* Interface for a general Kalman Filter
* A KalmanFilter can perform a time- and measurement update on a Model.
*/

#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_

#include "../headers/smart_pointer_typedefs.h"
#include "../headers/numeric_typedefs.h"

class KalmanFilter
{
public:
    virtual ~KalmanFilter() {}
    virtual void TimeUpdate(const ModelPtr& model, const MeasurementBatch& measurements, const F32 dt) const = 0;
    virtual void MeasurementUpdate(const ModelPtr& model, const MeasurementBatch& measurements, const F32 dt) const = 0;
};

#endif
