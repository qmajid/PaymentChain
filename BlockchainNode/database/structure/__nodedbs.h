#ifndef __DBSNODE_H
#define __DBSNODE_H

#include <QObject>
#include <QString>
#include <QDateTime>


class __nodedbs : public QObject
{
    Q_OBJECT

public:		// Properties

public:		// Methods

    explicit __nodedbs(QObject *parent = 0);

    qlonglong Getnode_id();
    QString Getnode_node_name();
    int Getnode_node_type();
    int Getnode_node_id();
    QString Getnode_ip();
    int Getnode_port();
    int Getnode_service_port();

    void Setnode_id(int value);
    void Setnode_node_name(QString value);
    void Setnode_node_type(int value);
    void Setnode_node_id(int value);
    void Setnode_ip(QString value);
    void Setnode_port(int value);
    void Setnode_service_port(int value);
public slots:	// Slots

    //------------------------------------------------------ Private

private:	// Properties

    qlonglong node_id;
    QString node_node_name;
    int node_node_type;
    int node_node_id;
    QString node_ip;
    int node_port;
    int service_port;

private:	// Methods

private slots:	// Slots

    //------------------------------------------------------ Protected

protected:	// Properties

protected:	// Methods

};

#endif // __DBSNODE_H
