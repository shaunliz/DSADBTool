#include "logproxymodel.h"

LogProxyModel::LogProxyModel(QObject* parent)
{

}

LogProxyModel::LogProxyModel(FilterManager* filterMgr, QObject* parent)
{
    mFilterMgr = filterMgr;
}

bool LogProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool bRet = true;

    QModelIndex modelLevelIndex = sourceModel()->index(source_row, COLUMN_LOG::LEVEL, source_parent);
    QModelIndex modelPidIndex = sourceModel()->index(source_row, COLUMN_LOG::PID, source_parent);
    QModelIndex modelTidIndex = sourceModel()->index(source_row, COLUMN_LOG::TID, source_parent);
    QModelIndex modelTagIndex = sourceModel()->index(source_row, COLUMN_LOG::TAG, source_parent);
    QModelIndex modelMsgIndex = sourceModel()->index(source_row, COLUMN_LOG::MESSAGE, source_parent);

    //qDebug() << __FUNCTION__ << " / source_row:" << source_row << " : " << sourceModel()->data(modelMsgIndex).toString();
    //qDebug() << __FUNCTION__ << " / v:" << mFilterMgr->getShowV() << " / d:" << mFilterMgr->getShowD();

    if(mFilterMgr != nullptr)// && mFilterMgr->getUsePid())
    {
        /* log level */
        if(bRet == true && !mFilterMgr->getShowV())
        {
            if(sourceModel()->data(modelLevelIndex).toString().contains("V"))
                bRet = false;
            else
                bRet = true;
        }
        if(bRet == true && !mFilterMgr->getShowD())
        {
            if(sourceModel()->data(modelLevelIndex).toString().contains("D"))
                bRet = false;
            else
                bRet = true;
        }
        if(bRet == true && !mFilterMgr->getShowI())
        {
            if(sourceModel()->data(modelLevelIndex).toString().contains("I"))
                bRet = false;
            else
                bRet = true;
        }
        if(bRet == true && !mFilterMgr->getShowW())
        {
            if(sourceModel()->data(modelLevelIndex).toString().contains("W"))
                bRet = false;
            else
                bRet = true;
        }
        if(bRet == true && !mFilterMgr->getShowE())
        {
            if(sourceModel()->data(modelLevelIndex).toString().contains("E"))
                bRet = false;
            else
                bRet = true;
        }
        if(bRet == true && !mFilterMgr->getShowF())
        {
            if(sourceModel()->data(modelLevelIndex).toString().contains("F"))
                bRet = false;
            else
                bRet = true;
        }

        /* pid */
        if(bRet == true && mFilterMgr->getUsePid())
        {
            if(sourceModel()->data(modelPidIndex).toString().contains(mFilterMgr->getPiValue()))
                bRet = true;
            else
                bRet = false;
        }

        /* tid */
        if(bRet == true && mFilterMgr->getUseTid())
        {
            if(sourceModel()->data(modelTidIndex).toString().contains(mFilterMgr->getTidValue()))
                bRet = true;
            else
                bRet = false;
        }

        /* tag */
        if(bRet == true && mFilterMgr->getUseTag())
        {
            if(sourceModel()->data(modelTagIndex).toString().contains(mFilterMgr->getTagValue()))
                bRet = true;
            else
                bRet = false;
        }

        /* msg show */
        if(bRet == true && mFilterMgr->getUseMsgShow())
        {
            if(sourceModel()->data(modelMsgIndex).toString().contains(mFilterMgr->getMsgShowValue()))
                bRet = true;
            else
                bRet = false;
        }

        /* msg hide */
        if(bRet == true && mFilterMgr->getUseMsgHide())
        {
            if(sourceModel()->data(modelMsgIndex).toString().contains(mFilterMgr->getMsgHideValue()))
                bRet = false;
            else
                bRet = true;
        }
    }

    return bRet;
}

void LogProxyModel::updateFilterSlot()
{
    qDebug() << __FUNCTION__;
    invalidateFilter();
}

void LogProxyModel::pidTextChangedSlot(QString strPid)
{
    qDebug() << __FUNCTION__ << " / strPid:" << strPid << " / ";
    invalidateFilter();
}

void LogProxyModel::tidTextChangedSlot(QString strTid)
{
    qDebug() << __FUNCTION__ << " / strTid:" << strTid;
    //invalidateFilter();
}
