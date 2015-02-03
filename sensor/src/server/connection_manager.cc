#include "connection_manager.h"
#include "client.h"
#include "message.h"

#include "classes/logger.h"

void ConnectionManager::Join(ClientPtr participant)
{
    Logger::Log(LogLevel::Info) << "ConnectionManager::Join()";
    connectedClients.insert(participant);
}

void ConnectionManager::Leave(ClientPtr participant)
{
    Logger::Log(LogLevel::Info) << "ConnectionManager::Leave()";
    connectedClients.erase(participant);
}

void ConnectionManager::SendToAll(const Message& msg)
{
    for (auto participant : connectedClients)
        participant->Send(msg);
}

void ConnectionManager::OnRecieveMessage(const Message& msg)
{
    std::string body((char*)msg.body(), msg.GetBodyLength());
    Logger::Log(LogLevel::Info) << "ConnectionManager::RecievedMessage(), length: " << msg.GetBodyLength() << " body: " << body;

    Message returnMessage;
    returnMessage.SetBodyLength(5);
    returnMessage.SetMsgType(1);
    returnMessage.EncodeHeader();
    returnMessage.WriteChar('R');
    returnMessage.WriteChar('E');
    returnMessage.WriteChar('P');
    returnMessage.WriteChar('L');
    returnMessage.WriteChar('Y');

    for (auto participant : connectedClients)
        participant->Send(returnMessage);
}
