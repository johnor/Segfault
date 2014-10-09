#include "test_control.h"
#include "wait_for_start.h"
#include "log_start_command.h"
#include "serial_port.h"

TestStartDecision awaitTestStartCommand(void)
{
  StartCommandResult startCommandResult = wait3sForTestStartCommand();

  writeStartCommandResultToLog(startCommandResult);

  if (startCommandResult == START_COMMAND_RECEIVED)
  {
    return TEST_GOOD_TO_GO;
  }
  return TEST_NO_GO;
}

TestResult runTest(void)
{
  if (initializeSerialPort() != SERIAL_PORT_SUCCESS)
  {
    return TEST_MALFUNCTION;
  }
  if (serialPortTransmit('H') == SERIAL_PORT_SUCCESS)
  {
    closeSerialPort();
    return TEST_COMPLETE;
  }

  closeSerialPort();
  return TEST_MALFUNCTION;
}
