#include "unity.h"
#include "hsit_performance_log.h"
#include "log.h"
#include "type.h"

#include <string.h>
#include <stdarg.h>

#define TEST_MALFUNCTION_LOG_ENTRY  "HSIT malfunctioned!\n"

static char writtenLogEntry[LOG_ENTRY_MAX_LENGTH]   = "";
static bool writeLogCalled = false;
static bool expectWriteLog = false;

static void clearWrittenLogEntry(void)
{
  bzero(writtenLogEntry, LOG_ENTRY_MAX_LENGTH);
}

LogResult writeLog(const char* format, ...)
{
  writeLogCalled = true;
  TEST_ASSERT_NOT_NULL_MESSAGE(format, "'writeLog()' called with NULL argument!");

  va_list arglist;
  va_start(arglist, format);
  (void)vsnprintf(writtenLogEntry, LOG_ENTRY_MAX_LENGTH, format, arglist);
  va_end(arglist);

  TEST_ASSERT_EQUAL_STRING(TEST_MALFUNCTION_LOG_ENTRY, writtenLogEntry);

  return LOG_SUCCESS;
}

void setUp(void)
{}

void tearDown(void)
{
  if (expectWriteLog)
  {
    TEST_ASSERT_MESSAGE(writeLogCalled, "Expected at least one call to 'writeLog()'!");
  }

  writeLogCalled = false;
  expectWriteLog = false;
  clearWrittenLogEntry();
}

void test_shallWriteEntryAboutMalfunctionedTest(void)
{
  expectWriteLog = true;
  writeHsitMalfunctionToLog();
}
