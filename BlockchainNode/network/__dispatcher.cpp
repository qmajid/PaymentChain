#include "__dispatcher.h"
#include "QDebug"
#include <QtConcurrent/QtConcurrent>
#include "network/__iso.h"

QHash<QString, QWebSocket*> __dispatcher::nodeHash;
__dispatcher* __dispatcher::instance;

__dispatcher::__dispatcher(QObject *parent)
{

}

__dispatcher *__dispatcher::getInstance()
{
    if(!instance)
    {
        instance = new __dispatcher();
    }
    return instance;
}

void __dispatcher::init()
{
    for(int i=0;i<__staticvalue::getNodesInfo()->count();i++)
    {
        __nodedbs * node =  __staticvalue::getNodesInfo()->at(i);

        QWebSocket* webSocket = new QWebSocket();
        connect(webSocket, SIGNAL(connected()) , this, SLOT(onConnected()));
        connect(webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

        QString url = mekeUrl(node->Getnode_ip(), node->Getnode_port());
        webSocket->open(url);

        nodeHash.insert(url, webSocket);
    }
}



void __dispatcher::onConnected()
{
    QWebSocket* webSocket = static_cast<QWebSocket*>(sender());
    //qDebug()<<"__dispatcher::onConnected "<<webSocket->requestUrl();

    QByteArray request = nodeMessageBuffer.value(webSocket->requestUrl().toString());
    if(!request.isEmpty())
    {
        qDebug()<<"exist nodeMessageBuffer for "<<webSocket->requestUrl().toString();
        webSocket->sendTextMessage(request);
    }
}

void __dispatcher::error(QAbstractSocket::SocketError er)
{
    QWebSocket* webSocket = static_cast<QWebSocket*>(sender());
    qDebug()<<"__dispatcher::error "<<webSocket->requestUrl() << er;
}

void __dispatcher::dispatch(ISO_STRUCTURE &input)
{
    qDebug()<<"------------ dispatch start ----------------";
    for(int i=0;i<__staticvalue::getNodesInfo()->count();i++)
    {
        __nodedbs * node =  __staticvalue::getNodesInfo()->at(i);
        sendMessageToNode(node->Getnode_ip(), node->Getnode_port(), input);
    }
    qDebug()<<"------------ dispatch end ----------------";
}



void __dispatcher::bufferMessage(ISO_STRUCTURE &input)
{
    QString url;
    QByteArray request;
    __iso iso;
    for(int i=0;i<__staticvalue::getNodesInfo()->count();i++)
    {
        __nodedbs * node =  __staticvalue::getNodesInfo()->at(i);
        url = mekeUrl(node->Getnode_ip(), node->Getnode_port());
        iso.createMessage(input, request);
        nodeMessageBuffer.insertMulti(url, request);
    }
}

void __dispatcher::bufferMessage(QString ip, int port, ISO_STRUCTURE input)
{
    __iso iso;
    QByteArray request;
    QString url = mekeUrl(ip, port);
    iso.createMessage(input, request);
    nodeMessageBuffer.insertMulti(url, request);
}

void __dispatcher::releaseBuffer()
{
    QString key ;
    QList<QString> keyList = nodeMessageBuffer.keys();
    QList<QByteArray> valueList;
    for(int i=0; i<keyList.count(); i++)
    {
        key = keyList.at(i);
        QWebSocket* webSocket = nodeHash.value(key);


        valueList.clear();
        valueList = nodeMessageBuffer.values(key);
        qDebug()<<"releaseBuffer sendMessageToNode "<<webSocket->state() << keyList.at(i)<< valueList.count();
        for(int j=0;i<valueList.count(); j++)
        {
            webSocket->sendTextMessage(valueList.at(i));
        }
    }
}

void __dispatcher::sendMessageToNode(QString ip, int port, ISO_STRUCTURE input)
{
    QString url = mekeUrl(ip, port);

    QByteArray request;
    __iso iso;
    iso.createMessage(input, request);

    QWebSocket* webSocket = nodeHash.value(url);
    qDebug()<<"QtConcurrent sendMessageToNode "<<ip<<port<<webSocket->state();

    nodeMessageBuffer.insert(url, request);
    if(webSocket->state() == QAbstractSocket::ConnectedState)
    {
        nodeMessageBuffer.remove(url);
        webSocket->sendTextMessage(request);
    }
    else if(webSocket->state() == QAbstractSocket::UnconnectedState)
    {
        webSocket->open(url);
    }
}

QString __dispatcher::mekeUrl(QString ip, int port)
{
    return "ws://"+ip+":"+QString::number(port);
}

