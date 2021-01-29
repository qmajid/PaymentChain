#ifndef __ISO_H
#define __ISO_H

#include <QObject>
#include "__staticvalue.h"


class __iso : public QObject
{
    Q_OBJECT
public:
    explicit __iso(QObject *parent = nullptr);
    void createMessage(ISO_STRUCTURE& input, QByteArray &output);
    void parseMessage(QByteArray &input, ISO_STRUCTURE& output);

signals:

public slots:
};

#endif // __ISO_H
