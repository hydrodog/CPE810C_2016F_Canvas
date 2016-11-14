QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = MyFirstServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myserver.cpp

HEADERS += \
    myserver.h
