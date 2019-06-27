#-------------------------------------------------
#
# Project created by QtCreator 2019-06-07T14:48:12
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PZ1_AD
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
        CAN_Driver/LikeCanDriver.c \
        GPS_Driver/an_packet_protocol.c \
        GPS_Driver/packet_example.c \
        GPS_Driver/rs232/rs232.c \
        GPS_Driver/spatial_packets.c \
        Pure_Pursuit_Contorl/Pure_Pursuit.cpp \
        main.cpp \
        mainwindow.cpp \
        qcustomplot.cpp

HEADERS += \
        CAN_Driver/ICANCmd.h \
        GPS_Driver/an_packet_protocol.h \
        GPS_Driver/rs232/rs232.h \
        GPS_Driver/spatial_packets.h \
        Pure_Pursuit_Contorl/Pure_Pursuit.h \
        mainwindow.h \
        qcustomplot.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/./ -lCanCmd

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

RESOURCES += \
    resources.qrc
