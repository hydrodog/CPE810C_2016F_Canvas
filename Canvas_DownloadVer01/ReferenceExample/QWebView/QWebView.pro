QT += core
QT -= gui
QT += network
QT += websockets

CONFIG += c++11

TARGET = QWebView
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
