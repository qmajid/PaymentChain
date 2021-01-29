#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QStringList>


const int NODES_COUNT = 10;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    system("killall -9 BlockchainServer;");
    ui->setupUi(this);
    this->setWindowTitle("نرم افزار ثبت تراکنش های بانکی بر بستر بلاک چین و پیگیری مغایرت های بانکی");
    ui->btn_connect->setStyleSheet("background-color: rgb(164, 0, 0);");
    ui->btn_connect->setText("Connect");

    webSocketTransaction = new QWebSocket();
    connect(webSocketTransaction, SIGNAL(connected()) , this, SLOT(onConnected()));
    connect(webSocketTransaction, SIGNAL(disconnected()) , this, SLOT(closed()));
    connect(webSocketTransaction , SIGNAL(textFrameReceived(QString,bool)) , this , SLOT(slot_textFrameReceived(QString,bool)));

    loadTraceInfo();
    setStyle();

    createNodesView();
}

MainWindow::~MainWindow()
{
    system("killall -9 BlockchainServer;");
    delete ui;
}

void MainWindow::on_btn_send_clicked()
{
    webSocketTransaction->sendTextMessage(createMessage(REQUEST_TRANSACTION, ui->lineEdit_from->text().trimmed(), ui->lineEdit_to->text().trimmed(),
                                             ui->lineEdit_amount->text().trimmed().toDouble(), "-1"));
}


void MainWindow::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(webSocketTransaction, SIGNAL(textMessageReceived(QString)),
            this, SLOT(onTextMessageReceived(QString)));

    ui->btn_connect->setText("Disconnect");
    ui->btn_connect->setStyleSheet("background-color: rgb(78, 154, 6);");
    ui->btn_send->setEnabled(true);
}

void MainWindow::closed()
{
    webSocketTransaction->close();
    ui->btn_connect->setStyleSheet("background-color: rgb(164, 0, 0);");
    ui->btn_connect->setText("Connect");
}

void MainWindow::onTextMessageReceived(QString msg)
{
    qDebug()<<"onTextMessageReceived "<<msg;
}


void MainWindow::on_btn_connect_clicked()
{
    QString url = "ws://"+ui->lineEdit_ip->text().trimmed()+":"+ui->lineEdit_port->text().trimmed();
    qDebug()<<"url"<<url;
    if(webSocketTransaction->state() == QAbstractSocket::UnconnectedState)
    {
        webSocketTransaction->open(QUrl(url));
    }
    else
    {
        webSocketTransaction->close();
        ui->btn_connect->setStyleSheet("background-color: rgb(164, 0, 0);");
        ui->btn_connect->setText("Connect");
    }
}

void MainWindow::createNodesView()
{
    qDebug()<<"Enter createNodesView";

    QGridLayout *gLayout = new QGridLayout();
    gLayout->setSpacing(0);
    gLayout->setMargin(0);
    gLayout->setContentsMargins(0,0,0,0);


    //رنگ زرد دور فریم نودها
    ui->frame_nodes->setObjectName("frame_nodes");
    QString style="#frame_nodes { border: 1px solid rgb(255, 255, 0); }";
    ui->frame_nodes->setStyleSheet(style);


    int columnCount = 5;
    int row = 0;
    int column = 0;

    QVector<QString> exePath;
    exePath.append("../nodes/psp1;     ./BlockchainServer");
    exePath.append("../nodes/psp2;     ./BlockchainServer");
    exePath.append("../nodes/psp3;     ./BlockchainServer");
    exePath.append("../nodes/psp4;     ./BlockchainServer");
    exePath.append("../nodes/shaparak; ./BlockchainServer");
    exePath.append("../nodes/shetab;   ./BlockchainServer");
    exePath.append("../nodes/b1;       ./BlockchainServer");
    exePath.append("../nodes/b2;       ./BlockchainServer");
    exePath.append("../nodes/b3;       ./BlockchainServer");
    exePath.append("../nodes/b4;       ./BlockchainServer");

    DialogNode* node  = NULL;
    QProcess *process = NULL;
    QStringList list;
    QStringList list2;
    QString nodeName = "";


    for(int i=0;i<NODES_COUNT;i++)
    {
        node = new DialogNode();
        node->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        if(i>0 && i%columnCount==0)
        {
            row++;
            column = 0;
        }
        gLayout->addWidget(node, row, column);
        column++;

        process = new QProcess();
        processHash.insert(process, node);
        node->setProcess( process);
        connect(process, SIGNAL(readyReadStandardOutput()), node, SLOT(readyReadStandardOutput()));
        connect(process, SIGNAL(readyReadStandardError()), node, SLOT(readyReadStandardError()));

        list = exePath[i].split(";",QString::SkipEmptyParts);
        process->setWorkingDirectory(list[0]);
        process->start(list[1]);

        list2 = QString(list.at(0)).split("/", QString::SkipEmptyParts);
        nodeName = list2.at(list2.count()-1);
        node->setNodeName(nodeName);
        qDebug()<<"Enter createNodesView "<<list[0]<<list[1];

    }
    ui->frame_nodes->setLayout(gLayout);
}

void MainWindow::readyReadOutput()
{
    QProcess* p = static_cast<QProcess*> (sender());
    QString output = QString(p->readAllStandardOutput().trimmed());
    processHash.value(p)->showOutput(output);
}

void MainWindow::slot_textFrameReceived(QString data, bool islast)
{
    QWebSocket* webSocket = static_cast<QWebSocket*> (sender());

    QByteArray buffer = data.toLocal8Bit();
    ISO_STRUCTURE isoStruct;
    parseMessage(buffer, isoStruct);

    ui->lineEdit_inputtracenumber->setText(isoStruct.trace_number.trimmed());
}

void MainWindow::parseMessage(QByteArray &input, ISO_STRUCTURE &output)
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
}

void MainWindow::parseMessageReport(QByteArray &input, ISO_STRUCTURE &output)
{
    //qDebug()<<"Enter parseMessageReport ";//<<input;
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

    output.trace_number  =  mainMap.value("trace_number").toString();
    output.is_approved   =  mainMap.value("is_approved").toBool();
    output.amount        =  mainMap.value("amount").toInt();
    output.card_number   =  mainMap.value("card_number").toString();
    output.receive_time  =  mainMap.value("datetime").toLongLong();
}


QByteArray MainWindow::createMessage(REQUEST_TYPE request, QString from, QString to, double amount, QString traceNumber)
{
    QJsonObject json;

    json.insert("trace_number", traceNumber);
    json.insert("request_type", request);
    if(request == REQUEST_TRANSACTION)
    {
        json.insert("source" , from);
        json.insert("destination" , to);
        json.insert("amount" , amount);
        json.insert("receive_time", QDateTime::currentMSecsSinceEpoch());
        json.insert("node_type", NODE_POS);
        json.insert("node_id", 123456);
        json.insert("card_number", "1234567890123456");
        json.insert("terminal_number", 1234);
        json.insert("merchant_number", 56);
        json.insert("new_transaction", true);
    }
    else if(request == REQUEST_REPORT)
    {
        json.insert("is_approved", false);
    }


    QJsonDocument doc;
    doc.setObject(json);
    return doc.toJson(QJsonDocument::Compact);
}


void MainWindow::setStyle()
{
    QString style;

    /////////////////////////////////////////////
    /////////////// TRACE ///////////////////////
    /////////////////////////////////////////////
    style = styleTraceLable.arg(traceLableWidth/2).arg("rgb(155, 154, 154);");
    ui->label_psp1->setFixedSize(traceLableWidth, traceLableWidth);
    ui->label_psp2->setFixedSize(traceLableWidth, traceLableWidth);
    ui->label_psp3->setFixedSize(traceLableWidth, traceLableWidth);
    ui->label_psp4->setFixedSize(traceLableWidth, traceLableWidth);
    ui->label_shb->setFixedSize(traceLableWidth,  traceLableWidth);
    ui->label_shp->setFixedSize(traceLableWidth,  traceLableWidth);
    ui->label_b1->setFixedSize(traceLableWidth,   traceLableWidth);
    ui->label_b2->setFixedSize(traceLableWidth,   traceLableWidth);
    ui->label_b3->setFixedSize(traceLableWidth,   traceLableWidth);
    ui->label_b4->setFixedSize(traceLableWidth,   traceLableWidth);

    ui->label_psp1->setStyleSheet(style);
    ui->label_psp2->setStyleSheet(style);
    ui->label_psp3->setStyleSheet(style);
    ui->label_psp4->setStyleSheet(style);
    ui->label_shb->setStyleSheet(style);
    ui->label_shp->setStyleSheet(style);
    ui->label_b1->setStyleSheet(style);
    ui->label_b2->setStyleSheet(style);
    ui->label_b3->setStyleSheet(style);
    ui->label_b4->setStyleSheet(style);
    qDebug()<<"setStyle "<<ui->label_psp1->width()<<ui->label_psp1->height();
}


//////////////////////////////////////////////////
/////////////////////// TRACE ////////////////////
//////////////////////////////////////////////////

void MainWindow::loadTraceInfo()
{
    traceVector.clear();
    TRACE_STRUCTURE structure;
    QString url;

    structure.url = "ws://127.0.0.1:6234";    structure.lable = ui->label_psp1;   traceVector.append(structure);
    structure.url = "ws://127.0.0.1:6235";    structure.lable = ui->label_psp2;   traceVector.append(structure);
    structure.url = "ws://127.0.0.1:6236";    structure.lable = ui->label_psp3;   traceVector.append(structure);
    structure.url = "ws://127.0.0.1:6237";    structure.lable = ui->label_psp4;   traceVector.append(structure);
    structure.url = "ws://127.0.0.1:6238";    structure.lable = ui->label_shp;    traceVector.append(structure);
    structure.url = "ws://127.0.0.1:6239";    structure.lable = ui->label_shb;    traceVector.append(structure);
    structure.url = "ws://127.0.0.1:6300";    structure.lable = ui->label_b1;     traceVector.append(structure);
    structure.url = "ws://127.0.0.1:6301";    structure.lable = ui->label_b2;     traceVector.append(structure);
    structure.url = "ws://127.0.0.1:6302";    structure.lable = ui->label_b3;     traceVector.append(structure);
    structure.url = "ws://127.0.0.1:6303";    structure.lable = ui->label_b4;     traceVector.append(structure);
}


void MainWindow::on_btn_trace_clicked()
{
    approvCount = 0;

    QString style = styleTraceLable.arg(traceLableWidth/2).arg("red;");
    for(int i=0; i<traceVector.count(); i++)
    {
        traceVector[i].lable->setStyleSheet(style);
    }

    QString traceNUmber = ui->lineEdit_tracenumber->text().trimmed();
    if(traceNUmber.isEmpty())
        return;



    QWebSocket* reportSocket = NULL;

    for(int i=0; i<traceVector.count(); i++)
    {
        reportSocket = new QWebSocket();
        connect(reportSocket, SIGNAL(connected()) , this, SLOT(onConnectedReportServer()));
        connect(reportSocket, SIGNAL(disconnected()) , this, SLOT(closedReportServer()));
        connect(reportSocket , SIGNAL(textFrameReceived(QString,bool)) , this , SLOT(slot_textFrameReceivedReportServer(QString,bool)));

        reportSocket->open(traceVector.at(i).url);
    }
}

void MainWindow::onConnectedReportServer()
{
    QWebSocket* webSocket = static_cast<QWebSocket*> (sender());

    QString traceNUmber = ui->lineEdit_tracenumber->text().trimmed();
    QByteArray request = createMessage(REQUEST_REPORT, "", "", 0, traceNUmber);
    webSocket->sendTextMessage(request);
}

void MainWindow::closedReportServer()
{
    qDebug()<<"Enter closedReportServer";
}

void MainWindow::slot_textFrameReceivedReportServer(QString data, bool islast)
{
    qDebug()<<"Enter slot_textFrameReceivedReportServer";
    QWebSocket* webSocket = static_cast<QWebSocket*> (sender());

    QByteArray buffer = data.toLocal8Bit();
    ISO_STRUCTURE reportStruct;
    parseMessageReport(buffer, reportStruct);

    QString style = "";
    QString url = "ws://"+webSocket->peerAddress().toString().trimmed()+":"+QString::number(webSocket->peerPort());


    for(int i=0; i<traceVector.count(); i++)
    {
        if(url == traceVector[i].url)
        {
            if(reportStruct.is_approved)
            {
                counterMutex.lock();
                qDebug()<<"approvCount "<<approvCount;
                approvCount++;
                counterMutex.unlock();
                style = styleTraceLable.arg(traceLableWidth/2).arg("green;");
            }
            else
            {
                style = styleTraceLable.arg(traceLableWidth/2).arg("red;");
            }

            traceVector[i].lable->setStyleSheet(style);
            break;
        }
    }

    if(approvCount >= (traceVector.count()/2)+1)
    {
        ui->label_traceResualt->setPixmap(QPixmap(":/resource/yes.png"));
    }
    else
    {
        ui->label_traceResualt->setPixmap(QPixmap(":/resource/no.png"));
    }
}
