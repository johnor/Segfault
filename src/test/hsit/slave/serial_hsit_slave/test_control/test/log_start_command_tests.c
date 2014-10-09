#include "unity.h"
#include "log_start_command.h"
#include "log.h"
#include <string.h>
#include <stdarg.h>

#define LOG_ENTRY_MAX_LENGTH        256
#define INVALID_COMMAND       "invalid"

static const char logEntryForStartCommandRecieved[] = "Start command received from HSIT master!\n";
static const char logEntryForInvalidCommand[]       = "Invalid command received from HSIT master!\n";
static const char logEntryForNothingReceived[]      = "No message received from HSIT master!\n";
static char writtenLogEntry[LOG_ENTRY_MAX_LENGTH]   = "";

static void clearWrittenLogEntry(void)
{
  bzero(writtenLogEntry, LOG_ENTRY_MAX_LENGTH);
}

LogResult writeLog(const char* format, ...)
{
  TEST_ASSERT_NOT_NULL_MESSAGE(format, "'writeLog()' called with NULL argument!");

  va_list arglist;
  va_start(arglist, format);
  (void)vsnprintf(writtenLogEntry, LOG_ENTRY_MAX_LENGTH, format, arglist);
  va_end(arglist);

  return LOG_SUCCESS;
}

void setUp(void)
{
  clearWrittenLogEntry();
}

void tearDown(void)
{}

void test_logEntryForReceivedStartCommand(void)
{
  writeStartCommandResultToLog(START_COMMAND_RECEIVED);
  TEST_ASSERT_EQUAL_STRING(logEntryForStartCommandRecieved, writtenLogEntry);
}

void test_logEntryForReceivedInvalidCommand(void)
{
  writeStartCommandResultToLog(INVALID_COMMAND_RECEIVED);
  TEST_ASSERT_EQUAL_STRING(logEntryForInvalidCommand, writtenLogEntry);
}

void test_logEntryForReceivedNothing(void)
{
  writeStartCommandResultToLog(NOTHING_RECEIVED);
  TEST_ASSERT_EQUAL_STRING(logEntryForNothingReceived, writtenLogEntry);
}
