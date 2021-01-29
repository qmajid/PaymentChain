#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include <QProcess>
#include <dialognode.h>
#include <QLabel>
#include <QMutex>

typedef enum
{
    NODE_PSP = 1,
    NODE_SHAPARAK,
    NODE_SHETAB,
    NODE_BANK_SWITCH,
    NODE_POS
}NODE_TYPE;

typedef enum
{
    REQUEST_TRANSACTION = 1,
    REQUEST_REPORT,
}REQUEST_TYPE;

typedef struct
{
    qlonglong receive_time;
    qlonglong response_time;
    int node_type;
    int node_id;
    QString card_number;
    QString terminal_number;
    QString merchant_number;
    int amount;
    QString source;
    QString destination;
    bool is_new_transaction = true;
    QString trace_number;
    REQUEST_TYPE request;
    bool is_approved = false;
}ISO_STRUCTURE;
Q_DECLARE_METATYPE(ISO_STRUCTURE)


typedef struct
{
    QString url;
    QLabel* lable;
}TRACE_STRUCTURE;

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
    void on_btn_send_clicked();
    void onConnected();
    void closed();
    void onTextMessageReceived(QString msg);

    void onConnectedReportServer();
    void closedReportServer();
    void slot_textFrameReceivedReportServer(QString data ,bool islast);

    void on_btn_connect_clicked();
    void createNodesView();

    void readyReadOutput();
    void slot_textFrameReceived(QString data ,bool islast);

    void on_btn_trace_clicked();

private:
    Ui::MainWindow *ui;
    QWebSocket *webSocketTransaction;
    QHash<QProcess*, DialogNode*> processHash;

    void setStyle();
    void parseMessage(QByteArray &input, ISO_STRUCTURE &output);
    void parseMessageReport(QByteArray &input, ISO_STRUCTURE &output);
    QByteArray createMessage(REQUEST_TYPE request, QString from, QString to, double amount, QString traceNumber);
    void loadTraceInfo();

    QString styleTraceLable = "border-radius: %1px; background: %2;";
    int traceLableWidth = 40;
    int approvCount = 0; //تعداد نودهایی که این تراکنش را تایید کرده اند
    QVector<TRACE_STRUCTURE> traceVector;
    QMutex counterMutex;
};

#endif // MAINWINDOW_H
