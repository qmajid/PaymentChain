/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QFrame *frame_nodes;
    QFrame *frame_transaction;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_connect;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit_port;
    QLabel *label_3;
    QLineEdit *lineEdit_amount;
    QLineEdit *lineEdit_ip;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_send;
    QLineEdit *lineEdit_to;
    QLineEdit *lineEdit_from;
    QPushButton *btn_connect;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_2;
    QLineEdit *lineEdit_inputtracenumber;
    QFrame *frame_trace;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_trace;
    QLineEdit *lineEdit_tracenumber;
    QLabel *label_traceResualt;
    QGridLayout *gridLayout;
    QLabel *label_psp1;
    QLabel *label_psp2;
    QLabel *label_psp3;
    QLabel *label_psp4;
    QLabel *label_shp;
    QLabel *label_shb;
    QLabel *label_b1;
    QLabel *label_b2;
    QLabel *label_b3;
    QLabel *label_b4;
    QSpacerItem *horizontalSpacer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1196, 423);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 1, 32);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame_nodes = new QFrame(centralWidget);
        frame_nodes->setObjectName(QString::fromUtf8("frame_nodes"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_nodes->sizePolicy().hasHeightForWidth());
        frame_nodes->setSizePolicy(sizePolicy);
        frame_nodes->setFrameShape(QFrame::StyledPanel);
        frame_nodes->setFrameShadow(QFrame::Raised);

        gridLayout_3->addWidget(frame_nodes, 2, 0, 1, 1);

        frame_transaction = new QFrame(centralWidget);
        frame_transaction->setObjectName(QString::fromUtf8("frame_transaction"));
        frame_transaction->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 252);\n"
""));
        frame_transaction->setFrameShape(QFrame::StyledPanel);
        frame_transaction->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_transaction);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout_connect = new QGridLayout();
        gridLayout_connect->setSpacing(6);
        gridLayout_connect->setObjectName(QString::fromUtf8("gridLayout_connect"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_connect->addItem(verticalSpacer, 5, 1, 1, 1);

        lineEdit_port = new QLineEdit(frame_transaction);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_port->sizePolicy().hasHeightForWidth());
        lineEdit_port->setSizePolicy(sizePolicy1);

        gridLayout_connect->addWidget(lineEdit_port, 0, 1, 1, 1);

        label_3 = new QLabel(frame_transaction);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_connect->addWidget(label_3, 3, 0, 1, 1);

        lineEdit_amount = new QLineEdit(frame_transaction);
        lineEdit_amount->setObjectName(QString::fromUtf8("lineEdit_amount"));
        sizePolicy1.setHeightForWidth(lineEdit_amount->sizePolicy().hasHeightForWidth());
        lineEdit_amount->setSizePolicy(sizePolicy1);

        gridLayout_connect->addWidget(lineEdit_amount, 3, 1, 1, 3);

        lineEdit_ip = new QLineEdit(frame_transaction);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_ip->sizePolicy().hasHeightForWidth());
        lineEdit_ip->setSizePolicy(sizePolicy2);

        gridLayout_connect->addWidget(lineEdit_ip, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btn_send = new QPushButton(frame_transaction);
        btn_send->setObjectName(QString::fromUtf8("btn_send"));
        btn_send->setEnabled(false);

        horizontalLayout_4->addWidget(btn_send);


        gridLayout_connect->addLayout(horizontalLayout_4, 0, 3, 1, 1);

        lineEdit_to = new QLineEdit(frame_transaction);
        lineEdit_to->setObjectName(QString::fromUtf8("lineEdit_to"));
        sizePolicy1.setHeightForWidth(lineEdit_to->sizePolicy().hasHeightForWidth());
        lineEdit_to->setSizePolicy(sizePolicy1);

        gridLayout_connect->addWidget(lineEdit_to, 2, 1, 1, 3);

        lineEdit_from = new QLineEdit(frame_transaction);
        lineEdit_from->setObjectName(QString::fromUtf8("lineEdit_from"));
        sizePolicy1.setHeightForWidth(lineEdit_from->sizePolicy().hasHeightForWidth());
        lineEdit_from->setSizePolicy(sizePolicy1);

        gridLayout_connect->addWidget(lineEdit_from, 1, 1, 1, 3);

        btn_connect = new QPushButton(frame_transaction);
        btn_connect->setObjectName(QString::fromUtf8("btn_connect"));

        gridLayout_connect->addWidget(btn_connect, 0, 2, 1, 1);

        label = new QLabel(frame_transaction);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_connect->addWidget(label, 2, 0, 1, 1);

        label_4 = new QLabel(frame_transaction);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_connect->addWidget(label_4, 4, 0, 1, 1);

        label_2 = new QLabel(frame_transaction);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_connect->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_inputtracenumber = new QLineEdit(frame_transaction);
        lineEdit_inputtracenumber->setObjectName(QString::fromUtf8("lineEdit_inputtracenumber"));
        lineEdit_inputtracenumber->setReadOnly(true);

        gridLayout_connect->addWidget(lineEdit_inputtracenumber, 4, 1, 1, 3);


        gridLayout_2->addLayout(gridLayout_connect, 1, 0, 1, 1);

        frame_trace = new QFrame(frame_transaction);
        frame_trace->setObjectName(QString::fromUtf8("frame_trace"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame_trace->sizePolicy().hasHeightForWidth());
        frame_trace->setSizePolicy(sizePolicy3);
        frame_trace->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 252);"));
        frame_trace->setFrameShape(QFrame::StyledPanel);
        frame_trace->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_trace);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_trace = new QPushButton(frame_trace);
        btn_trace->setObjectName(QString::fromUtf8("btn_trace"));
        btn_trace->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(btn_trace);

        lineEdit_tracenumber = new QLineEdit(frame_trace);
        lineEdit_tracenumber->setObjectName(QString::fromUtf8("lineEdit_tracenumber"));
        lineEdit_tracenumber->setMinimumSize(QSize(200, 0));

        horizontalLayout->addWidget(lineEdit_tracenumber);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

        label_traceResualt = new QLabel(frame_trace);
        label_traceResualt->setObjectName(QString::fromUtf8("label_traceResualt"));
        sizePolicy.setHeightForWidth(label_traceResualt->sizePolicy().hasHeightForWidth());
        label_traceResualt->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(label_traceResualt, 1, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_psp1 = new QLabel(frame_trace);
        label_psp1->setObjectName(QString::fromUtf8("label_psp1"));
        label_psp1->setMaximumSize(QSize(40, 40));
        label_psp1->setStyleSheet(QString::fromUtf8("border-radius: 20px; \n"
"background: red; \n"
"color: #4A0C46;"));
        label_psp1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_psp1, 0, 0, 1, 1);

        label_psp2 = new QLabel(frame_trace);
        label_psp2->setObjectName(QString::fromUtf8("label_psp2"));
        label_psp2->setMaximumSize(QSize(40, 40));
        label_psp2->setStyleSheet(QString::fromUtf8("border-radius: 20px; \n"
"background: red; \n"
"color: #4A0C46;"));
        label_psp2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_psp2, 0, 1, 1, 1);

        label_psp3 = new QLabel(frame_trace);
        label_psp3->setObjectName(QString::fromUtf8("label_psp3"));
        label_psp3->setMaximumSize(QSize(40, 40));
        label_psp3->setStyleSheet(QString::fromUtf8("border-radius: 20px; \n"
"background: red; \n"
"color: #4A0C46;"));
        label_psp3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_psp3, 0, 2, 1, 1);

        label_psp4 = new QLabel(frame_trace);
        label_psp4->setObjectName(QString::fromUtf8("label_psp4"));
        label_psp4->setMaximumSize(QSize(40, 40));
        label_psp4->setStyleSheet(QString::fromUtf8("border-radius: 20px; \n"
"background: red; \n"
"color: #4A0C46;"));
        label_psp4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_psp4, 0, 3, 1, 1);

        label_shp = new QLabel(frame_trace);
        label_shp->setObjectName(QString::fromUtf8("label_shp"));
        label_shp->setMaximumSize(QSize(40, 40));
        label_shp->setStyleSheet(QString::fromUtf8("border-radius: 20px; \n"
"background: red; \n"
"color: #4A0C46;"));
        label_shp->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_shp, 1, 1, 1, 1);

        label_shb = new QLabel(frame_trace);
        label_shb->setObjectName(QString::fromUtf8("label_shb"));
        label_shb->setMaximumSize(QSize(40, 40));
        label_shb->setStyleSheet(QString::fromUtf8("border-radius: 20px; \n"
"background: red; \n"
"color: #4A0C46;"));
        label_shb->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_shb, 1, 2, 1, 1);

        label_b1 = new QLabel(frame_trace);
        label_b1->setObjectName(QString::fromUtf8("label_b1"));
        label_b1->setMaximumSize(QSize(40, 40));
        label_b1->setStyleSheet(QString::fromUtf8("border-radius: 20px; \n"
"background: red; \n"
"color: #4A0C46;"));
        label_b1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_b1, 2, 0, 1, 1);

        label_b2 = new QLabel(frame_trace);
        label_b2->setObjectName(QString::fromUtf8("label_b2"));
        label_b2->setMaximumSize(QSize(40, 40));
        label_b2->setStyleSheet(QString::fromUtf8("border-radius: 20px; \n"
"background: red; \n"
"color: #4A0C46;"));
        label_b2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_b2, 2, 1, 1, 1);

        label_b3 = new QLabel(frame_trace);
        label_b3->setObjectName(QString::fromUtf8("label_b3"));
        label_b3->setMaximumSize(QSize(40, 40));
        label_b3->setStyleSheet(QString::fromUtf8("border-radius: 20px; \n"
"background: red; \n"
"color: #4A0C46;"));
        label_b3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_b3, 2, 2, 1, 1);

        label_b4 = new QLabel(frame_trace);
        label_b4->setObjectName(QString::fromUtf8("label_b4"));
        label_b4->setMaximumSize(QSize(40, 40));
        label_b4->setStyleSheet(QString::fromUtf8("border-radius: 20px; \n"
"background: red; \n"
"color: #4A0C46;"));
        label_b4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_b4, 2, 3, 1, 1);


        gridLayout_4->addLayout(gridLayout, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 1, 1, 1, 1);


        gridLayout_2->addWidget(frame_trace, 1, 2, 1, 1);


        gridLayout_3->addWidget(frame_transaction, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        lineEdit_port->setText(QApplication::translate("MainWindow", "5234", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Amount", nullptr));
        lineEdit_amount->setText(QApplication::translate("MainWindow", "1000", nullptr));
        lineEdit_ip->setText(QApplication::translate("MainWindow", "127.0.0.1", nullptr));
        btn_send->setText(QApplication::translate("MainWindow", "Send", nullptr));
        lineEdit_to->setText(QApplication::translate("MainWindow", "b", nullptr));
        lineEdit_from->setText(QApplication::translate("MainWindow", "a", nullptr));
        btn_connect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        label->setText(QApplication::translate("MainWindow", "To", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Trace nubmer", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "From", nullptr));
        lineEdit_inputtracenumber->setPlaceholderText(QApplication::translate("MainWindow", "trace number", nullptr));
        btn_trace->setText(QApplication::translate("MainWindow", "   Start trace   ", nullptr));
        lineEdit_tracenumber->setPlaceholderText(QApplication::translate("MainWindow", "enter trace number", nullptr));
        label_traceResualt->setText(QString());
        label_psp1->setText(QApplication::translate("MainWindow", "PSP1", nullptr));
        label_psp2->setText(QApplication::translate("MainWindow", "PSP2", nullptr));
        label_psp3->setText(QApplication::translate("MainWindow", "PSP3", nullptr));
        label_psp4->setText(QApplication::translate("MainWindow", "PSP4", nullptr));
        label_shp->setText(QApplication::translate("MainWindow", "SHP", nullptr));
        label_shb->setText(QApplication::translate("MainWindow", "SHB", nullptr));
        label_b1->setText(QApplication::translate("MainWindow", "B1", nullptr));
        label_b2->setText(QApplication::translate("MainWindow", "B2", nullptr));
        label_b3->setText(QApplication::translate("MainWindow", "B3", nullptr));
        label_b4->setText(QApplication::translate("MainWindow", "B4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
