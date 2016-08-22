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
    monthmodel.cpp \
    model.cpp

HEADERS  += mainwindow.h \
    monthmodel.h \
    model.h

FORMS    += mainwindow.ui

TRANSLATIONS += zh_cn.ts
