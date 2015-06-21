#ifndef CONNECTION_MANAGER_H_
#define CONNECTION_MANAGER_H_

#include "client.h"

#include <set>

class Message;

class ConnectionManager
{
public:
    ConnectionManager() = default;
    ~ConnectionManager() = default;

    void Join(Client::Ptr client);
    void Leave(Client::Ptr client);
    void SendToAll(Message& msg);

    void OnRecieveMessage(const Message& msg);
private:
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    std::set<Client::Ptr> connectedClients;
};

#endif
