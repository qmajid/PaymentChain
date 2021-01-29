#ifndef DIALOGNODE_H
#define DIALOGNODE_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class DialogNode;
}

class DialogNode : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNode(QWidget *parent = 0);
    void setNodeName(QString nodeName);
    void setProcess(QProcess* process);
    ~DialogNode();

public slots:
    void showOutput(QString data);
    void readyReadStandardOutput();
    void readyReadStandardError();

private slots:
    void on_btn_status_clicked();

    void on_btn_clear_clicked();

    void slot_started();
    void slot_stop(int);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::DialogNode *ui;
    QProcess *process;
    QString greenBackground = "background-color: rgb(78, 154, 6);";
    QString redBackground   = "background-color: rgb(204, 0, 0);";
};

#endif // DIALOGNODE_H
