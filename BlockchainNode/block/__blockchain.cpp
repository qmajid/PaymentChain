#include "__blockchain.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QCryptographicHash>
#include <database/provider/__blockprovider.h>
#include <network/__iso.h>
#include <QDebug>


__blockchain::__blockchain(QObject *parent) : QObject(parent)
{
    hashChain.clear();
    currentTransaction.clear();

    blockIndex=0;//genesis
    previousHash.clear();
    proof = 0;
    getLastIndexAndPOW();

    timer = new QTimer(this);
    connect(timer , SIGNAL(timeout()) , this , SLOT(slot_timeout()));
    timer->setInterval(1000);
    timer->start();
}


void __blockchain::createNewTransaction(ISO_STRUCTURE _transaction)
{
    transactionMutex.lock();
    currentTransaction.append(_transaction);
    qDebug()<<"createNewTransaction "<<currentTransaction.count();
    transactionMutex.unlock();
}


//void __blockchain::slot_timeout()
//{
//تشکیل بلاک ها براساس تعداد تراکنش های موجود در صف
//    //qDebug()<<"slot_timeout "<<currentTransaction.count();
//    if(currentTransaction.count() < TRANSACTION_COUNT_IN_BLOCK)
//        return;

//    transactionMutex.lock();
//    if(currentTransaction.count() < TRANSACTION_COUNT_IN_BLOCK)
//    {
//        transactionMutex.unlock();
//        return;
//    }
//    QVector<transactionStruct> localList = currentTransaction.mid(0,TRANSACTION_COUNT_IN_BLOCK);
//    currentTransaction.remove(0,TRANSACTION_COUNT_IN_BLOCK);
//    transactionMutex.unlock();


//    //هر ۱۰ تراکنش یک بلاک را تشکیل میدهند
//    createNewBlock(localList);
//    localList.clear();
//    blockIndex++;
//}


void __blockchain::slot_timeout()
{
    //تشکیل بلاک ها براساس زمان
    static int blockInterval = 0;
    blockInterval++;
    //qDebug()<<"time:"<<blockInterval <<" tr_count:"<< currentTransaction.count();

    if(blockInterval < TRANSACTION_CREATE_BLOCK_INTERVAL)
        return;
    blockInterval = 0;

    transactionMutex.lock();
    if(currentTransaction.count() == 0)
    {
        transactionMutex.unlock();
        return;
    }
    QVector<ISO_STRUCTURE> localList = currentTransaction;
    currentTransaction.clear();
    transactionMutex.unlock();


    createNewBlock(localList);
    localList.clear();
    blockIndex++;
}



void __blockchain::createNewBlock(QVector<ISO_STRUCTURE> &transactionList)
{
    //ایجاد بلاک جدید و اضافه کردن آن به زنجیره
    qDebug()<<"Enter createNewBlock";

    proofOfWork(proof);
    generateBlockString(transactionList);
    saveBlock2Database();
    emit signal_showBlock2User(blockIndex , blockString);

}



//void __blockchain::hashBlock(QByteArray &outputHash)
//{
//    // هش کردن یک بلاک
//    outputHash = QCryptographicHash::hash(blockString , QCryptographicHash::Sha256).toHex();
//}



void __blockchain::generateBlockString(QVector<ISO_STRUCTURE> &transactionList)
{
    qDebug()<<"Enter generateBlockString ";
    QJsonObject json;
    QString jsonValue;
    QJsonObject jsonTransaction;

    json.insert("index" , QJsonValue(blockIndex));
    json.insert("timestamp" , QJsonValue(QDateTime::currentDateTime().toString("yyyy-MM-dd    hh:mm:ss")));
    json.insert("proof" , QJsonValue(proof));
    json.insert("count" , QJsonValue(transactionList.count()));

    jsonValue = previousHash;
    json.insert("previousHash" , QJsonValue(jsonValue));

    QJsonArray transactionArray;
    for(int i=0;i<transactionList.count();i++)
    {
        jsonTransaction.insert("sender"       , QJsonValue(transactionList[i].source));
        jsonTransaction.insert("receiver"     , QJsonValue(transactionList[i].destination));
        jsonTransaction.insert("amount"       , QJsonValue(transactionList[i].amount));
        jsonTransaction.insert("node_type"    , QJsonValue(transactionList[i].node_type));
        jsonTransaction.insert("node_id"      , QJsonValue(transactionList[i].node_id));
        jsonTransaction.insert("trace_number" , QJsonValue(transactionList[i].trace_number));

        transactionArray.append(jsonTransaction);

    }
    json.insert("data" , QJsonValue(transactionArray));

    json2Byte(json); //generate block string

    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
    QByteArray currentBloackHash;
    currentBloackHash = __staticvalue::hashBlock(blockString); // create hash from : index & timestamp & data & prevoiusHash
    jsonValue = currentBloackHash;
    json.insert("hash" , QJsonValue(jsonValue)); //current block hash
    json2Byte(json , false);

    previousHash = currentBloackHash;

}


void __blockchain::json2Byte(QJsonObject json, bool save)
{
    QJsonDocument doc;
    doc.setObject(json);
    blockString = doc.toJson(QJsonDocument::Compact);

    if(save)
    {
        save2File("json/block_"+QTime::currentTime().toString("hh_mm_ss_zzz")+".json" , blockString);
    }
}


void __blockchain::save2File(QString name, QByteArray data)
{
    QFile file(name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << data;
    file.close();

}


void __blockchain::saveBlock2Database()
{
    __blockdbs block;
    block.Setblock_id(-1);
    //block.Setblock_data(blockString.trimmed().toHex());
    block.Setblock_data(blockString.trimmed());//TODO : uncomment abow line
    block.Setblock_index(blockIndex);
    block.Setblock_time(QDateTime::currentMSecsSinceEpoch());

    //MULTI CONNECTION
    __blockprovider provider;
    provider.Insert(&block);
}


void __blockchain::proofOfWork(int lastProof)
{
    QElapsedTimer eTimer;
    QByteArray newHash ;
    int number = 0;
    QString newString = "";
    eTimer.restart();
    while(!newHash.startsWith("00"))
    {
        newString = QString::number(lastProof)+QString::number(number);
        newHash = QCryptographicHash::hash(newString.toLocal8Bit() , QCryptographicHash::Sha256).toHex();
        number++;
        //qDebug()<<"POW:"<<newHash;
    }
    qDebug()<<"proofOfWork:"<<number <<"  eTimer:"<<(double)eTimer.elapsed()/1000<<" sec";
    proof = number;
}

void __blockchain::getLastIndexAndPOW()
{
    //استفاده از اطلاعات آخرین بلاک ذخیره شده برای بلاک جاری
    //تا در زمان باز و اجرای مجدد نرم افزار پیوستگی اطلاعات حفظ شود
    proof = 0;   //genesis
    blockIndex=0;//genesis

    __blockprovider provider;
    QByteArray blockInfo = provider.getLastBlockInfo();

    QString message = "";
    QJsonParseError jsonError;
    QJsonDocument flowerJson = QJsonDocument::fromJson( blockInfo ,&jsonError);

    if (jsonError.error != QJsonParseError::NoError)
    {
        message = jsonError.errorString();
        qDebug() <<"---------- Error------------------"<< message <<jsonError.error;
        return;
    }

    QJsonObject jObject = flowerJson.object();
    QVariantMap mainMap = jObject.toVariantMap();

    blockIndex   = mainMap.value("index").toLongLong()+1;
    proof        = mainMap.value("proof").toLongLong();
    previousHash = mainMap.value("previousHash").toByteArray();

    qDebug()<<"getLastIndexAndPOW blockIndex:"<<blockIndex<<" proof:"<<proof<<" previousHash:"<<previousHash;
}
