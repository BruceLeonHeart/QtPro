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
    OpenDrive/mathTools.c \
    Qplot/OpenDrivePlot.cpp \
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    OpenDrive/OpenDriveStruct.cpp \
    qcustomplot.cpp

HEADERS  += MainWindow.h \
    OpenDrive/OpenDriveParser.h \
    OpenDrive/mathTools.h \
    Qplot/OpenDrivePlot.h \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h \
    OpenDrive/OpenDriveStruct.h \
    qcustomplot.h

FORMS    += MainWindow.ui

DISTFILES += \
    RealMap2.xml \
    demomap.xml
