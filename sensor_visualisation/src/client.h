#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QMatrix4x4>//TODO: remove
#include <QQuaternion>
#include <QWindow>

class Client : public QObject
{
    Q_OBJECT
public:
    Client():
        m_host("localhost"),
        m_port(5001)
    {
        QObject::connect(&m_tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
        QObject::connect(&m_tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        QObject::connect(&m_tcpSocket, SIGNAL(readyRead()), this, SLOT(reciveQuaternion()));
        QObject::connect(&m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(reciveSocketError(QAbstractSocket::SocketError)));

        QObject::connect(&m_reconnectTimer, SIGNAL(timeout()), this, SLOT(tryToConnect()));
    }

    ~Client()
    {
        m_tcpSocket.abort();
    }

public slots:
    void tryToConnect()
    {
        m_reconnectTimer.stop();

        m_tcpSocket.abort();
        qDebug() << "Tring to connect to" << m_host << ":" << m_port;
        m_tcpSocket.connectToHost(m_host, m_port);
    }

    void connected()
    {
        qDebug() << "Connected to " << m_host << ":" << m_port;
    }

    void disconnected()
    {
        qDebug() << "Server disconnected!";
        reconnectLater();
    }

    void reciveSocketError(QAbstractSocket::SocketError e)
    {
        Q_UNUSED(e)
        qDebug() << m_tcpSocket.errorString();
        reconnectLater();
    }

    void reciveQuaternion()
    {
        static bool recivedHeader = false;
        static int headerData[2];
        static float bodyData[100];

        const int headerSize = sizeof(headerData);

        if (!recivedHeader)
        {
            if (m_tcpSocket.bytesAvailable() < headerSize)
                return;

            m_tcpSocket.read((char*)headerData, headerSize);
            recivedHeader = true;
        }
        const int bodySize = headerData[0];
        const int messageType = headerData[1];

        if (m_tcpSocket.bytesAvailable() < bodySize)
            return;

        m_tcpSocket.read((char*)bodyData, bodySize);
        recivedHeader = false;

        switch (messageType)
        {
            case 3:
                QQuaternion quaternion(bodyData[0], bodyData[1], bodyData[2], bodyData[3]);
                emit recivedQuaternion(quaternion);
                break;
        }
    }

signals:
    void recivedQuaternion(const QQuaternion);

private:
    void reconnectLater()
    {
        m_reconnectTimer.start(3000);
    }

private:
    QString m_host;
    int m_port;
    QTimer m_reconnectTimer;
    QTcpSocket m_tcpSocket;
    QMatrix4x4 m_rotations;
};

#endif // CLIENT_H
