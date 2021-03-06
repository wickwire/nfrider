#include <QCoreApplication>
#include "sslechoserver.h"
#include <stdlib.h>
#include "tcpechoserver.h"
#include <QDebug>
#include <QtGlobal>
#include <QFile>
#include <QObject>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //choose the certificate paths based on OS - developing in different environments nowadays ;)
    #if defined(Q_OS_WIN)
           qDebug()<<  "Windows";
           QFile certFile(QStringLiteral("D:\\QT.CODE\\NFRider\\openssl.certificates\\windows\\fbab8d9c-eaad-4b1d-b774-c62d68503ca0.public.pem"));
           QFile keyFile(QStringLiteral("D:\\QT.CODE\\NFRider\\openssl.certificates\\windows\\fbab8d9c-eaad-4b1d-b774-c62d68503ca0.private.pem"));
    #elif defined(Q_OS_LINUX)
           qDebug()<<  "GNU/Linux";
           QFile certFile(QStringLiteral("/home/wickwire/c92e3eb2-058b-4432-adc7-3d3e531eba0a.private_public/c92e3eb2-058b-4432-adc7-3d3e531eba0a.public.pem"));
           QFile keyFile(QStringLiteral("/home/wickwire/c92e3eb2-058b-4432-adc7-3d3e531eba0a.private_public/c92e3eb2-058b-4432-adc7-3d3e531eba0a.private.pem"));
    #endif

    int wsPort = 7777;
    int tcpPort = 8888;

    SslEchoServer WebSocketServer(wsPort, &certFile, &keyFile);
    TcpEchoServer TcpServer(tcpPort);

    QObject::connect(&WebSocketServer, SIGNAL(wsMessageReceived(QString)), &TcpServer, SLOT(sendDirection(QString)));

    Q_UNUSED(WebSocketServer);
    Q_UNUSED(TcpServer);



    return a.exec();
}
