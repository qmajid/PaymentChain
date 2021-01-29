#include <QObject>
#include <QString>
#include <QDateTime>
#include "__nodedbs.h"



__nodedbs::__nodedbs(QObject *parent) :
    QObject(parent)
{
    node_id = -1;
    node_node_name.clear();
    node_node_type = -1;
    node_node_id = -1;
    node_ip.clear();
    node_port = -1;
    
}

qlonglong __nodedbs::Getnode_id()
{
    return node_id;
}

QString __nodedbs::Getnode_node_name()
{
    return node_node_name;
}

int __nodedbs::Getnode_node_type()
{
    return node_node_type;
}

int __nodedbs::Getnode_node_id()
{
    return node_node_id;
}

QString __nodedbs::Getnode_ip()
{
    return node_ip;
}

int __nodedbs::Getnode_port()
{
    return node_port;
}

int __nodedbs::Getnode_service_port()
{
    return service_port;
}




void __nodedbs::Setnode_id(int value)
{
    node_id = value;
}

void __nodedbs::Setnode_node_name(QString value)
{
    node_node_name = value;
}

void __nodedbs::Setnode_node_type(int value)
{
    node_node_type = value;
}

void __nodedbs::Setnode_node_id(int value)
{
    node_node_id = value;
}

void __nodedbs::Setnode_ip(QString value)
{
    node_ip = value;
}

void __nodedbs::Setnode_port(int value)
{
    node_port = value;
}

void __nodedbs::Setnode_service_port(int value)
{
    service_port = value;
}


