#include "__staticvalue.h"
#include <QDebug>
#include <QSettings>
#include <QFile>
#include "database/provider/__nodeprovider.h"
#include "network/__websocketserver.h"
#include "network/__dispatcher.h"
#include <unistd.h>
#include <QDateTime>


CONFIG_STRUCTURE __staticvalue::config;
QVector<__nodedbs *> __staticvalue::node;
__nodedbs* __staticvalue::currentNode;


__staticvalue::__staticvalue(QObject *parent) : QObject(parent)
{

}

bool __staticvalue::readConfigFile()
{
    //این فایل حاوی اطلاعات گره و اطلاعات اتصال به بانک اطلاعاتی است
    qDebug()<<"Enter readConfigFile";

    if(!QFile::exists("config.conf"))
    {
        return false;
    }

    QSettings settings("config.conf", QSettings::NativeFormat);
    config.name         = settings.value("name").toString();
    config.node_type    = settings.value("node_type").toInt();
    config.node_id      = settings.value("node_id").toInt();
    config.db_port      = settings.value("db_port").toInt();
    config.db_username  = settings.value("db_username").toString();
    config.db_password  = settings.value("db_password").toString();
    config.db_driver    = settings.value("db_driver").toString();
    config.db_name      = settings.value("db_name").toString();
    config.db_host      = settings.value("db_host").toString();

    return true;
}

CONFIG_STRUCTURE *__staticvalue::getConfig()
{
    return &config;
}

void __staticvalue::readNodesInfo()
{
    qDebug()<<"Enter readNodesInfo ";
    __nodeprovider provider;
    QVector<__nodedbs *> data = provider.GetNodeList();
    qDebug()<<"nodes count: "<<data.count();

    for(int i=0;i<data.count();i++)
    {
        __nodedbs* dbs = new __nodedbs();
        dbs->Setnode_ip(data[i]->Getnode_ip());
        dbs->Setnode_node_type(data[i]->Getnode_node_type());
        dbs->Setnode_node_id(data[i]->Getnode_node_id());
        dbs->Setnode_node_name(data[i]->Getnode_node_name());
        dbs->Setnode_port(data[i]->Getnode_port());
        dbs->Setnode_service_port(data[i]->Getnode_service_port());

        if(config.node_type==dbs->Getnode_node_type() && config.node_id==dbs->Getnode_node_id())
        {
            currentNode = dbs;
        }
        else
        {
            node.append(dbs);
        }

    }
}

QVector<__nodedbs *> *__staticvalue::getNodesInfo()
{
    return &node;
}

__nodedbs *__staticvalue::getCurrentNodeInfo()
{
    return currentNode;
}

__nodedbs *__staticvalue::getNodeINfo(int node_type)
{
    for(int i=0;i<node.count();i++)
    {
        if(node[i]->Getnode_node_type()==node_type)
        {
            return node[i];
        }
    }
    return NULL;
}


QString __staticvalue::generateTraceNumber()
{
    QString traceNumber;
    traceNumber.append(QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"));//len=17
    traceNumber.append(QString::number(__staticvalue::getCurrentNodeInfo()->Getnode_node_id()));

    int rand = random()%1000;
    char randomString[3+1] = {0};
    sprintf( randomString, "%03d", rand);

    traceNumber.append(randomString);

    qDebug()<<"generateTraceNumber "<<traceNumber;
    return traceNumber;//len=20
}

qlonglong __staticvalue::getTransactionTime(QString traceNumber)
{
    qDebug()<<"Enter getTransactionTime traceNumber "<<traceNumber;
    QString timeString = traceNumber.mid(0, 17);
    qlonglong transactionTime = QDateTime::fromString(timeString, "yyyyMMddhhmmsszzz").addSecs(-TRANSACTION_CREATE_BLOCK_INTERVAL*2).toMSecsSinceEpoch();
    qDebug()<<"Enter getTransactionTime transactionTime"<<transactionTime;
    return transactionTime;
}


QByteArray __staticvalue::hashBlock(QByteArray &block)
{
    // هش کردن یک بلاک
    return QCryptographicHash::hash(block , QCryptographicHash::Sha256).toHex();
}


