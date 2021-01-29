#ifndef __DISPATCHER_H
#define __DISPATCHER_H

#include <QObject>
#include <__staticvalue.h>
#include <QHash>
#include <QWebSocket>

class __dispatcher : public QObject
{
    Q_OBJECT

private:
    explicit __dispatcher(QObject *parent = nullptr);

public:
    void init();
    static __dispatcher* getInstance();
    void dispatch(ISO_STRUCTURE &input);
    void sendMessageToNode(QString ip, int port, ISO_STRUCTURE input);

    void bufferMessage(ISO_STRUCTURE &input);
    void bufferMessage(QString ip, int port, ISO_STRUCTURE input);
    void releaseBuffer();

signals:

private slots:
    void onConnected();
    void error(QAbstractSocket::SocketError er);

private:
    QString mekeUrl(QString ip, int port);

    static QHash<QString, QWebSocket*> nodeHash;
    static __dispatcher* instance;
    QHash<QString, QByteArray> nodeMessageBuffer;// نود بالا نبوده و برای یک مرتبه بافر میشود
};

#endif // __DISPATCHER_H
