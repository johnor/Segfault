#ifndef CONNECTION_MANAGER_H_
#define CONNECTION_MANAGER_H_

#include "components/common/src/numeric_typedefs.h"
#include "components/sensor/src/headers/smart_pointer_typedefs.h"

#include <set>

class Message;

class ConnectionManager
{
public:
    ConnectionManager() = default;
    ~ConnectionManager() = default;

    void Join(ClientPtr client);
    void Leave(ClientPtr client);
    void SendToAll(const Message& msg);

    void OnRecieveMessage(const Message& msg);
private:
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    std::set<ClientPtr> connectedClients;
};

#endif
