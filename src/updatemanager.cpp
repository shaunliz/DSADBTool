#include "updatemanager.h"

UpdateManager::UpdateManager(QObject *parent) : QObject(parent)
{
    mThemeType = THEME_TYPE::DEFAULT;
}

UpdateManager::UpdateManager(QTableView* tv, QStandardItemModel* model, QObject *parent)
{
    mtv = tv;
    mModel = model;
    mThemeType = THEME_TYPE::DEFAULT;
}

UpdateManager::UpdateManager(QTableView* tv, QTableView* tvXSign, QStandardItemModel* model, QStandardItemModel* modelXSign, QObject *parent)
{
    mtv = tv;
    mXSignTv = tvXSign;
    mModel = model;
    mXSignModel = modelXSign;
    mThemeType = THEME_TYPE::DEFAULT;
}

void UpdateManager::updateLogData(QString strLogData)
{
    QStringList strLogList = strLogData.split("\r\n");
    //LogParser* logparser = new LogParser(this);
    LogParser* logparser = new LogParser(mThemeType, this);
    QBrush logBrush;
    QColor logColor;

    foreach(QString str, strLogList)
    {
        QStandardItem *item;
        QStandardItem *itemXSign;
        QList<QStandardItem*> itemList;
        QList<QStandardItem*> itemXSignList;
        QString levelItem, tagItem;

        if(str.isEmpty() || str == "")
            continue;

        logparser->setLogString(str);

        logColor = logparser->getLogColor();            /*QColor(Qt::red);*/
        logBrush.setColor(logColor);

        item = new QStandardItem(logparser->getDate());
        item->setForeground(logBrush);
        item->setTextAlignment(Qt::AlignCenter);
        itemList.append(item);

        item = new QStandardItem(logparser->getTime());
        item->setForeground(logBrush);
        item->setTextAlignment(Qt::AlignCenter);
        itemList.append(item);

        item = new QStandardItem(logparser->getLevel());
        item->setForeground(logBrush);
        item->setTextAlignment(Qt::AlignCenter);
        levelItem  = item->text();
        itemList.append(item);

        item = new QStandardItem(logparser->getPid());
        item->setForeground(logBrush);
        itemList.append(item);

        item = new QStandardItem(logparser->getTid());
        item->setForeground(logBrush);
        itemList.append(item);

        item = new QStandardItem(logparser->getTag());
        item->setForeground(logBrush);
        tagItem = item->text();
        itemList.append(item);

        item = new QStandardItem(logparser->getMessage());
        item->setForeground(logBrush);
        itemList.append(item);

        mModel->appendRow(itemList);

        /* MagicXSign Log */
        if(tagItem.contains("MagicXSign") == true || tagItem.contains("MagicSE") == true)
        {
            itemXSign = new QStandardItem(logparser->getDate());
            itemXSign->setForeground(logBrush);
            itemXSign->setTextAlignment(Qt::AlignCenter);
            itemXSignList.append(itemXSign);

            itemXSign = new QStandardItem(logparser->getTime());
            itemXSign->setForeground(logBrush);
            itemXSign->setTextAlignment(Qt::AlignCenter);
            itemXSignList.append(itemXSign);

            itemXSign = new QStandardItem(logparser->getLevel());
            itemXSign->setForeground(logBrush);
            itemXSign->setTextAlignment(Qt::AlignCenter);
            itemXSignList.append(itemXSign);

            itemXSign = new QStandardItem(logparser->getPid());
            itemXSign->setForeground(logBrush);
            itemXSignList.append(itemXSign);

            itemXSign = new QStandardItem(logparser->getTid());
            itemXSign->setForeground(logBrush);
            itemXSignList.append(itemXSign);

            itemXSign = new QStandardItem(logparser->getTag());
            itemXSign->setForeground(logBrush);
            itemXSignList.append(itemXSign);

            itemXSign = new QStandardItem(logparser->getMessage());
            itemXSign->setForeground(logBrush);
            itemXSignList.append(itemXSign);

            mXSignModel->appendRow(itemXSignList);
        }

#if 0
        if(checkMagicXSignLog(levelItem, tagItem) == true)
        {
            ;
            //mtv->hideRow(mModel->rowCount()-1);
            //mXSignModel->appendRow(itemList);
        }
        else if(checkHideLogLevel(levelItem) == true)
        {
            qDebug() << __FUNCTION__ << " / hide row";
            mtv->hideRow(mModel->rowCount()-1);
        }
#endif
    }


    if(StatusMonitor::GetInstance()->getScrollStatus())
    {
        mtv->scrollToBottom();
        mXSignTv->scrollToBottom();
    }
}


/* private */
bool UpdateManager::checkMagicXSignLog(QString logLevel, QString tagString)
{
    if(tagString.contains("MagicXSign"))
    {
        return true;
    }

    return false;
}

bool UpdateManager::checkHideLogLevel(QString loglevel)
{
    int ShowLogLevel = StatusMonitor::GetInstance()->getLogLevel();

    /* hide 'verbose' log */
    if(!(LOG_LEVEL::VERBOSE & ShowLogLevel) && (loglevel.compare("V", Qt::CaseInsensitive) == 0))
    {
        return true;
    }

    /* hide 'debug' log */
    if(!(LOG_LEVEL::DEBUG & ShowLogLevel) && (loglevel.compare("D", Qt::CaseInsensitive) == 0))
    {
        return true;
    }

    /* hide 'info' log */
    if(!(LOG_LEVEL::INFO & ShowLogLevel) && (loglevel.compare("I", Qt::CaseInsensitive) == 0))
    {
        return true;
    }

    /* hide 'warn' log */
    if(!(LOG_LEVEL::WARN & ShowLogLevel) && (loglevel.compare("W", Qt::CaseInsensitive) == 0))
    {
        return true;
    }

    /* hide 'error' log */
    if(!(LOG_LEVEL::ERROR_LOG & ShowLogLevel) && (loglevel.compare("E", Qt::CaseInsensitive) == 0))
    {
        return true;
    }

    /* hide 'fatal' log */
    if(!(LOG_LEVEL::FATAL & ShowLogLevel) && (loglevel.compare("F", Qt::CaseInsensitive) == 0))
    {
        return true;
    }

    return false;
}

void UpdateManager::updateFilteredModel(int prevLogLevel, int logLevel)
{
    /* verbose */
    int prevVLog = prevLogLevel & LOG_LEVEL::VERBOSE;
    int vLog = logLevel & LOG_LEVEL::VERBOSE;
    bool bUpdateVLog = false;
    if(prevVLog != vLog)
    {
        qDebug() << "V Log state changed. / vLog:" << vLog;
        bUpdateVLog = true;
    }

    /* debug */
    int prevDLog = prevLogLevel & LOG_LEVEL::DEBUG;
    int dLog = logLevel & LOG_LEVEL::DEBUG;
    bool bUpdateDLog = false;
    if(prevDLog != dLog)
    {
        qDebug() << "D Log state changed. / dLog:" << dLog;
        bUpdateDLog = true;
    }

    /* info */
    int prevILog = prevLogLevel & LOG_LEVEL::INFO;
    int iLog = logLevel & LOG_LEVEL::INFO;
    bool bUpdateILog = false;
    if(prevILog != iLog)
    {
        qDebug() << "I Log state changed. / iLog:" << iLog;
        bUpdateILog = true;
    }

    /* warn */
    int prevWLog = prevLogLevel & LOG_LEVEL::WARN;
    int wLog = logLevel & LOG_LEVEL::WARN;
    bool bUpdateWLog = false;
    if(prevWLog != wLog)
    {
        qDebug() << "W Log state changed. / wLog:" << wLog;
        bUpdateWLog = true;
    }

    /* error */
    int prevELog = prevLogLevel & LOG_LEVEL::ERROR_LOG;
    int eLog = logLevel & LOG_LEVEL::ERROR_LOG;
    bool bUpdateELog = false;
    if(prevELog != eLog)
    {
        qDebug() << "E Log state changed. / eLog:" << eLog;
        bUpdateELog = true;
    }

    /* fatal */
    int prevFLog = prevLogLevel & LOG_LEVEL::FATAL;
    int fLog = logLevel & LOG_LEVEL::FATAL;
    bool bUpdateFLog = false;
    if(prevFLog != fLog)
    {
        qDebug() << "F Log state changed. / fLog:" << fLog;
        bUpdateFLog = true;
    }

    qDebug() << __FUNCTION__ << " / table row count:" << mModel->rowCount();

    int rowCnt = mModel->rowCount();
    for(int nRow = 0; nRow < rowCnt; nRow++)
    {
        QStandardItem* item = new QStandardItem();
        item = mModel->item(nRow, COLUMN_LOG::LEVEL);

        /* show or hide verbose */
        if(bUpdateVLog && item->text().compare("V", Qt::CaseInsensitive) == 0)
        {
            if(vLog > 0) // show
            {
                mtv->showRow(nRow);
            }
            else        // hide
            {
                mtv->hideRow(nRow);
            }
        }

        /* show or hide debug */
        if(bUpdateDLog && item->text().compare("D", Qt::CaseInsensitive) == 0)
        {
            if(dLog > 0) // show
            {
                mtv->showRow(nRow);
            }
            else        // hide
            {
                mtv->hideRow(nRow);
            }
        }

        /* show or hide info */
        if(bUpdateILog && item->text().compare("I", Qt::CaseInsensitive) == 0)
        {
            if(iLog > 0) // show
            {
                mtv->showRow(nRow);
            }
            else        // hide
            {
                mtv->hideRow(nRow);
            }
        }

        /* show or hide warn */
        if(bUpdateWLog && item->text().compare("W", Qt::CaseInsensitive) == 0)
        {
            if(wLog > 0) // show
            {
                mtv->showRow(nRow);
            }
            else        // hide
            {
                mtv->hideRow(nRow);
            }
        }

        /* show or hide error */
        if(bUpdateELog && item->text().compare("E", Qt::CaseInsensitive) == 0)
        {
            if(eLog > 0) // show
            {
                mtv->showRow(nRow);
            }
            else        // hide
            {
                mtv->hideRow(nRow);
            }
        }

        /* show or hide fatal */
        if(bUpdateFLog && item->text().compare("F", Qt::CaseInsensitive) == 0)
        {
            if(fLog > 0) // show
            {
                mtv->showRow(nRow);
            }
            else        // hide
            {
                mtv->hideRow(nRow);
            }
        }
    }
}

void UpdateManager::setTheme(THEME_TYPE value)
{
    mThemeType = value;
}

