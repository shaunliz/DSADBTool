#include "adbmanager.h"

AdbManager* AdbManager::instance = nullptr;

AdbManager::AdbManager(QObject *parent) : QObject(parent)
{

    //connect(this, SIGNAL(showProgressSig(QProgressDialog*)), this, SLOT(showProgressSlot(QProgressDialog*)));
}

/* public */
AdbManager* AdbManager::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new AdbManager();
    }
    return instance;
}

QList<QString> AdbManager::queryAttachedDeviceList()
{
    QProcess process;
    QString strOut;
    QByteArray strArray;
    QList<QString> strDeviceList;
    QList<QString> retDeviceList;
    QString cmd = "";

    if(IniManager::GetInstance()->getUseAdbPath())
        cmd = IniManager::GetInstance()->getAdbPath();
    else
        cmd = ADB_CMD::ADB;

    cmd += ADB_CMD::DEVICES;

    process.start(cmd);
    process.waitForFinished(-1);

    strArray = process.readAllStandardOutput();

    //qDebug() << __FUNCTION__ << " - strArray:" << strArray;

    strOut = QString::fromStdString(strArray.toStdString());

    strOut.replace("\t", ";");
    strOut.replace("\r", ";");
    strOut.replace("\n", ";");

    strDeviceList = strOut.split(";");

    foreach(QString strItem, strDeviceList)
    {
        if(!strItem.isEmpty()
            && strItem.compare("device", Qt::CaseInsensitive) != 0
            && strItem.compare("unauthorized", Qt::CaseInsensitive) != 0
            && strItem.compare("List of devices attached", Qt::CaseInsensitive) != 0)
        {
            retDeviceList.append(strItem);
        }
    }

    //qDebug() << __FUNCTION__ << " / retDeviceList:" << retDeviceList;

    return retDeviceList;
}

QList<QString> AdbManager::queryInstalledPackageList(QString selectedDeviceName)
{
    QProcess process;
    QString strOut;
    QByteArray strArray;
    QString cmd = "";
    QList<QString> retPackagesList;

    if(IniManager::GetInstance()->getUseAdbPath())
        cmd = IniManager::GetInstance()->getAdbPath();
    else
        cmd = ADB_CMD::ADB;

    if(selectedDeviceName.compare("", Qt::CaseInsensitive) == 0
       || selectedDeviceName.compare(" ", Qt::CaseInsensitive) == 0
       || selectedDeviceName.isEmpty())
    {
        cmd += ADB_CMD::PACKAGE_LIST;
    }
    else
    {
        cmd += ADB_CMD::SELECT_DEVICE + selectedDeviceName + " " + ADB_CMD::PACKAGE_LIST;
    }

    qDebug() << __FUNCTION__ << " / cmd:" << cmd;

    process.start(cmd);
    process.waitForFinished(-1);

	/*if(!process.waitForFinished(3000))
        return retPackagesList;*/

    strArray = process.readAllStandardOutput();
    strOut = QString::fromStdString(strArray.toStdString());

    //qDebug() << __FUNCTION__ << " / strOut:" << strOut;

    /*QList<QString> resultList = strOut.split("\r\n");*/
    QList<QString> resultList = strOut.split("package:");

    //qDebug() << "\n\nresultList:" << resultList;

    foreach(QString item, resultList)
    {
        if(!item.isEmpty() && item.compare("", Qt::CaseInsensitive) != 0)
        {
            int endIdx = item.indexOf("\r\n");
            int beginIdx = item.lastIndexOf("=");
            QString packageName = item.right(endIdx - beginIdx + 1);

            if(!packageName.isEmpty())
            {
                packageName.remove("\r\n");
                retPackagesList.append(packageName);
            }
        }
    }

    //qDebug() << retPackagesList;

    return retPackagesList;
}

void AdbManager::clearLogData(QString deviceName)
{
    QProcess process;
    QString cmd;

    if(IniManager::GetInstance()->getUseAdbPath())
            cmd = IniManager::GetInstance()->getAdbPath();
        else
            cmd = ADB_CMD::ADB;

    if(!deviceName.isEmpty() || deviceName != NULL)
    {
        cmd += ADB_CMD::SELECT_DEVICE; /* "adb -s " */
        cmd += deviceName;
    }

    cmd += ADB_CMD::LOG_CLEAR;

    process.start(cmd);
    process.waitForFinished(-1);
}

void AdbManager::installApkFile(QString deviceName, QString pathApk)
{
    QProcess process;
    QString cmd;

//    QProgressDialog progress;
//    progress.setWindowModality(Qt::WindowModal);
//    progress.setMinimum(0);
//    progress.setMaximum(0);
//    progress.setLabelText("Install : " + pathApk);
//    progress.setValue(0);
//    progress.show();



    if(IniManager::GetInstance()->getUseAdbPath())
            cmd = IniManager::GetInstance()->getAdbPath();
        else
            cmd = ADB_CMD::ADB;

    if(!deviceName.isEmpty() || deviceName != NULL)
    {
        cmd += ADB_CMD::SELECT_DEVICE; /* "adb -s " */
        cmd += deviceName;
    }

    cmd += ADB_CMD::INSTALL_APK;
    cmd += pathApk;

    qDebug() << __FUNCTION__ << "/ cmd:" << cmd << " / pathApk:" << pathApk;

//    mProgressDlg = new QProgressDialog();
//    connect(this, SIGNAL(showProgressSig(QProgressDialog*)), this, SLOT(showProgressSlot(QProgressDialog*)));
//    emit showProgressSig(mProgressDlg);

    process.start(cmd);
    process.waitForFinished(-1);


//    mProgressDlg->cancel();
    disconnect(this, SIGNAL(showProgressSig(QProgressDialog*)), this, SLOT(showProgressSlot(QProgressDialog*)));

    QByteArray strArray = process.readAllStandardOutput();
    QString strOut = QString::fromStdString(strArray.toStdString());

    qDebug() << __FUNCTION__ << " / result:" << strOut;

    QString msgText = "";
    if(strOut.contains("success", Qt::CaseInsensitive))
    {
        msgText = "Completed.";
    }
    else
    {
        msgText = "Fail to Installation.";
    }

    QMessageBox msgBox;
    // QString _path = ui->lineEditPathApk->text();
    // QDir d = QFileInfo(_path).absoluteFilePath();
    // QString absolute = d.path();

    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(msgText);
    //msgBox.setInformativeText(absolute);//ui->lineEditPathApk->text());
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    msgBox.exec();
    return;
}

/* slots */
void AdbManager::showProgressSlot(QProgressDialog* progressDlg)
{
    qDebug() << __FUNCTION__ ;

    progressDlg->setWindowModality(Qt::WindowModal);
    progressDlg->setMinimum(0);
    progressDlg->setMaximum(0);
    progressDlg->setLabelText("Install : ");
    progressDlg->setValue(0);
    progressDlg->show();
}

/* private */
