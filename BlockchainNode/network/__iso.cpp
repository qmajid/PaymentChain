#include "__iso.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariantMap>
#include <QDebug>

__iso::__iso(QObject *parent) : QObject(parent)
{

}

void __iso::createMessage(ISO_STRUCTURE &input, QByteArray &output)
{
    QJsonObject json;

    json.insert("receive_time"      , QJsonValue(input.receive_time));
    json.insert("response_time"     , QJsonValue(input.response_time));
    json.insert("node_type"         , QJsonValue(input.node_type));
    json.insert("node_id"           , QJsonValue(input.node_id));
    json.insert("card_number"       , QJsonValue(input.card_number));
    json.insert("terminal_number"   , QJsonValue(input.terminal_number));
    json.insert("merchant_number"   , QJsonValue(input.merchant_number));
    json.insert("amount"            , QJsonValue(input.amount));
    json.insert("source"            , QJsonValue(input.source));
    json.insert("destination"       , QJsonValue(input.destination));
    json.insert("new_transaction"   , QJsonValue(input.is_new_transaction));
    json.insert("trace_number"      , QJsonValue(input.trace_number));
    json.insert("request_type"      , QJsonValue(input.request));
    json.insert("is_approved"       , QJsonValue(input.is_approved));

    QJsonDocument doc;
    doc.setObject(json);
    output = doc.toJson(QJsonDocument::Compact);
}

void __iso::parseMessage(QByteArray &input, ISO_STRUCTURE &output)
{
    //qDebug()<<"Enter parseMessage ";//<<input;
    QString message = "";
    QJsonParseError jsonError;
    QJsonDocument flowerJson = QJsonDocument::fromJson(input,&jsonError);

    if (jsonError.error != QJsonParseError::NoError)
    {
        message = jsonError.errorString();
        qDebug() <<"---------- Error------------------"<< message <<jsonError.error;
        return;
    }

    QJsonObject jObject = flowerJson.object();
    QVariantMap mainMap = jObject.toVariantMap();

    output.receive_time     =  mainMap.value("receive_time").toLongLong();
    output.response_time    =  QDateTime::currentMSecsSinceEpoch();
    output.node_type        =  mainMap.value("node_type").toInt();
    output.node_id          =  mainMap.value("node_id").toInt();
    output.card_number      =  mainMap.value("card_number").toString();
    output.terminal_number  =  mainMap.value("terminal_number").toString();
    output.merchant_number  =  mainMap.value("merchant_number").toString();
    output.amount           =  mainMap.value("amount").toInt();
    output.source           =  mainMap.value("source").toString();
    output.destination      =  mainMap.value("destination").toString();
    output.is_new_transaction =  mainMap.value("new_transaction").toBool();
    output.trace_number     =  mainMap.value("trace_number").toString();
    output.request          =  (REQUEST_TYPE)mainMap.value("request_type").toInt();
}
