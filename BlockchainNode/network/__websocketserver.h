#ifndef __WEBSOCKETSERVER_H
#define __WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QMutex>
#include "__staticvalue.h"
#include <network/__iso.h>

class __websocketserver : public QWebSocketServer
{
    Q_OBJECT
public:
    explicit __websocketserver(const QString &serverName, SslMode secureMode, QObject *parent = Q_NULLPTR);
    bool startListen(int port);

signals:
    void signal_receiveNewTransaction(ISO_STRUCTURE str);

private slots:
    void slot_newConnection();
    void slot_textFrameReceived(QString data ,bool islast);
    void slot_socketDisconnected();
    void slot_error(QAbstractSocket::SocketError err);
    void slot_sslErrors(QList<QSslError> er);
    void senReportResualt(QByteArray message, QString key);

protected:
    QHash<QString , QByteArray> socketHash; //ip message
    QHash<QString , QWebSocket*> socketHash2; //ip socket
    QMutex socketMutex;

private:
    __iso iso;

    void completeFlow(ISO_STRUCTURE isoStruct, QWebSocket* webSocket);
    void responseToPOS(ISO_STRUCTURE isoStruct, QWebSocket* webSocket);
    QString getKey(QString ip, int port);
};

#endif // __WEBSOCKETSERVER_H
