#include "logparserthread.h"

LogParserThread::LogParserThread()
{
    loop = true;
    mPos = 0;
}

LogParserThread::~LogParserThread()
{
}

void LogParserThread::run()
{
    qDebug() << "LogParserThread::" << __FUNCTION__;

    while(loop)
    {
        QFile file(mLogFileName);

        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream streamLog(&file);
            QString strLine, strAll;

            streamLog.seek(mPos);
            while(((strAll = streamLog.readAll()) != NULL) && loop)
            {
                mPos += strAll.size();
                emit updateModelDataSig(strAll);
            }
        }
        else
        {
            qDebug() << "- open fail.";
        }
        msleep(250);
    }
}

void LogParserThread::quit()
{
    loop = false;
    QThread::quit();
}

void LogParserThread::setLogFileName(QString fileName)
{
    mLogFileName = fileName;
}
