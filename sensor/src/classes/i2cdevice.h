
#ifndef I2CDEVICE_H_
#define I2CDEVICE_H_

#include "headers/numeric_typedefs.h"

class I2CDevice
{
public:
	I2CDevice() = default;
	~I2CDevice() = default;

	void Init(const U8 address);
	bool IsOpen() const;

	U8 ReadReg8(const U8 reg);
	F32 Read16BitToFloat(const U8 reg, const F32 scaling);
	void WriteReg8(const U8 reg, const U8 data);

private:
	static const int deviceNotOpen = -1;

	I2CDevice(const I2CDevice&) = delete;
	I2CDevice& operator=(const I2CDevice&) = delete;

	int fd{ deviceNotOpen };
};

#endif

