#include "__websocketserver.h"
#include <QWebSocket>
#include <QJsonParseError>
#include <QJsonObject>
#include "network/__dispatcher.h"
#include <unistd.h>
#include "report/__reportengin.h"

__websocketserver::__websocketserver(const QString &serverName, SslMode secureMode, QObject *parent) :
    QWebSocketServer(serverName,secureMode,parent)
{
}

bool __websocketserver::startListen(int port)
{
    //باز کردن سوکت برای دریافت اطلاعات از نودهای دیگر
    bool ok = listen(QHostAddress::AnyIPv4 , port);
    qDebug()<<"listen on port:"<<port<<ok;
    if(ok)
    {
        connect(this , SIGNAL(newConnection()) , this , SLOT(slot_newConnection()));
        connect(this , SIGNAL(sslErrors(QList<QSslError>)) , this , SLOT(slot_sslErrors(QList<QSslError>)));
        return true;
    }
    return false;
}

void __websocketserver::slot_newConnection()
{
    qDebug()<<"slot_newConnection from ";
    qDebug()<<"Enter slot_newConnection in tcpserver";
    if(!hasPendingConnections())
    {
        qDebug()<<"no exist PendingConnections";
        return;
    }

    QWebSocket* webSocket = this->nextPendingConnection();
    QString ip = webSocket->peerAddress().toString().trimmed();

    socketMutex.lock();
    socketHash2.insert(getKey(ip, webSocket->localPort()) , webSocket);
    socketMutex.unlock();

    connect(webSocket , SIGNAL(textFrameReceived(QString,bool)) , this , SLOT(slot_textFrameReceived(QString,bool)));
    connect(webSocket , SIGNAL(disconnected()) , this , SLOT(slot_socketDisconnected()));
    connect(webSocket , SIGNAL(error(QAbstractSocket::SocketError)) , this , SLOT(slot_error(QAbstractSocket::SocketError)));
}

void __websocketserver::slot_textFrameReceived(QString data, bool islast)
{
    QWebSocket* webSocket = static_cast<QWebSocket*> (sender());

    QString ip;
    QString key;
    quint16 port;
    QByteArray buffer;

    ip   = webSocket->peerAddress().toString().trimmed();
    port = webSocket->localPort();
    key  = ip+"_"+QString::number(port);

    buffer = socketHash.value(key , "");
    buffer.append(data);

    if(islast)
    {
        socketHash.insert(key , "");

        ISO_STRUCTURE isoStruct;
        iso.parseMessage(buffer, isoStruct);
        qDebug()<<"Enter slot_textFrameReceived from ip: "<<ip<<webSocket->peerPort()<<isoStruct.request<<isoStruct.trace_number;// << buffer;

        if(isoStruct.request == REQUEST_TRANSACTION)
        {
            emit signal_receiveNewTransaction(isoStruct);
            completeFlow(isoStruct, webSocket);
        }
        else if(isoStruct.request == REQUEST_REPORT)
        {
            //report
            __reportengin *rp = new __reportengin(getKey(ip, port), isoStruct.trace_number);
            connect(rp, SIGNAL(finished()), rp, SLOT(deleteLater()));
            connect(rp, SIGNAL(sendReportResponse(QByteArray,QString)), this, SLOT(senReportResualt(QByteArray,QString)), Qt::AutoConnection);
            rp->start();
        }
    }
}

void __websocketserver::slot_socketDisconnected()
{
    //قطع شدن ارتباط یکی از گره ها
    QWebSocket* webSocket = static_cast<QWebSocket*> (sender());
    QString ip = webSocket->peerAddress().toString().trimmed();

    qDebug()<<"Enter slot_socketDisconnected from ip: "<<ip ;

    socketMutex.lock();
    socketHash2.remove(getKey(ip, webSocket->localPort()));
    socketMutex.unlock();
}

void __websocketserver::slot_error(QAbstractSocket::SocketError err)
{
    QWebSocket* webSocket = static_cast<QWebSocket*> (sender());
    QString ip = webSocket->peerAddress().toString().trimmed();

    qDebug()<<Q_FUNC_INFO<<" ip:"<<ip<<" with error:"<<err<<" and errorString "<<webSocket->errorString();
}

void __websocketserver::slot_sslErrors(QList<QSslError> er)
{
    qDebug()<<"slot_sslErrors "<<er;
}


void __websocketserver::completeFlow(ISO_STRUCTURE isoStruct, QWebSocket *webSocket)
{
    int fromNodeType    = isoStruct.node_type;
    int currentNodeType = __staticvalue::getConfig()->node_type;
    qDebug()<<"completeFlow is_new_transaction "<<isoStruct.is_new_transaction<<" from:"<<fromNodeType <<" current"<<currentNodeType;

    if(isoStruct.is_new_transaction)
    {
        //صرفا برای ثبت در دفاتر دیگر

        isoStruct.node_type             = __staticvalue::getConfig()->node_type;
        isoStruct.node_id               = __staticvalue::getConfig()->node_id;
        isoStruct.is_new_transaction    = false;
        isoStruct.response_time         = QDateTime::currentMSecsSinceEpoch();

        usleep(100*1000);
        __dispatcher::getInstance()->dispatch(isoStruct);
        usleep(100*1000);


        //ارسال تراکنش برای گام بعدی
        //یعنی از پرداخت الکترونیک به شاپرک - از شاپرک به شتاب و از شتاب به سامانه متمرکز بانک
        isoStruct.is_new_transaction    = true;
        __nodedbs* node = NULL;

        //مسیر رفت تراکنش از پوز تا سویچ بانک
        if(fromNodeType==NODE_POS && currentNodeType==NODE_PSP)
        {
            isoStruct.trace_number = __staticvalue::generateTraceNumber();

            responseToPOS( isoStruct, webSocket);

            node = __staticvalue::getNodeINfo(NODE_SHAPARAK);
        }
        else if(fromNodeType==NODE_PSP && currentNodeType==NODE_SHAPARAK)
        {
            node = __staticvalue::getNodeINfo(NODE_SHETAB);
        }
        else if(fromNodeType==NODE_SHAPARAK && currentNodeType==NODE_SHETAB)
        {
            node = __staticvalue::getNodeINfo(NODE_BANK_SWITCH);
        }
        //مسیر برگشت تراکنش از سویچ بانک تا پوز
        else if(fromNodeType==NODE_SHETAB && currentNodeType==NODE_BANK_SWITCH)
        {
            node = __staticvalue::getNodeINfo(NODE_SHETAB);
        }
        else if(fromNodeType==NODE_BANK_SWITCH && currentNodeType==NODE_SHETAB)
        {
            node = __staticvalue::getNodeINfo(NODE_SHAPARAK);
        }
        else if(fromNodeType==NODE_SHETAB && currentNodeType==NODE_SHAPARAK)
        {
            node = __staticvalue::getNodeINfo(NODE_PSP);
        }
        if(node)
        {
            qDebug()<<"Send transaction to next node "<<node->Getnode_ip()<<node->Getnode_port();

            __dispatcher::getInstance()->sendMessageToNode(node->Getnode_ip(), node->Getnode_port(), isoStruct);

        }
    }
}

void __websocketserver::responseToPOS(ISO_STRUCTURE isoStruct, QWebSocket *webSocket)
{
    QByteArray request;
    __iso iso;
    iso.createMessage(isoStruct, request);

    qDebug()<<"responseToPOS "<<webSocket->peerAddress()<<webSocket->state();
    webSocket->sendTextMessage(request);
}

QString __websocketserver::getKey(QString ip, int port)
{
    return "ws://"+ip+":"+QString::number(port);
}


void __websocketserver::senReportResualt(QByteArray message, QString key)
{
    qDebug()<<"senReportResualt "<<key;
    if(socketHash2.contains(key))
    {
        qDebug()<<"Find report socket on key:"<<key;
        QWebSocket* webSocket = socketHash2.value(key);
        if(webSocket)
            webSocket->sendTextMessage(message);
    }
}
