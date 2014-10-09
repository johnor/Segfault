#include <string.h>

#include "unity.h"
#include "slave_connection.h"
#include "mock_system_socket.h"
#include "log.h"
#include "mock_log.h"

#define EXPECTATION_DEFINED_BY_CALLBACK  NULL
#define DUMMY_FILE_DESCRIPTOR            1234
#define SOCKET_FAILURE                     -1
#define BIND_SOCKET_SUCCESS                 0
#define CONNECT_TO_SOCKET_SUCCESS           0
//#define SET_SOCKET_NONBLOCKING_SUCCESS      0
#define CONNECT_TO_SOCKET_FAILURE          -1

void setUp()
{}

void tearDown()
{}

static const char expectedOpenSocketFailureMessage[] = "'connectToSlave()' has failed to open the socket!\n";
static const char expectedConnectToSocketFailureMessage[] = "'connectToSlave()' has failed to connect to the socket!\n";
//static const char expectedSetSocketNonblockingFailureMessage[] = "'connectToSlave()' has failed to set socket nonblocking!\n";


static LogResult checkOpenSocketFailureMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedOpenSocketFailureMessage), "Wrong message!");
  return LOG_SUCCESS;
}

static LogResult checkConnectToSocketFailureMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedConnectToSocketFailureMessage), "Wrong message!");
  return LOG_SUCCESS;
}

/*static LogResult checkSetSocketNonblockingFailureMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedSetSocketNonblockingFailureMessage), "Wrong message!");
  return LOG_SUCCESS;
}*/

void test_openSlaveConnectionShallOpenSocket(void)
{
  openSocket_ExpectAndReturn(DUMMY_FILE_DESCRIPTOR);
  //setSocketNonBlocking_IgnoreAndReturn(SET_SOCKET_NONBLOCKING_SUCCESS);
  connectToSocket_IgnoreAndReturn(CONNECT_TO_SOCKET_SUCCESS);
  (void)connectToSlave();
}

void test_connectToSlaveShallFailIfFailingToOpenSocket(void)
{
  openSocket_IgnoreAndReturn(SOCKET_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  ConnectionResult connectionResult = connectToSlave();
  TEST_ASSERT_EQUAL_MESSAGE(CONNECTION_FAILURE, connectionResult, "'connectToSlave()' shall fail if failing to open "
                                                                  "socket!");
}

void test_connectToSlaveShallLogFailureToOpenSocket(void)
{
  openSocket_IgnoreAndReturn(SOCKET_FAILURE);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkOpenSocketFailureMessage);
  (void)connectToSlave();
}

void test_connectToSlaveShallConnectToSocket(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  //setSocketNonBlocking_IgnoreAndReturn(SET_SOCKET_NONBLOCKING_SUCCESS);
  connectToSocket_ExpectAndReturn(CONNECT_TO_SOCKET_SUCCESS);
  (void)connectToSlave();
}

void test_connectToSlaveShallFailIfFailingToConnectToSocket(void)
{
  openSocket_ExpectAndReturn(DUMMY_FILE_DESCRIPTOR);
  //setSocketNonBlocking_ExpectAndReturn(SET_SOCKET_NONBLOCKING_SUCCESS);
  connectToSocket_ExpectAndReturn(CONNECT_TO_SOCKET_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Ignore();
  ConnectionResult connectionResult = connectToSlave();
  TEST_ASSERT_EQUAL_MESSAGE(CONNECTION_FAILURE, connectionResult, "'connectToSlave()' shall fail if failing to connect to "
                                                                  "socket!");
}

void test_connectToSlaveShallLogFailureToConnectToSocket(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  //setSocketNonBlocking_ExpectAndReturn(SET_SOCKET_NONBLOCKING_SUCCESS);
  connectToSocket_IgnoreAndReturn(CONNECT_TO_SOCKET_FAILURE);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkConnectToSocketFailureMessage);
  closeSocket_Ignore();
  (void)connectToSlave();
}

/*void test_connectToSlaveShallLogFailureToSetSocketNonBlocking(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  //setSocketNonBlocking_IgnoreAndReturn(SOCKET_FAILURE);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkSetSocketNonblockingFailureMessage);
  closeSocket_Ignore();
  (void)connectToSlave();
}*/


