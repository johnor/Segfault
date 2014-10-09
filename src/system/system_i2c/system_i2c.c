#include <wiringPiI2C.h>
#include "type.h"
#include "system_i2c.h"

static int i2cHandle = -1;


bool i2c_Init(int devId)
{
  i2cHandle = wiringPiI2CSetup(devId);
  if (i2cHandle < 0)
  {
    return false;
  }
  return true;
}

int i2c_Read8(const int reg)
{
  return wiringPiI2CReadReg8(i2cHandle, reg);
}

int i2c_Read16(const int reg)
{
  return wiringPiI2CReadReg16(i2cHandle, reg);
}

int i2c_Write8(const int reg, const int data)
{
  return wiringPiI2CWriteReg8(i2cHandle, reg, data);
}

int i2c_Write16(const int reg, const int data)
{
  return wiringPiI2CWriteReg16(i2cHandle, reg, data);
}
