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
    virtual void Start() = 0;
    virtual void Stop() = 0;
};


class ClientSession
    : public Client,
      public std::enable_shared_from_this<ClientSession>
{
public:
    ClientSession(tcp::socket socket, ConnectionManager& room);

    virtual void Send(const Message& msg) override;
    virtual void Start() override;
    virtual void Stop() override;

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
