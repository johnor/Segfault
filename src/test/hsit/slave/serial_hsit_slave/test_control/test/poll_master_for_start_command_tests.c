#include "unity.h"
#include "poll_master_for_start_command.h"
#include "mock_system_time.h"
#include "mock_master_connection.h"
#include "log.h"
#include <string.h>
#include <stdarg.h>

#define DELAY_FOR_TEST   99
#define EXPECT_ONE_CALL   1
#define ONE_CALL          1

#define ZERO_BUFFER_LENGTH                                    0
#define EXPECTED_MESSAGE_BUFFER_SIZE                         32
#define EXPECTED_TEST_START_COMMAND                   "start\n"
#define UNEXPECTED_TEST_START_COMMAND  "You don't expect this!"
#define INVALID_COMMAND_LOG_ENTRY      "Received invalid start command: " UNEXPECTED_TEST_START_COMMAND "\n"


typedef enum
{
  SHALL_READ_START_COMMAND,
  SHALL_READ_INVALID_COMMAND,
  SHALL_READ_NOTHING,
  NOT_SET
} ReadFromMasterCallBackSetting;

static ReadFromMasterCallBackSetting readFromMasterCallBackSetting;
static int numberOfCallsToReadFromMaster;
static int numberOfExpectedCallsToReadFromMaster;
static bool usingReadFromMasterCallBack = false;

static char writtenLogEntry[LOG_ENTRY_MAX_LENGTH]   = "";
static bool writeLogWasCalled = false;
static bool shallExpectWriteLog = false;

static void verifyValidDestinationBuffer(char* const destinationBuffer, const size_t destinationBufferSize)
{
  TEST_ASSERT_NOT_NULL_MESSAGE(destinationBuffer, "NULL passed to 'readFromMaster()'!");
  TEST_ASSERT_EQUAL_MESSAGE(destinationBufferSize, EXPECTED_MESSAGE_BUFFER_SIZE, "Incorrect 'destinationBufferSize'!");
}

static void setUpReadFromMasterCallBack(ReadFromMasterCallBackSetting callBackSetting, int expectedNumberOfCalls)
{
  readFromMasterCallBackSetting         = callBackSetting;
  numberOfExpectedCallsToReadFromMaster = expectedNumberOfCalls;
  usingReadFromMasterCallBack           = true;
}

static int readFromMasterCallBack(char* const destinationBuffer, const size_t destinationBufferSize, int numberOfPreviousCalls)
{
  TEST_ASSERT_NOT_EQUAL_MESSAGE(NOT_SET, readFromMasterCallBackSetting, "Test case broken! 'readFromMasterCallBack()' "
                                                                        "was called without having been set up!");

  numberOfCallsToReadFromMaster = numberOfPreviousCalls + ONE_CALL;
  verifyValidDestinationBuffer(destinationBuffer, destinationBufferSize);

     if (readFromMasterCallBackSetting == SHALL_READ_START_COMMAND)
     {
       strcpy(destinationBuffer, EXPECTED_TEST_START_COMMAND);
       return strlen(EXPECTED_TEST_START_COMMAND);
     }
     if (readFromMasterCallBackSetting == SHALL_READ_INVALID_COMMAND)
     {
       strcpy(destinationBuffer, UNEXPECTED_TEST_START_COMMAND);
       return strlen(UNEXPECTED_TEST_START_COMMAND);
     }

     return ZERO_BUFFER_LENGTH;
}

static void resetReadFromMasterCallBack(void)
{
  readFromMasterCallBackSetting         = NOT_SET;
  numberOfCallsToReadFromMaster         = 0;
  numberOfExpectedCallsToReadFromMaster = 0;
  usingReadFromMasterCallBack           = false;
}

static void clearWrittenLogEntry(void)
{
  bzero(writtenLogEntry, LOG_ENTRY_MAX_LENGTH);
}

LogResult writeLog(const char* format, ...)
{
  writeLogWasCalled = true;
  TEST_ASSERT_NOT_NULL_MESSAGE(format, "'writeLog()' called with NULL argument!");

  va_list arglist;
  va_start(arglist, format);
  (void)vsnprintf(writtenLogEntry, LOG_ENTRY_MAX_LENGTH, format, arglist);
  va_end(arglist);

  TEST_ASSERT_EQUAL_STRING(INVALID_COMMAND_LOG_ENTRY, writtenLogEntry);

  return LOG_SUCCESS;
}

void setUp(void)
{
  resetReadFromMasterCallBack();
  clearWrittenLogEntry();
  writeLogWasCalled   = false;
  shallExpectWriteLog = false;
}

void tearDown(void)
{
  if (usingReadFromMasterCallBack)
  {
    if (numberOfCallsToReadFromMaster < numberOfExpectedCallsToReadFromMaster)
    {
      TEST_FAIL_MESSAGE("Number of calls to 'ReadFromMaster()' are less than expected!");
    }
    if (numberOfCallsToReadFromMaster > numberOfExpectedCallsToReadFromMaster)
    {
      TEST_FAIL_MESSAGE("Number of calls to 'ReadFromMaster()' are greater than expected!");
    }
  }

  if (shallExpectWriteLog)
  {
    TEST_ASSERT_MESSAGE(writeLogWasCalled, "Expected at least one call to 'writeLog()' but none was made!");
  }
}

void test_shallDelayAsSpecifiedBeforeAttemptingToReadFromMaster(void)
{
  systemSleep_Expect(DELAY_FOR_TEST);
  readFromMaster_IgnoreAndReturn(ZERO_BUFFER_LENGTH);
  (void)pollMasterForStartCommand(DELAY_FOR_TEST);
}

void test_shallReadFromMaster(void)
{
  systemSleep_Ignore();
  setUpReadFromMasterCallBack(SHALL_READ_NOTHING, EXPECT_ONE_CALL);
  readFromMaster_StubWithCallback(readFromMasterCallBack);
  (void)pollMasterForStartCommand(DELAY_FOR_TEST);
}

void test_returnCodeForStartCommand(void)
{
  systemSleep_Ignore();
  setUpReadFromMasterCallBack(SHALL_READ_START_COMMAND, EXPECT_ONE_CALL);
  readFromMaster_StubWithCallback(readFromMasterCallBack);
  StartCommandResult result = pollMasterForStartCommand(DELAY_FOR_TEST);
  TEST_ASSERT_EQUAL_MESSAGE(START_COMMAND_RECEIVED, result, "Wrong return code from 'pollMasterForStartCommand()' "
                                                            "when receiving the start command!");
}

void test_returnCodeForInvalidCommand(void)
{
  systemSleep_Ignore();
  setUpReadFromMasterCallBack(SHALL_READ_INVALID_COMMAND, EXPECT_ONE_CALL);
  readFromMaster_StubWithCallback(readFromMasterCallBack);
  StartCommandResult result = pollMasterForStartCommand(DELAY_FOR_TEST);
  TEST_ASSERT_EQUAL_MESSAGE(INVALID_COMMAND_RECEIVED, result, "Wrong return code from 'pollMasterForStartCommand()' "
                                                               "when receiving invalid command!");
}

void test_returnCodeWhenNothingIsReceived(void)
{
  systemSleep_Ignore();
  setUpReadFromMasterCallBack(SHALL_READ_NOTHING, EXPECT_ONE_CALL);
  readFromMaster_StubWithCallback(readFromMasterCallBack);
  StartCommandResult result = pollMasterForStartCommand(DELAY_FOR_TEST);
  TEST_ASSERT_EQUAL_MESSAGE(NOTHING_RECEIVED, result, "Wrong return code from 'pollMasterForStartCommand()' "
                                                      "when receiving nothing!");
}

void test_shallLogInvalidCommand(void)
{
  systemSleep_Ignore();
  setUpReadFromMasterCallBack(SHALL_READ_INVALID_COMMAND, EXPECT_ONE_CALL);
  readFromMaster_StubWithCallback(readFromMasterCallBack);
  shallExpectWriteLog = true;
  (void)pollMasterForStartCommand(DELAY_FOR_TEST);
}
