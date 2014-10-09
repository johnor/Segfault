#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "log.h"
#include "system_time.h"
#include "system_file.h"

#define FILENAME_PREFIX          "apmaskin_" VARIANT "_"
#define FILENAME_SUFFIX          ".log"
#define FILE_MODE                "w"
#define ONE_CHAR                 1

#define LOG_FILENAME_MAX_LENGTH  256

static char logEntry[LOG_ENTRY_MAX_LENGTH + ONE_CHAR];
static char logFilename[LOG_FILENAME_MAX_LENGTH] = "";

static void* logFile = NULL;

LogResult initiateLog(void)
{
  if (logFile != NULL)
  {
    return LOG_FAILURE;
  }

  const char* currentTime = getDateAndTime();
  sprintf(logFilename, "%s%s%s", FILENAME_PREFIX, currentTime, FILENAME_SUFFIX);
  logFile = openFile(logFilename, FILE_MODE);

  if (logFile == NULL)
  {
    return LOG_FAILURE;
  }

  return LOG_SUCCESS;
}

LogResult writeLog(const char* format, ...)
{
  if (logFile == NULL)
  {
    return LOG_FAILURE;
  }

  int writtenCharacters;
  va_list arglist;
  va_start(arglist, format);
  writtenCharacters = vsnprintf(logEntry, LOG_ENTRY_MAX_LENGTH + ONE_CHAR, format, arglist);
  va_end( arglist );

  writtenCharacters = writeFile(logFile, logEntry);

  if (writtenCharacters < 0)
  {
    return LOG_FAILURE;
  }

  return LOG_SUCCESS;
}

LogResult terminateLog(void)
{
  int result = closeFile(logFile);
  logFile = NULL;

  if (result == EOF)
  {
    return LOG_FAILURE;
  }

  return LOG_SUCCESS;
}
