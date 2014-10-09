

#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>

#include "i2c_slave.h"

#define I2C_BUFFER_SIZE (16)
#define I2C_INVALID_ADDRESS (0xFF)

volatile uint8_t dataBuffer[I2C_BUFFER_SIZE];
volatile uint8_t currentAddress;

void I2C_init(uint8_t address)
{
  TWAR = (address << 1);

  // Enable twi with interrupt
  TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWEN);
}

uint8_t I2C_readData(const uint8_t address)
{
  return dataBuffer[address];
}

void I2C_writeData(const uint8_t address, const uint8_t data)
{
  dataBuffer[address] = data;
}

ISR(TWI_vect)
{
  switch(TW_STATUS)
  {
  //Slave Receiver mode
  case TW_SR_SLA_ACK: //SLA+W received, ACK returned
    currentAddress = I2C_INVALID_ADDRESS;

    //Send ack
    TWCR |= _BV(TWINT) | _BV(TWEA);
    break;

  case TW_SR_DATA_ACK: //Data received

    if(currentAddress == I2C_INVALID_ADDRESS)
    {
      currentAddress = TWDR;

      //Send ack
      TWCR |= _BV(TWINT) | _BV(TWEA);
    }
    else
    {
      dataBuffer[currentAddress] = TWDR;
      ++currentAddress;

      //Send ack
      TWCR |= _BV(TWINT) | _BV(TWEA);
    }
    break;

  case TW_SR_STOP: //Stop condition

    TWCR |= _BV(TWINT) | _BV(TWEA);
    break;

    //Slave transmitter mode
  case TW_ST_SLA_ACK: //SLA+R received, ACK returned
    TWDR = dataBuffer[currentAddress];
    ++currentAddress;

    //Send ack
    TWCR |= _BV(TWINT) | _BV(TWEA);
    break;

  case TW_ST_DATA_ACK: //Data sent, ACK received
    TWDR = dataBuffer[currentAddress];
    ++currentAddress;

    //Send ack
    TWCR |= _BV(TWINT) | _BV(TWEA);
    break;

  case TW_ST_DATA_NACK: //Data sent, NACK received
    TWCR |= _BV(TWINT) | _BV(TWEA);
    break;

  case TW_ST_LAST_DATA: //Last data byte, ACK received
    TWCR |= _BV(TWINT) | _BV(TWEA);
    break;
  }
}
