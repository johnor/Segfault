#include "window.h"
#include "client.h"

#include <QGuiApplication>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    Client client;
    OpenGLWindow window;
    QObject::connect(&client, SIGNAL(recivedMatrix(QMatrix4x4)), &window, SLOT(renderNow(QMatrix4x4)));
    client.connect();

    return app.exec();
}
