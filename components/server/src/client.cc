#include "client.h"
#include "connection_manager.h"
#include "common/src/logger.h"

ClientSession::ClientSession(tcp::socket socket, ConnectionManager& connectionManager)
: socket{std::move(socket)}, connectionManager(connectionManager)
{
}

void ClientSession::Start()
{
    Logger::Log(LogLevel::Info) << "ClientSession::Start()";
    ReadHeader();
}

void ClientSession::Stop()
{
    Logger::Log(LogLevel::Info) << "ClientSession::Stop()";
    socket.close();
}

void ClientSession::Send(const Message& msg)
{
    Logger::Log(LogLevel::Info) << "ClientSession::Send()";
    const bool writeInProgress = !writeMessages.empty();

    writeMessages.push_back(msg);
    if (!writeInProgress)
    {
        Write();
    }
}

void ClientSession::ReadHeader()
{
    Logger::Log(LogLevel::Info) << "ClientSession::ReadHeader()";
    auto self(shared_from_this());
    asio::async_read(socket,
                     asio::buffer(currentReadMessage.data(), Message::headerLength),
                     [this, self](std::error_code errorCode, std::size_t /*length*/)
    {
        if (!errorCode && currentReadMessage.DecodeHeader())
        {
            Logger::Log(LogLevel::Info) << "ClientSession::ReadHeader() finished";
            ReadBody();
        }
        else
        {
            Logger::Log(LogLevel::Error) << errorCode;
            connectionManager.Leave(shared_from_this());
        }
    });
}

void ClientSession::ReadBody()
{
    Logger::Log(LogLevel::Info) << "ClientSession::ReadBody()";
    auto self(shared_from_this());
    asio::async_read(socket,
                     asio::buffer(currentReadMessage.body(), currentReadMessage.GetBodyLength()),
                     [this, self](std::error_code errorCode, std::size_t /*length*/)
    {
        if (!errorCode)
        {
            Logger::Log(LogLevel::Info) << "ClientSession::ReadBody() finished";
            connectionManager.OnRecieveMessage(currentReadMessage);
            ReadHeader();
        }
        else
        {
            Logger::Log(LogLevel::Error) << errorCode;
            connectionManager.Leave(shared_from_this());
        }
    });
}

void ClientSession::Write()
{
    auto self(shared_from_this());
    asio::async_write(socket,
                      asio::buffer(writeMessages.front().data(),
                      writeMessages.front().getLength()),
                      [this, self](std::error_code errorCode, std::size_t /*length*/)
    {
        if (!errorCode)
        {
            writeMessages.pop_front();
            if (!writeMessages.empty())
            {
                Write();
            }
        }
        else
        {
            connectionManager.Leave(shared_from_this());
        }
    });
}
