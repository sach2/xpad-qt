#-------------------------------------------------
#
# Project created by QtCreator 2013-09-07T14:59:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xpad-qt
TEMPLATE = app


SOURCES += main.cpp\
    pad.cpp \
    padgroup.cpp \
    padwindow.cpp

HEADERS  += \
    pad.h \
    padgroup.h \
    padwindow.h

FORMS    += \
    padwindow.ui
