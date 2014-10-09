#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include "type.h"

typedef enum {
  SERIAL_PORT_SUCCESS,
  SERIAL_PORT_FAILURE
} SerialPortResult;

SerialPortResult initializeSerialPort(void);
SerialPortResult serialPortTransmit(uint8_t dataToTransmit);
void closeSerialPort(void);

#endif /* SERIALPORT_H_ */
