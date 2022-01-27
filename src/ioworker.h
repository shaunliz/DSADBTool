#ifndef IOWORKER_H
#define IOWORKER_H

#include <QObject>
#include <QDebug>
#include <QProcess>

#include "const.h"

class IOWorker : public QObject
{
    Q_OBJECT


public:
    explicit IOWorker(QObject *parent = nullptr);


signals:
    void start(const QString &str);


public slots:
    void doWork();
};

#endif // IOWORKER_H
