QT += core
QT -= gui
QT += network
CONFIG += c++11

TARGET = CanvasUpdate
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    canvasupdate.cpp

HEADERS += \
    canvasupdate.h
