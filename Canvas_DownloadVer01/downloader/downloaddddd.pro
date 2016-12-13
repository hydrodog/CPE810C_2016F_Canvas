QT += core
QT -= gui
QT += network
CONFIG += c++11

TARGET = downloaddddd
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    download.cpp

HEADERS += \
    downloader.h
