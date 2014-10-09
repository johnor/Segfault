#include <unistd.h>
#include <stdio.h>

#include "initiate_hsit_log.h"
#include "run_serial_hsit_master.h"
#include "terminate_hsit_log.h"
#include "system_socket.h"
#include "send_start_command.h"

#include "slave_connection.h"

#define START_MESSAGE  "Serial HSIT Master started\n\n"
#define END_MESSAGE    "Serial HSIT Master has finished\n\n"

#define START_COMMAND_TO_SEND     "start\n"

HsitResult runSerialHsitMaster(void)
{
  if(initiateHsitLog(START_MESSAGE) != HSIT_SUCCESS) {
    return HSIT_FAILURE;
  }

  if(connectToSlave() != CONNECTION_SUCCESS) {
    (void)terminateHsitLog(END_MESSAGE);
    return HSIT_FAILURE;
  }

  int sendStartCommandResult = tryToSendStartCmdAndSleep();

  if(sendStartCommandResult < 0) {
    (void)terminateHsitLog(END_MESSAGE);
    return HSIT_FAILURE;
  }

  return HSIT_SUCCESS;
}

