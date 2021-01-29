#ifndef __BLOCKCHAIN_H
#define __BLOCKCHAIN_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QDateTime>
#include <QCryptographicHash>
#include <QJsonObject>
#include "database/provider/__blockprovider.h"
#include <database/structure/__blockdbs.h>
#include "__staticvalue.h"
#include <QMutex>


class __blockchain : public QObject
{
    Q_OBJECT
public:
    explicit __blockchain(QObject *parent = nullptr);

public slots:
    void createNewTransaction(ISO_STRUCTURE _transaction);

private slots:
    void slot_timeout();

signals:
    void signal_showBlock2User(int index , QByteArray data);


private:
    QVector<QByteArray> hashChain; //زنجیره بلک ها
    QVector<ISO_STRUCTURE> currentTransaction; // لیست تراکنش ها
    QMutex transactionMutex;
    QTimer *timer;

    qlonglong blockIndex; //شماره بلاک جاری
    qlonglong createTime; //زمان ساخته شدن بلاک
    qlonglong proof;
    QByteArray previousHash; //هش بلاک قبلی
    QByteArray blockString;

    void createNewBlock(QVector<ISO_STRUCTURE> &transactionList);
    void generateBlockString(QVector<ISO_STRUCTURE> &transactionList);
    void json2Byte(QJsonObject json , bool save=false);
    void save2File(QString name, QByteArray data);
    void saveBlock2Database();
    void proofOfWork(int lastProof);

    void getLastIndexAndPOW();
};

#endif // __BLOCKCHAIN_H
