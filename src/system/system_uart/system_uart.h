#ifndef SYSTEM_UART_H_
#define SYSTEM_UART_H_

#include "type.h"

typedef enum
{
  UART_SUCCESS,
  UART_FAILURE
} UartResult;

UartResult openUartFileStream(void);
UartResult setUpUartFor115kbps8N1(void);
UartResult closeUartFileStream(void);
UartResult uartTransmitByte(uint8_t byteToTransmit);

#endif /* SYSTEM_UART_H_ */
