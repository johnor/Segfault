/*
* This file defines the AccAndMagHandler class which handles
* I2C-communication with the accelerometer and magnetometer on the IMU-chip.
*/
#include <stdexcept>
#include <iostream>
#include <math.h>
#include <bitset>
#include "acc_and_mag_handler.h"
#include "../measurements.h"
#include "wiringPi/headers/wiringPiI2C.h"
#include "classes/logger.h"


const U8 LSM303D_ADDRESS   = 0x1d;
const U8 LSM303D_ID        = 0x49;

const U8 L3GD20H_WHO_AM_I		= 0x0f;
const U8 LSM303D_CTRL1			= 0x20;
const U8 LSM303D_CTRL2			= 0x21;
const U8 LSM303D_STATUS_A		= 0x27;
const U8 LSM303D_STATUS_ZYXADA	= (1 << 3);

const U8 LSM303D_OUT_X_L_A = 0x28;
const U8 LSM303D_OUT_X_H_A = 0x29;
const U8 LSM303D_OUT_Y_L_A = 0x2A;
const U8 LSM303D_OUT_Y_H_A = 0x2B;
const U8 LSM303D_OUT_Z_L_A = 0x2C;
const U8 LSM303D_OUT_Z_H_A = 0x2D;

const U8 LSM303D_ACCEL_SAMPLERATE_50 = 5; // Sample rate 50 hz
const U8 LSM303D_ACCEL_FSR_8         = 3; // Full scale selection +- 8g
const U8 LSM303D_ACCEL_LPF_50        = 3; // Low pass filter 50hz


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

	// For testing
	measurements.emplace_back(new CompassMeasurement{ 1.f, 2.f, 3.f });

	if (HasNewAccelerometerMeasurement())
	{
		Logger::Log(LogLevel::Info) << "New accelerometer measurement available";

		measurements.push_back(GetNextAccelerometerMeasurement());
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
	if (i2cDevice.ReadReg8(L3GD20H_WHO_AM_I) != LSM303D_ID)
	{
		throw std::runtime_error("AccAndMagHandler::SetUpRegisters(): Wrong id read");
	}

	// Init ctrl1
	unsigned char ctrl1{ 0 };
	ctrl1 = LSM303D_ACCEL_SAMPLERATE_50 << 4; // Set data rate
	ctrl1 |= 0x07; //Enable z, x and y axes
	i2cDevice.WriteReg8(LSM303D_CTRL1, ctrl1);

	// Init ctrl2
	unsigned char ctrl2{ 0 };
	accelerometerScale = 0.000244f;  // g/LSB from table 3, page 10 in data sheet
	ctrl2 = LSM303D_ACCEL_LPF_50 << 6; // Set anti-alias filter bandwidth
	ctrl2 |= LSM303D_ACCEL_FSR_8 << 3; // Select full scale
	i2cDevice.WriteReg8(LSM303D_CTRL2, ctrl2);
}

bool AccAndMagHandler::HasNewAccelerometerMeasurement() const
{
	// read status
	int status = i2cDevice.ReadReg8(LSM303D_STATUS_A);
	Logger::Log(LogLevel::Debug) << "Status: " << (std::bitset<8>)status;

	return status & LSM303D_STATUS_ZYXADA ? true : false;
}

MeasurementPtr AccAndMagHandler::GetNextAccelerometerMeasurement() const
{
	Logger::Log(LogLevel::Debug) << "Reading measurement from accelerometer";
	F32 xAcc = i2cDevice.Read16BitToFloat(LSM303D_OUT_X_L_A, accelerometerScale);
	F32 yAcc = i2cDevice.Read16BitToFloat(LSM303D_OUT_Y_L_A, accelerometerScale);
	F32 zAcc = i2cDevice.Read16BitToFloat(LSM303D_OUT_Z_L_A, accelerometerScale);

	F32 sum = sqrt(xAcc*xAcc + yAcc*yAcc + zAcc*zAcc);
	Logger::Log(LogLevel::Debug) << "Sum: " << sum;

	return MeasurementPtr{ new AccelerometerMeasurement{ xAcc, yAcc, zAcc } };
}
