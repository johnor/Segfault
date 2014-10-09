#include "system_time.h"
#include "time.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DATE_AND_TIME_STRING_MAX_LENGTH 32
#define TM_BASE_YEAR                    1900  // See "time.h"
#define TWO_DIGITS_AND_A_NEWLINE        3

static char date_time[DATE_AND_TIME_STRING_MAX_LENGTH];
static char hours[TWO_DIGITS_AND_A_NEWLINE];
static char minutes[TWO_DIGITS_AND_A_NEWLINE];
static char seconds[TWO_DIGITS_AND_A_NEWLINE];

static void integerToTwoDigitString(unsigned int time, char* string)
{
  if (time < 10)
  {
    sprintf(string, "0%d", time);
  } else if (time < 100)
  {
    sprintf(string, "%d", time);
  }
}

const char* getDateAndTime(void)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    sprintf(date_time, "%d-%d-%d_", t->tm_year + TM_BASE_YEAR, t->tm_mon + 1,t->tm_mday);

    integerToTwoDigitString(t->tm_hour, hours);
    integerToTwoDigitString(t->tm_min, minutes);
    integerToTwoDigitString(t->tm_sec, seconds);

    strcat(date_time, hours);
    strcat(date_time, minutes);
    strcat(date_time, seconds);

    return date_time;
}

void systemSleep(int numberOfSecondsToSleep)
{
  (void)sleep(numberOfSecondsToSleep);
}

void systemSleepMicroSeconds(int numberOfMsToSleep)
{
  (void)usleep(numberOfMsToSleep);
}
