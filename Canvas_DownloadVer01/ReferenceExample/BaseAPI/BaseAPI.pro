QT += core
QT -= gui
QT += network
CONFIG += c++11

TARGET = BaseAPI
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    baseapi.cpp

HEADERS += \
    baseapi.h
