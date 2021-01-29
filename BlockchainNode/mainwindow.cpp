#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database/handler/__dbhandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Blockchain Server");

    init();

    qDebug()<<"getConfig()->nodeNumber: "<<__staticvalue::getConfig()->node_type;
    qDebug()<<"__staticvalue::getNodesInfo() "<<__staticvalue::getNodesInfo()->count()
           <<__staticvalue::getCurrentNodeInfo()->Getnode_node_type()
           <<__staticvalue::getCurrentNodeInfo()->Getnode_node_id()
           <<__staticvalue::getCurrentNodeInfo()->Getnode_node_name()
           <<__staticvalue::getCurrentNodeInfo()->Getnode_port();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::init()
{
    //اتصال به بانک اطلاعاتی
    //MULTI CONNECTION
    bool ok = __dbhandler::CreateConnection();
    qDebug()<<"connect "<<ok;
    if(!ok)
        qFatal("Can not connect to databse");

    //خواندن اطلاعات نودهایی که باید با آنها ارتباط داشته باشد
    __staticvalue::readNodesInfo();

    blockChain = new __blockchain(this);
    connect(blockChain , SIGNAL(signal_showBlock2User(int,QByteArray)) , this , SLOT(slot_showBlock2User(int,QByteArray)));


    //باز کردن سوکت ارتباطی با سایر گره ها
    websocketTransaction = new __websocketserver("Block chain server." , QWebSocketServer::NonSecureMode , this);
    int listenPort = __staticvalue::getCurrentNodeInfo()->Getnode_port();
    if(!websocketTransaction->startListen(listenPort))
    {
        qFatal(QString("Can not listen on port %1").arg(QString::number(listenPort)).toLocal8Bit().data());
    }
    connect(websocketTransaction , SIGNAL(signal_receiveNewTransaction(ISO_STRUCTURE)) , blockChain , SLOT(createNewTransaction(ISO_STRUCTURE)));

    __dispatcher::getInstance()->init();


    /////////////////////////////////////
    ///////////////////////////////////// REPORT
    /////////////////////////////////////
    websocketReport = new __websocketserver("Report engin." , QWebSocketServer::NonSecureMode , this);
    listenPort = __staticvalue::getCurrentNodeInfo()->Getnode_service_port();
    if(!websocketReport->startListen(listenPort))
    {
        qFatal(QString("Can not Report listen on port %1").arg(QString::number(listenPort)).toLocal8Bit().data());
    }
}


void MainWindow::slot_showBlock2User(int index, QByteArray data)
{
    qDebug()<<"slot_showBlock2User "<<index;


    QTextCharFormat format = ui->plainTextEdit->currentCharFormat();
    static int counter = 1;
    format.setForeground(QBrush(Qt::white));
    if(counter%2 == 0)
    {
        format.setForeground(QBrush(Qt::yellow));
        counter=0;
    }
    counter++;
    ui->plainTextEdit->setCurrentCharFormat(format);
    ui->plainTextEdit->appendPlainText("--------------------------------------------------- Block "+QString::number(index+1)+" ---------------------------------------------------");
    ui->plainTextEdit->appendPlainText(data);

    qDebug()<<"Block info:\n"<<data;
}
