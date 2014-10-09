#ifndef LOG_H_
#define LOG_H_

#define LOG_ENTRY_MAX_LENGTH  256

typedef enum
{
  LOG_FAILURE,
  LOG_SUCCESS
} LogResult;

LogResult initiateLog(void);
LogResult writeLog(const char* format, ...);
LogResult terminateLog(void);

#endif /* LOG_H_ */
