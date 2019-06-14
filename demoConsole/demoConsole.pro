QT += core
QT -= gui

TARGET = demoConsole
CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    ../demoSoPro/demosopro_global.h \
    ../demoSoPro/DemoSoPro.h



unix:!macx: LIBS += -L$$PWD/../build-demoSoPro-unknown-Debug/ -ldemoSoPro

INCLUDEPATH += $$PWD/../build-demoSoPro-unknown-Debug
DEPENDPATH += $$PWD/../build-demoSoPro-unknown-Debug
