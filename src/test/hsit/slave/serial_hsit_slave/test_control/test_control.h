#ifndef TEST_CONTROL_H_
#define TEST_CONTROL_H_

typedef enum
{
  TEST_GOOD_TO_GO,
  TEST_NO_GO
} TestStartDecision;

typedef enum
{
  TEST_COMPLETE,
  TEST_MALFUNCTION
} TestResult;

TestStartDecision awaitTestStartCommand(void);
TestResult runTest(void);

#endif /* TEST_CONTROL_H_ */
