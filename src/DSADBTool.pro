#-------------------------------------------------
#
# Project created by QtCreator 2021-04-21T23:10:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DSADBTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        adbmanager.cpp \
        const.cpp \
        devicemanager.cpp \
        dialogs/aboutdialog.cpp \
        filtermanager.cpp \
        inimanager.cpp \
        iothread.cpp \
        ioworker.cpp \
        logparser.cpp \
        logparserthread.cpp \
        logproxymodel.cpp \
        main.cpp \
        mainwindow.cpp \
        dialogs/messagedialog.cpp \
        dialogs/preferencesdialog.cpp \
        statusmonitor.cpp \
        thememanager.cpp \
        updatemanager.cpp \
        updatethread.cpp

HEADERS += \
        adbmanager.h \
        const.h \
        devicemanager.h \
        dialogs/aboutdialog.h \
        filtermanager.h \
        inimanager.h \
        iothread.h \
        ioworker.h \
        logparser.h \
        logparserthread.h \
        logproxymodel.h \
        mainwindow.h \
        dialogs/messagedialog.h \
        dialogs/preferencesdialog.h \
        statusmonitor.h \
        thememanager.h \
        updatemanager.h \
        updatethread.h

FORMS += \
        dialogs/aboutdialog.ui \
        mainwindow.ui \
        dialogs/messagedialog.ui \
        dialogs/preferencesdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

INCLUDEPATH += ./dialogs
