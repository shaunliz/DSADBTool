#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QDebug>

class DeviceManager : public QObject
{
    Q_OBJECT


public:
    static DeviceManager* GetInstance();

    void setDeviceNameList(QList<QString> strListDevice);
    QList<QString> getDeviceNameList();
    void setSelectedDeviceName(QString strDevName);
    QString getSelectedDeviceName();


signals:


private:
    explicit DeviceManager(QObject *parent = nullptr);
    static DeviceManager* instance;

    QList<QString> deviceNameList;
    QString selectedDeviceName;


public slots:
};

#endif // DEVICEMANAGER_H
