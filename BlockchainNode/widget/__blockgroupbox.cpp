#include "__blockgroupbox.h"

__blockgroupbox::__blockgroupbox(int index, QByteArray data, QObject *parent)
{
    vbox = new QVBoxLayout(this);
    vbox->addStretch(1);
    this->index = index;
    this->data = data;
    init();
}

void __blockgroupbox::init()
{
    setTitle("index:"+QString::number(index));
    QTextEdit *te = new QTextEdit();
    te->setText(data);

    vbox->addWidget(te);
    setLayout(vbox);
}
