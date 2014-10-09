#include "initiate_hsit_log.h"
#include "log.h"

HsitResult initiateHsitLog(const char* initMessage)
{
  if (initiateLog() != LOG_SUCCESS)
  {
    return HSIT_FAILURE;
  }

  if (writeLog(initMessage) != LOG_SUCCESS)
  {
    (void)terminateLog();
    return HSIT_FAILURE;
  }

  return HSIT_SUCCESS;
}
