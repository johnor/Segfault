#include "unity.h"
#include "serial_port.h"
#include "mock_system_uart.h"

#define BYTE_TO_TRANSMIT  0x55
#define UART_FILE_STREAM    43

void setUp(void)
{
}

void tearDown(void)
{
  closeUartFileStream_IgnoreAndReturn(UART_SUCCESS);
  closeSerialPort();
}

void test_initializeSerialPortShallOpenUartFileStream(void)
{
  openUartFileStream_ExpectAndReturn(UART_SUCCESS);
  setUpUartFor115kbps8N1_IgnoreAndReturn(UART_SUCCESS);
  initializeSerialPort();
}

void test_initializeSerialPortShallFailIfFailingToOpenUartFileStream(void)
{
  openUartFileStream_IgnoreAndReturn(UART_FAILURE);
  TEST_ASSERT_EQUAL_MESSAGE(SERIAL_PORT_FAILURE, initializeSerialPort(), "'initializeSerialPort()' shall fail if "
                                                                         "failing to open UART file stream!");
}

void test_initializeSerialPortShallSetUpUartFor115kbps8N1Operation(void)
{
  openUartFileStream_IgnoreAndReturn(UART_SUCCESS);
  setUpUartFor115kbps8N1_ExpectAndReturn(UART_SUCCESS);
  initializeSerialPort();
}

void test_initializeSerialPortShallFailIfFailingToSetUpUart(void)
{
  openUartFileStream_IgnoreAndReturn(UART_SUCCESS);
  setUpUartFor115kbps8N1_IgnoreAndReturn(UART_FAILURE);
  TEST_ASSERT_EQUAL_MESSAGE(SERIAL_PORT_FAILURE, initializeSerialPort(), "'initializeSerialPort()' shall fail if "
                                                                         "failing to set up UART!");
}

void test_initializeSerialPortShallFailIfCalledWhenAlreadyInitialized(void)
{
  openUartFileStream_ExpectAndReturn(UART_SUCCESS);
  setUpUartFor115kbps8N1_ExpectAndReturn(UART_SUCCESS);
  (void)initializeSerialPort();
  SerialPortResult result = initializeSerialPort();
  TEST_ASSERT_EQUAL_MESSAGE(SERIAL_PORT_FAILURE, result, "'initializeSerialPort()' shall fail if "
                                                                         "called when port is already initialized!");
}

void test_initializeSerialPortShallSucceedIfUartInitializationSucceeds(void)
{
  openUartFileStream_ExpectAndReturn(UART_SUCCESS);
  setUpUartFor115kbps8N1_ExpectAndReturn(UART_SUCCESS);
  TEST_ASSERT_EQUAL_MESSAGE(SERIAL_PORT_SUCCESS, initializeSerialPort(), "'initializeSerialPort()' shall succeed if "
                                                                         "UART initialization succeeds!");
}

void test_serialPortTransmitShallUseUartBytewiseTransmit(void)
{
  uartTransmitByte_ExpectAndReturn(BYTE_TO_TRANSMIT, UART_SUCCESS);
  serialPortTransmit(BYTE_TO_TRANSMIT);
}

void test_serialPortTransmitShallFailIfUartTransmissionFails(void)
{
  uartTransmitByte_ExpectAndReturn(BYTE_TO_TRANSMIT, UART_FAILURE);
  TEST_ASSERT_EQUAL_MESSAGE(SERIAL_PORT_FAILURE, serialPortTransmit(BYTE_TO_TRANSMIT),
                            "'serialPortTransmit()' shall fail if UART transmission fails!");
}

void test_serialPortTransmitShallSucceedIfUartTransmissionSucceeds(void)
{
  uartTransmitByte_ExpectAndReturn(BYTE_TO_TRANSMIT, UART_SUCCESS);
  TEST_ASSERT_EQUAL_MESSAGE(SERIAL_PORT_SUCCESS, serialPortTransmit(BYTE_TO_TRANSMIT),
                            "'serialPortTransmit()' shall succeed if UART transmission succeeds!");
}

void test_closeSerialPortShallCloseUartFileStream(void)
{
  closeUartFileStream_ExpectAndReturn(UART_SUCCESS);
  closeSerialPort();
}
