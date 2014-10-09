#include "serial_port.h"
#include "type.h"
#include "system_uart.h"

static bool isInitialized = false;

SerialPortResult initializeSerialPort(void)
{
  if (isInitialized)
  {
    return SERIAL_PORT_FAILURE;
  }

  if (openUartFileStream() != UART_SUCCESS)
  {
    return SERIAL_PORT_FAILURE;
  }

  if (setUpUartFor115kbps8N1() != UART_SUCCESS)
  {
    return SERIAL_PORT_FAILURE;
  }

  isInitialized = true;
  return SERIAL_PORT_SUCCESS;
}

SerialPortResult serialPortTransmit(uint8_t dataToTransmit)
{
  if (uartTransmitByte(dataToTransmit) != UART_SUCCESS)
  {
    return SERIAL_PORT_FAILURE;
  }
  return SERIAL_PORT_SUCCESS;
}

void closeSerialPort(void)
{
  (void)closeUartFileStream();
  isInitialized = false;
}
