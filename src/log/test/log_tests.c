#include <string.h>
#include "unity.h"
#include "log.h"
#include "mock_system_time.h"
#include "mock_system_file.h"

#define FILENAME_PREFIX          "apmaskin_" VARIANT "_"
#define CURRENT_TIME             "yyyy-mm-dd_hhmmss"
#define FILENAME_SUFFIX          ".log"
#define THE_RIGHT_FILEMODE       "w"
#define THE_RIGHT_FILENAME       FILENAME_PREFIX CURRENT_TIME FILENAME_SUFFIX
#define TOO_LONG                 (LOG_ENTRY_MAX_LENGTH + 8)  // '8' is more than enough

static char dummyVariable;  // Use any type just to have a variable whose address we can use for return value
static char tooLongString[TOO_LONG];

static unsigned int writtenStringLength;

static void setUpTooLongStringString(void)
{
  int i;

  for (i = 0; i < (TOO_LONG - 1); i++)
  {
    tooLongString[i] = 'a';
  }

  // Terminate the string,
  tooLongString[(TOO_LONG - 1)] = '\0';
}

int writeFileStringLengthCounter(void* file, const char* fileEntry, int numberOfPreviousCalls)
{
  writtenStringLength = strlen(fileEntry);
  return writtenStringLength;
}

void setUp(void)
{
  writtenStringLength = 0;
}

void tearDown(void)
{
  closeFile_IgnoreAndReturn(0);
  terminateLog();
}

static void setUpMockForValidLogFileInitiation(void)
{
  getDateAndTime_ExpectAndReturn(CURRENT_TIME);
  openFile_ExpectAndReturn(THE_RIGHT_FILENAME, THE_RIGHT_FILEMODE, (void*)&dummyVariable);
}

void test_initiateLogOpensTheRightFileUsingTheRightMode(void)
{
  setUpMockForValidLogFileInitiation();
  LogResult logResult = initiateLog();
  TEST_ASSERT_EQUAL_MESSAGE(LOG_SUCCESS, logResult, "'initiateLog()' is expected to return 'LOG_SUCCESS' when "
                                                    "succeeding in opening the log file!");
}

void test_initiateLogShallFailWhenUnableToOpenTheLogFile(void)
{
  getDateAndTime_IgnoreAndReturn(CURRENT_TIME);
  openFile_IgnoreAndReturn(NULL);
  LogResult logResult = initiateLog();
  TEST_ASSERT_EQUAL_MESSAGE(LOG_FAILURE, logResult, "'initiateLog()' is expected to return 'LOG_FAILURE' when "
                                                    "failing in opening the log file!");
}

void test_initiateLogShallFailIfCalledWhenAlreadyInitiated(void)
{
  LogResult logResult;
  setUpMockForValidLogFileInitiation();
  (void)initiateLog();
  logResult = initiateLog();
  TEST_ASSERT_EQUAL_MESSAGE(LOG_FAILURE, logResult, "'initiateLog()' is expected to return 'LOG_FAILURE' if called "
                                                    "when already initiated!");
}

void test_writeLogShallFailIfCalledWhenLogIsNotInitiated(void)
{
  LogResult logResult = writeLog("A simple log message");
  TEST_ASSERT_EQUAL_MESSAGE(LOG_FAILURE, logResult, "'writeLog()' is expected to return 'LOG_FAILURE' if called when "
                                                      "log module is not yet initiated!");
}


void test_writeLogCanWriteLogEntryToTheRightLogFile(void)
{
  LogResult logResult;
  const char stringToWrite[] = "A simple log entry";
  int stringLength = strlen(stringToWrite);

  setUpMockForValidLogFileInitiation();
  (void)initiateLog();

  writeFile_ExpectAndReturn((void*)&dummyVariable, stringToWrite, stringLength);
  logResult = writeLog(stringToWrite);

  TEST_ASSERT_EQUAL_MESSAGE(LOG_SUCCESS, logResult, "'writeLog()' is expected to return 'LOG_SUCCESS' when succeeding "
                                                    "in writing the log file!");
}

void test_writeLogShallFailWhenUnableToWriteToTheLogFile(void)
{
  LogResult logResult;
  const char stringToWrite[] = "Simple sample string";
  int stringLengthIndicatingFailure = -1;  // Negative numbers represent failure of 'fprintf()'

  setUpMockForValidLogFileInitiation();
  (void)initiateLog();

  writeFile_ExpectAndReturn((void*)&dummyVariable, stringToWrite, stringLengthIndicatingFailure);
  logResult = writeLog(stringToWrite);

  TEST_ASSERT_EQUAL_MESSAGE(LOG_FAILURE, logResult, "'writeLog()' is expected to return 'LOG_FAILURE' if file-write "
                                                    "operation fails!");
}

void test_writeLogShallNotWriteTooMuch(void)
{
  setUpTooLongStringString();
  setUpMockForValidLogFileInitiation();
  writeFile_StubWithCallback(writeFileStringLengthCounter);
  (void)initiateLog();
  (void)writeLog(tooLongString);
  TEST_ASSERT_EQUAL_MESSAGE(LOG_ENTRY_MAX_LENGTH, writtenStringLength, "'writeLog()' shall not exceed "
                                                                       "'LOG_ENTRY_MAX_LENGTH'!");

}

void test_terminateLogShallCloseTheLogFile(void)
{
  LogResult logResult;

  setUpMockForValidLogFileInitiation();
  (void)initiateLog();

  closeFile_ExpectAndReturn((void*)&dummyVariable, 0);
  logResult = terminateLog();

  TEST_ASSERT_EQUAL_MESSAGE(LOG_SUCCESS, logResult, "'terminateLog()' is expected to return 'LOG_SUCCESS' when "
                                                    "succeeding in closing the log file!");
}

void test_terminateLogShallFailIfFailingToCloseTheLogFile(void)
{
  LogResult logResult;

  setUpMockForValidLogFileInitiation();
  (void)initiateLog();

  closeFile_ExpectAndReturn((void*)&dummyVariable, EOF);
  logResult = terminateLog();

  TEST_ASSERT_EQUAL_MESSAGE(LOG_FAILURE, logResult, "'terminateLog()' is expected to return 'LOG_FAILURE' when "
                                                    "failing in closing the log file!");
}

void test_writeLogShallFailIfCalledWhenLogHasBeenTerminated(void)
{
  LogResult logResult;
  const char stringToWrite[] = "Simple sample string";
  int notZero = 5;

  setUpMockForValidLogFileInitiation();
  (void)initiateLog();

  closeFile_ExpectAndReturn((void*)&dummyVariable, 0);
  (void)terminateLog();

  writeFile_IgnoreAndReturn(notZero);
  logResult = writeLog(stringToWrite);

  TEST_ASSERT_EQUAL_MESSAGE(LOG_FAILURE, logResult, "'writeLog()' is expected to return 'LOG_FAILURE' if called after "
                                                    "log has been terminated!");
}
