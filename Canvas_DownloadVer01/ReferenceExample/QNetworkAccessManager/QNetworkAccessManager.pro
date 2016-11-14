QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = QNetworkAccessManager
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    downloader.cpp

HEADERS += \
    downloader.h
