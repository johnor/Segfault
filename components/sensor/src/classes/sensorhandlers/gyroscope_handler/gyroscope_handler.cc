/*
* This file defines the GyroscopeHandler class which handles
* I2C-communication with the gyroscope on the IMU-chip.
*
* The gyro will operate in bypass mode, meaning that
* each new measurement will overwrite the previous one.
*
* Block data update is enabled, meaning that the
* output registers cannot be updated until both
* output registers have been read sequentially.
*
* The high pass filter is disabled.
*
* Sample rate (ODR) is 100 Hz.
* LPF cutoff-freq is 12.5 Hz (nyquist freq / 4)
*
* Measurement range is +- 245 degrees per second.
*
* Output is scaled to radians per second.
*/

#include "headers/exceptions.h"
#include "interfaces/clock.h"
#include "classes/measurements/measurements.h"

#include "gyroscope_handler.h"

const U8 I2C_ADDRESS_SA0_HIGH = 0x6bU;

const U8 WHO_AM_I_ADDRESS = 0x0fU;
const U8 WHO_AM_I_DATA = 0xd7U;

const U8 X_OUT_LOW_ADDRESS = 0x28U;
const U8 Y_OUT_LOW_ADDRESS = 0x2aU;
const U8 Z_OUT_LOW_ADDRESS = 0x2cU;

const U8 CTRL_1_ADDRESS = 0x20U;
const U8 CTRL_1_DATA = 0x0fU; /* Power on, all axes enabled. */

const U8 CTRL_4_ADDRESS = 0x23U;
const U8 CTRL_4_DATA = 0x80U; /* Block data update enabled, range +- 245 degrees per second */

const U8 STATUS_ADDRESS = 0x27U;
const U8 NDA_BITMASK = (1u << 3);

const F32 PI = 3.14159265358979323846f;
const F32 scaleToDegreesPerSecond = 245.f / INT16_MAX;
const F32 scaleToRadiansPerSecond = scaleToDegreesPerSecond * (PI / 180.f);

GyroscopeHandler::GyroscopeHandler(ClockPtr clock)
    : i2cDevice{I2C_ADDRESS_SA0_HIGH}, clock{clock}
{
    SetupRegisters();
}

MeasurementBatch GyroscopeHandler::GetMeasurements() const
{
    MeasurementBatch measurements;

    if (HasNewGyroscopeMeasurement())
    {
        measurements.push_back(GetNextGyroscopeMeasurement());
    }

    return measurements;
}

void GyroscopeHandler::SetupRegisters()
{
    const U8 whoAmI{i2cDevice.Read8BitReg(WHO_AM_I_ADDRESS)};
    if (whoAmI != WHO_AM_I_DATA)
    {
        throw I2CException{"GyroscopeHandler() - Wrong WHO_AM_I value read."};
    }

    /* Set power on and enable all axes. */
    i2cDevice.WriteReg8(CTRL_1_ADDRESS, CTRL_1_DATA);

    /* Enabled block data update and set range to +- 245 degrees per second. */
    i2cDevice.WriteReg8(CTRL_4_ADDRESS, CTRL_4_DATA);
}

bool GyroscopeHandler::HasNewGyroscopeMeasurement() const
{
    const U8 statusReg{i2cDevice.Read8BitReg(STATUS_ADDRESS)};
    const bool newDataAvailable{(statusReg & NDA_BITMASK) ? true : false};

    return newDataAvailable;
}

MeasurementPtr GyroscopeHandler::GetNextGyroscopeMeasurement() const
{
    const U32 timeStamp{clock->GetTimeStampInMicroSecs()};
    const F32 xValue{i2cDevice.ReadTwo8BitRegsToFloat(X_OUT_LOW_ADDRESS, scaleToRadiansPerSecond)};
    const F32 yValue{i2cDevice.ReadTwo8BitRegsToFloat(Y_OUT_LOW_ADDRESS, scaleToRadiansPerSecond)};
    const F32 zValue{i2cDevice.ReadTwo8BitRegsToFloat(Z_OUT_LOW_ADDRESS, scaleToRadiansPerSecond)};

    return MeasurementPtr{new GyroscopeMeasurement{timeStamp, xValue, yValue, zValue}};
}
