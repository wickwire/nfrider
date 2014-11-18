#ifndef SSLECHOCLIENT_H
#define SSLECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QUrl>

QT_FORWARD_DECLARE_CLASS(QWebSocket)

class SslEchoClient : public QObject
{
    Q_OBJECT
public:
    explicit SslEchoClient(const QUrl &url, QObject *parent = Q_NULLPTR);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onSslErrors(const QList<QSslError> &errors);

private:
    QWebSocket m_webSocket;

public slots:
    void onDirectionPressed(QString key);
    void onDirectionReleased(QString key);
};

#endif // SSLECHOCLIENT_H
