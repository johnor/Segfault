#include <sstream>
#include "wiringPi/wiringPiI2C.h"

#include "../headers/exceptions.h"
#include "common/src/logger.h"

#include "i2cdevice.h"

I2CDevice::I2CDevice(const U8 address)
{
    Logger::Log() << "Opening i2c device at address: " << Convert8BitValueToHexString(address);

    /* Try to connect to i2c-device using the wiring pi library. */
    fileDescriptor = wiringPiI2CSetup(address);

    if (fileDescriptor < 0)
    {
        const std::string message{"I2CDevice(): Could not initialize connection to address: " + Convert8BitValueToHexString(address)};
        throw I2CException{message};
    }
}

U8 I2CDevice::Read8BitReg(const U8 reg) const
{
    const int result{wiringPiI2CReadReg8(fileDescriptor, reg)};

    if (result < 0)
    {
        const std::string message{"Could not read from device at address " +
                                  Convert8BitValueToHexString(reg)};
        throw I2CException{message};
    }

    return static_cast<U8>(result);
}

void I2CDevice::WriteReg8(const U8 reg, const U8 data) const
{
    const int result{wiringPiI2CWriteReg8(fileDescriptor, reg, data)};
    if (result < 0)
    {
        const std::string message{"Could not write data: " +
                                  Convert8BitValueToHexString(data) +
                                  " to register: " +
                                  Convert8BitValueToHexString(reg)};
        throw I2CException{message};
    }
}

U16 I2CDevice::Read16BitReg(const U8 reg) const
{
    const int result{wiringPiI2CReadReg16(fileDescriptor, reg)};

    if (result < 0)
    {
        const std::string message{"Could not read from device at address " + 
                                  Convert8BitValueToHexString(reg)};
        throw I2CException{message};
    }

    return static_cast<U16>(result);
}

void I2CDevice::WriteReg16(const U8 reg, const U16 data) const
{
    const int result{wiringPiI2CWriteReg8(fileDescriptor, reg, data)};
    if (result < 0)
    {
        std::string message{"Could not write data: " +
                            Convert16BitValueToHexString(data) +
                            " to register: " +
                            Convert8BitValueToHexString(reg)};
        throw I2CException{message};
    }
}

F32 I2CDevice::ReadTwo8BitRegsToFloat(const U8 lowReg, const F32 scaling) const
{
    const U8 highReg{static_cast<U8>(lowReg + 1u)};

    const U8 lowByte{Read8BitReg(lowReg)};
    const U8 highByte{Read8BitReg(highReg)};

    const S16 sixteenBitTwosComplement{static_cast<S16>((highByte << 8) | lowByte)};

    return static_cast<F32>(sixteenBitTwosComplement) * scaling;
}

F32 I2CDevice::ReadThree8BitRegsToFloat(const U8 lowReg, const F32 scaling) const
{
    const U8 middleReg{static_cast<U8>(lowReg + 1u)};
    const U8 highReg{static_cast<U8>(lowReg + 2u)};

    const U8 lowByte{Read8BitReg(lowReg)};
    const U8 middleByte{Read8BitReg(middleReg)};
    const U8 highByte{Read8BitReg(highReg)};

    const S32 twentyFourBitTwosComplement{static_cast<S32>((highByte << 16) | (middleByte << 8) | lowByte)};

    return static_cast<F32>(twentyFourBitTwosComplement) * scaling;
}

std::string I2CDevice::Convert8BitValueToHexString(const U8 value)
{
    std::ostringstream stream;
    stream << std::hex << std::showbase << static_cast<S32>(value);
    return stream.str();
}

std::string I2CDevice::Convert16BitValueToHexString(const U16 value)
{
    std::ostringstream stream;
    stream << std::hex << std::showbase << static_cast<S32>(value);
    return stream.str();
}
