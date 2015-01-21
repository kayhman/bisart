#-------------------------------------------------
#
# Project created by QtCreator 2015-01-16T09:07:25
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cxonsole
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qconsole.cpp \
    glWidget.cpp \
    parser.cpp

HEADERS  += mainwindow.h \
    qconsole.h \
    glWidget.h \
    singleton.h \
    parser.h

FORMS    += mainwindow.ui

#INCLUDEPATH += deps/include
#INCLUDEPATH += freeglut/include/


INCLUDEPATH += /usr/include/lua5.2

#LIBS += ../cxonsole/deps/lua52.lib
#LIBS += ../cxonsole/freeglut/lib/freeglut.lib

LIBS += -llua5.2
LIBS += -lGLU
