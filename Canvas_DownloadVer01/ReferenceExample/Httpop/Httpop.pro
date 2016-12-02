QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = Httpop
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    httpop.cpp

HEADERS += \
    httpop.h
