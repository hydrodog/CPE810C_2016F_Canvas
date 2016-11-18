#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T13:06:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutomaticshiftingofDate
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    createassignmententry.cpp \
    createassignment.cpp \
    createassignmentcontroller.cpp \
    holiday.cpp

HEADERS  += mainwindow.h \
    createassignmententry.h \
    createassignment.h \
    createassignmentcontroller.h \
    holiday.h

FORMS    += mainwindow.ui
