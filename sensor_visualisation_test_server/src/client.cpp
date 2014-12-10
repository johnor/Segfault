#include "client.h"

Client::Client(QTcpSocket *tcpSocket, QObject *parent) :
    QObject(parent),
    m_tcpSocket(tcpSocket)
{
    QObject::connect(tcpSocket, SIGNAL(disconnected()),
                     this, SLOT(socketDisconnected()));
}

void Client::socketDisconnected()
{
    emit disconnected(this);
}

Client::~Client()
{
    m_tcpSocket->deleteLater();
}

void Client::send(const char* data, qint64 size)
{
    m_tcpSocket->write(data, size);
}
