#ifndef SYSTEM_I2C_H_
#define SYSTEM_I2C_H_

#include "type.h"

bool i2c_Init(int devId);

int i2c_Read8(const int reg);
int i2c_Read16(const int reg);

int i2c_Write8(const int reg, const int data);
int i2c_Write16(const int reg, const int data);

#endif
