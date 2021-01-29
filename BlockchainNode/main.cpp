#include "mainwindow.h"
#include <QApplication>
#include <QDebug>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!__staticvalue::readConfigFile())
    {
        qDebug()<<"Can not read config file";
        return -1;
    }

    MainWindow w;
    //w.showMaximized();


//    __blockchain bc;
//    transaction tr;
//    for(int i=0;i<10;i++)
//    {
//        tr.sender="majid";
//        tr.receiver="hamid";
//        tr.amount = (i+1)*10;

//        bc.createNewTransaction(tr);
//    }



    return a.exec();
}
