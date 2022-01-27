#ifndef CONST_H
#define CONST_H

#include <QString>

namespace ADB_CMD
{
    static const QString ADB = "adb ";
    static const QString DEVICES = " devices";
    //static const QString DEVICES = "adb devices ";
    //static const QString BASIC = "adb ";
    //static const QString SELECT_DEVICE = "adb -s ";
    static const QString SELECT_DEVICE = " -s ";
    static const QString LOG_OPTION_BASIC = " logcat -v threadtime ";
    static const QString PACKAGE_LIST = " shell pm list packages -f -3"; /* -3 은 third party app. 만 출력하는 option. */
    static const QString LOG_CLEAR = " logcat -c";
    //static const QString INSTALL_APK = " install -r -g -t ";
    static const QString INSTALL_APK = " install -r -t ";
}

namespace DSADB_TOOL
{
    enum WORKER_CMD
    {
        CMD_RUN     = 0x01,
        CMD_STOP    = 0x02,
        CMD_PAUSE   = 0x04
    };

    enum COLUMN_LOG
    {
        DATE_LOG        = 0,
        TIME        = 1,
        LEVEL       = 2,
        PID         = 3,
        TID         = 4,
        TAG         = 5,
        MESSAGE     = 6
    };

    enum THEME_TYPE
    {
        DEFAULT     = 0,
        ADAPTIC     = 1,
        COMBINEAR   = 2,
        DARKEUM     = 3,
        DIFFNES     = 4,
        FIBERS      = 5,
        INTEGRID     = 6,
        IRRORATER   = 7
    };

    enum OP_STATUS
    {
        STATUS_STOP        = 0,
        STATUS_PLAY        = 1,
        STATUS_PAUSE       = 2
    };

    enum LOG_LEVEL
    {
        VERBOSE            = 0x01,
        DEBUG              = 0x02,
        INFO               = 0x04,
        WARN               = 0x08,
        ERROR_LOG              = 0x10,
        FATAL              = 0x20
    };

    enum SHOW_COLUMN
    {
        COL_DATE                = 0x01,
        COL_TIME                = 0x02,
        COL_LEVEL               = 0x04,
        COL_PID                 = 0x08,
        COL_TID                 = 0x10,
        COL_TAG                 = 0x20,
        COL_MESSAGE             = 0x40
    };
}

class Const
{
public:
    Const();
};

#endif // CONST_H
