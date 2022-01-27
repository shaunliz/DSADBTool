#include "ioworker.h"

IOWorker::IOWorker(QObject *parent) : QObject(parent)
{

}

void IOWorker::doWork()
{
    qDebug() << __FUNCTION__;

//    QProcess process;
//    process.start("adb logcat >> log.txt");
//    process.waitForFinished(-1);
//    QByteArray logcatOut = process.readAllStandardOutput();
//    QString logString = QString::fromStdString(logcatOut.toStdString());
}
