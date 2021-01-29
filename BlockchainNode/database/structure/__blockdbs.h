#ifndef __BLOCKDBS_H
#define __BLOCKDBS_H

#include <QObject>
#include <QString>
#include <QDateTime>


class __blockdbs : public QObject
{
    Q_OBJECT

public:		// Methods
    explicit __blockdbs(QObject *parent = 0);

    qlonglong Getblock_id();
    qlonglong Getblock_index();
    qlonglong Getblock_time();
    QString Getblock_data();

    void Setblock_id(qlonglong value);
    void Setblock_index(qlonglong value);
    void Setblock_time(qlonglong value);
    void Setblock_data(QString value);

public slots:	// Slots

    //------------------------------------------------------ Private

private:	// Properties

    qlonglong block_id;
    qlonglong block_index;
    qlonglong block_time;
    QString block_data;

};

#endif // __BLOCKDBS_H
