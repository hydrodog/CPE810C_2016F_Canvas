#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T21:40:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = plotcurve_1
TEMPLATE = app


SOURCES += plot.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    student.cpp \
    category.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    student.h \
    category.h

FORMS    += mainwindow.ui
