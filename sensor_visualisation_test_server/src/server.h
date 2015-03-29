#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>

#include "client.h"

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
    ~Server();

public slots:
    void newConnection();
    void clientDisconnected(Client*);
    void sendQuaternion();

private:
    QTcpServer *m_tcpServer;
    QList<Client*> m_clients;
    static const quint16 m_port = 5001;
    QTimer m_timer;
};

#endif // SERVER_H
