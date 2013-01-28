#-------------------------------------------------
#
# Project created by QtCreator 2012-12-29T23:08:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtimage
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    myscene.cpp

HEADERS  += widget.h \
    myscene.h

FORMS    += widget.ui

RC_FILE += myrc.rc
