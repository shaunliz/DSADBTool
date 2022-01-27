#include "iothread.h"

IOThread::IOThread()
{
    mLogParserThread = new LogParserThread();
    makeConnection();
}

IOThread::~IOThread()
{
    mLogParserThread->quit();
}

void IOThread::run()
{
    qInfo() << __FUNCTION__ << " / mDeviceName:" << mDeviceName << " / mFileName:" << mFileName;

    bool PackagesChecked = StatusMonitor::GetInstance()->getPackagesChecked();

    QTextStream qout(stdout);
    mProcess = new QProcess();

    QString strCmd = "";
    QString strPid = QString();

    if(IniManager::GetInstance()->getUseAdbPath())
        strCmd += IniManager::GetInstance()->getAdbPath();
    else
        strCmd = ADB_CMD::ADB;

    // log clear.
    if(!mDeviceName.isEmpty())
    {
        strCmd += ADB_CMD::SELECT_DEVICE; /* "adb -s " */
        strCmd += mDeviceName;
    }

    strCmd += ADB_CMD::LOG_CLEAR;
    mProcess->start(strCmd);

    if(!mProcess->waitForFinished())
    {
        qDebug() << "fail to finished process.";
    }

    strCmd.clear();
    msleep(100);

    /* find pid */
    if(PackagesChecked)
    {
        mProcess = new QProcess();

        QString PackageName = StatusMonitor::GetInstance()->getCheckedPackageName();
        qDebug() << "\n\n" << __FUNCTION__ << " / PackageName:" << PackageName;

        if(IniManager::GetInstance()->getUseAdbPath())
            strCmd += IniManager::GetInstance()->getAdbPath();
        else
            strCmd = ADB_CMD::ADB;

        if(!mDeviceName.isEmpty())
        {
            strCmd += ADB_CMD::SELECT_DEVICE; /* "adb -s " */
            strCmd += mDeviceName;
        }

        //strCmd += " shell ps -A | find " + QString("\"") + PackageName + "\"";
        //strCmd += " shell ps -A | grep " + PackageName;
        strCmd += " shell ps -ef -o PID,ARGS=CMD";
        qDebug() << "strCmd:" << strCmd;

        mProcess->setReadChannel(QProcess::StandardOutput);
        mProcess->setProcessChannelMode(QProcess::MergedChannels);
        mProcess->start(strCmd);

        if(!mProcess->waitForStarted())
        {
            qDebug() << "fail to started process.";
        }

        QByteArray processResult;
        msleep(500);

        if(!mProcess->waitForReadyRead())
        {
            qDebug() << "fail to read read.";
        }

        if(!mProcess->waitForFinished())
        {
            qDebug() << "fail to finished process.";
        }

        processResult =  mProcess->readAll();
        //processResult =  mProcess->readAllStandardOutput();

        QString resultString = QString(processResult);
        QStringList resultStrList = resultString.split("\r\n");
        QString itemCheckedPackageName = QString();

        for(int i = 0; i < resultStrList.size(); i++)
        {
            QString item = resultStrList.at(i);
            if(item.contains(PackageName))
            {
                itemCheckedPackageName = item;
                break;
            }
        }

        QStringList splitStr = itemCheckedPackageName.split(' ', QString::SkipEmptyParts);
        if(splitStr.size() > 1) strPid = splitStr.at(0);
    }

    strCmd.clear();
    msleep(100);

    if(IniManager::GetInstance()->getUseAdbPath())
        strCmd += IniManager::GetInstance()->getAdbPath();
    else
        strCmd = ADB_CMD::ADB;

    if(!mDeviceName.isEmpty())
    {
        strCmd += ADB_CMD::SELECT_DEVICE; /* "adb -s " */
        strCmd += mDeviceName;
    }

    strCmd += ADB_CMD::LOG_OPTION_BASIC; /* " logcat -v threadtime" */

    if(PackagesChecked && !strPid.isEmpty())
    {
        strCmd += " --pid=" + strPid;
    }

    qDebug() << " - strCmd:" << strCmd;

    mProcess->setReadChannel(QProcess::StandardOutput);
    mProcess->setProcessChannelMode(QProcess::MergedChannels);
    mProcess->start(strCmd);

    if(!mProcess->waitForStarted())
    {
        qDebug() << "fail to start process.";
    }

    QByteArray result;

    if(!mProcess->waitForReadyRead())
    {
        qDebug() << "failt to read read.";
    }

    mLogParserThread->setLogFileName(mFileName);
    mLogParserThread->start();

    /* while(!mProcess->atEnd()) */
    while(true)
    {
        result = mProcess->readAll();
        //qout << result;

        QFile file(mFileName);

        if(file.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            QTextStream out(&file);
            out << result;
            file.flush();
            /* file.close(); */
        }
        mProcess->waitForReadyRead();
        this->msleep(250);
    }
}

void IOThread::quit()
{
    qInfo() << __FUNCTION__;
    mProcess->kill();
    mLogParserThread->quit();
    QThread::quit();
}

void IOThread::setDeviceName(QString deviceName)
{
    mDeviceName = deviceName;
}

void IOThread::setFileName(QString fileName)
{
    mFileName = fileName;
}

void IOThread::updateModelDataSlot(QString strData)
{
    emit updateModelDataSig(strData);
}

void IOThread::makeConnection()
{
    disconnect(mLogParserThread, SIGNAL(updateModelDataSig(QString)), this, SLOT(updateModelDataSlot(QString)));
    connect(mLogParserThread, SIGNAL(updateModelDataSig(QString)), this, SLOT(updateModelDataSlot(QString)), Qt::DirectConnection);
}
