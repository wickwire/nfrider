#include "tcpechoclient.h"
#include <QtNetwork>
#include <QDebug>


TcpEchoClient::TcpEchoClient(QObject *parent) :
    QObject(parent), networkSession(0)
{

    tcpSocket = new QTcpSocket(this);

    QTimer::singleShot(0, this, SLOT(TcpServerConnect()));

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(getDirection()));

    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(TcpServerConnect()));

}

void TcpEchoClient::TcpServerConnect()
{
    QHostAddress tcpHost("127.0.0.1");
    quint16 tcpHostPort = 8888;
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(tcpHost, tcpHostPort);
    //qDebug() << "Connected to host";
}

void TcpEchoClient::getDirection()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
        return;

    QString nextFortune;
    in >> nextFortune;

    qDebug() << "TS: Msg: " << nextFortune;
    currentFortune = nextFortune;
}

void TcpEchoClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found. Please check the host name and port settings.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.";

        break;
    default:
        qDebug() << "The following error occurred: " << tcpSocket->errorString();
    }

}

void TcpEchoClient::sessionOpened()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();

    qDebug() << "This examples requires that you run the Fortune Server example as well.";

}
