#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "sslechoclient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    SslEchoClient client(QUrl(QStringLiteral("wss://localhost:1234")));
    Q_UNUSED(client);

    engine.rootContext()->setContextProperty("sshclient", &client);

    return app.exec();
}
