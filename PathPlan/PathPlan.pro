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
    Cephes/const.cpp \
    Cephes/fresnl.cpp \
    OpenDrive/Junction.cpp \
    OpenDrive/Lane.cpp \
    OpenDrive/ObjectSignal.cpp \
    OpenDrive/OpenDrive.cpp \
    OpenDrive/OpenDriveXmlParser.cpp \
    OpenDrive/OpenDriveXmlWriter.cpp \
    OpenDrive/OtherStructures.cpp \
    OpenDrive/Road.cpp \
    OpenDrive/RoadGeometry.cpp \
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    Cephes/polevl.c
    #Algs/AStar.cpp

HEADERS  += MainWindow.h \
    Cephes/mconf.h \
    OpenDrive/Junction.h \
    OpenDrive/Lane.h \
    OpenDrive/ObjectSignal.h \
    OpenDrive/OpenDrive.h \
    OpenDrive/OpenDriveXmlParser.h \
    OpenDrive/OpenDriveXmlWriter.h \
    OpenDrive/OtherStructures.h \
    OpenDrive/Road.h \
    OpenDrive/RoadGeometry.h \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h
    #Algs/AStar.h

FORMS    += MainWindow.ui

DISTFILES += \
    RealMap20190617 .xml \
    demomap.xml
