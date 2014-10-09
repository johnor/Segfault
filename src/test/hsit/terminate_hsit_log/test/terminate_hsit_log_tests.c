#include "unity.h"
#include <string.h>
#include "terminate_hsit_log.h"
#include "mock_log.h"

#define EXPECTATION_DEFINED_BY_CALLBACK  NULL

static const char expectedTerminationMessage[] = "Termination message\n";

static LogResult verifyEndMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedTerminationMessage), "Wrong termination message!");
  return LOG_SUCCESS;
}

void setUp(void)
{}

void tearDown(void)
{}

void test_terminateHsitLogShallWriteTerminationMessageToTheLog(void)
{
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(verifyEndMessage);
  terminateLog_IgnoreAndReturn(LOG_SUCCESS);
  (void)terminateHsitLog(expectedTerminationMessage);
}

void test_terminateHsitLogShallFailIfUnableToWriteToTheLog(void)
{
  writeLog_IgnoreAndReturn(LOG_FAILURE);
  terminateLog_IgnoreAndReturn(LOG_SUCCESS);
  HsitResult result = terminateHsitLog("Anything");
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, result, "'terminateHsitLog()' shall fail for this test case");
}

void test_terminateHsitLogShallTerminateTheLogIfUnableToWriteToTheLog(void)
{
  writeLog_IgnoreAndReturn(LOG_FAILURE);
  terminateLog_ExpectAndReturn(LOG_SUCCESS);
  (void)terminateHsitLog("Anything");
}

void test_terminateHsitLogShallTerminateTheLog(void)
{
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  terminateLog_ExpectAndReturn(LOG_SUCCESS);
  (void)terminateHsitLog("Anything");
}

void test_terminateHsitLogShallFailIfUnableToTerminateTheLog(void)
{
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  terminateLog_IgnoreAndReturn(LOG_FAILURE);
  HsitResult result = terminateHsitLog("Anything");
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, result, "'terminateHsitLog()' shall fail for this test case");
}

void test_terminateHsitLogShallSucceedIfAllGoesWell(void)
{
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  terminateLog_IgnoreAndReturn(LOG_SUCCESS);
  HsitResult result = terminateHsitLog("Anything");
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_SUCCESS, result, "'terminateHsitLog()' shall return  'HSIT_SUCCESS' when "
                                                  "log termination succeeds!");
}
