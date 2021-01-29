#include <QObject>
#include <QString>
#include <QDateTime>
#include "__blockdbs.h"


__blockdbs::__blockdbs(QObject *parent) :
    QObject(parent)
{
    block_id = -1;
    block_index = 0;
    block_time = 0;
    block_data.clear();
}

qlonglong __blockdbs::Getblock_id()
{
    return block_id;
}

qlonglong __blockdbs::Getblock_index()
{
    return block_index;
}

qlonglong __blockdbs::Getblock_time()
{
    return block_time;
}

QString __blockdbs::Getblock_data()
{
    return block_data;
}





void __blockdbs::Setblock_id(qlonglong value)
{
    block_id = value;
}

void __blockdbs::Setblock_index(qlonglong value)
{
    block_index = value;
}

void __blockdbs::Setblock_time(qlonglong value)
{
    block_time = value;
}

void __blockdbs::Setblock_data(QString value)
{
    block_data = value;
}

