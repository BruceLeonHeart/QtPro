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
    OpenDrive/OpenDriveParser.cpp \
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    OpenDrive/OpenDriveStruct.cpp

HEADERS  += MainWindow.h \
    OpenDrive/OpenDriveParser.h \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h \
    OpenDrive/OpenDriveStruct.h

FORMS    += MainWindow.ui

DISTFILES += \
    demomap.xml
