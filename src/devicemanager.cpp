#include "devicemanager.h"

DeviceManager* DeviceManager::instance;// = nullptr;

DeviceManager::DeviceManager(QObject *parent) : QObject(parent)
{
}

DeviceManager* DeviceManager::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new DeviceManager();
    }
    return instance;
}

void DeviceManager::setDeviceNameList(QList<QString> strListDevice)
{
    deviceNameList.clear();
    deviceNameList = strListDevice;
}

QList<QString> DeviceManager::getDeviceNameList()
{
    return deviceNameList;
}

void DeviceManager::setSelectedDeviceName(QString strDevName)
{
    qInfo() << __FUNCTION__ << " / strDevName:" << strDevName;
    selectedDeviceName = strDevName;
}

QString DeviceManager::getSelectedDeviceName()
{
    return selectedDeviceName;
}
