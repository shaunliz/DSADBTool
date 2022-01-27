#ifndef LOGPARSERTHREAD_H
#define LOGPARSERTHREAD_H

#include <QThread>
#include <QDebug>
#include <QFile>
#include <QLockFile>
#include <QSaveFile>

class LogParserThread : public QThread
{
    Q_OBJECT

public:
    LogParserThread();
    ~LogParserThread();
    void run();
    void quit();

    void setLogFileName(QString fileName);

signals:
    void updateModelDataSig(QString data);

private:
    bool loop;
    QString mLogFileName;
    int mPos;
};

#endif // LOGPARSERTHREAD_H
