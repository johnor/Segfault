#include "unity.h"
#include <string.h>
#include "master_connection.h"
#include "mock_system_socket.h"
#include "mock_log.h"

#define EXPECTATION_DEFINED_BY_CALLBACK  NULL
#define DUMMY_FILE_DESCRIPTOR            1234
#define DUMMY_FILE_DESCRIPTOR_2          5678
#define SOCKET_FAILURE                     -1
#define BIND_SOCKET_SUCCESS                 0
#define BIND_SOCKET_FAILURE                -1
#define LISTEN_SOCKET_SUCCESS               0
#define LISTEN_SOCKET_FAILURE              -1
#define ONE_CONNECTION_REQUEST_RECEIVED     1
#define WAIT_FOR_CLIENT_TIMEOUT             0
#define WAIT_FOR_CLIENT_FAILURE            -1
#define MORE_THAN_ONE_CLIENT                2
#define ACCEPT_CLIENT_FAILURE              -1
#define TEST_BUFFER_SIZE                  256
#define ZERO_BYTES                          0
#define NUMBER_OF_BYTES_READ_FROM_CLIENT   32

static const char expectedOpenSocketFailureMessage[] = "'connectToMaster()' has failed to open the socket!\n";

static LogResult checkOpenSocketFailureMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedOpenSocketFailureMessage), "Wrong message!");
  return LOG_SUCCESS;
}

static const char expectedBindSocketFailureMessage[] = "'connectToMaster()' has failed to bind the socket!\n";

static LogResult checkBindSocketFailureMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedBindSocketFailureMessage), "Wrong message!");
  return LOG_SUCCESS;
}

static const char expectedListenToSocketFailureMessage[] = "'connectToMaster()' has failed to listen to the socket!\n";

static LogResult checkListenToSocketFailureMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedListenToSocketFailureMessage), "Wrong message!");
  return LOG_SUCCESS;
}

static const char expectedWaitForClientTimeoutMessage[] = "'connectToMaster()': Wait for client timed out!\n";

static LogResult checkWaitForClientTimeoutMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedWaitForClientTimeoutMessage), "Wrong message!");
  return LOG_SUCCESS;
}

static const char expectedWaitForClientFailureMessage[] = "'connectToMaster()': Wait for client failed!\n";

static LogResult checkWaitForClientFailureMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedWaitForClientFailureMessage), "Wrong message!");
  return LOG_SUCCESS;
}

static const char expectedMoreThanOneClientMessage[] = "'connectToMaster()': Wait for client received more than one "
                                                       "connection requests!\n";

static LogResult checkMoreThanOneClientMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedMoreThanOneClientMessage), "Wrong message!");
  return LOG_SUCCESS;
}

static const char expectedAcceptFailureMessage[] = "'connectToMaster()' failed to accept client!\n";

static LogResult checkAcceptFailureMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedAcceptFailureMessage), "Wrong message!");
  return LOG_SUCCESS;
}

static const char expectedNullPointerMessage[] = "'readFromMaster()' called with 'NULL' for destination buffer!\n";

static LogResult checkNullPointerMessage(const char* format, int numPreviousCalls)
{
  TEST_ASSERT_MESSAGE(!strcmp(format, expectedNullPointerMessage), "Wrong message!");
  return LOG_SUCCESS;
}

static char readFromMasterDestinationBuffer[TEST_BUFFER_SIZE] = "";

void setUp(void)
{}

void tearDown(void)
{}

void test_connectToMasterShallOpenSocket(void)
{
  openSocket_ExpectAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(ONE_CONNECTION_REQUEST_RECEIVED);
  acceptClient_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR_2);
  setNonBlockingSocketOperation_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallFailIfFailingToOpenSocket(void)
{
  openSocket_IgnoreAndReturn(SOCKET_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  ConnectionResult connectionResult = connectToMaster();
  TEST_ASSERT_EQUAL_MESSAGE(CONNECTION_FAILURE, connectionResult, "'connectToMaster()' shall fail if failing to open "
                                                                  "socket!");
}

void test_connectToMasterShallLogFailureToOpenSocket(void)
{
  openSocket_IgnoreAndReturn(SOCKET_FAILURE);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkOpenSocketFailureMessage);
  (void)connectToMaster();
}

void test_connectToMasterShallBindSocket(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_ExpectAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(ONE_CONNECTION_REQUEST_RECEIVED);
  acceptClient_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR_2);
  setNonBlockingSocketOperation_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallFailIfFailingToBindSocket(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Ignore();
  ConnectionResult connectionResult = connectToMaster();
  TEST_ASSERT_EQUAL_MESSAGE(CONNECTION_FAILURE, connectionResult, "'connectToMaster()' shall fail if failing to bind "
                                                                  "socket!");
}

void test_connectToMasterShallLogFailureToBindSocket(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_FAILURE);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkBindSocketFailureMessage);
  closeSocket_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallCloseSocketIfFailingToBindSocket(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Expect();
  (void)connectToMaster();
}

void test_connectToMasterShallListenToSocket(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_ExpectAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(ONE_CONNECTION_REQUEST_RECEIVED);
  acceptClient_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR_2);
  setNonBlockingSocketOperation_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallFailIfFailingToListenToSocket(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Ignore();
  ConnectionResult connectionResult = connectToMaster();
  TEST_ASSERT_EQUAL_MESSAGE(CONNECTION_FAILURE, connectionResult, "'connectToMaster()' shall fail if failing to listen "
                                                                  "to socket!");
}

void test_connectToMasterShallCloseSocketIfFailingToListenToSocket(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Expect();
  (void)connectToMaster();
}

void test_connectToMasterShallLogFailureToListenToSocket(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_FAILURE);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkListenToSocketFailureMessage);
  closeSocket_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallWaitForClientToEstablishConnection(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_ExpectAndReturn(ONE_CONNECTION_REQUEST_RECEIVED);
  acceptClient_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR_2);
  setNonBlockingSocketOperation_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallIndicateTimeoutIfWaitForClientTimesOut(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(WAIT_FOR_CLIENT_TIMEOUT);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Ignore();
  ConnectionResult connectionResult = connectToMaster();
  TEST_ASSERT_EQUAL_MESSAGE(CONNECTION_TIMEOUT, connectionResult, "'connectToMaster()' shall indicate timeout if "
                                                                  "'waitForClient()' times out");
}

void test_connectToMasterShallCloseSocketIfWaitForClientTimesOut(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(WAIT_FOR_CLIENT_TIMEOUT);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Expect();
  (void)connectToMaster();
}

void test_connectToMasterShallLogWaitForClientTimeOut(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(WAIT_FOR_CLIENT_TIMEOUT);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkWaitForClientTimeoutMessage);
  closeSocket_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallFailIfWaitForClientFails(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(WAIT_FOR_CLIENT_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Ignore();
  ConnectionResult connectionResult = connectToMaster();
  TEST_ASSERT_EQUAL_MESSAGE(CONNECTION_FAILURE, connectionResult, "'connectToMaster()' shall fail if 'waitForClient()' "
                                                                  "fails!");
}

void test_connectToMasterShallCloseSocketIfWaitForClientFails(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(WAIT_FOR_CLIENT_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Expect();
  (void)connectToMaster();
}

void test_connectToMasterShallLogWaitForClientFailure(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(WAIT_FOR_CLIENT_FAILURE);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkWaitForClientFailureMessage);
  closeSocket_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallFailIfMoreThanOneClientTriesToConnect(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(MORE_THAN_ONE_CLIENT);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Ignore();
  ConnectionResult connectionResult = connectToMaster();
  TEST_ASSERT_EQUAL_MESSAGE(CONNECTION_FAILURE, connectionResult, "'connectToMaster()' shall fail if more than one "
                                                                  "client tries to connect!");
}

void test_connectToMasterShallCloseSocketIfMoreThanOneClientTriesToConnect(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(MORE_THAN_ONE_CLIENT);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Expect();
  (void)connectToMaster();
}

void test_connectToMasterShallLogMoreThanOneClientTryingToConnect(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(MORE_THAN_ONE_CLIENT);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkMoreThanOneClientMessage);
  closeSocket_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallAcceptClient(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(ONE_CONNECTION_REQUEST_RECEIVED);
  acceptClient_ExpectAndReturn(DUMMY_FILE_DESCRIPTOR_2);
  setNonBlockingSocketOperation_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallFailIfFailingToAcceptClient(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(ONE_CONNECTION_REQUEST_RECEIVED);
  acceptClient_IgnoreAndReturn(ACCEPT_CLIENT_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Ignore();
  ConnectionResult connectionResult = connectToMaster();
  TEST_ASSERT_EQUAL_MESSAGE(CONNECTION_FAILURE, connectionResult, "'connectToMaster()' shall fail if failing to accept "
                                                                  "client!");
}

void test_connectToMasterShallCloseSocketIfFailingToAcceptClient(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(ONE_CONNECTION_REQUEST_RECEIVED);
  acceptClient_IgnoreAndReturn(ACCEPT_CLIENT_FAILURE);
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  closeSocket_Expect();
  (void)connectToMaster();
}

void test_connectToMasterShallLogFailingToAcceptClient(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(ONE_CONNECTION_REQUEST_RECEIVED);
  acceptClient_IgnoreAndReturn(ACCEPT_CLIENT_FAILURE);
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkAcceptFailureMessage);
  closeSocket_Ignore();
  (void)connectToMaster();
}

void test_connectToMasterShallSetNonBlockingSocketOperation(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(ONE_CONNECTION_REQUEST_RECEIVED);
  acceptClient_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR_2);
  setNonBlockingSocketOperation_Expect();
  (void)connectToMaster();
}

void test_connectToMasterShallSucceedIfConnectionSucceeds(void)
{
  openSocket_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR);
  bindSocket_IgnoreAndReturn(BIND_SOCKET_SUCCESS);
  listenToSocket_IgnoreAndReturn(LISTEN_SOCKET_SUCCESS);
  waitForClient_IgnoreAndReturn(ONE_CONNECTION_REQUEST_RECEIVED);
  acceptClient_IgnoreAndReturn(DUMMY_FILE_DESCRIPTOR_2);
  setNonBlockingSocketOperation_Ignore();
  ConnectionResult connectionResult = connectToMaster();
  TEST_ASSERT_EQUAL_MESSAGE(CONNECTION_SUCCESS, connectionResult, "'connectToMaster()' shall succeed if connection "
                                                                  "succeeds!");
}

void test_readFromMasterShallFailIfPassedNullForDestinationBuffer(void)
{
  writeLog_IgnoreAndReturn(LOG_SUCCESS);
  int readResult = readFromMaster(NULL, TEST_BUFFER_SIZE);
  TEST_ASSERT_EQUAL_MESSAGE(READ_FAILURE, readResult, "'readFromMaster()' shall fail if passed 'NULL' for destination "
                                                      "buffer!");
}

void test_readFromMasterShallLogIfPassedNullForDestinationBuffer(void)
{
  writeLog_ExpectAndReturn(EXPECTATION_DEFINED_BY_CALLBACK, LOG_SUCCESS);
  writeLog_StubWithCallback(checkNullPointerMessage);
  (void)readFromMaster(NULL, TEST_BUFFER_SIZE);
}

void test_readFromMasterShallReturnZeroIfPassedDestinationBufferOfSizeZero(void)
{
  int readResult = readFromMaster(readFromMasterDestinationBuffer, ZERO_BYTES);
  TEST_ASSERT_EQUAL_MESSAGE(ZERO_BYTES, readResult, "'readFromMaster()' shall return zero if passed a destination "
                                                    "buffer of size zero!");
}

void test_readFromMasterShallReturnErrorIfReadFromClientFails(void)
{
  readFromClient_IgnoreAndReturn(-1);
  int readResult = readFromMaster(readFromMasterDestinationBuffer, TEST_BUFFER_SIZE);
  TEST_ASSERT_EQUAL_MESSAGE(READ_FAILURE, readResult, "'readFromMaster()' shall fail 'readFromClient()' fails!");
}

void test_readFromMasterShallReturnTheNumberOfReadCharactersIfSuccessful(void)
{
  readFromClient_IgnoreAndReturn(NUMBER_OF_BYTES_READ_FROM_CLIENT);
  int readResult = readFromMaster(readFromMasterDestinationBuffer, TEST_BUFFER_SIZE);
  TEST_ASSERT_EQUAL_MESSAGE(NUMBER_OF_BYTES_READ_FROM_CLIENT, readResult, "'readFromMaster()' return number of read "
                                                                          "characters if successful!");
}

void test_readFromMasterShallPassDestinationBufferToReadFromClient(void)
{
  readFromClient_ExpectAndReturn(readFromMasterDestinationBuffer, TEST_BUFFER_SIZE, NUMBER_OF_BYTES_READ_FROM_CLIENT);
  (void)readFromMaster(readFromMasterDestinationBuffer, TEST_BUFFER_SIZE);
}

void test_terminateMasterConnectionShallCloseSocket(void)
{
  closeSocket_Expect();
  terminateMasterConnection();
}
