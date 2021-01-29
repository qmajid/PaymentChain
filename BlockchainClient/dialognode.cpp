#include "dialognode.h"
#include "ui_dialognode.h"
#include <QProcess>

DialogNode::DialogNode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNode)
{
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->btn_status->setText("Stop");
    ui->btn_status->setStyleSheet(greenBackground);
}

void DialogNode::setNodeName(QString nodeName)
{
    ui->label->setText(nodeName);
}

void DialogNode::setProcess(QProcess *process)
{
    this->process = process;
    connect(this->process, SIGNAL(started()), this, SLOT(slot_started()));
    connect(this->process, SIGNAL(finished(int)), this, SLOT(slot_stop(int)));
}

DialogNode::~DialogNode()
{
    delete ui;
}

void DialogNode::showOutput(QString data)
{
    ui->plainTextEdit->appendPlainText(data);
}

void DialogNode::readyReadStandardOutput()
{
    QProcess* p = static_cast<QProcess*> (sender());
    ui->plainTextEdit->appendPlainText(p->readAllStandardOutput());
}

void DialogNode::readyReadStandardError()
{
    QProcess* p = static_cast<QProcess*> (sender());
    ui->plainTextEdit->appendPlainText(p->readAllStandardError());
    ui->plainTextEdit->moveCursor(QTextCursor::End);
}

void DialogNode::on_btn_status_clicked()
{
    QString btnText = ui->btn_status->text().trimmed().toLower();

    if(btnText == "stop")
    {
        //now is running
        process->kill();
    }
    else
    {
        process->start();
    }

}

void DialogNode::on_btn_clear_clicked()
{
    ui->plainTextEdit->clear();
}

void DialogNode::slot_started()
{
    ui->btn_status->setText("Stop");
    ui->btn_status->setStyleSheet(greenBackground);
}

void DialogNode::slot_stop(int )
{
    ui->btn_status->setText("Start");
    ui->btn_status->setStyleSheet(redBackground);
}

void DialogNode::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        event->ignore();
    }else
       event->accept();
}
