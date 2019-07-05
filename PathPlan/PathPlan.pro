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
#    Path_Plan/Cephes/const.cpp \
    Path_Plan/Cephes/fresnl.cpp \
    Path_Plan/Cephes/polevl.c \
    Path_Plan/OpenDrive/Junction.cpp \
    Path_Plan/OpenDrive/Lane.cpp \
    Path_Plan/OpenDrive/ObjectSignal.cpp \
    Path_Plan/OpenDrive/OpenDrive.cpp \
    Path_Plan/OpenDrive/OpenDriveXmlParser.cpp \
    Path_Plan/OpenDrive/OpenDriveXmlWriter.cpp \
    Path_Plan/OpenDrive/OtherStructures.cpp \
    Path_Plan/OpenDrive/Road.cpp \
    Path_Plan/OpenDrive/RoadGeometry.cpp \
    Path_Plan/TinyXML/tinystr.cpp \
    Path_Plan/TinyXML/tinyxml.cpp \
    Path_Plan/TinyXML/tinyxmlerror.cpp \
    Path_Plan/TinyXML/tinyxmlparser.cpp

HEADERS  += MainWindow.h \
    Path_Plan/Cephes/mconf.h \
    Path_Plan/OpenDrive/Junction.h \
    Path_Plan/OpenDrive/Lane.h \
    Path_Plan/OpenDrive/ObjectSignal.h \
    Path_Plan/OpenDrive/OpenDrive.h \
    Path_Plan/OpenDrive/OpenDriveXmlParser.h \
    Path_Plan/OpenDrive/OpenDriveXmlWriter.h \
    Path_Plan/OpenDrive/OtherStructures.h \
    Path_Plan/OpenDrive/Road.h \
    Path_Plan/OpenDrive/RoadGeometry.h \
    Path_Plan/TinyXML/tinystr.h \
    Path_Plan/TinyXML/tinyxml.h

FORMS    += MainWindow.ui

DISTFILES += \
    RealMap20190617 .xml \
    demomap.xml
