#-------------------------------------------------
#
# Project created by QtCreator 2013-11-28T15:48:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MC1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Dialogs/Preference/preferencedialog.cpp \
    Dialogs/Preference/pages.cpp

HEADERS  += mainwindow.h \
    Dialogs/Preference/preferencedialog.h \
    Dialogs/Preference/pages.h

RESOURCES += \
    mc1.qrc
