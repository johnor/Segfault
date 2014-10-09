#ifndef WAIT_FOR_START_H_
#define WAIT_FOR_START_H_

typedef enum
{
  START_COMMAND_RECEIVED,
  INVALID_COMMAND_RECEIVED,
  NOTHING_RECEIVED
} StartCommandResult;

StartCommandResult wait3sForTestStartCommand(void);

#endif /* WAIT_FOR_START_H_ */
