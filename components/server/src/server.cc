#include "server.h"
#include "common/src/logger.h"

Server::Server(asio::io_service& io_service, const U16 port) : acceptor(io_service), socket(io_service)
{
    tcp::endpoint endpoint(tcp::v4(), port);
    acceptor.open(endpoint.protocol());
    acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();

    Accept();
}

ConnectionManager & Server::GetConnectionManager()
{
    return connectionManager;
}

void Server::Accept()
{
    acceptor.async_accept(socket,
        [this](std::error_code ec)
    {
        if (!ec)
        {
            Logger::Log(LogLevel::Info) << "Server::Accept()";
            ClientPtr connectedClient = std::make_shared<ClientSession>(std::move(socket), connectionManager);
            connectionManager.Join(connectedClient);
        }

        Accept();
    });
}


