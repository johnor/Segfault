#include <stdexcept>
#include "i2cdevice.h"
#include "wiringPi/headers/wiringPiI2C.h"
#include "logger.h"

void I2CDevice::Init(const U8 address)
{
	Logger::Log(LogLevel::Debug) << "Opening i2c device at address: " << std::hex << static_cast<int>(address);
	fd = wiringPiI2CSetup(address);

	if (fd == deviceNotOpen)
	{
		throw std::runtime_error("I2CDevice::Init: Could not open i2c device");
	}
}

bool I2CDevice::IsOpen() const
{
	return fd != deviceNotOpen;
}

U8 I2CDevice::ReadReg8(const U8 reg) const
{
	//Logger::Log(LogLevel::Debug) << "ReadReg8: Reading data from register: " << std::hex << static_cast<int>(reg);
	int result = wiringPiI2CReadReg8(fd, reg);
	if (result < 0)
	{
		throw std::runtime_error("Could not read from device");
	}
	//Logger::Log(LogLevel::Debug) << "Read data: " << std::hex << static_cast<int>(result);
	return static_cast<U8>(result);
}


F32 I2CDevice::Read16BitToFloat(const U8 reg, const F32 scaling) const
{
	//Logger::Log(LogLevel::Debug) << "Read16BitToFloat: Reading data from register: " << std::hex << static_cast<int>(reg);
	int low = ReadReg8(reg);
	int high = ReadReg8(reg + 1);

	//Logger::Log(LogLevel::Info) << "Read low byte: " << std::hex << low;
	//Logger::Log(LogLevel::Info) << "Read high byte: " << std::hex << high;

	S16 reg16 = (S16)(((U16)high << 8) | (U16)low);
	return static_cast<F32>(reg16) * scaling;
}


void I2CDevice::WriteReg8(const U8 reg, const U8 data) const
{
	//Logger::Log(LogLevel::Debug) << "WriteReg8: Writing: " << std::hex << static_cast<int>(data) << " to register: " << std::hex << static_cast<int>(reg);
	int result = wiringPiI2CWriteReg8(fd, reg, data);
	if (result < 0)
	{
		throw std::runtime_error("Could not write to device");
	}
}
