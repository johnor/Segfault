/*
* This file defines the AccAndMagHandler class which handles
* I2C-communication with the accelerometer and magnetometer on the IMU-chip.
*/
#include "acc_and_mag_handler.h"

#include <iostream>
#include <math.h>
#include <bitset>

#include "../measurements.h"
#include "classes/logger.h"
#include "../../headers/exceptions.h"


const U8 LSM303D_ADDRESS        = 0x1d;
const U8 LSM303D_ID             = 0x49;
const U8 L3GD20H_WHO_AM_I        = 0x0f;

/* accelerometer defines */
const U8 LSM303D_CTRL1            = 0x20;
const U8 LSM303D_CTRL2            = 0x21;
const U8 LSM303D_STATUS_A        = 0x27;
const U8 LSM303D_STATUS_ZYXADA    = (1u << 3);

const U8 LSM303D_OUT_X_L_A = 0x28;
const U8 LSM303D_OUT_X_H_A = 0x29;
const U8 LSM303D_OUT_Y_L_A = 0x2A;
const U8 LSM303D_OUT_Y_H_A = 0x2B;
const U8 LSM303D_OUT_Z_L_A = 0x2C;
const U8 LSM303D_OUT_Z_H_A = 0x2D;

const U8 LSM303D_ACCEL_SAMPLERATE_50 = 5u; // Sample rate 50 hz
const U8 LSM303D_ACCEL_FSR_8         = 3u; // Full scale selection +- 8g
const U8 LSM303D_ACCEL_LPF_50        = 3u; // Low pass filter 50hz

/* magnetometer defines */
const U8 LSM303D_CTRL5         = 0x24;
const U8 LSM303D_CTRL6         = 0x25;
const U8 LSM303D_CTRL7         = 0x26;
const U8 LSM303D_STATUS_M      = 0x07;
const U8 LSM303D_STATUS_ZYXMDA = (1u << 3);

const U8 LSM303D_OUT_X_L_M     = 0x08;
const U8 LSM303D_OUT_X_H_M     = 0x09;
const U8 LSM303D_OUT_Y_L_M     = 0x0a;
const U8 LSM303D_OUT_Y_H_M     = 0x0b;
const U8 LSM303D_OUT_Z_L_M     = 0x0c;
const U8 LSM303D_OUT_Z_H_M     = 0x0d;

const U8 LSM303D_COMPASS_SAMPLERATE_50 = 4u;
const U8 LSM303D_COMPASS_FSR_2         = 0u;


AccAndMagHandler::AccAndMagHandler()
try
: i2cDevice(LSM303D_ADDRESS)
{
    SetUpRegisters();
}
catch (std::runtime_error &e)
{
    Logger::Log(LogLevel::Error) << "AccAndMagHandler::AccAndMagHandler: " << e.what();
}


MeasurementBatch AccAndMagHandler::GetMeasurements() const
{
    MeasurementBatch measurements;

    /*if (HasNewAccelerometerMeasurement())
    {
    Logger::Log(LogLevel::Info) << "New accelerometer measurement available";

    measurements.push_back(GetNextAccelerometerMeasurement());
    }*/

    if (HasNewMagnetometerMeasurement())
    {
        Logger::Log(LogLevel::Info) << "New magnetometer measurement available";

        measurements.push_back(GetNextMagnetometerMeasurement());
    }

    if (HasNewMagnetometerMeasurement())
    {
        Logger::Log(LogLevel::Info) << "New magnetometer measurement available";

        measurements.push_back(GetNextMagnetometerMeasurement());
    }


    return measurements;
}

bool AccAndMagHandler::HasAvailableMeasurements() const
{
    /* For testing purposes only */
    return true;
}


void AccAndMagHandler::SetUpRegisters()
{
    Logger::Log(LogLevel::Info) << "Initializing i2c for acc and mag handler";
    if (i2cDevice.Read8BitReg(L3GD20H_WHO_AM_I) != LSM303D_ID)
    {
        throw I2CException("AccAndMagHandler::SetUpRegisters(): Wrong id read");
    }

    /* accelerometer registers */
    // Init ctrl1
    U8 ctrl1{ 0 };
    ctrl1 = LSM303D_ACCEL_SAMPLERATE_50 << 4; // Set data rate
    ctrl1 |= 0x07; //Enable z, x and y axes
    i2cDevice.WriteReg8(LSM303D_CTRL1, ctrl1);

    // Init ctrl2
    U8 ctrl2{ 0 };
    accelerometerScale = 0.000244f;  // g/LSB from table 3, page 10 in data sheet
    ctrl2 = LSM303D_ACCEL_LPF_50 << 6; // Set anti-alias filter bandwidth
    ctrl2 |= LSM303D_ACCEL_FSR_8 << 3; // Select full scale
    i2cDevice.WriteReg8(LSM303D_CTRL2, ctrl2);


    /* magnetometer registers */
    // Init ctrl5
    U8 ctrl5{ 0 };
    ctrl5 = LSM303D_COMPASS_SAMPLERATE_50 << 2; // Set data rate
    i2cDevice.WriteReg8(LSM303D_CTRL5, ctrl5);

    // Init ctrl6
    U8 ctrl6{ 0 };
    ctrl6 = 0; // Select full scale +- 2 gauss
    compassScale = 0.00008f; // gauss/LSB from table 3, page 10 in data sheet
    i2cDevice.WriteReg8(LSM303D_CTRL6, ctrl6);

    // Init ctrl7
    U8 ctrl7{ 0 };
    ctrl7 = 0x60;
    i2cDevice.WriteReg8(LSM303D_CTRL7, ctrl7);
}

bool AccAndMagHandler::HasNewAccelerometerMeasurement() const
{
    // read status
    const U8 status = i2cDevice.Read8BitReg(LSM303D_STATUS_A);
    Logger::Log(LogLevel::Debug) << "Status: " << (std::bitset<8>)status;

    return status & LSM303D_STATUS_ZYXADA ? true : false;
}

bool AccAndMagHandler::HasNewMagnetometerMeasurement() const
{
    // read status
    const U8 status = i2cDevice.Read8BitReg(LSM303D_STATUS_M);
    Logger::Log(LogLevel::Debug) << "Status: " << (std::bitset<8>)status;

    return status & LSM303D_STATUS_ZYXMDA ? true : false;
}

MeasurementPtr AccAndMagHandler::GetNextAccelerometerMeasurement() const
{
    Logger::Log(LogLevel::Debug) << "Reading measurement from accelerometer";
    const F32 xAcc = i2cDevice.ReadTwo8BitRegsToFloat(LSM303D_OUT_X_L_A, accelerometerScale);
    const F32 yAcc = i2cDevice.ReadTwo8BitRegsToFloat(LSM303D_OUT_Y_L_A, accelerometerScale);
    const F32 zAcc = i2cDevice.ReadTwo8BitRegsToFloat(LSM303D_OUT_Z_L_A, accelerometerScale);

    const F32 sum = sqrt(xAcc*xAcc + yAcc*yAcc + zAcc*zAcc);
    Logger::Log(LogLevel::Debug) << "Sum: " << sum;

    return MeasurementPtr{ new AccelerometerMeasurement{ 0, xAcc, yAcc, zAcc } };
}

MeasurementPtr AccAndMagHandler::GetNextMagnetometerMeasurement() const
{
    Logger::Log(LogLevel::Debug) << "Reading measurement from magnetometer";
    const F32 xComp = i2cDevice.ReadTwo8BitRegsToFloat(LSM303D_OUT_X_L_M, compassScale);
    const F32 yComp = i2cDevice.ReadTwo8BitRegsToFloat(LSM303D_OUT_Y_L_M, compassScale);
    const F32 zComp = i2cDevice.ReadTwo8BitRegsToFloat(LSM303D_OUT_Z_L_M, compassScale);

    Logger::Log(LogLevel::Debug) << "xComp: " << xComp;
    Logger::Log(LogLevel::Debug) << "yComp: " << yComp;
    Logger::Log(LogLevel::Debug) << "zComp: " << zComp;

    return MeasurementPtr{ new CompassMeasurement{ 0, xComp, yComp, zComp } };
}
