#include "thememanager.h"

ThemeManager::ThemeManager(QObject *parent) : QObject(parent)
  , mParent(parent)
{
}



/* slots */
QString ThemeManager::getDefaultTheme()
{
    return QString();
}

QString ThemeManager::getAdapticTheme()
{
    QFile styleSheetFile(":/qss/theme/Adaptic/Adaptic.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    return styleSheet;
}

QString ThemeManager::getCombinearTheme()
{
    QFile styleSheetFile(":/qss/theme/Combinear/Combinear.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    return styleSheet;
}

QString ThemeManager::getDarkeumTheme()
{
    QFile styleSheetFile(":/qss/theme/Darkeum/Darkeum.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    return styleSheet;
}

QString ThemeManager::getDiffnesTheme()
{
    QFile styleSheetFile(":/qss/theme/Diffnes/Diffnes.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    return styleSheet;
}

QString ThemeManager::getFibersTheme()
{
    QFile styleSheetFile(":/qss/theme/Fibers/Fibers.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    return styleSheet;
}

QString ThemeManager::getIntegridTheme()
{
    QFile styleSheetFile(":/qss/theme/Integrid/Integrid.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    return styleSheet;
}

QString ThemeManager::getIrroraterTheme()
{
    QFile styleSheetFile(":/qss/theme/Irrorater/Irrorater.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    return styleSheet;
}
