/*
* This file defines the AccAndMagHandler class which handles
* I2C-communication with the accelerometer and magnetometer on the IMU-chip.
*
* The accelerometer and magnetometer will operate in bypass mode, meaning that
* each new measurement will overwrite the previous one.
*
* Block data update is enabled, meaning that the
* output registers cannot be updated until both
* output registers have been read sequentially.
*
* Accelerometer data rate is set to 100 Hz.
* Accelerometer scale is +- 4g.
* The accelerometer anti-alias filter is enabled with bandwidth 50 Hz.
* The accelerometer high-pass filter is disabled.
* Output is scaled to m/s^2.
*
* Magnetometer data rate is set to 100 Hz.
* Magnetometer scale is +- 2 Gauss.
* The magnetometer high resolution mode is enabled.
* Continuouos conversion mode is enabled.
* Output is scaled to T.
*
* The temperature sensor is disabled.
*
*/

#include "../../headers/exceptions.h"
#include "../../interfaces/clock.h"
#include "../measurements.h"

#include "acc_and_mag_handler.h"

/* I2C and who am I */
const U8 I2C_ADDRESS_SA0_HIGH = 0x1dU;
const U8 WHO_AM_I_ADDRESS = 0x0fU;
const U8 WHO_AM_I_DATA = 0x49U;

/* Accelerometer specifics */
const U8 ACC_STATUS_ADDRESS = 0x27U;
const U8 ACC_NDA_BITMASK = (1u << 3);
const U8 ACC_X_OUT_LOW_ADDRESS = 0x28U;
const U8 ACC_Y_OUT_LOW_ADDRESS = 0x2aU;
const U8 ACC_Z_OUT_LOW_ADDRESS = 0x2cU;

/* Magnetometer specifics */
const U8 MAG_STATUS_ADDRESS = 0x07U;
const U8 MAG_NDA_BITMASK = (1u << 3);
const U8 MAG_X_OUT_LOW_ADDRESS = 0x08U;
const U8 MAG_Y_OUT_LOW_ADDRESS = 0x0aU;
const U8 MAG_Z_OUT_LOW_ADDRESS = 0x0cU;

/* Control registers */
const U8 CTRL_1_ADDRESS = 0x20U;
const U8 CTRL_1_DATA = 0x6fU; /* Acc data rate 100 Hz, BDU enabled, all acc axes enabled. */

const U8 CTRL_2_ADDRESS = 0x21U;
const U8 CTRL_2_DATA = 0xc8U; /* Acc AA-filter bw 50 Hz, full-scale selection +- 4g */

const U8 CTRL_5_ADDRESS = 0x24U;
const U8 CTRL_5_DATA = 0x74U; /* Temp sensor disabled, mag high resolution enabled, mag data rate 100 Hz */

const U8 CTRL_6_ADDRESS = 0x25U;
const U8 CTRL_6_DATA = 0u; /* Mag full-scale +- 2 Gauss. */

const U8 CTRL_7_ADDRESS = 0x26U;
const U8 CTRL_7_DATA = 0u; /* Acc high-pass filter disabled, mag continuous conversion mode enabled. */

/* Scale factors */
const F32 gravitationalAcceleration = 9.81f;
const F32 accelerometerScaleFactor = 0.000122f * gravitationalAcceleration; /* 0.122 mg/LSB at +- 4g full-scale */

const F32 gaussToTesla = 0.0001f;
const F32 magnetometerScaleFactor = 0.00008f * gaussToTesla; /* 0.080 mGauss/LSB at +- 2 Gauss full-scale */

AccAndMagHandler::AccAndMagHandler(ClockPtr clock)
    : i2cDevice{I2C_ADDRESS_SA0_HIGH}, clock{clock}
{
    SetUpRegisters();
}

MeasurementBatch AccAndMagHandler::GetMeasurements() const
{
    MeasurementBatch measurements;

    if (HasNewAccelerometerMeasurement())
    {
        measurements.push_back(GetNextAccelerometerMeasurement());
    }

    if (HasNewMagnetometerMeasurement())
    {
        measurements.push_back(GetNextMagnetometerMeasurement());
    }

    return measurements;
}

bool AccAndMagHandler::HasAvailableMeasurements() const
{
    return HasNewAccelerometerMeasurement() || HasNewMagnetometerMeasurement();
}

void AccAndMagHandler::SetUpRegisters()
{
    if (i2cDevice.Read8BitReg(WHO_AM_I_ADDRESS) != WHO_AM_I_DATA)
    {
        throw I2CException("AccAndMagHandler::SetUpRegisters(): Wrong WHO_AM_I value read.");
    }

    i2cDevice.WriteReg8(CTRL_1_ADDRESS, CTRL_1_DATA);

    i2cDevice.WriteReg8(CTRL_2_ADDRESS, CTRL_2_DATA);

    i2cDevice.WriteReg8(CTRL_5_ADDRESS, CTRL_5_DATA);

    i2cDevice.WriteReg8(CTRL_6_ADDRESS, CTRL_6_DATA);

    i2cDevice.WriteReg8(CTRL_7_ADDRESS, CTRL_7_DATA);
}

bool AccAndMagHandler::HasNewAccelerometerMeasurement() const
{
    const U8 status{i2cDevice.Read8BitReg(ACC_STATUS_ADDRESS)};
    return (status & ACC_NDA_BITMASK) ? true : false;
}

bool AccAndMagHandler::HasNewMagnetometerMeasurement() const
{
    const U8 status{i2cDevice.Read8BitReg(MAG_STATUS_ADDRESS)};
    return (status & MAG_NDA_BITMASK) ? true : false;
}

MeasurementPtr AccAndMagHandler::GetNextAccelerometerMeasurement() const
{
    const F32 xAcc{i2cDevice.ReadTwo8BitRegsToFloat(ACC_X_OUT_LOW_ADDRESS, accelerometerScaleFactor)};
    const F32 yAcc{i2cDevice.ReadTwo8BitRegsToFloat(ACC_Y_OUT_LOW_ADDRESS, accelerometerScaleFactor)};
    const F32 zAcc{i2cDevice.ReadTwo8BitRegsToFloat(ACC_Z_OUT_LOW_ADDRESS, accelerometerScaleFactor)};

    return MeasurementPtr{new AccelerometerMeasurement{clock->GetTimeStampInMicroSecs(), xAcc, yAcc, zAcc }};
}

MeasurementPtr AccAndMagHandler::GetNextMagnetometerMeasurement() const
{
    const F32 xMag{i2cDevice.ReadTwo8BitRegsToFloat(MAG_X_OUT_LOW_ADDRESS, magnetometerScaleFactor)};
    const F32 yMag{i2cDevice.ReadTwo8BitRegsToFloat(MAG_Y_OUT_LOW_ADDRESS, magnetometerScaleFactor)};
    const F32 zMag{i2cDevice.ReadTwo8BitRegsToFloat(MAG_Z_OUT_LOW_ADDRESS, magnetometerScaleFactor)};

    return MeasurementPtr{new CompassMeasurement{clock->GetTimeStampInMicroSecs(), xMag, yMag, zMag}};
}
