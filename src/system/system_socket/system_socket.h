#ifndef SYSTEM_SOCKET_H_
#define SYSTEM_SOCKET_H_

#include <stddef.h>

int openSocket(void);
int bindSocket(void);
int listenToSocket(void);
int connectToSocket(void);
int waitForClient(void);
int acceptClient(void);
void setNonBlockingSocketOperation(void);
int setSocketNonBlocking();
int readFromClient(char* destinationBuffer, size_t destinationBufferSize);
int writeToClient(const char* message);
int writeToSocket(const char* message);
void closeSocket(void);

#endif /* SYSTEM_SOCKET_H_ */
