#include "sslechoclient.h"
#include <QtCore/QDebug>
#include <QtWebSockets/QWebSocket>
#include <QCoreApplication>

QT_USE_NAMESPACE

SslEchoClient::SslEchoClient(const QUrl &url, QObject *parent) :
    QObject(parent),
    m_webSocket()
{
    connect(&m_webSocket, &QWebSocket::connected, this, &SslEchoClient::onConnected);
    typedef void (QWebSocket:: *sslErrorsSignal)(const QList<QSslError> &);
    connect(&m_webSocket, static_cast<sslErrorsSignal>(&QWebSocket::sslErrors),
            this, &SslEchoClient::onSslErrors);
    m_webSocket.open(QUrl(url));
}

void SslEchoClient::onConnected()
{
    qDebug() << "WebSocket connected";
    //this connect returned client message from the server back to the client, from the example - we're not using it
    //connect(&m_webSocket, &QWebSocket::textMessageReceived,this, &SslEchoClient::onTextMessageReceived);
    //m_webSocket.sendTextMessage(QStringLiteral("Client connected"));
}

void SslEchoClient::onDirectionPressed(QString key)
{
    qDebug() << "Key pressed: " << key;
    m_webSocket.sendTextMessage(key);
}

void SslEchoClient::onDirectionReleased(QString key)
{
    qDebug() << "Key released: " << key;
    m_webSocket.sendTextMessage(key);
}

void SslEchoClient::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
    //qApp->quit();
}

void SslEchoClient::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.

    m_webSocket.ignoreSslErrors();
}
