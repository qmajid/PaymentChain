

//------------------------------------------------------ Include files

// Qt

// Default
#include "__nodeprovider.h"

// User

//------------------------------------------------------ EOB

__nodeprovider::__nodeprovider()
{
}

__nodedbs* __nodeprovider::ConvertRow(QVector<QVariant> *data)
{
    __nodedbs* rt;
    rt = new __nodedbs(this);
    rt->Setnode_id(data->value(0).toInt());
    rt->Setnode_node_name(data->value(1).toString());
    rt->Setnode_node_type(data->value(2).toInt());
    rt->Setnode_node_id(data->value(3).toInt());
    rt->Setnode_ip(data->value(4).toString());
    rt->Setnode_port(data->value(5).toInt());
    rt->Setnode_service_port(data->value(6).toInt());

    return rt;
}



QVector<__nodedbs*> __nodeprovider::ConvertTable(QVector<QVector<QVariant> > *data)
{
    QVector<__nodedbs*> rt;
    for (int a=0 ; a <= data->count()-1 ; a++)
    {
        __nodedbs* nowData;
        QVector<QVariant> row = data->value(a);
        nowData = ConvertRow(&row);
        rt.push_back(nowData);
    }
    return rt;
}


QVector<__nodedbs *> __nodeprovider::GetNodeList()
{
    QVariantList parameter;
    QString Query = "select * from node";
    QVector<QVector<QVariant> > data = _DataBaseHandler.runQuery(Query, parameter);
    return ConvertTable(&data);
}
