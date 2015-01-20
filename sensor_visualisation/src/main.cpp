#include "window.h"
#include "client.h"

#include <QGuiApplication>
#include <QQuaternion>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    Client client;
    OpenGLWindow window;
    QObject::connect(&client, SIGNAL(recivedQuaternion(QQuaternion)), &window, SLOT(renderNow(QQuaternion)));
    client.tryToConnect();

    return app.exec();
}
