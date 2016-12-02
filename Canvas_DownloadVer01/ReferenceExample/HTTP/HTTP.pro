QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = HTTP
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    downloadmanager.cpp

HEADERS += \
    downloadmanager.h
