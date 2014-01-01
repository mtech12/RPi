#-------------------------------------------------
#
# Project created by QtCreator 2014-01-01T17:52:58
#
#-------------------------------------------------

INCLUDEPATH += ../../MT500_lib/

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RPiServer_ui
TEMPLATE = app


SOURCES += main.cpp \
    rpiserver.cpp \
    ../../MT500_lib/utilities.cpp \
    ../../MT500_lib/tcpserver.cpp \
    ../../MT500_lib/tcpclient.cpp \
    ../../MT500_lib/imageprocessor.cpp \
    ../../MT500_lib/dataprotocol.cpp \
    ../../MT500_lib/commandparser.cpp

HEADERS += \
    rpiserver.h \
    ../../MT500_lib/utilities.h \
    ../../MT500_lib/tcpserver.h \
    ../../MT500_lib/tcpclient.h \
    ../../MT500_lib/imageprocessor.h \
    ../../MT500_lib/dataprotocol.h \
    ../../MT500_lib/commands.h \
    ../../MT500_lib/commandparser.h

FORMS    += rpiserver.ui
