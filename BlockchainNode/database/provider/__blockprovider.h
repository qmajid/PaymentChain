#ifndef __BLOCKPROVIDER_H
#define __BLOCKPROVIDER_H

#include "database/handler/__dbhandler.h"
#include "database/structure/__blockdbs.h"
#include<QSqlDatabase>
#include<QSqlQuery>


class __blockprovider:public QObject
{
    Q_OBJECT

public:		// Methods

    __blockprovider();

    QVector<__blockdbs*>  ConvertTable(QVector<QVector<QVariant> > * data);
    __blockdbs* ConvertRow(QVector<QVariant>* data);

    QVariant Insert(__blockdbs *data);
    QVariant executeQuery(QString SQL, QVariantList parameter);
    QVector<QVector<QVariant> >  runQuery(QString SQL, QVariantList parameter);

    QByteArray getLastBlockInfo();
    QVector<__blockdbs*> getAll(qlonglong time, int limit);


private:	// Properties
    __dbhandler _DataBaseHandler;
};

#endif // __BLOCKPROVIDER_H
