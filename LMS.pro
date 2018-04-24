#-------------------------------------------------
#
# Project created by QtCreator 2018-04-07T18:59:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LMS
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    studentinformation.cpp \
    datastorage.cpp \
    actionwidget.cpp \
    enterform.cpp

HEADERS  += mainwidget.h \
    studentinformation.h \
    datastorage.h \
    actionwidget.h \
    enterform.h

FORMS    += mainwidget.ui \
    actionwidget.ui \
    enterform.ui
