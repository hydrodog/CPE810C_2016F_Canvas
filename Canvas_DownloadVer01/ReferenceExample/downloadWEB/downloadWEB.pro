QT += core
QT -= gui
QT += network
QT += widgets
CONFIG += c++11

TARGET = downloadWEB
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    httpfun.cpp

HEADERS += \
    httpfun.h
