/*
* This file defines the BarometerHandler class which handles
* I2C-communication with the barometer on the IMU-chip.
*/

#include "barometer_handler.h"
#include "../measurements.h"

MeasurementBatch BarometerHandler::GetMeasurements() const
{
    MeasurementBatch measurements;

    /* For testing purposes only */
    static bool returnPressure{true};
    if (returnPressure)
    {
        measurements.push_back(MeasurementPtr{ new PressureMeasurement{ 0, 1.f } });
    }
    else
    {
        returnPressure = true;
        measurements.push_back(MeasurementPtr{ new TemperatureMeasurement{ 0, 1.f } });
    }
    return measurements;
}

bool BarometerHandler::HasAvailableMeasurements() const
{
    /* For testing purposes only */
    return true;
}
