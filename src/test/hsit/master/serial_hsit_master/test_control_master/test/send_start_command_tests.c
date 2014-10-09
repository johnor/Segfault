#include "unity.h"
#include "send_start_command.h"
#include "mock_system_time.h"
#include "mock_system_socket.h"


#define START_COMMAND_SENT_SUCCESS              0

#define NUMBER_BYTES_WRITTEN                    5
#define WRITE_SOCKET_ERROR                      -1
#define NUMBER_OF_MS_TO_SLEEP_AFTER_FAIL        100

void setUp()
{}

void tearDown()
{}


void test_tryToSendStartCmdAndSleepShallReturnSuccessWhenStartCommandSent(void)
{
    writeToSocket_IgnoreAndReturn(NUMBER_BYTES_WRITTEN);
    (void)tryToSendStartCmdAndSleep();
}

void test_tryToSendStartCmdAndSleepShallSleep3TimesIfFailingToSendStartCommandOneTime(void)
{
  writeToSocket_IgnoreAndReturn(WRITE_SOCKET_ERROR);
  writeToSocket_IgnoreAndReturn(WRITE_SOCKET_ERROR);
  writeToSocket_IgnoreAndReturn(WRITE_SOCKET_ERROR);
  systemSleepMicroSeconds_Expect(NUMBER_OF_MS_TO_SLEEP_AFTER_FAIL);
  systemSleepMicroSeconds_Expect(NUMBER_OF_MS_TO_SLEEP_AFTER_FAIL);
  systemSleepMicroSeconds_Expect(NUMBER_OF_MS_TO_SLEEP_AFTER_FAIL);
  (void)tryToSendStartCmdAndSleep();
}

