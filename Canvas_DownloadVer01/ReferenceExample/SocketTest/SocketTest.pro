QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = SocketTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sockettest.cpp

HEADERS += \
    sockettest.h
