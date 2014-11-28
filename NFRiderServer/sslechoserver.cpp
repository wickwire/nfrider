#include "sslechoserver.h"
#include "tcpechoserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>

QT_USE_NAMESPACE

SslEchoServer::SslEchoServer(quint16 port, QFile *certFile, QFile *keyFile, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(Q_NULLPTR),
    m_clients()
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("SSL Echo Server"),
                                              QWebSocketServer::SecureMode,
                                              this);
    QSslConfiguration sslConfiguration;    


    certFile->open(QIODevice::ReadOnly);
    keyFile->open(QIODevice::ReadOnly);
    QSslCertificate certificate(certFile, QSsl::Pem);
    QSslKey sslKey(keyFile, QSsl::Rsa, QSsl::Pem);
    certFile->close();
    keyFile->close();
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setLocalCertificate(certificate);
    sslConfiguration.setPrivateKey(sslKey);
    sslConfiguration.setProtocol(QSsl::TlsV1SslV3);
    m_pWebSocketServer->setSslConfiguration(sslConfiguration);

    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "SSL Echo Server listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &SslEchoServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::sslErrors,
                this, &SslEchoServer::onSslErrors);
    }
}

SslEchoServer::~SslEchoServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void SslEchoServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    qDebug() << "WS: Client Connected";

    connect(pSocket, &QWebSocket::textMessageReceived, this, &SslEchoServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived,
            this, &SslEchoServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &SslEchoServer::socketDisconnected);

    m_clients << pSocket;
}

void SslEchoServer::processTextMessage(QString message)
{

    qDebug() << "WS: Msg: " << message;

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        pClient->sendTextMessage(message);
    }

    emit wsMessageReceived(message);
}

void SslEchoServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        pClient->sendBinaryMessage(message);
    }
}

void SslEchoServer::socketDisconnected()
{
    qDebug() << "WS: Client disconnected";
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void SslEchoServer::onSslErrors(const QList<QSslError> &)
{
    qDebug() << "WS: Ssl errors occurred";
}
