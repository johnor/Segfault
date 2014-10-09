#include "wait_for_start.h"
#include "poll_master_for_start_command.h"

#define DELAY_ONE_SECOND   1
#define MAX_READ_ATTEMPTS  3

StartCommandResult wait3sForTestStartCommand(void)
{
  unsigned int i;
  StartCommandResult startCommandResult;

  for (i = 0; i < MAX_READ_ATTEMPTS; i++)
  {
    startCommandResult = pollMasterForStartCommand(DELAY_ONE_SECOND);

    if (startCommandResult != NOTHING_RECEIVED)
    {
      return startCommandResult;
    }
  }

  return NOTHING_RECEIVED;
}
