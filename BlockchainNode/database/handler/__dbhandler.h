#ifndef __DBHANDLER_H
#define __DBHANDLER_H

#include <QObject>
#include <QtSql/QtSql>
#include <QString>

typedef struct{QSqlDatabase database;QMutex* mutex;} connectionStructure;

class __dbhandler : public QObject
{
    Q_OBJECT

public:
    explicit __dbhandler(QObject *parent = nullptr);
    static int COUNTER;
    static int maxConnection;
    static QMutex dbmutex;
    static QMutex COUNTERMUTEX;
    static QHash<int,connectionStructure> connectionHash;

    static bool CreateConnection();
    static void setMaxConnection(int value);

private:
    QString error;

public :
    QVariant executeQuery(QString SqlQuery, QVariantList parameter);
    QVector<QVector<QVariant> > runQuery(QString SqlQuery,QVariantList parameter );
};

#endif // __DBHANDLER_H
