/********************************************************************************
** Form generated from reading UI file 'dialognode.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGNODE_H
#define UI_DIALOGNODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogNode
{
public:
    QGridLayout *gridLayout;
    QPushButton *btn_status;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QPushButton *btn_clear;

    void setupUi(QDialog *DialogNode)
    {
        if (DialogNode->objectName().isEmpty())
            DialogNode->setObjectName(QString::fromUtf8("DialogNode"));
        DialogNode->resize(400, 300);
        gridLayout = new QGridLayout(DialogNode);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        btn_status = new QPushButton(DialogNode);
        btn_status->setObjectName(QString::fromUtf8("btn_status"));
        btn_status->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 252);\n"
""));

        gridLayout->addWidget(btn_status, 0, 0, 1, 1);

        label = new QLabel(DialogNode);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("color: rgb(8, 249, 108);\n"
"font: 14pt \"Ubuntu\";"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        plainTextEdit = new QPlainTextEdit(DialogNode);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 215, 207);"));
        plainTextEdit->setReadOnly(true);
        plainTextEdit->setMaximumBlockCount(2000);
        plainTextEdit->setCenterOnScroll(false);

        gridLayout->addWidget(plainTextEdit, 1, 0, 1, 3);

        btn_clear = new QPushButton(DialogNode);
        btn_clear->setObjectName(QString::fromUtf8("btn_clear"));
        btn_clear->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 252);"));

        gridLayout->addWidget(btn_clear, 0, 1, 1, 1);


        retranslateUi(DialogNode);

        QMetaObject::connectSlotsByName(DialogNode);
    } // setupUi

    void retranslateUi(QDialog *DialogNode)
    {
        DialogNode->setWindowTitle(QApplication::translate("DialogNode", "Dialog", nullptr));
        btn_status->setText(QApplication::translate("DialogNode", "Stop", nullptr));
        label->setText(QApplication::translate("DialogNode", "TextLabel", nullptr));
        btn_clear->setText(QApplication::translate("DialogNode", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogNode: public Ui_DialogNode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGNODE_H
