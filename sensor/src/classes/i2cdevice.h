#ifndef I2C_DEVICE_H_
#define I2C_DEVICE_H_

#include <string>
#include "headers/numeric_typedefs.h"

/*
* Wrapper class around the WiringPi lib handling
* I2C communication with various devices.
*/
class I2CDevice
{
public:
    explicit I2CDevice(const U8 address);

    U8 Read8BitReg(const U8 reg) const;
    void WriteReg8(const U8 reg, const U8 data) const;

    U16 Read16BitReg(const U8 reg) const;
    void WriteReg16(const U8 reg, const U16 data) const;

    F32 ReadTwo8BitRegsToFloat(const U8 lowReg, const F32 scaling) const;
    F32 ReadThree8BitRegsToFloat(const U8 lowReg, const F32 scaling) const;
private:
    I2CDevice(const I2CDevice&) = delete;
    I2CDevice& operator=(const I2CDevice&) = delete;
    static std::string Convert8BitValueToHexString(const U8 value);
    static std::string Convert16BitValueToHexString(const U16 value);

    int fileDescriptor;
};

#endif
