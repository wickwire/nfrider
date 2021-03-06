#ifndef TCPECHOSERVER_H
#define TCPECHOSERVER_H

#include <QtCore/QObject>
#include <QStringList>

class QTcpServer;
class QTcpSocket;
class QNetworkSession;

class TcpEchoServer : public QObject
{
    Q_OBJECT

public:
    TcpEchoServer(quint16 port, QObject *parent = 0);

private slots:
    void clientConnected();
    void sessionOpened(quint16 port);

private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QNetworkSession *networkSession;
    int port;

public slots:
    void sendDirection(QString tcpMessage);

};

#endif
