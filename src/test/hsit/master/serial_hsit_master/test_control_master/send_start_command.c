#include <unistd.h>

#include "system_socket.h"
#include "send_start_command.h"
#include "system_time.h"

#define START_COMMAND_TO_SEND     "start\n"

int tryToSendStartCmdAndSleep (){
  int i;
  for (i = 0; i < 3; ++i) {
    if (sendStartCommandToSlave() < 0) {
      systemSleepMicroSeconds(100);
      continue;
    }
    return 0;
  }
  return -1;
}

int sendStartCommandToSlave() {
  if(writeToSocket(START_COMMAND_TO_SEND) < 0) {
    return -1;
  }
  return 0;
}
