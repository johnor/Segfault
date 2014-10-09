#include "log_start_command.h"
#include "log.h"

static const char logEntryForStartCommandRecieved[] = "Start command received from HSIT master!\n";
static const char logEntryForInvalidCommand[]       = "Invalid command received from HSIT master!\n";
static const char logEntryForNothingReceived[]      = "No message received from HSIT master!\n";

static const char* logEntry = logEntryForStartCommandRecieved;

void writeStartCommandResultToLog(StartCommandResult startCommandResult)
{
  if (startCommandResult == START_COMMAND_RECEIVED)
  {
    logEntry = logEntryForStartCommandRecieved;
  }
  else if (startCommandResult == INVALID_COMMAND_RECEIVED)
  {
    logEntry = logEntryForInvalidCommand;
  }
  else if (startCommandResult == NOTHING_RECEIVED)
  {
    logEntry = logEntryForNothingReceived;
  }

  writeLog(logEntry);
}
