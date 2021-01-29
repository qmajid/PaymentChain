#ifndef __BLOCKGROUPBOX_H
#define __BLOCKGROUPBOX_H

#include <QObject>
#include <QGroupBox>
#include <QTextEdit>
#include <QVBoxLayout>

class __blockgroupbox : public QGroupBox
{
    Q_OBJECT
public:
    __blockgroupbox(int index , QByteArray data , QObject *parent=0);

private:
    void init();
    int index;
    QByteArray data;
    QVBoxLayout *vbox;
};

#endif // __BLOCKGROUPBOX_H
