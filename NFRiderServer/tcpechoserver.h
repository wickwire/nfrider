#ifndef TCPECHOSERVER_H
#define TCPECHOSERVER_H

#include <QtCore/QObject>

class QTcpServer;
class QNetworkSession;

class TcpEchoServer : public QObject
{
    Q_OBJECT

public:
    TcpEchoServer(QObject *parent = 0);

private slots:
    void sessionOpened();

private:
    QTcpServer *tcpServer;
    QNetworkSession *networkSession;
    int port;
};

#endif
