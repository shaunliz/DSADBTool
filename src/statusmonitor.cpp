#include "statusmonitor.h"

StatusMonitor* StatusMonitor::instance;

StatusMonitor::StatusMonitor(QObject *parent) : QObject(parent)
{
    mStatus = OP_STATUS::STATUS_STOP;
}

StatusMonitor* StatusMonitor::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new StatusMonitor();
    }

    return instance;
}

void StatusMonitor::setCurrentOpStatus(OP_STATUS status)
{
    mStatus = status;
}

OP_STATUS StatusMonitor::getCurrentOpStatus()
{
    return mStatus;
}

void StatusMonitor::setScrollStatus(bool status)
{
    mScroll = status;
}

bool StatusMonitor::getScrollStatus()
{
    return mScroll;
}

void StatusMonitor::setLogLevel(int level)
{
    mLogLevel = level;
}

int StatusMonitor::getLogLevel()
{
    return mLogLevel;
}

void StatusMonitor::setShowColumn(int show_column)
{
    mShowColumn = show_column;
}

int StatusMonitor::getShowColumn()
{
    return mShowColumn;
}

void StatusMonitor::setCurrentTheme(int themeId)
{
    qDebug() << __FUNCTION__ << " / themeId:" << themeId;
    mThemeName = themeId;
}

int StatusMonitor::getCurrentTheme()
{
    return mThemeName;
}

void StatusMonitor::setPackagesChecked(bool value)
{
    mPackagesChecked = value;
}

bool StatusMonitor::getPackagesChecked()
{
    return mPackagesChecked;
}

void StatusMonitor::setCheckedPackageName(QString packageName)
{
    mCheckedPackageName = packageName;
}

QString StatusMonitor::getCheckedPackageName()
{
    return mCheckedPackageName;
}
