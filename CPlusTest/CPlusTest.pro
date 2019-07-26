TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -pthread
SOURCES += main.cpp \
    Interrupt.cpp \
    Student.cpp \
    thread.cpp

HEADERS += \
    Student.h

