#include "poll_master_for_start_command.h"
#include "system_time.h"
#include "master_connection.h"
#include "log.h"
#include <string.h>

#define EXPECTED_TEST_START_COMMAND     "start\n"
#define MESSAGE_FROM_MASTER_MAX_LENGTH         32
#define ZERO_BUFFER_LENGTH                      0

static char messageFromMaster[MESSAGE_FROM_MASTER_MAX_LENGTH] = "";

static bool messageFromMasterEqualsExpectedTestStartCommand(void)
{
  if (strcmp(EXPECTED_TEST_START_COMMAND, messageFromMaster))
  {
    writeLog("Received invalid start command: %s\n", messageFromMaster);
    return false;
  }
  return true;
}

StartCommandResult pollMasterForStartCommand(unsigned int delay)
{
  systemSleep(delay);

  if (readFromMaster(messageFromMaster, MESSAGE_FROM_MASTER_MAX_LENGTH) > ZERO_BUFFER_LENGTH)
  {
    if (messageFromMasterEqualsExpectedTestStartCommand())
    {
      return START_COMMAND_RECEIVED;
    }
    return INVALID_COMMAND_RECEIVED;
  }
  return NOTHING_RECEIVED;
}
