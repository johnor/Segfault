#include "hsit_performance_log.h"
#include "log.h"

#define TEST_MALFUNCTION_LOG_ENTRY  "HSIT malfunctioned!\n"

void writeHsitMalfunctionToLog(void)
{
  writeLog(TEST_MALFUNCTION_LOG_ENTRY);
}
