#include "slave_connection.h"
#include "system_socket.h"
#include "log.h"

ConnectionResult connectToSlave(){
  if (openSocket() < 0)
  {
    (void)writeLog("'connectToSlave()' has failed to open the socket!\n");
    return CONNECTION_FAILURE;
  }

  /*if (setSocketNonBlocking() < 0) {
    (void)writeLog("'connectToSlave()' has failed to set socket nonblocking!\n");
    closeSocket();
    return CONNECTION_FAILURE;
  };*/

  if (connectToSocket() < 0)
  {
    (void)writeLog("'connectToSlave()' has failed to connect to the socket!\n");
    closeSocket();
    return CONNECTION_FAILURE;
  }

  return CONNECTION_SUCCESS;
}
