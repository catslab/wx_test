#-------------------------------------------------
#
# Project created by QtCreator 2015-02-02T15:44:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pruss_wx
TEMPLATE = app

DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += main.cpp\
        mainwindow.cpp \
    adcthread.cpp \
    datamanagement.cpp

LIBS +=-lprussdrv
#LIBS +=libprussdrv.so
INCLUDEPATH +=/Users/cedric/Development/BeagleBone/sysroot/include/pruss
QMAKE_LIBDIR+=/Users/cedric/Development/BeagleBone/sysroot/lib

HEADERS  += mainwindow.h \
    adcthread.h \
    common.h \
    datamanagement.h \
    myconstants.h

FORMS    += mainwindow.ui

# install
target.path = /root/pruss_wx5
INSTALLS += target
