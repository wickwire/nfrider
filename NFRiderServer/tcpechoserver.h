#ifndef TCPECHOSERVER_H
#define TCPECHOSERVER_H

#include <QtCore/QObject>
#include <QStringList>

class QTcpServer;
class QNetworkSession;

class TcpEchoServer : public QObject
{
    Q_OBJECT

public:
    TcpEchoServer(quint16 port, QObject *parent = 0);

private slots:
    void clientConnected();
    void sessionOpened(quint16 port);
    void sendDirection();

private:
    QTcpServer *tcpServer;
    QNetworkSession *networkSession;
    int port;
    QStringList fortunes;
};

#endif
