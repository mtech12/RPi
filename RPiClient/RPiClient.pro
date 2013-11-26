#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T20:49:22
#
#-------------------------------------------------

INCLUDEPATH += /home/administrator/MT500_lib/

QT       += core \
            gui \
            network

TARGET = RPiClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    rpiclient.cpp \
    /home/administrator/MT500_lib/imageprocessor.cpp \
    /home/administrator/MT500_lib/dataprotocol.cpp \
    /home/administrator/MT500_lib/tcpserver.cpp \
    /home/administrator/MT500_lib/commandparser.cpp \
    /home/administrator/MT500_lib/utilities.cpp \
    /home/administrator/MT500_lib/tcpclient.cpp

HEADERS += \
    rpiclient.h \
    /home/administrator/MT500_lib/imageprocessor.h \
    /home/administrator/MT500_lib/dataprotocol.h \
    /home/administrator/MT500_lib/tcpserver.h \
    /home/administrator/MT500_lib/commandparser.h \
    /home/administrator/MT500_lib/utilities.h \
    /home/administrator/MT500_lib/tcpclient.h
