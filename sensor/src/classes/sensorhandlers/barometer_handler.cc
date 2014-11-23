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

#include "barometer_handler.h"
#include "../measurements.h"
#include "../../headers/exceptions.h"
#include "../clock.h"

const U8 I2C_ADDRESS_SA0_HIGH = 0x5d;

const U8 WHO_AM_I_ADDRESS = 0x0f;
const U8 WHO_AM_I_DATA = 0xbd;

const U8 CTRL_1_ADDRESS = 0x20;
const U8 CTRL_1_DATA = 0xc4; /* Power on, sample rate 25 Hz, block data update enabled. */

const U8 PRESS_OUT_LOW_ADDRESS = 0x28;

const U8 TEMP_OUT_LOW_ADDRESS = 0x2b;

const U8 STATUS_ADDRESS = 0x27;
const U8 TEMP_NDA_MASK = 1u;
const U8 PRESS_NDA_MASK = (1u << 1);

const F32 scaleToHectoPascals = 1.f / 4096.f;
const F32 tempScaleFactor = 1.f / 480.f;
const F32 tempOffsetFactor = 42.5f;

BarometerHandler::BarometerHandler()
    : i2cDevice{I2C_ADDRESS_SA0_HIGH}
{
    SetupRegisters();
}

MeasurementBatch BarometerHandler::GetMeasurements() const
{
    MeasurementBatch measurements;

    if (HasAvailableMeasurements())
    {
        const F32 pressureMeasurement{i2cDevice.ReadThree8BitRegsToFloat(PRESS_OUT_LOW_ADDRESS, scaleToHectoPascals)};
        const F32 tempMeasurement{i2cDevice.ReadTwo8BitRegsToFloat(TEMP_OUT_LOW_ADDRESS, tempScaleFactor) + tempOffsetFactor};
        const U32 timeStamp{Clock::GetTimeStampInMicroSecs()};

        measurements.push_back(MeasurementPtr{new PressureMeasurement{timeStamp, pressureMeasurement}});
        measurements.push_back(MeasurementPtr{new PressureMeasurement{timeStamp, tempMeasurement}});
    }

    return measurements;
}

bool BarometerHandler::HasAvailableMeasurements() const
{
    const U8 statusReg{i2cDevice.Read8BitReg(STATUS_ADDRESS)};
    const bool pressureDataAvailable{static_cast<bool>(statusReg & PRESS_NDA_MASK)};
    const bool tempDataAvailable{static_cast<bool>(statusReg & TEMP_NDA_MASK)};

    return (pressureDataAvailable && tempDataAvailable);
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
