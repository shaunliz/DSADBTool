#ifndef INIMANAGER_H
#define INIMANAGER_H

#include <QObject>
#include <QSettings>

#include "const.h"

using namespace DSADB_TOOL;

#define SETTING_FILE    "settings.ini"

class IniManager : public QObject
{
    Q_OBJECT

public:
    static IniManager * GetInstance();

    void setUseAdbPath(bool value);
    bool getUseAdbPath();
    void setAdbPath(QString filePath);
    QString getAdbPath();

private:
    explicit IniManager(QObject *parent = nullptr);
    static IniManager * instance;

signals:

};

#endif // INIMANAGER_H
