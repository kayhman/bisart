#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T21:13:04
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

LIBS += -lGLU

SOURCES += main.cpp\
        mainwindow.cpp \
    glWidget.cpp

HEADERS  += mainwindow.h \
    glWidget.h

FORMS    += mainwindow.ui
