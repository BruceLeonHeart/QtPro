#-------------------------------------------------
#
# Project created by QtCreator 2019-07-04T14:31:31
#
#-------------------------------------------------

QT       += core gui
QT  +=  printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = pathPlan5
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Path_Plan/AStarRoute/AStarRoute.cpp \
        Path_Plan/OpenDrive/OpenDriveParser.cpp \
        Path_Plan/OpenDrive/OpenDriveStruct.cpp \
        Path_Plan/TinyXML/tinystr.cpp \
        Path_Plan/TinyXML/tinyxml.cpp \
        Path_Plan/TinyXML/tinyxmlerror.cpp \
        Path_Plan/TinyXML/tinyxmlparser.cpp \
        Path_Plan/Utils/mathUtils.c \
        main.cpp \
        MainWindow.cpp \
        qcustomplot.cpp

HEADERS += \
        MainWindow.h \
        Path_Plan/AStarRoute/AStarRoute.h \
        Path_Plan/OpenDrive/OpenDriveParser.h \
        Path_Plan/OpenDrive/OpenDriveStruct.h \
        Path_Plan/TinyXML/tinystr.h \
        Path_Plan/TinyXML/tinyxml.h \
        Path_Plan/Utils/mathUtils.h \
        qcustomplot.h

FORMS += \
        MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    RealMap2.xml \
    demomap.xml
