#ifndef __NODEPROVIDER_H
#define __NODEPROVIDER_H

#include "database/handler/__dbhandler.h"
#include "database/structure/__nodedbs.h"
#include<QSqlDatabase>
#include<QSqlQuery>



class __nodeprovider:public QObject
{
    Q_OBJECT


public:		// Properties


public:		// Methods

    __nodeprovider();

    QVector<__nodedbs*>  ConvertTable(QVector<QVector<QVariant> > * data);
    __nodedbs* ConvertRow(QVector<QVariant>* data);

    QVector<__nodedbs*> GetNodeList();

private:
    __dbhandler _DataBaseHandler;

};

#endif // __NODEPROVIDER_H
