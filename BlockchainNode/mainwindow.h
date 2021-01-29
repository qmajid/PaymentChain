#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "network/__websocketserver.h"
#include "block/__blockchain.h"
#include "widget/__blockgroupbox.h"
#include "__staticvalue.h"
#include "network/__dispatcher.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slot_showBlock2User(int index ,QByteArray data);

private:
    Ui::MainWindow *ui;
    __websocketserver *websocketTransaction;
    __websocketserver *websocketReport;
    __blockchain *blockChain;

    void init();
};

#endif // MAINWINDOW_H
