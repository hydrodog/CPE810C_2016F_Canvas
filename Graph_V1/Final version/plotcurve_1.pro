#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T21:40:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = plotcurve_1
TEMPLATE = app


SOURCES += plot.cpp\
    qcustomplot.cpp \
    student.cpp \
    Distribution.cpp \
    canvasconnection.cpp

HEADERS  += \
    qcustomplot.h \
    student.h \
    Distribution.h \
    canvasconnection.h

FORMS    += mainwindow.ui
