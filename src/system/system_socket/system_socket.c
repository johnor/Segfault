#include "system_socket.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define CALL_OF_DUTY_BLACK_OPS_PORT  3071  // Surely won't run on our target :)
#define RB_IP_ADDRESS                "192.168.0.199"
#define PORT_NUMBER                  CALL_OF_DUTY_BLACK_OPS_PORT

static int sockfd = -1;
static int newsockfd = -1;
static struct sockaddr_in serv_addr;
static struct sockaddr_in cli_addr;
static socklen_t clilen = sizeof(cli_addr);

int openSocket(void)
{
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  return sockfd;
}

int bindSocket(void)
{
  if (sockfd < 0)
  {
    return -1;
  }

  bzero((char*)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PORT_NUMBER);

  return bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
}

int listenToSocket(void)
{
  return listen(sockfd, 5);
}

int connectToSocket(void)
{
  bzero((char*)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT_NUMBER);
  serv_addr.sin_addr.s_addr = inet_addr(RB_IP_ADDRESS);

  return connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
}

int waitForClient(void)
{
  // Example from http://stackoverflow.com/questions/14045064/how-to-accept-socket-with-timeout
  int selectResult;
  struct timeval tv;
  fd_set fileDescriptorSet;
  FD_ZERO(&fileDescriptorSet);
  FD_SET(sockfd, &fileDescriptorSet);
  tv.tv_sec = (long)5;
  tv.tv_usec = 0;

  // 'int nfds' - The highest file descriptor in all given sets plus one
  // - http://www.techrepublic.com/article/using-the-select-and-poll-methods/
  // Also see man page for 'select()'
  selectResult = select(sockfd + 1, &fileDescriptorSet, (fd_set*)0, (fd_set*)0, &tv);
  return selectResult;
}

int acceptClient(void)
{
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  return newsockfd;
}

void setNonBlockingSocketOperation(void)
{
  (void)fcntl(newsockfd, F_SETFL, O_NONBLOCK);
}

int readFromClient(char* destinationBuffer, size_t destinationBufferSize)
{
  if (destinationBuffer == NULL)
  {
    return -1;
  }

  if (destinationBufferSize == 0)
  {
    return -1;
  }

  bzero(destinationBuffer, destinationBufferSize);
  return read(newsockfd, destinationBuffer, (destinationBufferSize - 1));  // Leave space for terminating 'null' char
}

int writeToClient(const char* message)
{
  return write(newsockfd, message, strlen(message));
}

int writeToSocket(const char* message)
{
  return write(sockfd, message, strlen(message));
}

void closeSocket(void)
{
  if (newsockfd >= 0)
  {
    close(newsockfd);
  }

  if (sockfd >= 0)
  {
    close(sockfd);
  }
}
