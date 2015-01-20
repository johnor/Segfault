#include "ekf_filter.h"
#include "gyro_input_model.h"
#include "interfaces/measurement.h"
#include "interfaces/kalman_model.h"


void EkfFilter::Update(KalmanModelPtr& model, const MeasurementBatch& measurementBatch)
{
    for (const auto& measurement : measurementBatch)
    {
        measurement->Accept(*model);

        model->GetState().GetX() = model->GetPredictedState();

        //Update P

        //Measurement update
    }
}
