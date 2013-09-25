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
    padwindow.cpp \
    app.cpp \
    propertieswindow.cpp \
    properties.cpp \
    padserializer.cpp

HEADERS  += \
    pad.h \
    padgroup.h \
    padwindow.h \
    app.h \
    propertieswindow.h \
    properties.h \
    padserializer.h

FORMS    += \
    padwindow.ui \
    propertieswindow.ui
