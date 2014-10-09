#ifndef MASTER_CONNECTION_H_
#define MASTER_CONNECTION_H_

#include "type.h"

#define READ_FAILURE  -1

typedef enum
{
  CONNECTION_SUCCESS,
  CONNECTION_FAILURE,
  CONNECTION_TIMEOUT
} ConnectionResult;

/**
 * Create an internet socket, bind the socket to a compile-time defined
 * port, listen to the socket and await master connection for a finite
 * amount of time. Accept the master connection if it arrives.
 *
 * @return 'CONNECTION_SUCCESS'    Master has established connection
 * @return 'CONNECTION_FAILURE'    Master did not establish connection within
 *                                 the finite amount of time
 */
ConnectionResult connectToMaster(void);

/**
 * Non-blocking read from the socket that connects to the master
 *
 * @param  destinationBuffer        Pointer to where to store the read data
 * @param  destinationBufferSize    Size of 'destinationBuffer'
 *
 * @return    Less than zero if read failed
 * @return    Number of read characters if successful
 *
 */
int readFromMaster(char* const destinationBuffer, const size_t destinationBufferSize);

/**
 * Close all sockets and file descriptors that are open to the master
 */
void terminateMasterConnection(void);

#endif /* MASTER_CONNECTION_H_ */
