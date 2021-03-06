#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T20:49:22
#
#-------------------------------------------------

INCLUDEPATH += ../MT500_lib/

QT       += core \
            gui \
            network

TARGET = RPiClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    rpiclient.cpp \
    ../MT500_lib/imageprocessor.cpp \
    ../MT500_lib/dataprotocol.cpp \
    ../MT500_lib/tcpserver.cpp \
    ../MT500_lib/commandparser.cpp \
    ../MT500_lib/utilities.cpp \
    ../MT500_lib/tcpclient.cpp

HEADERS += \
    rpiclient.h \
    ../MT500_lib/imageprocessor.h \
    ../MT500_lib/dataprotocol.h \
    ../MT500_lib/tcpserver.h \
    ../MT500_lib/commandparser.h \
    ../MT500_lib/utilities.h \
    ../MT500_lib/tcpclient.h
