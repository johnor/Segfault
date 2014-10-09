#include "master_connection.h"
#include "system_socket.h"
#include "log.h"

ConnectionResult connectToMaster(void)
{
  if (openSocket() < 0)
  {
    (void)writeLog("'connectToMaster()' has failed to open the socket!\n");
    return CONNECTION_FAILURE;
  }

  if (bindSocket() < 0)
  {
    (void)writeLog("'connectToMaster()' has failed to bind the socket!\n");
    closeSocket();
    return CONNECTION_FAILURE;
  }

  if (listenToSocket() < 0)
  {
    (void)writeLog("'connectToMaster()' has failed to listen to the socket!\n");
    closeSocket();
    return CONNECTION_FAILURE;
  }

  int waitResult = waitForClient();

  if (waitResult == 0)
  {
    (void)writeLog("'connectToMaster()': Wait for client timed out!\n");
    closeSocket();
    return CONNECTION_TIMEOUT;
  }

  if (waitResult < 0)
  {
    (void)writeLog("'connectToMaster()': Wait for client failed!\n");
    closeSocket();
    return CONNECTION_FAILURE;
  }

  if (waitResult != 1)
  {
    (void)writeLog("'connectToMaster()': Wait for client received more than one connection requests!\n");
    closeSocket();
    return CONNECTION_FAILURE;
  }

  if (acceptClient() < 0)
  {
    (void)writeLog("'connectToMaster()' failed to accept client!\n");
    closeSocket();
    return CONNECTION_FAILURE;
  }

  setNonBlockingSocketOperation();

  return CONNECTION_SUCCESS;
}

int readFromMaster(char* const destinationBuffer, const size_t destinationBufferSize)
{
  if (destinationBuffer == NULL)
  {
    (void)writeLog("'readFromMaster()' called with 'NULL' for destination buffer!\n");
    return READ_FAILURE;
  }
  if (destinationBufferSize == 0)
  {
    return 0;
  }

  return readFromClient(destinationBuffer, destinationBufferSize);
}

void terminateMasterConnection(void)
{
  closeSocket();
}
