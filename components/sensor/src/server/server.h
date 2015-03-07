#ifndef SERVER_H_
#define SERVER_H_

#include <asio.hpp>

#include "message.h"
#include "client.h"
#include "connection_manager.h"

using asio::ip::tcp;

class Server
{
public:
    Server(asio::io_service& io_service, const U16 port);
    ~Server() = default;

    ConnectionManager &GetConnectionManager();

private:
    Server(const Server&) = delete;
    const Server& operator=(const Server&) = delete;

    void Accept();

    tcp::acceptor acceptor;
    tcp::socket socket;
    ConnectionManager connectionManager;
};

#endif