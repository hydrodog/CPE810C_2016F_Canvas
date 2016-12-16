QT += core
QT -= gui

CONFIG += c++11

TARGET = hujingyi
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    canvasconnection.cpp

HEADERS += \
    canvasconnection.h
