#include <QCoreApplication>
#include "sslechoserver.h"
#include <stdlib.h>
#include "tcpechoserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SslEchoServer WebSocketServer(7777);
    TcpEchoServer TcpServer;

    Q_UNUSED(WebSocketServer);
    Q_UNUSED(TcpServer);

    return a.exec();
}
