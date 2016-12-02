QT += core
QT -= gui

CONFIG += c++11

TARGET = SmtpClient
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    emailaddress.cpp \
    mimeattachment.cpp \
    mimecontentformatter.cpp \
    mimefile.cpp \
    mimehtml.cpp \
    mimeinlinefile.cpp \
    mimemessage.cpp \
    mimemultipart.cpp \
    mimepart.cpp \
    mimetext.cpp \
    quotedprintable.cpp \
    smtpclient.cpp

HEADERS += \
    emailaddress.h \
    mimeattachment.h \
    mimecontentformatter.h \
    mimefile.h \
    mimehtml.h \
    mimeinlinefile.h \
    mimemessage.h \
    mimemultipart.h \
    mimepart.h \
    mimetext.h \
    quotedprintable.h \
    smtpclient.h \
    smtpexports.h
