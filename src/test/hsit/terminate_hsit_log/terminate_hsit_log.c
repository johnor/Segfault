#include "terminate_hsit_log.h"
#include "log.h"

HsitResult terminateHsitLog(const char* terminationMessage)
{
  if (writeLog(terminationMessage) != LOG_SUCCESS)
  {
    (void)terminateLog();
    return HSIT_FAILURE;
  }

  if (terminateLog() != LOG_SUCCESS)
  {
    return HSIT_FAILURE;
  }

  return HSIT_SUCCESS;
}
