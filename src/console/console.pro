#-------------------------------------------------
#
# Project created by QtCreator 2015-01-15T20:46:25
#
#-------------------------------------------------

QT       += core gui widgets # widgets added

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = console
TEMPLATE = app


SOURCES += main.cpp\
        console.cpp\
        mainwindow.cpp
        

HEADERS  += mainwindow.h\
            console.h

FORMS    += mainwindow.ui

LIBS += -llua5.2

INCLUDEPATH += /usr/include/lua5.2/
