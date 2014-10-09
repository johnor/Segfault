#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H



void I2C_init(uint8_t address);
uint8_t I2C_readData(const uint8_t address);
void I2C_writeData(const uint8_t address, const uint8_t data);

#endif // I2C_SLAVE_H
