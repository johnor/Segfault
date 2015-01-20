#include "server.h"

#include <QQuaternion>

enum QuaternionValue {SCALAR, X, Y, Z, NUM_VALUES};

Server::Server(QObject *parent)
    : QObject(parent)
{
    m_tcpServer = new QTcpServer();

    QObject::connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(sendQuaternion()));

    m_timer.start(100);

    if (m_tcpServer->listen(QHostAddress::Any, m_port))
    {
        qDebug() << "Server assigned to port: " << m_port;
    }
    else
    {
        qDebug() << "Assigning port:" << m_port << " failed!";
    }
}

Server::~Server()
{
    delete m_tcpServer;
    while (!m_clients.empty())
    {
        delete m_clients.front();
        m_clients.pop_front();
    }
}

void Server::newConnection()
{
    qDebug() << "New connection!!";

    Client* client = new Client(m_tcpServer->nextPendingConnection());

    m_clients.push_back(client);
    QObject::connect(client, SIGNAL(disconnected(Client*)),
                     this, SLOT(clientDisconnected(Client*)));
}

void Server::clientDisconnected(Client* client)
{
    m_clients.removeOne(client);
    delete client;
    qDebug() << "Client disconnected!";
}

void Server::sendQuaternion()
{
    static QQuaternion quaternion;
    quaternion = quaternion * QQuaternion(0.01f, QVector3D(0.0f, 0.0f, 1.0f)).normalized();

    float data[NUM_VALUES] = {quaternion.scalar(), quaternion.x(), quaternion.y(), quaternion.z()};
    qint64 size = sizeof(data);

    for (QList<Client*>::iterator clientItr = m_clients.begin(); clientItr != m_clients.constEnd(); ++clientItr)
    {
        (*clientItr)->send((char*)data, size);
    }
}
