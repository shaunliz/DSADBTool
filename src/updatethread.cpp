/*
 * not used.
 *
 */
#include "updatethread.h"
#include "statusmonitor.h"
UpdateThread::UpdateThread()
{

}

UpdateThread::UpdateThread(QTableView* tv, QStandardItemModel* model, QString &strData, QMutex* mutex)
{
    mtv = tv;
    mModel = model;
    strLogData = strData;
    mMutex = mutex;

    StatusMonitor* monitor = StatusMonitor::GetInstance();

    int currentTheme = monitor->getCurrentTheme();
}

UpdateThread::~UpdateThread()
{

}

void UpdateThread::run()
{
    mMutex->lock();

    qInfo() << __FUNCTION__;

    /* int row = mModel->rowCount(); */
    QStringList strLogList = strLogData.split("\r\n");

    foreach(QString str, strLogList)
    {
        QStandardItem *item;
        QList<QStandardItem*> itemList;

        //qDebug() << __FUNCTION__ << " row:" << row << " / str:" << str;
        item = new QStandardItem("test0");
        itemList.append(item);

        item = new QStandardItem("test1");
        itemList.append(item);

        item = new QStandardItem("test2");
        itemList.append(item);

        item = new QStandardItem("test3");
        itemList.append(item);

        item = new QStandardItem("test4");
        itemList.append(item);

        item = new QStandardItem("test5");
        itemList.append(item);

        item = new QStandardItem(str);
        itemList.append(item);
        mModel->appendRow(itemList);
    }
    mtv->update();
    mtv->scrollToBottom();
    mMutex->unlock();
}

void UpdateThread::quit()
{
    QThread::quit();
}
