#-------------------------------------------------
#
# Project created by QtCreator 2019-06-24T16:21:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pathPlan2
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    OpenDrive/OpenDriveParser.cpp

HEADERS  += MainWindow.h \
    OpenDrive/OpenDriveParser.h

FORMS    += MainWindow.ui

DISTFILES += \
    demomap.xml
