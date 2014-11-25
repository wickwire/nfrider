#ifndef SSLECHOSERVER_H
#define SSLECHOSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QtNetwork/QSslError>
#include <QFile>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class SslEchoServer : public QObject
{
    Q_OBJECT
public:
    explicit SslEchoServer(quint16 port, QFile *certFile, QFile *keyFile, QObject *parent = Q_NULLPTR);
    virtual ~SslEchoServer();

Q_SIGNALS:
    void wsMessageReceived();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void onSslErrors(const QList<QSslError> &errors);

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif //SSLECHOSERVER_H
