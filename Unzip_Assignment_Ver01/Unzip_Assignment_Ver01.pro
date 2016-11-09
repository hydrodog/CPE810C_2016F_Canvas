QT += core
QT -= gui

CONFIG += c++11

TARGET = Unzip_Assignment_Ver01
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
#Set variables
QUAZIPCODEIR = "/Users/fangmingzhao/course/Project/LOP/quazip-0.7.2/quazip"
ZLIBCODEDIR = "/Users/fangmingzhao/course/Project/LOP/zlib-1.2.8"
CUSTMOHL ="/Users/fangmingzhao/course/Project/LOP/customclass"


#include the compiled code
unix {
    LIBS += -L$${ZLIBCODEDIR} -lz
}
#include files

INCLUDEPATH += $${QUAZIPCODEIR}
HEADERS += $${QUAZIPCODEIR}/*.h \
    Assignment_Unzip.hh


SOURCES += $${QUAZIPCODEIR}/*.cpp \
    Assignment_Unzip.cpp
SOURCES += $${QUAZIPCODEIR}/*.c

SOURCES += main.cpp
