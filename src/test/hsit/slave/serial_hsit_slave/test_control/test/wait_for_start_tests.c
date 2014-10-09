#include "unity.h"
#include "wait_for_start.h"
#include "mock_poll_master_for_start_command.h"

#define ONE_SECOND_DELAY  1

void setUp(void)
{}

void tearDown(void)
{}

void test_wait3sForTestStartCommandShallMakeThreeAttemptsAtPollingMaster(void)
{
  pollMasterForStartCommand_ExpectAndReturn(ONE_SECOND_DELAY, NOTHING_RECEIVED);
  pollMasterForStartCommand_ExpectAndReturn(ONE_SECOND_DELAY, NOTHING_RECEIVED);
  pollMasterForStartCommand_ExpectAndReturn(ONE_SECOND_DELAY, NOTHING_RECEIVED);
  (void)wait3sForTestStartCommand();
}

void test_rightReturnCodeWhenStartCommandReceived(void)
{
  pollMasterForStartCommand_ExpectAndReturn(ONE_SECOND_DELAY, START_COMMAND_RECEIVED);
  StartCommandResult result = wait3sForTestStartCommand();
  TEST_ASSERT_EQUAL_MESSAGE(START_COMMAND_RECEIVED, result, "Wrong return code from 'wait3sForTestStartCommand()' when "
                                                            "test start command received!");
}

void test_rightReturnCodeWhenIvalidCommandReceived(void)
{
  pollMasterForStartCommand_ExpectAndReturn(ONE_SECOND_DELAY, INVALID_COMMAND_RECEIVED);
  StartCommandResult result = wait3sForTestStartCommand();
  TEST_ASSERT_EQUAL_MESSAGE(INVALID_COMMAND_RECEIVED, result, "Wrong return code from 'wait3sForTestStartCommand()' when "
                                                              "invalid test start command received!");
}

void test_rightReturnCodeWhenNoMessageIsReceived(void)
{
  pollMasterForStartCommand_IgnoreAndReturn(NOTHING_RECEIVED);
  StartCommandResult result = wait3sForTestStartCommand();
  TEST_ASSERT_EQUAL_MESSAGE(NOTHING_RECEIVED, result, "Wrong return code from 'wait3sForTestStartCommand()' when "
                                                      "no message is received!");
}
