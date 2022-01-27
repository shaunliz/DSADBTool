#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <Qt>
#include <QObject>
#include <QDebug>
#include <QTableView>
#include <QTableWidget>
#include <QStandardItemModel>

#include "logparser.h"
#include "statusmonitor.h"
#include "const.h"

using namespace DSADB_TOOL;

class UpdateManager : public QObject
{
    Q_OBJECT
public:
    explicit UpdateManager(QObject *parent = nullptr);
    explicit UpdateManager(QTableView* tv, QStandardItemModel* model, QObject *parent = nullptr);
    explicit UpdateManager(QTableView* tv, QTableView* tvXSign, QStandardItemModel* model, QStandardItemModel* modelXSign, QObject *parent = nullptr);

    void updateLogData(QString strData);
    void updateFilteredModel(int prevLogLevel, int logLevel);
    void setTheme(THEME_TYPE value);

signals:

private:

    bool checkMagicXSignLog(QString logLevel, QString tagString);
    bool checkHideLogLevel(QString loglevel);

    //QTableWidget *mtw;
    QTableView *mtv;
    QTableView *mXSignTv;
    QStandardItemModel *mModel;
    QStandardItemModel *mXSignModel;

    QString strLogData;
    THEME_TYPE mThemeType;
};

#endif // UPDATEMANAGER_H
