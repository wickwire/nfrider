#ifndef TCPECHOCLIENT_H
#define TCPECHOCLIENT_H

#include <QObject>
#include <QtNetwork>

class QTcpSocket;
class QNetworkSession;

class TcpEchoClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpEchoClient(QObject *parent = 0);

private slots:
    void requestNewFortune();
    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();

private:
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;
    QNetworkSession *networkSession;

};

#endif // TCPECHOCLIENT_H
