#include "unity.h"
#include <string.h>
#include "type.h"
#include "run_serial_hsit_slave.h"
#include "mock_initiate_hsit_log.h"
#include "mock_terminate_hsit_log.h"
#include "mock_master_connection.h"
#include "mock_test_control.h"
#include "mock_hsit_performance_log.h"

#define EXPECTATION_DEFINED_BY_CALLBACK  NULL

static const char expectedSlaveInitMessage[] = "Serial HSIT Slave started\n\n";

static HsitResult verifySlaveInitMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedSlaveInitMessage), "Wrong message!");
  return HSIT_SUCCESS;
}

static const char expectedSlaveTerminationMessage[] = "Serial HSIT slave has finished\n\n";

static HsitResult verifySlaveTerminationMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedSlaveTerminationMessage), "Wrong message!");
  return HSIT_SUCCESS;
}

void setUp(void)
{}

void tearDown(void)
{}

void test_runSerialHsitSlaveShallInitiateHsitLogUsingTheRightInitMessage(void)
{
  initiateHsitLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, HSIT_SUCCESS);
  initiateHsitLog_StubWithCallback(verifySlaveInitMessage);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_COMPLETE);
  terminateMasterConnection_Ignore();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallFailIfFailingToInitiateSlaveLog(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_FAILURE);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  HsitResult result = runSerialHsitSlave();
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, result, "'runSerialHsitSlave()' shall fail for this test case");
}

void test_runSerialHsitSlaveShallConnectToMaster(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_ExpectAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_COMPLETE);
  terminateMasterConnection_Ignore();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallFailIfFailingToConnectToMaster(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_FAILURE);
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  HsitResult result = runSerialHsitSlave();
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, result, "'runSerialHsitSlave()' shall fail for this test case");

}

void test_runSerialHsitSlaveShallTerminateHsitLogIfFailingToConnectToMaster(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_FAILURE);
  terminateHsitLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, HSIT_SUCCESS);
  terminateHsitLog_StubWithCallback(verifySlaveTerminationMessage);
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallAwaitTestStartCommand(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_ExpectAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_COMPLETE);
  terminateMasterConnection_Ignore();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallFailIfTestStartCommandIsNotReceived(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_NO_GO);
  terminateMasterConnection_Ignore();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  HsitResult result = runSerialHsitSlave();
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, result, "'runSerialHsitSlave()' shall fail for this test case");
}

void test_runSerialHsitSlaveShallTerminateMasterConnectionIfTestStartCommandIsNotReceived(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_NO_GO);
  terminateMasterConnection_Expect();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallTerminateHsitLogIfTestStartCommandIsNotReceived(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_NO_GO);
  terminateMasterConnection_Ignore();
  terminateHsitLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, HSIT_SUCCESS);
  terminateHsitLog_StubWithCallback(verifySlaveTerminationMessage);
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallExecuteTestWhenTestStartCommandHasBeenReceived(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_ExpectAndReturn(TEST_COMPLETE);
  terminateMasterConnection_Ignore();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallLogTestMalfunction(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_MALFUNCTION);
  terminateMasterConnection_Ignore();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  writeHsitMalfunctionToLog_Expect();
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallFailIfTestMalfunctions(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_MALFUNCTION);
  writeHsitMalfunctionToLog_Ignore();
  terminateMasterConnection_Ignore();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  HsitResult result = runSerialHsitSlave();
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, result, "'runSerialHsitSlave()' shall fail for this test case");
}

void test_runSerialHsitSlaveShallTerminateMasterConnectionIfTestMalfunctions(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_MALFUNCTION);
  writeHsitMalfunctionToLog_Ignore();
  terminateMasterConnection_Expect();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallTerminateHsitLogIfTestMalfunctions(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_MALFUNCTION);
  writeHsitMalfunctionToLog_Ignore();
  terminateMasterConnection_Ignore();
  terminateHsitLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, HSIT_SUCCESS);
  terminateHsitLog_StubWithCallback(verifySlaveTerminationMessage);
  (void)runSerialHsitSlave();
}


void test_runSerialHsitSlaveShallTerminateMasterConnection(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_COMPLETE);
  terminateMasterConnection_Expect();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallTerminateHsitLog(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_COMPLETE);
  terminateMasterConnection_Ignore();
  terminateHsitLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, HSIT_SUCCESS);
  terminateHsitLog_StubWithCallback(verifySlaveTerminationMessage);
  (void)runSerialHsitSlave();
}

void test_runSerialHsitSlaveShallFailIfFailingToTerminateHsitLog(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_COMPLETE);
  terminateMasterConnection_Ignore();
  terminateHsitLog_IgnoreAndReturn(HSIT_FAILURE);
  HsitResult result = runSerialHsitSlave();
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, result, "'runSerialHsitSlave()' shall fail for this test case");
}

void test_runSerialHsitSlaveShallSucceedIfAllGoesWell(void)
{
  initiateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  connectToMaster_IgnoreAndReturn(CONNECTION_SUCCESS);
  awaitTestStartCommand_IgnoreAndReturn(TEST_GOOD_TO_GO);
  runTest_IgnoreAndReturn(TEST_COMPLETE);
  terminateMasterConnection_Ignore();
  terminateHsitLog_IgnoreAndReturn(HSIT_SUCCESS);
  HsitResult result = runSerialHsitSlave();
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_SUCCESS, result, "'runSerialHsitSlave()' shall return 'HSIT_SUCCESS' when test "
                                                  "execution succeeds!");
}
