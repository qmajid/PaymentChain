#include "__dbhandler.h"
#include <QtDebug>
#include "__staticvalue.h"

QMutex __dbhandler::dbmutex;
int __dbhandler::COUNTER = 0;
int __dbhandler::maxConnection = 1;
QHash<int,connectionStructure> __dbhandler::connectionHash;
QMutex __dbhandler::COUNTERMUTEX;
\

__dbhandler::__dbhandler(QObject *parent) : QObject(parent)
{

}

void __dbhandler::setMaxConnection(int value)
{
    maxConnection = value;
}

bool __dbhandler::CreateConnection()
{
    QMutex* MU;
    QSqlDatabase voip;
    connectionStructure connectionStr;
    int index = connectionHash.count();
    //MULTI CONNECTION
    for (int var = 0; var < maxConnection ; var++)
    {
        qDebug()<<"QSqlDatabase::drivers => "<<QSqlDatabase::drivers();
        voip = QSqlDatabase::addDatabase(__staticvalue::getConfig()->db_driver,"voip"+QString::number (index));
        voip.setHostName(__staticvalue::getConfig()->db_host);                      // host
        voip.setDatabaseName(__staticvalue::getConfig()->db_name);          // database
        voip.setUserName(__staticvalue::getConfig()->db_username);                  // user
        voip.setPassword(__staticvalue::getConfig()->db_password);                  // password
        voip.setPort(__staticvalue::getConfig()->db_port);                      // port

        bool  b = voip.open();
        if (b)
        {
            qDebug() << "Connect to Data Base  SuccessFully";
        }
        else
        {
            qDebug() << "can't Connect to Data Base With Error=> "+voip.lastError ().databaseText();
            return false;
        }

        MU = new QMutex;
        connectionStr.database = voip;
        connectionStr.mutex = MU;
        connectionHash.insert (index,connectionStr);
        qDebug()<<"CreateConnection "<<index;
        index++;
    }
    return true;
}



QVariant __dbhandler::executeQuery(QString SqlQuery,QVariantList parameter)
{
    COUNTERMUTEX.lock ();
    int index = COUNTER++;
    index = index % maxConnection;
    COUNTERMUTEX.unlock ();

    connectionHash[index].mutex->lock ();
    error = "Success";

    QVariant rt;
    rt = false;
    int cnt = 1;

    if (!connectionHash[index].database.isOpen ())
        connectionHash[index].database.open();

    if (connectionHash[index].database.isOpen ())
    {
        QSqlQuery* query = new QSqlQuery(connectionHash[index].database);

        if(parameter.count()>0)
        {
            query->prepare(SqlQuery);
            if (parameter.at(parameter.count()-1).toInt() == -1) cnt = 2;


            for (int a= 0; a <= parameter.count()-cnt ; a++)
            {
                QVariant V;
                V = parameter.value(a);
                if (V.type()==QMetaType::QString)
                {
                    if (V=="''" || V=="")
                    {
                        V.clear();
                    }
                }
                query->bindValue(a,V);
            }
        }

        if ( !query->exec() )
        {
            qDebug()<<"Can't Exec SQL = "<<query->lastQuery ()<<"With Err = " <<query->lastError().text();

            error = query->lastError().text();
            delete query;

            connectionHash[index].mutex->unlock ();


            if (cnt == 1)/*Update OR Delete*/
                return rt ; else return -1; /*Insert*/

        }
        else
        {
            if (cnt == 1)/*Update OR Delete*/
            {
                rt = true;
            }
            else /*Insert*/
            {
                while (query->next()) {
                    rt =  query->value (0);
                }
            }
        }

        delete query;
    }
    else
    {
        qDebug()<<"Can't open SQL "<< connectionHash[index].database.lastError().text();
    }



    connectionHash[index].mutex->unlock ();


    return rt;

}


QVector<QVector<QVariant> >  __dbhandler::runQuery(QString SqlQuery,QVariantList parameter)
{
    COUNTERMUTEX.lock ();
    int index = COUNTER++;
    index = index % maxConnection;
    COUNTERMUTEX.unlock ();

    connectionHash[index].mutex->lock ();
    error = "Success";

    QVector<QVector<QVariant> > rt;
    int Counter=0;

    if (!connectionHash[index].database.isOpen ())
        connectionHash[index].database.open();

    if (connectionHash[index].database.isOpen ())
    {
        QSqlQuery* query = new QSqlQuery(connectionHash[index].database);
        query->prepare(SqlQuery);

        if(parameter.count()>0)
        {
            for (int a= 0; a <= parameter.count()-1 ; a++)
            {
                query->bindValue(a,parameter.value(a));
            }
        }

        if ( !query->exec() )
        {
            qDebug()<<"Can't Exec SQL = "<<query->lastQuery ()<<"With Err = " << query->lastError().text ();
            error = query->lastError().text();
            //////////////////////////////////////////////////
            //////////////////////////////////////////////////
            /////////////        Return        ///////////////
            //////////////////////////////////////////////////
            //////////////////////////////////////////////////


            connectionHash[index].mutex->unlock ();
            delete query;

            return rt ;
        }
        else
        {
            while (query->next())
            {
                int co = query->record().count();

                QVector<QVariant> data;
                for (int a=0 ;a <= co-1 ; a++)
                {
                    data.push_back(query->value(a));
                }
                rt.push_back(data);
                Counter++;
            }

        }

        delete query;
    }
    else
    {
        qDebug()<<"Can't open SQL "<< connectionHash[index].database.lastError().text();

    }

    connectionHash[index].mutex->unlock ();
    return rt;
}
