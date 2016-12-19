QT += core
QT -= gui

CONFIG += c++11

TARGET = Canvas_ZipFileRules
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    smtp.cpp \
    zipfile.cpp

HEADERS += \
    smtp.h \
    zipfile.h

INCLUDEPATH += G:/Qt/zlib-1.2.8
LIBS += -LG:/Qt/zlib-1.2.8 -lz
INCLUDEPATH += G:/Qt/quazip-0.7/quazip
LIBS += -LG:/Qt/quazip-0.7/quazip/release -lquazip


