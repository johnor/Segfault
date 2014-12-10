#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QMatrix4x4>
#include <QWindow>

class Client : public QObject
{
    Q_OBJECT
public:
    Client()
    {
        QObject::connect(&m_tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        QObject::connect(&m_tcpSocket, SIGNAL(readyRead()), this, SLOT(reciveMatrix()));
    }

    ~Client()
    {
        m_tcpSocket.abort();
    }

    void connect()
    {
        m_tcpSocket.abort();
        m_tcpSocket.connectToHost("localhost", 55555);
    }

public slots:
    void reciveMatrix()
    {
        const int matrixSize = 4 * 4 * sizeof(float);

        if (m_tcpSocket.bytesAvailable() < matrixSize)
            return;

        float data[matrixSize];
        m_tcpSocket.read((char*)data, matrixSize);
        QMatrix4x4 modelMatrix(data);
        emit recivedMatrix(modelMatrix);
    }
    void disconnected()
    {
        qDebug() << "Server disconnected!";
    }

signals:
    void recivedMatrix(const QMatrix4x4);

private:
    QTcpSocket m_tcpSocket;
    QMatrix4x4 m_rotations;
};

#endif // CLIENT_H
