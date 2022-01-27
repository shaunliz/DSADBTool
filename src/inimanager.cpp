#include "inimanager.h"

IniManager* IniManager::instance;

IniManager::IniManager(QObject *parent) : QObject(parent)
{

}

IniManager* IniManager::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new IniManager();
    }

    return instance;
}

void IniManager::setUseAdbPath(bool value)
{
    QSettings settings(SETTING_FILE, QSettings::IniFormat);
    settings.setValue("USE_ADB_PATH", value);
}

bool IniManager::getUseAdbPath()
{
    QSettings settings(SETTING_FILE, QSettings::IniFormat);
    return settings.value("USE_ADB_PATH", false).toBool();
}

void IniManager::setAdbPath(QString filePath)
{
    QSettings settings(SETTING_FILE, QSettings::IniFormat);
    settings.setValue("ADB_PATH", filePath);
}

QString IniManager::getAdbPath()
{
    QSettings settings(SETTING_FILE, QSettings::IniFormat);
    return settings.value("ADB_PATH", "adb.exe").toString() + " ";
}


