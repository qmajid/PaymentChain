#ifndef __STATICVALUE_H
#define __STATICVALUE_H

#include <QObject>
#include "database/structure/__nodedbs.h"


const int WEB_SOCKET_SERVER_LISTEN_PORT = 1234;
#define TRANSACTION_COUNT_IN_BLOCK 5
#define TRANSACTION_CREATE_BLOCK_INTERVAL 10 //sec


typedef enum
{
    REQUEST_TRANSACTION = 1,
    REQUEST_REPORT,
}REQUEST_TYPE;


typedef struct {
    int db_port;
    QString db_username;
    QString db_password;
    QString db_driver;
    QString db_name;
    QString db_host;
    QString name;
    int node_type;
    int node_id;
}CONFIG_STRUCTURE;

typedef struct
{
    qlonglong receive_time;
    qlonglong response_time;
    int node_type;
    int node_id;
    QString card_number;
    QString terminal_number;
    QString merchant_number;
    int amount;
    QString source;
    QString destination;
    bool is_new_transaction = true;
    QString trace_number;
    REQUEST_TYPE request;
    bool is_approved = false;
}ISO_STRUCTURE;
Q_DECLARE_METATYPE(ISO_STRUCTURE)


typedef enum
{
    NODE_PSP = 1,
    NODE_SHAPARAK,
    NODE_SHETAB,
    NODE_BANK_SWITCH,
    NODE_POS
}NODE_TYPE;




class __staticvalue : public QObject
{
    Q_OBJECT
public:
    explicit __staticvalue(QObject *parent = nullptr);

    static bool readConfigFile();
    static CONFIG_STRUCTURE* getConfig();

    static void readNodesInfo();
    static QVector<__nodedbs *>* getNodesInfo();
    static __nodedbs* getCurrentNodeInfo();
    static __nodedbs* getNodeINfo(int node_type);

    static QString generateTraceNumber();
    static qlonglong getTransactionTime(QString traceNumber);
    static QByteArray hashBlock(QByteArray &block);
signals:

public slots:

private:

    static CONFIG_STRUCTURE config;
    static QVector<__nodedbs *> node;
    static __nodedbs* currentNode;
};

#endif // __STATICVALUE_H
