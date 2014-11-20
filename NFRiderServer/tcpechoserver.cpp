#include <QtNetwork>
#include <QDebug>
#include <stdlib.h>
#include "tcpechoserver.h"

TcpEchoServer::TcpEchoServer(quint16 port, QObject *parent)
:   QObject(parent), tcpServer(0), networkSession(0)
{
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        qDebug() << "Opening network session.";
        networkSession->open();
    } else {
        sessionOpened(port);
    }

    fortunes << tr("Move forward")
             << tr("Turn left")
             << tr("Move backward")
             << tr("Turn right");

    //connect(tcpServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));

    QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SIGNAL(badjoras()));
        timer->start(20000);

    //connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendDirection()));

    connect(this, SIGNAL(badjoras()), this, SLOT(sendDirection()));
}

void TcpEchoServer::sessionOpened(quint16 port)
{
    // Save the used configuration
    if (networkSession) {
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
    }

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Unable to start the server";
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() << "TCP Echo Server listening on port " << port;
}


void TcpEchoServer::clientConnected()
{
    qDebug() << "TCP: Client just connected!";
}

void TcpEchoServer::sendDirection()
{
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out << (quint16)0;
        out << fortunes.at(qrand() % fortunes.size());
        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));

        QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
        connect(clientConnection, SIGNAL(disconnected()),
                clientConnection, SLOT(deleteLater()));

        clientConnection->write(block);
        clientConnection->disconnectFromHost();
    //! [5]
}

