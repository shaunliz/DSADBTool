#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace DSADB_TOOL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* deco. - transparent. */
    // parent->setWindowFlag(Qt::FramelessWindowHint);
    // parent->setAttribute(Qt::WA_TranslucentBackground, true);
    // parent->setStyleSheet("background-color: rgba(255, 0, 0, 128)");

    initialization();
    initTable();
    updateDeviceList();
    makeConnection();
    makeThreadConnection();

    prepare();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(mIoThread != nullptr)
    {
        if(mIoThread->isRunning())
        {
            mIoThread->quit();  /* emit mIoThread->finished(); */
            mIoThread = nullptr;
        }
    }
}

/* slots */
void MainWindow::changeDeviceSelection()
{
    QList<QListWidgetItem*> selectedDeviceName = ui->listWidgetDevice->selectedItems();

    if(selectedDeviceName.count() > 0)
    {
        mDeviceMgr->setSelectedDeviceName(selectedDeviceName.first()->text());
    }
    else
    {
        mDeviceMgr->setSelectedDeviceName(" ");
    }

    emit queryDevicePackageListSig();
}

void MainWindow::clidkedRefreshDeviceList()
{
    qDebug() << "clidkedRefreshDeviceList()";
    updateDeviceList();
}

void MainWindow::clickedRunButton()
{
    qDebug() << __FUNCTION__;

    mStatusMonitor = StatusMonitor::GetInstance();
    mLogFileName = makeLogFileName();

    if(mIoThread == nullptr)
    {
        mIoThread = new IOThread();
        makeConnectionIoThread();
    }

    if(mIoThread != nullptr)
    {
        qDebug() << __FUNCTION__ << "    - start io thread";
        mIoThread->setDeviceName(mDeviceMgr->getSelectedDeviceName());
        mIoThread->setFileName(mLogFileName);
        mIoThread->start();

        mStatusMonitor->setCurrentOpStatus(OP_STATUS::STATUS_PLAY);
        mStatusMonitor->setScrollStatus(true);

        changeStatusSig(mStatusMonitor->getCurrentOpStatus());
    }
}

void MainWindow::clickedStopButton()
{
    qDebug() << __FUNCTION__;

    if(mIoThread != nullptr)
    {
        if(mIoThread->isRunning())
        {
            qDebug() << "    - call stop thread.";
            mIoThread->quit();  /* emit mIoThread->finished(); */
            mIoThread = nullptr;

            mStatusMonitor->setCurrentOpStatus(OP_STATUS::STATUS_STOP);
            mStatusMonitor->setScrollStatus(false);

            changeStatusSig(mStatusMonitor->getCurrentOpStatus());
        }
    }
}

void MainWindow::clickedClearButton()
{
    qDebug() << __FUNCTION__;

    AdbManager::GetInstance()->clearLogData(mDeviceMgr->getSelectedDeviceName());

    if(mTableView != nullptr)
    {
        mTableView->clearSpans();
    }
    mTableView->model()->removeRows(0, mTableView->model()->rowCount());

    if(mMagicXSignTableView != nullptr)
    {
        mMagicXSignTableView->clearSpans();
    }
    mMagicXSignTableView->model()->removeRows(0, mMagicXSignTableView->model()->rowCount());

}

void MainWindow::clickedScrollButton()
{
    StatusMonitor* statusMonitor = StatusMonitor::GetInstance();

    qDebug() << __FUNCTION__ << " / statusMonitor->getScrollStatus():" << statusMonitor->getScrollStatus();

    if(statusMonitor->getScrollStatus())
    {
        statusMonitor->setScrollStatus(false);
        ui->btnScroll->setDown(false);
    }
    else
    {
        statusMonitor->setScrollStatus(true);
        ui->btnScroll->setDown(true);
    }
}

void MainWindow::clickedUserGuide()
{
    qDebug() << __FUNCTION__;
}

void MainWindow::clickedAbout()
{
    qDebug() << __FUNCTION__;
}

void MainWindow::receivedLogData(QString strData)
{

    /*QStringList strLogList = strData.split("\r\n");

    if(strLogList.length() > 0)
        qDebug() << "strLogList.at(0):" << strLogList.at(0);

    UpdateThread *uThread = new UpdateThread(mTableView, model, strData, &mutex);
    uThread->start();*/

    // prev. code
    mUpdateMgr->updateLogData(strData);
}

void MainWindow::themeChangeToDefault()
{
    QString styleSheet = mThemeMgr->getDefaultTheme();
    this->setStyleSheet(styleSheet);

    mUpdateMgr->setTheme(THEME_TYPE::DEFAULT);
    StatusMonitor::GetInstance()->setCurrentTheme(THEME_TYPE::DEFAULT);
}

void MainWindow::themeChangeToAdaptic()
{
    this->setStyleSheet("");
    QString styleSheet = mThemeMgr->getAdapticTheme();
    this->setStyleSheet(styleSheet);

    mUpdateMgr->setTheme(THEME_TYPE::ADAPTIC);
    StatusMonitor::GetInstance()->setCurrentTheme(THEME_TYPE::ADAPTIC);
}

void MainWindow::themeChangeToCombinear()
{
    this->setStyleSheet("");
    QString styleSheet = mThemeMgr->getCombinearTheme();
    this->setStyleSheet(styleSheet);

    mUpdateMgr->setTheme(THEME_TYPE::COMBINEAR);
    StatusMonitor::GetInstance()->setCurrentTheme(THEME_TYPE::COMBINEAR);
}

void MainWindow::themeChangeToDarkeum()
{
    this->setStyleSheet("");
    QString styleSheet = mThemeMgr->getDarkeumTheme();
    this->setStyleSheet(styleSheet);

    mUpdateMgr->setTheme(THEME_TYPE::DARKEUM);
    StatusMonitor::GetInstance()->setCurrentTheme(THEME_TYPE::DARKEUM);
}

void MainWindow::themeChangeToDiffnes()
{
    this->setStyleSheet("");
    QString styleSheet = mThemeMgr->getDiffnesTheme();
    this->setStyleSheet(styleSheet);

    mUpdateMgr->setTheme(THEME_TYPE::DIFFNES);
    StatusMonitor::GetInstance()->setCurrentTheme(THEME_TYPE::DIFFNES);
}

void MainWindow::themeChangeToFibers()
{
    this->setStyleSheet("");
    QString styleSheet = mThemeMgr->getFibersTheme();
    this->setStyleSheet(styleSheet);

    mUpdateMgr->setTheme(THEME_TYPE::FIBERS);
    StatusMonitor::GetInstance()->setCurrentTheme(THEME_TYPE::FIBERS);
}

void MainWindow::themeChangeToIntegrid()
{
    this->setStyleSheet("");
    QString styleSheet = mThemeMgr->getIntegridTheme();
    this->setStyleSheet(styleSheet);

    mUpdateMgr->setTheme(THEME_TYPE::INTEGRID);
    StatusMonitor::GetInstance()->setCurrentTheme(THEME_TYPE::INTEGRID);
}

void MainWindow::themeChangeToIrrorater()
{
    this->setStyleSheet("");
    QString styleSheet = mThemeMgr->getIrroraterTheme();
    this->setStyleSheet(styleSheet);

    mUpdateMgr->setTheme(THEME_TYPE::IRRORATER);
    StatusMonitor::GetInstance()->setCurrentTheme(THEME_TYPE::IRRORATER);
}

void MainWindow::changeStatusSlot(OP_STATUS status)
{
    if(status == OP_STATUS::STATUS_STOP)
    {
        ui->btnRun->setEnabled(true);
        ui->btnPause->setDisabled(true);
        ui->btnStop->setDisabled(true);
        ui->btnScroll->setDown(false);
    }
    else if(status == OP_STATUS::STATUS_PLAY)
    {
        ui->btnRun->setDisabled(true);
        ui->btnPause->setEnabled(true);
        ui->btnStop->setEnabled(true);
        ui->btnScroll->setDown(true);
    }
    else
    {
        ;//ui->btnRun->setEnabled(true);
    }
}

void MainWindow::tvSelectionItemChanged(const QItemSelection &, const QItemSelection)
{
    if(StatusMonitor::GetInstance()->getScrollStatus())
    {
        StatusMonitor::GetInstance()->setScrollStatus(false);
        ui->btnScroll->setDown(false);
    }
}

void MainWindow::queryDevicePackageListSlot()
{

    qInfo() << __FUNCTION__;

    if(mAdbMgr == nullptr)
        mAdbMgr = AdbManager::GetInstance();

    ui->cbPackageList->clear();

    QStringList packageList = mAdbMgr->queryInstalledPackageList(mDeviceMgr->getSelectedDeviceName());

    QCollator collator;
    collator.setCaseSensitivity(Qt::CaseInsensitive);
    std::sort(packageList.begin(), packageList.end(), collator);

    ui->cbPackageList->addItems(packageList);
}

void MainWindow::logLevelChangedSlot()
{
    /* update log level -> statusmonitor */
    int logLevel = 0;
    int prevLogLevel = mStatusMonitor->GetInstance()->getLogLevel();

    if(ui->checkBoxV->isChecked()) {  logLevel = logLevel|LOG_LEVEL::VERBOSE;   mFilterMgr->setShowV(true); } else mFilterMgr->setShowV(false);
    if(ui->checkBoxD->isChecked()) {  logLevel = logLevel|LOG_LEVEL::DEBUG;     mFilterMgr->setShowD(true); } else mFilterMgr->setShowD(false);
    if(ui->checkBoxI->isChecked()) {  logLevel = logLevel|LOG_LEVEL::INFO;      mFilterMgr->setShowI(true); } else mFilterMgr->setShowI(false);
    if(ui->checkBoxW->isChecked()) {  logLevel = logLevel|LOG_LEVEL::WARN;      mFilterMgr->setShowW(true); } else mFilterMgr->setShowW(false);
    if(ui->checkBoxE->isChecked()) {  logLevel = logLevel|LOG_LEVEL::ERROR_LOG;     mFilterMgr->setShowE(true); } else mFilterMgr->setShowE(false);
    if(ui->checkBoxF->isChecked()) {  logLevel = logLevel|LOG_LEVEL::FATAL;     mFilterMgr->setShowF(true); } else mFilterMgr->setShowF(false);

    mStatusMonitor->GetInstance()->setLogLevel(logLevel);
    /* mUpdateMgr->updateFilteredModel(prevLogLevel, logLevel); // :: proxy model 로 처리하도록 변경 함. */

    qDebug() << __FUNCTION__ << " / logLevel:" << logLevel;
}

void MainWindow::showColumnChangeSlot()
{
    /* show column -> statusmonitor */
    int showColumn = 0;

    if(ui->checkBoxDate->isChecked()) showColumn = showColumn|SHOW_COLUMN::COL_DATE;
    if(ui->checkBoxTime->isChecked()) showColumn = showColumn|SHOW_COLUMN::COL_TIME;
    if(ui->checkBoxLogLevel->isChecked()) showColumn = showColumn|SHOW_COLUMN::COL_LEVEL;
    if(ui->checkBoxPid->isChecked()) showColumn = showColumn|SHOW_COLUMN::COL_PID;
    if(ui->checkBoxThread->isChecked()) showColumn = showColumn|SHOW_COLUMN::COL_TID;

    mStatusMonitor->GetInstance()->setShowColumn(showColumn);

    qDebug() << __FUNCTION__ << " / showColumn:" << showColumn;

    updateColumnDisplay();
}

void MainWindow::packagesCheckedSlot(int state)
{
    mStatusMonitor = StatusMonitor::GetInstance();
    qDebug() << __FUNCTION__ << " / state:" << state << " / Op Status:" << mStatusMonitor->getCurrentOpStatus();

    if(Qt::Checked == state)
    {
        mStatusMonitor->setPackagesChecked(true);
        mStatusMonitor->setCheckedPackageName(ui->cbPackageList->currentText());
    }
    else
    {
        mStatusMonitor->setPackagesChecked(false);
    }

    if(OP_STATUS::STATUS_PLAY != mStatusMonitor->getCurrentOpStatus())
    {
        return;
    }
    else
    {
        clickedStopButton();
        this->uiSleep(300);
        clickedRunButton();
    }
}

void MainWindow::checkedPackageNameChangedSlot(const QString checkedPackageName)
{
    qDebug() << __FUNCTION__ << " / packageName:" << checkedPackageName;

    mStatusMonitor = StatusMonitor::GetInstance();
    mStatusMonitor->setCheckedPackageName(checkedPackageName);

    if(OP_STATUS::STATUS_PLAY != mStatusMonitor->getCurrentOpStatus())
    {
        return;
    }

    bool checkedStatus = mStatusMonitor->getPackagesChecked();

    if(checkedStatus)
    {
        qInfo() << __FUNCTION__ << " / checked Package / name:" << mStatusMonitor->getCheckedPackageName();

        clickedStopButton();
        this->uiSleep(300);
        clickedRunButton();
    }
    else
    {
        qInfo() << __FUNCTION__ << " / unchecked Package / name:" << mStatusMonitor->getCheckedPackageName();
    }
}

void MainWindow::clickedSelectInstallApkButton()
{
    QStringList strListPaths = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    QString filePath = QFileDialog::getOpenFileName(this, "Select APK File.", strListPaths.first(), "Apk Files(*.apk)");
    qDebug() << __FUNCTION__ << " / filePath:" << filePath;

    if(!filePath.isEmpty() && filePath.compare("") != 0)
        ui->lineEditPathApk->setText(filePath);
}

void MainWindow::clickedInstallApkButton()
{
    QFile file(ui->lineEditPathApk->text());

    if(!file.exists())
    {
        QMessageBox msgBox;
        QString _path = ui->lineEditPathApk->text();
        QDir d = QFileInfo(_path).absoluteFilePath();
        QString absolute = d.path();

        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("File Does not exist.");
        msgBox.setInformativeText(absolute);//ui->lineEditPathApk->text());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        msgBox.exec();
        return;
    }

    qDebug() << __FUNCTION__ << " / file exist.";


    if(mAdbMgr == nullptr)
        mAdbMgr = AdbManager::GetInstance();

    QString pathApk(ui->lineEditPathApk->text());

    mAdbMgr->installApkFile(mDeviceMgr->getSelectedDeviceName(), pathApk);
}

void MainWindow::clickedSelectAab2ApkButton()
{
    QStringList strListPaths = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    QString filePath = QFileDialog::getOpenFileName(this, "Select AAB File.", strListPaths.first(), "Aab Files(*.aab)");
    qDebug() << __FUNCTION__ << " / filePath:" << filePath;

    if(!filePath.isEmpty() && filePath.compare("") != 0)
        ui->lineEditPathAab->setText(filePath);
}

void MainWindow::clickedConvertAab2ApkButton()
{
    QFile file(ui->lineEditPathAab->text());

    if(!file.exists())
    {
        QMessageBox msgBox;
        QString _path = ui->lineEditPathAab->text();
        QDir d = QFileInfo(_path).absoluteFilePath();
        QString absolute = d.path();

        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("File Does not exist.");
        msgBox.setInformativeText(absolute);//ui->lineEditPathAab->text());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        msgBox.exec();
        return;
    }

    qDebug() << __FUNCTION__ << " / file exist.";


    if(mAdbMgr == nullptr)
        mAdbMgr = AdbManager::GetInstance();

    QString pathAab(ui->lineEditPathApk->text());
}

void MainWindow::actionPreferences()
{
    PreferencesDialog *prefDlg = new PreferencesDialog(this);

    prefDlg->exec();
}

void MainWindow::actionAbout()
{
    AboutDialog* aboutDlg = new AboutDialog(this);

    aboutDlg->exec();
}


void MainWindow::menuExit()
{
    QMainWindow::close();
}


/* private */
void MainWindow::initialization()
{
    mAdbMgr = AdbManager::GetInstance();
    mDeviceMgr = DeviceManager::GetInstance();
    mIoThread = new IOThread();
    mThemeMgr = new ThemeManager(this);
    //mUpdateMgr = new UpdateManager(this);
    makeConnectionIoThread();
    //mLogParserThread = new LogParserThread();
    mFilterMgr = new FilterManager(this);
    mFilterMgr->initFilter();

    mTabAll = ui->tabAll;
    mTabXSign = ui->tabXSign;


    /* check all log level*/
    ui->checkBoxV->setChecked(true);
    ui->checkBoxD->setChecked(true);
    ui->checkBoxI->setChecked(true);
    ui->checkBoxW->setChecked(true);
    ui->checkBoxE->setChecked(true);
    ui->checkBoxF->setChecked(true);
    mStatusMonitor->GetInstance()->setLogLevel(LOG_LEVEL::VERBOSE|LOG_LEVEL::DEBUG|LOG_LEVEL::INFO
                                               |LOG_LEVEL::WARN|LOG_LEVEL::ERROR_LOG|LOG_LEVEL::FATAL);

    /* check all show column */
    ui->checkBoxDate->setChecked(true);
    ui->checkBoxTime->setChecked(true);
    ui->checkBoxLogLevel->setChecked(true);
    ui->checkBoxPid->setChecked(true);
    ui->checkBoxThread->setChecked(true);
    mStatusMonitor->GetInstance()->setShowColumn(SHOW_COLUMN::COL_DATE|SHOW_COLUMN::COL_TIME|SHOW_COLUMN::COL_LEVEL
                                                 |SHOW_COLUMN::COL_PID|SHOW_COLUMN::COL_TID|SHOW_COLUMN::COL_TAG
                                                 |SHOW_COLUMN::COL_MESSAGE);

    /* packages setting */
    mStatusMonitor->GetInstance()->setPackagesChecked(false);
    mStatusMonitor->GetInstance()->setCheckedPackageName(QString());

    //qDebug() << __FUNCTION__ << " / current log level:" << mStatusMonitor->GetInstance()->getLogLevel();
    //qDebug() << __FUNCTION__ << " / current show column level:" << mStatusMonitor->GetInstance()->getShowColumn();
}

void MainWindow::makeConnection()
{
    connect(ui->listWidgetDevice, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(changeDeviceSelection()));
    connect(ui->btnRun, SIGNAL(clicked()), this, SLOT(clickedRunButton()));
    connect(ui->btnStop, SIGNAL(clicked()), this, SLOT(clickedStopButton()));
    connect(ui->btnPause, SIGNAL(clicked()), this, SLOT(clickedStopButton()));
    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(clickedClearButton()));
    connect(ui->btnScroll, SIGNAL(clicked()), this, SLOT(clickedScrollButton()));
    connect(ui->actionUserGuide, SIGNAL(triggered()), this, SLOT(clickedUserGuide()));
    connect(ui->btnRefreshDeviceList, SIGNAL(clicked()), this, SLOT(clidkedRefreshDeviceList()));

    /* menu */
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(menuExit()));
    connect(ui->actionPreferences, SIGNAL(triggered()), this, SLOT(actionPreferences()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(actionAbout()));

    /* theme change */
    connect(ui->actionThemeDefault, SIGNAL(triggered()), this, SLOT(themeChangeToDefault()));
    connect(ui->actionThemeAdaptic, SIGNAL(triggered()), this, SLOT(themeChangeToAdaptic()));
    connect(ui->actionThemeCombinear, SIGNAL(triggered()), this, SLOT(themeChangeToCombinear()));
    connect(ui->actionThemeDarkeum, SIGNAL(triggered()), this, SLOT(themeChangeToDarkeum()));
    connect(ui->actionThemeDiffnes, SIGNAL(triggered()), this, SLOT(themeChangeToDiffnes()));
    connect(ui->actionThemeFibers, SIGNAL(triggered()), this, SLOT(themeChangeToFibers()));
    connect(ui->actionThemeIntegrid, SIGNAL(triggered()), this, SLOT(themeChangeToIntegrid()));
    connect(ui->actionThemeIrrorater, SIGNAL(triggered()), this, SLOT(themeChangeToIrrorater()));

    /* log-level change */
    connect(ui->checkBoxV, SIGNAL(stateChanged(int)), this, SLOT(logLevelChangedSlot()));
    connect(ui->checkBoxD, SIGNAL(stateChanged(int)), this, SLOT(logLevelChangedSlot()));
    connect(ui->checkBoxI, SIGNAL(stateChanged(int)), this, SLOT(logLevelChangedSlot()));
    connect(ui->checkBoxW, SIGNAL(stateChanged(int)), this, SLOT(logLevelChangedSlot()));
    connect(ui->checkBoxE, SIGNAL(stateChanged(int)), this, SLOT(logLevelChangedSlot()));
    connect(ui->checkBoxF, SIGNAL(stateChanged(int)), this, SLOT(logLevelChangedSlot()));

    /* show column change */
    connect(ui->checkBoxDate, SIGNAL(stateChanged(int)), this, SLOT(showColumnChangeSlot()));
    connect(ui->checkBoxTime, SIGNAL(stateChanged(int)), this, SLOT(showColumnChangeSlot()));
    connect(ui->checkBoxLogLevel, SIGNAL(stateChanged(int)), this, SLOT(showColumnChangeSlot()));
    connect(ui->checkBoxPid, SIGNAL(stateChanged(int)), this, SLOT(showColumnChangeSlot()));
    connect(ui->checkBoxThread, SIGNAL(stateChanged(int)), this, SLOT(showColumnChangeSlot()));

    /* packages checked */
    connect(ui->checkBoxPackageName, SIGNAL(stateChanged(int)), this, SLOT(packagesCheckedSlot(int)));
    connect(ui->cbPackageList, SIGNAL(currentIndexChanged(const QString)), this, SLOT(checkedPackageNameChangedSlot(const QString)));

    //connect(mIoWorker, SIGNAL(&IOWorker::start), mIoWorker, SLOT(&IOWoerker::doWork));

    /* status control */
    connect(this, SIGNAL(changeStatusSig(OP_STATUS)), this, SLOT(changeStatusSlot(OP_STATUS)));

    /* table view */
    connect(ui->tvAll->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(tvSelectionItemChanged(const QItemSelection &, const QItemSelection)));

    /* query installed packages */
    connect(this, SIGNAL(queryDevicePackageListSig()), this, SLOT(queryDevicePackageListSlot()));

    /* filter */
    connect(mFilterMgr, SIGNAL(updateFilterSig()), mProxyModel, SLOT(updateFilterSlot())); // update
    connect(ui->checkBoxFilterPid, SIGNAL(stateChanged(int)), mFilterMgr, SLOT(pidFilterChangedSlot(int)));
    connect(ui->lineEditPid, SIGNAL(textChanged(QString)), mFilterMgr, SLOT(pidTextChangedSlot(QString)));
    connect(ui->checkBoxTid, SIGNAL(stateChanged(int)), mFilterMgr, SLOT(tidFilterChangedSlot(int)));
    connect(ui->lineEditTid, SIGNAL(textChanged(QString)), mFilterMgr, SLOT(tidTextChangedSlot(QString)));
    connect(ui->checkBoxTag, SIGNAL(stateChanged(int)), mFilterMgr, SLOT(tagFilterChangedSlot(int)));
    connect(ui->lineEditTag, SIGNAL(textChanged(QString)), mFilterMgr, SLOT(tagTextChangedSlot(QString)));
    connect(ui->checkBoxMsgShow, SIGNAL(stateChanged(int)), mFilterMgr, SLOT(msgShowFilterChangedSlot(int)));
    connect(ui->lineEditMsgShow, SIGNAL(textChanged(QString)), mFilterMgr, SLOT(msgShowTextChangedSlot(QString)));
    connect(ui->checkBoxMsgHide, SIGNAL(stateChanged(int)), mFilterMgr, SLOT(msgHideFilterChangedSlot(int)));
    connect(ui->lineEditMsgHide, SIGNAL(textChanged(QString)), mFilterMgr, SLOT(msgHideTextChangedSlot(QString)));

    /* update proxy model */
    //connect(ui->lineEditPid, SIGNAL(textChanged(QString)), mProxyModel, SLOT(pidTextChangedSlot(QString)));
    //connect(ui->lineEditTid, SIGNAL(textChanged(QString)), mProxyModel, SLOT(tidTextChangedSlot(QString)));

    /* tool */
    connect(ui->btnSelectApk, SIGNAL(clicked()), this, SLOT(clickedSelectInstallApkButton()));
    connect(ui->btnInstallApk, SIGNAL(clicked()), this, SLOT(clickedInstallApkButton()));
    connect(ui->btnSelectAab2Apk, SIGNAL(clicked()), this, SLOT(clickedSelectAab2ApkButton()));
    connect(ui->btnConvertAab, SIGNAL(clicked()), this, SLOT(clickedConvertAab2ApkButton()));
}

void MainWindow::makeConnectionIoThread()
{
    qInfo() << __FUNCTION__;

    disconnect(mIoThread, SIGNAL(finished()), mIoThread, SLOT(deleteLater()));
    disconnect(mIoThread, SIGNAL(updateModelDataSig(QString)), this, SLOT(receivedLogData(QString)));

    connect(mIoThread, SIGNAL(finished()), mIoThread, SLOT(deleteLater()));
    connect(mIoThread, SIGNAL(updateModelDataSig(QString)), this, SLOT(receivedLogData(QString)));
}

void MainWindow::makeThreadConnection()
{
    disconnect(mIoThread, SIGNAL(finished()), mIoThread, SLOT(deleteLater()));
    connect(mIoThread, SIGNAL(finished()), mIoThread, SLOT(deleteLater()));
}

void MainWindow::updateDeviceList()
{
    QList<QString> strDevList;

    if(mAdbMgr != nullptr)
    {
        strDevList = mAdbMgr->queryAttachedDeviceList();
        mDeviceMgr->setDeviceNameList(strDevList);
    }

    ui->listWidgetDevice->clear();
    foreach(QString strItem, strDevList)
    {
        ui->listWidgetDevice->addItem(strItem);
    }
}

QString MainWindow::makeLogFileName()
{
    QString fileName = QDateTime::currentDateTime().toString("yyyyMMdd-HHmmss");
    fileName += ".txt";
    return fileName;
}

void MainWindow::initTable()
{
    qInfo() << __FUNCTION__;

    // view / model
    mTableView = ui->tvAll;
    model = new QStandardItemModel(mTabAll);

    /* proxymodel */
    mProxyModel = new LogProxyModel(mFilterMgr, this);
    mProxyModel->setSourceModel(model);

    model->setHorizontalHeaderLabels(QStringList() << "Date" << "Time" <<"Level" << "PID" << "TID" << "Tag" << "Message");

    /* proxymodel */
    //mTableView->setModel(model);
    mTableView->setModel(mProxyModel);


    mTableView->horizontalHeader()->show();
    mTableView->horizontalHeader()->setStretchLastSection(true);

    QHeaderView *verticalHeader = mTableView->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(22);

    /* column width */
    mTableView->setColumnWidth(DSADB_TOOL::COLUMN_LOG::DATE_LOG,    50);    /* date */
    mTableView->setColumnWidth(DSADB_TOOL::COLUMN_LOG::TIME,    100);   /* time */
    mTableView->setColumnWidth(DSADB_TOOL::COLUMN_LOG::LEVEL,   40);
    mTableView->setColumnWidth(DSADB_TOOL::COLUMN_LOG::PID,     60);
    mTableView->setColumnWidth(DSADB_TOOL::COLUMN_LOG::TID,     60);
    mTableView->setColumnWidth(DSADB_TOOL::COLUMN_LOG::TAG,     180);

    // table option.
    mTableView->setWordWrap(true);
    mTableView->setTextElideMode(Qt::ElideMiddle);
    mTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    mTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //mTableView->verticalHeader()->setFixedHeight(25);
    mTableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    mTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    mTableView->horizontalHeader()->setStretchLastSection(true);

    mTableView->show();
    mTableView->scrollToBottom();

    //mUpdateMgr = new UpdateManager(mTableView, model);

    /* MagicXSign Log */
    mMagicXSignTableView = ui->tvXSignLog;
    mMagicXSignModel = new QStandardItemModel(mTabXSign);

    mMagicXSignModel->setHorizontalHeaderLabels(QStringList() << "Date" << "Time" <<"Level" << "PID" << "TID" << "Tag" << "Message");

    mMagicXSignTableView->setModel(mMagicXSignModel);

    mMagicXSignTableView->horizontalHeader()->show();
    mMagicXSignTableView->horizontalHeader()->setStretchLastSection(true);

    QHeaderView *xsignTableVerticalHeader = mMagicXSignTableView->verticalHeader();
    xsignTableVerticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    xsignTableVerticalHeader->setDefaultSectionSize(22);

    /* column width */
    mMagicXSignTableView->setColumnWidth(COLUMN_LOG::DATE_LOG,    50);    /* date */
    mMagicXSignTableView->setColumnWidth(COLUMN_LOG::TIME,    100);   /* time */
    mMagicXSignTableView->setColumnWidth(COLUMN_LOG::LEVEL,   40);
    mMagicXSignTableView->setColumnWidth(COLUMN_LOG::PID,     60);
    mMagicXSignTableView->setColumnWidth(COLUMN_LOG::TID,     60);
    mMagicXSignTableView->setColumnWidth(COLUMN_LOG::TAG,     180);

    // table option.
    mMagicXSignTableView->setWordWrap(true);
    mMagicXSignTableView->setTextElideMode(Qt::ElideMiddle);
    mMagicXSignTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    mMagicXSignTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    mMagicXSignTableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    mMagicXSignTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    mMagicXSignTableView->horizontalHeader()->setStretchLastSection(true);

    mMagicXSignTableView->show();
    mMagicXSignTableView->scrollToBottom();

    mUpdateMgr = new UpdateManager(mTableView, mMagicXSignTableView, model, mMagicXSignModel);
}

void MainWindow::prepare()
{
    emit changeStatusSig(OP_STATUS::STATUS_STOP);
}

void MainWindow::updateColumnDisplay()
{
    int ShowColumn = mStatusMonitor->GetInstance()->getShowColumn();

    if(ShowColumn & SHOW_COLUMN::COL_DATE)
    {
        mTableView->setColumnHidden(COLUMN_LOG::DATE_LOG, false);
    }
    else
    {
        mTableView->setColumnHidden(COLUMN_LOG::DATE_LOG, true);
    }

    if(ShowColumn & SHOW_COLUMN::COL_TIME)
    {
        mTableView->setColumnHidden(COLUMN_LOG::TIME, false);
    }
    else
    {
        mTableView->setColumnHidden(COLUMN_LOG::TIME, true);
    }

    if(ShowColumn & SHOW_COLUMN::COL_LEVEL)
    {
        mTableView->setColumnHidden(COLUMN_LOG::LEVEL, false);
    }
    else
    {
        mTableView->setColumnHidden(COLUMN_LOG::LEVEL, true);
    }

    if(ShowColumn & SHOW_COLUMN::COL_PID)
    {
        mTableView->setColumnHidden(COLUMN_LOG::PID, false);
    }
    else
    {
        mTableView->setColumnHidden(COLUMN_LOG::PID, true);
    }

    if(ShowColumn & SHOW_COLUMN::COL_TID)
    {
        mTableView->setColumnHidden(COLUMN_LOG::TID, false);
    }
    else
    {
        mTableView->setColumnHidden(COLUMN_LOG::TID, true);
    }

    /*
    if(ShowColumn & SHOW_COLUMN::COL_TAG)
    {
        mTableView->setColumnHidden(COLUMN_LOG::TAG, false);
    }
    else
    {
        mTableView->setColumnHidden(COLUMN_LOG::TAG, true);
    }
    */
}

void MainWindow::uiSleep(int ms)
{
    Q_ASSERT(ms > 0);

#ifdef Q_OS_WIN
    Sleep(uint(ms));
#else // Linux
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#endif
}

/*void MainWindow::runAdb()
{
}*/
