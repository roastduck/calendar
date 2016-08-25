#-------------------------------------------------
#
# Project created by QtCreator 2016-08-22T20:36:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = calendar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    html.cpp \
    tile.cpp \
    tilebar.cpp \
    sidebar.cpp \
    data.cpp \
    task.cpp \
    taskdisplay.cpp

HEADERS  += mainwindow.h \
    html.h \
    tile.h \
    tilebar.h \
    sidebar.h \
    data.h \
    task.h \
    taskdisplay.h

FORMS    += mainwindow.ui \
    tilebar.ui \
    taskdisplay.ui \
    tile.ui

TRANSLATIONS += zh_cn.ts

RESOURCES += \
    icon.qrc \
    translation.qrc
