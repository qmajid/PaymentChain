#ifndef __REPORTENGIN_H
#define __REPORTENGIN_H

#include <QObject>
#include <QThread>
#include "__staticvalue.h"

class __reportengin : public QThread
{
    Q_OBJECT
public:
    __reportengin(QString key, QString traceNumber);

protected:
    void run();

signals:
    void sendReportResponse(QByteArray, QString);

private:
    QString key;
    QString traceNumber;

    void startSearch();
};

#endif // __REPORTENGIN_H
