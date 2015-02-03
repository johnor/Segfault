#ifndef CONNECTED_CLIENTS_H_
#define CONNECTED_CLIENTS_H_

#include "headers/smart_pointer_typedefs.h"

#include <set>

class Message;

class ConnectionManager
{
public:
    ConnectionManager() = default;

    void Join(ClientPtr participant);
    void Leave(ClientPtr participant);
    void SendToAll(const Message& msg);

    void OnRecieveMessage(const Message& msg);
private:
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    std::set<ClientPtr> connectedClients;
};

#endif
