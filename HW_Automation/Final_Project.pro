QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = Final_Project
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    hw_automation.cpp \
    Course.cpp \
    Assignment.cpp \
    Submission.cpp

HEADERS += \
    hw_automation.hh \
    course.hh \
    assignment.hh \
    submission.hh \
    ../Canvas_Update/CanvasUpdate/canvasupdate.h \
    ../Curving/curving.h \
    ../Plagiarism_Detector_Ver01/PlagiarismDetector.hh

