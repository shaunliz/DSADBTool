#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QFile>

class ThemeManager : public QObject
{
    Q_OBJECT
public:
    explicit ThemeManager(QObject *parent = nullptr);
    //explicit ThemeManager(QObject *parent);

signals:

public slots:
    QString getDefaultTheme();
    QString getAdapticTheme();
    QString getCombinearTheme();
    QString getDarkeumTheme();
    QString getDiffnesTheme();
    QString getFibersTheme();
    QString getIntegridTheme();
    QString getIrroraterTheme();

private:
    QObject* mParent;
};

#endif // THEMEMANAGER_H
