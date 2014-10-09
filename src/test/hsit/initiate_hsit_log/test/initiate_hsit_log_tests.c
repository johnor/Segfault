#include "unity.h"
#include <string.h>
#include "initiate_hsit_log.h"
#include "mock_log.h"


#define EXPECTATION_DEFINED_BY_CALLBACK  NULL

static const char expectedInitMessage[] = "Expected Init Message\n";

static LogResult verifyInitMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedInitMessage), "Wrong message!");
  return LOG_SUCCESS;
}

void setUp(void)
{}

void tearDown(void)
{}

void test_initiateHsitLogShallInitiateLog(void)
{
  initiateLog_ExpectAndReturn(LOG_SUCCESS);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  (void)initiateHsitLog("Anything");
}

void test_initiateHsitLogShallFailIfUnableToInitiateLog(void)
{
  initiateLog_IgnoreAndReturn(LOG_FAILURE);
  HsitResult result = initiateHsitLog("Anything");
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, result, "'initiateHsitLog()' shall fail for this test case");
}

void test_initiateHsitLogShallWriteInitMessageToTheLog(void)
{
  initiateLog_IgnoreAndReturn(LOG_SUCCESS);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(verifyInitMessage);
  (void)initiateHsitLog(expectedInitMessage);
}

void test_initiateHsitLogShallFailIfUnableToWriteToTheLog(void)
{
  initiateLog_IgnoreAndReturn(LOG_SUCCESS);
  writeLog_IgnoreAndReturn(LOG_FAILURE);
  terminateLog_IgnoreAndReturn(LOG_SUCCESS);
  HsitResult result = initiateHsitLog("Anything");
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_FAILURE, result, "'initiateHsitLog()' shall fail for this test case");
}

void test_initiateHsitLogShallTerminateLogIfUnableToWriteToTheLog(void)
{
  initiateLog_IgnoreAndReturn(LOG_SUCCESS);
  writeLog_IgnoreAndReturn(LOG_FAILURE);
  terminateLog_ExpectAndReturn(LOG_SUCCESS);
  (void)initiateHsitLog("Anything");
}

void test_initiateHsitLogShallSucceedIfAllGoesWell(void)
{
  initiateLog_IgnoreAndReturn(LOG_SUCCESS);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  HsitResult result = initiateHsitLog("Anything");
  TEST_ASSERT_EQUAL_MESSAGE(HSIT_SUCCESS, result, "'initiateHsitLog()' shall return 'HSIT_SUCCESS' when initialization "
                                                  "succeeds!");
}
