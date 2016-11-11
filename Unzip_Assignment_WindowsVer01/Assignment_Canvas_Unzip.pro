QT += core
QT -= gui

CONFIG += c++11

TARGET = Assignment_Canvas_Unzip
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    Assignment_Canvas_Unzip.cpp

HEADERS += \
    Assignment_Canvas_Unzip.h

INCLUDEPATH += G:/Qt/zlib-1.2.8
LIBS += -LG:/Qt/zlib-1.2.8 -lz
INCLUDEPATH += G:/Qt/quazip-0.7/quazip
LIBS += -LG:/Qt/quazip-0.7/quazip/release -lquazip

