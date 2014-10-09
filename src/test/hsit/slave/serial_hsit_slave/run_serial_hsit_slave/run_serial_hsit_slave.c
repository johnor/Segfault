#include "run_serial_hsit_slave.h"
#include "initiate_hsit_log.h"
#include "terminate_hsit_log.h"
#include "master_connection.h"
#include "test_control.h"
#include "hsit_performance_log.h"

#define START_MESSAGE  "Serial HSIT Slave started\n\n"
#define END_MESSAGE    "Serial HSIT slave has finished\n\n"

HsitResult runSerialHsitSlave(void)
{
  if (initiateHsitLog(START_MESSAGE) != HSIT_SUCCESS)
  {
    return HSIT_FAILURE;
  }

  if (connectToMaster() != CONNECTION_SUCCESS)
  {
    (void)terminateHsitLog(END_MESSAGE);
    return HSIT_FAILURE;
  }

  if (awaitTestStartCommand() != TEST_GOOD_TO_GO)
  {
    terminateMasterConnection();
    (void)terminateHsitLog(END_MESSAGE);
    return HSIT_FAILURE;
  }

  if (runTest() != TEST_COMPLETE)
  {
    writeHsitMalfunctionToLog();
    terminateMasterConnection();
    (void)terminateHsitLog(END_MESSAGE);
    return HSIT_FAILURE;
  }

  terminateMasterConnection();

  if (terminateHsitLog(END_MESSAGE) != HSIT_SUCCESS)
  {
    return HSIT_FAILURE;
  }

  return HSIT_SUCCESS;
}
