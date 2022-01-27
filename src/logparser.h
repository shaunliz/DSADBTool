#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <QObject>
#include <QDebug>
#include <QColor>

#include "const.h"

using namespace DSADB_TOOL;

class LogParser : public QObject
{
    Q_OBJECT
public:
    explicit LogParser(QObject *parent = nullptr);
    explicit LogParser(THEME_TYPE value, QObject *parent = nullptr);
    explicit LogParser(QString strLogData, QObject *parent = nullptr);

    void setLogString(QString strLogData);
    QString getLine();
    QString getDate();
    QString getTime();
    QString getLevel();
    QString getPid();
    QString getTid();
    QString getTag();
    QString getMessage();
    QColor  getLogColor();
    void setThemeType(THEME_TYPE value);

signals:

private:
    QString mLogData;
    QString mLine;
    QString mDate;
    QString mTime;
    QString mLevel;
    QString mPid;
    QString mTid;
    QString mTag;
    QString mMessage;
    THEME_TYPE mTheme;
};

#endif // LOGPARSER_H
