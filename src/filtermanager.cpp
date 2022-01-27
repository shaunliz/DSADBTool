#include "filtermanager.h"

FilterManager::FilterManager(QObject *parent) : QObject(parent)
{

}

void FilterManager::initFilter()
{
    mShowV = true;
    mShowD = true;
    mShowI = true;
    mShowW = true;
    mShowE = true;
    mShowF = true;

    mUsePid = false;
    mPidValue = "";
    mUseTid = false;
    mTidValue = "";
    mUseTag = false;
    mTagValue = "";
    mUseMsgShow = false;
    mMsgShowValue = "";
    mUseMsgHide = false;
    mMsgHideValue = "";
}

void FilterManager::setShowV(bool value)
{
    mShowV = value;
    emit updateFilterSig();
}

bool FilterManager::getShowV()
{
    return mShowV;
}

void FilterManager::setShowD(bool value)
{
    mShowD = value;
    emit updateFilterSig();
}

bool FilterManager::getShowD()
{
    return mShowD;
}

void FilterManager::setShowI(bool value)
{
    mShowI = value;
}

bool FilterManager::getShowI()
{
    return mShowI;
}

void FilterManager::setShowW(bool value)
{
    mShowW = value;
}

bool FilterManager::getShowW()
{
    return mShowW;
}

void FilterManager::setShowE(bool value)
{
    mShowE = value;
}

bool FilterManager::getShowE()
{
    return mShowE;
}

void FilterManager::setShowF(bool value)
{
    mShowF = value;
}

bool FilterManager::getShowF()
{
    return mShowF;
}

bool FilterManager::getUsePid()
{
    return mUsePid;
}

void FilterManager::setUsePid(bool value)
{
    mUsePid = value;
}

QString FilterManager::getPiValue()
{
    return mPidValue;
}

void FilterManager::setPidValue(QString value)
{
    mPidValue = value;
}

bool FilterManager::getUseTid()
{
    return mUseTid;
}

QString FilterManager::getTidValue()
{
    return mTidValue;
}

bool FilterManager::getUseTag()
{
    return mUseTag;
}

QString FilterManager::getTagValue()
{
    return mTagValue;
}

bool FilterManager::getUseMsgShow()
{
    return mUseMsgShow;
}

QString FilterManager::getMsgShowValue()
{
    return mMsgShowValue;
}


bool FilterManager::getUseMsgHide()
{
    return mUseMsgHide;
}

QString FilterManager::getMsgHideValue()
{
    return mMsgHideValue;
}

void FilterManager::pidFilterChangedSlot(int value)
{
    if(value == 0)
        mUsePid = false;
    else
        mUsePid = true;

    emit updateFilterSig();
}

void FilterManager::pidTextChangedSlot(QString value)
{
    mPidValue = value;

    emit updateFilterSig();
}

void FilterManager::tidFilterChangedSlot(int value)
{
    if(value == 0)
        mUseTid = false;
    else
        mUseTid = true;

    emit updateFilterSig();
}

void FilterManager::tidTextChangedSlot(QString value)
{
    mTidValue = value;

    emit updateFilterSig();
}

void FilterManager::tagFilterChangedSlot(int value)
{
    if(value == 0)
        mUseTag = false;
    else
        mUseTag = true;

    emit updateFilterSig();
}

void FilterManager::tagTextChangedSlot(QString value)
{
    mTagValue = value;

    emit updateFilterSig();
}

void FilterManager::msgShowFilterChangedSlot(int value)
{
    if(value == 0)
        mUseMsgShow = false;
    else
        mUseMsgShow = true;

    emit updateFilterSig();
}

void FilterManager::msgShowTextChangedSlot(QString value)
{
    mMsgShowValue = value;

    emit updateFilterSig();
}

void FilterManager::msgHideFilterChangedSlot(int value)
{
    if(value == 0)
        mUseMsgHide = false;
    else
        mUseMsgHide = true;

    emit updateFilterSig();
}

void FilterManager::msgHideTextChangedSlot(QString value)
{
    mMsgHideValue = value;

    emit updateFilterSig();
}
