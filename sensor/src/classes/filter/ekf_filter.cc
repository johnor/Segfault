#include "../../interfaces/state.h"
#include "../../interfaces/measurement.h"
#include "../../interfaces/kalman_model.h"
#include "classes/measurements.h"
#include "ekf_filter.h"

void EkfFilter::Update(KalmanModelPtr& model, const MeasurementBatch& measurementBatch)
{
    for (const auto& measurement : measurementBatch)
    {
        if (dynamic_cast<GyroscopeMeasurement*>(measurement.get()))
        {
            measurement->Accept(*model);

            State& state = model->GetState();
            state.GetX() = model->GetPredictedState();
            state.SetTimeStamp(measurement->GetTimeStamp());

            //Update P

            //Measurement update
        }
    }
}
