#ifndef IOTHREAD_H
#define IOTHREAD_H

#include <QProcess>
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QSaveFile>

#include "logparserthread.h"
#include "const.h"
#include "statusmonitor.h"
#include "inimanager.h"

class IOThread : public QThread
{
    Q_OBJECT

public:
    IOThread();
    ~IOThread();
    void run();
    void quit();

    void setDeviceName(QString);
    void setFileName(QString);


signals:
    void updateModelDataSig(QString);


public slots:
    void updateModelDataSlot(QString strData);


private:
    QProcess* mProcess;
    LogParserThread* mLogParserThread;
    QString mDeviceName;
    QString mFileName;

    void makeConnection();
};

#endif // IOTHREAD_H
