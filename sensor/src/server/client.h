#ifndef SESSION_H_
#define SESSION_H_

#include <asio.hpp>

#include "message.h"
#include "connection_manager.h"

using asio::ip::tcp;

class Client
{
public:
    virtual ~Client() {}
    virtual void Send(const Message& msg) = 0;
};


class ClientSession
    : public Client,
      public std::enable_shared_from_this<ClientSession>
{
public:
    ClientSession(tcp::socket socket, ConnectionManager& room);

    void Start();
    void Send(const Message& msg);

private:
    void ReadHeader();
    void ReadBody();
    void Write();

    tcp::socket socket;
    ConnectionManager &connectionManager;
    Message currentReadMessage;
    MessageQueue writeMessages;
};


#endif
