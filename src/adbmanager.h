#ifndef ADBMANAGER_H
#define ADBMANAGER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QProgressDialog>

#include "const.h"
#include "inimanager.h"

class AdbManager : public QObject
{
    Q_OBJECT
public:
    static AdbManager* GetInstance();

    QList<QString> queryAttachedDeviceList();
    QList<QString> queryInstalledPackageList(QString selectedDeviceName = "");
    void clearLogData(QString deviceName);
    void installApkFile(QString deviceName, QString pathApk);

signals:
    void showProgressSig(QProgressDialog*);

public slots:

private slots:
    void showProgressSlot(QProgressDialog*);

private:
    explicit AdbManager(QObject *parent = nullptr);
    static AdbManager* instance;
    QProgressDialog* mProgressDlg;
};

#endif // ADBMANAGER_H
