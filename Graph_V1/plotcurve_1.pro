#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T21:40:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = plotcurve_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    student.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    student.h

FORMS    += mainwindow.ui
