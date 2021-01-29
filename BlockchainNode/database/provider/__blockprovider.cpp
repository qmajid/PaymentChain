#include "__blockprovider.h"


__blockprovider::__blockprovider()
{
}

QVariant __blockprovider::Insert(__blockdbs *data)
{
    QVariantList vl;
    vl << data->Getblock_data() << data->Getblock_time() << data->Getblock_index();

    QString command;
    command = "Insert Into block(block_data,block_time,block_index)";
    command += " Values(?,?,?) returning block_id ";
    return _DataBaseHandler.executeQuery(command, vl).toLongLong();
}


__blockdbs* __blockprovider::ConvertRow(QVector<QVariant> *data)
{
    __blockdbs* rt;
    rt = new __blockdbs(this);
    rt->Setblock_id(data->value(0).toLongLong());
    rt->Setblock_index(data->value(1).toLongLong());
    rt->Setblock_time(data->value(2).toLongLong());
    rt->Setblock_data(data->value(3).toString());
    return rt;
}

QVector<__blockdbs*> __blockprovider::ConvertTable(QVector<QVector<QVariant> > *data)
{
    QVector<__blockdbs*> rt;
    for (int a=0 ; a <= data->count()-1 ; a++)
    {
        __blockdbs* nowData;
        QVector<QVariant> row = data->value(a);
        nowData = ConvertRow(&row);
        rt.push_back(nowData);
    }
    return rt;
}


QVariant __blockprovider::executeQuery(QString SQL, QVariantList parameter)
{
    return _DataBaseHandler.executeQuery(SQL,parameter);
}


QVector<QVector<QVariant> >  __blockprovider::runQuery(QString SQL, QVariantList parameter)
{
    return _DataBaseHandler.runQuery (SQL,parameter);
}

QByteArray __blockprovider::getLastBlockInfo()
{
    QString query = "select block_data from block order by block_time desc limit 1";
    QVector<QVector<QVariant> > list = _DataBaseHandler.runQuery(query, QVariantList());
    if(list.count()==0)
        return "";

    return list[0][0].toString().toLocal8Bit();
}

QVector<__blockdbs *> __blockprovider::getAll(qlonglong time, int limit)
{
    QString query = "select * from block where block_time > ? limit ?";
    QVector<QVector<QVariant> > list = _DataBaseHandler.runQuery(query, QVariantList()<<time<<limit);
    return ConvertTable(&list);
}


