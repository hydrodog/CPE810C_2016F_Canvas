QT += core
QT -= gui

CONFIG += c++11

TARGET = Curving
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    curving.cpp

HEADERS += \
    curving.h
