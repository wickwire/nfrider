#include <QCoreApplication>
#include "tcpechoclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpEchoClient TcpClient;

    Q_UNUSED(TcpClient);

    return a.exec();
}
