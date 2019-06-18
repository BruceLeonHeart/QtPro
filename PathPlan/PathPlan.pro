#-------------------------------------------------
#
# Project created by QtCreator 2019-06-18T11:31:22
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PathPlan
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    AStar.cpp \
    MXmlStreamReader.cpp

HEADERS  += MainWindow.h \
    AStar.h \
    MXmlStreamReader.h

FORMS    += MainWindow.ui

DISTFILES += \
    RealMap20190617 .xml
