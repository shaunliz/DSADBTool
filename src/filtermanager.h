#ifndef FILTERMANAGER_H
#define FILTERMANAGER_H

#include <QObject>
#include <QDebug>

class FilterManager : public QObject
{
    Q_OBJECT
public:
    explicit FilterManager(QObject *parent = nullptr);

    void initFilter();

    void setShowV(bool value);
    bool getShowV();
    void setShowD(bool value);
    bool getShowD();
    void setShowI(bool value);
    bool getShowI();
    void setShowW(bool value);
    bool getShowW();
    void setShowE(bool value);
    bool getShowE();
    void setShowF(bool value);
    bool getShowF();

    bool getUsePid();
    void setUsePid(bool value);
    QString getPiValue();
    void setPidValue(QString value);

    bool getUseTid();
    QString getTidValue();

    bool getUseTag();
    QString getTagValue();

    bool getUseMsgShow();
    QString getMsgShowValue();

    bool getUseMsgHide();
    QString getMsgHideValue();

signals:
    void updateFilterSig();

public slots:
    void pidFilterChangedSlot(int value);
    void pidTextChangedSlot(QString value);
    void tidFilterChangedSlot(int value);
    void tidTextChangedSlot(QString value);
    void tagFilterChangedSlot(int value);
    void tagTextChangedSlot(QString value);
    void msgShowFilterChangedSlot(int value);
    void msgShowTextChangedSlot(QString value);
    void msgHideFilterChangedSlot(int value);
    void msgHideTextChangedSlot(QString value);

private:
    bool mShowV;
    bool mShowD;
    bool mShowI;
    bool mShowW;
    bool mShowE;
    bool mShowF;

    bool mUsePid;
    QString mPidValue;
    bool mUseTid;
    QString mTidValue;
    bool mUseTag;
    QString mTagValue;
    bool mUseMsgShow;
    QString mMsgShowValue;
    bool mUseMsgHide;
    QString mMsgHideValue;
};

#endif // FILTERMANAGER_H
