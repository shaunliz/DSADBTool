#include "logparser.h"

LogParser::LogParser(QObject *parent) : QObject(parent)
{

}

LogParser::LogParser(THEME_TYPE value, QObject *parent)
{
    mTheme = value;
}

LogParser::LogParser(QString strLogData, QObject *parent) : QObject(parent)
{

}

void LogParser::setLogString(QString strLogData)
{
    QStringList _msgElementList = strLogData.split(" ");
    QStringList msgElementList;

    foreach(QString str, _msgElementList)
    {
        if(!str.isEmpty() && str != "")
            msgElementList.append(str);
    }

    //qDebug() << "msgElementList:" << msgElementList;

    int msgLen = msgElementList.size();

    if(msgLen >= 1) mDate = msgElementList.at(0);   /* date */
    if(msgLen >= 2) mTime = msgElementList.at(1);   /* time */
    if(msgLen >= 3) mPid = msgElementList.at(2);    /* pid */
    if(msgLen >= 4) mTid = msgElementList.at(3);    /* tid */
    if(msgLen >= 5) mLevel = msgElementList.at(4);  /* log level */
    if(msgLen >= 6) mTag = msgElementList.at(5);    /* tag */

    mMessage = "";

    if(msgLen >= 7)
        for(int i = 6; i < msgLen; i++)
            mMessage += msgElementList.at(i) + " "; /* log message */

    //qDebug() << mDate << mTime << mPid << mTid << mLevel << mTag << mMessage;
}

QString LogParser::getLine()
{
    return mLine;
}

QString LogParser::getDate()
{
    return mDate;
}

QString LogParser::getTime()
{
    return mTime;
}

QString LogParser::getLevel()
{
    return mLevel;
}

QString LogParser::getPid()
{
    return mPid;
}

QString LogParser::getTid()
{
    return mTid;
}

QString LogParser::getTag()
{
    return mTag;
}

QString LogParser::getMessage()
{
    return mMessage;
}

QColor LogParser::getLogColor()
{
    QColor retColor(Qt::black);

    if(mLevel.compare("v", Qt::CaseInsensitive) == 0)
    {
        if(mTheme == THEME_TYPE::COMBINEAR)
            retColor = QColor("#C0C0C0");
        else if(mTheme == THEME_TYPE::DARKEUM)
            retColor = QColor("#E0E0E0");
        else if(mTheme == THEME_TYPE::DIFFNES)
            retColor = QColor("#E0E0E0");
        else if(mTheme == THEME_TYPE::FIBERS)
            retColor = QColor("#E0E0E0");
        else if(mTheme == THEME_TYPE::IRRORATER)
            retColor = QColor(Qt::white);
    }
    else if(mLevel.compare("d", Qt::CaseInsensitive) == 0)
    {
        if(mTheme == THEME_TYPE::ADAPTIC)
            retColor = QColor("#00FFFF");
        else if(mTheme == THEME_TYPE::COMBINEAR)
            retColor = QColor("#0099FF");
        else if(mTheme == THEME_TYPE::DARKEUM)
            retColor = QColor("#0099FF");
        else if(mTheme == THEME_TYPE::DIFFNES)
            retColor = QColor("#0099FF");
        else if(mTheme == THEME_TYPE::FIBERS)
            retColor = QColor("#00FFFF");
        else if(mTheme == THEME_TYPE::IRRORATER)
            retColor = QColor("#0080FF");
        else
            retColor = QColor(Qt::blue);
    }
    else if(mLevel.compare("i", Qt::CaseInsensitive) == 0)
    {
        if(mTheme == THEME_TYPE::ADAPTIC)
            retColor = QColor("#00FF00");
        else if(mTheme == THEME_TYPE::COMBINEAR)
            retColor = QColor("#00CC00");
        else if(mTheme == THEME_TYPE::DARKEUM)
                retColor = QColor("#00CC00");
        else if(mTheme == THEME_TYPE::DIFFNES)
            retColor = QColor("#00CC00");
        else if(mTheme == THEME_TYPE::FIBERS)
            retColor = QColor("#00FF00");
        else if(mTheme == THEME_TYPE::INTEGRID)
            retColor = QColor("#009900");
        else if(mTheme == THEME_TYPE::IRRORATER)
            retColor = QColor("#00CC00");
        else
            retColor = QColor(Qt::darkGreen);
    }
    else if(mLevel.compare("w", Qt::CaseInsensitive) == 0)
    {
        if(mTheme == THEME_TYPE::ADAPTIC)
            retColor = QColor("#FFFF33");
        else if(mTheme == THEME_TYPE::COMBINEAR)
            retColor = QColor("#FFFF00");
        else if(mTheme == THEME_TYPE::DARKEUM)
            retColor = QColor("#FFFF00");
        else if(mTheme == THEME_TYPE::DIFFNES)
            retColor = QColor("#FFFF00");
        else if(mTheme == THEME_TYPE::FIBERS)
            retColor = QColor("#FFFF33");
        else if(mTheme == THEME_TYPE::INTEGRID)
            retColor = QColor("#A8A800");
        else if(mTheme == THEME_TYPE::IRRORATER)
            retColor = QColor("#FFFF00");
        else
            retColor = QColor(Qt::darkYellow);
    }
    else if(mLevel.compare("e", Qt::CaseInsensitive) == 0)
    {
        if(mTheme == THEME_TYPE::ADAPTIC)
            retColor = QColor("#A50010");
        else if(mTheme == THEME_TYPE::COMBINEAR)
            retColor = QColor(Qt::red);
        else if(mTheme == THEME_TYPE::DARKEUM)
            retColor = QColor("#FF0000");
        else if(mTheme == THEME_TYPE::DIFFNES)
            retColor = QColor("#FF0000");
        else if(mTheme == THEME_TYPE::FIBERS)
            retColor = QColor("#FFCCCC");
        else
            retColor = QColor(Qt::red);
    }
    else if(mLevel.compare("f", Qt::CaseInsensitive) == 0)
    {
        if(mTheme == THEME_TYPE::ADAPTIC)
            retColor = QColor("#FF99FF");
        else if(mTheme == THEME_TYPE::COMBINEAR)
            retColor = QColor(Qt::magenta);
        else if(mTheme == THEME_TYPE::DARKEUM)
            retColor = QColor(Qt::magenta);
        else if(mTheme == THEME_TYPE::DIFFNES)
            retColor = QColor(Qt::magenta);
        else if(mTheme == THEME_TYPE::FIBERS)
            retColor = QColor(Qt::magenta);
        else
            retColor = QColor(Qt::magenta);
    }
    else
    {
        if(mTheme == THEME_TYPE::COMBINEAR)
            retColor = QColor("#C0C0C0");
        else if(mTheme == THEME_TYPE::DARKEUM)
                retColor = QColor("#E0E0E0");
        else if(mTheme == THEME_TYPE::DIFFNES)
            retColor = QColor("#E0E0E0");
        else if(mTheme == THEME_TYPE::IRRORATER)
            retColor = QColor(Qt::white);
    }

    return retColor;
}

void LogParser::setThemeType(THEME_TYPE value)
{
    mTheme = value;
}
