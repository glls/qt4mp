#-------------------------------------------------
#
# Project created by QtCreator 2016-01-02T15:24:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt4mp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    consolerunner.cpp

HEADERS  += mainwindow.h \
    config.h \
    consolerunner.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources/icons.qrc
