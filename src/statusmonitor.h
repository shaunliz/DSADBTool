#ifndef STATUSMONITOR_H
#define STATUSMONITOR_H

#include <QObject>
#include <QDebug>

#include "const.h"

using namespace DSADB_TOOL;

class StatusMonitor : public QObject
{
    Q_OBJECT
public:
    static StatusMonitor* GetInstance();

    void setCurrentOpStatus(OP_STATUS status);
    OP_STATUS getCurrentOpStatus();
    void setScrollStatus(bool status);
    bool getScrollStatus();
    void setLogLevel(int level);
    int getLogLevel();
    void setShowColumn(int show_column);
    int getShowColumn();
    void setCurrentTheme(int themeId);
    int getCurrentTheme();
    void setPackagesChecked(bool value);
    bool getPackagesChecked();
    void setCheckedPackageName(QString packageName);
    QString getCheckedPackageName();

signals:

private:
    explicit StatusMonitor(QObject *parent = nullptr);
    static StatusMonitor* instance;

    OP_STATUS mStatus;
    bool mScroll;
    int mLogLevel;
    int mShowColumn;
    int mThemeName;
    bool mPackagesChecked;
    QString mCheckedPackageName;

public slots:
};

#endif // STATUSMONITOR_H
