#include "connection_manager.h"
#include "client.h"
#include "message.h"

#include "components/common/src/logger.h"

void ConnectionManager::Join(Client::Ptr client)
{
    Logger::Log(LogLevel::Info) << "ConnectionManager::Join()";
    connectedClients.insert(client);
    client->Start();
}

void ConnectionManager::Leave(Client::Ptr client)
{
    Logger::Log(LogLevel::Info) << "ConnectionManager::Leave()";
    connectedClients.erase(client);
    client->Stop();
}

void ConnectionManager::SendToAll(Message& msg)
{
    msg.EncodeHeader();

    for (auto client : connectedClients)
    {
        client->Send(msg);
    }
}

void ConnectionManager::OnRecieveMessage(const Message& msg)
{
    std::string body((char*)msg.body(), msg.GetBodyLength());
    Logger::Log(LogLevel::Info) << "ConnectionManager::RecievedMessage(), length: " << msg.GetBodyLength() << " body: " << body;
}
