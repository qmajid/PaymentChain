#include "__reportengin.h"
#include <QDebug>
#include <database/provider/__blockprovider.h>
#include <database/structure/__blockdbs.h>
#include "block/__blockchain.h"
#include <QJsonArray>
#include "network/__iso.h"

__reportengin::__reportengin(QString key, QString traceNumber)
{
    this->key   = key;
    this->traceNumber = traceNumber;
}

void __reportengin::run()
{
    startSearch();
}

void __reportengin::startSearch()
{
    qDebug()<<"Enter startSearch";

    int limit = 10;
    qlonglong lastId = 0;
    QByteArray blockInfo;
    __blockprovider provider;
    QString message = "";
    QJsonParseError jsonError;
    QVector<__blockdbs *>  blockList;
    QJsonDocument flowerJson ;
    QJsonObject jObject;
    QVariantMap mainMap;
    QVariantMap transactionMap;
    QByteArray newHash;
    QByteArray previusBlockHash = "";
    QByteArray currentHash = "";
    QString storeTraceNumber;
    QJsonArray transactionArray;
    __iso iso;
    QByteArray request;
    ISO_STRUCTURE isoStruct;
    isoStruct.is_approved = false;

    qlonglong transactionTime = __staticvalue::getTransactionTime(traceNumber);

    blockList = provider.getAll(transactionTime, limit);

    for(int i=0; i<blockList.count(); i++)
    {
        lastId = blockList[i]->Getblock_id();

        blockInfo = blockList[i]->Getblock_data().toLocal8Bit();


        flowerJson = QJsonDocument::fromJson( blockInfo ,&jsonError);

        if (jsonError.error != QJsonParseError::NoError)
        {
            message = jsonError.errorString();
            qDebug() <<"---------- Error in startSearch------------------"<< message <<jsonError.error;
            return;
        }

        jObject = flowerJson.object();
        mainMap = jObject.toVariantMap();

        currentHash = mainMap.value("hash").toByteArray().trimmed();

        //////////////////////////////////////
        //هش بلاک جدید ساخته میشود تا با هش همان بلاک در بانک اطلاعاتی مقایسه گردد تا تقلب بررسی گردد
        newHash.clear();
        mainMap.remove("hash");
        QJsonDocument doc;
        doc.setObject(QJsonObject::fromVariantMap(mainMap));
        QByteArray blockString = doc.toJson(QJsonDocument::Compact);
        newHash = __staticvalue::hashBlock(blockString);


        if(newHash != currentHash)
        {
            //بلاک دستکاری شده است
            qDebug() <<"---------- Error Hash Comparition ------------------";
            return;
        }
        if(!previusBlockHash.isEmpty() && mainMap.value("previousHash").toByteArray() != previusBlockHash)
        {
            //بلاک دستکاری شده است
            qDebug() <<"---------- Error Previous Hash Comparition ------------------";
            //return;
        }

        previusBlockHash = currentHash;

        transactionArray = mainMap.value("data").toJsonArray();
        qDebug()<<"transactionArray "<<transactionArray;
        for(int j=0; j<transactionArray.count(); j++)
        {
            transactionMap = transactionArray.at(j).toObject().toVariantMap();
            storeTraceNumber = transactionMap.value("trace_number").toString().trimmed();
            if(traceNumber == storeTraceNumber)
            {
                //تراکنش مورد نظر یافت شد
                qDebug()<<"------------------- FIND ----------------------";
                isoStruct.is_approved = true;

                request.clear();
                iso.createMessage(isoStruct, request);
                emit sendReportResponse(request, key);

                return;
            }
        }
    }

    qDebug()<<"------------------- NOT FIND ----------------------";
    request.clear();
    iso.createMessage(isoStruct, request);
    emit sendReportResponse(request, key);
}
