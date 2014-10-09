#include "unity.h"
#include "run_serial_hsit_master.h"
#include "mock_initiate_hsit_log.h"
#include "mock_slave_connection.h"
#include "mock_send_start_command.h"
#include "mock_terminate_hsit_log.h"

#define FAIL_TO_SEND_START_COMMAND              -1
#define SUCCESS_TO_SEND_START_COMMAND            0

void setUp()
{}

void tearDown()
{}


void test_runSerialHsitMasterShallConnectToSlave(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToSlave_IgnoreAndReturn(CONNECTION_SUCCESS);
  tryToSendStartCmdAndSleep_IgnoreAndReturn(SUCCESS_TO_SEND_START_COMMAND);
  HsitResult hsitResult = runSerialHsitMaster();
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_SUCCESS, hsitResult, "runSerialHsitMaster() "
      "shall success when connecting to slave!");
}

void test_runSerialHsitMasterShallFailIfFailingToInitiateHsitLog(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_FAILURE);
  HsitResult hsitResult = runSerialHsitMaster();
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, hsitResult, "runSerialHsitMaster() "
      "shall fail when failing to initiate HSIT log!");
}


void test_runSerialHsitMasterShallFailIfFailingToConnectToSlave(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToSlave_IgnoreAndReturn(CONNECTION_FAILURE);
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  HsitResult hsitResult = runSerialHsitMaster();
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, hsitResult, "runSerialHsitMaster() "
      "shall fail when failing to connect to slave!");
}

void test_runSerialHsitMasterShallFailIfFailingToSendStartCommand(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToSlave_IgnoreAndReturn(CONNECTION_SUCCESS);
  tryToSendStartCmdAndSleep_IgnoreAndReturn(FAIL_TO_SEND_START_COMMAND);
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  HsitResult hsitResult = runSerialHsitMaster();
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, hsitResult, "runSerialHsitMaster() "
      "shall fail when failing to send start command!");
}
