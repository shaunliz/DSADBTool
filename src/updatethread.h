#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTableView>
#include <QStandardItemModel>
#include <QMutex>

class UpdateThread : public QThread
{
    Q_OBJECT

public:
    UpdateThread();
    UpdateThread(QTableView* tv, QStandardItemModel* model, QString &strData, QMutex *mutex);
    ~UpdateThread();

    void run();
    void quit();

private:
    QMutex mutex;
    QTableView *mtv;
    QStandardItemModel *mModel;
    QString strLogData;
    QMutex *mMutex;
};

#endif // UPDATETHREAD_H
