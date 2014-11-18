#include <QCoreApplication>
#include "sslechoserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SslEchoServer server(1234);

    Q_UNUSED(server);

    return a.exec();
}
