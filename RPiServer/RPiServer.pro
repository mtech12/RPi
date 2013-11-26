#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T21:17:43
#
#-------------------------------------------------

INCLUDEPATH += /home/ubuntu/RPi/MT500_lib

QT       += core \
            gui \
            network

TARGET = RPiServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    rpiserver.cpp \
    ../MT500_lib/tcpserver.cpp \
    ../MT500_lib/tcpclient.cpp \
    ../MT500_lib/dataprotocol.cpp \
    ../MT500_lib/commandparser.cpp \
    ../MT500_lib/utilities.cpp \
    ../MT500_lib/imageprocessor.cpp

HEADERS += \
    rpiserver.h \
    ../MT500_lib/tcpserver.h \
    ../MT500_lib/tcpclient.h \
    ../MT500_lib/dataprotocol.h \
    ../MT500_lib/commandparser.h \
    ../MT500_lib/utilities.h \
    ../MT500_lib/imageprocessor.h
