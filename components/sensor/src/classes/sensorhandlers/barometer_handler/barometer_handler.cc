/*
* This file defines the BarometerHandler class which handles
* I2C-communication with the barometer on the IMU-chip.
*
* The barometer will operate in bypass mode, meaning that
* each new measurement will overwrite the previous one.
*
* Block data update is enabled, meaning that the
* output registers cannot be updated until all
* output registers have been read sequentially.
*
* Sample rate (ODR) is 25 Hz.
*
* Pressure data is scaled to hPa.
* Temperature data is scaled to degrees Celcius.
*/

#include "headers/exceptions.h"
#include "interfaces/clock.h"
#include "classes/measurements/measurements.h"

#include "barometer_handler.h"

const U8 I2C_ADDRESS_SA0_HIGH = 0x5dU;

const U8 WHO_AM_I_ADDRESS = 0x0fU;
const U8 WHO_AM_I_DATA = 0xbdU;

const U8 CTRL_1_ADDRESS = 0x20U;
const U8 CTRL_1_DATA = 0xc4U; /* Power on, sample rate 25 Hz, block data update enabled. */

const U8 PRESS_OUT_LOW_ADDRESS = 0x28U;

const U8 TEMP_OUT_LOW_ADDRESS = 0x2bU;

const U8 STATUS_ADDRESS = 0x27U;
const U8 TEMP_NDA_MASK = 1U;
const U8 PRESS_NDA_MASK = (1u << 1);

const F32 scaleToHectoPascals = 1.f / 4096.f;
const F32 tempScaleFactor = 1.f / 480.f;
const F32 tempOffsetFactor = 42.5f;

BarometerHandler::BarometerHandler(ClockPtr clock)
    : i2cDevice{I2C_ADDRESS_SA0_HIGH}, clock{clock}
{
    SetupRegisters();
}

MeasurementBatch BarometerHandler::GetMeasurements() const
{
    MeasurementBatch measurements;
    const U8 statusReg{i2cDevice.Read8BitReg(STATUS_ADDRESS)};
    const U32 timeStamp{clock->GetTimeStampInMicroSecs()};

    if (HasAvailablePressureMeasurement(statusReg))
    {
        const F32 pressureMeasurement{i2cDevice.ReadThree8BitRegsToFloat(PRESS_OUT_LOW_ADDRESS, scaleToHectoPascals)};
        measurements.push_back(MeasurementPtr{new PressureMeasurement{timeStamp, pressureMeasurement}});
    }

    if (HasAvailableTemperatureMeasurement(statusReg))
    {
        const F32 tempMeasurement{i2cDevice.ReadTwo8BitRegsToFloat(TEMP_OUT_LOW_ADDRESS, tempScaleFactor) + tempOffsetFactor};
        measurements.push_back(MeasurementPtr{new TemperatureMeasurement{timeStamp, tempMeasurement}});
    }

    return measurements;
}

bool BarometerHandler::HasAvailableMeasurements() const
{
    const U8 statusReg{i2cDevice.Read8BitReg(STATUS_ADDRESS)};

    return HasAvailablePressureMeasurement(statusReg) ||
           HasAvailableTemperatureMeasurement(statusReg);
}

void BarometerHandler::SetupRegisters()
{
    const U8 whoAmI{i2cDevice.Read8BitReg(WHO_AM_I_ADDRESS)};
    if (whoAmI != WHO_AM_I_DATA)
    {
        throw I2CException{"BarometerHandler() - Wrong WHO_AM_I value read."};
    }

    /* Set power on, sample rate 25 Hz, block data update enabled. */
    i2cDevice.WriteReg8(CTRL_1_ADDRESS, CTRL_1_DATA);
}

bool BarometerHandler::HasAvailablePressureMeasurement(const U8 statusReg) const
{
    const bool pressureDataAvailable{(statusReg & PRESS_NDA_MASK) ? true : false};
    return pressureDataAvailable;
}

bool BarometerHandler::HasAvailableTemperatureMeasurement(const U8 statusReg) const
{
    const bool temperatureDataAvailable{(statusReg & TEMP_NDA_MASK) ? true : false};
    return temperatureDataAvailable;
}
