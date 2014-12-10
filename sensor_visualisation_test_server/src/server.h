#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QMatrix4x4>

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
    void sendMatrix();

private:
    QTcpServer *m_tcpServer;
    QList<Client*> m_clients;
    static const quint16 m_port = 55555;
    QMatrix4x4 m_matrix;
    QTimer m_timer;
};

#endif // SERVER_H
