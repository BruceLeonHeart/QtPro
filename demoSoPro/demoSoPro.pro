#-------------------------------------------------
#
# Project created by QtCreator 2019-06-12T14:01:12
#
#-------------------------------------------------

QT       -= gui

TARGET = demoSoPro
TEMPLATE = lib

DEFINES += DEMOSOPRO_LIBRARY

SOURCES += DemoSoPro.cpp

HEADERS += DemoSoPro.h\
        demosopro_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
