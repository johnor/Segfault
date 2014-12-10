#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QTcpSocket *tcpSocket, QObject *parent = 0);
    ~Client();
    void send(const char * data, qint64 size);

signals:
    void disconnected(Client*);

public slots:
    void socketDisconnected();

private:
    QTcpSocket* m_tcpSocket;
};

#endif // CLIENT_H
