#include "unity.h"
#include <string.h>
#include "mock_initiate_hsit_log.h"
#include "mock_slave_connection.h"
#include "run_serial_hsit_master.h"
#include "mock_send_start_command.h"

#define EXPECTATION_DEFINED_BY_CALLBACK  NULL

#define SUCCESS_TO_SEND_START_COMMAND    0

static const char expectedMasterInitMessage[] = "Serial HSIT Master started\n\n";

static HsitResult verifyMasterInitMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedMasterInitMessage), "Wrong message!");
  return HSIT_SUCCESS;
}

void setUp(void)
{}

void tearDown(void)
{}

void test_runSerialHsitMasterShallInitiateHsitLogUsingTheRightInitMessage(void)
{
  initiateHsitLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, HSIT_SUCCESS);
  initiateHsitLog_StubWithCallback(verifyMasterInitMessage);
  connectToSlave_ExpectAndReturn(CONNECTION_SUCCESS);
  tryToSendStartCmdAndSleep_ExpectAndReturn(SUCCESS_TO_SEND_START_COMMAND);
  runSerialHsitMaster();
}
