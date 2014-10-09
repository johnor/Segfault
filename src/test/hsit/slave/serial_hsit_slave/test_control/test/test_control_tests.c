#include "unity.h"
#include "test_control.h"
#include "mock_wait_for_start.h"
#include "mock_log.h"
#include "mock_log_start_command.h"
#include "mock_serial_port.h"

void setUp(void)
{}

void tearDown(void)
{}

void test_awaitTestStartCommandShallCall3sWaitLoop(void)
{
  writeStartCommandResultToLog_Ignore();
  wait3sForTestStartCommand_ExpectAndReturn(NOTHING_RECEIVED);
  (void)awaitTestStartCommand();
}

void test_awaitTestStartCommandReturnValueWhenReceivingTestStartCommand(void)
{
  writeStartCommandResultToLog_Ignore();
  wait3sForTestStartCommand_IgnoreAndReturn(START_COMMAND_RECEIVED);
  TestStartDecision result = awaitTestStartCommand();
  TEST_ASSERT_EQUAL_MESSAGE(TEST_GOOD_TO_GO, result, "Wrong return value from 'awaitTestStartCommand()' "
                                                                 "when having received the start command!");
}

void test_awaitTestStartCommandReturnValueWhenReceivingInvalidCommand(void)
{
  writeStartCommandResultToLog_Ignore();
  wait3sForTestStartCommand_IgnoreAndReturn(INVALID_COMMAND_RECEIVED);
  TestStartDecision result = awaitTestStartCommand();
  TEST_ASSERT_EQUAL_MESSAGE(TEST_NO_GO, result, "Wrong return value from 'awaitTestStartCommand()' "
                                                                     "when having received invalid command!");
}

void test_awaitTestStartCommandReturnValueWhenReceivingNothing(void)
{
  writeStartCommandResultToLog_Ignore();
  wait3sForTestStartCommand_IgnoreAndReturn(NOTHING_RECEIVED);
  TestStartDecision result = awaitTestStartCommand();
  TEST_ASSERT_EQUAL_MESSAGE(TEST_NO_GO, result, "Wrong return value from 'awaitTestStartCommand()' "
                                                                     "when having received nothing!");
}

void test_awaitTestStartCommandShallWriteStartCommandResultToLog(void)
{
  writeStartCommandResultToLog_Expect(START_COMMAND_RECEIVED);
  wait3sForTestStartCommand_IgnoreAndReturn(START_COMMAND_RECEIVED);
  (void)awaitTestStartCommand();
}

void test_runTestShallInitializeSerialPort(void)
{
  initializeSerialPort_ExpectAndReturn(SERIAL_PORT_SUCCESS);
  serialPortTransmit_IgnoreAndReturn(SERIAL_PORT_SUCCESS);
  closeSerialPort_Ignore();
  runTest();
}

void test_runTestShallReturnTestMalfunctionIfSerialPortFailsToInitialize(void)
{
  initializeSerialPort_IgnoreAndReturn(SERIAL_PORT_FAILURE);
  TEST_ASSERT_EQUAL_MESSAGE(TEST_MALFUNCTION, runTest(), "Invalid return value from 'runTest()'!");
}

void test_runTestShallTransmitTheLetterH(void)
{
  initializeSerialPort_IgnoreAndReturn(SERIAL_PORT_SUCCESS);
  serialPortTransmit_ExpectAndReturn('H', SERIAL_PORT_SUCCESS);
  closeSerialPort_Ignore();
  runTest();
}

void test_runTestShallReturnTestCompleteIfSerialPortTransmissionSucceeds(void)
{
  initializeSerialPort_IgnoreAndReturn(SERIAL_PORT_SUCCESS);
  serialPortTransmit_IgnoreAndReturn(SERIAL_PORT_SUCCESS);
  closeSerialPort_Ignore();
  TEST_ASSERT_EQUAL_MESSAGE(TEST_COMPLETE, runTest(), "Invalid return value from 'runTest()'!");
}

void test_runTestShallCloseSerialPortAfterCompletedTest(void)
{
  initializeSerialPort_IgnoreAndReturn(SERIAL_PORT_SUCCESS);
  serialPortTransmit_IgnoreAndReturn(SERIAL_PORT_SUCCESS);
  closeSerialPort_Expect();
  (void)runTest();
}

void test_runTestShallReturnTestMalfunctionIfSerialPortTransmissionFails(void)
{
  initializeSerialPort_IgnoreAndReturn(SERIAL_PORT_SUCCESS);
  serialPortTransmit_IgnoreAndReturn(SERIAL_PORT_FAILURE);
  closeSerialPort_Ignore();
  TEST_ASSERT_EQUAL_MESSAGE(TEST_MALFUNCTION, runTest(), "Invalid return value from 'runTest()'!");
}

void test_runTestShallCloseSerialPortAfterTestMalfunction(void)
{
  initializeSerialPort_IgnoreAndReturn(SERIAL_PORT_SUCCESS);
  serialPortTransmit_IgnoreAndReturn(SERIAL_PORT_FAILURE);
  closeSerialPort_Expect();
  runTest();
}
