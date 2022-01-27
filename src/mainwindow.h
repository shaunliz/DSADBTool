#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QByteArray>
#include <QDebug>
#include <QThread>
#include <QDate>
#include <QDateTime>
#include <QTableView>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QCollator>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

#include "adbmanager.h"
#include "devicemanager.h"
#include "ioworker.h"
#include "iothread.h"
#include "logparserthread.h"
#include "updatethread.h"
#include "updatemanager.h"
#include "thememanager.h"
#include "statusmonitor.h"
#include "logproxymodel.h"
#include "filtermanager.h"
#include "preferencesdialog.h"
#include "aboutdialog.h"

#ifdef Q_OS_WIN
#include <Windows.h> /* for Sleep */
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void closeEvent(QCloseEvent* event);


public slots:
    void changeDeviceSelection();
    void clidkedRefreshDeviceList();
    void clickedRunButton();
    void clickedStopButton();
    void clickedClearButton();
    void clickedScrollButton();
    void clickedUserGuide();
    void clickedAbout();
    void receivedLogData(QString str);
    void themeChangeToDefault();
    void themeChangeToAdaptic();
    void themeChangeToCombinear();
    void themeChangeToDarkeum();
    void themeChangeToDiffnes();
    void themeChangeToFibers();
    void themeChangeToIntegrid();
    void themeChangeToIrrorater();
    void changeStatusSlot(OP_STATUS);    void tvSelectionItemChanged(const QItemSelection &, const QItemSelection);

    void queryDevicePackageListSlot();
    void logLevelChangedSlot();
    void showColumnChangeSlot();
    void packagesCheckedSlot(int state);
    void checkedPackageNameChangedSlot(const QString checkedPackageName);
    void clickedSelectInstallApkButton();
    void clickedInstallApkButton();
    void clickedSelectAab2ApkButton();
    void clickedConvertAab2ApkButton();
    void actionPreferences();
    void actionAbout();
    void menuExit();

signals:
    void changeStatusSig(OP_STATUS);
    void queryDevicePackageListSig();


private:
    void initialization();
    void makeConnection();
    void makeConnectionIoThread();
    void makeThreadConnection();
    void updateDeviceList();
    QString makeLogFileName();
    void initTable();
    void prepare();
    void updateColumnDisplay();
    void uiSleep(int ms);

    Ui::MainWindow *ui;
    AdbManager* mAdbMgr;
    DeviceManager* mDeviceMgr;
    IOWorker* mIoWorker;
    IOThread* mIoThread;
    ThemeManager* mThemeMgr;
    //LogParserThread* mLogParserThread;
    UpdateManager* mUpdateMgr;
    StatusMonitor* mStatusMonitor;
    LogProxyModel *mProxyModel;
    FilterManager* mFilterMgr;

    QProcess mProcess;
    QString mLogFileName;
    QWidget* mTabAll;
    QWidget* mTabXSign;
    QTableView *mTableView;
    //QTableWidget *mTableView;
    QTableView *mMagicXSignTableView;
    QStandardItemModel *model;
    QStandardItemModel *mMagicXSignModel;
    QMutex mutex;

    //QAction *actionThemeDefault;

    /* static void runAdb(); */
};

#endif // MAINWINDOW_H
